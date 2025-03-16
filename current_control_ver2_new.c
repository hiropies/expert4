/*
  20200630メモ
  H33は計算合うのにH11は合わない。式が長すぎるのが原因か？
  20200701メモ
  1/2とかの分数が途中で入るとバグるので0.5などの小数表記にする
  20210507メモ
  powは計算コストがかかるようなのでx*xにする
  ライブラリにしたい
  mainでつかうものとinterruptで使うものを明確に
  mainのやつは処理重くてもよい
  構造体多い 引数で使うとき注意

  pevボードの対応は毎回要チェック
  全体を作ってから制御手法が違うもので分けたほうがいいかも

*/

/*
20220304 FDTD離散FF制御　2軸目対象
指令値の加減速時間　及び　FBゲインン倍率が姿勢によって違うことに注意
1軸目ZOHオブザーバの設計値　JLの最大値
初期姿勢値　注意
*/

#include <mwio4.h>
#include "enc.h"
#include <math.h>
#include <complex.h>

// Expert関連定数
//  BDN 無印は引数用

#define BDN0 0    //!< PEVボード番号 1軸
#define BDN1 1    //!< PEVボード番号 2軸
#define BDN2 2    //!< PEVボード番号 3軸
#define BDN_ENC 2 //!< エンコーダボード番号, PEVボード番号と非排他なので無問題
#define ENC_CH0 0 //!< 駆動側エンコーダ情報取得用のエンコーダボードチャンネル
#define ENC_CH1 2 //!< 駆動側エンコーダ情報取得用のエンコーダボードチャンネル
#define ENC_CH2 1 //!< 駆動側エンコーダ情報取得用のエンコーダボードチャンネル

#define axis1 joint[0] // 配列と軸の番号が違う(0,1,2 と 1,2,3）ので間違えないように
#define axis2 joint[1] // なるべくこっちを使う
#define axis3 joint[2] //  ex) axis1.theta_rm など.

#define START 1
#define CTRL_ON 2
#define STOP 0

#define QL1_MAX 5.0
#define QL1_MIN -5.0
#define QL2_MAX 50.0
#define QL2_MIN -10.0
#define QL3_MAX 10.0
#define QL3_MIN -10.0

/// 制御用定数
static const float PI = 3.14159265358979; /// 円周率
static const float Fs = 8000;            /// キャリア周波数[Hz]
static const float Ts = 125e-6;           /// [s]	電流制御系の制御周期 (Fsを変えたら変えること)
static const float Tp = 250e-6;           /// [s]	位置/速度制御系の制御周期
static const float cmd_1_soft[] = {-1.094, -1.094};
static const float cmd_2_soft[] = {87.72, 87.72};
static const float cmd_3_soft[] = {-0.388, -0.388};
static const float cmd_1_hard[] = {-1.094, -1.094};
static const float cmd_2_hard[] = {87.72, 87.72};
static const float cmd_3_hard[] = {-0.388, -0.388};
static const float scale = 2.5;
static const float scale_fast = 7.5;
static const float scale_slow = 7.5;
static float start_hand[3] = {1.2746, -0.010, 0.2466};
// static float start_hand[3] = {1.2746, -0.07071, 0.2466}; //{1.2746, 0.000, 0.2466}を中心としたひし形のスタート地点
// static float start_hand[3] = {1.2846, -0.07071, 0.2466}; //{1.2846, 0.000, 0.2466}を中心としたひし形のスタート地点
// static float start_hand[3] = {1.2696, -0.07071, 0.2466}; //{1.2696, 0.000, 0.2466}を中心としたひし形のスタート地点

enum SeqMode
{
  INIT_MODE1,
  INIT_MODE2,
  CURRENT_CTRL
}; /// 制御動作モード定義
/// コンパイル中に追加した項目
static const float Td = 4.0e-6;                           /// [s]	デッドタイム
float range[] = {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0}; /// AD変換レンジ 5.0でMAX 5V

/************************************************************************
  PE-View WAVE 監視用変数
  共有のプログラムソースを使用する上でルールを設ける
  PE-View WAVE 監視用変数は　WAVE_oooo とする。
************************************************************************/

// フラグ
volatile int WAVE_INIT_COUNT = 0;
volatile float WAVE_FIL_Y = 0;

volatile int flag_cont_start = 0;  //!< 制御開始フラグ
volatile float flag_dead = 1;      //!< デッドタイム補償フラグ
volatile int flag_dyn_payload = 1; // 動力学計算ペイロード切り替えフラグ(0:無負荷、1:7.2kg負荷、2:4kg負荷)
volatile int flag_CalcHandCmd = 0; // 手先軌跡選択フラグ(0:circle, 1:rectangle, 2:diamond)
volatile int flag_debug = 0;
volatile int flag_pv = 0;         // 位置/速度制御切り替えフラグ
volatile int flag_delay = 0;      // FF用　1/z^2 遅延フラグ
volatile int flag_Vdc_setted = 0; // 位置/速度制御切り替えフラグ
volatile int flag_FBgain = 1;     // パナ指定FBゲイン倍率
volatile int flag_PPgain = 2;     // 位置Pゲイン
volatile int flag_FF = 0;         // FF制御フラグ
volatile int flag_SOB = 0;        // 状態オブザーバフラグ
volatile int counter_2 = 0;       // 指令値Z^=2用カウンタ
volatile int WAVE_LoopCount = 1;
volatile int flag_FF_triple = 0;
volatile int flag_cmd_end = 0;

volatile float WAVE_Timer0 = 0.0; // タイマー記録変数
volatile float WAVE_Timer1 = 0.0; // タイマー記録変数
volatile float WAVE_Timer2 = 0.0; // タイマー記録変数

volatile float WAVE_TimeGetEnc = 0.0;
volatile float WAVE_TimeSetWm = 0.0;
volatile float WAVE_TimeConv2dq = 0.0;
volatile float WAVE_TimeResRatch = 0.0;
volatile float WAVE_TimeJl = 0.0;
volatile float WAVE_TimeGain = 0.0;
volatile float WAVE_TimeWrInit = 0.0;
volatile float WAVE_TimeWr = 0.0;
volatile float WAVE_TimeTauLdyn = 0.0;
volatile float WAVE_TimeTm = 0.0;
volatile float WAVE_TimeGrav = 0.0;
volatile float WAVE_TimeSOB = 0.0;
volatile float WAVE_TimeP_PI = 0.0;
volatile float WAVE_TimeACC = 0.0;
volatile float WAVE_TimeConv2uvw = 0.0;
volatile float WAVE_TimeInsert = 0.0;
volatile float WAVE_TimeCalcCmd = 0.0;
volatile float WAVE_TimeCalcInvCmd = 0.0;

volatile float WAVE_Joint1 = 0.0;
volatile float WAVE_Joint2 = 0.0;
volatile float WAVE_Joint3 = 0.0;
volatile float WAVE_HandX = 0.0;
volatile float WAVE_HandY = 0.0;
volatile float WAVE_HandZ = 0.0;
volatile float WAVE_fx = 0.0;
volatile float WAVE_fy = 0.0;
volatile float WAVE_fz = 0.0;
volatile float WAVE_vx = 0.0;
volatile float WAVE_vy = 0.0;
volatile float WAVE_vz = 0.0;

volatile int flag_reposition = 0;
volatile int flag_first_go = 0;
volatile int flag_first_back = 1;
volatile int flag_hard = 0;
volatile int flag_CircleStart1 = 0;
volatile int flag_CircleStart2 = 0;
volatile int flag_CircleStart3 = 0;
volatile int flag_end1 = 0;
volatile int flag_end2 = 0;
volatile int flag_end3 = 0;
volatile int flag_on = 0;
volatile float start_go1 = 0.0;
volatile float start_go2 = 0.0;
volatile float start_go3 = 0.0;
volatile float start_back1 = 0.0;
volatile float start_back2 = 0.0;
volatile float start_back3 = 0.0;

// 可変指令値
float Ref_Iq_ref_direct = 0.0; // [A]		q軸 電流指令
float Ref_wM_direct = 0.0;     // [rad/s]	速度指令
float Iq_off = 0.0;
int Flag_ARCS_start = 0; // ARCSへの制御フラグ信号
int Flag_ARCS_clear = 0; // ARCSへの制御フラグ信号

//
volatile float ref_wm_direct = 0.0;         // 全慣性測定用速度指令値
volatile int debug_theta = 0;               // デバッグ用変数。axis1.theta_rl_fullをこれで置き換えて、プログラムの挙動を見る
volatile float load_angle_limit_deg1 = 0.0; // 1軸 負荷側角度リミット
volatile float load_angle_limit_deg2 = 0.0; // 2軸 負荷側角度リミット
volatile float load_angle_limit_deg3 = 0.0; // 3軸 負荷側角度リミット
volatile float load_angle_limit_deg5 = 0.0; // 5軸 負荷側角度リミット
volatile float load_angle_limit_rad1 = 0.0; // 1軸 負荷側角度リミット
volatile float load_angle_limit_rad2 = 0.0; // 2軸 負荷側角度リミット
volatile float load_angle_limit_rad3 = 0.0; // 3軸 負荷側角度リミット
volatile float load_angle_limit_rad5 = 0.0; // 5軸 負荷側角度リミット
volatile int left_rotation_flag = 1;        // 1軸 ロボットから見て左方向に回転させるフラグ
volatile int right_rotation_flag = 0;       // 1軸 ロボットから見て右方向に回転させるフラグ
volatile int down_rotation_flag2 = 1;       // 2軸 ロボットから見て下方向に回転させるフラグ
volatile int up_rotation_flag2 = 0;         // 2軸 ロボットから見て上方向に回転させるフラグ
volatile int down_rotation_flag3 = 1;       // 3軸 ロボットから見て下方向に回転させるフラグ
volatile int up_rotation_flag3 = 0;         // 3軸 ロボットから見て上方向に回転させるフラグ
volatile int down_rotation_flag5 = 1;       // 5軸 ロボットから見て下方向に回転させるフラグ
volatile int up_rotation_flag5 = 0;         // 5軸 ロボットから見て上方向に回転させるフラグ

// 変調率
volatile float WAVE_MRU1;
volatile float WAVE_MRV1;
volatile float WAVE_MRW1;
volatile float WAVE_MRU2;
volatile float WAVE_MRV2;
volatile float WAVE_MRW2;
volatile float WAVE_MRU3;
volatile float WAVE_MRV3;
volatile float WAVE_MRW3;

// 回生ブレーキ確認
volatile float WAVE_MRBR1;
volatile float WAVE_MRBR2;
volatile float WAVE_MRBR3;

/// ゲイン
// 1軸目
volatile float WAVE_Kpp1 = 0.0;
volatile float WAVE_Kff1 = 0.0;
volatile float WAVE_Kfb1 = 0.0;
volatile float WAVE_Kvp1 = 0.0;
volatile float WAVE_Kvi1 = 0.0;
volatile float WAVE_fwm1 = 0.0;
volatile float WAVE_fqs1 = 0.0;
volatile float WAVE_fwl1 = 0.0;
// 2軸目
volatile float WAVE_Kpp2 = 0.0;
volatile float WAVE_Kff2 = 0.0;
volatile float WAVE_Kfb2 = 0.0;
volatile float WAVE_Kvp2 = 0.0;
volatile float WAVE_Kvi2 = 0.0;
volatile float WAVE_fwm2 = 0.0;
volatile float WAVE_fqs2 = 0.0;
volatile float WAVE_fwl2 = 0.0;
// 3軸目
volatile float WAVE_Kpp3 = 0.0;
volatile float WAVE_Kff3 = 0.0;
volatile float WAVE_Kfb3 = 0.0;
volatile float WAVE_Kvp3 = 0.0;
volatile float WAVE_Kvi3 = 0.0;
volatile float WAVE_fwm3 = 0.0;
volatile float WAVE_fqs3 = 0.0;
volatile float WAVE_fwl3 = 0.0;

// 動力学外乱トルク
volatile float WAVE_tauLdyn1; // [Nm] 動力学外乱トルク
volatile float WAVE_tauLdyn2; // [Nm] 動力学外乱トルク
volatile float WAVE_tauLdyn3; // [Nm] 動力学外乱トルク
// 動力学によるJl計算値
volatile float WAVE_Jl_calc1; // [kgm^2] 動力学によるJl計算値
volatile float WAVE_Jl_calc2; // [kgm^2] 動力学によるJl計算値
volatile float WAVE_Jl_calc3; // [kgm^2] 動力学によるJl計算値

// 　負荷側情報計算関数　計算結果
volatile float WAVE_al_calc1 = 0.0;
volatile float WAVE_wl_calc1 = 0.0;
volatile float WAVE_ql_calc1 = 0.0;
volatile float WAVE_wm_calc1 = 0.0;
volatile float WAVE_al_calc2 = 0.0;
volatile float WAVE_wl_calc2 = 0.0;
volatile float WAVE_ql_calc2 = 0.0;
volatile float WAVE_wm_calc2 = 0.0;
volatile float WAVE_al_calc3 = 0.0;
volatile float WAVE_wl_calc3 = 0.0;
volatile float WAVE_ql_calc3 = 0.0;
volatile float WAVE_wm_calc3 = 0.0;

volatile float WAVE_al_calc_DPD1 = 0.0;
volatile float WAVE_wl_calc_DPD1 = 0.0;
volatile float WAVE_ql_calc_DPD1 = 0.0;
volatile float WAVE_wm_calc_DPD1 = 0.0;
volatile float WAVE_al_calc_DPD2 = 0.0;
volatile float WAVE_wl_calc_DPD2 = 0.0;
volatile float WAVE_ql_calc_DPD2 = 0.0;
volatile float WAVE_wm_calc_DPD2 = 0.0;
volatile float WAVE_al_calc_DPD3 = 0.0;
volatile float WAVE_wl_calc_DPD3 = 0.0;
volatile float WAVE_ql_calc_DPD3 = 0.0;
volatile float WAVE_wm_calc_DPD3 = 0.0;

volatile float WAVE_est_wm1 = 0.0;
volatile float WAVE_est_qs1 = 0.0;
volatile float WAVE_est_wl1 = 0.0;
volatile float WAVE_est_wm2 = 0.0;
volatile float WAVE_est_qs2 = 0.0;
volatile float WAVE_est_wl2 = 0.0;
volatile float WAVE_est_wm3 = 0.0;
volatile float WAVE_est_qs3 = 0.0;
volatile float WAVE_est_wl3 = 0.0;

volatile float WAVE_est_conv_wm1 = 0.0;
volatile float WAVE_est_conv_qs1 = 0.0;
volatile float WAVE_est_conv_wl1 = 0.0;
volatile float WAVE_est_conv_wm2 = 0.0;
volatile float WAVE_est_conv_qs2 = 0.0;
volatile float WAVE_est_conv_wl2 = 0.0;
volatile float WAVE_est_conv_wm3 = 0.0;
volatile float WAVE_est_conv_qs3 = 0.0;
volatile float WAVE_est_conv_wl3 = 0.0;

volatile float WAVE_est_prop_wm1 = 0.0;
volatile float WAVE_est_prop_qs1 = 0.0;
volatile float WAVE_est_prop_wl1 = 0.0;
volatile float WAVE_est_prop_wm2 = 0.0;
volatile float WAVE_est_prop_qs2 = 0.0;
volatile float WAVE_est_prop_wl2 = 0.0;
volatile float WAVE_est_prop_wm3 = 0.0;
volatile float WAVE_est_prop_qs3 = 0.0;
volatile float WAVE_est_prop_wl3 = 0.0;

volatile float WAVE_est_ISOB_wm1 = 0.0;
volatile float WAVE_est_ISOB_qs1 = 0.0;
volatile float WAVE_est_ISOB_wl1 = 0.0;
volatile float WAVE_est_ISOB_wm2 = 0.0;
volatile float WAVE_est_ISOB_qs2 = 0.0;
volatile float WAVE_est_ISOB_wl2 = 0.0;
volatile float WAVE_est_ISOB_wm3 = 0.0;
volatile float WAVE_est_ISOB_qs3 = 0.0;
volatile float WAVE_est_ISOB_wl3 = 0.0;

/*****************************
 応答側の取得データ
*****************************/
// uvw三相電流
volatile float WAVE_IresU1 = 0.0;
volatile float WAVE_IresU2 = 0.0;
volatile float WAVE_IresU3 = 0.0;
volatile float WAVE_IresV1 = 0.0;
volatile float WAVE_IresV2 = 0.0;
volatile float WAVE_IresV3 = 0.0;
volatile float WAVE_IresW1 = 0.0;
volatile float WAVE_IresW2 = 0.0;
volatile float WAVE_IresW3 = 0.0;

// dq直流二相電流
volatile float WAVE_IresD1;
volatile float WAVE_IresD2;
volatile float WAVE_IresD3;
volatile float WAVE_IresQ1;
volatile float WAVE_IresQ2;
volatile float WAVE_IresQ3;

// 直流リンク電圧
volatile float WAVE_Vdc1;
volatile float WAVE_Vdc2;
volatile float WAVE_Vdc3;

// 直流リンク電流
volatile float WAVE_Idc1;
volatile float WAVE_Idc2;
volatile float WAVE_Idc3;

// 位置情報
volatile int WAVE_ENC_temp1;
volatile int WAVE_ENC_temp2;
volatile int WAVE_ENC_temp3;
volatile int WAVE_ENC1;
volatile int WAVE_ENC2;
volatile int WAVE_ENC3;
volatile float WAVE_theta_rm1;      //!< 機械角
volatile float WAVE_theta_rm2;      //!< 機械角
volatile float WAVE_theta_rm3;      //!< 機械角
volatile float WAVE_theta_rm_ref1;  //!< 総機械角指令値
volatile float WAVE_theta_rm_ref2;  //!< 総機械角指令値
volatile float WAVE_theta_rm_ref3;  //!< 総機械角指令値
volatile float WAVE_theta_rm_full1; //!< 総機械角
volatile float WAVE_theta_rm_full2; //!< 総機械角
volatile float WAVE_theta_rm_full3; //!< 総機械角
volatile float WAVE_theta_re1;      //!< 電気角
volatile float WAVE_theta_re2;      //!< 電気角
volatile float WAVE_theta_re3;      //!< 電気角

volatile float WAVE_TRG_WM1;
volatile float WAVE_TRG_WM2;
volatile float WAVE_TRG_WM3;
volatile float WAVE_wm1;
volatile float WAVE_wm2;
volatile float WAVE_wm3;
volatile float WAVE_wm_ref_org;
volatile float WAVE_wm_ref1;
volatile float WAVE_wm_ref2;
volatile float WAVE_wm_ref3;
volatile float WAVE_wm_cmd1;
volatile float WAVE_wm_cmd2;
volatile float WAVE_wm_cmd3;
volatile float WAVE_wm_CCC1;
volatile float WAVE_wm_CCC2;
volatile float WAVE_wm_CCC3;
volatile float WAVE_qm1;
volatile float WAVE_qm2;
volatile float WAVE_qm3;
volatile float WAVE_qm_ref1;
volatile float WAVE_qm_ref2;
volatile float WAVE_qm_ref3;
volatile float WAVE_ql1;
volatile float WAVE_ql2;
volatile float WAVE_ql3;
volatile float WAVE_Iq1;
volatile float WAVE_Iq2;
volatile float WAVE_Iq3;
volatile float WAVE_Isfb1;
volatile float WAVE_Isfb2;
volatile float WAVE_Isfb3;

volatile float WAVE_jark1;
volatile float WAVE_jark2;
volatile float WAVE_jark3;
volatile float WAVE_am_TriAccCmd1;
volatile float WAVE_am_TriAccCmd2;
volatile float WAVE_am_TriAccCmd3;
volatile float WAVE_wm_TriAccCmd1;
volatile float WAVE_wm_TriAccCmd2;
volatile float WAVE_wm_TriAccCmd3;
volatile float WAVE_qm_TriAccCmd1;
volatile float WAVE_qm_TriAccCmd2;
volatile float WAVE_qm_TriAccCmd3;

// 外部センサ取得用変数
volatile float WAVE_ACC_LW8079 = 0.0;      // 加速度センサ
volatile float WAVE_ACC_LW8174 = 0.0;      // 加速度センサ
volatile float WAVE_ACC_LW8174_axis = 0.0; // 加速度センサrad/s^2換算値
volatile float WAVE_Fz = 0.0;              // 力センサ(z軸方向)
volatile float WAVE_WSX = 0.0;             // レーザー変位計(x軸方向)
volatile float WAVE_WSY = 0.0;             // レーザー変位計(y軸方向)
volatile float WAVE_WSZ = 0.0;             // レーザー変位計(z軸方向)

/*****************************
 指令側の取得データ
*****************************/
// uvw三相電圧　リミット前
volatile float WAVE_VrefU1;
volatile float WAVE_VrefV1;
volatile float WAVE_VrefW1;
volatile float WAVE_VrefU2;
volatile float WAVE_VrefV2;
volatile float WAVE_VrefW2;
volatile float WAVE_VrefU3;
volatile float WAVE_VrefV3;
volatile float WAVE_VrefW3;
// uvw三相電圧　規格化 リミット後
volatile float WAVE_vu_ref_stand1;
volatile float WAVE_vv_ref_stand1;
volatile float WAVE_vw_ref_stand1;
volatile float WAVE_vu_ref_stand2;
volatile float WAVE_vv_ref_stand2;
volatile float WAVE_vw_ref_stand2;
volatile float WAVE_vu_ref_stand3;
volatile float WAVE_vv_ref_stand3;
volatile float WAVE_vw_ref_stand3;
// dq直流二相電流
volatile float WAVE_IrefD1;
volatile float WAVE_IrefD2;
volatile float WAVE_IrefD3;
volatile float WAVE_IrefQ1;
volatile float WAVE_IrefQ2;
volatile float WAVE_IrefQ3;
// dq直流二相電圧(非干渉化制御前)
volatile float WAVE_VrefD_dcpl1;
volatile float WAVE_VrefQ_dcpl1;
volatile float WAVE_VrefD_dcpl2;
volatile float WAVE_VrefQ_dcpl2;
volatile float WAVE_VrefD_dcpl3;
volatile float WAVE_VrefQ_dcpl3;
// dq直流二相電圧(非干渉化制御後)
volatile float WAVE_VrefD1;
volatile float WAVE_VrefQ1;
volatile float WAVE_VrefD2;
volatile float WAVE_VrefQ2;
volatile float WAVE_VrefD3;
volatile float WAVE_VrefQ3;
// dq直流二相電圧 リミット偏差FBのリミット前後の偏差分
volatile float WAVE_vd_lim_dif1;
volatile float WAVE_vq_lim_dif1;
volatile float WAVE_vd_lim_dif2;
volatile float WAVE_vq_lim_dif2;
volatile float WAVE_vd_lim_dif3;
volatile float WAVE_vq_lim_dif3;

volatile float WAVE_U_modulation = 0.0;
volatile float WAVE_V_modulation = 0.0;
volatile float WAVE_W_modulation = 0.0;

volatile float WAVE_omega_rm1;
volatile float WAVE_omega_rm2;
volatile float WAVE_omega_rm3;

volatile float WAVE_omega_rm1_ref;
volatile float WAVE_omega_rm2_ref;
volatile float WAVE_omega_rm3_ref;

volatile float WAVE_Tq1;
volatile float WAVE_Tq2;
volatile float WAVE_Tq3;

volatile float WAVE_Icmp1;
volatile float WAVE_Icmp2;
volatile float WAVE_Icmp3;

volatile float ref_Iq_direct1 = 0.0;
volatile float ref_Iq_direct2 = 0.0;
volatile float ref_Iq_direct3 = 0.0;

volatile float ref_Iq_freq_direct1;
volatile float ref_Iq_freq_direct2;
volatile float ref_Iq_freq_direct3;

volatile float WAVE_Iff_1;
volatile float WAVE_Iff_2;
volatile float WAVE_Iff_3;

volatile float WAVE_tauL_dyn_2nd;

volatile float WAVE_VWX;
volatile float WAVE_VWY;
volatile float WAVE_VWZ;

volatile float WAVE_AccCmd1 = 0;
volatile float WAVE_VelCmd1 = 0;
volatile float WAVE_AccCmd2 = 0;
volatile float WAVE_VelCmd2 = 0;
volatile float WAVE_AccCmd3 = 0;
volatile float WAVE_VelCmd3 = 0;

#pragma SET_DATA_SECTION(".DATA_ON_HIGHER_SPEED")

/*********************************
  オフセット関数テスト
*********************************/
// デバッグ用(エンコーダ取得エラー格納用)
volatile INT32 WAVE_Enc_error = 0;
volatile float WAVE_ofst_Iu = 0.0;
volatile float WAVE_ofst_Iv = 0.0;
volatile float WAVE_ofst_Iw = 0.0;
volatile float WAVE_Vdc_ofst = 0.0;
/// 一時的変数,デバッグ用
volatile float debug[4] = {-1};
volatile float debug2[4] = {-1};
volatile float debug3[4] = {-1};
volatile float ad1;
volatile float ad2;
volatile float ad3;
//
// volatile float WAVE_IresU2;
// volatile float WAVE_IresV2;
// volatile float WAVE_IresW2;

volatile float ModRatioU;
volatile float ModRatioV;
volatile float ModRatioW;

/*! @struct Robot
 *  @brief ロボット構造体, パラメータや指令値, 応答値すべてを格納
 *  巨大なので引数にする際は必ず参照渡し(ポインタ渡し)すること。
 **/
typedef volatile struct Robot
{
  /// 定数
  unsigned int BDN;    //!< ボード番号
  unsigned int ENC_CH; //!< エンコーダチャンネル
  float VrefD_Lim;     //!< [V]		d軸電圧指令制限値
  float VrefQ_Lim;     //!< [V]		q軸電圧指令制限値
  float IrefD_Lim;     //!< [A]		d軸電流指令制限値
  float IrefQ_Lim;     //!< [A]		q軸電流指令制限値
  unsigned int p;      //!< 			モータ極対数
  // モータパラメータ
  float Lq;    //!< [mH] q軸インダクタンス
  float Ld;    //!< [mH]	q軸インダクタンス
  float Rq;    //!< [Ω]	q軸抵抗
  float Rd;    //!< [Ω]	d軸抵抗
  float Phifa; //!<		磁束鎖交数
               // ロボットパラメータ
  float Jmn;   // [kgm^2] 駆動側慣性モーメント
  float Jln;   // [kgm^2] 負荷側慣性モーメント
  float Dmn;   // [Nm/rad/s] 駆動側粘性摩擦係数
  float Dln;   // [Nm/rad/s] 負荷側粘性摩擦係数
  float Ktn;   // [Nm/A] トルク係数
  float Ksn;   // [Nm/rad] ばね定数
  float Rgn;   // [-] ギア比

  // 電流制御ゲイン
  float KpiD; //!< d軸電流Pゲイン
  float KiiD; //!< d軸電流Iゲイン
  float KpiQ; //!< q軸電流Pゲイン
  float KiiQ; //!< q軸電流Iゲイン

  float Kpp; // 位置Pゲイン
  float Kff;
  float Kfb;
  float Kvi; //!< 速度制御Iゲイン
  float Kvp; //!< 速度制御Pゲイン
  float fwm; //!< モータ速度状態FBゲイン
  float fqs; //!< ねじれ角度状態FBゲイン
  float fwl; //!< 負荷側速度状態FBゲイン

  // 電流制御用変数
  float Vdc;                 //!< [V] 		直流リンク電圧
  float Idc;                 //!< [A] 		直流リンク電流
  float IresU, IresV, IresW; //!< [A] 		UVW相 電流応答値
  float theta_rm;            //!< [rad]	位置応答値 (0～2πの値域制限あり)
  float theta_rm_ref;        //!< [rad]	位置指令値 (0～2πの値域制限なし)
  float theta_rm_full;       //!< [rad]	位置応答値 (0～2πの値域制限なし)
  float theta_rm_init;       //!< [rad]    位置応答値 (何回転したか総回転数取得)
  float theta_rl_full;       //!< [rad] 負荷側角度
  float theta_rl_init;       //!< [rad] 負荷側角度の初期角度
  float theta_re;            //!< [rad/s]	電気角位置応答値
  int enc_data_prev;         //!< [rad] 1つ前のエンコーダ情報
  int up_count_m;            //!< エンコーダ, 上位カウンタ
  float omega_rm;            //!< [rad/s]	速度応答値
  float omega_re;            //!< [rad/s]	電気角速度応答値
  float omega_rm_ref;        //!< [rad/s]	速度指令
  float IresA, IresB;        //!< [A]		αβ軸 電流応答
  float IresD, IresQ;        //!< [A]		dq軸 電流応答
  float IrefD, IrefQ;        //!< [A]		dq軸 電流指令
  float I_SOBinput;          //!< 各状態オブザーバの入力電流

  // 2軸目だけモデルで考えている、電流と負荷側の動作方向が逆なので電流制御の手前で正負を入れ替える
  float IrefD_inv_2nd, IrefQ_inv_2nd;        //!< [A] 2軸目の電流制御用
  float IdifD, IdifQ;                        //!< [A]		dq軸 電流差分
  float VrefD, VrefQ;                        //!< [V]		dq軸 電圧指令
  float VrefD_dcpl, VrefQ_dcpl;              //!< [V]		dq軸 電圧指令 (非干渉制御器出力後)
  float VrefA, VrefB;                        //!< [V]		αβ軸 電圧指令
  float VrefU, VrefV, VrefW;                 //!< [V] 		UVW相 電圧指令値
  float Vu_std, Vv_std, Vw_std;              //!< 		Vdcリンク電圧で規格化された値
  float Vlim_diffD, Vlim_diffQ;              //!<		電圧飽和対策のリミット偏差フィードバックの偏差
  float Vdc_ofst, ofst_Iu, ofst_Iv, ofst_Iw; //!< 電圧,電流センサーオフセット
  float MRBR;                                // ブレーキチョッパ用の変調率

  // 位置/速度制御用変数
  float qm_ref;    // [rad] 位置指令値(0～2πの値域制限なし)
  float qm_ref_z1; // FF制御用
  float qm_ref_z2;
  float qm_ref_z3;
  float wm_cmd;

  // 負荷側位置リミット
  float ql_max;
  float ql_min;
  float qm_max;
  float qm_min;

  float qm;     // [rad] 位置応答値(0～2πの値域制限なし)
  float ql;     // [rad] 負荷側角度
  float wm_ref; // [rad/s] 速度指令値
  float wm;     // [rad/s] 速度応答値
  float Iq;     // [A] Wr用にq軸電流指令値をラッチ
                // float est_wM, est_Qs, est_wL;//!< 状態オブザーバの推定値
  // float est_conv_wM, est_conv_Qs, est_conv_wL;//!< 従来法状態オブザーバの推定値
  // float est_prop_wM, est_prop_Qs, est_prop_wL;//!< 提案法状態オブザーバの推定値
  float est_conv_wm, est_conv_qs, est_conv_wl; //!< 従来法状態オブザーバの推定値
  float est_prop_wm, est_prop_qs, est_prop_wl; //!< 提案法状態オブザーバの推定値
  float est_ISOB_wm, est_ISOB_qs, est_ISOB_wl; //!< ISOB推定値
  float Isfb;                                  //!< [A] 状態オブザーバによる推定補償電流
  float obp;
  float obpz;
  float Icmd;
  float Icmp; //!<	[A] 重力補償電流
  float Tq;   //!< [N/m]重力補償トルク
  // FF制御
  float Iff;
  // 動力学計算結果
  float tauLdyn; // 動力学外乱トルク(慣性行列の非対角項および遠心・コリオリ、重力項)
  float tauLdyn_z1;
  float tauLdyn_z2;
  float Jl_calc; // 慣性行列の対角項
  float Jl_calc_z1;
  float Jl_calc_z2;
  // Wr計算結果
  float ql_calc;
  float wl_calc;
  float al_calc;
  float wm_calc;

  // Wr計算結果(DPD)
  float ql_calc_DPD;
  float wl_calc_DPD;
  float al_calc_DPD;
  float wm_calc_DPD;

  // 加速度センサrad/s^2換算値
  float al;
  // ランプ指令用変数
  float l_50;   // 830mm
  float l_80;   // 1270mm
  float y_ref;  // 150mm
  float wl_max; // 170deg/s
  float posi_trg_rad;
  float a_ramp;
  float a_ramp_back;
  float t_start;
  float t_ramp;
  float t_ramp_back;
  float t_const;
  float vel;
} Robot;

/// 動作軸数が3つなので構造体は3つ
Robot joint[3] = {0};

// *********************************
// FDTDオブザーバ用構造体
// *********************************
typedef struct Fdtd_Tsob_Coefficient
{
  // Jlに関する係数
  // A行列
  float a11cf, a12cf, a13cf;
  float a21cf, a22cf1, a22cf2;
  float a23cf1, a23cf2;
  float a31cf, a32cf, a33cf1, a33cf2;
  // B行列(IrefQ入力)
  float biq1cf;
  float biq2cf;
  float biq3cf;
  // B行列(tauLdyn入力)
  float btl1cf;
  float btl2cf;
  float btl3cf;
  // オブザーバゲイン
  float k1m1, k1z0;
  float k2m2, k2m1, k2z0;
  float k3n0, k3n1, k3n2, k3n3, k3d2, k3d3;
} Fdtd_Tsob_Coefficient;

Fdtd_Tsob_Coefficient ob_sub[3] = {0};

// *********************************
// FDTD Wr計算用構造体
// *********************************
// Jlに関する係数 2慣性系プラントのIqref入力
// typedef struct Fdtd_Wr_Coefficient{
//   float a11cf, a12cf         , a13cf         , a14cf;
//   float a21cf, a22cf1, a22cf2, a23cf1, a23cf2, a24cf;
//   float a31cf, a32cf         , a33cf1, a33cf2, a34cf;
//   float a41cf, a42cf         , a43cf         , a44cf;
//   float b1cf , b2cf          , b3cf          , b4cf ;
// }Fdtd_Wr_Coefficient;
// Jlに関する係数 2慣性系プラントのwmref入力
// typedef struct Fdtd_Wr_Coefficient{
//   float a11cf, a12cf         , a13cf         , a14cf, a15cf;
//   float a21cf, a22cf1 ,a22cf2, a23cf1 ,a23cf2, a24cf, a25cf;
//   float a31cf, a32cf         , a33cf1 ,a33cf2, a34cf, a35cf;
//   float a41cf, a42cf         , a43cf         , a44cf, a45cf;
//   float a51cf, a52cf         , a53cf         , a54cf, a55cf;
//   float b1cf , b2cf          , b3cf          , b4cf , b5cf;
// }Fdtd_Wr_Coefficient;
// Jlに関する係数 2慣性系プラントのqmref入力
typedef struct Fdtd_Wr_Coefficient
{
  // _x7及び_7xはwm_cmd入力でのみ用いる
  float a11cf, a12cf, a13cf, a14cf, a15cf, a16cf, a17cf;
  float a21cf, a22cf, a23cf, a24cf, a25cf, a26cf, a27cf;
  float a31cf, a32cf, a33cf1, a33cf2, a34cf1, a34cf2, a35cf, a36cf, a37cf;
  float a41cf, a42cf, a43cf, a44cf1, a44cf2, a45cf, a46cf, a47cf;
  float a51cf, a52cf, a53cf, a54cf1, a54cf2, a55cf, a56cf, a57cf;
  float a61cf, a62cf, a63cf, a64cf, a65cf, a66cf, a67cf;
  float a71cf, a72cf, a73cf, a74cf, a75cf, a76cf, a77cf;
  float b1cf, b2cf, b3cf, b4cf, b5cf, b6cf, b7cf;

  // Iq入力とwm入力の関数でエラーにならないようにqm入力では使わない変数を宣言しておく
  float a22cf1, a22cf2, a23cf1, a23cf2, a34cf, a44cf;
} Fdtd_Wr_Coefficient;

Fdtd_Wr_Coefficient Wr_sub[3] = {0};
Fdtd_Wr_Coefficient Wr_DPD[3] = {0};

// *********************************
// 動力学計算用構造体
// *********************************
typedef struct DynamicsValues
{

  // 計算用変数
  // 慣性行列
  float H11p1, H11p2, H11p3, H11p4, H11p5, H11p6, H11p7, H11p8, H11p9, H11p10, H11p11, H11p12, H11p13;
  float H12p1;
  float H22p1, H22p2, H22p3;
  float H23p1, H23p2, H23p3;
  float H33p1;

  float b122p1;
  float b112p1, b112p2, b112p3, b112p4, b112p5, b112p6, b112p7, b112p8;
  float b113p1, b113p2, b113p3, b113p4, b113p5, b113p6, b113p7, b113p8;
  float b211p1, b211p2, b211p3, b211p4, b211p5, b211p6, b211p7, b211p8;

  float b233p1, b233p2;

  float b223p1, b223p2;

  float b311p1, b311p2, b311p3, b311p4, b311p5, b311p6, b311p7, b311p8;

  float b322p1, b322p2;

  float G2p1, G2p2, G2p3;

  float G3p1, G3p2;
} DynamicsValues;

DynamicsValues dyn = {0};

// *********************************
// 三角加速度指令用構造体
// *********************************
typedef struct TriangularAccelerationCommandValues
{
  float a_time_full;
  float t1;
  float t2;
  float t3;
  float t4;
  float t5;
  float t6;
  float ql_const;
  float qm_const;
  float jark;
} TriangularAccelerationCommandValues;

TriangularAccelerationCommandValues tri[3] = {0};

// **************************************
// 位置・速度制御系可変ゲイン演算用構造体
// **************************************
typedef struct PVGainValues
{
  float Kvp_cfp1;
  float fwm_cf0;
  float fwm_cfp1;
  float fwm_cfn1;
  float fqs_cf0;
  float fqs_cfp1;
  float fqs_cfn1;
  float fqs_cfn2;
  float fwl_cf0;
  float fwl_cfp1;
  float fwl_cfn1;
  float fwl_cfn2;
  float zw;
  // 極配置法用の変数
  float complex pw1; // 指定極1
  float complex pw2; // 指定極2
  float complex pw3; // 指定極3
  float complex pw4; // 指定極4
  // 係数図法用の変数
  float r_cdm1;   // 係数比1
  float r_cdm2;   // 係数比2
  float r_cdm3;   // 係数比3
  float r_cdm4;   // 係数比4
  float tau_cdm;  // 速度制御の等価時定数
  float tau_pole; // 位置制御の等価時定数
} PVGainValues;

PVGainValues gsub[3] = {0};

// *********************************
// 三角加速度指令用構造体
// *********************************
typedef struct Fdtd_Tm_Coefficient
{
  float den_0;
  float den_1;
  float den_2;
  float num_0;
  float num_1;
  float num_2;
} Fdtd_Tm_Coefficient;

Fdtd_Tm_Coefficient Tm_sub[3] = {0};

#pragma SET_DATA_SECTION()

/*! @struct Controller
  @brief 制御器・安定化器関数構造体

  関数のポインタに関数の実態を代入しないと使えないことに注意<br/>
  ポインタを渡した関数内にstatic変数があった場合,
  関数を使いまわしてもstatic変数は一意(unique)なことに注意<br/>
  (要はstatic変数使うと致命的なバグが発生します.)*/
typedef volatile struct Controller
{
  // メンバ(インスタンス変数)
  // static 変数の置き換え
  float uZ1;
  float yZ1;
  // メソッド(関数)
  /// PIcontroller(float u, const float Kp, const float Ki, const float Ts, float *uZ1, float *yZ1)の関数ポインタ格納用変数
  float (*PIcontroller)(float u, const float Kp, const float Ki, const float Ts, volatile float *uZ1, volatile float *yZ1);
  /// PIcontroller_withAntiwindup(float u, float rl, const float Kp, const float Ki, const float Ts, float *uZ1, float *yZ1)の関数ポインタ格納用変数
  float (*PIcontroller_withAntiwindup)(float u, float rl, const float Kp, const float Ki, const float Ts, volatile float *uZ1, volatile float *yZ1);
  /// void DecouplingControl(Robot *robo)の関数ポインタ格納用
  float (*Pcontroller)(float u, const float Kp);
  void (*DecouplingControl)(Robot *robo);
} Controller;

/*! @struct Sensor
 * 	@brief センサー類の換算ゲイン,オフセット格納
 * 	Vadc対応(CH0 = iu, CH1 = iv, CH2 = iw, CH3 = Vdc, CH4 = Vvw, CH5 = Vvu, CH6=NC, CH7 = NC)
 * 	3相電流センサが無い場合
 */
typedef volatile struct Sensor
{
  float VtoVdc;      //!< [V/V] 直流リンク電圧換算ゲイン
  float VtoI;        //!< [A/V] UVW相電流換算ゲイン
  float VtoIdc;      //!< [A/V] 直流リンク電流換算ゲイン
  float offset[5];   //!< センサオフセット Iu, Iv, Iw, Vdc, Idc の並び
  float WSXf_ofst;   // レーザ変位計のオフセット
  float WSZf_ofst;   // レーザ変位計のオフセット
  float WSYf_ofst;   // レーザ変位計のオフセット
  float LW8174_ofst; // DC加速度センサのオフセット
  float LW8079_ofst; // DC加速度センサのオフセット
  int offset_count;
  float Iu_sum, Iv_sum, Iw_sum, Vdc_sum, Idc_sum, WSXf_sum, WSYf_sum, WSZf_sum, LW8174_sum, LW8079_sum; /// 合計値
} Sensor;

// 換算ゲイン初期化
Sensor sen[3] = {0};

/*! @struct LPF
 * 	@brief フィルター用定数の構造体
 */
typedef volatile struct LPF_param
{
  int Num;  // Filterの番号
  int flag; // 通過するのが初回かどうかの確認
  float Ts; // [s]		制御周期の格納
  float w;  // [rad/s]	遮断周波数
  float Q;  //			鋭さ(0.5のときに重根設定となる)
  float uZ1, uZ2, uZ3, yZ1, yZ2, yZ3;
} LPF_param;

LPF_param LPF_motor[3] = {0};
LPF_param LPF_cmd[3] = {0};
/**
 *  プロトタイプ宣言
 **/

/// 複数のエンコーダの位置を取得する関数
void GetMultiPositions(Robot robo[]);
/// P コントローラ
float Pcontroller(float u, const float Kp);
/// PI コントローラ
float PIcontroller(float u, const float Kp, const float Ki, const float Ts, volatile float *uZ1, volatile float *yZ1);
float VconPI5Axis(float u, const float Kp, const float Ki);
/// リミット偏差フィードバック付きPIコントローラ
float PIcontroller_withAntiwindup(float u, float rl, const float Kp, const float Ki, const float Ts, volatile float *uZ1, volatile float *yZ1);
/// 状態オブザーバ
void StateObserver(float Iref, float wM, volatile float *est_wM, volatile float *est_Qs, volatile float *est_wL, int BDN);
// tauLdyn入力型FDTD二慣性系状態オブザーバ
void FDTD_T_SOB(Robot *robo);
// FDTD二慣性系状態オブザーバ
void CalcFDTDTSOBInit(void);
void FDTDSOB(Robot *robo);
// FF制御器　補償電流計算Tm(z)
void FDTD_Tm(Robot *robo);
void FDTD_Tm_Init(void);
/// 電流と各センサの値取得
void GetVoltAndCurrent(Robot *robo, Sensor *sense);
/// センサオフセット計算
void CalcOffset(int BDN, Sensor *sense);
/// 非干渉制御
void DecouplingControl(Robot *robo);
/// リミッタ
float Limiter(float input, float limit);
/// リミット偏差フィードバック用 電圧指令リミット前後差を計算する関数
void LimDiffCalcDQ(Robot *robo);
// 動力学計算
void CalcTauLDyn(Robot axis[]);
void CalcJl(Robot axis[]);
void CalcGravIcmp(Robot axis[]);
void CalcDynamicsInit(int flag_dyn_payload);

// FDTDで離散化した負荷側情報計算関数
void CalcFDTDWr_QmrefInputType(Robot *robo);
void CalcFDTDWrInit_QmrefInputType(void);
void CalcFDTDWrUpdate_QmrefInputType_1st2nd(void);
void CalcFDTDWrUpdate_QmrefInputType_2nd(void);

// FDTDで離散化した負荷側情報計算関数(D-PD対応Wm_cmd入力型)
void CalcFDTDWr_WmcmdInputType(Robot *robo);
void CalcFDTDWrInit_WmcmdInputType(Robot *robo);
void CalcFDTDWrUpdate_WmcmdInputType_1st2nd(Robot *robo);
void CalcFDTDWrUpdate_WmcmdInputType_2nd(Robot *robo);

// ランプ位置指令生成関数
float CalcPref2axis(float t_lim, float ql_deg_tilt, int flag);
float CalcPrefRep2axis(float t_lim_up, float ql_deg_tilt_up, float t_lim_down, float ql_deg_tilt_down, float t_wait);
float CalcPrefRep3axis(float t_lim_up, float ql_deg_tilt_up, float t_lim_down, float ql_deg_tilt_down, float t_wait);
// 位置・速度制御系可変ゲイン演算関数
void CalcPVGain(void);
void CalcPVGainInitCDM(void); // 係数図法
// 回生ブレーキ関連
float CalcVdcMean(int BDN, float Vdc);
void BrakeController(Robot *robo);
/// 速度計算(位置差分)
float GetVelocity(float theta, volatile float *theta_Z1, const float Ts);
/// インバータ電圧指令値設定
void SetVoltReferences(Robot *robo);
/// 位置指令生成関数
// #pragma CODE_SECTION(func, “.CODE_ON_HIGHER_SPEED”)
void SetLPF(LPF_param Filter[], float Ts, float fs, float Q);
float GetFilterdSignal(LPF_param *Filter, float u, int flag_init);
int CalcHandCmdCenter(int flag_cmd, float goal[3], float t_wait, float speed, float start_hand[3], int flag_loop);
int CalcHandCmdCircle(float goal[3], float vel_hand[3], float t_wait, float speed, float start_hand[3], int flag_loop);
int CalcHandCmdRectangle(float goal[3], float t_wait, float speed, float start_hand[3], int flag_loop);
int CalcHandCmdDiamond(float goal[3], float t_wait, float speed, float start_hand[3], int flag_loop);
void LimitPosCmd(Robot *robo);
// void CalcInverseCmd(float goal[3], float joint[3], float motor[3], float wm[3], int flag_filter, int flag_reset, float dt);
void CalcInverseCmd_vel(float goal[3], float vel_hand[3], float ql_cmd[3], float wl_cmd[3], float ql_init[3], int flag_reset);
// 疑似微分なんやで
float backward_diff(float x, float xZ, float dt);
float GeneratorCircle1st(float t_wait, float start);
float GeneratorCircle2nd(float t_wait, float start);
float GeneratorCircle3rd(float t_wait, float start);
float ManyRampGenerator1stAxis(float a_ramp, float vel, float t_wait, float t_ramp, float t_const, float a_ramp_back, float t_ramp_back);
float ManyRampGenerator2ndAxis(float a_ramp, float vel, float t_wait, float t_ramp, float t_const, float a_ramp_back, float t_ramp_back);
float ManyRampGenerator3rdAxis(float a_ramp, float vel, float t_wait, float t_ramp, float t_const, float a_ramp_back, float t_ramp_back);
// 三角加速度指令生成関数
float TriangularAccelerationCommandGenerator(int BDN);
void TriangularAccelerationCommandGeneratorInit(float ql_const_deg, float q_time_full, float w_time_full, float Rg, int BDN);
/// SET,GET
void SetRampParams(float cmd1, float cmd2, float cmd3);
void SetBDN(Robot *robo, int Bnum);   //!< ロボット構造体のボード番号設定
void SetENC_CH(Robot *robo, int Ech); //!< エンコーダボードch番号
void SetGain(Robot robo[]);           ///!< 電流,速度,位置のゲインの挿入

float Integrator_acc_ref(float u, const float Ts);  // 加速度指令==>速度指令　1軸用
float Integrator_w_ref(float u, const float Ts);    // 速度指令==>位置指令　　1軸用
float Integrator_acc_ref2(float u, const float Ts); // 加速度指令==>速度指令　1軸用
float Integrator_w_ref2(float u, const float Ts);   // 速度指令==>位置指令　　1軸用
float Integrator_acc_ref3(float u, const float Ts); // 加速度指令==>速度指令　3軸用
float Integrator_w_ref3(float u, const float Ts);   // 速度指令==>位置指令  　3軸用

// 制御器初期化
Controller q_current[3] = {0}; /*!< q軸電流コントローラ */
Controller d_current[3] = {0}; /*!< d軸電流コントローラ */

Controller velocity[3] = {0}; //!< 速度コントローラー
Controller position[3] = {0}; //!< 位置コントローラー

Controller force[3] = {0}; //!< 力コントローラー(未実装)

/** @brief 割り込み関数 タイマーにより一定間隔(制御周期)ごとに呼ばれる。<br/>
 * 詳細は下記URL
 * https://www.aps-web.jp/academy/rtos/10/
 **/
interrupt void ControlFunction(void)
{
  C6657_timer2_stop();  /*!< 制御周期測定用タイマの停止 */
  C6657_timer2_clear(); /*!< 制御周期測定用タイマのクリア */
  C6657_timer2_start(); /*!< 制御周期測定用タイマの始動 */

  static unsigned long int LoopCount = 0; //!< 制御周期カウンタ
  static float t = 0.0;                   //!< [s]		時刻
  static float hand_cmd[3] = {0, 0, 0};
  static float hand_vel[3] = {0, 0, 0};
  static float joint_cmd[3] = {0, 0, 0};
  static float motor_cmd[3] = {0, 0, 0};
  static float motor_vel_cmd[3] = {0, 0, 0};
  static float motor_cmd_init[3] = {0, 0, 0};

  GetMultiPositions(joint); //!< 複数軸同時取得(特別な事情がない限りこっちを使う)

  debug3[0] = axis2.IresU;
  debug3[1] = axis2.IresV;
  debug3[2] = axis2.IresW;
  debug3[3] = axis2.Vdc;

  joint[0].omega_rm = GetVelocity(joint[0].theta_rm_full, &position[0].yZ1, Ts); /// 速度応答の取得
  joint[0].omega_re = joint[0].omega_rm * (float)joint[0].p;                     //!< 電気角速度へ変換
  joint[0].theta_rl_full = joint[0].theta_rl_init + (joint[0].theta_rm_full - joint[0].theta_rm_init) / joint[0].Rgn;

  joint[1].omega_rm = GetVelocity(joint[1].theta_rm_full, &position[1].yZ1, Ts); /// 速度応答の取得
  joint[1].omega_re = joint[1].omega_rm * (float)joint[1].p;
  joint[1].theta_rl_full = -joint[1].theta_rl_init + (joint[1].theta_rm_full - joint[1].theta_rm_init) / joint[1].Rgn;

  joint[2].omega_rm = GetVelocity(joint[2].theta_rm_full, &position[2].yZ1, Ts); /// 速度応答の取得
  joint[2].omega_re = joint[2].omega_rm * (float)joint[2].p;
  joint[2].theta_rl_full = joint[2].theta_rl_init + (joint[2].theta_rm_full - joint[2].theta_rm_init) / joint[2].Rgn;

  // 3相->2相変換 uvw->ab->dq
  uvw2ab(joint[0].IresU, joint[0].IresV, joint[0].IresW, &joint[0].IresA, &joint[0].IresB);   //!< αβ軸へ変換
  ab2dq(joint[0].IresA, joint[0].IresB, joint[0].theta_re, &joint[0].IresD, &joint[0].IresQ); //!< d-q軸へ変換
  uvw2ab(joint[1].IresU, joint[1].IresV, joint[1].IresW, &joint[1].IresA, &joint[1].IresB);   //!< αβ軸へ変換
  ab2dq(joint[1].IresA, joint[1].IresB, joint[1].theta_re, &joint[1].IresD, &joint[1].IresQ); //!< d-q軸へ変換
  uvw2ab(joint[2].IresU, joint[2].IresV, joint[2].IresW, &joint[2].IresA, &joint[2].IresB);   //!< αβ軸へ変換
  ab2dq(joint[2].IresA, joint[2].IresB, joint[2].theta_re, &joint[2].IresD, &joint[2].IresQ); //!< d-q軸へ変換

  ///	制御開始フラグが立った場合
  if (1 <= flag_cont_start)
  {

    // flag_cont_start == 1 : 電流制御確認
    if (1 == flag_cont_start)
    {
      /*****************************************************************************
        ロボット TA1400
        1軸目 : 電流指令　正　→　ロボットから見て　右
                エンコーダ情報は右向きが正
        2軸目 : 電流指令　正　→　ロボットから見て　上
                エンコーダ情報は上向きが正
        3軸目 : 電流指令　正　→　ロボットから見て　下

        ＊軸によって違うので注意！！！（ギアとかによる）
      ***************************************************************************** */

      // 位置応答と速度応答をラッチ
      axis1.qm = axis1.theta_rm_full - axis1.theta_rm_init;
      axis2.qm = axis2.theta_rm_full - axis2.theta_rm_init;
      axis2.qm = -1.0 * axis2.qm;
      axis3.qm = axis3.theta_rm_full - axis3.theta_rm_init;
      axis1.ql = axis1.theta_rl_full;
      axis2.ql = axis2.theta_rl_full;
      axis2.ql = -1.0 * axis2.ql;
      axis3.ql = axis3.theta_rl_full;
      axis1.wm = axis1.omega_rm;
      axis2.wm = axis2.omega_rm;
      axis2.wm = -1.0 * axis2.wm;
      axis3.wm = axis3.omega_rm;
      if (flag_on == 0)
      {
        axis1.qm_ref = 0.0;
        LimitPosCmd(&axis1);
        axis2.qm_ref = 0.0;
        LimitPosCmd(&axis2);
        axis3.qm_ref = 0.0;
        LimitPosCmd(&axis3);
      }
      else
      {
        axis1.qm_ref = axis1.qm;
        LimitPosCmd(&axis1);
        axis2.qm_ref = axis2.qm;
        LimitPosCmd(&axis2);
        axis3.qm_ref = axis3.qm;
        LimitPosCmd(&axis3);
      }

      CalcGravIcmp(joint); // 2,3軸の重力補償電流を計算　main関数の初期姿勢を要確認！！！！
      CalcJl(joint);       // JLの変動は使うので3軸分計算

      // // 可変ゲイン計算
      // CalcPVGain();
      if (flag_PPgain == 1)
        {
          axis1.Kpp = 20;
          axis1.Kff = 0.00;
          axis1.Kfb = 0.00;
          axis2.Kpp = 20;
          axis1.Kff = 0.00;
          axis2.Kfb = 0.00;
          axis3.Kpp = 20;
          axis1.Kff = 0.00;
          axis3.Kfb = 0.00;
        }
        else if (flag_PPgain == 2)
        {
          axis1.Kpp = 20;
          axis1.Kff = 1.400;
          axis1.Kfb = 0.400;
          axis2.Kpp = 20;
          axis1.Kff = 1.400;
          axis2.Kfb = 0.400;
          axis3.Kpp = 20;
          axis3.Kff = 1.400;
          axis3.Kfb = 0.400;
        }

      // 負荷側情報計算
      // CalcFDTDWr_QmrefInputType(&axis1);
      // CalcFDTDWr_QmrefInputType(&axis2);
      // CalcFDTDWr_QmrefInputType(&axis3);

      CalcFDTDWr_WmcmdInputType(&axis1);
      CalcFDTDWr_WmcmdInputType(&axis2);
      CalcFDTDWr_WmcmdInputType(&axis3);

      // 動力学トルクを計算
      CalcTauLDyn(joint);
      // FF制御　動力学補償電流
      FDTD_Tm(&axis1);
      FDTD_Tm(&axis2);
      FDTD_Tm(&axis3);

      // axis1.IrefQ = Pcontroller((axis1.wm_ref - axis1.wm),Kpv);
      // 動力学方程式より出るトルクの正負に合わせて補償電流を入れる
      // inspectorで要確認！！！！
      axis1.Icmd = 0.0;
      axis2.Icmd = 0.0;
      axis3.Icmd = 0.0;

      axis1.IrefQ = axis1.Icmd;
      axis2.IrefQ = axis2.Icmd + axis2.Icmp;
      axis3.IrefQ = axis3.Icmd + axis3.Icmp;
    }
    if (2 <= flag_cont_start)
    {
      flag_on = 1;
      if (flag_pv == 0)
      {
        flag_pv = 1;

        // ****************************************************
        // 時間測定 flag_pv = 0
        // ****************************************************
        // 制御周期測定用タイマのクリア
        C6657_timer0_stop();
        C6657_timer0_clear();
        C6657_timer0_start();

        // 位置応答と速度応答をラッチ
        axis1.qm = axis1.theta_rm_full - axis1.theta_rm_init;
        axis2.qm = axis2.theta_rm_full - axis2.theta_rm_init;
        axis2.qm = -1.0 * axis2.qm;
        axis3.qm = axis3.theta_rm_full - axis3.theta_rm_init;
        axis1.ql = axis1.theta_rl_full;
        axis2.ql = axis2.theta_rl_full;
        axis2.ql = -1.0 * axis2.ql;
        axis3.ql = axis3.theta_rl_full;
        axis1.wm = axis1.omega_rm;
        axis2.wm = axis2.omega_rm;
        axis2.wm = -1.0 * axis2.wm;
        axis3.wm = axis3.omega_rm;

        // ラッチしたqlの情報をもとにJlを計算
        CalcJl(joint); // JLの変動は使うので3軸分計算

        // 可変ゲイン計算
        CalcPVGain();
        if (flag_PPgain == 1)
        {
          axis1.Kpp = 20;
          axis1.Kff = 0.00;
          axis1.Kfb = 0.00;
          axis2.Kpp = 20;
          axis1.Kff = 0.00;
          axis2.Kfb = 0.00;
          axis3.Kpp = 20;
          axis1.Kff = 0.00;
          axis3.Kfb = 0.00;
        }
        else if (flag_PPgain == 2)
        {
          axis1.Kpp = 20;
          axis1.Kff = 1.400;
          axis1.Kfb = 0.400;
          axis2.Kpp = 20;
          axis1.Kff = 1.400;
          axis2.Kfb = 0.400;
          axis3.Kpp = 20;
          axis3.Kff = 1.400;
          axis3.Kfb = 0.400;
        }

        float start2 = (float)C6657_timer0_read() * 4.8e-9 * 1e6;

        if (flag_FF_triple == 1)
        {
          // 1,2軸動力学モデル更新
          // CalcFDTDWrUpdate_QmrefInputType_1st2nd();
          CalcFDTDWrUpdate_WmcmdInputType_1st2nd(&axis1);
          CalcFDTDWrUpdate_WmcmdInputType_1st2nd(&axis2);
          CalcFDTDWrUpdate_WmcmdInputType_1st2nd(&axis3);
          WAVE_TimeWrInit = (float)C6657_timer0_read() * 4.8e-9 * 1e6 - start2;
        }
        else
        {
          // 2軸のみモデル更新
          // CalcFDTDWrUpdate_QmrefInputType_2nd();
          CalcFDTDWrUpdate_WmcmdInputType_2nd(&axis1);
          CalcFDTDWrUpdate_WmcmdInputType_2nd(&axis2);
          CalcFDTDWrUpdate_WmcmdInputType_2nd(&axis3);
          WAVE_TimeWrInit = (float)C6657_timer0_read() * 4.8e-9 * 1e6 - start2;
        }

        // 制御周期の測定結果出力 ファンクションリファレンスp45より
        // 制御にかかった時間を測定している。
        WAVE_Timer0 = (float)C6657_timer0_read() * 4.8e-9 * 1e6;
      }
      else
      {
        flag_pv = 0;

        // 制御周期測定用タイマのクリア
        C6657_timer1_stop();
        C6657_timer1_clear();
        C6657_timer1_start();

        float start3 = (float)C6657_timer1_read() * 4.8e-9 * 1e6;
        // FF制御　FDTDで離散化した負荷側情報計算関数(qmref入力)
        if (flag_FF_triple == 1)
        {
          // CalcFDTDWr_QmrefInputType(&axis1); // 1軸目は動力学外乱入力なし
          // CalcFDTDWr_QmrefInputType(&axis2);
          // CalcFDTDWr_QmrefInputType(&axis3);

          CalcFDTDWr_WmcmdInputType(&axis1);
          CalcFDTDWr_WmcmdInputType(&axis2);
          CalcFDTDWr_WmcmdInputType(&axis3);
          WAVE_TimeWr = (float)C6657_timer1_read() * 4.8e-9 * 1e6 - start3;
        }
        else
        {
          // CalcFDTDWr_QmrefInputType(&axis2);
          // CalcFDTDWr_QmrefInputType(&axis3);

          CalcFDTDWr_WmcmdInputType(&axis2);
          CalcFDTDWr_WmcmdInputType(&axis3);
          WAVE_TimeWr = (float)C6657_timer1_read() * 4.8e-9 * 1e6 - start3;
        }

        start3 = (float)C6657_timer1_read() * 4.8e-9 * 1e6;
        // 動力学トルクを計算
        CalcTauLDyn(joint); // 1軸目の動力学外乱は使わないのでコメントアウト
        WAVE_TimeTauLdyn = (float)C6657_timer1_read() * 4.8e-9 * 1e6 - start3;

        start3 = (float)C6657_timer1_read() * 4.8e-9 * 1e6;
        // FF制御　動力学補償電流
        FDTD_Tm(&axis1);
        FDTD_Tm(&axis2);
        FDTD_Tm(&axis3);
        WAVE_TimeTm = (float)C6657_timer1_read() * 4.8e-9 * 1e6 - start3;

        start3 = (float)C6657_timer1_read() * 4.8e-9 * 1e6;
        CalcGravIcmp(joint);
        WAVE_TimeGrav = (float)C6657_timer1_read() * 4.8e-9 * 1e6 - start3;

        CalcGravIcmp(joint);

        if (flag_SOB == 0)
        {
          // 状態推定(従来法SOB)
          StateObserver(axis1.IrefQ, axis1.wm, &axis1.est_conv_wm, &axis1.est_conv_qs, &axis1.est_conv_wl, axis1.BDN);
          StateObserver(axis2.I_SOBinput, axis2.wm, &axis2.est_conv_wm, &axis2.est_conv_qs, &axis2.est_conv_wl, axis2.BDN);
          StateObserver(axis3.I_SOBinput, axis3.wm, &axis3.est_conv_wm, &axis3.est_conv_qs, &axis3.est_conv_wl, axis3.BDN);
          // 状態フィードバック電流の計算
          axis1.Isfb = axis1.est_conv_wm * axis1.fwm + axis1.est_conv_qs * axis1.fqs + axis1.est_conv_wl * axis1.fwl;
          axis2.Isfb = axis2.est_conv_wm * axis2.fwm + axis2.est_conv_qs * axis2.fqs + axis2.est_conv_wl * axis2.fwl;
          axis3.Isfb = axis3.est_conv_wm * axis3.fwm + axis3.est_conv_qs * axis3.fqs + axis3.est_conv_wl * axis3.fwl;
        }
        else if (flag_SOB == 1)
        {
          // 状態推定(従来法FDTDSOB)
          FDTDSOB(&axis1);
          FDTDSOB(&axis2);
          FDTDSOB(&axis3);

          // 状態フィードバック電流の計算
          axis1.Isfb = axis1.est_prop_wm * axis1.fwm + axis1.est_prop_qs * axis1.fqs + axis1.est_prop_wl * axis1.fwl;
          axis2.Isfb = axis2.est_prop_wm * axis2.fwm + axis2.est_prop_qs * axis2.fqs + axis2.est_prop_wl * axis2.fwl;
          axis3.Isfb = axis3.est_prop_wm * axis3.fwm + axis3.est_prop_qs * axis3.fqs + axis3.est_prop_wl * axis3.fwl;
        }
        else if (flag_SOB == 2)
        {
          // 状態推定(提案法tauLdyn入力型FDTDSOB)
          FDTD_T_SOB(&axis1);
          FDTD_T_SOB(&axis2);
          FDTD_T_SOB(&axis3);
          // 状態フィードバック電流の計算
          axis1.Isfb = axis1.est_prop_wm * axis1.fwm + axis1.est_prop_qs * axis1.fqs + axis1.est_prop_wl * axis1.fwl;
          axis2.Isfb = axis2.est_prop_wm * axis2.fwm + axis2.est_prop_qs * axis2.fqs + axis2.est_prop_wl * axis2.fwl;
          axis3.Isfb = axis3.est_prop_wm * axis3.fwm + axis3.est_prop_qs * axis3.fqs + axis3.est_prop_wl * axis3.fwl;
        }
        /* comment
           2軸目は正の電流指令でアームが上向きに回る。
           CalcTauLDyn、CalcGravIcmpで計算される動力学トルクはアームが上がるほうに正、下がるほうに負となる。 180deg 超えると逆
           Tmで計算された補償電流は制御系に加算される前提で計算される。
        */

        // 3軸目状態オブザーバ
        // StateObserver(axis3.IrefQ, axis3.wm, &axis3.est_conv_wm, &axis3.est_conv_qs, &axis3.est_conv_wl, axis3.BDN);
        // axis3.Isfb = axis3.est_conv_wm*axis3.fwm + axis3.est_conv_qs*axis3.fqs + axis3.est_conv_wl*axis3.fwl;

        if (2 == flag_cont_start)
        {
          static int flag_fin = 0;
          // 初期姿勢から実験姿勢へ遷移
          // ランプ指令用変数の設定
          if (flag_reposition == 0 && flag_first_go == 0)
          {
            flag_reposition = 1;
            flag_first_go = 1;
            flag_first_back = 0;
            flag_end1 = 0;
            flag_end2 = 0;
            flag_end3 = 0;
          }
          if (flag_reposition == 1)
          {
            hand_cmd[0] = start_hand[0];
            hand_cmd[1] = start_hand[1];
            hand_cmd[2] = start_hand[2];
            static float wait_cmd = 3.0;
            static float speed = 10.0; // [m/min] = 60 [m/s]
            static int flag_loop = 0;
            static int filter = 0;
            // filter = CalcHandCmdCenter(flag_CalcHandCmd, hand_cmd, wait, speed, start_hand, flag_loop);
            filter = CalcHandCmdCircle(hand_cmd, hand_vel, wait_cmd, speed, start_hand, flag_loop);
            // start_hand[0] = hand_cmd[0];
            // start_hand[1] = hand_cmd[1];
            // start_hand[2] = hand_cmd[2];
            static int flag = 0;
            static int reset = 1;
            // CalcInverseCmd(hand_cmd, joint_cmd, motor_cmd, motor_vel_cmd, filter, reset, Tp);
            CalcInverseCmd_vel(hand_cmd, hand_vel, motor_cmd, motor_vel_cmd, motor_cmd_init, 1);
            start_go1 = axis1.qm;
            start_go2 = axis2.qm;
            start_go3 = axis3.qm;
            flag_reposition = 0;
            // 指令値の設定値
            SetRampParams((motor_cmd[0]), (motor_cmd[1]), (motor_cmd[2]));
          }
          // ランプ指令用変数の設定

          // 初期姿勢
          //  1st-axis 0deg
          //  2nd-axis 0deg
          //  2rd-axis 0deg
          // 待機姿勢
          //  1st-axis -0.45260031 deg
          //  2nd-axis -29.07706521 deg
          //  3rd-axis 8.22494633 deg

          /*****************************************************************************
            ロボット TA1400
            1軸目 : 電流指令　正　→　ロボットから見て　右
                    エンコーダ情報は右向きが正
            2軸目 : 電流指令　正　→　ロボットから見て　上
                    エンコーダ情報は上向きが正
            3軸目 : 電流指令　正　→　ロボットから見て　下

            ＊軸によって違うので注意！！！（ギアとかによる）
          ***************************************************************************** */

          // 1軸目 位置指令
          // ランプ関数生成関数で位置指令を決定
          // 引数 a:傾き、t_wait:開始時間、t_ramp:ランプアップ時間、t_const:定常時間
          axis1.qm_ref_z2 = axis1.qm_ref_z1;
          axis1.qm_ref_z1 = axis1.qm_ref;
          axis1.wm_cmd = 1.0 * ManyRampGenerator1stAxis(axis1.a_ramp, axis1.vel, axis1.t_start, axis1.t_ramp, axis1.t_const, axis1.a_ramp_back, axis1.t_ramp_back);
          // axis1.qm_ref = 1.0 * ManyRampGenerator1stAxis(axis1.a_ramp, axis1.vel, axis1.t_start, axis1.t_ramp, axis1.t_const, axis1.a_ramp_back, axis1.t_ramp_back);
          axis1.qm_ref = axis1.wm_cmd * Tp + axis1.qm_ref_z1;
          LimitPosCmd(&axis1);
          // axis1.qm_ref = 0.0;
          // 1軸目 位置P制御
          // axis1.wm_ref = (axis1.qm_ref_z2 - axis1.qm) * axis1.Kpp;
          axis1.wm_ref = (axis1.qm_ref_z2 - axis1.qm) * axis1.Kpp + axis1.Kff * axis1.wm_cmd - axis1.Kfb * axis1.wm;
          // axis3.wm_ref = (axis3.qm_ref_z2 - axis3.qm) * axis3.Kpp + axis3.Kff * axis3.wm_cmd - axis3.Kfb * axis3.wm;

          if (flag_FF == 1)
          {
            // 1軸目 速度PI制御＋SFB＋FF
            axis1.IrefQ = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb + axis1.Iff;
            axis1.I_SOBinput = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb;

            if (flag_SOB == 1)
            {
              axis1.I_SOBinput = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb;
            }
            else if (flag_SOB == 2)
            {
              axis1.I_SOBinput = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb + axis1.Iff;
            }
          }
          else if (flag_FF == 0)
          {
            // 1軸目 速度PI制御＋SFB
            axis1.IrefQ = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb;
            axis1.I_SOBinput = axis1.IrefQ;
          }

          // 2軸目 位置指令
          // ランプ関数生成関数で位置指令を決定
          // 引数 a:傾き、t_wait:開始時間、t_ramp:ランプアップ時間、t_const:定常時間
          axis2.qm_ref_z2 = axis2.qm_ref_z1;
          axis2.qm_ref_z1 = axis2.qm_ref;
          axis2.wm_cmd = 1.0 * ManyRampGenerator2ndAxis(axis2.a_ramp, axis2.vel, axis2.t_start, axis2.t_ramp, axis2.t_const, axis2.a_ramp_back, axis2.t_ramp_back);
          // axis2.qm_ref = 1.0 * ManyRampGenerator2ndAxis(axis2.a_ramp, axis2.vel, axis2.t_start, axis2.t_ramp, axis2.t_const, axis2.a_ramp_back, axis2.t_ramp_back);
          axis2.qm_ref = axis2.wm_cmd * Tp + axis2.qm_ref_z1;
          LimitPosCmd(&axis2);
          // axis2.qm_ref = 0.0;
          // 2軸目 位置P制御
          // axis2.wm_ref = (axis2.qm_ref_z2 - axis2.qm) * axis2.Kpp;
          axis2.wm_ref = (axis2.qm_ref_z2 - axis2.qm) * axis2.Kpp + axis2.Kff * axis2.wm_cmd - axis2.Kfb * axis2.wm;
          
          if (flag_FF == 1)
          {
            // 2軸目 速度PI制御＋SFB＋FF
            axis2.IrefQ = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb + axis2.Iff;
            axis2.I_SOBinput = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb;

            if (flag_SOB == 1)
            {
              axis2.I_SOBinput = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb;
            }
            else if (flag_SOB == 2)
            {
              axis2.I_SOBinput = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb + axis2.Iff;
            }
          }
          else if (flag_FF == 0)
          {
            // 2軸目 速度PI制御＋SFB
            axis2.IrefQ = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb;
            axis2.I_SOBinput = axis2.IrefQ;
          }

          // 3軸目 位置指令
          // ランプ関数生成関数で位置指令を決定
          // 引数 a:傾き、t_wait:開始時間、t_ramp:ランプアップ時間、t_const:定常時間
          axis3.qm_ref_z2 = axis3.qm_ref_z1;
          axis3.qm_ref_z1 = axis3.qm_ref;
          axis3.wm_cmd = 1.0 * ManyRampGenerator3rdAxis(axis3.a_ramp, axis3.vel, axis3.t_start, axis3.t_ramp, axis3.t_const, axis3.a_ramp_back, axis3.t_ramp_back);
          // axis3.qm_ref = 1.0 * ManyRampGenerator3rdAxis(axis3.a_ramp, axis3.vel, axis3.t_start, axis3.t_ramp, axis3.t_const, axis3.a_ramp_back, axis3.t_ramp_back);
          axis3.qm_ref = axis3.wm_cmd * Tp + axis3.qm_ref_z1;
          LimitPosCmd(&axis3);
          // axis3.qm_ref = 0.0;
          // 3軸目 位置P制御
          // axis3.wm_ref = (axis3.qm_ref_z2 - axis3.qm) * axis3.Kpp;
          axis3.wm_ref = (axis3.qm_ref_z2 - axis3.qm) * axis3.Kpp + axis3.Kff * axis3.wm_cmd - axis3.Kfb * axis3.wm;

          // 3軸目 速度PI制御＋SFB
          if (flag_FF == 1)
          {
            // 3軸目 速度PI制御＋SFB＋FF
            axis3.IrefQ = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb + axis3.Iff;
            axis3.I_SOBinput = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb;

            if (flag_SOB == 1)
            {
              axis3.I_SOBinput = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb;
            }
            else if (flag_SOB == 2)
            {
              axis3.I_SOBinput = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb + axis3.Iff;
            }
          }
          else if (flag_FF == 0)
          {
            axis3.IrefQ = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb;
            axis3.I_SOBinput = axis3.IrefQ;
          }

          if (flag_end1 == 1 && flag_end2 == 1 && flag_end3 == 1)
          {
            if (flag_fin > 20)
            {
              flag_CircleStart1 = 1;
              flag_CircleStart2 = 1;
              flag_CircleStart3 = 1;
            }
            else
            {
              flag_fin++;
            }
          }
        }
        else if (3 == flag_cont_start)
        {
          //-------------------------- 実験 -----------------------------
          // y = -45°平面での円軌道

          // ランプ指令用変数の設定

          // 初期姿勢
          //  1st-axis -0.45260031 deg
          //  2nd-axis -29.07706521 deg
          //  3rd-axis 8.22494633 deg
          // 終端姿勢
          //  1st-axis 0.45483276 deg
          //  2nd-axis -29.072343 deg
          //  3rd-axis 8.22969042 deg

          /*****************************************************************************
            ロボット TA1400
            1軸目 : 電流指令　正　→　ロボットから見て　右
                    エンコーダ情報は右向きが正
            2軸目 : 電流指令　正　→　ロボットから見て　上
                    エンコーダ情報は上向きが正
            3軸目 : 電流指令　正　→　ロボットから見て　下

            ＊軸によって違うので注意！！！（ギアとかによる）
          ***************************************************************************** */
          static float time_wait = 3.0;
          static float speed_hand = 10.0; // [m/min] = 60 [m/s]
          static int flag_loop = 1;
          static int filter_reset = 0;
          static int inverse_reset = 1;

          float start_cmd = (float)C6657_timer0_read() * 4.8e-9 * 1e6;

          // int flag_filter_on = CalcHandCmdCenter(flag_CalcHandCmd ,hand_cmd, time_wait, speed_hand, start_hand, flag_loop);
          int flag_filter_on = CalcHandCmdCircle(hand_cmd, hand_vel, time_wait, speed_hand, start_hand, flag_loop);
          WAVE_TimeCalcCmd = (float)C6657_timer0_read() * 4.8e-9 * 1e6 - start_cmd;

          start_cmd = (float)C6657_timer0_read() * 4.8e-9 * 1e6;
          // CalcInverseCmd(hand_cmd, joint_cmd, motor_cmd, motor_vel_cmd, flag_filter_on, filter_reset, Tp);
          CalcInverseCmd_vel(hand_cmd, hand_vel, motor_cmd, motor_vel_cmd, motor_cmd_init, inverse_reset);
          inverse_reset = 0;
          WAVE_TimeCalcInvCmd = (float)C6657_timer0_read() * 4.8e-9 * 1e6 - start_cmd;

          // 1軸目 位置指令
          // ランプ関数生成関数で位置指令を決定
          // 引数 a:傾き、t_wait:開始時間、t_ramp:ランプアップ時間、t_const:定常時間
          axis1.wm_cmd = motor_vel_cmd[0];
          axis1.qm_ref_z2 = axis1.qm_ref_z1;
          axis1.qm_ref_z1 = axis1.qm_ref;

          // P制御用
          // axis1.qm_ref = motor_cmd[0];
          // LimitPosCmd(&axis1);
          // axis1.wm_ref = (axis1.qm_ref_z2 - axis1.qm) * axis1.Kpp;

          // D-PD制御用
          // axis1.qm_ref = motor_cmd[0];
          axis1.qm_ref = axis1.wm_cmd * Tp + axis1.qm_ref_z1;
          LimitPosCmd(&axis1);
          axis1.wm_ref = (axis1.qm_ref_z2 - axis1.qm) * axis1.Kpp + axis1.Kff * axis1.wm_cmd - axis1.Kfb * axis1.wm;

          if (flag_FF == 1)
          {
            // 1軸目 速度PI制御＋SFB＋FF
            axis1.IrefQ = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb + axis1.Iff;
            axis1.I_SOBinput = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb;

            if (flag_SOB == 1)
            {
              axis1.I_SOBinput = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb;
            }
            else if (flag_SOB == 2)
            {
              axis1.I_SOBinput = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb + axis1.Iff;
            }
          }
          else if (flag_FF == 0)
          {
            // 1軸目 速度PI制御＋SFB
            axis1.IrefQ = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb;
            axis1.I_SOBinput = axis1.IrefQ;
          }

          // 2軸目 位置指令
          // ランプ関数生成関数で位置指令を決定
          // 引数 a:傾き、t_wait:開始時間、t_ramp:ランプアップ時間、t_const:定常時間
          axis2.wm_cmd = motor_vel_cmd[1];
          axis2.qm_ref_z2 = axis2.qm_ref_z1;
          axis2.qm_ref_z1 = axis2.qm_ref;
          // P制御用
          // axis2.qm_ref = motor_cmd[1];
          // LimitPosCmd(&axis2);
          // axis2.wm_ref = (axis2.qm_ref_z2 - axis2.qm) * axis2.Kpp;
          // D-PD制御用
          // axis2.qm_ref = motor_cmd[1];
          axis2.qm_ref = axis2.wm_cmd * Tp + axis2.qm_ref_z1;
          LimitPosCmd(&axis2);
          axis2.wm_ref = (axis2.qm_ref_z2 - axis2.qm) * axis2.Kpp + axis2.Kff * axis2.wm_cmd - axis2.Kfb * axis2.wm;

          if (flag_FF == 1)
          {
            // 2軸目 速度PI制御＋SFB＋FF
            axis2.IrefQ = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb + axis2.Iff;
            axis2.I_SOBinput = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb;

            if (flag_SOB == 1)
            {
              axis2.I_SOBinput = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb;
            }
            else if (flag_SOB == 2)
            {
              axis2.I_SOBinput = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb + axis2.Iff;
            }
          }
          else if (flag_FF == 0)
          {
            // 2軸目 速度PI制御＋SFB
            axis2.IrefQ = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb;
            axis2.I_SOBinput = axis2.IrefQ;
          }

          // 3軸目 位置指令
          // ランプ関数生成関数で位置指令を決定
          // 引数 a:傾き、t_wait:開始時間、t_ramp:ランプアップ時間、t_const:定常時間
          axis3.wm_cmd = motor_vel_cmd[2];
          axis3.qm_ref_z2 = axis3.qm_ref_z1;
          axis3.qm_ref_z1 = axis3.qm_ref;
          // P制御用
          // axis3.qm_ref = motor_cmd[2];
          // LimitPosCmd(&axis3);
          // axis3.wm_ref = (axis3.qm_ref_z2 - axis3.qm) * axis3.Kpp;
          // D-PD制御用
          // axis3.qm_ref = motor_cmd[2];
          axis3.qm_ref = axis3.wm_cmd * Tp + axis3.qm_ref_z1;
          LimitPosCmd(&axis3);
          axis3.wm_ref = (axis3.qm_ref_z2 - axis3.qm) * axis3.Kpp + axis3.Kff * axis3.wm_cmd - axis3.Kfb * axis3.wm;

          // 3軸目 速度PI制御＋SFB
          if (flag_FF == 1)
          {
            // 3軸目 速度PI制御＋SFB＋FF
            axis3.IrefQ = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb + axis3.Iff;
            axis3.I_SOBinput = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb;

            if (flag_SOB == 1)
            {
              axis3.I_SOBinput = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb;
            }
            else if (flag_SOB == 2)
            {
              axis3.I_SOBinput = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb + axis3.Iff;
            }
          }
          else if (flag_FF == 0)
          {
            axis3.IrefQ = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb;
            axis3.I_SOBinput = axis3.IrefQ;
          }
        }
        else if (4 == flag_cont_start)
        {
          static int flag_fin = 0;
          //-------------------------- 実験 -----------------------------
          // 実験終端姿勢からの戻り
          // ランプ指令用変数の設定
          if (flag_reposition == 0 && flag_first_back == 0)
          {
            flag_reposition = 1;
            flag_first_back = 1;
            flag_first_go = 0;
            flag_end1 = 0;
            flag_end2 = 0;
            flag_end3 = 0;
          }
          if (flag_reposition == 1)
          {
            flag_cmd_end = 0;
            start_back1 = axis1.qm;
            start_back2 = axis2.qm;
            start_back3 = axis3.qm;
            flag_reposition = 0;
            // flag_reposition = 0;
            // 指令値の設定値
            SetRampParams((0.0 - start_back1), (0.0 - start_back2), (0.0 - start_back3));
          }

          /*****************************************************************************
            ロボット TA1400
            1軸目 : 電流指令　正　→　ロボットから見て　右
                    エンコーダ情報は右向きが正
            2軸目 : 電流指令　正　→　ロボットから見て　上
                    エンコーダ情報は上向きが正
            3軸目 : 電流指令　正　→　ロボットから見て　下

            ＊軸によって違うので注意！！！（ギアとかによる）
          ***************************************************************************** */
          start3 = (float)C6657_timer1_read() * 4.8e-9 * 1e6;
          // 1軸目 位置指令
          // ランプ関数生成関数で位置指令を決定
          // 引数 a:傾き、t_wait:開始時間、t_ramp:ランプアップ時間、t_const:定常時間
          axis1.qm_ref_z2 = axis1.qm_ref_z1;
          axis1.qm_ref_z1 = axis1.qm_ref;
          if (flag_end3 == 1)
          {            
            axis1.wm_cmd = 1.0 * ManyRampGenerator1stAxis(axis1.a_ramp, axis1.vel, axis1.t_start, axis1.t_ramp, axis1.t_const, axis1.a_ramp_back, axis1.t_ramp_back);
            // axis1.qm_ref = 1.0 * ManyRampGenerator1stAxis(axis1.a_ramp, axis1.vel, axis1.t_start, axis1.t_ramp, axis1.t_const, axis1.a_ramp_back, axis1.t_ramp_back) + start_back1;
            axis1.qm_ref = axis1.wm_cmd * Tp + axis1.qm_ref_z1;
          }
          else
          {
            axis1.wm_cmd = 0.0;
            // axis1.qm_ref = start_back1;
            axis1.qm_ref =  axis1.qm_ref_z1;
          }

          // 1軸目 速度P制御
          axis1.wm_ref = (axis1.qm_ref_z2 - axis1.qm) * axis1.Kpp;

          if (flag_FF == 1)
          {
            // 1軸目 速度PI制御＋SFB＋FF
            axis1.IrefQ = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb + axis1.Iff;
            axis1.I_SOBinput = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb;

            if (flag_SOB == 1)
            {
              axis1.I_SOBinput = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb;
            }
            else if (flag_SOB == 2)
            {
              axis1.I_SOBinput = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb + axis1.Iff;
            }
          }
          else if (flag_FF == 0)
          {
            // 1軸目 速度PI制御＋SFB
            axis1.IrefQ = velocity[0].PIcontroller(axis1.wm_ref - axis1.wm, axis1.Kvp, axis1.Kvi, Tp, &velocity[0].uZ1, &velocity[0].yZ1) - axis1.Isfb;
            axis1.I_SOBinput = axis1.IrefQ;
          }

          // 2軸目 位置指令
          // ランプ関数生成関数で位置指令を決定
          // 引数 a:傾き、t_wait:開始時間、t_ramp:ランプアップ時間、t_const:定常時間
          axis2.qm_ref_z2 = axis2.qm_ref_z1;
          axis2.qm_ref_z1 = axis2.qm_ref;
          if (flag_end3 == 1 && flag_end1 == 1)
          {
            axis2.wm_cmd = 1.0 * ManyRampGenerator2ndAxis(axis2.a_ramp, axis2.vel, axis2.t_start, axis2.t_ramp, axis2.t_const, axis2.a_ramp_back, axis2.t_ramp_back);
            axis2.qm_ref = axis2.wm_cmd * Tp + axis2.qm_ref_z1;
          }
          else
          {
            axis2.wm_cmd = 0.0;
            // axis2.qm_ref = start_back2;
            axis2.qm_ref = axis2.qm_ref_z1;
          }

          // 2軸目 速度P制御
          axis2.wm_ref = (axis2.qm_ref_z2 - axis2.qm) * axis2.Kpp;

          if (flag_FF == 1)
          {
            // 2軸目 速度PI制御＋SFB＋FF
            axis2.IrefQ = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb + axis2.Iff;
            axis2.I_SOBinput = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb;

            if (flag_SOB == 1)
            {
              axis2.I_SOBinput = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb;
            }
            else if (flag_SOB == 2)
            {
              axis2.I_SOBinput = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb + axis2.Iff;
            }
          }
          else if (flag_FF == 0)
          {
            // 2軸目 速度PI制御＋SFB
            axis2.IrefQ = velocity[1].PIcontroller(axis2.wm_ref - axis2.wm, axis2.Kvp, axis2.Kvi, Tp, &velocity[1].uZ1, &velocity[1].yZ1) - axis2.Isfb;
            axis2.I_SOBinput = axis2.IrefQ;
          }

          // 3軸目 位置指令
          // ランプ関数生成関数で位置指令を決定
          // 引数 a:傾き、t_wait:開始時間、t_ramp:ランプアップ時間、t_const:定常時間
          axis3.qm_ref_z2 = axis3.qm_ref_z1;
          axis3.qm_ref_z1 = axis3.qm_ref;
          axis3.wm_cmd = 1.0 * ManyRampGenerator3rdAxis(axis3.a_ramp, axis3.vel, axis3.t_start, axis3.t_ramp, axis3.t_const, axis3.a_ramp_back, axis3.t_ramp_back);
          // axis3.qm_ref = 1.0 * ManyRampGenerator3rdAxis(axis3.a_ramp, axis3.vel, axis3.t_start, axis3.t_ramp, axis3.t_const, axis3.a_ramp_back, axis3.t_ramp_back) + start_back3;
          axis3.qm_ref = axis3.wm_cmd * Tp + axis3.qm_ref_z1;

          // 3軸目 速度P制御
          axis3.wm_ref = (axis3.qm_ref_z2 - axis3.qm) * axis3.Kpp;

          // 3軸目 速度PI制御＋SFB
          if (flag_FF == 1)
          {
            // 3軸目 速度PI制御＋SFB＋FF
            axis3.IrefQ = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb + axis3.Iff;
            axis3.I_SOBinput = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb;

            if (flag_SOB == 1)
            {
              axis3.I_SOBinput = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb;
            }
            else if (flag_SOB == 2)
            {
              axis3.I_SOBinput = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb + axis3.Iff;
            }
          }
          else if (flag_FF == 0)
          {
            axis3.IrefQ = velocity[2].PIcontroller(axis3.wm_ref - axis3.wm, axis3.Kvp, axis3.Kvi, Tp, &velocity[2].uZ1, &velocity[2].yZ1) - axis3.Isfb;
            axis3.I_SOBinput = axis3.IrefQ;
          }
          if (flag_end1 == 1 && flag_end2 == 1 && flag_end3 == 1)
          {
            if (flag_fin > 20)
            {
              flag_cont_start = 1;
              flag_fin = 0;
            }
            else
            {
              flag_fin++;
            }
          }
          WAVE_TimeP_PI = (float)C6657_timer1_read() * 4.8e-9 * 1e6 - start3;
        }
        else
        {
          axis1.IrefQ = 0.0;
          axis2.IrefQ = axis2.Icmp;
          axis3.IrefQ = axis3.Icmp;
        }
        // 制御周期の測定結果出力 ファンクションリファレンスp45より
        // 制御にかかった時間を測定している。
        WAVE_Timer1 = (float)C6657_timer1_read() * 4.8e-9 * 1e6;
      }
    }

    /// 電流指令リミッタ
    axis1.IrefQ = Limiter(joint[0].IrefQ, joint[0].IrefQ_Lim);
    axis1.IrefD = Limiter(joint[0].IrefD, joint[0].IrefD_Lim);
    axis2.IrefQ = Limiter(joint[1].IrefQ, joint[1].IrefQ_Lim);
    axis2.IrefD = Limiter(joint[1].IrefD, joint[1].IrefD_Lim);
    axis3.IrefQ = Limiter(joint[2].IrefQ, joint[2].IrefQ_Lim);
    axis3.IrefD = Limiter(joint[2].IrefD, joint[2].IrefD_Lim);

    axis2.IrefQ_inv_2nd = -1.0 * axis2.IrefQ;
    axis2.IrefD_inv_2nd = -1.0 * axis2.IrefD;

    /// リミット偏差フィードバック用計算
    LimDiffCalcDQ(&joint[0]);
    LimDiffCalcDQ(&joint[1]);
    LimDiffCalcDQ(&joint[2]);

    /// 指令値と応答の差分
    joint[0].IdifQ = joint[0].IrefQ - joint[0].IresQ;
    joint[0].IdifD = joint[0].IrefD - joint[0].IresD;
    joint[1].IdifQ = joint[1].IrefQ_inv_2nd - joint[1].IresQ;
    joint[1].IdifD = joint[1].IrefD_inv_2nd - joint[1].IresD;
    joint[2].IdifQ = joint[2].IrefQ - joint[2].IresQ;
    joint[2].IdifD = joint[2].IrefD - joint[2].IresD;
    /// 電流PIコントローラ
    joint[0].VrefQ = q_current[0].PIcontroller_withAntiwindup(joint[0].IdifQ, (joint[0].Vlim_diffQ / joint[0].KpiQ), joint[0].KpiQ, joint[0].KiiQ, Ts, &q_current[0].uZ1, &q_current[0].yZ1);
    joint[0].VrefD = d_current[0].PIcontroller_withAntiwindup(joint[0].IdifD, (joint[0].Vlim_diffD / joint[0].KpiD), joint[0].KpiD, joint[0].KiiD, Ts, &d_current[0].uZ1, &d_current[0].yZ1);
    joint[1].VrefQ = q_current[1].PIcontroller_withAntiwindup(joint[1].IdifQ, (joint[1].Vlim_diffQ / joint[1].KpiQ), joint[1].KpiQ, joint[1].KiiQ, Ts, &q_current[1].uZ1, &q_current[1].yZ1);
    joint[1].VrefD = d_current[1].PIcontroller_withAntiwindup(joint[1].IdifD, (joint[1].Vlim_diffD / joint[1].KpiD), joint[1].KpiD, joint[1].KiiD, Ts, &d_current[1].uZ1, &d_current[1].yZ1);
    joint[2].VrefQ = q_current[2].PIcontroller_withAntiwindup(joint[2].IdifQ, (joint[2].Vlim_diffQ / joint[2].KpiQ), joint[2].KpiQ, joint[2].KiiQ, Ts, &q_current[2].uZ1, &q_current[2].yZ1);
    joint[2].VrefD = d_current[2].PIcontroller_withAntiwindup(joint[2].IdifD, (joint[2].Vlim_diffD / joint[2].KpiD), joint[2].KpiD, joint[2].KiiD, Ts, &d_current[2].uZ1, &d_current[2].yZ1);
    /// 非干渉化制御
    DecouplingControl(&joint[0]);
    DecouplingControl(&joint[1]);
    DecouplingControl(&joint[2]);

    // 2相->3相変換 dq->ab->uvw
    dq2ab(joint[0].VrefD_dcpl, joint[0].VrefQ_dcpl, joint[0].theta_re, &joint[0].VrefA, &joint[0].VrefB); //!< αβ軸へ変換
    ab2uvw(joint[0].VrefA, joint[0].VrefB, &joint[0].VrefU, &joint[0].VrefV, &joint[0].VrefW);            //!< UVW相へ変換
    dq2ab(joint[1].VrefD_dcpl, joint[1].VrefQ_dcpl, joint[1].theta_re, &joint[1].VrefA, &joint[1].VrefB); //!< αβ軸へ変換
    ab2uvw(joint[1].VrefA, joint[1].VrefB, &joint[1].VrefU, &joint[1].VrefV, &joint[1].VrefW);            //!< UVW相へ変換
    dq2ab(joint[2].VrefD_dcpl, joint[2].VrefQ_dcpl, joint[2].theta_re, &joint[2].VrefA, &joint[2].VrefB); //!< αβ軸へ変換
    ab2uvw(joint[2].VrefA, joint[2].VrefB, &joint[2].VrefU, &joint[2].VrefV, &joint[2].VrefW);            //!< UVW相へ変換
  }
  else
  { /// 制御OFFの時
    // PE-ViewXはC89のコンパイラを使用している.
    int i; // C89だとfor文のカウント変数を事前に宣言しておく必要がある。
    for (i = 0; i < 3; i++)
    {
      joint[i].VrefU = 0;
      joint[i].VrefV = 0;
      joint[i].VrefW = 0;
      joint[i].IrefQ = 0;
      joint[i].IrefD = 0;
    }
  }

  // PEV_inverter_control_break()でブレーキの制御を正論理PWMで制御するように設定した
  // ファンクションリファレンスマニュアルpp.133の変調率の関係から、ブレーキチョッパのon/offの変調率は以下のように表される。
  // +2 : 常時ON
  // -2 : 常時OFF
  if (flag_Vdc_setted == 1)
  {
    BrakeController(&axis1);
    BrakeController(&axis2);
    BrakeController(&axis3);
    // axis2.MRBR = 2;
  }
  else
  {
    axis1.MRBR = -2;
    axis2.MRBR = -2;
    axis3.MRBR = -2;
  }
  WAVE_MRBR1 = axis1.MRBR;
  WAVE_MRBR2 = axis2.MRBR;
  WAVE_MRBR3 = axis3.MRBR;

  /// 電圧指令をインバータへ入力
  SetVoltReferences(&joint[0]);
  SetVoltReferences(&joint[1]);
  SetVoltReferences(&joint[2]);

  // 以下監視用変数への代入
  WAVE_Joint1 = joint_cmd[0];
  WAVE_Joint2 = joint_cmd[1];
  WAVE_Joint3 = joint_cmd[2];
  WAVE_HandX = hand_cmd[0];
  WAVE_HandY = hand_cmd[1];
  WAVE_HandZ = hand_cmd[2];

  WAVE_IresU1 = axis1.IresU;
  WAVE_IresV1 = axis1.IresV;
  WAVE_IresW1 = axis1.IresV;
  WAVE_Vdc1 = axis1.Vdc;
  WAVE_Idc1 = axis1.Idc;

  WAVE_IresU2 = axis2.IresU;
  WAVE_IresV2 = axis2.IresV;
  WAVE_IresW2 = axis2.IresW;
  WAVE_Vdc2 = axis2.Vdc;
  WAVE_Idc2 = axis2.Idc;

  WAVE_IresU3 = axis3.IresU;
  WAVE_IresV3 = axis3.IresV;
  WAVE_IresW3 = axis3.IresW;
  WAVE_Vdc3 = axis3.Vdc;
  WAVE_Idc3 = axis3.Idc;

  // 電流ループと位置/速度ループの制御周期が同じ時のエンコーダ情報格納変数
  WAVE_theta_rm1 = axis1.theta_rm;
  WAVE_theta_rm2 = axis2.theta_rm;
  WAVE_theta_rm3 = axis3.theta_rm;

  WAVE_theta_rm_full1 = axis1.theta_rm_full;
  WAVE_theta_rm_full2 = axis2.theta_rm_full;
  WAVE_theta_rm_full3 = axis3.theta_rm_full;

  WAVE_wm1 = axis1.wm;
  WAVE_wm2 = axis2.wm;
  WAVE_wm3 = axis3.wm;
  WAVE_qm1 = axis1.qm;
  WAVE_qm2 = axis2.qm;
  WAVE_qm3 = axis3.qm;
  WAVE_ql1 = axis1.ql;
  WAVE_ql2 = axis2.ql;
  WAVE_ql3 = axis3.ql;
  WAVE_Iq1 = axis1.Iq;
  WAVE_Iq2 = axis2.Iq;
  WAVE_Iq3 = axis3.Iq;

  WAVE_Isfb1 = axis1.Isfb;
  WAVE_Isfb2 = axis2.Isfb;
  WAVE_Isfb3 = axis3.Isfb;

  WAVE_Iff_1 = axis1.Iff;
  WAVE_Iff_2 = axis2.Iff;
  WAVE_Iff_3 = axis3.Iff;

  WAVE_wm_ref1 = axis1.wm_ref;
  WAVE_wm_ref2 = axis2.wm_ref;
  WAVE_wm_ref3 = axis3.wm_ref;

  WAVE_qm_ref1 = axis1.qm_ref;
  WAVE_qm_ref2 = axis2.qm_ref;
  WAVE_qm_ref3 = axis3.qm_ref;

  WAVE_wm_cmd1 = axis1.wm_cmd;
  WAVE_wm_cmd2 = axis2.wm_cmd;
  WAVE_wm_cmd3 = axis3.wm_cmd;
  WAVE_wm_CCC1 = motor_vel_cmd[0];
  WAVE_wm_CCC2 = motor_vel_cmd[1];
  WAVE_wm_CCC3 = motor_vel_cmd[2];

  WAVE_IrefQ1 = axis1.IrefQ;
  WAVE_IrefQ2 = axis2.IrefQ;
  WAVE_IrefQ3 = axis3.IrefQ;

  WAVE_IresQ1 = axis1.IresQ;
  WAVE_IresQ2 = -axis2.IresQ;
  WAVE_IresQ3 = axis3.IresQ;

  WAVE_IrefD1 = axis1.IrefD;
  WAVE_IrefD2 = axis2.IrefD;
  WAVE_IrefD3 = axis3.IrefD;

  WAVE_IresD1 = axis1.IresD;
  WAVE_IresD2 = -axis2.IresD;
  WAVE_IresD3 = axis3.IresD;

  WAVE_VrefD1 = axis1.VrefD;
  WAVE_VrefQ1 = axis1.VrefQ;
  WAVE_VrefD2 = axis2.VrefD;
  WAVE_VrefQ2 = axis2.VrefQ;
  WAVE_VrefD3 = axis3.VrefD;
  WAVE_VrefQ3 = axis3.VrefQ;

  WAVE_VrefU1 = axis1.VrefU;
  WAVE_VrefV1 = axis1.VrefV;
  WAVE_VrefW1 = axis1.VrefW;
  WAVE_VrefU2 = axis2.VrefU;
  WAVE_VrefV2 = axis2.VrefV;
  WAVE_VrefW2 = axis2.VrefW;
  WAVE_VrefU3 = axis3.VrefU;
  WAVE_VrefV3 = axis3.VrefV;
  WAVE_VrefW3 = axis3.VrefW;

  WAVE_IresU2 = axis2.IresU;
  WAVE_IresV2 = axis2.IresV;
  WAVE_IresW2 = axis2.IresW;

  WAVE_ofst_Iu = sen[1].offset[0];

  WAVE_omega_rm1 = axis1.omega_rm;
  WAVE_omega_rm2 = axis2.omega_rm;
  WAVE_omega_rm3 = axis3.omega_rm;

  WAVE_omega_rm1_ref = axis1.omega_rm_ref;
  WAVE_omega_rm2_ref = axis2.omega_rm_ref;
  WAVE_omega_rm3_ref = axis3.omega_rm_ref;

  WAVE_Tq1 = axis1.Tq;
  WAVE_Tq2 = axis2.Tq;
  WAVE_Tq3 = axis3.Tq;

  WAVE_Icmp1 = axis1.Icmp;
  WAVE_Icmp2 = axis2.Icmp;
  WAVE_Icmp3 = axis3.Icmp;

  // ModRatioU = axis2.Vu_std;
  // ModRatioV = axis2.Vv_std;
  // ModRatioW = axis2.Vw_std;

  WAVE_tauLdyn1 = axis1.tauLdyn;
  WAVE_tauLdyn2 = axis2.tauLdyn;
  WAVE_tauLdyn3 = axis3.tauLdyn;

  WAVE_Jl_calc1 = axis1.Jl_calc;
  WAVE_Jl_calc2 = axis2.Jl_calc;
  WAVE_Jl_calc3 = axis3.Jl_calc;

  WAVE_al_calc1 = axis1.al_calc;
  WAVE_wl_calc1 = axis1.wl_calc;
  WAVE_ql_calc1 = axis1.ql_calc;
  WAVE_wm_calc1 = axis1.wm_calc;
  WAVE_al_calc2 = axis2.al_calc;
  WAVE_wl_calc2 = axis2.wl_calc;
  WAVE_ql_calc2 = axis2.ql_calc;
  WAVE_wm_calc2 = axis2.wm_calc;
  WAVE_al_calc3 = axis3.al_calc;
  WAVE_wl_calc3 = axis3.wl_calc;
  WAVE_ql_calc3 = axis3.ql_calc;
  WAVE_wm_calc3 = axis3.wm_calc;

  WAVE_al_calc_DPD1 = axis1.al_calc_DPD;
  WAVE_wl_calc_DPD1 = axis1.wl_calc_DPD;
  WAVE_ql_calc_DPD1 = axis1.ql_calc_DPD;
  WAVE_wm_calc_DPD1 = axis1.wm_calc_DPD;
  WAVE_al_calc_DPD2 = axis2.al_calc_DPD;
  WAVE_wl_calc_DPD2 = axis2.wl_calc_DPD;
  WAVE_ql_calc_DPD2 = axis2.ql_calc_DPD;
  WAVE_wm_calc_DPD2 = axis2.wm_calc_DPD;
  WAVE_al_calc_DPD3 = axis3.al_calc_DPD;
  WAVE_wl_calc_DPD3 = axis3.wl_calc_DPD;
  WAVE_ql_calc_DPD3 = axis3.ql_calc_DPD;
  WAVE_wm_calc_DPD3 = axis3.wm_calc_DPD;

  WAVE_TRG_WM1 = axis1.posi_trg_rad;
  WAVE_TRG_WM2 = axis2.posi_trg_rad;
  WAVE_TRG_WM3 = axis3.posi_trg_rad;
  if (flag_SOB == 0)
  {
    WAVE_est_wm2 = axis2.est_conv_wm;
    WAVE_est_qs2 = axis2.est_conv_qs;
    WAVE_est_wl2 = axis2.est_conv_wl;
    WAVE_est_wm3 = axis3.est_conv_wm;
    WAVE_est_qs3 = axis3.est_conv_qs;
    WAVE_est_wl3 = axis3.est_conv_wl;
  }
  else if (flag_SOB == 1)
  {
    WAVE_est_wm2 = axis2.est_prop_wm;
    WAVE_est_qs2 = axis2.est_prop_qs;
    WAVE_est_wl2 = axis2.est_prop_wl;
    WAVE_est_wm3 = axis3.est_prop_wm;
    WAVE_est_qs3 = axis3.est_prop_qs;
    WAVE_est_wl3 = axis3.est_prop_wl;
  }
  else if (flag_SOB == 2)
  {
    WAVE_est_wm2 = axis2.est_prop_wm;
    WAVE_est_qs2 = axis2.est_prop_qs;
    WAVE_est_wl2 = axis2.est_prop_wl;
    WAVE_est_wm3 = axis3.est_prop_wm;
    WAVE_est_qs3 = axis3.est_prop_qs;
    WAVE_est_wl3 = axis3.est_prop_wl;
  }

  WAVE_est_conv_wm1 = axis1.est_conv_wm;
  WAVE_est_conv_qs1 = axis1.est_conv_qs;
  WAVE_est_conv_wl1 = axis1.est_conv_wl;
  WAVE_est_conv_wm2 = axis2.est_conv_wm;
  WAVE_est_conv_qs2 = axis2.est_conv_qs;
  WAVE_est_conv_wl2 = axis2.est_conv_wl;
  WAVE_est_conv_wm3 = axis3.est_conv_wm;
  WAVE_est_conv_qs3 = axis3.est_conv_qs;
  WAVE_est_conv_wl3 = axis3.est_conv_wl;

  WAVE_est_prop_wm1 = axis1.est_prop_wm;
  WAVE_est_prop_qs1 = axis1.est_prop_qs;
  WAVE_est_prop_wl1 = axis1.est_prop_wl;
  WAVE_est_prop_wm2 = axis2.est_prop_wm;
  WAVE_est_prop_qs2 = axis2.est_prop_qs;
  WAVE_est_prop_wl2 = axis2.est_prop_wl;
  WAVE_est_prop_wm3 = axis3.est_prop_wm;
  WAVE_est_prop_qs3 = axis3.est_prop_qs;
  WAVE_est_prop_wl3 = axis3.est_prop_wl;

  WAVE_est_ISOB_wm1 = axis1.est_ISOB_wm;
  WAVE_est_ISOB_qs1 = axis1.est_ISOB_qs;
  WAVE_est_ISOB_wl1 = axis1.est_ISOB_wl;
  WAVE_est_ISOB_wm2 = axis2.est_ISOB_wm;
  WAVE_est_ISOB_qs2 = axis2.est_ISOB_qs;
  WAVE_est_ISOB_wl2 = axis2.est_ISOB_wl;
  WAVE_est_ISOB_wm3 = axis3.est_ISOB_wm;
  WAVE_est_ISOB_qs3 = axis3.est_ISOB_qs;
  WAVE_est_ISOB_wl3 = axis3.est_ISOB_wl;

  WAVE_Kpp1 = axis1.Kpp;
  WAVE_Kff1 = axis1.Kff;
  WAVE_Kfb1 = axis1.Kfb;
  WAVE_Kvp1 = axis1.Kvp;
  WAVE_Kvi1 = axis1.Kvi;
  WAVE_fwm1 = axis1.fwm;
  WAVE_fqs1 = axis1.fqs;
  WAVE_fwl1 = axis1.fwl;

  WAVE_Kpp2 = axis2.Kpp;
  WAVE_Kff2 = axis2.Kff;
  WAVE_Kfb2 = axis2.Kfb;
  WAVE_Kvp2 = axis2.Kvp;
  WAVE_Kvi2 = axis2.Kvi;
  WAVE_fwm2 = axis2.fwm;
  WAVE_fqs2 = axis2.fqs;
  WAVE_fwl2 = axis2.fwl;

  WAVE_Kpp3 = axis3.Kpp;
  WAVE_Kff3 = axis3.Kff;
  WAVE_Kfb3 = axis3.Kfb;
  WAVE_Kvp3 = axis3.Kvp;
  WAVE_Kvi3 = axis3.Kvi;
  WAVE_fwm3 = axis3.fwm;
  WAVE_fqs3 = axis3.fqs;
  WAVE_fwl3 = axis3.fwl;
  // WAVE_ACC_LW8174_axis = axis2.al; // 加速度センサrad/s^2換算値
  // WAVE_ACC_LW8079 = ACC_LW8079;
  // WAVE_ACC_LW8174 = ACC_LW8174;
  // WAVE_Fz         = Fz;
  // WAVE_WSX        = WSX;
  // WAVE_WSY        = WSY;
  // WAVE_WSZ        = WSZ;

  // 制御演算開始
  t = (float)LoopCount * Ts; //!< 時刻計算
  WAVE_LoopCount = -WAVE_LoopCount;
  LoopCount++; // 時刻計算のため, ループ回数+1

  // 制御周期の測定結果出力

  WAVE_Timer2 = (float)C6657_timer2_read() * 4.8e-9 * 1e6;
  int3_ack(); //!< 次の割り込みを可能にするための関数
}
/**	@brief 各種ボード, インバータの初期化
 * PEV_sync_pwm_init( INT32 bdn, INT32 mode, INT32 int_num ); <br/>
 * PEV_sync_ad_init( INT32 bdn, INT32 mode, INT32 int_num );	<br/>
 * PEVボード間で同期を取るための関数である。それぞれ pwd同期, AD同期	<br/>
 * int num が同期信号の受信chである。(1~8),【注意】1つの信号につき同期信号1ch必要である。<br/>
 * ad同期信号を２つのボードに出す場合は <br/>
 * PEV_sync_ad_out( BDN0, 1)
 * PEV_sync_ad_out( BDN0, 2) <br/>
 * 更にpwdも同期したい場合は
 * PEV_sync_pwm_out( BDN0, 3, 0, 0);
 * PEV_sync_pwm_out( BDN0, 4, 0, 0);
 * 割り込み関数に変数を渡す場合はグローバル変数しかない気がする。*/
void MW_main(void)
{
  int_disable(); // Disabling all interrupt
  // int_disable();で割り込みの停止
  // int_enable();が呼ばれるまではリアルタイム処理を行う必要が無い,
  // 重たい処理, 初期化はここ
  int i;

  for (i = 0; i < 3; i++)
  {
    /// @brief 関数のポインタのメンバに対して関数のアドレスを代入
    /// @brief これで関数を構造体のメンバとして呼び出せる
    q_current[i].PIcontroller_withAntiwindup = PIcontroller_withAntiwindup;
    d_current[i].PIcontroller_withAntiwindup = PIcontroller_withAntiwindup;

    velocity[i].PIcontroller = PIcontroller;
    // PIDでも良い
    position[i].PIcontroller = PIcontroller;
  }

  SetBDN(&axis1, BDN0);       /// Robot構造体変数jointにボード番号をセット
  SetENC_CH(&axis1, ENC_CH0); /// Robot構造体変数jointにエンコーダchをセット

  SetBDN(&axis2, BDN1);       /// Robot構造体変数jointにボード番号をセット
  SetENC_CH(&axis2, ENC_CH1); /// Robot構造体変数jointにエンコーダchをセット

  SetBDN(&axis3, BDN2);       /// Robot構造体変数jointにボード番号をセット
  SetENC_CH(&axis3, ENC_CH2); /// Robot構造体変数jointにエンコーダchをセット

  float fs = 5.0;
  float fs2 = 10.0;
  float Q = 1.0 / sqrt(2.0);
  SetLPF(LPF_motor, Tp, fs, Q);
  SetLPF(LPF_cmd, Tp, fs, Q);

  /// ゲインのセット
  SetGain(joint);

  /// 初期位置のセット
  GetMultiPositions(joint);
  axis1.theta_rm_init = axis1.theta_rm;
  axis2.theta_rm_init = axis2.theta_rm;
  axis3.theta_rm_init = axis3.theta_rm;

  // ロボット実験開始時姿勢
  axis1.theta_rl_init = 0.0 * PI / 180.0; // [rad]
  // JL最大
  // axis2.theta_rl_init = 90.0 * PI/180.0; // [rad]
  // axis3.theta_rl_init = -75.0 * PI/180.0; // [rad]
  // 80%
  // axis2.theta_rl_init = 41.27 * PI/180.0; // [rad]
  // axis3.theta_rl_init = 0.76 * PI/180.0; // [rad]
  // 50%
  // axis2.theta_rl_init = 6.03 * PI/180.0; // [rad]
  // axis3.theta_rl_init = 50.25 * PI/180.0; // [rad]

  axis2.theta_rl_init = 0.0 * PI / 180.0; // [rad]
  // axis2.theta_rl_init =  -axis2.theta_rl_init;
  axis3.theta_rl_init = 0.0 * PI / 180.0; // [rad]

  // 指令値の設定値
  SetRampParams(cmd_1_soft[0], cmd_2_soft[0], cmd_3_soft[0]);

  // 動力学計算の定数計算関数
  // 引数 0 : 無負荷
  // 引数 1 : 7.2kg負荷
  // 引数 2 : 3.7kg負荷
  CalcDynamicsInit(flag_dyn_payload);

  // 負荷側情報計算関数の定数計算関数
  CalcFDTDWrInit_QmrefInputType();
  
  CalcFDTDWrInit_WmcmdInputType(&axis1);
  CalcFDTDWrInit_WmcmdInputType(&axis2);
  CalcFDTDWrInit_WmcmdInputType(&axis3);

  // FDTD状態オブザーバの定数計算関数
  CalcFDTDTSOBInit();

  // FF制御　補償電流計算関数Tm 係数計算
  FDTD_Tm_Init();

  // 可変ゲインの極を指定する(係数図法)
  // 1軸目
  gsub[0].tau_pole = 0.1;
  gsub[0].tau_cdm = 0.05;
  gsub[0].zw = 30.0;
  gsub[0].r_cdm1 = 2.5;
  gsub[0].r_cdm2 = 2.0;
  gsub[0].r_cdm3 = 2.0;
  gsub[0].r_cdm4 = 2.0;
  // 2軸目
  gsub[1].tau_pole = 0.1;
  gsub[1].tau_cdm = 0.05;
  gsub[1].zw = 30.0;
  gsub[1].r_cdm1 = 2.5;
  gsub[1].r_cdm2 = 2.0;
  gsub[1].r_cdm3 = 2.0;
  gsub[1].r_cdm4 = 2.0;
  // 3軸目
  gsub[2].tau_pole = 0.1;
  gsub[2].tau_cdm = 0.058;
  gsub[2].zw = 30.0;
  gsub[2].r_cdm1 = 2.5;
  gsub[2].r_cdm2 = 2.0;
  gsub[2].r_cdm3 = 2.0;
  gsub[2].r_cdm4 = 2.0;

  // 可変ゲインの定数計算関数
  CalcPVGainInitCDM(); // 係数図法

  // 三角加速度指令の定数計算関数
  // 引数の解説                             (ql_const_deg, q_time_full, w_time_full, Rg, BDN);
  TriangularAccelerationCommandGeneratorInit(60.0, 1.0, 0.2, axis1.Rgn, axis1.BDN);
  TriangularAccelerationCommandGeneratorInit(2.0, 2.0, 1.0, axis2.Rgn, axis2.BDN);
  TriangularAccelerationCommandGeneratorInit(2.0, 2.0, 1.0, axis3.Rgn, axis3.BDN);

  /// q軸電流指令リミッタ 定格 5.1*sqrt(3/2) [A]
  axis1.IrefQ_Lim = 15.0; // 10.2; // 定格 5.1[A]の3倍
  /// d軸電流指令リミッタ 定格 5.1*sqrt(3/2) [A]
  axis1.IrefD_Lim = 15.0; // 10.2; // 定格 5.1[A]の3倍

  /// q軸電流指令リミッタ 定格 7.9*sqrt(3/2) [A]
  axis2.IrefQ_Lim = 23.7; // 定格7.9[A]の3倍。 //7.9*sqrtf(3.0/2.0);
  /// d軸電流指令リミッタ 定格 7.9*sqrt(3/2) [A]
  axis2.IrefD_Lim = 23.7; // 定格7.9[A]の3倍。 //7.9*sqrtf(3.0/2.0);

  /// q軸電流指令リミッタ 定格 4.6*sqrt(3/2) [A]
  axis3.IrefQ_Lim = 13.8; // 定格4.6[A]の3倍。 //4.6*sqrtf(3.0/2.0);
  /// d軸電流指令リミッタ 定格 4.6*sqrt(3/2) [A]
  axis3.IrefD_Lim = 13.8; // 定格4.6[A]の3倍。 //4.6*sqrtf(3.0/2.0);

  /// 1軸 MWINV-5R022 電圧センサモニタ部仕様 Page. 16/39 より 500V/5V = 100[V/V]
  sen[0].VtoVdc = 100.0;
  /// 1軸 MWINV-5R022 電流センサモニタ部仕様(U相,W相共通) 31.25A/5V = 6.25[A/V]
  sen[0].VtoI = 6.25;
  /// 1軸 MWINV-5R022 電流センサモニタ部仕様 31.25A/5V = 6.25[A/V]
  sen[0].VtoIdc = 6.25;
  /// 2軸 MWINV-9R122B 電流センサモニタ部仕様 Page. 16/40 より 400V/5V = 80[V/V]
  sen[1].VtoVdc = 80.0;
  /// 2軸 MWPE-IS-01 電流センサーユニット Page. 5/7 (50A,5回巻き)10A/5V = 2[A/V] -> 2軸目の定格電流は7.9[A]。瞬時最大で定格の3倍(=23.7[A])まで観測できない
  // sen[1].VtoI = 2.0;
  /// 2軸 MWINV-9R122B 電流センサモニタ部仕様 Page. 16/40 より 50/5V = 10[V/V]
  sen[1].VtoI = 10.0;
  /// 2軸 MWINV-9R122B 電流センサモニタ部仕様 Page. 16/40 より 50/5V = 10[V/V]
  sen[1].VtoIdc = 10.0;
  /// 3軸 MWINV-5R022 電圧センサモニタ部仕様 Page. 16/39 より 500V/5V = 100[V/V]
  sen[2].VtoVdc = 100.0;
  /// 3軸 MWINV-5R022 電流センサモニタ部仕様(U相,W相共通) 31.25A/5V = 6.25[A/V]
  sen[2].VtoI = 6.25;

  PEV_int_init(BDN0, 0, 0, 0, 2, 0, 0, 0, 0); // 割り込み設定

  int3_init_vector(ControlFunction, (CSL_IntcVectId)4, FALSE); // 割り込みルーチンの設定, 割り込み関数名の設定:ControlFunction
  int3_enable_int();                                           // 初期化
  PEV_init(BDN0);                                              // PEVボード初期化
  PEV_init(BDN1);                                              // PEVボード初期化
  PEV_init(BDN2);                                              // PEVボード初期化

  PEV_inverter_init(BDN0, (INT32)Fs, (INT32)(Td * 1e9)); // PWMキャリア周波数とデッドタイムの設定
  PEV_inverter_init(BDN1, (INT32)Fs, (INT32)(Td * 1e9)); /* Setting carrier frequency and dead time		 					*/
  PEV_inverter_init(BDN2, (INT32)Fs, (INT32)(Td * 1e9)); /* Setting carrier frequency and dead time		 					*/

  PEV_sync_ad_init(BDN0, 1, 0); /* Setting ad sync mode. Master			 							*/
  PEV_sync_ad_init(BDN1, 0, 1); /* Setting ad sync mode. Slave 									*/
  PEV_sync_ad_init(BDN2, 0, 1); /* Setting ad sync mode. Slave 			 							*/
  PEV_sync_ad_out(BDN0, 1);     /* Setting ad sync mode. 	 			 							*/

  PEV_sync_pwm_init(BDN0, 1, 0);   /* Setting sync mode	 											*/
  PEV_sync_pwm_init(BDN1, 0, 3);   /* Setting sync mode	 											*/
  PEV_sync_pwm_init(BDN2, 0, 4);   /* 同期信号ch1につきボード1枚同期なのでch2目の同期信号設定	 											*/
  PEV_sync_pwm_out(BDN0, 3, 0, 0); /* Setting sync mode	 											*/
  PEV_sync_pwm_out(BDN0, 4, 0, 0); /* Setting sync mode	 											*/

  PEV_ad_set_range(BDN0, range); /* AD converter range setup*/
  PEV_ad_set_mode(BDN0, 1);      /* AD convert mode = career synchronous mode*/
  PEV_ad_set_range(BDN1, range); /* AD converter range setup*/
  PEV_ad_set_mode(BDN1, 1);      /* AD convert mode = career synchronous mode*/
  PEV_ad_set_range(BDN2, range); /* AD converter range setup*/
  PEV_ad_set_mode(BDN2, 1);      /* AD convert mode = career synchronous mode*/

  ENC_ss_init(BDN_ENC, ENC_CH0); // エンコーダボード初期設定	シングルショットモード用
  ENC_ss_init(BDN_ENC, ENC_CH1); // エンコーダボード初期設定	シングルショットモード用
  ENC_ss_init(BDN_ENC, ENC_CH2); // エンコーダボード初期設定	シングルショットモード用

  PEV_inverter_set_uvw(BDN0, 0, 0, 0, 0); /* Setting initial PWM references									*/
  PEV_inverter_set_uvw(BDN1, 0, 0, 0, 0); /* Setting initial PWM references									*/
  PEV_inverter_set_uvw(BDN2, 0, 0, 0, 0); /* Setting initial PWM references										*/

  PEV_inverter_init_adtrig_timing(BDN0, 1, 0); // 三角波の山でAD変換開始
  PEV_inverter_init_adtrig_timing(BDN1, 1, 0); // 三角波の山でAD変換開始
  PEV_inverter_init_adtrig_timing(BDN2, 1, 0); // 三角波の山でAD変換開始

  PEV_inverter_init_refload_timing(BDN0, 1); // 山で電圧指令値更新
  PEV_inverter_init_refload_timing(BDN1, 1); // 山で電圧指令値更新
  PEV_inverter_init_refload_timing(BDN2, 1); // 山で電圧指令値更新

  PEV_inverter_enable_int(BDN0); /* Enabling INT5 intrrupt at the top point of the carrier mountain	*/
  PEV_inverter_enable_int(BDN1); /* Enabling INT5 intrrupt at the top point of the carrier mountain	*/
  PEV_inverter_enable_int(BDN2); /* Enabling INT5 intrrupt at the top point of the carrier mountain	*/

  // ブレーキアーム設定 正論理PWM
  PEV_inverter_control_break(BDN0, 0);
  PEV_inverter_control_break(BDN1, 0);
  PEV_inverter_control_break(BDN2, 0);

  // 制御周期測定用タイマの初期化
  C6657_timer0_init(1e+6); // 割り込みとして使わないので割り込み周期は適当
  C6657_timer1_init(1e+6); // 割り込みとして使わないので割り込み周期は適当
  C6657_timer2_init(1e+6); // 割り込みとして使わないので割り込み周期は適当

  int_enable();
  PEV_ad_disable_int(BDN0);
  PEV_ad_disable_int(BDN1);
  PEV_ad_disable_int(BDN2);   /* Enabling all interrupts											*/
  C6657_timer0_disable_int(); // 割り込みを無効化
  C6657_timer1_disable_int(); // 割り込みを無効化
  C6657_timer2_disable_int(); // 割り込みを無効化
  wait((INT32)(Ts * 1e6));    /* Waitting more than half of the carrier period					*/

  PEV_inverter_start_pwm(BDN0); /* Starting 3-phase PWM signal output								*/
  PEV_inverter_start_pwm(BDN1); /* Starting 3-phase PWM signal output								*/
  PEV_inverter_start_pwm(BDN2); /* Starting 3-phase PWM signal output								*/

  while (1)
  {
  } /* 割り込み待ち */
}

/*! @brief 台形速度位置指令用のパラメータを設定する。
  @param	[in] cmd1 // 1軸位置目標値
  @param	[in] cmd2 // 2軸位置目標値
  @param	[in] cmd3 // 3軸位置目標値
  */
void SetRampParams(float cmd1, float cmd2, float cmd3)
{
  // 指令値の設定値
  // 1軸目指令
  axis1.posi_trg_rad = cmd1; // 　モータ側目標位置
  axis1.t_const = 4.0;       // 定常値の時間　三角波なら0
  axis1.t_ramp = 2.0;        // ランプアップ時間
  axis1.t_ramp_back = axis1.t_ramp;
  axis1.t_start = 2.0; // 待機時間
  axis1.vel = axis1.posi_trg_rad / (axis1.t_const + axis1.t_ramp);
  axis1.a_ramp = axis1.vel / axis1.t_ramp; // 傾き
  axis1.a_ramp_back = -axis1.a_ramp_back;

  // 2軸目指令
  axis2.posi_trg_rad = cmd2; // 　モータ側目標位置
  axis2.t_const = 4.0;       // 定常値の時間　三角波なら0
  axis2.t_ramp = 2.0;        // ランプアップ時間
  axis2.t_ramp_back = axis2.t_ramp;
  axis2.t_start = 2.0; // 待機時間
  axis2.vel = axis2.posi_trg_rad / (axis2.t_const + axis2.t_ramp);
  axis2.a_ramp = axis2.vel / axis2.t_ramp; // 傾き
  axis2.a_ramp_back = -axis2.a_ramp_back;

  // 3軸目指令
  axis3.posi_trg_rad = cmd3; // 　モータ側目標位置
  axis3.t_const = 4.0;       // 定常値の時間　三角波なら0
  axis3.t_ramp = 2.0;        // ランプアップ時間
  axis3.t_ramp_back = axis3.t_ramp;
  axis3.t_start = 2.0; // 待機時間
  axis3.vel = axis3.posi_trg_rad / (axis3.t_const + axis3.t_ramp);
  axis3.a_ramp = axis3.vel / axis3.t_ramp; // 傾き
  axis3.a_ramp_back = -axis3.a_ramp_back;
}

/*! @brief PVEボード番号を代入する関数
  @param	[in,out] Robot
  @param	[in]	Bnum	PVEボード番号
  */
void SetBDN(Robot *robo, int Bnum)
{
  robo->BDN = Bnum;
}
/*! @brief エンコーダチャンネルを代入する関数
  @param	[in,out] Robot
  @param	[in]	Ech	エンコーダチャンネル番号
 */
void SetENC_CH(Robot *robo, int Ech)
{
  robo->ENC_CH = Ech;
}

/** @brief 多摩川エンコーダ専用　エンコーダボードによる位置情報取得関数
 エンコーダはアブソリュート型
 @param [in] Robot.BDN PEV ボード番号
 @param [in] Robot.ENC_CH エンコーダチャンネル
 @param [out]	Robot.theta_re	電気角[rad]
 @param [out]	Robot.theta_rm	モータ角度[rad]
 @param [out]	Robot.theta_rm_full モータ総回転角度[rad]
*/

/** @brief 多摩川エンコーダ専用　エンコーダボードによる位置情報取得関数
 * 	複数軸(1,2,3)の情報をまとめて取得する。
 */
// #pragma CODE_SECTION(GetMultiPositions, “.CODE_ON_HIGHER_SPEED”)

void GetMultiPositions(Robot robo[])
{
  int enc_data[3] = {0};
  int enc_data_temp[3] = {0};
  float theta_re_temp[3] = {0};             //!< 臨時使用変数
  const float theta_reso = 2 * PI / 131072; //!< [rad/bit]	エンコーダ分解能17bit (機械角)
  const float theta_re_offset = PI;         //!< 電気角オフセット（エンコーダ零点と磁極の位置関係から）
  int i;
  for (i = 0; i < 3; i++)
  {
    ENC_ss_get_start(BDN_ENC, robo[i].ENC_CH); // エンコーダのデータ要求信号の開始
  }
  GetVoltAndCurrent(&joint[0], &sen[0]); //!< robot構造体に各部電圧電流の格納
  GetVoltAndCurrent(&joint[1], &sen[1]); //!< robot構造体に各部電圧電流の格納
  GetVoltAndCurrent(&joint[2], &sen[2]); //!< robot構造体に各部電圧電流の格納

  // データ未確定時とパラメータ異常の判定
  while (1)
  {
    enc_data_temp[0] = ENC_ss_get_abs(BDN_ENC, ENC_CH0);
    enc_data_temp[1] = ENC_ss_get_abs(BDN_ENC, ENC_CH1);
    enc_data_temp[2] = ENC_ss_get_abs(BDN_ENC, ENC_CH2);
    WAVE_ENC_temp1 = enc_data_temp[0];
    WAVE_ENC_temp2 = enc_data_temp[1];
    WAVE_ENC_temp3 = enc_data_temp[2];
    if (enc_data_temp[0] != 0xDFFFFFFF && enc_data_temp[1] != 0xDFFFFFFF && enc_data_temp[2] != 0xDFFFFFFF)
    { // データ未確定時は無限ループで待機
      if (enc_data_temp[0] != 0xEFFFFFFF && enc_data_temp[1] != 0xEFFFFFFF && enc_data_temp[2] != 0xEFFFFFFF)
      { // パラメータ異常時は無限ループで待機
        if (0 <= enc_data_temp[0] && enc_data_temp[0] <= 131072 && 0 <= enc_data_temp[1] && enc_data_temp[1] <= 131072 && 0 <= enc_data_temp[2] && enc_data_temp[2] <= 131072)
        {
          // エンコーダbit値の取得
          enc_data[0] = enc_data_temp[0];
          enc_data[1] = enc_data_temp[1];
          enc_data[2] = enc_data_temp[2];
          WAVE_ENC1 = enc_data[0];
          WAVE_ENC2 = enc_data[1];
          WAVE_ENC3 = enc_data[2];
          break;
        }
      }
    }
  }
  /********************************************************************
    エンコーダボードより取得した位置情報を演算
   ********************************************************************/
  for (i = 0; i < 3; i++)
  {
    // 総回転情報用の処理
    if (0x0001F000 < robo[i].enc_data_prev && enc_data[i] < 0x00000FFF)
    { // 17bitオーバーフローを検出したら
      // 判定に用いる値は試行錯誤的に決定
      robo[i].up_count_m++; // 上位カウンタをカウントアップ
    }
    if (robo[i].enc_data_prev < 0x00000FFF && 0x0001F000 < enc_data[i])
    {                       // 17bitアンダーフローを検出したら
      robo[i].up_count_m--; // 上位カウンタをカウントダウン
    }
    robo[i].enc_data_prev = enc_data[i]; // 次回のために今回のカウント値を記録
    // 機械角の戻り値
    robo[i].theta_rm = (float)enc_data[i] * theta_reso;                                               // 機械角[rad]を返す (0～2πの値域)
    robo[i].theta_rm_full = (float)enc_data[i] * theta_reso + 2.0 * PI * ((float)robo[i].up_count_m); // 機械角[rad]を返す

    // 電気角演算
    theta_re_temp[i] = (robo[i].p) * enc_data[i] * theta_reso + theta_re_offset; // 極対数*機械角（0～2pi) + オフセット

    while (theta_re_temp[i] >= 2.0 * PI)
    { // 電気角が0～2piとなるようにwhileで繰り返す
      theta_re_temp[i] -= 2.0 * PI;
    }
    while (theta_re_temp[i] <= -2.0 * PI)
    {
      theta_re_temp[i] += 2.0 * PI;
    }
    robo[i].theta_re = theta_re_temp[i];
  }
}
/**
 * 多摩川エンコーダ専用　エンコーダボードより取得した位置情報の
 * 加算型theta_rm_full より速度情報の演算
 */
float GetVelocity(float theta, volatile float *theta_Z1, const float Ts)
{
  // 速度応答を取得する関数
  float ret;
  ret = (theta - (*theta_Z1)) / (Ts); //!< 位置差分
  *theta_Z1 = theta;                  //!< 次回用に今回の位置を格納
  return ret;                         //
}
/////////////////////////////////////////////////////////////////////////////////////////////
/*!	@brief オフセット計算
  @param[out] Sensor.offset[] Sensor構造体メンバ
  @param[in]  int BDN PEVボード番号
  @param[in]  Sensor.VtoI	センサ換算ゲイン
  @param[in]	Sensor.VtoVdc センサ換算ゲイン
*/
void CalcOffset(int BDN, Sensor *sense)
{
  // static int offset_count =0;
  float Vadc[8] = {0};
  float VtoI = sense->VtoI;       //!< 電流センサ出力電圧->電流換算ゲイン
  float VtoVdc = sense->VtoVdc;   /// 電圧センサ出力電圧->電圧換算ゲイン
  float VtoIdc = sense->VtoIdc;   //!< 電流センサ出力電圧->電流換算ゲイン
  const float VtoMM_IL600 = 80.0; // [mm/V] レーザ変位計IL-600
  // const float VtoMM_IL100 = 4.0;		// [mm/V] レーザ変位計IL-100
  const float VtoACC_LW8174 = 1 / (20.30e-3); // [(m/s^2)/V] DC加速度センサ 20.30 [mV/(m/s^2)]:Model 3711B1110G, SERIAL LW8174
  const float VtoACC_LW8079 = 1 / (20.18e-3); // [(m/s^2)/V] DC加速度センサ 20.18 [mV/(m/s^2)]:Model 3711B1110G, SERIAL LW8079
  // ループカウントは関数が呼ばれる度に増える
  // 割り込み毎に何回呼ばれているか確認すること, 設定した五万回に特に意味はない.
  if (sense->offset_count < 50000)
  {
    sense->offset_count = sense->offset_count + 1;
    while (1)
    {
      ad1 = PEV_ad_in_st(BDN);
      if (PEV_ad_in_st(BDN) == 0)
        break; /// ADC動作状態のポーリング
    }

    PEV_ad_in_grp(BDN, Vadc); /// ADC入力電圧値の取得

    sense->Vdc_sum += VtoVdc * Vadc[3]; /// 直流リンク電圧の取得

    sense->Iu_sum += VtoI * Vadc[0]; /// U相電流応答の取得
    if (BDN0 == BDN)
    {
      sense->WSXf_sum += VtoMM_IL600 * Vadc[7]; // レーザ変位計の値取得(作業空間X軸)
      sense->WSZf_sum += VtoMM_IL600 * Vadc[1]; // レーザ変位計の値取得(作業空間Z軸)
      sense->Idc_sum += VtoIdc * Vadc[1];       // 直流リンク電流の取得
    }
    if (BDN1 == BDN)
    {
      sense->Iw_sum -= VtoI * Vadc[2];              /// W相電流応答の取得
      sense->Idc_sum += VtoIdc * Vadc[6];           // 2軸目インバータのIdcを観測する
      sense->LW8174_sum += VtoACC_LW8174 * Vadc[7]; /// AC加速度センサCH2の取得
    }
    else
    {
      sense->WSYf_sum += VtoMM_IL600 * Vadc[6]; // レーザ変位計の値取得(作業空間X軸)
      sense->Iw_sum += VtoI * Vadc[2];          /// W相電流応答の取得
    }
    if (BDN2 == BDN)
    {
      sense->LW8079_sum += VtoACC_LW8079 * Vadc[1]; /// AC加速度センサCH1の取得
    }
  }
  sense->offset[0] = sense->Iu_sum / sense->offset_count;
  sense->offset[1] = sense->Iv_sum / sense->offset_count;
  sense->offset[2] = sense->Iw_sum / sense->offset_count;
  sense->offset[3] = sense->Vdc_sum / sense->offset_count;
  sense->offset[4] = sense->Idc_sum / sense->offset_count;
  sense->WSXf_ofst = 600.0;
  sense->WSZf_ofst = 600.0;
  sense->WSYf_ofst = 600.0;
  sense->LW8079_ofst = sense->LW8079_sum / sense->offset_count;
  sense->LW8174_ofst = sense->LW8174_sum / sense->offset_count;
}

/** @brief アナログポートからの取得する電圧・電流等の情報取得
    - 依存関係 CalcOffset()
 @param[in]	Robot.BDN	PVEボード番号
 @param[in]	Sensor.VtoI	換算ゲイン
 @param[in] Sensor.VtoVdc 換算ゲイン
 @param[out] Robot.IresU, Robot.IresV, Robot.IresW	[A] 電流応答値
*/
void GetVoltAndCurrent(Robot *robo, Sensor *sense)
{
  /// float *Vdc, float *Iu, float *Iv, float *Iw
  ///  各部電圧電流を取得する関数
  ///  Vadc対応(CH0 = iu, CH1 = iv, CH2 = iw, CH3 = Vdc, CH4 = Vvw, CH5 = Vvu, CH6=taus, CH7 = NC)
  int BDN = robo->BDN;
  float VtoI = sense->VtoI;
  float VtoVdc = sense->VtoVdc;
  float VtoIdc = sense->VtoIdc;
  const float VtoMM_IL600 = 80.0; // [mm/V] レーザ変位計IL-600
  // const float VtoMM_IL100 = 4.0;		// [mm/V] レーザ変位計IL-100
  const float VtoACC_LW8174 = 1 / (20.30e-3); // [(m/s^2)/V] DC加速度センサ 20.30 [mV/(m/s^2)]:Model 3711B1110G, SERIAL LW8174
  const float VtoACC_LW8079 = 1 / (20.18e-3); // [(m/s^2)/V] DC加速度センサ 20.18 [mV/(m/s^2)]:Model 3711B1110G, SERIAL LW8079

  CalcOffset(BDN, sense);

  // WAVE_ofst_Iu = sense->offset[0];
  // WAVE_ofst_Iv = sense->offset[1];
  // WAVE_ofst_Iw = sense->offset[2];
  // WAVE_Vdc_ofst = sense->offset[3];

  float Vadc[8] = {0};          //!< [V]   ADC電圧入力値
  float Iu_buf, Iv_buf, Iw_buf; //!< [A]   UVW相電流応答値
  // A/D変換が完了するまで待機する
  while (1)
  {
    ad1 = PEV_ad_in_st(BDN);
    if (PEV_ad_in_st(BDN) == 0)
    {
      break;
    } //!< ADC動作状態のポーリング
  }
  PEV_ad_in_grp(BDN, Vadc); //!< ADC入力電圧値の取得

  Iu_buf = VtoI * Vadc[0] - sense->offset[0]; //!< U相電流応答の取得
  if (BDN0 == BDN)
  {
    WAVE_VWX = Vadc[7];
    WAVE_VWZ = Vadc[1];
    WAVE_WSX = (VtoMM_IL600 * Vadc[7] + sense->WSXf_ofst); // レーザ変位計の値取得(作業空間X軸)
    WAVE_WSZ = (VtoMM_IL600 * Vadc[1] + sense->WSZf_ofst); // レーザ変位計の値取得(作業空間Z軸)
    robo->Idc = VtoIdc * Vadc[6] - sense->offset[4];       // 直流リンク電流の取得
  }
  if (BDN1 == BDN)
  {
    Iw_buf = -VtoI * Vadc[2] - sense->offset[2];                    //!< W相電流応答の取得
    robo->Idc = VtoIdc * Vadc[6] - sense->offset[4];                // 直流リンク電流の取得
    WAVE_ACC_LW8174 = VtoACC_LW8174 * Vadc[7] - sense->LW8174_ofst; // 加速度センサ
  }
  else
  {
    Iw_buf = VtoI * Vadc[2] - sense->offset[2]; //!< W相電流応答の取得
  }
  if (BDN2 == BDN)
  {
    WAVE_ACC_LW8079 = VtoACC_LW8079 * Vadc[1] - sense->LW8079_ofst; // 加速度センサ
    WAVE_VWY = Vadc[6];
    WAVE_WSY = (VtoMM_IL600 * Vadc[6] + sense->WSYf_ofst); // レーザ変位計の値取得(作業空間Z軸)
  }
  Iv_buf = -Iu_buf - Iw_buf; //!< (電流センサ2個のためV相は三相平衡時のUW相からの差分とする。)

  robo->Vdc = VtoVdc * Vadc[3] - sense->offset[3]; // 直流リンク電圧の取得
  robo->IresU = Iu_buf;                            //!< [A] U相電流応答値を返す
  robo->IresV = Iv_buf;                            //!< [A] V相電流応答値を返す
  robo->IresW = Iw_buf;                            //!< [A] W相電流応答値を返す
}

float Pcontroller(float u, const float Kp)
{
  /// u；入力信号
  return u * Kp;
}

/** @brief PIコントローラ
 * @param[in]		u	入力
 * @param[in]		Kp	比例ゲイン
 * @param[in]		Ki	積分ゲイン
 * @param[in]		Ts	サンプリング周期
 * @param[in,out] uZ1, yZ1 前回の入力, 出力値(積分器)
 *
 * @return y	PI制御器の計算結果
 * @exception	none
 */
float PIcontroller(float u, const float Kp, const float Ki, const float Ts, volatile float *uZ1, volatile float *yZ1)
{
  // 出力信号の取得 u；入力信号, rl:リミット偏差FB補償
  float y;
  float _uZ1 = *uZ1;
  float _yZ1 = *yZ1;
  y = (Kp + Ts * Ki) * u - Kp * _uZ1 + _yZ1; //!< PI制御器の式
  *yZ1 = y;
  *uZ1 = u;
  return y;
}
float VconPI5Axis(float u, const float Kp, const float Ki)
{
  float y;
  static float _uZ1 = 0.0;
  static float _yZ1 = 0.0;
  y = (Kp + Ts * Ki) * u - Kp * _uZ1 + _yZ1; //!< PI制御器の式
  _yZ1 = y;
  _uZ1 = u;
  return y;
}
/** @brief リミット偏差計算
 * @param[out]		Robot.Vlim_diffD, Robot.Vlim_diffQ	リミットに引っかかった前後の差
 * @return y	none
 * @exception	none
 */
void LimDiffCalcDQ(Robot *robo)
{
  float vu_ref_lim_dif = 0.0, vv_ref_lim_dif = 0.0, vw_ref_lim_dif = 0.0; /// リミット偏差フィードバック用電圧指令リミット前後の差
  float va_ref_lim_dif = 0.0, vb_ref_lim_dif = 0.0;
  float vd_ref_lim_dif = 0.0, vq_ref_lim_dif = 0.0;

  vu_ref_lim_dif = robo->VrefU - (robo->Vu_std) * ((robo->Vdc) / 2.0); /// リミット前後の差	規格化された指令値を電圧指令に戻して差を取る
  vv_ref_lim_dif = robo->VrefV - (robo->Vv_std) * ((robo->Vdc) / 2.0);
  vw_ref_lim_dif = robo->VrefW - (robo->Vw_std) * ((robo->Vdc) / 2.0);

  uvw2ab(vu_ref_lim_dif, vv_ref_lim_dif, vw_ref_lim_dif, &va_ref_lim_dif, &vb_ref_lim_dif);
  ab2dq(va_ref_lim_dif, vb_ref_lim_dif, robo->theta_re, &vd_ref_lim_dif, &vq_ref_lim_dif);

  robo->Vlim_diffD = vd_ref_lim_dif; //!< d座標でみたリミット前後の差
  robo->Vlim_diffQ = vq_ref_lim_dif; //!< q座標でみたリミット前後の差
}
/** @brief リミット偏差フィードバックPIコントローラ
 * - 依存 LimDiffCalcDQ
 * @param[in]		u	  入力
 * @param[in]		rl	リミット偏差
 * @param[in]		Kp	比例ゲイン
 * @param[in]		Ki	積分ゲイン
 * @param[in]		Ts	サンプリング周期
 * @param[in,out] uZ1, yZ1 前回の入力, 出力値(積分器)
 *
 * @return y	PI制御器の計算結果
 * @exception	none
 */
float PIcontroller_withAntiwindup(float u, float rl, const float Kp, const float Ki, const float Ts, volatile float *uZ1, volatile float *yZ1)
{
  /// 出力信号の取得 u；入力信号, rl:リミット偏差FB補償
  float y;
  float _uZ1 = *uZ1;
  float _yZ1 = *yZ1;
  y = Kp * u + Ts * Ki * (u - rl) - Kp * _uZ1 + _yZ1;
  *yZ1 = y;
  *uZ1 = u;
  return y;
}

/** @brief リミッタ
 * @param[in]		input	入力
 * @param[in]		limit	リミット
 *
 * @return input	リミット後の入力
 * @exception	none
 */
float Limiter(float input, float limit)
{

  if (limit < input)
    input = limit; // 任意の数値で入力を制限して出力
  if (input < -limit)
    input = -limit;
  return input;
}
/** @brief dq軸非干渉化制御
 * @param[in]		VrefQ	q軸電圧指令
 * @param[in]		VrefD	d軸電圧指令
 * @param[in]		IresD	d軸電流応答
 * @param[in]		IresQ	q軸電流応答
 * @param[in]		omega_re 電機角速度
 * @param[in]		Lq		q軸インダクタンス
 * @param[in]		Ld		d軸インダクタンス
 * @param[out]	VrefD_dcpl	非干渉化後d軸電圧指令
 * @param[out]	VrefQ_dcpl	非干渉化後q軸電圧指令
 * @param[in]		Phifa	鎖交磁束数
 *
 * @exception	none
 */
void DecouplingControl(Robot *robo)
{
  // 非干渉制御
  robo->VrefD_dcpl = robo->VrefD - robo->omega_re * robo->Lq * robo->IresQ;
  robo->VrefQ_dcpl = robo->VrefQ + robo->omega_re * (robo->Phifa + robo->Ld * robo->IresD);
}
/// 状態オブザーバ
void StateObserver(float Iref, float wM, volatile float *est_wM, volatile float *est_Qs, volatile float *est_wL, int BDN)
{
  // 状態オブザーバ(ゼロ次ホールド離散化)
  // 各状態量の推定(二慣性系モデル) Iref; [A] 電流指令値, wM; [rad/s] 速度応答値
  // 以下はサンプルプログラムである。モデルごとに作成し直すこと
  // 作成条件：p=-150 [rad/s] 、Ts=200[us]、

  // 1軸目SOB　初期姿勢：2軸目10deg,3軸目60deg
  // // A行列
  // const double a1_11 = 9.1460e-01;
  // const double a1_12 = -3.6622e+02;
  // const double a1_13 = 3.6593e-02;
  // const double a1_21 = 5.3870e-06;
  // const double a1_22 = 9.9955e-01;
  // const double a1_23 = -1.9971e-04;
  // const double a1_31 = 1.5539e-04;
  // const double a1_32 = 1.8700e+00;
  // const double a1_33 = 9.9719e-01;
  // // B行列
  // const double b1_11 = 1.5688e-01;
  // const double b1_12 = 8.5141e-02;
  // const double b1_21 = 1.1186e-07;
  // const double b1_22 = -3.9612e-06;
  // const double b1_31 = 6.9782e-08;
  // const double b1_32 = -1.5406e-04;

  // 1軸目SOB　初期姿勢：2軸目90deg,3軸目-75deg
  // A行列
  const double a1_11 = 9.1228e-01;
  const double a1_12 = -3.6624e+02;
  const double a1_13 = 3.6619e-02;
  const double a1_21 = 6.6759e-06;
  const double a1_22 = 9.9970e-01;
  const double a1_23 = -1.9992e-04;
  const double a1_31 = -2.3138e-04;
  const double a1_32 = 4.2219e-01;
  const double a1_33 = 9.9936e-01;
  // B行列
  const double b1_11 = 1.5688e-01;
  const double b1_12 = 8.7464e-02;
  const double b1_21 = 1.1186e-07;
  const double b1_22 = -5.2501e-06;
  const double b1_31 = 1.5747e-08;
  const double b1_32 = 2.3168e-04;

  // 2軸目SOB　
  // 初期姿勢：2軸目0.0deg,3軸目0.0deg JL = 23.9
  const double a2_11 = 9.1330e-01;
  const double a2_12 = -3.3086e+02;
  const double a2_13 = 3.3071e-02;
  const double a2_21 = 6.9233e-06;
  const double a2_22 = 9.9965e-01;
  const double a2_23 = -1.9982e-04;
  const double a2_31 = -1.3375e-04;
  const double a2_32 = 7.7399e-01;
  const double a2_33 = 9.9839e-01;
  // B行列
  const double b2_11 = 1.2688e-01;
  const double b2_12 = 8.6428e-02;
  const double b2_21 = 1.0486e-07;
  const double b2_22 = -5.2706e-06;
  const double b2_31 = 2.7068e-08;
  const double b2_32 = 1.3439e-04;
  /*
  // 初期姿勢：2軸目72deg,3軸目-72deg JL = 24.30
  // A行列
  const double a2_11 = 9.1284e-01;
  const double a2_12 = -3.3087e+02;
  const double a2_13 = 3.3076e-02;
  const double a2_21 = 7.1633e-06;
  const double a2_22 = 9.9967e-01;
  const double a2_23 = -1.9987e-04;
  const double a2_31 = -2.0167e-04;
  const double a2_32 = 5.6260e-01;
  const double a2_33 = 9.9883e-01;
  // B行列
  const double b2_11 = 1.2688e-01;
  const double b2_12 = 8.6889e-02;
  const double b2_21 = 1.0486e-07;
  const double b2_22 = -5.5106e-06;
  const double b2_31 = 1.9674e-08;
  const double b2_32 = 2.0214e-04;
  // 初期姿勢：2軸目10deg,3軸目60deg
  // A行列
  const double a2_11 = 9.1523e-01;
  const double a2_12 = -3.3085e+02;
  const double a2_13 = 3.3052e-02;
  const double a2_21 = 5.9320e-06;
  const double a2_22 = 9.9956e-01;
  const double a2_23 = -1.9964e-04;
  const double a2_31 = 1.3344e-04;
  const double a2_32 = 1.6577e+00;
  const double a2_33 = 9.9655e-01;
  // B行列
  const double b2_11 = 1.2688e-01;
  const double b2_12 = 8.4501e-02;
  const double b2_21 = 1.0486e-07;
  const double b2_22 = -4.2794e-06;
  const double b2_31 = 5.8002e-08;
  const double b2_32 = -1.3207e-04;
  */

  // 3軸目SOB　
  // A行列
  const double a3_11 = 9.1366e-01;
  const double a3_12 = -1.1761e+02;
  const double a3_13 = 1.1753e-02;
  const double a3_21 = 1.9806e-05;
  const double a3_22 = 9.9986e-01;
  const double a3_23 = -1.9978e-04;
  const double a3_31 = -5.7786e-04;
  const double a3_32 = 4.1917e-01;
  const double a3_33 = 9.9782e-01;
  // B行列
  const double b3_11 = 2.0511e-01;
  const double b3_12 = 8.6247e-02;
  const double b3_21 = 1.6951e-07;
  const double b3_22 = -1.8153e-05;
  const double b3_31 = 2.3699e-08;
  const double b3_32 = 5.7821e-04;

  // 状態変数の定義
  static float est_wM_Z1[3] = {0}, est_Qs_Z1[3] = {0}, est_wL_Z1[3] = {0};
  static float est_wM_Z[3] = {0}, est_Qs_Z[3] = {0}, est_wL_Z[3] = {0};

  if (BDN == BDN0)
  {
    // 状態オブザーバの離散方程式
    est_wM_Z[0] = a1_11 * est_wM_Z1[0] + a1_12 * est_Qs_Z1[0] + a1_13 * est_wL_Z1[0] + b1_11 * Iref + b1_12 * wM;
    est_Qs_Z[0] = a1_21 * est_wM_Z1[0] + a1_22 * est_Qs_Z1[0] + a1_23 * est_wL_Z1[0] + b1_21 * Iref + b1_22 * wM;
    est_wL_Z[0] = a1_31 * est_wM_Z1[0] + a1_32 * est_Qs_Z1[0] + a1_33 * est_wL_Z1[0] + b1_31 * Iref + b1_32 * wM;

    // 状態量の更新
    est_wM_Z1[0] = est_wM_Z[0];
    est_Qs_Z1[0] = est_Qs_Z[0];
    est_wL_Z1[0] = est_wL_Z[0];

    // 状態量の出力
    *est_wM = est_wM_Z[0];
    *est_Qs = est_Qs_Z[0];
    *est_wL = est_wL_Z[0];
  }
  if (BDN == BDN1)
  {
    // 状態オブザーバの離散方程式
    est_wM_Z[1] = a2_11 * est_wM_Z1[1] + a2_12 * est_Qs_Z1[1] + a2_13 * est_wL_Z1[1] + b2_11 * Iref + b2_12 * wM;
    est_Qs_Z[1] = a2_21 * est_wM_Z1[1] + a2_22 * est_Qs_Z1[1] + a2_23 * est_wL_Z1[1] + b2_21 * Iref + b2_22 * wM;
    est_wL_Z[1] = a2_31 * est_wM_Z1[1] + a2_32 * est_Qs_Z1[1] + a2_33 * est_wL_Z1[1] + b2_31 * Iref + b2_32 * wM;

    // 状態量の更新
    est_wM_Z1[1] = est_wM_Z[1];
    est_Qs_Z1[1] = est_Qs_Z[1];
    est_wL_Z1[1] = est_wL_Z[1];

    // 状態量の出力
    *est_wM = est_wM_Z[1];
    *est_Qs = est_Qs_Z[1];
    *est_wL = est_wL_Z[1];
  }
  if (BDN == BDN2)
  {
    // 状態オブザーバの離散方程式
    est_wM_Z[2] = a3_11 * est_wM_Z1[2] + a3_12 * est_Qs_Z1[2] + a3_13 * est_wL_Z1[2] + b3_11 * Iref + b3_12 * wM;
    est_Qs_Z[2] = a3_21 * est_wM_Z1[2] + a3_22 * est_Qs_Z1[2] + a3_23 * est_wL_Z1[2] + b3_21 * Iref + b3_22 * wM;
    est_wL_Z[2] = a3_31 * est_wM_Z1[2] + a3_32 * est_Qs_Z1[2] + a3_33 * est_wL_Z1[2] + b3_31 * Iref + b3_32 * wM;

    // 状態量の更新
    est_wM_Z1[2] = est_wM_Z[2];
    est_Qs_Z1[2] = est_Qs_Z[2];
    est_wL_Z1[2] = est_wL_Z[2];

    // 状態量の出力
    *est_wM = est_wM_Z[2];
    *est_Qs = est_Qs_Z[2];
    *est_wL = est_wL_Z[2];
  }
}

void FDTD_T_SOB(Robot *robo)
{
  // 1軸目 AB行列
  float a1_11 = 0.0;
  float a1_12 = 0.0;
  float a1_13 = 0.0;
  float a1_21 = 0.0;
  float a1_22 = 0.0;
  float a1_23 = 0.0;
  float a1_31 = 0.0;
  float a1_32 = 0.0;
  float a1_33 = 0.0;
  float b1iq1 = 0.0;
  float b1iq2 = 0.0;
  float b1iq3 = 0.0;
  float b1tl1 = 0.0;
  float b1tl2 = 0.0;
  float b1tl3 = 0.0;
  float b1wm1 = 0.0;
  float b1wm2 = 0.0;
  float b1wm3 = 0.0;
  // 1軸目 オブザーバゲイン
  float k1_1 = 0.0;
  float k1_2 = 0.0;
  float k1_3 = 0.0;
  // 2軸目 AB行列
  float a2_11 = 0.0;
  float a2_12 = 0.0;
  float a2_13 = 0.0;
  float a2_21 = 0.0;
  float a2_22 = 0.0;
  float a2_23 = 0.0;
  float a2_31 = 0.0;
  float a2_32 = 0.0;
  float a2_33 = 0.0;
  float b2iq1 = 0.0;
  float b2iq2 = 0.0;
  float b2iq3 = 0.0;
  float b2tl1 = 0.0;
  float b2tl2 = 0.0;
  float b2tl3 = 0.0;
  float b2wm1 = 0.0;
  float b2wm2 = 0.0;
  float b2wm3 = 0.0;
  // 2軸目 オブザーバゲイン
  float k2_1 = 0.0;
  float k2_2 = 0.0;
  float k2_3 = 0.0;
  // 3軸目 AB行列
  float a3_11 = 0.0;
  float a3_12 = 0.0;
  float a3_13 = 0.0;
  float a3_21 = 0.0;
  float a3_22 = 0.0;
  float a3_23 = 0.0;
  float a3_31 = 0.0;
  float a3_32 = 0.0;
  float a3_33 = 0.0;
  float b3iq1 = 0.0;
  float b3iq2 = 0.0;
  float b3iq3 = 0.0;
  float b3tl1 = 0.0;
  float b3tl2 = 0.0;
  float b3tl3 = 0.0;
  float b3wm1 = 0.0;
  float b3wm2 = 0.0;
  float b3wm3 = 0.0;
  // 3軸目 オブザーバゲイン
  float k3_1 = 0.0;
  float k3_2 = 0.0;
  float k3_3 = 0.0;

  // 状態変数の定義
  static float wm_Z[3] = {0}, qs_Z[3] = {0}, wl_Z[3] = {0};
  static float wm_Z1[3] = {0}, qs_Z1[3] = {0}, wl_Z1[3] = {0};

  if (robo->BDN == BDN0)
  {
    // 1軸目 オブザーバゲイン計算
    k1_1 = ob_sub[0].k1m1 / axis1.Jl_calc + ob_sub[0].k1z0;
    k1_2 = ob_sub[0].k2m2 / (axis1.Jl_calc * axis1.Jl_calc) + ob_sub[0].k2m1 / axis1.Jl_calc + ob_sub[0].k2z0;
    k1_3 = (ob_sub[0].k3n3 * (axis1.Jl_calc * axis1.Jl_calc * axis1.Jl_calc) + ob_sub[0].k3n2 * (axis1.Jl_calc * axis1.Jl_calc) + ob_sub[0].k3n1 * axis1.Jl_calc + ob_sub[0].k3n0) / (ob_sub[0].k3d3 * (axis1.Jl_calc * axis1.Jl_calc * axis1.Jl_calc) + ob_sub[0].k3d2 * (axis1.Jl_calc * axis1.Jl_calc));
    // 1軸目 AB行列 計算
    a1_11 = ob_sub[0].a11cf - k1_1;
    a1_12 = ob_sub[0].a12cf;
    a1_13 = ob_sub[0].a13cf;
    a1_21 = ob_sub[0].a21cf - k1_2;
    a1_22 = ob_sub[0].a22cf1 + ob_sub[0].a22cf2 / axis1.Jl_calc;
    a1_23 = ob_sub[0].a23cf1 + ob_sub[0].a23cf2 / axis1.Jl_calc;
    a1_31 = ob_sub[0].a31cf - k1_3;
    a1_32 = ob_sub[0].a32cf / axis1.Jl_calc;
    a1_33 = ob_sub[0].a33cf1 + ob_sub[0].a33cf2 / axis1.Jl_calc;
    b1iq1 = ob_sub[0].biq1cf;
    b1iq2 = ob_sub[0].biq2cf;
    b1iq3 = ob_sub[0].biq3cf;
    b1tl1 = ob_sub[0].btl1cf;
    b1tl2 = ob_sub[0].btl2cf / axis1.Jl_calc;
    b1tl3 = ob_sub[0].btl3cf / axis1.Jl_calc;
    b1wm1 = k1_1;
    b1wm2 = k1_2;
    b1wm3 = k1_3;

    // 状態オブザーバの離散方程式(TSOB)
    // wm_Z[0] = a1_11*wm_Z1[0] + a1_12*qs_Z1[0] + a1_13*wl_Z1[0] + b1iq1*robo->IrefQ + b1tl1*robo->tauLdyn + b1wm1*robo->wm;
    // qs_Z[0] = a1_21*wm_Z1[0] + a1_22*qs_Z1[0] + a1_23*wl_Z1[0] + b1iq2*robo->IrefQ + b1tl2*robo->tauLdyn + b1wm2*robo->wm;
    // wl_Z[0] = a1_31*wm_Z1[0] + a1_32*qs_Z1[0] + a1_33*wl_Z1[0] + b1iq3*robo->IrefQ + b1tl3*robo->tauLdyn + b1wm3*robo->wm;
    wm_Z[0] = a1_11 * wm_Z1[0] + a1_12 * qs_Z1[0] + a1_13 * wl_Z1[0] + b1iq1 * robo->I_SOBinput + b1tl1 * robo->tauLdyn_z2 + b1wm1 * robo->wm;
    qs_Z[0] = a1_21 * wm_Z1[0] + a1_22 * qs_Z1[0] + a1_23 * wl_Z1[0] + b1iq2 * robo->I_SOBinput + b1tl2 * robo->tauLdyn_z2 + b1wm2 * robo->wm;
    wl_Z[0] = a1_31 * wm_Z1[0] + a1_32 * qs_Z1[0] + a1_33 * wl_Z1[0] + b1iq3 * robo->I_SOBinput + b1tl3 * robo->tauLdyn_z2 + b1wm3 * robo->wm;

    // 状態量の更新
    wm_Z1[0] = wm_Z[0];
    qs_Z1[0] = qs_Z[0];
    wl_Z1[0] = wl_Z[0];

    // 状態量の出力
    robo->est_prop_wm = wm_Z[0];
    robo->est_prop_qs = qs_Z[0];
    robo->est_prop_wl = wl_Z[0];
  }
  else if (robo->BDN == BDN1)
  {
    // 2軸目 オブザーバゲイン計算
    k2_1 = ob_sub[1].k1m1 / axis2.Jl_calc + ob_sub[1].k1z0;
    k2_2 = ob_sub[1].k2m2 / (axis2.Jl_calc * axis2.Jl_calc) + ob_sub[1].k2m1 / axis2.Jl_calc + ob_sub[1].k2z0;
    k2_3 = (ob_sub[1].k3n3 * (axis2.Jl_calc * axis2.Jl_calc * axis2.Jl_calc) + ob_sub[1].k3n2 * (axis2.Jl_calc * axis2.Jl_calc) + ob_sub[1].k3n1 * axis2.Jl_calc + ob_sub[1].k3n0) / (ob_sub[1].k3d3 * (axis2.Jl_calc * axis2.Jl_calc * axis2.Jl_calc) + ob_sub[1].k3d2 * (axis2.Jl_calc * axis2.Jl_calc));
    // 2軸目 AB行列 計算
    a2_11 = ob_sub[1].a11cf - k2_1;
    a2_12 = ob_sub[1].a12cf;
    a2_13 = ob_sub[1].a13cf;
    a2_21 = ob_sub[1].a21cf - k2_2;
    a2_22 = ob_sub[1].a22cf1 + ob_sub[1].a22cf2 / axis2.Jl_calc;
    a2_23 = ob_sub[1].a23cf1 + ob_sub[1].a23cf2 / axis2.Jl_calc;
    a2_31 = ob_sub[1].a31cf - k2_3;
    a2_32 = ob_sub[1].a32cf / axis2.Jl_calc;
    a2_33 = ob_sub[1].a33cf1 + ob_sub[1].a33cf2 / axis2.Jl_calc;
    b2iq1 = ob_sub[1].biq1cf;
    b2iq2 = ob_sub[1].biq2cf;
    b2iq3 = ob_sub[1].biq3cf;
    b2tl1 = ob_sub[1].btl1cf;
    b2tl2 = ob_sub[1].btl2cf / axis2.Jl_calc;
    b2tl3 = ob_sub[1].btl3cf / axis2.Jl_calc;
    b2wm1 = k2_1;
    b2wm2 = k2_2;
    b2wm3 = k2_3;

    // 状態オブザーバの離散方程式(TSOB)
    // wm_Z[1] = a2_11*wm_Z1[1] + a2_12*qs_Z1[1] + a2_13*wl_Z1[1] + b2iq1*robo->IrefQ + b2tl1*robo->tauLdyn + b2wm1*robo->wm;
    // qs_Z[1] = a2_21*wm_Z1[1] + a2_22*qs_Z1[1] + a2_23*wl_Z1[1] + b2iq2*robo->IrefQ + b2tl2*robo->tauLdyn + b2wm2*robo->wm;
    // wl_Z[1] = a2_31*wm_Z1[1] + a2_32*qs_Z1[1] + a2_33*wl_Z1[1] + b2iq3*robo->IrefQ + b2tl3*robo->tauLdyn + b2wm3*robo->wm;
    wm_Z[1] = a2_11 * wm_Z1[1] + a2_12 * qs_Z1[1] + a2_13 * wl_Z1[1] + b2iq1 * robo->I_SOBinput + b2tl1 * robo->tauLdyn_z2 + b2wm1 * robo->wm;
    qs_Z[1] = a2_21 * wm_Z1[1] + a2_22 * qs_Z1[1] + a2_23 * wl_Z1[1] + b2iq2 * robo->I_SOBinput + b2tl2 * robo->tauLdyn_z2 + b2wm2 * robo->wm;
    wl_Z[1] = a2_31 * wm_Z1[1] + a2_32 * qs_Z1[1] + a2_33 * wl_Z1[1] + b2iq3 * robo->I_SOBinput + b2tl3 * robo->tauLdyn_z2 + b2wm3 * robo->wm;

    // 状態量の更新
    wm_Z1[1] = wm_Z[1];
    qs_Z1[1] = qs_Z[1];
    wl_Z1[1] = wl_Z[1];

    // 状態量の出力
    robo->est_prop_wm = wm_Z[1];
    robo->est_prop_qs = qs_Z[1];
    robo->est_prop_wl = wl_Z[1];
  }
  else if (robo->BDN == BDN2)
  {
    // 3軸目 オブザーバゲイン計算
    k3_1 = ob_sub[2].k1m1 / axis3.Jl_calc + ob_sub[2].k1z0;
    k3_2 = ob_sub[2].k2m2 / powf(axis3.Jl_calc, 2) + ob_sub[2].k2m1 / axis3.Jl_calc + ob_sub[2].k2z0;
    k3_3 = (ob_sub[2].k3n3 * powf(axis3.Jl_calc, 3) + ob_sub[2].k3n2 * powf(axis3.Jl_calc, 2) + ob_sub[2].k3n1 * axis3.Jl_calc + ob_sub[2].k3n0) / (ob_sub[2].k3d3 * powf(axis3.Jl_calc, 3) + ob_sub[2].k3d2 * powf(axis3.Jl_calc, 2));
    // 3軸目 AB行列 計算
    a3_11 = ob_sub[2].a11cf - k3_1;
    a3_12 = ob_sub[2].a12cf;
    a3_13 = ob_sub[2].a13cf;
    a3_21 = ob_sub[2].a21cf - k3_2;
    a3_22 = ob_sub[2].a22cf1 + ob_sub[2].a22cf2 / axis3.Jl_calc;
    a3_23 = ob_sub[2].a23cf1 + ob_sub[2].a23cf2 / axis3.Jl_calc;
    a3_31 = ob_sub[2].a31cf - k3_3;
    a3_32 = ob_sub[2].a32cf / axis3.Jl_calc;
    a3_33 = ob_sub[2].a33cf1 + ob_sub[2].a33cf2 / axis3.Jl_calc;
    b3iq1 = ob_sub[2].biq1cf;
    b3iq2 = ob_sub[2].biq2cf;
    b3iq3 = ob_sub[2].biq3cf;
    b3tl1 = ob_sub[2].btl1cf;
    b3tl2 = ob_sub[2].btl2cf / axis3.Jl_calc;
    b3tl3 = ob_sub[2].btl3cf / axis3.Jl_calc;
    b3wm1 = k3_1;
    b3wm2 = k3_2;
    b3wm3 = k3_3;

    // 状態オブザーバの離散方程式(TSOB)
    // wm_Z[2] = a3_11*wm_Z1[2] + a3_12*qs_Z1[2] + a3_13*wl_Z1[2] + b3iq1*robo->IrefQ + b3tl1*robo->tauLdyn + b3wm1*robo->wm;
    // qs_Z[2] = a3_21*wm_Z1[2] + a3_22*qs_Z1[2] + a3_23*wl_Z1[2] + b3iq2*robo->IrefQ + b3tl2*robo->tauLdyn + b3wm2*robo->wm;
    // wl_Z[2] = a3_31*wm_Z1[2] + a3_32*qs_Z1[2] + a3_33*wl_Z1[2] + b3iq3*robo->IrefQ + b3tl3*robo->tauLdyn + b3wm3*robo->wm;
    wm_Z[2] = a3_11 * wm_Z1[2] + a3_12 * qs_Z1[2] + a3_13 * wl_Z1[2] + b3iq1 * robo->I_SOBinput + b3tl1 * robo->tauLdyn_z2 + b3wm1 * robo->wm;
    qs_Z[2] = a3_21 * wm_Z1[2] + a3_22 * qs_Z1[2] + a3_23 * wl_Z1[2] + b3iq2 * robo->I_SOBinput + b3tl2 * robo->tauLdyn_z2 + b3wm2 * robo->wm;
    wl_Z[2] = a3_31 * wm_Z1[2] + a3_32 * qs_Z1[2] + a3_33 * wl_Z1[2] + b3iq3 * robo->I_SOBinput + b3tl3 * robo->tauLdyn_z2 + b3wm3 * robo->wm;

    // 状態量の更新
    wm_Z1[2] = wm_Z[2];
    qs_Z1[2] = qs_Z[2];
    wl_Z1[2] = wl_Z[2];

    // 状態量の出力
    robo->est_prop_wm = wm_Z[2];
    robo->est_prop_qs = qs_Z[2];
    robo->est_prop_wl = wl_Z[2];
  }
  else
  {
    // ボード番号認識できない場合
  }
}

void CalcFDTDTSOBInit(void)
{
  // 指定極の離散化
  axis1.obpz = expf(axis1.obp * Tp);
  axis2.obpz = expf(axis2.obp * Tp);
  axis3.obpz = expf(axis3.obp * Tp);

  // Jlの係数(1つ目のゲイン)
  ob_sub[0].k1m1 = -Tp * (axis1.Ksn * Tp + axis1.Dln);
  ob_sub[1].k1m1 = -Tp * (axis2.Ksn * Tp + axis2.Dln);
  ob_sub[2].k1m1 = -Tp * (axis3.Ksn * Tp + axis3.Dln);
  ob_sub[0].k1z0 = (((-3.0 * axis1.obpz + 3.0) * axis1.Jmn - axis1.Dmn * Tp) * powf(axis1.Rgn, 2.0) - axis1.Ksn * powf(Tp, 2.0)) / axis1.Jmn / powf(axis1.Rgn, 2.0);
  ob_sub[1].k1z0 = (((-3.0 * axis2.obpz + 3.0) * axis2.Jmn - axis2.Dmn * Tp) * powf(axis2.Rgn, 2.0) - axis2.Ksn * powf(Tp, 2.0)) / axis2.Jmn / powf(axis2.Rgn, 2.0);
  ob_sub[2].k1z0 = (((-3.0 * axis3.obpz + 3.0) * axis3.Jmn - axis3.Dmn * Tp) * powf(axis3.Rgn, 2.0) - axis3.Ksn * powf(Tp, 2.0)) / axis3.Jmn / powf(axis3.Rgn, 2.0);

  // Jlの係数(2つ目のゲイン)
  ob_sub[0].k2m2 = -axis1.Jmn * axis1.Rgn * Tp * powf(axis1.Ksn * Tp + axis1.Dln, 2.0) / axis1.Ksn;
  ob_sub[1].k2m2 = -axis2.Jmn * axis2.Rgn * Tp * powf(axis2.Ksn * Tp + axis2.Dln, 2.0) / axis2.Ksn;
  ob_sub[2].k2m2 = -axis3.Jmn * axis3.Rgn * Tp * powf(axis3.Ksn * Tp + axis3.Dln, 2.0) / axis3.Ksn;
  ob_sub[0].k2m1 = (-2.0 * powf(axis1.Ksn, 2.0) * powf(Tp, 3.0) - (axis1.Jmn * (3.0 * axis1.obpz - 4.0) * powf(axis1.Rgn, 2.0) + axis1.Dln * Tp) * Tp * axis1.Ksn - 3.0 * axis1.Dln * axis1.Jmn * powf(axis1.Rgn, 2.0) * (axis1.obpz - 1.0)) / axis1.Rgn / axis1.Ksn;
  ob_sub[1].k2m1 = (-2.0 * powf(axis2.Ksn, 2.0) * powf(Tp, 3.0) - (axis2.Jmn * (3.0 * axis2.obpz - 4.0) * powf(axis2.Rgn, 2.0) + axis2.Dln * Tp) * Tp * axis2.Ksn - 3.0 * axis2.Dln * axis2.Jmn * powf(axis2.Rgn, 2.0) * (axis2.obpz - 1.0)) / axis2.Rgn / axis2.Ksn;
  ob_sub[2].k2m1 = (-2.0 * powf(axis3.Ksn, 2.0) * powf(Tp, 3.0) - (axis3.Jmn * (3.0 * axis3.obpz - 4.0) * powf(axis3.Rgn, 2.0) + axis3.Dln * Tp) * Tp * axis3.Ksn - 3.0 * axis3.Dln * axis3.Jmn * powf(axis3.Rgn, 2.0) * (axis3.obpz - 1.0)) / axis3.Rgn / axis3.Ksn;
  ob_sub[0].k2z0 = (-3.0 * powf(axis1.Jmn, 2.0) * powf(axis1.obpz - 1.0, 2.0) * powf(axis1.Rgn, 4.0) - (axis1.Jmn * (3.0 * axis1.obpz - 4.0) + axis1.Dmn * Tp) * powf(Tp, 2.0) * axis1.Ksn * powf(axis1.Rgn, 2.0) - powf(axis1.Ksn, 2.0) * powf(Tp, 4.0)) / axis1.Jmn / axis1.Ksn / powf(axis1.Rgn, 3.0) / Tp;
  ob_sub[1].k2z0 = (-3.0 * powf(axis2.Jmn, 2.0) * powf(axis2.obpz - 1.0, 2.0) * powf(axis2.Rgn, 4.0) - (axis2.Jmn * (3.0 * axis2.obpz - 4.0) + axis2.Dmn * Tp) * powf(Tp, 2.0) * axis2.Ksn * powf(axis2.Rgn, 2.0) - powf(axis2.Ksn, 2.0) * powf(Tp, 4.0)) / axis2.Jmn / axis2.Ksn / powf(axis2.Rgn, 3.0) / Tp;
  ob_sub[2].k2z0 = (-3.0 * powf(axis3.Jmn, 2.0) * powf(axis3.obpz - 1.0, 2.0) * powf(axis3.Rgn, 4.0) - (axis3.Jmn * (3.0 * axis3.obpz - 4.0) + axis3.Dmn * Tp) * powf(Tp, 2.0) * axis3.Ksn * powf(axis3.Rgn, 2.0) - powf(axis3.Ksn, 2.0) * powf(Tp, 4.0)) / axis3.Jmn / axis3.Ksn / powf(axis3.Rgn, 3.0) / Tp;

  // Jlの係数(3つ目のゲイン)
  ob_sub[0].k3n0 = axis1.Dln * axis1.Jmn * powf(axis1.Rgn, 2.0) * powf(Tp, 3.0) * powf(axis1.Ksn * Tp + axis1.Dln, 2.0);
  ob_sub[1].k3n0 = axis2.Dln * axis2.Jmn * powf(axis2.Rgn, 2.0) * powf(Tp, 3.0) * powf(axis2.Ksn * Tp + axis2.Dln, 2.0);
  ob_sub[2].k3n0 = axis3.Dln * axis3.Jmn * powf(axis3.Rgn, 2.0) * powf(Tp, 3.0) * powf(axis3.Ksn * Tp + axis3.Dln, 2.0);
  ob_sub[0].k3n1 = ((3.0 * axis1.Jmn * powf(axis1.Rgn, 2.0) * (axis1.obpz - 1.0) * powf(axis1.Dln, 2.0)) + (0.3e1 * (axis1.obpz - 0.5e1 / 0.3e1) * powf(axis1.Rgn, 2.0) * axis1.Jmn + axis1.Ksn * powf(Tp, 2.0)) * Tp * axis1.Ksn * axis1.Dln - powf(Tp, 2.0) * axis1.Jmn * powf(axis1.Ksn, 2.0) * powf(axis1.Rgn, 2.0)) * powf(Tp, 2.0);
  ob_sub[1].k3n1 = ((3.0 * axis2.Jmn * powf(axis2.Rgn, 2.0) * (axis2.obpz - 1.0) * powf(axis2.Dln, 2.0)) + (0.3e1 * (axis2.obpz - 0.5e1 / 0.3e1) * powf(axis2.Rgn, 2.0) * axis2.Jmn + axis2.Ksn * powf(Tp, 2.0)) * Tp * axis2.Ksn * axis2.Dln - powf(Tp, 2.0) * axis2.Jmn * powf(axis2.Ksn, 2.0) * powf(axis2.Rgn, 2.0)) * powf(Tp, 2.0);
  ob_sub[2].k3n1 = ((3.0 * axis3.Jmn * powf(axis3.Rgn, 2.0) * (axis3.obpz - 1.0) * powf(axis3.Dln, 2.0)) + (0.3e1 * (axis3.obpz - 0.5e1 / 0.3e1) * powf(axis3.Rgn, 2.0) * axis3.Jmn + axis3.Ksn * powf(Tp, 2.0)) * Tp * axis3.Ksn * axis3.Dln - powf(Tp, 2.0) * axis3.Jmn * powf(axis3.Ksn, 2.0) * powf(axis3.Rgn, 2.0)) * powf(Tp, 2.0);
  ob_sub[0].k3n2 = -(3.0 * (axis1.obpz - 1.0) * powf(axis1.Rgn, 2.0) * (axis1.Ksn * Tp - axis1.Dln * (axis1.obpz - 1.0)) * axis1.Jmn + powf(axis1.Ksn, 2.0) * powf(Tp, 3.0)) * Tp;
  ob_sub[1].k3n2 = -(3.0 * (axis2.obpz - 1.0) * powf(axis2.Rgn, 2.0) * (axis2.Ksn * Tp - axis2.Dln * (axis2.obpz - 1.0)) * axis2.Jmn + powf(axis2.Ksn, 2.0) * powf(Tp, 3.0)) * Tp;
  ob_sub[2].k3n2 = -(3.0 * (axis3.obpz - 1.0) * powf(axis3.Rgn, 2.0) * (axis3.Ksn * Tp - axis3.Dln * (axis3.obpz - 1.0)) * axis3.Jmn + powf(axis3.Ksn, 2.0) * powf(Tp, 3.0)) * Tp;
  ob_sub[0].k3n3 = powf(axis1.Rgn, 2.0) * axis1.Jmn * powf(axis1.obpz - 1.0, 3.0);
  ob_sub[1].k3n3 = powf(axis2.Rgn, 2.0) * axis2.Jmn * powf(axis2.obpz - 1.0, 3.0);
  ob_sub[2].k3n3 = powf(axis3.Rgn, 2.0) * axis3.Jmn * powf(axis3.obpz - 1.0, 3.0);
  ob_sub[0].k3d2 = axis1.Rgn * axis1.Ksn * powf(Tp, 3.0) * axis1.Dln;
  ob_sub[1].k3d2 = axis2.Rgn * axis2.Ksn * powf(Tp, 3.0) * axis2.Dln;
  ob_sub[2].k3d2 = axis3.Rgn * axis3.Ksn * powf(Tp, 3.0) * axis3.Dln;
  ob_sub[0].k3d3 = -axis1.Rgn * axis1.Ksn * powf(Tp, 2.0);
  ob_sub[1].k3d3 = -axis2.Rgn * axis2.Ksn * powf(Tp, 2.0);
  ob_sub[2].k3d3 = -axis3.Rgn * axis3.Ksn * powf(Tp, 2.0);

  // 2慣性系プラントA行列
  ob_sub[0].a11cf = 1.0 - axis1.Dmn * Tp / axis1.Jmn;
  ob_sub[1].a11cf = 1.0 - axis2.Dmn * Tp / axis2.Jmn;
  ob_sub[2].a11cf = 1.0 - axis3.Dmn * Tp / axis3.Jmn;
  ob_sub[0].a12cf = -axis1.Ksn * Tp / (axis1.Rgn * axis1.Jmn);
  ob_sub[1].a12cf = -axis2.Ksn * Tp / (axis2.Rgn * axis2.Jmn);
  ob_sub[2].a12cf = -axis3.Ksn * Tp / (axis3.Rgn * axis3.Jmn);
  ob_sub[0].a13cf = 0.0;
  ob_sub[1].a13cf = 0.0;
  ob_sub[2].a13cf = 0.0;
  ob_sub[0].a21cf = Tp / axis1.Rgn - axis1.Dmn * powf(Tp, 2.0) / (axis1.Rgn * axis1.Jmn);
  ob_sub[1].a21cf = Tp / axis2.Rgn - axis2.Dmn * powf(Tp, 2.0) / (axis2.Rgn * axis2.Jmn);
  ob_sub[2].a21cf = Tp / axis3.Rgn - axis3.Dmn * powf(Tp, 2.0) / (axis3.Rgn * axis3.Jmn);
  ob_sub[0].a22cf1 = -axis1.Ksn * powf(Tp, 2.0) / (powf(axis1.Rgn, 2.0) * axis1.Jmn) + 1.0;
  ob_sub[1].a22cf1 = -axis2.Ksn * powf(Tp, 2.0) / (powf(axis2.Rgn, 2.0) * axis2.Jmn) + 1.0;
  ob_sub[2].a22cf1 = -axis3.Ksn * powf(Tp, 2.0) / (powf(axis3.Rgn, 2.0) * axis3.Jmn) + 1.0;
  ob_sub[0].a22cf2 = -axis1.Ksn * powf(Tp, 2.0);
  ob_sub[1].a22cf2 = -axis2.Ksn * powf(Tp, 2.0);
  ob_sub[2].a22cf2 = -axis3.Ksn * powf(Tp, 2.0);
  ob_sub[0].a23cf1 = -Tp;
  ob_sub[1].a23cf1 = -Tp;
  ob_sub[2].a23cf1 = -Tp;
  ob_sub[0].a23cf2 = axis1.Dln * powf(Tp, 2.0);
  ob_sub[1].a23cf2 = axis2.Dln * powf(Tp, 2.0);
  ob_sub[2].a23cf2 = axis3.Dln * powf(Tp, 2.0);
  ob_sub[0].a31cf = 0.0;
  ob_sub[1].a31cf = 0.0;
  ob_sub[2].a31cf = 0.0;
  ob_sub[0].a32cf = axis1.Ksn * Tp;
  ob_sub[1].a32cf = axis2.Ksn * Tp;
  ob_sub[2].a32cf = axis3.Ksn * Tp;
  ob_sub[0].a33cf1 = 1.0;
  ob_sub[1].a33cf1 = 1.0;
  ob_sub[2].a33cf1 = 1.0;
  ob_sub[0].a33cf2 = -axis1.Dln * Tp;
  ob_sub[1].a33cf2 = -axis2.Dln * Tp;
  ob_sub[2].a33cf2 = -axis3.Dln * Tp;

  // 2慣性系プラントB行列(IrefQ入力)
  ob_sub[0].biq1cf = axis1.Ktn * Tp / axis1.Jmn;
  ob_sub[1].biq1cf = axis2.Ktn * Tp / axis2.Jmn;
  ob_sub[2].biq1cf = axis3.Ktn * Tp / axis3.Jmn;
  ob_sub[0].biq2cf = axis1.Ktn * powf(Tp, 2.0) / (axis1.Rgn * axis1.Jmn);
  ob_sub[1].biq2cf = axis2.Ktn * powf(Tp, 2.0) / (axis2.Rgn * axis2.Jmn);
  ob_sub[2].biq2cf = axis3.Ktn * powf(Tp, 2.0) / (axis3.Rgn * axis3.Jmn);
  ob_sub[0].biq3cf = 0.0;
  ob_sub[1].biq3cf = 0.0;
  ob_sub[2].biq3cf = 0.0;

  // 2慣性系プラントB行列(tauLdyn入力)
  ob_sub[0].btl1cf = 0.0;
  ob_sub[1].btl1cf = 0.0;
  ob_sub[2].btl1cf = 0.0;
  ob_sub[0].btl2cf = -powf(Tp, 2.0);
  ob_sub[1].btl2cf = -powf(Tp, 2.0);
  ob_sub[2].btl2cf = -powf(Tp, 2.0);
  ob_sub[0].btl3cf = -Tp;
  ob_sub[1].btl3cf = -Tp;
  ob_sub[2].btl3cf = -Tp;
}

// FDTDSOB
void FDTDSOB(Robot *robo)
{
  // 1軸目 AB行列
  float a1_11 = 0.0;
  float a1_12 = 0.0;
  float a1_13 = 0.0;
  float a1_21 = 0.0;
  float a1_22 = 0.0;
  float a1_23 = 0.0;
  float a1_31 = 0.0;
  float a1_32 = 0.0;
  float a1_33 = 0.0;
  float b1iq1 = 0.0;
  float b1iq2 = 0.0;
  float b1iq3 = 0.0;
  float b1wm1 = 0.0;
  float b1wm2 = 0.0;
  float b1wm3 = 0.0;
  // 1軸目 オブザーバゲイン
  float k1_1 = 0.0;
  float k1_2 = 0.0;
  float k1_3 = 0.0;
  // 2軸目 AB行列
  float a2_11 = 0.0;
  float a2_12 = 0.0;
  float a2_13 = 0.0;
  float a2_21 = 0.0;
  float a2_22 = 0.0;
  float a2_23 = 0.0;
  float a2_31 = 0.0;
  float a2_32 = 0.0;
  float a2_33 = 0.0;
  float b2iq1 = 0.0;
  float b2iq2 = 0.0;
  float b2iq3 = 0.0;
  float b2wm1 = 0.0;
  float b2wm2 = 0.0;
  float b2wm3 = 0.0;
  // 2軸目 オブザーバゲイン
  float k2_1 = 0.0;
  float k2_2 = 0.0;
  float k2_3 = 0.0;
  // 3軸目 AB行列
  float a3_11 = 0.0;
  float a3_12 = 0.0;
  float a3_13 = 0.0;
  float a3_21 = 0.0;
  float a3_22 = 0.0;
  float a3_23 = 0.0;
  float a3_31 = 0.0;
  float a3_32 = 0.0;
  float a3_33 = 0.0;
  float b3iq1 = 0.0;
  float b3iq2 = 0.0;
  float b3iq3 = 0.0;
  float b3wm1 = 0.0;
  float b3wm2 = 0.0;
  float b3wm3 = 0.0;
  // 3軸目 オブザーバゲイン
  float k3_1 = 0.0;
  float k3_2 = 0.0;
  float k3_3 = 0.0;

  // 状態変数の定義
  static float wm_Z[3] = {0}, qs_Z[3] = {0}, wl_Z[3] = {0};
  static float wm_Z1[3] = {0}, qs_Z1[3] = {0}, wl_Z1[3] = {0};

  if (robo->BDN == BDN0)
  {
    // 1軸目 オブザーバゲイン計算
    k1_1 = ob_sub[0].k1m1 / axis1.Jl_calc + ob_sub[0].k1z0;
    k1_2 = ob_sub[0].k2m2 / powf(axis1.Jl_calc, 2) + ob_sub[0].k2m1 / axis1.Jl_calc + ob_sub[0].k2z0;
    k1_3 = (ob_sub[0].k3n3 * powf(axis1.Jl_calc, 3) + ob_sub[0].k3n2 * powf(axis1.Jl_calc, 2) + ob_sub[0].k3n1 * axis1.Jl_calc + ob_sub[0].k3n0) / (ob_sub[0].k3d3 * powf(axis1.Jl_calc, 3) + ob_sub[0].k3d2 * powf(axis1.Jl_calc, 2));
    // 1軸目 AB行列 計算
    a1_11 = ob_sub[0].a11cf - k1_1;
    a1_12 = ob_sub[0].a12cf;
    a1_13 = ob_sub[0].a13cf;
    a1_21 = ob_sub[0].a21cf - k1_2;
    a1_22 = ob_sub[0].a22cf1 + ob_sub[0].a22cf2 / axis1.Jl_calc;
    a1_23 = ob_sub[0].a23cf1 + ob_sub[0].a23cf2 / axis1.Jl_calc;
    a1_31 = ob_sub[0].a31cf - k1_3;
    a1_32 = ob_sub[0].a32cf / axis1.Jl_calc;
    a1_33 = ob_sub[0].a33cf1 + ob_sub[0].a33cf2 / axis1.Jl_calc;
    b1iq1 = ob_sub[0].biq1cf;
    b1iq2 = ob_sub[0].biq2cf;
    b1iq3 = ob_sub[0].biq3cf;
    b1wm1 = k1_1;
    b1wm2 = k1_2;
    b1wm3 = k1_3;

    // 状態オブザーバの離散方程式(SOB)
    wm_Z[0] = a1_11 * wm_Z1[0] + a1_12 * qs_Z1[0] + a1_13 * wl_Z1[0] + b1iq1 * robo->I_SOBinput + b1wm1 * robo->wm;
    qs_Z[0] = a1_21 * wm_Z1[0] + a1_22 * qs_Z1[0] + a1_23 * wl_Z1[0] + b1iq2 * robo->I_SOBinput + b1wm2 * robo->wm;
    wl_Z[0] = a1_31 * wm_Z1[0] + a1_32 * qs_Z1[0] + a1_33 * wl_Z1[0] + b1iq3 * robo->I_SOBinput + b1wm3 * robo->wm;

    // 状態量の更新
    wm_Z1[0] = wm_Z[0];
    qs_Z1[0] = qs_Z[0];
    wl_Z1[0] = wl_Z[0];

    // 状態量の出力
    robo->est_prop_wm = wm_Z[0];
    robo->est_prop_qs = qs_Z[0];
    robo->est_prop_wl = wl_Z[0];
  }
  else if (robo->BDN == BDN1)
  {
    // 2軸目 オブザーバゲイン計算
    k2_1 = ob_sub[1].k1m1 / axis2.Jl_calc + ob_sub[1].k1z0;
    k2_2 = ob_sub[1].k2m2 / powf(axis2.Jl_calc, 2) + ob_sub[1].k2m1 / axis2.Jl_calc + ob_sub[1].k2z0;
    k2_3 = (ob_sub[1].k3n3 * powf(axis2.Jl_calc, 3) + ob_sub[1].k3n2 * powf(axis2.Jl_calc, 2) + ob_sub[1].k3n1 * axis2.Jl_calc + ob_sub[1].k3n0) / (ob_sub[1].k3d3 * powf(axis2.Jl_calc, 3) + ob_sub[1].k3d2 * powf(axis2.Jl_calc, 2));
    // 2軸目 AB行列 計算
    a2_11 = ob_sub[1].a11cf - k2_1;
    a2_12 = ob_sub[1].a12cf;
    a2_13 = ob_sub[1].a13cf;
    a2_21 = ob_sub[1].a21cf - k2_2;
    a2_22 = ob_sub[1].a22cf1 + ob_sub[1].a22cf2 / axis2.Jl_calc;
    a2_23 = ob_sub[1].a23cf1 + ob_sub[1].a23cf2 / axis2.Jl_calc;
    a2_31 = ob_sub[1].a31cf - k2_3;
    a2_32 = ob_sub[1].a32cf / axis2.Jl_calc;
    a2_33 = ob_sub[1].a33cf1 + ob_sub[1].a33cf2 / axis2.Jl_calc;
    b2iq1 = ob_sub[1].biq1cf;
    b2iq2 = ob_sub[1].biq2cf;
    b2iq3 = ob_sub[1].biq3cf;
    b2wm1 = k2_1;
    b2wm2 = k2_2;
    b2wm3 = k2_3;

    // FF制御がある場合はオブザーバの入力電流からFF制御の補償電流を除く
    // 状態オブザーバの離散方程式(SOB)
    wm_Z[1] = a2_11 * wm_Z1[1] + a2_12 * qs_Z1[1] + a2_13 * wl_Z1[1] + b2iq1 * robo->I_SOBinput + b2wm1 * robo->wm;
    qs_Z[1] = a2_21 * wm_Z1[1] + a2_22 * qs_Z1[1] + a2_23 * wl_Z1[1] + b2iq2 * robo->I_SOBinput + b2wm2 * robo->wm;
    wl_Z[1] = a2_31 * wm_Z1[1] + a2_32 * qs_Z1[1] + a2_33 * wl_Z1[1] + b2iq3 * robo->I_SOBinput + b2wm3 * robo->wm;

    // 状態量の更新
    wm_Z1[1] = wm_Z[1];
    qs_Z1[1] = qs_Z[1];
    wl_Z1[1] = wl_Z[1];

    // 状態量の出力
    robo->est_prop_wm = wm_Z[1];
    robo->est_prop_qs = qs_Z[1];
    robo->est_prop_wl = wl_Z[1];
  }
  else if (robo->BDN == BDN2)
  {
    // 3軸目 オブザーバゲイン計算
    k3_1 = ob_sub[2].k1m1 / axis3.Jl_calc + ob_sub[2].k1z0;
    k3_2 = ob_sub[2].k2m2 / powf(axis3.Jl_calc, 2) + ob_sub[2].k2m1 / axis3.Jl_calc + ob_sub[2].k2z0;
    k3_3 = (ob_sub[2].k3n3 * powf(axis3.Jl_calc, 3) + ob_sub[2].k3n2 * powf(axis3.Jl_calc, 2) + ob_sub[2].k3n1 * axis3.Jl_calc + ob_sub[2].k3n0) / (ob_sub[2].k3d3 * powf(axis3.Jl_calc, 3) + ob_sub[2].k3d2 * powf(axis3.Jl_calc, 2));
    // 3軸目 AB行列 計算
    a3_11 = ob_sub[2].a11cf - k3_1;
    a3_12 = ob_sub[2].a12cf;
    a3_13 = ob_sub[2].a13cf;
    a3_21 = ob_sub[2].a21cf - k3_2;
    a3_22 = ob_sub[2].a22cf1 + ob_sub[2].a22cf2 / axis3.Jl_calc;
    a3_23 = ob_sub[2].a23cf1 + ob_sub[2].a23cf2 / axis3.Jl_calc;
    a3_31 = ob_sub[2].a31cf - k3_3;
    a3_32 = ob_sub[2].a32cf / axis3.Jl_calc;
    a3_33 = ob_sub[2].a33cf1 + ob_sub[2].a33cf2 / axis3.Jl_calc;
    b3iq1 = ob_sub[2].biq1cf;
    b3iq2 = ob_sub[2].biq2cf;
    b3iq3 = ob_sub[2].biq3cf;
    b3wm1 = k3_1;
    b3wm2 = k3_2;
    b3wm3 = k3_3;

    // 状態オブザーバの離散方程式(SOB)
    wm_Z[2] = a3_11 * wm_Z1[2] + a3_12 * qs_Z1[2] + a3_13 * wl_Z1[2] + b3iq1 * robo->I_SOBinput + b3wm1 * robo->wm;
    qs_Z[2] = a3_21 * wm_Z1[2] + a3_22 * qs_Z1[2] + a3_23 * wl_Z1[2] + b3iq2 * robo->I_SOBinput + b3wm2 * robo->wm;
    wl_Z[2] = a3_31 * wm_Z1[2] + a3_32 * qs_Z1[2] + a3_33 * wl_Z1[2] + b3iq3 * robo->I_SOBinput + b3wm3 * robo->wm;

    // 状態量の更新
    wm_Z1[2] = wm_Z[2];
    qs_Z1[2] = qs_Z[2];
    wl_Z1[2] = wl_Z[2];

    // 状態量の出力
    robo->est_prop_wm = wm_Z[2];
    robo->est_prop_qs = qs_Z[2];
    robo->est_prop_wl = wl_Z[2];
  }
  else
  {
    // ボード番号認識できない場合
  }
}

void FDTD_Tm(Robot *robo)
{
  static float y_0 = 0.0;
  static float y_1 = 0.0;
  static float y_2 = 0.0;
  static float uZ1_0 = 0.0;
  static float uZ1_1 = 0.0;
  static float uZ1_2 = 0.0;
  static float uZ2_0 = 0.0;
  static float uZ2_1 = 0.0;
  static float uZ2_2 = 0.0;
  static float a_0 = 0.0;
  static float a_1 = 0.0;
  static float a_2 = 0.0;

  if (robo->BDN == BDN0)
  {
    y_0 = 1.0 / Tm_sub[0].den_2 * (Tm_sub[0].num_2 * robo->tauLdyn + Tm_sub[0].num_1 * uZ1_0 + Tm_sub[0].num_0 * uZ2_0);
    robo->Iff = y_0;
    a_0 = uZ1_0;
    uZ1_0 = robo->tauLdyn;
    uZ2_0 = a_0;
  }
  else if (robo->BDN == BDN1)
  {
    y_1 = 1.0 / Tm_sub[1].den_2 * (Tm_sub[1].num_2 * robo->tauLdyn + Tm_sub[1].num_1 * uZ1_1 + Tm_sub[1].num_0 * uZ2_1);
    robo->Iff = y_1;
    a_1 = uZ1_1;
    uZ1_1 = robo->tauLdyn;
    uZ2_1 = a_1;
  }
  else if (robo->BDN == BDN2)
  {
    y_2 = 1.0 / Tm_sub[2].den_2 * (Tm_sub[2].num_2 * robo->tauLdyn + Tm_sub[2].num_1 * uZ1_2 + Tm_sub[2].num_0 * uZ2_2);
    robo->Iff = y_2;
    a_2 = uZ1_2;
    uZ1_2 = robo->tauLdyn;
    uZ2_2 = a_2;
  }
}

void FDTD_Tm_Init()
{
  Tm_sub[0].den_0 = 0.0;
  Tm_sub[0].den_1 = 0.0;
  Tm_sub[0].den_2 = (Tp * Tp * axis1.Ksn * axis1.Ktn) / axis1.Rgn / axis1.Jmn;
  Tm_sub[0].num_0 = (-Tp * axis1.Dmn + axis1.Jmn) / axis1.Jmn;
  Tm_sub[0].num_1 = (axis1.Rgn * axis1.Rgn * (Tp * axis1.Dmn - 2.0 * axis1.Jmn) + Tp * Tp * axis1.Ksn) / axis1.Rgn / axis1.Rgn / axis1.Jmn;
  Tm_sub[0].num_2 = 1.0;

  Tm_sub[1].den_0 = 0.0;
  Tm_sub[1].den_1 = 0.0;
  Tm_sub[1].den_2 = (Tp * Tp * axis2.Ksn * axis2.Ktn) / axis2.Rgn / axis2.Jmn;
  Tm_sub[1].num_0 = (-Tp * axis2.Dmn + axis2.Jmn) / axis2.Jmn;
  Tm_sub[1].num_1 = (axis2.Rgn * axis2.Rgn * (Tp * axis2.Dmn - 2.0 * axis2.Jmn) + Tp * Tp * axis2.Ksn) / axis2.Rgn / axis2.Rgn / axis2.Jmn;
  Tm_sub[1].num_2 = 1.0;

  Tm_sub[2].den_0 = 0.0;
  Tm_sub[2].den_1 = 0.0;
  Tm_sub[2].den_2 = (Tp * Tp * axis3.Ksn * axis3.Ktn) / axis3.Rgn / axis3.Jmn;
  Tm_sub[2].num_0 = (-Tp * axis3.Dmn + axis3.Jmn) / axis3.Jmn;
  Tm_sub[2].num_1 = (axis3.Rgn * axis3.Rgn * (Tp * axis3.Dmn - 2.0 * axis3.Jmn) + Tp * Tp * axis3.Ksn) / axis3.Rgn / axis3.Rgn / axis3.Jmn;
  Tm_sub[2].num_2 = 1.0;
}

void SetLPF(LPF_param *Filter, float Ts, float fs, float Q)
{
  float w = 2 * PI * fs;
  Filter[0].Num = 1;
  Filter[0].flag = 0;
  Filter[0].Ts = Ts;
  Filter[0].w = w;
  Filter[0].Q = Q;
  Filter[0].uZ1 = 0.0;
  Filter[0].uZ2 = 0.0;
  Filter[0].uZ3 = 0.0;
  Filter[0].yZ1 = 0.0;
  Filter[0].yZ2 = 0.0;
  Filter[0].yZ3 = 0.0;
  Filter[1].Num = 2;
  Filter[1].flag = 0;
  Filter[1].Ts = Ts;
  Filter[1].w = w;
  Filter[1].Q = Q;
  Filter[1].uZ1 = 0.0;
  Filter[1].uZ2 = 0.0;
  Filter[1].uZ3 = 0.0;
  Filter[1].yZ1 = 0.0;
  Filter[1].yZ2 = 0.0;
  Filter[1].yZ3 = 0.0;
  Filter[2].Num = 3;
  Filter[2].flag = 0;
  Filter[2].Ts = Ts;
  Filter[2].w = w;
  Filter[2].Q = Q;
  Filter[2].uZ1 = 0.0;
  Filter[2].uZ2 = 0.0;
  Filter[2].uZ3 = 0.0;
  Filter[2].yZ1 = 0.0;
  Filter[2].yZ2 = 0.0;
  Filter[2].yZ3 = 0.0;
}

// LPF
float GetFilterdSignal(LPF_param *Filter, float u, int flag_init)
{
  float Q, w, Ts, y, yZ1, yZ2, yZ3, uZ1, uZ2, uZ3;
  Q = Filter->Q;
  w = Filter->w;
  Ts = Filter->Ts;
  if(flag_init == 1){
    Filter->flag = 0;
  }
  if (Filter->flag == 0)
  {
    WAVE_INIT_COUNT++;
    Filter->flag = 1;
    Filter->uZ1 = u;
    Filter->uZ2 = u;
    Filter->uZ3 = u;
    Filter->yZ1 = u;
    Filter->yZ2 = u;
    Filter->yZ3 = u;
  }
  uZ1 = Filter->uZ1;
  uZ2 = Filter->uZ2;
  uZ3 = Filter->uZ3;
  yZ1 = Filter->yZ1;
  yZ2 = Filter->yZ2;
  yZ3 = Filter->yZ3;
  y = Q * Ts * Ts * Ts * w * w * (u + 3.0 * uZ1 + 3.0 * uZ2 + uZ3) - 4.0 * Q * Ts * (yZ3 - yZ2 - yZ1) - 2.0 * w * Ts * Ts * (-yZ3 - yZ2 + yZ1) - Q * Ts * Ts * Ts * w * w * (yZ3 + 3.0 * yZ2 + 3.0 * yZ1);
  y = y * 1.0 / (4.0 * Q * Ts + 2.0 * w * Ts * Ts + Q * Ts * Ts * Ts * w * w);
  Filter->uZ3 = Filter->uZ2;
  Filter->uZ2 = Filter->uZ1;
  Filter->uZ1 = u;
  Filter->yZ3 = Filter->yZ2;
  Filter->yZ2 = Filter->yZ1;
  Filter->yZ1 = y;
  return y;
}

// int CalcHandCmdCenter(int flag_cmd, float goal[3], float t_wait, float speed, float start_hand[3], int flag_loop){
//   float wait_dummy = t_wait;
//   float vel_dummy = speed;
//   if(flag_cmd == 0){
//     return CalcHandCmdCircle(goal[3], 3.00, 10.0, start_hand[3], flag_loop);
//   }else if(flag_cmd == 1){
//     return CalcHandCmdRectangle(goal[3], 3.00, 10.0, start_hand[3], flag_loop);
//   }else if(flag_cmd == 2){
//     return CalcHandCmdDiamond(goal[3], 3.00, 10.0, start_hand[3], flag_loop);
//   }
// }

// 手先軌跡(円)
int CalcHandCmdCircle(float goal[3], float vel_hand[3], float t_wait, float speed, float start_hand[3], int flag_loop)
{
  const float D = 0.020;
  const float path = (PI * D);
  const float freq = 1 / (path / (speed/60.0));
  const float t_task = (1.0 / freq) * 1.5;
  // const float t_task = 1.5 / freq;
  // const float S1 = mwsin(theta);
  // const float C1 = mwcos(theta);
  // const float S2 = mwsin(theta2);
  // const float C2 = mwcos(theta2);
  const float S1 = -0.7071;
  const float C1 = 0.7071;
  // static float start_hand[3] = {1.2746, -0.07071, 0.2466};
  const float x_slide = 1.2746;
  // const float x_slide = 1.2846; // +x側10mmオフセット
  // const float x_slide = 1.2696; // -x側10mmオフセット
  const float y_slide = 0.0;
  const float z_slide = 0.2466;
  static float Tall = 0;
  static float goalZ[3] = {0, 0, 0};
  static float fxZ, fyZ, fzZ;
  static float fx = 0, fy = 0, fz = 0;
  static float vfx = 0, vfy = 0, vfz = 0;
  static int flag_init = 0;
  if(flag_cmd_end == 0){
    if (flag_init == 0)
    {
      if (flag_loop == 1)
      {
        flag_init = 1;
      }
      else
      {
        flag_init = 0;
      }
      fx = 0.000;
      fy = -D/2.0;
      fz = 0.000;
      goal[0] = C1 * fx + S1 * fz + x_slide;
      goal[1] = fy + y_slide;
      goal[2] = C1 * fz - S1 * fx + z_slide;
      vel_hand[0] = 0.0;
      vel_hand[1] = 0.0;
      vel_hand[2] = 0.0;
      goalZ[0] = goal[0];
      goalZ[1] = goal[1];
      goalZ[2] = goal[2];
      // fx = C1 * (start_hand[0] - x_slide) - S1 * (start_hand[2] - z_slide);
      // fy = (start_hand[1] - y_slide);
      // fz = S1 * (start_hand[0] - x_slide) + C1 * (start_hand[2] - z_slide);
      fxZ = fx;
      fyZ = fy;
      fzZ = fz;
    }
    if(flag_init == 1){
      if (Tall < t_wait)
      {
        goal[0] = goalZ[0];
        goal[1] = goalZ[1];
        goal[2] = goalZ[2];
        vel_hand[0] = 0.0;
        vel_hand[1] = 0.0;
        vel_hand[2] = 0.0;
      }
      else if (Tall >= t_wait && Tall < (t_wait + t_task))
      {
        fx = (D / 2.0) * sin(2 * PI * freq * (Tall - t_wait));
        fy = -(D / 2.0) * cos(2 * PI * freq * (Tall - t_wait));
        fz = 0;
        vfx = (D / 2.0) * (2 * PI * freq) * cos(2 * PI * freq * (Tall - t_wait));
        vfy = (D / 2.0) * (2 * PI * freq) * sin(2 * PI * freq * (Tall - t_wait));
        vfz = 0;

        goal[0] = C1 * fx + S1 * fz + x_slide;
        goal[1] = fy + y_slide;
        goal[2] = C1 * fz - S1 * fx + z_slide;
        vel_hand[0] = C1 * vfx + S1 * vfz;
        vel_hand[1] = vfy;
        vel_hand[2] = C1 * vfz - S1 * vfx;
        fxZ = fx;
        fyZ = fy;
        fzZ = fz;
        goalZ[0] = goal[0];
        goalZ[1] = goal[1];
        goalZ[2] = goal[2];
      }
      else if (Tall >= t_wait + t_task)
      {
        goal[0] = goalZ[0];
        goal[1] = goalZ[1];
        goal[2] = goalZ[2];
        vel_hand[0] = 0;
        vel_hand[1] = 0;
        vel_hand[2] = 0;
        flag_cmd_end = 1;
      }
      Tall += Tp;
    }
  }else{
    goal[0] = goalZ[0];
    goal[1] = goalZ[1];
    goal[2] = goalZ[2];
    vel_hand[0] = 0;
    vel_hand[1] = 0;
    vel_hand[2] = 0;
    Tall = 0;
    flag_init = 0;
  }
  WAVE_fx = goal[0];
  WAVE_fy = goal[1];
  WAVE_fz = goal[2];
  WAVE_vx = vel_hand[0];
  WAVE_vy = vel_hand[1];
  WAVE_vz = vel_hand[2];
  return 1; //1を返すと逆運動学でFilterあり。０を返すとFilter無し。
}

// 手先軌跡(四角) 100mm四方の正方形
// この関数におけるfx,fy,fzからGoalへの変換はy軸周りでの回転を前提としている。
int CalcHandCmdRectangle(float goal[3], float t_wait, float speed, float start_hand[3], int flag_loop)
{
  const float path = (0.100 * 5);
  const float t_task = path * (60.0 / speed);
  const float slope = 0.100 / (t_task / 5.0);
  const float theta = -PI / 4;
  const float S1 = -0.7071;
  const float C1 = 0.7071;
  // static float start_hand[3] = {1.2746, -0.07071, 0.2466};
  const float x_slide = 1.2746;
  const float y_slide = 0.0;
  const float z_slide = 0.2466;
  static float Tall = 0;
  static float goalZ[3] = {0, 0, 0};
  static float fxZ, fyZ, fzZ;
  static float fx = 0, fy = 0, fz = 0;
  static int flag_init = 0;
  if(flag_cmd_end == 0){
    if (flag_init == 0)
    {
      if (flag_loop == 1)
      {
        flag_init = 1;
      }
      else
      {
        flag_init = 0;
      }
      fx = 0.050;
      fy = -0.050;
      fz = 0.000;
      goal[0] = C1 * fxZ + S1 * fzZ + x_slide;
      goal[1] = fyZ + y_slide;
      goal[2] = C1 * fzZ - S1 * fxZ + z_slide;
      goalZ[0] = goal[0];
      goalZ[1] = goal[1];
      goalZ[2] = goal[2];
      // fx = C1 * (start_hand[0] - x_slide) - S1 * (start_hand[2] - z_slide);
      // fy = (start_hand[1] - y_slide);
      // fz = S1 * (start_hand[0] - x_slide) + C1 * (start_hand[2] - z_slide);
      fxZ = fx;
      fyZ = fy;
      fzZ = fz;
    }
    if(flag_init == 1){
      if (Tall < t_wait)
      {
        goal[0] = goalZ[0];
        goal[1] = goalZ[1];
        goal[2] = goalZ[2];
        Tall += Tp;
      }
      else if (Tall >= t_wait && Tall < (t_wait + t_task))
      {
        // 正方形（XY平面で見た時[10,-10]から反時計回りに初めて[10,10]で終わる）
        // 正方形を5辺分描画するのでt_taskを5分割する
        if ((Tall - t_wait) < t_task / 5.0)
        {
          fx = fxZ;              //  50 -> 50
          fy = slope * Tp + fyZ; // -50 -> 50
          fz = fzZ;
        }
        else if ((Tall - t_wait) >= t_task * (1.0 / 5.0) && (Tall - t_wait) < t_task * (2.0 / 5.0))
        {
          fx = -slope * Tp + fxZ; //  50 -> -50
          fy = fyZ;               //  50 ->  50
          fz = fzZ;
        }
        else if ((Tall - t_wait) >= t_task * (2.0 / 5.0) && (Tall - t_wait) < t_task * (3.0 / 5.0))
        {
          fx = fxZ;               // -50 -> -50
          fy = -slope * Tp + fyZ; //  50 -> -50
          fz = fzZ;
        }
        else if ((Tall - t_wait) >= t_task * (3.0 / 5.0) && (Tall - t_wait) < t_task * (4.0 / 5.0))
        {
          fx = slope * Tp + fxZ; // -50 ->  50
          fy = fyZ;              // -50 -> -50
          fz = fzZ;
        }
        else if ((Tall - t_wait) >= t_task * (4.0 / 5.0) && (Tall - t_wait) < t_task * (5.0 / 5.0))
        {
          fx = fxZ;              //  50 -> 50
          fy = slope * Tp + fyZ; // -50 -> 50
          fz = fzZ;
        }
        goal[0] = C1 * fxZ + S1 * fzZ + x_slide;
        goal[1] = fyZ + y_slide;
        goal[2] = C1 * fzZ - S1 * fxZ + z_slide;
        fxZ = fx;
        fyZ = fy;
        fzZ = fz;
        goalZ[0] = goal[0];
        goalZ[1] = goal[1];
        goalZ[2] = goal[2];
        Tall += Tp;
      }
      else if (Tall >= t_wait + t_task)
      {
        goal[0] = goalZ[0];
        goal[1] = goalZ[1];
        goal[2] = goalZ[2];
        Tall += Tp;
        flag_cmd_end = 1;
      }
    }
  }else{
    goal[0] = goalZ[0];
    goal[1] = goalZ[1];
    goal[2] = goalZ[2];
    Tall = 0;
    flag_init = 0;
  }
  WAVE_fx = fx;
  WAVE_fy = fy;
  WAVE_fz = fz;
  return 0;
}

// 手先軌跡(ひし形) 一辺100mm,XY軸上に頂点を持つひし形
// この関数におけるfx,fy,fzからGoalへの変換はz軸周り-45度の回転、y軸周りでの回転、伸長80％空間への並進としている。
int CalcHandCmdDiamond(float goal[3], float t_wait, float speed, float start_hand[3], int flag_loop)
{
  const float l = 0.100;
  const float path = (l * 6);
  const float t_task = path * (60.0 / speed);
  const float slope = l / (t_task / 6.0);
  const float theta = -PI / 4;
  const float theta2 = -PI / 4;
  // const float S1 = mwsin(theta);
  // const float C1 = mwcos(theta);
  // const float S2 = mwsin(theta2);
  // const float C2 = mwcos(theta2);
  const float S1 = -0.7071;
  const float C1 = 0.7071;
  const float S2 = -0.7071;
  const float C2 = 0.7071;
  // static float start_hand[3] = {1.2746, -0.07071, 0.2466};
  const float x_slide = 1.2746;
  const float y_slide = 0.0;
  const float z_slide = 0.2466;
  static float Tall = 0;
  static float goalZ[3] = {0, 0, 0};
  static float fxZ, fyZ, fzZ;
  static float fx = 0, fy = 0, fz = 0;
  static int flag_init = 0;
  if(flag_cmd_end == 0){
    if (flag_init == 0)
    {
      if (flag_loop == 1)
      {
        flag_init = 1;
      }
      else
      {
        flag_init = 0;
      }
      fx = 0.000;
      fy = -0.07071;
      fz = 0.000;
      goal[0] = (C1 * C2 * fx) + (S1 * fz) - (C1 * S2 * fy) + x_slide;
      goal[1] = (S2 * fx) + (C2 * fy) + y_slide;
      goal[2] = (C1 * fz) - (S1 * C2 * fx) + (S1 * S2 * fy) + z_slide;
      goalZ[0] = goal[0];
      goalZ[1] = goal[1];
      goalZ[2] = goal[2];
      // 正方形用の手先→作業座標系変換
      // fx = C1 * (start_hand[0] - x_slide) - S1 * (start_hand[2] - z_slide);
      // fy = (start_hand[1] - y_slide);
      // fz = S1 * (start_hand[0] - x_slide) + C1 * (start_hand[2] - z_slide);
      // ひし形用の手先→作業座標系変換
      // fx = (C1 * C2 * (start_hand[0] - x_slide)) + (S2 * (start_hand[1] - y_slide)) - (S1 * C2 * (start_hand[2] - z_slide));
      // fy = (C1 * S2 * (start_hand[0] - x_slide)) + (C2 * (start_hand[1] - y_slide)) - (S1 * S2 * (start_hand[2] - z_slide));
      // fz = (S1 * (start_hand[0] - x_slide)) + (C1 * (start_hand[2] - z_slide));
      fxZ = fx;
      fyZ = fy;
      fzZ = fz;
    }
    if(flag_init == 1){
      if (Tall < t_wait)
      {
        goal[0] = goalZ[0];
        goal[1] = goalZ[1];
        goal[2] = goalZ[2];
        Tall += Tp;
      }
      else if (Tall >= t_wait && Tall < (t_wait + t_task))
      {
        // 正方形（XY平面で見た時[10,-10]から反時計回りに初めて[10,10]で終わる）
        // 正方形を5辺分描画するのでt_taskを5分割する
        if ((Tall - t_wait) < t_task / 6.0)
        {
          fx = fxZ;              //  50 -> 50
          fy = slope * Tp + fyZ; // -50 -> 50
          fz = fzZ;
        }
        else if ((Tall - t_wait) >= t_task * (1.0 / 6.0) && (Tall - t_wait) < t_task * (2.0 / 6.0))
        {
          fx = -slope * Tp + fxZ; //  50 -> -50
          fy = fyZ;               //  50 ->  50
          fz = fzZ;
        }
        else if ((Tall - t_wait) >= t_task * (2.0 / 6.0) && (Tall - t_wait) < t_task * (3.0 / 6.0))
        {
          fx = fxZ;               // -50 -> -50
          fy = -slope * Tp + fyZ; //  50 -> -50
          fz = fzZ;
        }
        else if ((Tall - t_wait) >= t_task * (3.0 / 6.0) && (Tall - t_wait) < t_task * (4.0 / 6.0))
        {
          fx = slope * Tp + fxZ; // -50 ->  50
          fy = fyZ;              // -50 -> -50
          fz = fzZ;
        }
        else if ((Tall - t_wait) >= t_task * (4.0 / 6.0) && (Tall - t_wait) < t_task * (5.0 / 6.0))
        {
          fx = fxZ;              //  50 -> 50
          fy = slope * Tp + fyZ; // -50 -> 50
          fz = fzZ;
        }
        else if ((Tall - t_wait) >= t_task * (5.0 / 6.0) && (Tall - t_wait) < t_task * (6.0 / 6.0))
        {
          fx = -slope * Tp + fxZ; //  50 -> -50
          fy = fyZ;               //  50 ->  50
          fz = fzZ;
        }
        goal[0] = (C1 * C2 * fx) + (S1 * fz) - (C1 * S2 * fy) + x_slide;
        goal[1] = (S2 * fx) + (C2 * fy) + y_slide;
        goal[2] = (C1 * fz) - (S1 * C2 * fx) + (S1 * S2 * fy) + z_slide;
        fxZ = fx;
        fyZ = fy;
        fzZ = fz;
        goalZ[0] = goal[0];
        goalZ[1] = goal[1];
        goalZ[2] = goal[2];
        Tall += Tp;
      }
      else if (Tall >= t_wait + t_task)
      {
        goal[0] = goalZ[0];
        goal[1] = goalZ[1];
        goal[2] = goalZ[2];
        Tall += Tp;
        flag_cmd_end = 1;
      }
    }
  }else{
    goal[0] = goalZ[0];
    goal[1] = goalZ[1];
    goal[2] = goalZ[2];
    Tall = 0;
    flag_init = 0;
  }
  WAVE_fx = fx;
  WAVE_fy = fy;
  WAVE_fz = fz;
  return 0;
}

void LimitPosCmd(Robot *robo)
{
  if (robo->qm_ref >= robo->qm_max)
  {
    robo->qm_ref = robo->qm_max;
  }
  else if (robo->qm_min >= robo->qm_ref)
  {
    robo->qm_ref = robo->qm_min;
  }
}

// // 逆運動学（手先 -> モーター位置）
// void CalcInverseCmd(float goal[3], float joint[3], float motor[3], float wm[3], int flag_filter, int flag_reset, float dt)
// {
//   static float motorZ[3];
//   const float Rgn1 = 140.254;
//   const float Rgn2 = 121;
//   const float Rgn3 = 121;
//   const float Lb = 0.16;
//   const float Ld = 0.088;
//   const float Lac = 0.2685;
//   const float Le = 0.56;
//   const float Lf = 0.088;
//   const float Lg = 0.13;
//   const float Lh1 = 0.145;
//   const float Lh2 = 0.455;
//   const float Lii = 0.04;
//   const float Lj = 0.2;
//   const float Lk = 0.05;
//   const float Larm = sqrtf(((Lh1 + Lh2 + Lj + Lk) * (Lh1 + Lh2 + Lj + Lk) + (Lii + Lg) * (Lii + Lg)));

//   static float p1[3] = {0, 0, 0};
//   static float Lp2h = 0.0;
//   static float Lg2h = 0.0;
//   static float Phi1 = 0.0;
//   static float Phi2 = 0.0;
//   static float Phi3 = 0.0;
//   static float Phi4 = 0.0;
//   static int flag_init = 0;
//   if(flag_reset == 1){
//     flag_init = 1;
//   }

//   joint[0] = 1 * atan2f(goal[1], goal[0]);
//   if(flag_filter == 1){
//     joint[0] = GetFilterdSignal(&LPF_motor[0], joint[0], flag_init);
//   }
//   // joint[0] = mwarctan2(goal[1], goal[0]);

//   p1[0] = Lb * cos(joint[0]);
//   // p1[0] = Lb * mwcos(joint[0]);
//   p1[1] = Lb * sin(joint[0]);
//   // p1[1] = Lb * mwsin(joint[0]);
//   p1[2] = Lac;

//   Lp2h = sqrtf((((goal[0] - p1[0]) * (goal[0] - p1[0])) + ((goal[1] - p1[1]) * (goal[1] - p1[1])) + ((goal[2] - p1[2]) * (goal[2] - p1[2]))));
//   Lg2h = sqrtf((((goal[0] - p1[0]) * (goal[0] - p1[0])) + ((goal[1] - p1[1]) * (goal[1] - p1[1])) + ((goal[2] - 0.0) * (goal[2] - 0.0))));

//   Phi1 = acos(((Le * Le) + (Larm * Larm) - (Lp2h * Lp2h)) / (2 * Le * Larm));
//   Phi2 = acos((Lh1 + Lh2 + Lj + Lk) / (Larm));
//   Phi3 = acos(((Le * Le) + (Lp2h * Lp2h) - (Larm * Larm)) / (2 * Le * Lp2h));
//   Phi4 = acos(((Lac * Lac) + (Lp2h * Lp2h) - (Lg2h * Lg2h)) / (2 * Lac * Lp2h));

//   joint[2] = (PI / 2.0) - Phi1 + Phi2;
//   if (flag_filter == 1)
//   {
//     joint[2] = GetFilterdSignal(&LPF_motor[2], joint[2], flag_init);
//   }
//   joint[1] = PI - Phi3 - Phi4;
//   if (flag_filter == 1)
//   {
//     joint[1] = GetFilterdSignal(&LPF_motor[1], joint[1], flag_init);
//   }
//   motor[0] = -joint[0] * Rgn1;
//   motor[1] = joint[1] * Rgn2;
//   motor[2] = joint[2] * Rgn3;
//   if (flag_reset == 1)
//   {
//     motorZ[0] = motor[0];
//     motorZ[1] = motor[1];
//     motorZ[2] = motor[2];
//   }

//   wm[0] = backward_diff(motor[0], motorZ[0], dt);
//   wm[1] = backward_diff(motor[1], motorZ[1], dt);
//   wm[2] = backward_diff(motor[2], motorZ[2], dt);
//   wm[0] = GetFilterdSignal(&LPF_cmd[0], wm[0], flag_init);
//   wm[1] = GetFilterdSignal(&LPF_cmd[1], wm[1], flag_init);
//   wm[2] = GetFilterdSignal(&LPF_cmd[2], wm[2], flag_init);

//   motorZ[0] = motor[0];
//   motorZ[1] = motor[1];
//   motorZ[2] = motor[2];

//   flag_init = 0;
// }

void CalcInverseCmd_vel(float goal[3], float vel_hand[3], float ql_cmd[3], float wl_cmd[3], float ql_init[3], int flag_reset)
{
  static int initialized = 0;
  static float Rgn1, Rgn2, Rgn3;
  static float Lb, Lac, Ld, Le, Lf, Lg, Lh1, Lh2, Lii, Lj, Lk, Larm, L4;
  static float joint[3], motor[3], ql_vel[3], qm_vel[3], qm_first[3];
  static int flag_init = 0;
  static float p1[3] = {0.0, 0.0, 0.0};
  static float J[3][3] = {{0,0,0},
                          {0,0,0},
                          {0,0,0}};

  if (flag_reset == 1){
    initialized = 0;
    flag_init = 1;
  }
  if (initialized == 0)
  {
    Rgn1 = 140.254;
    Rgn2 = 121;
    Rgn3 = 121;
    Lac = 0.2685;
    Lb = 0.16;
    Ld = 0.088;
    Le = 0.56;
    Lf = 0.088;
    Lg = 0.13;
    Lh1 = 0.145;
    Lh2 = 0.455;
    Lii = 0.04;
    Lj = 0.2;
    Lk = 0.05;
    Larm = sqrt(pow(Lh1 + Lh2 + Lj + Lk, 2) + pow(Lii + Lg, 2));
    L4 = Lh1 + Lh2 + Lj + Lk;
    initialized = 1;
  }

  float x = goal[0];
  float y = goal[1];
  float z = goal[2];
  float vx = vel_hand[0];
  float vy = vel_hand[1];
  float vz = vel_hand[2];

  joint[0] = -atan2(y, x);
  p1[0] = Lb * cos(joint[0]);
  p1[1] = Lb * sin(joint[0]);
  p1[2] = Lac;

  float Lp2h = sqrt(pow(x - p1[0], 2) + pow(y - p1[1], 2) + pow(z - p1[2], 2));
  float Lg2h = sqrt(pow(x - p1[0], 2) + pow(y - p1[1], 2) + pow(z - 0.0, 2));

  float Phi1 = acos((Le * Le + Larm * Larm - Lp2h * Lp2h) / (2 * Le * Larm));
  float Phi2 = acos((Lh1 + Lh2 + Lj + Lk) / Larm);
  float Phi3 = acos((Le * Le + Lp2h * Lp2h - Larm * Larm) / (2 * Le * Lp2h));
  float Phi4 = acos((Lac * Lac + Lp2h * Lp2h - Lg2h * Lg2h) / (2 * Lac * Lp2h));

  joint[2] = (PI / 2.0) - Phi1 + Phi2;
  joint[1] = PI - Phi3 - Phi4;

  // 三角関数の計算
  float S1 = sin(joint[0]);
  float C1 = cos(joint[0]);
  float S2 = sin(joint[1]);
  float C2 = cos(joint[1]);
  float S23 = sin(joint[1] + joint[2]);
  float C23 = cos(joint[1] + joint[2]);

  // ヤコビアン行列の成分
  J[0][0] = (Lf - Ld) * C1 - S1 * (Lb + L4 * C23 + Le * S2 + Lg * S23 + Lii * S23);
  J[0][1] = C1 * (Le * C2 + Lg * C23 + Lii * C23 - L4 * S23);
  J[0][2] = C1*(Lg*C23+Lii*C23-L4*S23);
  J[1][0] = -(Lf - Ld) * S1 - C1 * (Lb + L4 * C23 + Le * S2 + Lg * S23 + Lii * S23);
  J[1][1] = -S1 * (Le * C2 + Lg * C23 + Lii * C23 - L4 * S23);
  J[1][2] = -S1 * (Lg * C23 + Lii * C23 - L4 * S23);
  J[2][0] = 0;
  J[2][1] = -L4 * C23 - Le * S2 - (Lg + Lii) * S23;
  J[2][2] = -L4 * C23 - Lg + Lii * S23;

  // 逆行列の計算 (手計算で導出)
  float detJ = J[0][0] * (J[1][1] * J[2][2] - J[1][2] * J[2][1]) -
                J[0][1] * (J[1][0] * J[2][2] - J[1][2] * J[2][0]) +
                J[0][2] * (J[1][0] * J[2][1] - J[1][1] * J[2][0]);

  if (fabs(detJ) < 1e-6)
  {
    ql_vel[0] = ql_vel[1] = ql_vel[2] = 0;
  }
  else
  {
    float invJ[3][3];

    invJ[0][0] = (J[1][1] * J[2][2] - J[1][2] * J[2][1]) / detJ;
    invJ[0][1] = (J[0][2] * J[2][1] - J[0][1] * J[2][2]) / detJ;
    invJ[0][2] = (J[0][1] * J[1][2] - J[0][2] * J[1][1]) / detJ;
    invJ[1][0] = (J[1][2] * J[2][0] - J[1][0] * J[2][2]) / detJ;
    invJ[1][1] = (J[0][0] * J[2][2] - J[0][2] * J[2][0]) / detJ;
    invJ[1][2] = (J[0][2] * J[1][0] - J[0][0] * J[1][2]) / detJ;
    invJ[2][0] = (J[1][0] * J[2][1] - J[1][1] * J[2][0]) / detJ;
    invJ[2][1] = (J[0][1] * J[2][0] - J[0][0] * J[2][1]) / detJ;
    invJ[2][2] = (J[0][0] * J[1][1] - J[0][1] * J[1][0]) / detJ;

    ql_vel[0] = invJ[0][0] * vx + invJ[0][1] * vy + invJ[0][2] * vz;
    ql_vel[1] = invJ[1][0] * vx + invJ[1][1] * vy + invJ[1][2] * vz;
    ql_vel[2] = invJ[2][0] * vx + invJ[2][1] * vy + invJ[2][2] * vz;
  }

  joint[0] = GetFilterdSignal(&LPF_motor[0], joint[0], flag_init);
  joint[1] = GetFilterdSignal(&LPF_motor[1], joint[1], flag_init);
  joint[2] = GetFilterdSignal(&LPF_motor[2], joint[2], flag_init);
  ql_vel[0] = GetFilterdSignal(&LPF_cmd[0], ql_vel[0], flag_init);
  ql_vel[1] = GetFilterdSignal(&LPF_cmd[1], ql_vel[1], flag_init);
  ql_vel[2] = GetFilterdSignal(&LPF_cmd[2], ql_vel[2], flag_init);

  motor[0] = joint[0] * Rgn1;
  motor[1] = joint[1] * Rgn2;
  motor[2] = joint[2] * Rgn3;
  qm_vel[0] = ql_vel[0] * Rgn1;
  qm_vel[1] = ql_vel[1] * Rgn2;
  qm_vel[2] = ql_vel[2] * Rgn3;

  if (initialized == 1){
    qm_first[0] = motor[0];
    qm_first[1] = motor[1];
    qm_first[2] = motor[2];
    initialized = 2;
  }
  int i = 0;
  for (i = 0; i < 3; i++)
  {
    ql_cmd[i] = motor[i];
    wl_cmd[i] = qm_vel[i];
    ql_init[i] = qm_first[i];
  }
  flag_init = 0;
}

float backward_diff(float x, float xZ, float dt)
{
  return ((x - xZ) / dt);
}

float GeneratorCircle1st(float t_wait, float start)
{
  static float y = 0.0;
  static float yZ1 = 0.0;
  static float Tall = 0.0;
  static int j = 0;
  static int k = 0;
  static float Ts_data = 1.0 / 500.0;
  static float scale1 = 3.0;
  if (flag_CircleStart1 != 0)
  {
    yZ1 = start;
    flag_CircleStart1 = 0;
    Tall = 0.0;
  }
  if (flag_hard == 1)
  {
    scale1 = scale_slow;
  }
  else
  {
    scale1 = scale_fast;
    // scale1 = scale;
  }
  if (Tall < t_wait)
  {
    y = yZ1;
    yZ1 = y;
    Tall += Tp;
  }
  else if (Tall >= t_wait && Tall < (t_wait + scale1)) // t_wait = 2.0 s
  {
    // if (j == 0)
    // {
    //   if (flag_hard == 1)
    //   {
    //     y = cmd_1_hard[k];
    //   }
    //   else
    //   {
    //     y = cmd_1_soft[k];
    //   }
    // }
    // else
    // {
    //   if (flag_hard == 1)
    //   {
    //     y = cmd_1_hard[k] + ((cmd_1_hard[k + 1] - cmd_1_hard[k])) * Tp / Ts_data * j;
    //   }
    //   else
    //   {
    //     y = cmd_1_soft[k] + ((cmd_1_soft[k + 1] - cmd_1_soft[k])) * Tp / Ts_data * j;
    //   }
    // }
    // j++;
    // if (j > 9)
    // {
    //   j = 0;
    //   k++;
    // }
    y = yZ1;
    yZ1 = y;
    Tall += Tp;
  }
  else if (Tall >= (t_wait + scale1))
  {
    y = yZ1;
    yZ1 = y;
    j = 0;
    k = 0;
    Tall += Tp;
  }
  return y;
}

float GeneratorCircle2nd(float t_wait, float start)
{
  static float y = 0.0;
  static float yZ1 = 0.0;
  static float Tall = 0.0;
  static int j = 0;
  static int k = 0;
  static float Ts_data = 1.0 / 500.0;
  static float scale2 = 3.0;
  if (flag_CircleStart2 != 0)
  {
    yZ1 = start;
    flag_CircleStart2 = 0;
    Tall = 0.0;
  }
  if (flag_hard == 1)
  {
    scale2 = scale_slow;
  }
  else
  {
    scale2 = scale_fast;
    // scale2 = scale;
  }
  if (Tall < t_wait)
  {
    y = yZ1;
    yZ1 = y;
    Tall += Tp;
  }
  else if (Tall >= t_wait && Tall < (t_wait + scale2)) // t_wait = 2.0 s
  {
    // if (j == 0)
    // {
    //   if (flag_hard == 1)
    //   {
    //     y = cmd_2_hard[k];
    //   }
    //   else
    //   {
    //     y = cmd_2_soft[k];
    //   }
    // }
    // else
    // {
    //   if (flag_hard == 1)
    //   {
    //     y = cmd_2_hard[k] + ((cmd_2_hard[k + 1] - cmd_2_hard[k])) * Tp / Ts_data * j;
    //   }
    //   else
    //   {
    //     y = cmd_2_soft[k] + ((cmd_2_soft[k + 1] - cmd_2_soft[k])) * Tp / Ts_data * j;
    //   }
    // }
    // j++;
    // if (j > 9)
    // {
    //   j = 0;
    //   k++;
    // }
    y = yZ1;
    yZ1 = y;
    Tall += Tp;
  }
  else if (Tall >= (t_wait + scale2))
  {
    y = yZ1;
    yZ1 = y;
    j = 0;
    k = 0;
    Tall += Tp;
  }
  return y;
}

float GeneratorCircle3rd(float t_wait, float start)
{
  static float y = 0.0;
  static float yZ1 = 0.0;
  static float Tall = 0.0;
  static int j = 0;
  static int k = 0;
  static float Ts_data = 1.0 / 500.0;
  static float scale3 = 3.0;
  if (flag_CircleStart3 != 0)
  {
    yZ1 = start;
    flag_CircleStart3 = 0;
    Tall = 0.0;
  }
  if (flag_hard == 1)
  {
    scale3 = scale_slow;
  }
  else
  {
    scale3 = scale_fast;
    // scale3 = scale;
  }
  if (Tall < t_wait)
  {
    y = yZ1;
    yZ1 = y;
    Tall += Tp;
  }
  else if (Tall >= t_wait && Tall < (t_wait + scale3)) // t_wait = 2.0 s
  {
    // if (j == 0)
    // {
    //   if (flag_hard == 1)
    //   {
    //     y = cmd_3_hard[k];
    //   }
    //   else
    //   {
    //     y = cmd_3_soft[k];
    //   }
    // }
    // else
    // {
    //   if (flag_hard == 1)
    //   {
    //     y = cmd_3_hard[k] + ((cmd_3_hard[k + 1] - cmd_3_hard[k])) * Tp / Ts_data * j;
    //   }
    //   else
    //   {
    //     y = cmd_3_soft[k] + ((cmd_3_soft[k + 1] - cmd_3_soft[k])) * Tp / Ts_data * j;
    //   }
    // }
    // j++;
    // if (j > 9)
    // {
    //   j = 0;
    //   k++;
    // }
    y = yZ1;
    yZ1 = y;
    Tall += Tp;
  }
  else if (Tall >= (t_wait + scale3))
  {
    y = yZ1;
    yZ1 = y;
    j = 0;
    k = 0;
    Tall += Tp;
  }
  return y;
}

float ManyRampGenerator1stAxis(float a_ramp, float vel, float t_wait, float t_ramp, float t_const, float a_ramp_back, float t_ramp_back)
{
  // a_rammp 傾き, t_wait ランプアップ開始時間, t_ramp ランプアップ時間, t_const 定常値の時間
  // 台形速度位置指令生成 つまり台形　
  // 最後初期化する
  // 再実験可能
  float a2 = vel / t_ramp;
  float b2 = 0;
  float c2 = -vel / t_ramp_back;
  int wait_line = t_wait / Tp;
  int ramp_line = (t_ramp) / Tp + wait_line;
  int const_line = t_const / Tp + ramp_line;
  int back_line = t_ramp_back / Tp + const_line;
  int stay_line = 4.0 / Tp + back_line;

  static float t_all = 0.0;
  static int t = 0.0;
  static float a = 0.0;
  static float aZ1 = 0.0;
  static float w = 0.0;
  static float wZ1 = 0.0;
  static float z = 0.0;
  static float zZ1 = 0.0;
  static float z_state = 0.0;
  if (flag_end1 == 0)
  {
    // t_waitの間指令値は0
    if (t < (wait_line))
    {
      a = 0.0;
      t++;
    }
    else if (t < ramp_line)
    { // ランプアップ
      a = a2;
      t++;
    }
    else if (t < const_line)
    { // 一定値を保持
      a = b2;
      t++;
    }
    else if (t < back_line)
    { // ランプダウン
      a = c2;
      t++;
    }
    else if (t < stay_line)
    {
      a = 0;
      t++;
    }
    else
    { // 次のステップへ
      flag_end1 = 1;
    }
    w = wZ1 + a * Tp;
    wZ1 = w;

    z = zZ1 + w * Tp;
    zZ1 = z;
    z_state = z;

    t_all += Tp;
  }
  else
  {
    z = z_state;
    zZ1 = 0;
    w = 0;
    wZ1 = 0;
    a = 0;
    t = 0;
    t_all = 0;
  }
  WAVE_AccCmd1 = a;
  WAVE_VelCmd1 = w;
  // return z;
  return w; // D-PD
}

float ManyRampGenerator2ndAxis(float a_ramp, float vel, float t_wait, float t_ramp, float t_const, float a_ramp_back, float t_ramp_back)
{
  // a_rammp 傾き, t_wait ランプアップ開始時間, t_ramp ランプアップ時間, t_const 定常値の時間
  // 台形速度位置指令生成 つまり台形　
  // 最後初期化する
  // 再実験可能
  float a2 = vel / t_ramp;
  float b2 = 0;
  float c2 = -vel / t_ramp_back;
  int wait_line = t_wait / Tp;
  int ramp_line = (t_ramp) / Tp + wait_line;
  int const_line = t_const / Tp + ramp_line;
  int back_line = t_ramp_back / Tp + const_line;
  int stay_line = 4.0 / Tp + back_line;

  static float t_all = 0.0;
  static int t = 0.0;
  static float a = 0.0;
  static float aZ1 = 0.0;
  static float w = 0.0;
  static float wZ1 = 0.0;
  static float z = 0.0;
  static float zZ1 = 0.0;
  static float z_state = 0.0;
  if (flag_end2 == 0)
  {
    // t_waitの間指令値は0
    if (t < (wait_line))
    {
      a = 0.0;
      t++;
    }
    else if (t < ramp_line)
    { // ランプアップ
      a = a2;
      t++;
    }
    else if (t < const_line)
    { // 一定値を保持
      a = b2;
      t++;
    }
    else if (t < back_line)
    { // ランプダウン
      a = c2;
      t++;
    }
    else if (t < stay_line)
    {
      a = 0;
      t++;
    }
    else
    { // 次のステップへ
      flag_end2 = 1;
    }
    w = wZ1 + a * Tp;
    wZ1 = w;

    z = zZ1 + w * Tp;
    zZ1 = z;
    z_state = z;

    t_all += Tp;
  }
  else
  {
    z = z_state;
    zZ1 = 0;
    w = 0;
    wZ1 = 0;
    a = 0;
    t = 0;
    t_all = 0;
  }
  WAVE_AccCmd2 = a;
  WAVE_VelCmd2 = w;
  // return z;
  return w; // D-PD
}

float ManyRampGenerator3rdAxis(float a_ramp, float vel, float t_wait, float t_ramp, float t_const, float a_ramp_back, float t_ramp_back)
{
  // a_rammp 傾き, t_wait ランプアップ開始時間, t_ramp ランプアップ時間, t_const 定常値の時間
  // 台形速度位置指令生成 つまり台形　
  // 最後初期化する
  // 再実験可能
  float a2 = vel / t_ramp;
  float b2 = 0;
  float c2 = -vel / t_ramp_back;
  int wait_line = t_wait / Tp;
  int ramp_line = (t_ramp) / Tp + wait_line;
  int const_line = t_const / Tp + ramp_line;
  int back_line = t_ramp_back / Tp + const_line;
  int stay_line = 4.0 / Tp + back_line;

  static float t_all = 0.0;
  static int t = 0.0;
  static float a = 0.0;
  static float aZ1 = 0.0;
  static float w = 0.0;
  static float wZ1 = 0.0;
  static float z = 0.0;
  static float zZ1 = 0.0;
  static float z_state = 0.0;
  if (flag_end3 == 0)
  {
    // t_waitの間指令値は0
    if (t < (wait_line))
    {
      a = 0.0;
      t++;
    }
    else if (t < ramp_line)
    { // ランプアップ
      a = a2;
      t++;
    }
    else if (t < const_line)
    { // 一定値を保持
      a = b2;
      t++;
    }
    else if (t < back_line)
    { // ランプダウン
      a = c2;
      t++;
    }
    else if (t < stay_line)
    {
      a = 0;
      t++;
    }
    else
    { // 次のステップへ
      flag_end3 = 1;
    }
    w = wZ1 + a * Tp;
    wZ1 = w;

    z = zZ1 + w * Tp;
    zZ1 = z;
    z_state = z;

    t_all += Tp;
  }
  else
  {
    z = z_state;
    zZ1 = 0;
    w = 0;
    wZ1 = 0;
    a = 0;
    t = 0;
    t_all = 0;
  }
  WAVE_AccCmd3 = a;
  WAVE_VelCmd3 = w;
  // return z;
  return w; // D-PD
}

float TriangularAccelerationCommandGenerator(int BDN)
{
  // ・三角加速度指令の説明
  // 三角加速度指令は以下のような波形で、1～6の区間をそれぞれif文で作っている
  // a_time_full=w_time_full/2の関係は固定する必要がある
  //
  // 区間     1    2    3     4  5    6
  //
  //            /\
  //           /  \
  // _________/    \_________      _________
  //                         \    /
  //                          \  /
  //                           \/

  // 積分実装用変数
  static float wm_prev[3] = {0};
  static float qm_prev[3] = {0};

  // 作業用変数
  static int loop_count_num[3] = {0};    // [s] 経過時間
  static int sign_invers[3] = {1, 1, 1}; // 符号反転用フラグ
  float am_ref = 0.0;                    // [rad/s^2]駆動側加速度指令値
  float wm_ref = 0.0;                    // [rad/s]駆動側速度指令値
  float qm_ref = 0.0;                    // [rad]駆動側位置指令値
  float t = 0.0;                         // [s]時間

  // 1軸目指令値生成
  if (BDN == BDN0)
  {
    // 三角加速度指令演算開始
    loop_count_num[0] = loop_count_num[0] + 1;
    t = Tp * loop_count_num[0];

    // 区間1
    if (tri[0].t1 < t && t <= tri[0].t2)
    {
      am_ref = sign_invers[0] * tri[0].jark * t;
    }
    // 区間2
    else if (tri[0].t2 < t && t <= tri[0].t3)
    {
      am_ref = sign_invers[0] * (tri[0].jark * tri[0].t2 - tri[0].jark * (t - tri[0].t2));
    }
    // 区間3
    else if (tri[0].t3 < t && t <= tri[0].t4)
    {
      am_ref = 0;
    }
    // 区間4
    else if (tri[0].t4 < t && t <= tri[0].t5)
    {
      am_ref = sign_invers[0] * (-tri[0].jark * (t - tri[0].t4));
    }
    // 区間5
    else if (tri[0].t5 < t && t <= tri[0].t6)
    {
      am_ref = sign_invers[0] * (-tri[0].jark * (tri[0].t5 - tri[0].t4) + tri[0].jark * (t - tri[0].t5));
    }
    // 三角加速度指令の初期化処理
    else if (tri[0].t6 <= t)
    {
      loop_count_num[0] = 0;
      sign_invers[0] = -1 * sign_invers[0];
      am_ref = 0;
    }
    else
    {
      // 三角加速度指令計算ミス
    }

    // 加速度→速度(後退差分で積分器を実装)
    wm_ref = Tp * am_ref + wm_prev[0];
    wm_prev[0] = wm_ref;

    // 速度→位置(後退差分で積分器を実装)
    qm_ref = Tp * wm_ref + qm_prev[0];
    qm_prev[0] = qm_ref;

    WAVE_jark1 = tri[0].jark;
    WAVE_am_TriAccCmd1 = am_ref;
    WAVE_wm_TriAccCmd1 = wm_ref;
    WAVE_qm_TriAccCmd1 = qm_ref;
  }

  // 2軸目指令値生成
  if (BDN == BDN1)
  {
    // 三角加速度指令演算開始
    loop_count_num[1] = loop_count_num[1] + 1;
    t = Tp * loop_count_num[1];

    // 区間1
    if (tri[1].t1 < t && t <= tri[1].t2)
    {
      am_ref = sign_invers[1] * tri[1].jark * t;
    }
    // 区間2
    else if (tri[1].t2 < t && t <= tri[1].t3)
    {
      am_ref = sign_invers[1] * (tri[1].jark * tri[1].t2 - tri[1].jark * (t - tri[1].t2));
    }
    // 区間3
    else if (tri[1].t3 < t && t <= tri[1].t4)
    {
      am_ref = 0;
    }
    // 区間4
    else if (tri[1].t4 < t && t <= tri[1].t5)
    {
      am_ref = sign_invers[1] * (-tri[1].jark * (t - tri[1].t4));
    }
    // 区間5
    else if (tri[1].t5 < t && t <= tri[1].t6)
    {
      am_ref = sign_invers[1] * (-tri[1].jark * (tri[1].t5 - tri[1].t4) + tri[1].jark * (t - tri[1].t5));
    }
    // 三角加速度指令の初期化処理
    else if (tri[1].t6 <= t)
    {
      loop_count_num[1] = 0;
      sign_invers[1] = -1 * sign_invers[1];
      am_ref = 0;
    }
    else
    {
      // 三角加速度指令計算ミス
    }

    // 加速度→速度(後退差分で積分器を実装)
    wm_ref = Tp * am_ref + wm_prev[1];
    wm_prev[1] = wm_ref;

    // 速度→位置(後退差分で積分器を実装)
    qm_ref = Tp * wm_ref + qm_prev[1];
    qm_prev[1] = qm_ref;

    WAVE_jark2 = tri[1].jark;
    WAVE_am_TriAccCmd2 = am_ref;
    WAVE_wm_TriAccCmd2 = wm_ref;
    WAVE_qm_TriAccCmd2 = qm_ref;
  }

  // 3軸目指令値生成
  if (BDN == BDN2)
  {
    // 三角加速度指令演算開始
    loop_count_num[2] = loop_count_num[2] + 1;
    t = Tp * loop_count_num[2];

    // 区間1
    if (tri[2].t1 < t && t <= tri[2].t2)
    {
      am_ref = sign_invers[2] * tri[2].jark * t;
    }
    // 区間2
    else if (tri[2].t2 < t && t <= tri[2].t3)
    {
      am_ref = sign_invers[2] * (tri[2].jark * tri[2].t2 - tri[2].jark * (t - tri[2].t2));
    }
    // 区間3
    else if (tri[2].t3 < t && t <= tri[2].t4)
    {
      am_ref = 0;
    }
    // 区間4
    else if (tri[2].t4 < t && t <= tri[2].t5)
    {
      am_ref = sign_invers[2] * (-tri[2].jark * (t - tri[2].t4));
    }
    // 区間5
    else if (tri[2].t5 < t && t <= tri[2].t6)
    {
      am_ref = sign_invers[2] * (-tri[2].jark * (tri[2].t5 - tri[2].t4) + tri[2].jark * (t - tri[2].t5));
    }
    // 三角加速度指令の初期化処理
    else if (tri[2].t6 <= t)
    {
      loop_count_num[2] = 0;
      sign_invers[2] = -1 * sign_invers[2];
      am_ref = 0;
    }
    else
    {
      // 三角加速度指令計算ミス
    }

    // 加速度→速度(後退差分で積分器を実装)
    wm_ref = Tp * am_ref + wm_prev[2];
    wm_prev[2] = wm_ref;

    // 速度→位置(後退差分で積分器を実装)
    qm_ref = Tp * wm_ref + qm_prev[2];
    qm_prev[2] = qm_ref;

    WAVE_jark3 = tri[2].jark;
    WAVE_am_TriAccCmd3 = am_ref;
    WAVE_wm_TriAccCmd3 = wm_ref;
    WAVE_qm_TriAccCmd3 = qm_ref;
  }

  // 計算した位置指令値を返す
  return qm_ref;
}

void TriangularAccelerationCommandGeneratorInit(float ql_const_deg, float q_time_full, float w_time_full, float Rg, int BDN)
{
  // 1軸目計算
  if (BDN == BDN0)
  {
    // 加速時間の定義
    tri[0].a_time_full = w_time_full / 2.0;

    // 区間1～6を区切る時間
    tri[0].t1 = 0.0;
    tri[0].t2 = tri[0].a_time_full;
    tri[0].t3 = 2.0 * tri[0].a_time_full;
    tri[0].t4 = q_time_full - w_time_full;
    tri[0].t5 = q_time_full - w_time_full + tri[0].a_time_full;
    tri[0].t6 = q_time_full;

    // ql[deg.] -> qm[rad]変換
    tri[0].ql_const = ql_const_deg * PI / 180.0; // [rad] 負荷側位置目標値
    tri[0].qm_const = tri[0].ql_const * Rg;      // [rad] 駆動側位置目標値

    // ジャーク値 [rad/s^3] 台形の三角の傾き
    tri[0].jark = -6.0 * tri[0].qm_const / (-powf(tri[0].t6, 3) + (-3.0 * tri[0].t4 + 6.0 * tri[0].t5) * powf(tri[0].t6, 2) + (-6.0 * powf(tri[0].t2, 2) + 3.0 * powf(tri[0].t4, 2) - 6.0 * powf(tri[0].t5, 2)) * tri[0].t6 + powf(tri[0].t1, 3) - 2.0 * powf(tri[0].t2, 3) + 12.0 * powf(tri[0].t2, 2) * tri[0].t3 - 6.0 * tri[0].t2 * powf(tri[0].t3, 2) + powf(tri[0].t3, 3) - powf(tri[0].t4, 3) + 2.0 * powf(tri[0].t5, 3));
  }
  // 2軸目計算
  else if (BDN == BDN1)
  {
    // 加速時間の定義
    tri[1].a_time_full = w_time_full / 2.0;

    // 区間1～6を区切る時間
    tri[1].t1 = 0.0;
    tri[1].t2 = tri[1].a_time_full;
    tri[1].t3 = 2.0 * tri[1].a_time_full;
    tri[1].t4 = q_time_full - w_time_full;
    tri[1].t5 = q_time_full - w_time_full + tri[1].a_time_full;
    tri[1].t6 = q_time_full;

    // ql[deg.] -> qm[rad]変換
    tri[1].ql_const = ql_const_deg * PI / 180.0; // [rad] 負荷側位置目標値
    tri[1].qm_const = tri[1].ql_const * Rg;      // [rad] 駆動側位置目標値

    // ジャーク値 [rad/s^3] 台形の三角の傾き
    tri[1].jark = -6.0 * tri[1].qm_const / (-powf(tri[1].t6, 3) + (-3.0 * tri[1].t4 + 6.0 * tri[1].t5) * powf(tri[1].t6, 2) + (-6.0 * powf(tri[1].t2, 2) + 3.0 * powf(tri[1].t4, 2) - 6.0 * powf(tri[1].t5, 2)) * tri[1].t6 + powf(tri[1].t1, 3) - 2.0 * powf(tri[1].t2, 3) + 12.0 * powf(tri[1].t2, 2) * tri[1].t3 - 6.0 * tri[1].t2 * powf(tri[1].t3, 2) + powf(tri[1].t3, 3) - powf(tri[1].t4, 3) + 2.0 * powf(tri[1].t5, 3));
  }
  // 3軸目計算
  else if (BDN == BDN2)
  {
    // 加速時間の定義
    tri[2].a_time_full = w_time_full / 2.0;

    // 区間1～6を区切る時間
    tri[2].t1 = 0.0;
    tri[2].t2 = tri[2].a_time_full;
    tri[2].t3 = 2.0 * tri[2].a_time_full;
    tri[2].t4 = q_time_full - w_time_full;
    tri[2].t5 = q_time_full - w_time_full + tri[2].a_time_full;
    tri[2].t6 = q_time_full;

    // ql[deg.] -> qm[rad]変換
    tri[2].ql_const = ql_const_deg * PI / 180.0; // [rad] 負荷側位置目標値
    tri[2].qm_const = tri[2].ql_const * Rg;      // [rad] 駆動側位置目標値

    // ジャーク値 [rad/s^3] 台形の三角の傾き
    tri[2].jark = -6.0 * tri[2].qm_const / (-powf(tri[2].t6, 3) + (-3.0 * tri[2].t4 + 6.0 * tri[2].t5) * powf(tri[2].t6, 2) + (-6.0 * powf(tri[2].t2, 2) + 3.0 * powf(tri[2].t4, 2) - 6.0 * powf(tri[2].t5, 2)) * tri[2].t6 + powf(tri[2].t1, 3) - 2.0 * powf(tri[2].t2, 3) + 12.0 * powf(tri[2].t2, 2) * tri[2].t3 - 6.0 * tri[2].t2 * powf(tri[2].t3, 2) + powf(tri[2].t3, 3) - powf(tri[2].t4, 3) + 2.0 * powf(tri[2].t5, 3));
  }
  else
  {
  }
}

/** @brief 電圧指令設定
 @param [in] Robot.BDN PEV ボード番号
 @param [in] Robot.Vdc	DCリンク電圧
 @param [in] Robot.VrefU,Robot.VrefV,Robot.VrefW	電圧指令値
 @param [in] Robot.IresU,Robot.IresV,Robot.IresW	電流応答
 @param [out]	Robot.Vu_std,Robot.Vv_std,Robot.Vw_std	変調率
*/
void SetVoltReferences(Robot *robo)
{
  /// SetVoltReferences(Vdc, VrefU, VrefV, VrefW, &Vu_std, &Vv_std, &Vw_std, IresU, IresV, IresW);		// 電圧指令値の出力
  /// int BDN,float Vdc, float Vu, float Vv, float Vw, float *Vu_std, float *Vv_std, float *Vw_std, float iu_res, float iv_res, float iw_res
  /// インバータの電圧指令値を設定する関数
  float Vdc = robo->Vdc;
  float Vu = robo->VrefU, Vv = robo->VrefV, Vw = robo->VrefW;
  float iu_res = robo->IresU, iv_res = robo->IresV, iw_res = robo->IresW;

  float vu_comp = 0.0, vv_comp = 0.0, vw_comp = 0.0;
  float ModRatioU = 0; // U相変調率
  float ModRatioV = 0; // V相変調率
  float ModRatioW = 0; // W相変調率f
  float del_vdead = 0.0;

  // 変調率の計算
  if (Vdc == 0)
  {
    // ゼロ割処理
    ModRatioU = 0;
    ModRatioV = 0;
    ModRatioW = 0;
  }
  else
  {
    // 電圧センサで取得した直流リンク電圧から変調率を計算
    // 変調率は±2でリミット
    ModRatioU = Limiter(Vu / (Vdc / 2.0), 2);
    ModRatioV = Limiter(Vv / (Vdc / 2.0), 2);
    ModRatioW = Limiter(Vw / (Vdc / 2.0), 2);
  }
  robo->Vu_std = ModRatioU;
  robo->Vv_std = ModRatioV;
  robo->Vw_std = ModRatioW;
  // PEV_inverter_set_uvw(robo->BDN, ModRatioU, ModRatioV, ModRatioW, 0);
  //  デッドタイム補償 リミット偏差フィードバックしないよう，補償はここで行う
  del_vdead = Vdc * Td * Fs; // "ACサーボ"p54参照。直流リンク電圧Ed × デッドタイムTd × キャリア周波数
  if (iu_res >= 0.0)         // デッドタイム補償値生成(電流の向き判定)
    vu_comp = del_vdead;     // u相電流向き判定，正なら＋dV_dead，負なら-dV_deadを補償値とする
  else
    vu_comp = -del_vdead;

  if (iv_res >= 0.0)
    vv_comp = del_vdead; // 同上
  else
    vv_comp = -del_vdead;

  if (iw_res >= 0.0)
    vw_comp = del_vdead; // 同上
  else
    vw_comp = -del_vdead;

  if (flag_dead == 1)
  { // 補償
    ModRatioU += vu_comp / (Vdc / 2.0);
    ModRatioV += vv_comp / (Vdc / 2.0);
    ModRatioW += vw_comp / (Vdc / 2.0);
  }
  // 再度リミット
  ModRatioU = Limiter(ModRatioU, 1.0);
  ModRatioV = Limiter(ModRatioV, 1.0);
  ModRatioW = Limiter(ModRatioW, 1.0);

  WAVE_U_modulation = ModRatioU;
  WAVE_V_modulation = ModRatioV;
  WAVE_W_modulation = ModRatioW;

  // インバータへ出力
  //  PEV_inverter_set_uvw(robo->BDN, ModRatioU, ModRatioV, ModRatioW, 0);
  if (robo->BDN == BDN0)
  {
    PEV_inverter_set_uvw_br(robo->BDN, ModRatioU, ModRatioV, ModRatioW, robo->MRBR, 0);
  }
  else if (robo->BDN == BDN1)
  {
    PEV_inverter_set_uvw_br(robo->BDN, ModRatioU, ModRatioV, ModRatioW, robo->MRBR, 0);
  }
  else if (robo->BDN == BDN2)
  {
    PEV_inverter_set_uvw_br(robo->BDN, ModRatioU, ModRatioV, ModRatioW, robo->MRBR, 0);
  }

  // 監視用変数に変調率を代入
  if (robo->BDN == BDN0)
  {
    WAVE_MRU1 = ModRatioU;
    WAVE_MRV1 = ModRatioV;
    WAVE_MRW1 = ModRatioW;
  }
  else if (robo->BDN == BDN1)
  {
    WAVE_MRU2 = ModRatioU;
    WAVE_MRV2 = ModRatioV;
    WAVE_MRW2 = ModRatioW;
  }
  else if (robo->BDN == BDN2)
  {
    WAVE_MRU3 = ModRatioU;
    WAVE_MRV3 = ModRatioV;
    WAVE_MRW3 = ModRatioW;
  }
}

void CalcFDTDWr_QmrefInputType(Robot *robo)
{
  // 状態変数の定義
  static float wm_Z[3] = {0}, qm_Z[3] = {0}, qs_Z[3] = {0}, wl_Z[3] = {0}, ql_Z[3] = {0}, z_Z[3] = {0};
  static float wm_Z1[3] = {0}, qm_Z1[3] = {0}, qs_Z1[3] = {0}, wl_Z1[3] = {0}, ql_Z1[3] = {0}, z_Z1[3] = {0};

  if (robo->BDN == BDN0)
  {
    // 状態量の計算
    wm_Z[0] = Wr_sub[0].a11cf * wm_Z1[0] + Wr_sub[0].a12cf * qm_Z1[0] + Wr_sub[0].a13cf * qs_Z1[0] + Wr_sub[0].a14cf * wl_Z1[0] + Wr_sub[0].a15cf * ql_Z1[0] + Wr_sub[0].a16cf * z_Z1[0] + Wr_sub[0].b1cf * robo->qm_ref;
    qm_Z[0] = Wr_sub[0].a21cf * wm_Z1[0] + Wr_sub[0].a22cf * qm_Z1[0] + Wr_sub[0].a23cf * qs_Z1[0] + Wr_sub[0].a24cf * wl_Z1[0] + Wr_sub[0].a25cf * ql_Z1[0] + Wr_sub[0].a26cf * z_Z1[0] + Wr_sub[0].b2cf * robo->qm_ref;
    qs_Z[0] = Wr_sub[0].a31cf * wm_Z1[0] + Wr_sub[0].a32cf * qm_Z1[0] + (Wr_sub[0].a33cf1 + Wr_sub[0].a33cf2 / axis1.Jl_calc) * qs_Z1[0] + (Wr_sub[0].a34cf1 + Wr_sub[0].a34cf2 / axis1.Jl_calc) * wl_Z1[0] + Wr_sub[0].a35cf * ql_Z1[0] + Wr_sub[0].a36cf * z_Z1[0] + Wr_sub[0].b3cf * robo->qm_ref;
    wl_Z[0] = Wr_sub[0].a41cf * wm_Z1[0] + Wr_sub[0].a42cf * qm_Z1[0] + Wr_sub[0].a43cf / axis1.Jl_calc * qs_Z1[0] + (Wr_sub[0].a44cf1 + Wr_sub[0].a44cf2 / axis1.Jl_calc) * wl_Z1[0] + Wr_sub[0].a45cf * ql_Z1[0] + Wr_sub[0].a46cf * z_Z1[0] + Wr_sub[0].b4cf * robo->qm_ref;
    ql_Z[0] = Wr_sub[0].a51cf * wm_Z1[0] + Wr_sub[0].a52cf * qm_Z1[0] + Wr_sub[0].a53cf / axis1.Jl_calc * qs_Z1[0] + (Wr_sub[0].a54cf1 + Wr_sub[0].a54cf2 / axis1.Jl_calc) * wl_Z1[0] + Wr_sub[0].a55cf * ql_Z1[0] + Wr_sub[0].a56cf * z_Z1[0] + Wr_sub[0].b5cf * robo->qm_ref;
    z_Z[0] = Wr_sub[0].a61cf * wm_Z1[0] + Wr_sub[0].a62cf * qm_Z1[0] + Wr_sub[0].a63cf * qs_Z1[0] + Wr_sub[0].a64cf * wl_Z1[0] + Wr_sub[0].a65cf * ql_Z1[0] + Wr_sub[0].a66cf * z_Z1[0] + Wr_sub[0].b6cf * robo->qm_ref;

    // 状態量の更新axis1.
    wm_Z1[0] = wm_Z[0];
    qm_Z1[0] = qm_Z[0];
    qs_Z1[0] = qs_Z[0];
    wl_Z1[0] = wl_Z[0];
    ql_Z1[0] = ql_Z[0];
    z_Z1[0] = z_Z[0];

    // 計算結果の代入
    robo->ql_calc = robo->theta_rl_init + ql_Z[0];
    robo->wl_calc = wl_Z[0];
    robo->al_calc = (robo->Ksn * qs_Z[0] - robo->Dln * wl_Z[0]) / robo->Jl_calc;
    robo->wm_calc = wm_Z[0];
  }
  else if (robo->BDN == BDN1)
  {
    // 状態量の計算
    wm_Z[1] = Wr_sub[1].a11cf * wm_Z1[1] + Wr_sub[1].a12cf * qm_Z1[1] + Wr_sub[1].a13cf * qs_Z1[1] + Wr_sub[1].a14cf * wl_Z1[1] + Wr_sub[1].a15cf * ql_Z1[1] + Wr_sub[1].a16cf * z_Z1[1] + Wr_sub[1].b1cf * axis2.qm_ref;
    qm_Z[1] = Wr_sub[1].a21cf * wm_Z1[1] + Wr_sub[1].a22cf * qm_Z1[1] + Wr_sub[1].a23cf * qs_Z1[1] + Wr_sub[1].a24cf * wl_Z1[1] + Wr_sub[1].a25cf * ql_Z1[1] + Wr_sub[1].a26cf * z_Z1[1] + Wr_sub[1].b2cf * axis2.qm_ref;
    qs_Z[1] = Wr_sub[1].a31cf * wm_Z1[1] + Wr_sub[1].a32cf * qm_Z1[1] + (Wr_sub[1].a33cf1 + Wr_sub[1].a33cf2 / axis2.Jl_calc) * qs_Z1[1] + (Wr_sub[1].a34cf1 + Wr_sub[1].a34cf2 / axis2.Jl_calc) * wl_Z1[1] + Wr_sub[1].a35cf * ql_Z1[1] + Wr_sub[1].a36cf * z_Z1[1] + Wr_sub[1].b3cf * axis2.qm_ref;
    wl_Z[1] = Wr_sub[1].a41cf * wm_Z1[1] + Wr_sub[1].a42cf * qm_Z1[1] + Wr_sub[1].a43cf / axis2.Jl_calc * qs_Z1[1] + (Wr_sub[1].a44cf1 + Wr_sub[1].a44cf2 / axis2.Jl_calc) * wl_Z1[1] + Wr_sub[1].a45cf * ql_Z1[1] + Wr_sub[1].a46cf * z_Z1[1] + Wr_sub[1].b4cf * axis2.qm_ref;
    ql_Z[1] = Wr_sub[1].a51cf * wm_Z1[1] + Wr_sub[1].a52cf * qm_Z1[1] + Wr_sub[1].a53cf / axis2.Jl_calc * qs_Z1[1] + (Wr_sub[1].a54cf1 + Wr_sub[1].a54cf2 / axis2.Jl_calc) * wl_Z1[1] + Wr_sub[1].a55cf * ql_Z1[1] + Wr_sub[1].a56cf * z_Z1[1] + Wr_sub[1].b5cf * axis2.qm_ref;
    z_Z[1] = Wr_sub[1].a61cf * wm_Z1[1] + Wr_sub[1].a62cf * qm_Z1[1] + Wr_sub[1].a63cf * qs_Z1[1] + Wr_sub[1].a64cf * wl_Z1[1] + Wr_sub[1].a65cf * ql_Z1[1] + Wr_sub[1].a66cf * z_Z1[1] + Wr_sub[1].b6cf * axis2.qm_ref;

    // 状態量の更新
    wm_Z1[1] = wm_Z[1];
    qm_Z1[1] = qm_Z[1];
    qs_Z1[1] = qs_Z[1];
    wl_Z1[1] = wl_Z[1];
    ql_Z1[1] = ql_Z[1];
    z_Z1[1] = z_Z[1];

    // 計算結果の代入
    axis2.ql_calc = axis2.theta_rl_init + ql_Z[1];
    axis2.wl_calc = wl_Z[1];
    axis2.al_calc = (axis2.Ksn * qs_Z[1] - axis2.Dln * wl_Z[1]) / axis2.Jl_calc;
    axis2.wm_calc = wm_Z[1];
  }
  else if (robo->BDN == BDN2)
  {
    // 状態量の計算
    wm_Z[2] = Wr_sub[2].a11cf * wm_Z1[2] + Wr_sub[2].a12cf * qm_Z1[2] + Wr_sub[2].a13cf * qs_Z1[2] + Wr_sub[2].a14cf * wl_Z1[2] + Wr_sub[2].a15cf * ql_Z1[2] + Wr_sub[2].a16cf * z_Z1[2] + Wr_sub[2].b1cf * robo->qm_ref;
    qm_Z[2] = Wr_sub[2].a21cf * wm_Z1[2] + Wr_sub[2].a22cf * qm_Z1[2] + Wr_sub[2].a23cf * qs_Z1[2] + Wr_sub[2].a24cf * wl_Z1[2] + Wr_sub[2].a25cf * ql_Z1[2] + Wr_sub[2].a26cf * z_Z1[2] + Wr_sub[2].b2cf * robo->qm_ref;
    qs_Z[2] = Wr_sub[2].a31cf * wm_Z1[2] + Wr_sub[2].a32cf * qm_Z1[2] + (Wr_sub[2].a33cf1 + Wr_sub[2].a33cf2 / axis3.Jl_calc) * qs_Z1[2] + (Wr_sub[2].a34cf1 + Wr_sub[2].a34cf2 / axis3.Jl_calc) * wl_Z1[2] + Wr_sub[2].a35cf * ql_Z1[2] + Wr_sub[2].a36cf * z_Z1[2] + Wr_sub[2].b3cf * robo->qm_ref;
    wl_Z[2] = Wr_sub[2].a41cf * wm_Z1[2] + Wr_sub[2].a42cf * qm_Z1[2] + Wr_sub[2].a43cf / axis3.Jl_calc * qs_Z1[2] + (Wr_sub[2].a44cf1 + Wr_sub[2].a44cf2 / axis3.Jl_calc) * wl_Z1[2] + Wr_sub[2].a45cf * ql_Z1[2] + Wr_sub[2].a46cf * z_Z1[2] + Wr_sub[2].b4cf * robo->qm_ref;
    ql_Z[2] = Wr_sub[2].a51cf * wm_Z1[2] + Wr_sub[2].a52cf * qm_Z1[2] + Wr_sub[2].a53cf / axis3.Jl_calc * qs_Z1[2] + (Wr_sub[2].a54cf1 + Wr_sub[2].a54cf2 / axis3.Jl_calc) * wl_Z1[2] + Wr_sub[2].a55cf * ql_Z1[2] + Wr_sub[2].a56cf * z_Z1[2] + Wr_sub[2].b5cf * robo->qm_ref;
    z_Z[2] = Wr_sub[2].a61cf * wm_Z1[2] + Wr_sub[2].a62cf * qm_Z1[2] + Wr_sub[2].a63cf * qs_Z1[2] + Wr_sub[2].a64cf * wl_Z1[2] + Wr_sub[2].a65cf * ql_Z1[2] + Wr_sub[2].a66cf * z_Z1[2] + Wr_sub[2].b6cf * robo->qm_ref;

    // 状態量の更新
    wm_Z1[2] = wm_Z[2];
    qm_Z1[2] = qm_Z[2];
    qs_Z1[2] = qs_Z[2];
    wl_Z1[2] = wl_Z[2];
    ql_Z1[2] = ql_Z[2];
    z_Z1[2] = z_Z[2];

    // 計算結果の代入
    robo->ql_calc = robo->theta_rl_init + ql_Z[2];
    robo->wl_calc = wl_Z[2];
    robo->al_calc = (robo->Ksn * qs_Z[2] - robo->Dln * wl_Z[2]) / robo->Jl_calc;
    robo->wm_calc = wm_Z[2];
  }
  else
  {
    // ボード番号認識できない場合
  }
}

void CalcFDTDWrInit_QmrefInputType(void)
{ // 20220408 FDTD法適用見直し
  // qm^ref入力型FDTDWrのJlの係数の計算
  // 1軸目
  Wr_sub[0].a11cf = (-axis1.Ktn * axis1.Kvp * Tp - axis1.Ktn * axis1.fwm * Tp - axis1.Dmn * Tp + axis1.Jmn) / axis1.Jmn;
  Wr_sub[0].a12cf = -axis1.Ktn * axis1.Kvp * axis1.Kpp * Tp / axis1.Jmn;
  Wr_sub[0].a13cf = (-axis1.Ktn * axis1.fqs * Tp - axis1.Ksn * Tp / axis1.Rgn) / axis1.Jmn;
  Wr_sub[0].a14cf = -axis1.Ktn * axis1.fwl * Tp / axis1.Jmn;
  Wr_sub[0].a15cf = 0.0;
  Wr_sub[0].a16cf = axis1.Ktn * Tp / axis1.Jmn;
  Wr_sub[0].a21cf = Tp;
  Wr_sub[0].a22cf = 1.0;
  Wr_sub[0].a23cf = 0.0;
  Wr_sub[0].a24cf = 0.0;
  Wr_sub[0].a25cf = 0.0;
  Wr_sub[0].a26cf = 0.0;
  Wr_sub[0].a31cf = (-axis1.Ktn * axis1.Kvp * powf(Tp, 2) - axis1.Ktn * axis1.fwm * powf(Tp, 2) - axis1.Dmn * powf(Tp, 2) + axis1.Jmn * Tp) / (axis1.Jmn * axis1.Rgn);
  Wr_sub[0].a32cf = -axis1.Ktn * axis1.Kvp * axis1.Kpp * powf(Tp, 2) / (axis1.Jmn * axis1.Rgn);
  Wr_sub[0].a33cf1 = 1.0 + (-axis1.Ktn * axis1.fqs * powf(Tp, 2) - axis1.Ksn * powf(Tp, 2) / axis1.Rgn) / (axis1.Jmn * axis1.Rgn);
  Wr_sub[0].a33cf2 = -powf(Tp, 2) * axis1.Ksn;
  Wr_sub[0].a34cf1 = -Tp - axis1.Ktn * axis1.fwl * powf(Tp, 2) / (axis1.Jmn * axis1.Rgn);
  Wr_sub[0].a34cf2 = powf(Tp, 2) * axis1.Dln;
  Wr_sub[0].a35cf = 0.0;
  Wr_sub[0].a36cf = axis1.Ktn * powf(Tp, 2) / (axis1.Jmn * axis1.Rgn);
  Wr_sub[0].a41cf = 0.0;
  Wr_sub[0].a42cf = 0.0;
  Wr_sub[0].a43cf = Tp * axis1.Ksn;
  Wr_sub[0].a44cf1 = 1.0;
  Wr_sub[0].a44cf2 = -Tp * axis1.Dln;
  Wr_sub[0].a45cf = 0.0;
  Wr_sub[0].a46cf = 0.0;
  Wr_sub[0].a51cf = 0.0;
  Wr_sub[0].a52cf = 0.0;
  Wr_sub[0].a53cf = 0.0;
  Wr_sub[0].a54cf1 = Tp;
  Wr_sub[0].a54cf2 = 0.0;
  Wr_sub[0].a55cf = 1.0;
  Wr_sub[0].a56cf = 0.0;
  Wr_sub[0].a61cf = (axis1.Ktn * axis1.Kvp * axis1.Kvi * powf(Tp, 2) + axis1.Ktn * axis1.fwm * axis1.Kvi * powf(Tp, 2) + axis1.Dmn * axis1.Kvi * powf(Tp, 2) - axis1.Jmn * axis1.Kvi * Tp) / axis1.Jmn - axis1.Kvi * axis1.Kpp * powf(Tp, 2);
  Wr_sub[0].a62cf = axis1.Ktn * axis1.Kvp * axis1.Kpp * axis1.Kvi * powf(Tp, 2) / axis1.Jmn - Tp * axis1.Kvi * axis1.Kpp;
  Wr_sub[0].a63cf = (axis1.Ktn * axis1.fqs * axis1.Kvi * powf(Tp, 2) + axis1.Ksn * axis1.Kvi * powf(Tp, 2) / axis1.Rgn) / axis1.Jmn;
  Wr_sub[0].a64cf = axis1.Ktn * axis1.fwl * axis1.Kvi * powf(Tp, 2) / axis1.Jmn;
  Wr_sub[0].a65cf = 0.0;
  Wr_sub[0].a66cf = 1.0 - axis1.Ktn * axis1.Kvi * powf(Tp, 2) / axis1.Jmn;
  Wr_sub[0].b1cf = axis1.Kpp * axis1.Kvp * axis1.Ktn * Tp / axis1.Jmn;
  Wr_sub[0].b2cf = 0.0;
  Wr_sub[0].b3cf = axis1.Kpp * axis1.Kvp * axis1.Ktn * powf(Tp, 2) / (axis1.Jmn * axis1.Rgn);
  Wr_sub[0].b4cf = 0.0;
  Wr_sub[0].b5cf = 0.0;
  Wr_sub[0].b6cf = -axis1.Kpp * axis1.Kvp * axis1.Kvi * axis1.Ktn * powf(Tp, 2) / axis1.Jmn + Tp * axis1.Kpp * axis1.Kvi;

  // 2軸目
  Wr_sub[1].a11cf = (-axis2.Ktn * axis2.Kvp * Tp - axis2.Ktn * axis2.fwm * Tp - axis2.Dmn * Tp + axis2.Jmn) / axis2.Jmn;
  Wr_sub[1].a12cf = -axis2.Ktn * axis2.Kvp * axis2.Kpp * Tp / axis2.Jmn;
  Wr_sub[1].a13cf = (-axis2.Ktn * axis2.fqs * Tp - axis2.Ksn * Tp / axis2.Rgn) / axis2.Jmn;
  Wr_sub[1].a14cf = -axis2.Ktn * axis2.fwl * Tp / axis2.Jmn;
  Wr_sub[1].a15cf = 0.0;
  Wr_sub[1].a16cf = axis2.Ktn * Tp / axis2.Jmn;
  Wr_sub[1].a21cf = Tp * Wr_sub[1].a11cf;
  Wr_sub[1].a22cf = Tp * Wr_sub[1].a12cf + 1.0;
  Wr_sub[1].a23cf = Tp * Wr_sub[1].a13cf;
  Wr_sub[1].a24cf = Tp * Wr_sub[1].a14cf;
  Wr_sub[1].a25cf = Tp * Wr_sub[1].a15cf;
  Wr_sub[1].a26cf = Tp * Wr_sub[1].a16cf;
  Wr_sub[1].a31cf = (-axis2.Ktn * axis2.Kvp * powf(Tp, 2) - axis2.Ktn * axis2.fwm * powf(Tp, 2) - axis2.Dmn * powf(Tp, 2) + axis2.Jmn * Tp) / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a32cf = -axis2.Ktn * axis2.Kvp * axis2.Kpp * powf(Tp, 2) / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a33cf1 = 1.0 + (-axis2.Ktn * axis2.fqs * powf(Tp, 2) - axis2.Ksn * powf(Tp, 2) / axis2.Rgn) / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a33cf2 = -powf(Tp, 2) * axis2.Ksn;
  Wr_sub[1].a34cf1 = -Tp - axis2.Ktn * axis2.fwl * powf(Tp, 2) / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a34cf2 = powf(Tp, 2) * axis2.Dln;
  Wr_sub[1].a35cf = 0.0;
  Wr_sub[1].a36cf = axis2.Ktn * powf(Tp, 2) / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a41cf = 0.0;
  Wr_sub[1].a42cf = 0.0;
  Wr_sub[1].a43cf = Tp * axis2.Ksn;
  Wr_sub[1].a44cf1 = 1.0;
  Wr_sub[1].a44cf2 = -Tp * axis2.Dln;
  Wr_sub[1].a45cf = 0.0;
  Wr_sub[1].a46cf = 0.0;
  Wr_sub[1].a51cf = 0.0;
  Wr_sub[1].a52cf = 0.0;
  Wr_sub[1].a53cf = Tp * Wr_sub[1].a43cf;
  Wr_sub[1].a54cf1 = Tp * Wr_sub[1].a44cf1;
  Wr_sub[1].a54cf2 = Tp * Wr_sub[1].a44cf2;
  Wr_sub[1].a55cf = 1.0;
  Wr_sub[1].a56cf = 0.0;
  Wr_sub[1].a61cf = (axis2.Ktn * axis2.Kvp * axis2.Kvi * powf(Tp, 2) + axis2.Ktn * axis2.fwm * axis2.Kvi * powf(Tp, 2) + axis2.Dmn * axis2.Kvi * powf(Tp, 2) - axis2.Jmn * axis2.Kvi * Tp) / axis2.Jmn - axis2.Kvi * axis2.Kpp * powf(Tp, 2);
  Wr_sub[1].a62cf = axis2.Ktn * axis2.Kvp * axis2.Kpp * axis2.Kvi * powf(Tp, 2) / axis2.Jmn - Tp * axis2.Kvi * axis2.Kpp;
  Wr_sub[1].a63cf = (axis2.Ktn * axis2.fqs * axis2.Kvi * powf(Tp, 2) + axis2.Ksn * axis2.Kvi * powf(Tp, 2) / axis2.Rgn) / axis2.Jmn;
  Wr_sub[1].a64cf = axis2.Ktn * axis2.fwl * axis2.Kvi * powf(Tp, 2) / axis2.Jmn;
  Wr_sub[1].a65cf = 0.0;
  Wr_sub[1].a66cf = 1.0 - axis2.Ktn * axis2.Kvi * powf(Tp, 2) / axis2.Jmn;
  Wr_sub[1].b1cf = axis2.Kpp * axis2.Kvp * axis2.Ktn * Tp / axis2.Jmn;
  Wr_sub[1].b2cf = axis2.Kpp * axis2.Kvp * axis2.Ktn * Tp * Tp / axis2.Jmn;
  Wr_sub[1].b3cf = axis2.Kpp * axis2.Kvp * axis2.Ktn * powf(Tp, 2) / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].b4cf = 0.0;
  Wr_sub[1].b5cf = 0.0;
  Wr_sub[1].b6cf = -axis2.Kpp * axis2.Kvp * axis2.Kvi * axis2.Ktn * powf(Tp, 2) / axis2.Jmn + Tp * axis2.Kpp * axis2.Kvi;

  // 3軸目
  Wr_sub[2].a11cf = (-axis3.Ktn * axis3.Kvp * Tp - axis3.Ktn * axis3.fwm * Tp - axis3.Dmn * Tp + axis3.Jmn) / axis3.Jmn;
  Wr_sub[2].a12cf = -axis3.Ktn * axis3.Kvp * axis3.Kpp * Tp / axis3.Jmn;
  Wr_sub[2].a13cf = (-axis3.Ktn * axis3.fqs * Tp - axis3.Ksn * Tp / axis3.Rgn) / axis3.Jmn;
  Wr_sub[2].a14cf = -axis3.Ktn * axis3.fwl * Tp / axis3.Jmn;
  Wr_sub[2].a15cf = 0.0;
  Wr_sub[2].a16cf = axis3.Ktn * Tp / axis3.Jmn;
  Wr_sub[2].a21cf = Tp * Wr_sub[2].a11cf;
  Wr_sub[2].a22cf = Tp * Wr_sub[2].a12cf + 1.0;
  Wr_sub[2].a23cf = Tp * Wr_sub[2].a13cf;
  Wr_sub[2].a24cf = Tp * Wr_sub[2].a14cf;
  Wr_sub[2].a25cf = Tp * Wr_sub[2].a15cf;
  Wr_sub[2].a26cf = Tp * Wr_sub[2].a16cf;
  Wr_sub[2].a31cf = (-axis3.Ktn * axis3.Kvp * powf(Tp, 2) - axis3.Ktn * axis3.fwm * powf(Tp, 2) - axis3.Dmn * powf(Tp, 2) + axis3.Jmn * Tp) / (axis3.Jmn * axis3.Rgn);
  Wr_sub[2].a32cf = -axis3.Ktn * axis3.Kvp * axis3.Kpp * powf(Tp, 2) / (axis3.Jmn * axis3.Rgn);
  Wr_sub[2].a33cf1 = 1.0 + (-axis3.Ktn * axis3.fqs * powf(Tp, 2) - axis3.Ksn * powf(Tp, 2) / axis3.Rgn) / (axis3.Jmn * axis3.Rgn);
  Wr_sub[2].a33cf2 = -powf(Tp, 2) * axis3.Ksn;
  Wr_sub[2].a34cf1 = -Tp - axis3.Ktn * axis3.fwl * powf(Tp, 2) / (axis3.Jmn * axis3.Rgn);
  Wr_sub[2].a34cf2 = powf(Tp, 2) * axis3.Dln;
  Wr_sub[2].a35cf = 0.0;
  Wr_sub[2].a36cf = axis3.Ktn * powf(Tp, 2) / (axis3.Jmn * axis3.Rgn);
  Wr_sub[2].a41cf = 0.0;
  Wr_sub[2].a42cf = 0.0;
  Wr_sub[2].a43cf = Tp * axis3.Ksn;
  Wr_sub[2].a44cf1 = 1.0;
  Wr_sub[2].a44cf2 = -Tp * axis3.Dln;
  Wr_sub[2].a45cf = 0.0;
  Wr_sub[2].a46cf = 0.0;
  Wr_sub[2].a51cf = 0.0;
  Wr_sub[2].a52cf = 0.0;
  Wr_sub[2].a53cf = Tp * Wr_sub[2].a43cf;
  Wr_sub[2].a54cf1 = Tp * Wr_sub[2].a44cf1;
  Wr_sub[2].a54cf2 = Tp * Wr_sub[2].a44cf2;
  Wr_sub[2].a55cf = 1.0;
  Wr_sub[2].a56cf = 0.0;
  Wr_sub[2].a61cf = (axis3.Ktn * axis3.Kvp * axis3.Kvi * powf(Tp, 2) + axis3.Ktn * axis3.fwm * axis3.Kvi * powf(Tp, 2) + axis3.Dmn * axis3.Kvi * powf(Tp, 2) - axis3.Jmn * axis3.Kvi * Tp) / axis3.Jmn - axis3.Kvi * axis3.Kpp * powf(Tp, 2);
  Wr_sub[2].a62cf = axis3.Ktn * axis3.Kvp * axis3.Kpp * axis3.Kvi * powf(Tp, 2) / axis3.Jmn - Tp * axis3.Kvi * axis3.Kpp;
  Wr_sub[2].a63cf = (axis3.Ktn * axis3.fqs * axis3.Kvi * powf(Tp, 2) + axis3.Ksn * axis3.Kvi * powf(Tp, 2) / axis3.Rgn) / axis3.Jmn;
  Wr_sub[2].a64cf = axis3.Ktn * axis3.fwl * axis3.Kvi * powf(Tp, 2) / axis3.Jmn;
  Wr_sub[2].a65cf = 0.0;
  Wr_sub[2].a66cf = 1.0 - axis3.Ktn * axis3.Kvi * powf(Tp, 2) / axis3.Jmn;
  Wr_sub[2].b1cf = axis3.Kpp * axis3.Kvp * axis3.Ktn * Tp / axis3.Jmn;
  Wr_sub[2].b2cf = Tp * Wr_sub[2].b1cf;
  Wr_sub[2].b3cf = axis3.Kpp * axis3.Kvp * axis3.Ktn * powf(Tp, 2) / (axis3.Jmn * axis3.Rgn);
  Wr_sub[2].b4cf = 0.0;
  Wr_sub[2].b5cf = 0.0;
  Wr_sub[2].b6cf = -axis3.Kpp * axis3.Kvp * axis3.Kvi * axis3.Ktn * powf(Tp, 2) / axis3.Jmn + Tp * axis3.Kpp * axis3.Kvi;
}

void CalcFDTDWrUpdate_QmrefInputType_1st2nd(void)
{ // 20220408 FDTD法適用見直し
  // qm^ref入力型FDTDWrのJlの係数の計算
  // 1軸目
  float Tp_2 = Tp * Tp;
  Wr_sub[0].a11cf = (-axis1.Ktn * axis1.Kvp * Tp - axis1.Ktn * axis1.fwm * Tp - axis1.Dmn * Tp + axis1.Jmn) / axis1.Jmn;
  Wr_sub[0].a12cf = -axis1.Ktn * axis1.Kvp * axis1.Kpp * Tp / axis1.Jmn;
  Wr_sub[0].a13cf = (-axis1.Ktn * axis1.fqs * Tp - axis1.Ksn * Tp / axis1.Rgn) / axis1.Jmn;
  Wr_sub[0].a14cf = -axis1.Ktn * axis1.fwl * Tp / axis1.Jmn;

  Wr_sub[1].a21cf = Tp * Wr_sub[1].a11cf;
  Wr_sub[1].a22cf = Tp * Wr_sub[1].a12cf + 1.0;
  Wr_sub[1].a23cf = Tp * Wr_sub[1].a13cf;
  Wr_sub[1].a24cf = Tp * Wr_sub[1].a14cf;

  Wr_sub[0].a31cf = (-axis1.Ktn * axis1.Kvp * Tp_2 - axis1.Ktn * axis1.fwm * Tp_2 - axis1.Dmn * Tp_2 + axis1.Jmn * Tp) / (axis1.Jmn * axis1.Rgn);
  Wr_sub[0].a32cf = -axis1.Ktn * axis1.Kvp * axis1.Kpp * Tp_2 / (axis1.Jmn * axis1.Rgn);
  Wr_sub[0].a33cf1 = 1.0 + (-axis1.Ktn * axis1.fqs * Tp_2 - axis1.Ksn * Tp_2 / axis1.Rgn) / (axis1.Jmn * axis1.Rgn);
  Wr_sub[0].a34cf1 = -Tp - axis1.Ktn * axis1.fwl * Tp_2 / (axis1.Jmn * axis1.Rgn);

  Wr_sub[0].a61cf = (axis1.Ktn * axis1.Kvp * axis1.Kvi * Tp_2 + axis1.Ktn * axis1.fwm * axis1.Kvi * Tp_2 + axis1.Dmn * axis1.Kvi * Tp_2 - axis1.Jmn * axis1.Kvi * Tp) / axis1.Jmn - axis1.Kvi * axis1.Kpp * Tp_2;
  Wr_sub[0].a62cf = axis1.Ktn * axis1.Kvp * axis1.Kpp * axis1.Kvi * Tp_2 / axis1.Jmn - Tp * axis1.Kvi * axis1.Kpp;
  Wr_sub[0].a63cf = (axis1.Ktn * axis1.fqs * axis1.Kvi * Tp_2 + axis1.Ksn * axis1.Kvi * Tp_2 / axis1.Rgn) / axis1.Jmn;
  Wr_sub[0].a64cf = axis1.Ktn * axis1.fwl * axis1.Kvi * Tp_2 / axis1.Jmn;
  Wr_sub[0].a66cf = 1.0 - axis1.Ktn * axis1.Kvi * Tp_2 / axis1.Jmn;

  Wr_sub[0].b1cf = axis1.Kpp * axis1.Kvp * axis1.Ktn * Tp / axis1.Jmn;
  Wr_sub[0].b3cf = axis1.Kpp * axis1.Kvp * axis1.Ktn * Tp_2 / (axis1.Jmn * axis1.Rgn);
  Wr_sub[0].b6cf = -axis1.Kpp * axis1.Kvp * axis1.Kvi * axis1.Ktn * Tp_2 / axis1.Jmn + Tp * axis1.Kpp * axis1.Kvi;

  // 2軸目
  Wr_sub[1].a11cf = (-axis2.Ktn * axis2.Kvp * Tp - axis2.Ktn * axis2.fwm * Tp - axis2.Dmn * Tp + axis2.Jmn) / axis2.Jmn;
  Wr_sub[1].a12cf = -axis2.Ktn * axis2.Kvp * axis2.Kpp * Tp / axis2.Jmn;
  Wr_sub[1].a13cf = (-axis2.Ktn * axis2.fqs * Tp - axis2.Ksn * Tp / axis2.Rgn) / axis2.Jmn;
  Wr_sub[1].a14cf = -axis2.Ktn * axis2.fwl * Tp / axis2.Jmn;

  Wr_sub[1].a21cf = Tp * Wr_sub[1].a11cf;
  Wr_sub[1].a22cf = Tp * Wr_sub[1].a12cf + 1.0;
  Wr_sub[1].a23cf = Tp * Wr_sub[1].a13cf;
  Wr_sub[1].a24cf = Tp * Wr_sub[1].a14cf;

  Wr_sub[1].a31cf = (-axis2.Ktn * axis2.Kvp * Tp_2 - axis2.Ktn * axis2.fwm * Tp_2 - axis2.Dmn * Tp_2 + axis2.Jmn * Tp) / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a32cf = -axis2.Ktn * axis2.Kvp * axis2.Kpp * Tp_2 / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a33cf1 = 1.0 + (-axis2.Ktn * axis2.fqs * Tp_2 - axis2.Ksn * Tp_2 / axis2.Rgn) / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a34cf1 = -Tp - axis2.Ktn * axis2.fwl * Tp_2 / (axis2.Jmn * axis2.Rgn);

  Wr_sub[1].a61cf = (axis2.Ktn * axis2.Kvp * axis2.Kvi * Tp_2 + axis2.Ktn * axis2.fwm * axis2.Kvi * Tp_2 + axis2.Dmn * axis2.Kvi * Tp_2 - axis2.Jmn * axis2.Kvi * Tp) / axis2.Jmn - axis2.Kvi * axis2.Kpp * Tp_2;
  Wr_sub[1].a62cf = axis2.Ktn * axis2.Kvp * axis2.Kpp * axis2.Kvi * Tp_2 / axis2.Jmn - Tp * axis2.Kvi * axis2.Kpp;
  Wr_sub[1].a63cf = (axis2.Ktn * axis2.fqs * axis2.Kvi * Tp_2 + axis2.Ksn * axis2.Kvi * Tp_2 / axis2.Rgn) / axis2.Jmn;
  Wr_sub[1].a64cf = axis2.Ktn * axis2.fwl * axis2.Kvi * Tp_2 / axis2.Jmn;
  Wr_sub[1].a66cf = 1.0 - axis2.Ktn * axis2.Kvi * Tp_2 / axis2.Jmn;

  Wr_sub[1].b1cf = axis2.Kpp * axis2.Kvp * axis2.Ktn * Tp / axis2.Jmn;
  Wr_sub[1].b2cf = axis2.Kpp * axis2.Kvp * axis2.Ktn * Tp_2 / axis2.Jmn;
  Wr_sub[1].b3cf = axis2.Kpp * axis2.Kvp * axis2.Ktn * Tp_2 / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].b6cf = -axis2.Kpp * axis2.Kvp * axis2.Kvi * axis2.Ktn * Tp_2 / axis2.Jmn + Tp * axis2.Kpp * axis2.Kvi;
}

void CalcFDTDWrUpdate_QmrefInputType_2nd(void)
{ // 20220408 FDTD法適用見直し
  // qm^ref入力型FDTDWrのJlの係数の計算
  float Tp_2 = Tp * Tp;
  // 2軸目
  Wr_sub[1].a11cf = (-axis2.Ktn * axis2.Kvp * Tp - axis2.Ktn * axis2.fwm * Tp - axis2.Dmn * Tp + axis2.Jmn) / axis2.Jmn;
  Wr_sub[1].a12cf = -axis2.Ktn * axis2.Kvp * axis2.Kpp * Tp / axis2.Jmn;
  Wr_sub[1].a13cf = (-axis2.Ktn * axis2.fqs * Tp - axis2.Ksn * Tp / axis2.Rgn) / axis2.Jmn;
  Wr_sub[1].a14cf = -axis2.Ktn * axis2.fwl * Tp / axis2.Jmn;

  Wr_sub[1].a21cf = Tp * Wr_sub[1].a11cf;
  Wr_sub[1].a22cf = Tp * Wr_sub[1].a12cf + 1.0;
  Wr_sub[1].a23cf = Tp * Wr_sub[1].a13cf;
  Wr_sub[1].a24cf = Tp * Wr_sub[1].a14cf;

  Wr_sub[1].a31cf = (-axis2.Ktn * axis2.Kvp * Tp_2 - axis2.Ktn * axis2.fwm * Tp_2 - axis2.Dmn * Tp_2 + axis2.Jmn * Tp) / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a32cf = -axis2.Ktn * axis2.Kvp * axis2.Kpp * Tp_2 / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a33cf1 = 1.0 + (-axis2.Ktn * axis2.fqs * Tp_2 - axis2.Ksn * Tp_2 / axis2.Rgn) / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].a34cf1 = -Tp - axis2.Ktn * axis2.fwl * Tp_2 / (axis2.Jmn * axis2.Rgn);

  Wr_sub[1].a61cf = (axis2.Ktn * axis2.Kvp * axis2.Kvi * Tp_2 + axis2.Ktn * axis2.fwm * axis2.Kvi * Tp_2 + axis2.Dmn * axis2.Kvi * Tp_2 - axis2.Jmn * axis2.Kvi * Tp) / axis2.Jmn - axis2.Kvi * axis2.Kpp * Tp_2;
  Wr_sub[1].a62cf = axis2.Ktn * axis2.Kvp * axis2.Kpp * axis2.Kvi * Tp_2 / axis2.Jmn - Tp * axis2.Kvi * axis2.Kpp;
  Wr_sub[1].a63cf = (axis2.Ktn * axis2.fqs * axis2.Kvi * Tp_2 + axis2.Ksn * axis2.Kvi * Tp_2 / axis2.Rgn) / axis2.Jmn;
  Wr_sub[1].a64cf = axis2.Ktn * axis2.fwl * axis2.Kvi * Tp_2 / axis2.Jmn;
  Wr_sub[1].a66cf = 1.0 - axis2.Ktn * axis2.Kvi * Tp_2 / axis2.Jmn;

  Wr_sub[1].b1cf = axis2.Kpp * axis2.Kvp * axis2.Ktn * Tp / axis2.Jmn;
  Wr_sub[1].b2cf = axis2.Kpp * axis2.Kvp * axis2.Ktn * Tp_2 / axis2.Jmn;
  Wr_sub[1].b3cf = axis2.Kpp * axis2.Kvp * axis2.Ktn * Tp_2 / (axis2.Jmn * axis2.Rgn);
  Wr_sub[1].b6cf = -axis2.Kpp * axis2.Kvp * axis2.Kvi * axis2.Ktn * Tp_2 / axis2.Jmn + Tp * axis2.Kpp * axis2.Kvi;
}

volatile int Wr_Throth_check = 0;
void CalcFDTDWr_WmcmdInputType(Robot *robo)
{
  // 状態変数の定義
  static float wm_Z[3] = {0}, qm_Z[3] = {0}, qs_Z[3] = {0}, wl_Z[3] = {0}, ql_Z[3] = {0}, n_Z[3] = {0}, m_Z[3] = {0};
  static float wm_Z1[3] = {0}, qm_Z1[3] = {0}, qs_Z1[3] = {0}, wl_Z1[3] = {0}, ql_Z1[3] = {0}, n_Z1[3] = {0}, m_Z1[3] = {0};

  if (robo->BDN == BDN0)
  {
    // 状態量の計算
    wm_Z[0] = Wr_DPD[0].a11cf * wm_Z1[0] + Wr_DPD[0].a12cf * qm_Z1[0] + Wr_DPD[0].a13cf * qs_Z1[0] + Wr_DPD[0].a14cf * wl_Z1[0] + Wr_DPD[0].a15cf * ql_Z1[0] + Wr_DPD[0].a16cf * n_Z1[0] + Wr_DPD[0].a17cf * m_Z1[0] + Wr_DPD[0].b1cf * robo->wm_cmd;
    qm_Z[0] = Wr_DPD[0].a21cf * wm_Z1[0] + Wr_DPD[0].a22cf * qm_Z1[0] + Wr_DPD[0].a23cf * qs_Z1[0] + Wr_DPD[0].a24cf * wl_Z1[0] + Wr_DPD[0].a25cf * ql_Z1[0] + Wr_DPD[0].a26cf * n_Z1[0] + Wr_DPD[0].a27cf * m_Z1[0] + Wr_DPD[0].b2cf * robo->wm_cmd;
    qs_Z[0] = Wr_DPD[0].a31cf * wm_Z1[0] + Wr_DPD[0].a32cf * qm_Z1[0] + (Wr_DPD[0].a33cf1 + Wr_DPD[0].a33cf2 / robo->Jl_calc) * qs_Z1[0] + (Wr_DPD[0].a34cf1 + Wr_DPD[0].a34cf2 / robo->Jl_calc) * wl_Z1[0] + Wr_DPD[0].a35cf * ql_Z1[0] + Wr_DPD[0].a36cf * n_Z1[0] + Wr_DPD[0].a37cf * m_Z1[0] + Wr_DPD[0].b3cf * robo->wm_cmd;
    wl_Z[0] = Wr_DPD[0].a41cf * wm_Z1[0] + Wr_DPD[0].a42cf * qm_Z1[0] + Wr_DPD[0].a43cf / robo->Jl_calc * qs_Z1[0] + (Wr_DPD[0].a44cf1 + Wr_DPD[0].a44cf2 / robo->Jl_calc) * wl_Z1[0] + Wr_DPD[0].a45cf * ql_Z1[0] + Wr_DPD[0].a46cf * n_Z1[0] + Wr_DPD[0].a47cf * m_Z1[0] + Wr_DPD[0].b4cf * robo->wm_cmd;
    ql_Z[0] = Wr_DPD[0].a51cf * wm_Z1[0] + Wr_DPD[0].a52cf * qm_Z1[0] + Wr_DPD[0].a53cf / robo->Jl_calc * qs_Z1[0] + (Wr_DPD[0].a54cf1 + Wr_DPD[0].a54cf2 / robo->Jl_calc) * wl_Z1[0] + Wr_DPD[0].a55cf * ql_Z1[0] + Wr_DPD[0].a56cf * n_Z1[0] + Wr_DPD[0].a57cf * m_Z1[0] + Wr_DPD[0].b5cf * robo->wm_cmd;
    n_Z[0] = Wr_DPD[0].a61cf * wm_Z1[0] + Wr_DPD[0].a62cf * qm_Z1[0] + Wr_DPD[0].a63cf * qs_Z1[0] + Wr_DPD[0].a64cf * wl_Z1[0] + Wr_DPD[0].a65cf * ql_Z1[0] + Wr_DPD[0].a66cf * n_Z1[0] + Wr_DPD[0].a67cf * m_Z1[0] + Wr_DPD[0].b6cf * robo->wm_cmd;
    m_Z[0] = Wr_DPD[0].a71cf * wm_Z1[0] + Wr_DPD[0].a72cf * qm_Z1[0] + Wr_DPD[0].a73cf * qs_Z1[0] + Wr_DPD[0].a74cf * wl_Z1[0] + Wr_DPD[0].a75cf * ql_Z1[0] + Wr_DPD[0].a76cf * n_Z1[0] + Wr_DPD[0].a77cf * m_Z1[0] + Wr_DPD[0].b7cf * robo->wm_cmd;

    // 状態量の更新axis1.
    wm_Z1[0] = wm_Z[0];
    qm_Z1[0] = qm_Z[0];
    qs_Z1[0] = qs_Z[0];
    wl_Z1[0] = wl_Z[0];
    ql_Z1[0] = ql_Z[0];
    n_Z1[0] = n_Z[0];
    m_Z1[0] = m_Z[0];

    // 計算結果の代入
    robo->ql_calc = robo->theta_rl_init + ql_Z[0];
    robo->wl_calc = wl_Z[0];
    robo->al_calc = (robo->Ksn * qs_Z[0] - robo->Dln * wl_Z[0]) / robo->Jl_calc;
    robo->wm_calc = wm_Z[0];
  }
  else if (robo->BDN == BDN1)
  {
    // 状態量の計算
    wm_Z[1] = Wr_DPD[1].a11cf * wm_Z1[1] + Wr_DPD[1].a12cf * qm_Z1[1] + Wr_DPD[1].a13cf * qs_Z1[1] + Wr_DPD[1].a14cf * wl_Z1[1] + Wr_DPD[1].a15cf * ql_Z1[1] + Wr_DPD[1].a16cf * n_Z1[1] + Wr_DPD[1].a17cf * m_Z1[1] + Wr_DPD[1].b1cf * robo->wm_cmd;
    qm_Z[1] = Wr_DPD[1].a21cf * wm_Z1[1] + Wr_DPD[1].a22cf * qm_Z1[1] + Wr_DPD[1].a23cf * qs_Z1[1] + Wr_DPD[1].a24cf * wl_Z1[1] + Wr_DPD[1].a25cf * ql_Z1[1] + Wr_DPD[1].a26cf * n_Z1[1] + Wr_DPD[1].a27cf * m_Z1[1] + Wr_DPD[1].b2cf * robo->wm_cmd;
    qs_Z[1] = Wr_DPD[1].a31cf * wm_Z1[1] + Wr_DPD[1].a32cf * qm_Z1[1] + (Wr_DPD[1].a33cf1 + Wr_DPD[1].a33cf2 / robo->Jl_calc) * qs_Z1[1] + (Wr_DPD[1].a34cf1 + Wr_DPD[1].a34cf2 / robo->Jl_calc) * wl_Z1[1] + Wr_DPD[1].a35cf * ql_Z1[1] + Wr_DPD[1].a36cf * n_Z1[1] + Wr_DPD[1].a37cf * m_Z1[1] + Wr_DPD[1].b3cf * robo->wm_cmd;
    wl_Z[1] = Wr_DPD[1].a41cf * wm_Z1[1] + Wr_DPD[1].a42cf * qm_Z1[1] + Wr_DPD[1].a43cf / robo->Jl_calc * qs_Z1[1] + (Wr_DPD[1].a44cf1 + Wr_DPD[1].a44cf2 / robo->Jl_calc) * wl_Z1[1] + Wr_DPD[1].a45cf * ql_Z1[1] + Wr_DPD[1].a46cf * n_Z1[1] + Wr_DPD[1].a47cf * m_Z1[1] + Wr_DPD[1].b4cf * robo->wm_cmd;
    ql_Z[1] = Wr_DPD[1].a51cf * wm_Z1[1] + Wr_DPD[1].a52cf * qm_Z1[1] + Wr_DPD[1].a53cf / robo->Jl_calc * qs_Z1[1] + (Wr_DPD[1].a54cf1 + Wr_DPD[1].a54cf2 / robo->Jl_calc) * wl_Z1[1] + Wr_DPD[1].a55cf * ql_Z1[1] + Wr_DPD[1].a56cf * n_Z1[1] + Wr_DPD[1].a57cf * m_Z1[1] + Wr_DPD[1].b5cf * robo->wm_cmd;
    n_Z[1] = Wr_DPD[1].a61cf * wm_Z1[1] + Wr_DPD[1].a62cf * qm_Z1[1] + Wr_DPD[1].a63cf * qs_Z1[1] + Wr_DPD[1].a64cf * wl_Z1[1] + Wr_DPD[1].a65cf * ql_Z1[1] + Wr_DPD[1].a66cf * n_Z1[1] + Wr_DPD[1].a67cf * m_Z1[1] + Wr_DPD[1].b6cf * robo->wm_cmd;
    m_Z[1] = Wr_DPD[1].a71cf * wm_Z1[1] + Wr_DPD[1].a72cf * qm_Z1[1] + Wr_DPD[1].a73cf * qs_Z1[1] + Wr_DPD[1].a74cf * wl_Z1[1] + Wr_DPD[1].a75cf * ql_Z1[1] + Wr_DPD[1].a76cf * n_Z1[1] + Wr_DPD[1].a77cf * m_Z1[1] + Wr_DPD[1].b7cf * robo->wm_cmd;

    // 状態量の更新
    wm_Z1[1] = wm_Z[1];
    qm_Z1[1] = qm_Z[1];
    qs_Z1[1] = qs_Z[1];
    wl_Z1[1] = wl_Z[1];
    ql_Z1[1] = ql_Z[1];
    n_Z1[1] = n_Z[1];
    m_Z1[1] = m_Z[1];

    // 計算結果の代入
    robo->ql_calc = robo->theta_rl_init + ql_Z[1];
    robo->wl_calc = wl_Z[1];
    robo->al_calc = (robo->Ksn * qs_Z[1] - robo->Dln * wl_Z[1]) / robo->Jl_calc;
    robo->wm_calc = wm_Z[1];
  }
  else if (robo->BDN == BDN2)
  {
    // 状態量の計算
    wm_Z[2] = Wr_DPD[2].a11cf * wm_Z1[2] + Wr_DPD[2].a12cf * qm_Z1[2] + Wr_DPD[2].a13cf * qs_Z1[2] + Wr_DPD[2].a14cf * wl_Z1[2] + Wr_DPD[2].a15cf * ql_Z1[2] + Wr_DPD[2].a16cf * n_Z1[2] + Wr_DPD[2].a17cf * m_Z1[2] + Wr_DPD[2].b1cf * robo->wm_cmd;
    qm_Z[2] = Wr_DPD[2].a21cf * wm_Z1[2] + Wr_DPD[2].a22cf * qm_Z1[2] + Wr_DPD[2].a23cf * qs_Z1[2] + Wr_DPD[2].a24cf * wl_Z1[2] + Wr_DPD[2].a25cf * ql_Z1[2] + Wr_DPD[2].a26cf * n_Z1[2] + Wr_DPD[2].a27cf * m_Z1[2] + Wr_DPD[2].b2cf * robo->wm_cmd;
    qs_Z[2] = Wr_DPD[2].a31cf * wm_Z1[2] + Wr_DPD[2].a32cf * qm_Z1[2] + (Wr_DPD[2].a33cf1 + Wr_DPD[2].a33cf2 / robo->Jl_calc) * qs_Z1[2] + (Wr_DPD[2].a34cf1 + Wr_DPD[2].a34cf2 / robo->Jl_calc) * wl_Z1[2] + Wr_DPD[2].a35cf * ql_Z1[2] + Wr_DPD[2].a36cf * n_Z1[2] + Wr_DPD[2].a37cf * m_Z1[2] + Wr_DPD[2].b3cf * robo->wm_cmd;
    wl_Z[2] = Wr_DPD[2].a41cf * wm_Z1[2] + Wr_DPD[2].a42cf * qm_Z1[2] + Wr_DPD[2].a43cf / robo->Jl_calc * qs_Z1[2] + (Wr_DPD[2].a44cf1 + Wr_DPD[2].a44cf2 / robo->Jl_calc) * wl_Z1[2] + Wr_DPD[2].a45cf * ql_Z1[2] + Wr_DPD[2].a46cf * n_Z1[2] + Wr_DPD[2].a47cf * m_Z1[2] + Wr_DPD[2].b4cf * robo->wm_cmd;
    ql_Z[2] = Wr_DPD[2].a51cf * wm_Z1[2] + Wr_DPD[2].a52cf * qm_Z1[2] + Wr_DPD[2].a53cf / robo->Jl_calc * qs_Z1[2] + (Wr_DPD[2].a54cf1 + Wr_DPD[2].a54cf2 / robo->Jl_calc) * wl_Z1[2] + Wr_DPD[2].a55cf * ql_Z1[2] + Wr_DPD[2].a56cf * n_Z1[2] + Wr_DPD[2].a57cf * m_Z1[2] + Wr_DPD[2].b5cf * robo->wm_cmd;
    n_Z[2] = Wr_DPD[2].a61cf * wm_Z1[2] + Wr_DPD[2].a62cf * qm_Z1[2] + Wr_DPD[2].a63cf * qs_Z1[2] + Wr_DPD[2].a64cf * wl_Z1[2] + Wr_DPD[2].a65cf * ql_Z1[2] + Wr_DPD[2].a66cf * n_Z1[2] + Wr_DPD[2].a67cf * m_Z1[2] + Wr_DPD[2].b6cf * robo->wm_cmd;
    m_Z[2] = Wr_DPD[2].a71cf * wm_Z1[2] + Wr_DPD[2].a72cf * qm_Z1[2] + Wr_DPD[2].a73cf * qs_Z1[2] + Wr_DPD[2].a74cf * wl_Z1[2] + Wr_DPD[2].a75cf * ql_Z1[2] + Wr_DPD[2].a76cf * n_Z1[2] + Wr_DPD[2].a77cf * m_Z1[2] + Wr_DPD[2].b7cf * robo->wm_cmd;

    // 状態量の更新
    wm_Z1[2] = wm_Z[2];
    qm_Z1[2] = qm_Z[2];
    qs_Z1[2] = qs_Z[2];
    wl_Z1[2] = wl_Z[2];
    ql_Z1[2] = ql_Z[2];
    n_Z1[2] = n_Z[2];
    m_Z1[2] = m_Z[2];

    // 計算結果の代入
    robo->ql_calc = robo->theta_rl_init + ql_Z[2];
    robo->wl_calc = wl_Z[2];
    robo->al_calc = (robo->Ksn * qs_Z[2] - robo->Dln * wl_Z[2]) / robo->Jl_calc;
    robo->wm_calc = wm_Z[2];
  }
  else
  {
    // ボード番号認識できない場合
    Wr_Throth_check++;
  }
}

void CalcFDTDWrInit_WmcmdInputType(Robot *robo)
{
  float Tp2 = powf(Tp, 2);

  if (robo->BDN == BDN0)
  {
    // 20220408 FDTD法適用見直し
    // wm_cmd入力型FDTDWrのJlの係数の計算
    // 1軸目
    Wr_DPD[0].a11cf  = ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[0].a12cf  = -robo->Ktn * robo->Kvp * robo->Kpp * Tp / robo->Jmn;
    Wr_DPD[0].a13cf  = (-robo->Ktn * robo->fqs * Tp - robo->Ksn * Tp / robo->Rgn) / robo->Jmn;
    Wr_DPD[0].a14cf  = -robo->Ktn * robo->fwl * Tp / robo->Jmn;
    Wr_DPD[0].a15cf  = 0.0;
    Wr_DPD[0].a16cf  = robo->Ktn * Tp / robo->Jmn;
    Wr_DPD[0].a17cf  = Tp * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[0].a21cf  = (Tp * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)))) / robo->Jmn;
    Wr_DPD[0].a22cf  = 1 - (robo->Ktn * robo->Kvp * robo->Kpp * Tp2) / robo->Jmn;
    Wr_DPD[0].a23cf  = -((robo->Ktn * robo->fqs * robo->Rgn + robo->Ksn) * Tp2) / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a24cf  = -robo->Ktn * robo->fwl * Tp2 / robo->Jmn;
    Wr_DPD[0].a25cf  = 0.0;
    Wr_DPD[0].a26cf  = robo->Ktn * Tp2 / robo->Jmn;
    Wr_DPD[0].a27cf  = Tp2 * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[0].a31cf  = (Tp / robo->Rgn) * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[0].a32cf  = -robo->Ktn * robo->Kvp * robo->Kpp * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a33cf1 = 1.0 + (Tp2 * (robo->Ksn / robo->Rgn + robo->fqs * robo->Ktn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a33cf2 = -Tp2 * robo->Ksn;
    Wr_DPD[0].a34cf1 = -Tp - robo->Ktn * robo->fwl * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a34cf2 = Tp2 * robo->Dln;
    Wr_DPD[0].a35cf  = 0.0;
    Wr_DPD[0].a36cf  = robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a37cf  = robo->Kvp * robo->Kpp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a41cf  = 0.0;
    Wr_DPD[0].a42cf  = 0.0;
    Wr_DPD[0].a43cf  = Tp * robo->Ksn;
    Wr_DPD[0].a44cf1 = 1.0;
    Wr_DPD[0].a44cf2 = -Tp * robo->Dln;
    Wr_DPD[0].a45cf  = 0.0;
    Wr_DPD[0].a46cf  = 0.0;
    Wr_DPD[0].a47cf  = 0.0;
    Wr_DPD[0].a51cf  = 0.0;
    Wr_DPD[0].a52cf  = 0.0;
    Wr_DPD[0].a53cf  = Tp2 * robo->Ksn;
    Wr_DPD[0].a54cf1 = Tp;
    Wr_DPD[0].a54cf2 = -Tp2 * robo->Dln;
    Wr_DPD[0].a55cf  = 1.0;
    Wr_DPD[0].a56cf  = 0.0;
    Wr_DPD[0].a57cf  = 0.0;
    Wr_DPD[0].a61cf  = ((1 + robo->Kfb) * robo->Kvi * Tp * (-robo->Jmn + (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)) * Tp)) / robo->Jmn;
    Wr_DPD[0].a62cf  = (robo->Kpp * robo->Kvi * Tp * (-robo->Jmn + (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[0].a63cf  = (Tp2 * (1 + robo->Kfb) * robo->Kvi * (robo->Ksn + robo->fqs * robo->Ktn * robo->Rgn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a64cf  = (robo->fwl * (1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[0].a65cf  = 0;
    Wr_DPD[0].a66cf  = 1 - ((1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[0].a67cf  = (robo->Kpp * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[0].a71cf  = 0;
    Wr_DPD[0].a72cf  = 0;
    Wr_DPD[0].a73cf  = 0;
    Wr_DPD[0].a74cf  = 0;
    Wr_DPD[0].a75cf  = 0;
    Wr_DPD[0].a76cf  = 0;
    Wr_DPD[0].a77cf  = 1;
    Wr_DPD[0].b1cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp / robo->Jmn;
    Wr_DPD[0].b2cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / robo->Jmn;
    Wr_DPD[0].b3cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].b4cf   = 0.0;
    Wr_DPD[0].b5cf   = 0.0;
    Wr_DPD[0].b6cf   = (robo->Kff * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kfb * Tp)) / robo->Jmn;
    Wr_DPD[0].b7cf   = Tp;
  }
  else if (robo->BDN == BDN1)
  {
    // 2軸目
    Wr_DPD[1].a11cf  = ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[1].a12cf  = -robo->Ktn * robo->Kvp * robo->Kpp * Tp / robo->Jmn;
    Wr_DPD[1].a13cf  = (-robo->Ktn * robo->fqs * Tp - robo->Ksn * Tp / robo->Rgn) / robo->Jmn;
    Wr_DPD[1].a14cf  = -robo->Ktn * robo->fwl * Tp / robo->Jmn;
    Wr_DPD[1].a15cf  = 0.0;
    Wr_DPD[1].a16cf  = robo->Ktn * Tp / robo->Jmn;
    Wr_DPD[1].a17cf  = Tp * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[1].a21cf  = (Tp * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)))) / robo->Jmn;
    Wr_DPD[1].a22cf  = 1 - (robo->Ktn * robo->Kvp * robo->Kpp * Tp2) / robo->Jmn;
    Wr_DPD[1].a23cf  = -((robo->Ktn * robo->fqs * robo->Rgn + robo->Ksn) * Tp2) / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a24cf  = -robo->Ktn * robo->fwl * Tp2 / robo->Jmn;
    Wr_DPD[1].a25cf  = 0.0;
    Wr_DPD[1].a26cf  = robo->Ktn * Tp2 / robo->Jmn;
    Wr_DPD[1].a27cf  = Tp2 * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[1].a31cf  = (Tp / robo->Rgn) * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[1].a32cf  = -robo->Ktn * robo->Kvp * robo->Kpp * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a33cf1 = 1.0 + (Tp2 * (robo->Ksn / robo->Rgn + robo->fqs * robo->Ktn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a33cf2 = -Tp2 * robo->Ksn;
    Wr_DPD[1].a34cf1 = -Tp - robo->Ktn * robo->fwl * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a34cf2 = Tp2 * robo->Dln;
    Wr_DPD[1].a35cf  = 0.0;
    Wr_DPD[1].a36cf  = robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a37cf  = robo->Kvp * robo->Kpp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a41cf  = 0.0;
    Wr_DPD[1].a42cf  = 0.0;
    Wr_DPD[1].a43cf  = Tp * robo->Ksn;
    Wr_DPD[1].a44cf1 = 1.0;
    Wr_DPD[1].a44cf2 = -Tp * robo->Dln;
    Wr_DPD[1].a45cf  = 0.0;
    Wr_DPD[1].a46cf  = 0.0;
    Wr_DPD[1].a47cf  = 0.0;
    Wr_DPD[1].a51cf  = 0.0;
    Wr_DPD[1].a52cf  = 0.0;
    Wr_DPD[1].a53cf  = Tp2 * robo->Ksn;
    Wr_DPD[1].a54cf1 = Tp;
    Wr_DPD[1].a54cf2 = -Tp2 * robo->Dln;
    Wr_DPD[1].a55cf  = 1.0;
    Wr_DPD[1].a56cf  = 0.0;
    Wr_DPD[1].a57cf  = 0.0;
    Wr_DPD[1].a61cf  = ((1 + robo->Kfb) * robo->Kvi * Tp * (-robo->Jmn + (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)) * Tp)) / robo->Jmn;
    Wr_DPD[1].a62cf  = (robo->Kpp * robo->Kvi * Tp * (-robo->Jmn + (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[1].a63cf  = (Tp2 * (1 + robo->Kfb) * robo->Kvi * (robo->Ksn + robo->fqs * robo->Ktn * robo->Rgn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a64cf  = (robo->fwl * (1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[1].a65cf  = 0;
    Wr_DPD[1].a66cf  = 1 - ((1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[1].a67cf  = (robo->Kpp * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[1].a71cf  = 0;
    Wr_DPD[1].a72cf  = 0;
    Wr_DPD[1].a73cf  = 0;
    Wr_DPD[1].a74cf  = 0;
    Wr_DPD[1].a75cf  = 0;
    Wr_DPD[1].a76cf  = 0;
    Wr_DPD[1].a77cf  = 1;
    Wr_DPD[1].b1cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp / robo->Jmn;
    Wr_DPD[1].b2cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / robo->Jmn;
    Wr_DPD[1].b3cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].b4cf   = 0.0;
    Wr_DPD[1].b5cf   = 0.0;
    Wr_DPD[1].b6cf   = (robo->Kff * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kfb * Tp)) / robo->Jmn;
    Wr_DPD[1].b7cf   = Tp;
  }
  else if (robo->BDN == BDN2)
  {
    // 3軸目
    Wr_DPD[2].a11cf  = ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[2].a12cf  = -robo->Ktn * robo->Kvp * robo->Kpp * Tp / robo->Jmn;
    Wr_DPD[2].a13cf  = (-robo->Ktn * robo->fqs * Tp - robo->Ksn * Tp / robo->Rgn) / robo->Jmn;
    Wr_DPD[2].a14cf  = -robo->Ktn * robo->fwl * Tp / robo->Jmn;
    Wr_DPD[2].a15cf  = 0.0;
    Wr_DPD[2].a16cf  = robo->Ktn * Tp / robo->Jmn;
    Wr_DPD[2].a17cf  = Tp * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[2].a21cf  = (Tp * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)))) / robo->Jmn;
    Wr_DPD[2].a22cf  = 1 - (robo->Ktn * robo->Kvp * robo->Kpp * Tp2) / robo->Jmn;
    Wr_DPD[2].a23cf  = -((robo->Ktn * robo->fqs * robo->Rgn + robo->Ksn) * Tp2) / (robo->Jmn * robo->Rgn);
    Wr_DPD[2].a24cf  = -robo->Ktn * robo->fwl * Tp2 / robo->Jmn;
    Wr_DPD[2].a25cf  = 0.0;
    Wr_DPD[2].a26cf  = robo->Ktn * Tp2 / robo->Jmn;
    Wr_DPD[2].a27cf  = Tp2 * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[2].a31cf  = (Tp / robo->Rgn) * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[2].a32cf  = -robo->Ktn * robo->Kvp * robo->Kpp * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[2].a33cf1 = 1.0 + (Tp2 * (robo->Ksn / robo->Rgn + robo->fqs * robo->Ktn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[2].a33cf2 = -Tp2 * robo->Ksn;
    Wr_DPD[2].a34cf1 = -Tp - robo->Ktn * robo->fwl * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[2].a34cf2 = Tp2 * robo->Dln;
    Wr_DPD[2].a35cf  = 0.0;
    Wr_DPD[2].a36cf  = robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[2].a37cf  = robo->Kvp * robo->Kpp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[2].a41cf  = 0.0;
    Wr_DPD[2].a42cf  = 0.0;
    Wr_DPD[2].a43cf  = Tp * robo->Ksn;
    Wr_DPD[2].a44cf1 = 1.0;
    Wr_DPD[2].a44cf2 = -Tp * robo->Dln;
    Wr_DPD[2].a45cf  = 0.0;
    Wr_DPD[2].a46cf  = 0.0;
    Wr_DPD[2].a47cf  = 0.0;
    Wr_DPD[2].a51cf  = 0.0;
    Wr_DPD[2].a52cf  = 0.0;
    Wr_DPD[2].a53cf  = Tp2 * robo->Ksn;
    Wr_DPD[2].a54cf1 = Tp;
    Wr_DPD[2].a54cf2 = -Tp2 * robo->Dln;
    Wr_DPD[2].a55cf  = 1.0;
    Wr_DPD[2].a56cf  = 0.0;
    Wr_DPD[2].a57cf  = 0.0;
    Wr_DPD[2].a61cf  = ((1 + robo->Kfb) * robo->Kvi * Tp * (-robo->Jmn + (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)) * Tp)) / robo->Jmn;
    Wr_DPD[2].a62cf  = (robo->Kpp * robo->Kvi * Tp * (-robo->Jmn + (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[2].a63cf  = (Tp2 * (1 + robo->Kfb) * robo->Kvi * (robo->Ksn + robo->fqs * robo->Ktn * robo->Rgn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[2].a64cf  = (robo->fwl * (1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[2].a65cf  = 0;
    Wr_DPD[2].a66cf  = 1 - ((1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[2].a67cf  = (robo->Kpp * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[2].a71cf  = 0;
    Wr_DPD[2].a72cf  = 0;
    Wr_DPD[2].a73cf  = 0;
    Wr_DPD[2].a74cf  = 0;
    Wr_DPD[2].a75cf  = 0;
    Wr_DPD[2].a76cf  = 0;
    Wr_DPD[2].a77cf  = 1;
    Wr_DPD[2].b1cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp / robo->Jmn;
    Wr_DPD[2].b2cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / robo->Jmn;
    Wr_DPD[2].b3cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[2].b4cf   = 0.0;
    Wr_DPD[2].b5cf   = 0.0;
    Wr_DPD[2].b6cf   = (robo->Kff * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kfb * Tp)) / robo->Jmn;
    Wr_DPD[2].b7cf   = Tp;
  }
  else
  {
    // ボード番号認識できない場合
    Wr_Throth_check++;
  }
  }

void CalcFDTDWrUpdate_WmcmdInputType_1st2nd(Robot *robo)
{
  float Tp2 = Tp * Tp;
  if (robo->BDN == BDN0)
  {
    // 1軸目
    Wr_DPD[0].a11cf  = ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[0].a12cf  = -robo->Ktn * robo->Kvp * robo->Kpp * Tp / robo->Jmn;
    Wr_DPD[0].a13cf  = (-robo->Ktn * robo->fqs * Tp - robo->Ksn * Tp / robo->Rgn) / robo->Jmn;
    Wr_DPD[0].a14cf  = -robo->Ktn * robo->fwl * Tp / robo->Jmn;
    Wr_DPD[0].a17cf  = Tp * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[0].a21cf  = (Tp * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)))) / robo->Jmn;
    Wr_DPD[0].a22cf  = 1 - (robo->Ktn * robo->Kvp * robo->Kpp * Tp2) / robo->Jmn;
    Wr_DPD[0].a23cf  = -((robo->Ktn * robo->fqs * robo->Rgn + robo->Ksn) * Tp2) / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a24cf  = -robo->Ktn * robo->fwl * Tp2 / robo->Jmn;
    Wr_DPD[0].a27cf  = Tp2 * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[0].a31cf  = (Tp / robo->Rgn) * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[0].a32cf  = -robo->Ktn * robo->Kvp * robo->Kpp * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a33cf1 = 1.0 + (Tp2 * (robo->Ksn / robo->Rgn + robo->fqs * robo->Ktn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a34cf1 = -Tp - robo->Ktn * robo->fwl * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a37cf  = robo->Kvp * robo->Kpp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a61cf  = ((1 + robo->Kfb) * robo->Kvi * Tp * (-robo->Jmn + (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)) * Tp)) / robo->Jmn;
    Wr_DPD[0].a62cf  = (robo->Kpp * robo->Kvi * Tp * (-robo->Jmn + (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[0].a63cf  = (Tp2 * (1 + robo->Kfb) * robo->Kvi * (robo->Ksn + robo->fqs * robo->Ktn * robo->Rgn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].a64cf  = (robo->fwl * (1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[0].a66cf  = 1 - ((1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[0].a67cf  = (robo->Kpp * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[0].b1cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp / robo->Jmn;
    Wr_DPD[0].b2cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / robo->Jmn;
    Wr_DPD[0].b3cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[0].b6cf   = (robo->Kff * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kfb * Tp)) / robo->Jmn;
  }
  else if (robo->BDN == BDN1)
  {
    // 2軸目
    Wr_DPD[1].a11cf  = ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[1].a12cf  = -robo->Ktn * robo->Kvp * robo->Kpp * Tp / robo->Jmn;
    Wr_DPD[1].a13cf  = (-robo->Ktn * robo->fqs * Tp - robo->Ksn * Tp / robo->Rgn) / robo->Jmn;
    Wr_DPD[1].a14cf  = -robo->Ktn * robo->fwl * Tp / robo->Jmn;
    Wr_DPD[1].a17cf  = Tp * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[1].a21cf  = (Tp * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)))) / robo->Jmn;
    Wr_DPD[1].a22cf  = 1 - (robo->Ktn * robo->Kvp * robo->Kpp * Tp2) / robo->Jmn;
    Wr_DPD[1].a23cf  = -((robo->Ktn * robo->fqs * robo->Rgn + robo->Ksn) * Tp2) / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a24cf  = -robo->Ktn * robo->fwl * Tp2 / robo->Jmn;
    Wr_DPD[1].a27cf  = Tp2 * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[1].a31cf  = (Tp / robo->Rgn) * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[1].a32cf  = -robo->Ktn * robo->Kvp * robo->Kpp * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a33cf1 = 1.0 + (Tp2 * (robo->Ksn / robo->Rgn + robo->fqs * robo->Ktn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a34cf1 = -Tp - robo->Ktn * robo->fwl * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a37cf  = robo->Kvp * robo->Kpp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a61cf  = ((1 + robo->Kfb) * robo->Kvi * Tp * (-robo->Jmn + (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)) * Tp)) / robo->Jmn;
    Wr_DPD[1].a62cf  = (robo->Kpp * robo->Kvi * Tp * (-robo->Jmn + (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[1].a63cf  = (Tp2 * (1 + robo->Kfb) * robo->Kvi * (robo->Ksn + robo->fqs * robo->Ktn * robo->Rgn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a64cf  = (robo->fwl * (1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[1].a66cf  = 1 - ((1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[1].a67cf  = (robo->Kpp * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[1].b1cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp / robo->Jmn;
    Wr_DPD[1].b2cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / robo->Jmn;
    Wr_DPD[1].b3cf   = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].b6cf   = (robo->Kff * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kfb * Tp)) / robo->Jmn;
  }
  else if (robo->BDN == BDN2)
  {
    // BDN2を代えることは、ないんですね
  }
  else
  {
    // ボード番号認識できない場合
    Wr_Throth_check++;
  }
}

void CalcFDTDWrUpdate_WmcmdInputType_2nd(Robot *robo)
{
  float Tp2 = powf(Tp, 2);
  if (robo->BDN == BDN0)
  {
    // この時は、2軸だけを変えたい
  }
  else if (robo->BDN == BDN1)
  {
    // 2軸目
    Wr_DPD[1].a11cf = ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[1].a12cf = -robo->Ktn * robo->Kvp * robo->Kpp * Tp / robo->Jmn;
    Wr_DPD[1].a13cf = (-robo->Ktn * robo->fqs * Tp - robo->Ksn * Tp / robo->Rgn) / robo->Jmn;
    Wr_DPD[1].a14cf = -robo->Ktn * robo->fwl * Tp / robo->Jmn;
    Wr_DPD[1].a17cf = Tp * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[1].a21cf = (Tp * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)))) / robo->Jmn;
    Wr_DPD[1].a22cf = 1 - (robo->Ktn * robo->Kvp * robo->Kpp * Tp2) / robo->Jmn;
    Wr_DPD[1].a23cf = -((robo->Ktn * robo->fqs * robo->Rgn + robo->Ksn) * Tp2) / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a24cf = -robo->Ktn * robo->fwl * Tp2 / robo->Jmn;
    Wr_DPD[1].a27cf = Tp2 * robo->Ktn * robo->Kvp * robo->Kpp / robo->Jmn;
    Wr_DPD[1].a31cf = (Tp / robo->Rgn) * ((robo->Jmn) - Tp * (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp))) / robo->Jmn;
    Wr_DPD[1].a32cf = -robo->Ktn * robo->Kvp * robo->Kpp * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a33cf1 = 1.0 + (Tp2 * (robo->Ksn / robo->Rgn + robo->fqs * robo->Ktn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a34cf1 = -Tp - robo->Ktn * robo->fwl * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a37cf = robo->Kvp * robo->Kpp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a61cf = ((1 + robo->Kfb) * robo->Kvi * Tp * (-robo->Jmn + (robo->Dmn + robo->Ktn * (robo->fwm + robo->Kvp + robo->Kfb * robo->Kvp)) * Tp)) / robo->Jmn;
    Wr_DPD[1].a62cf = (robo->Kpp * robo->Kvi * Tp * (-robo->Jmn + (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[1].a63cf = (Tp2 * (1 + robo->Kfb) * robo->Kvi * (robo->Ksn + robo->fqs * robo->Ktn * robo->Rgn)) / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].a64cf = (robo->fwl * (1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[1].a66cf = 1 - ((1 + robo->Kfb) * robo->Ktn * robo->Kvi * Tp2) / robo->Jmn;
    Wr_DPD[1].a67cf = (robo->Kpp * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kvp * Tp)) / robo->Jmn;
    Wr_DPD[1].b1cf = robo->Kff * robo->Kvp * robo->Ktn * Tp / robo->Jmn;
    Wr_DPD[1].b2cf = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / robo->Jmn;
    Wr_DPD[1].b3cf = robo->Kff * robo->Kvp * robo->Ktn * Tp2 / (robo->Jmn * robo->Rgn);
    Wr_DPD[1].b6cf = (robo->Kff * robo->Kvi * Tp * (robo->Jmn - (1 + robo->Kfb) * robo->Ktn * robo->Kfb * Tp)) / robo->Jmn;
  }
  else if (robo->BDN == BDN2)
  {
    // BDN2を代えることは、ないんですね
  }
  else
  {
    // ボード番号認識できない場合
    Wr_Throth_check++;
  }
}

// 位置・速度制御系可変ゲイン演算関数
void CalcPVGain(void)
{

  // 1軸目
  axis1.Kvp = gsub[0].Kvp_cfp1 * axis1.Jl_calc;
  axis1.Kvi = gsub[0].zw * axis1.Kvp;
  axis1.fwm = gsub[0].fwm_cf0 + gsub[0].fwm_cfp1 * axis1.Jl_calc + gsub[0].fwm_cfn1 / axis1.Jl_calc;
  axis1.fqs = gsub[0].fqs_cf0 + gsub[0].fqs_cfp1 * axis1.Jl_calc + gsub[0].fqs_cfn1 / axis1.Jl_calc + gsub[0].fqs_cfn2 / powf(axis1.Jl_calc, 2);
  axis1.fwl = gsub[0].fwl_cf0 + gsub[0].fwl_cfp1 * axis1.Jl_calc + gsub[0].fwl_cfn1 / axis1.Jl_calc + gsub[0].fwl_cfn2 / powf(axis1.Jl_calc, 2);
  axis1.Kpp = -axis1.Ksn * axis1.Kvi / (axis1.Dln * axis1.Kvi + (-gsub[0].tau_pole * axis1.Kvi + axis1.Kvp) * axis1.Ksn);
  WAVE_Kpp1 = axis1.Kpp;
  WAVE_Kvp1 = axis1.Kvp;
  WAVE_Kvi1 = axis1.Kvi;
  WAVE_fwm1 = axis1.fwm;
  WAVE_fqs1 = axis1.fqs;
  WAVE_fwl1 = axis1.fwl;
  // 2軸目
  if (flag_SOB == 0)
  {
    axis2.Kvp = gsub[1].Kvp_cfp1 * 23.97;
    axis2.Kvi = gsub[1].zw * axis2.Kvp;
    axis2.fwm = gsub[1].fwm_cf0 + gsub[1].fwm_cfp1 * 23.97 + gsub[1].fwm_cfn1 / 23.97;
    axis2.fqs = gsub[1].fqs_cf0 + gsub[1].fqs_cfp1 * 23.97 + gsub[1].fqs_cfn1 / 23.97 + gsub[1].fqs_cfn2 / powf(23.97, 2);
    axis2.fwl = gsub[1].fwl_cf0 + gsub[1].fwl_cfp1 * 23.97 + gsub[1].fwl_cfn1 / 23.97 + gsub[1].fwl_cfn2 / powf(23.97, 2);
    axis2.Kpp = -axis2.Ksn * axis2.Kvi / (axis2.Dln * axis2.Kvi + (-gsub[1].tau_pole * axis2.Kvi + axis2.Kvp) * axis2.Ksn);
  }
  else
  {
    axis2.Kvp = gsub[1].Kvp_cfp1 * axis2.Jl_calc;
    axis2.Kvi = gsub[1].zw * axis2.Kvp;
    axis2.fwm = gsub[1].fwm_cf0 + gsub[1].fwm_cfp1 * axis2.Jl_calc + gsub[1].fwm_cfn1 / axis2.Jl_calc;
    axis2.fqs = gsub[1].fqs_cf0 + gsub[1].fqs_cfp1 * axis2.Jl_calc + gsub[1].fqs_cfn1 / axis2.Jl_calc + gsub[1].fqs_cfn2 / powf(axis2.Jl_calc, 2);
    axis2.fwl = gsub[1].fwl_cf0 + gsub[1].fwl_cfp1 * axis2.Jl_calc + gsub[1].fwl_cfn1 / axis2.Jl_calc + gsub[1].fwl_cfn2 / powf(axis2.Jl_calc, 2);
    axis2.Kpp = -axis2.Ksn * axis2.Kvi / (axis2.Dln * axis2.Kvi + (-gsub[1].tau_pole * axis2.Kvi + axis2.Kvp) * axis2.Ksn);
  }
  WAVE_Kpp2 = axis2.Kpp;
  WAVE_Kvp2 = axis2.Kvp;
  WAVE_Kvi2 = axis2.Kvi;
  WAVE_fwm2 = axis2.fwm;
  WAVE_fqs2 = axis2.fqs;
  WAVE_fwl2 = axis2.fwl;
  // 3軸目
  axis3.Kvp = gsub[2].Kvp_cfp1 * axis3.Jl_calc;
  axis3.Kvi = gsub[2].zw * axis3.Kvp;
  axis3.fwm = gsub[2].fwm_cf0 + gsub[2].fwm_cfp1 * axis3.Jl_calc + gsub[2].fwm_cfn1 / axis3.Jl_calc;
  axis3.fqs = gsub[2].fqs_cf0 + gsub[2].fqs_cfp1 * axis3.Jl_calc + gsub[2].fqs_cfn1 / axis3.Jl_calc + gsub[2].fqs_cfn2 / powf(axis3.Jl_calc, 2);
  axis3.fwl = gsub[2].fwl_cf0 + gsub[2].fwl_cfp1 * axis3.Jl_calc + gsub[2].fwl_cfn1 / axis3.Jl_calc + gsub[2].fwl_cfn2 / powf(axis3.Jl_calc, 2);
  axis3.Kpp = -axis3.Ksn * axis3.Kvi / (axis3.Dln * axis3.Kvi + (-gsub[2].tau_pole * axis3.Kvi + axis3.Kvp) * axis3.Ksn);
  WAVE_Kpp3 = axis3.Kpp;
  WAVE_Kvp3 = axis3.Kvp;
  WAVE_Kvi3 = axis3.Kvi;
  WAVE_fwm3 = axis3.fwm;
  WAVE_fqs3 = axis3.fqs;
  WAVE_fwl3 = axis3.fwl;
}

// 位置・速度制御系可変ゲイン演算関数(初期化用：係数図法)
void CalcPVGainInitCDM(void)
{
  // 1軸目
  gsub[0].Kvp_cfp1 = powf(gsub[0].r_cdm1, 3) * powf(gsub[0].r_cdm2, 2) * gsub[0].r_cdm3 * axis1.Jmn / axis1.Ksn / axis1.Ktn / gsub[0].zw / powf(gsub[0].tau_cdm, 4);
  gsub[0].fwm_cf0 = (axis1.Jmn * gsub[0].r_cdm1 * gsub[0].r_cdm2 * gsub[0].r_cdm3 - axis1.Dmn * gsub[0].tau_cdm) / axis1.Ktn / gsub[0].tau_cdm;
  gsub[0].fwm_cfp1 = -powf(gsub[0].r_cdm1, 3) * powf(gsub[0].r_cdm2, 2) * gsub[0].r_cdm3 * axis1.Jmn / axis1.Ksn / axis1.Ktn / gsub[0].zw / powf(gsub[0].tau_cdm, 4);
  gsub[0].fwm_cfn1 = -axis1.Dln * axis1.Jmn / axis1.Ktn;
  gsub[0].fqs_cf0 = 0.1e1 / powf(gsub[0].tau_cdm, 2) * (axis1.Jmn * powf(axis1.Rgn, 2) * powf(gsub[0].r_cdm1, 2) * powf(gsub[0].r_cdm2, 2) * gsub[0].r_cdm3 - axis1.Ksn * powf(gsub[0].tau_cdm, 2)) / axis1.Rgn / axis1.Ktn;
  gsub[0].fqs_cfp1 = -axis1.Jmn * axis1.Rgn * powf(gsub[0].r_cdm1, 3) * powf(gsub[0].r_cdm2, 2) * gsub[0].r_cdm3 / axis1.Ksn / axis1.Ktn / powf(gsub[0].tau_cdm, 4);
  gsub[0].fqs_cfn1 = -axis1.Jmn * axis1.Rgn / gsub[0].tau_cdm * (axis1.Dln * gsub[0].r_cdm1 * gsub[0].r_cdm2 * gsub[0].r_cdm3 + axis1.Ksn * gsub[0].tau_cdm) / axis1.Ktn;
  gsub[0].fqs_cfn2 = powf(axis1.Dln, 2) * axis1.Jmn * axis1.Rgn / axis1.Ktn;
  gsub[0].fwl_cf0 = -axis1.Rgn * axis1.Jmn * gsub[0].r_cdm1 * gsub[0].r_cdm2 * gsub[0].r_cdm3 / powf(gsub[0].tau_cdm, 2) * (axis1.Dln * gsub[0].r_cdm1 * gsub[0].r_cdm2 + axis1.Ksn * gsub[0].tau_cdm) / axis1.Ksn / axis1.Ktn;
  gsub[0].fwl_cfp1 = axis1.Jmn * axis1.Rgn * powf(gsub[0].r_cdm1, 3) * powf(gsub[0].r_cdm2, 2) * gsub[0].r_cdm3 / axis1.Ksn / axis1.Ktn / powf(gsub[0].tau_cdm, 3);
  gsub[0].fwl_cfn1 = axis1.Rgn * axis1.Jmn * axis1.Dln / gsub[0].tau_cdm * (axis1.Dln * gsub[0].r_cdm1 * gsub[0].r_cdm2 * gsub[0].r_cdm3 + 2.0 * axis1.Ksn * gsub[0].tau_cdm) / axis1.Ksn / axis1.Ktn;
  gsub[0].fwl_cfn2 = -powf(axis1.Dln, 3) * axis1.Jmn * axis1.Rgn / axis1.Ksn / axis1.Ktn;
  // 2軸目
  gsub[1].Kvp_cfp1 = powf(gsub[1].r_cdm1, 3) * powf(gsub[1].r_cdm2, 2) * gsub[1].r_cdm3 * axis2.Jmn / axis2.Ksn / axis2.Ktn / gsub[1].zw / powf(gsub[1].tau_cdm, 4);
  gsub[1].fwm_cf0 = (axis2.Jmn * gsub[1].r_cdm1 * gsub[1].r_cdm2 * gsub[1].r_cdm3 - axis2.Dmn * gsub[1].tau_cdm) / axis2.Ktn / gsub[1].tau_cdm;
  gsub[1].fwm_cfp1 = -powf(gsub[1].r_cdm1, 3) * powf(gsub[1].r_cdm2, 2) * gsub[1].r_cdm3 * axis2.Jmn / axis2.Ksn / axis2.Ktn / gsub[1].zw / powf(gsub[1].tau_cdm, 4);
  gsub[1].fwm_cfn1 = -axis2.Dln * axis2.Jmn / axis2.Ktn;
  gsub[1].fqs_cf0 = 0.1e1 / powf(gsub[1].tau_cdm, 2) * (axis2.Jmn * powf(axis2.Rgn, 2) * powf(gsub[1].r_cdm1, 2) * powf(gsub[1].r_cdm2, 2) * gsub[1].r_cdm3 - axis2.Ksn * powf(gsub[1].tau_cdm, 2)) / axis2.Rgn / axis2.Ktn;
  gsub[1].fqs_cfp1 = -axis2.Jmn * axis2.Rgn * powf(gsub[1].r_cdm1, 3) * powf(gsub[1].r_cdm2, 2) * gsub[1].r_cdm3 / axis2.Ksn / axis2.Ktn / powf(gsub[1].tau_cdm, 4);
  gsub[1].fqs_cfn1 = -axis2.Jmn * axis2.Rgn / gsub[1].tau_cdm * (axis2.Dln * gsub[1].r_cdm1 * gsub[1].r_cdm2 * gsub[1].r_cdm3 + axis2.Ksn * gsub[1].tau_cdm) / axis2.Ktn;
  gsub[1].fqs_cfn2 = powf(axis2.Dln, 2) * axis2.Jmn * axis2.Rgn / axis2.Ktn;
  gsub[1].fwl_cf0 = -axis2.Rgn * axis2.Jmn * gsub[1].r_cdm1 * gsub[1].r_cdm2 * gsub[1].r_cdm3 / powf(gsub[1].tau_cdm, 2) * (axis2.Dln * gsub[1].r_cdm1 * gsub[1].r_cdm2 + axis2.Ksn * gsub[1].tau_cdm) / axis2.Ksn / axis2.Ktn;
  gsub[1].fwl_cfp1 = axis2.Jmn * axis2.Rgn * powf(gsub[1].r_cdm1, 3) * powf(gsub[1].r_cdm2, 2) * gsub[1].r_cdm3 / axis2.Ksn / axis2.Ktn / powf(gsub[1].tau_cdm, 3);
  gsub[1].fwl_cfn1 = axis2.Rgn * axis2.Jmn * axis2.Dln / gsub[1].tau_cdm * (axis2.Dln * gsub[1].r_cdm1 * gsub[1].r_cdm2 * gsub[1].r_cdm3 + 2.0 * axis2.Ksn * gsub[1].tau_cdm) / axis2.Ksn / axis2.Ktn;
  gsub[1].fwl_cfn2 = -powf(axis2.Dln, 3) * axis2.Jmn * axis2.Rgn / axis2.Ksn / axis2.Ktn;
  // 3軸目
  gsub[2].Kvp_cfp1 = powf(gsub[2].r_cdm1, 3) * powf(gsub[2].r_cdm2, 2) * gsub[2].r_cdm3 * axis3.Jmn / axis3.Ksn / axis3.Ktn / gsub[2].zw / powf(gsub[2].tau_cdm, 4);
  gsub[2].fwm_cf0 = (axis3.Jmn * gsub[2].r_cdm1 * gsub[2].r_cdm2 * gsub[2].r_cdm3 - axis3.Dmn * gsub[2].tau_cdm) / axis3.Ktn / gsub[2].tau_cdm;
  gsub[2].fwm_cfp1 = -powf(gsub[2].r_cdm1, 3) * powf(gsub[2].r_cdm2, 2) * gsub[2].r_cdm3 * axis3.Jmn / axis3.Ksn / axis3.Ktn / gsub[2].zw / powf(gsub[2].tau_cdm, 4);
  gsub[2].fwm_cfn1 = -axis3.Dln * axis3.Jmn / axis3.Ktn;
  gsub[2].fqs_cf0 = 0.1e1 / powf(gsub[2].tau_cdm, 2) * (axis3.Jmn * powf(axis3.Rgn, 2) * powf(gsub[2].r_cdm1, 2) * powf(gsub[2].r_cdm2, 2) * gsub[2].r_cdm3 - axis3.Ksn * powf(gsub[2].tau_cdm, 2)) / axis3.Rgn / axis3.Ktn;
  gsub[2].fqs_cfp1 = -axis3.Jmn * axis3.Rgn * powf(gsub[2].r_cdm1, 3) * powf(gsub[2].r_cdm2, 2) * gsub[2].r_cdm3 / axis3.Ksn / axis3.Ktn / powf(gsub[2].tau_cdm, 4);
  gsub[2].fqs_cfn1 = -axis3.Jmn * axis3.Rgn / gsub[2].tau_cdm * (axis3.Dln * gsub[2].r_cdm1 * gsub[2].r_cdm2 * gsub[2].r_cdm3 + axis3.Ksn * gsub[2].tau_cdm) / axis3.Ktn;
  gsub[2].fqs_cfn2 = powf(axis3.Dln, 2) * axis3.Jmn * axis3.Rgn / axis3.Ktn;
  gsub[2].fwl_cf0 = -axis3.Rgn * axis3.Jmn * gsub[2].r_cdm1 * gsub[2].r_cdm2 * gsub[2].r_cdm3 / powf(gsub[2].tau_cdm, 2) * (axis3.Dln * gsub[2].r_cdm1 * gsub[2].r_cdm2 + axis3.Ksn * gsub[2].tau_cdm) / axis3.Ksn / axis3.Ktn;
  gsub[2].fwl_cfp1 = axis3.Jmn * axis3.Rgn * powf(gsub[2].r_cdm1, 3) * powf(gsub[2].r_cdm2, 2) * gsub[2].r_cdm3 / axis3.Ksn / axis3.Ktn / powf(gsub[2].tau_cdm, 3);
  gsub[2].fwl_cfn1 = axis3.Rgn * axis3.Jmn * axis3.Dln / gsub[2].tau_cdm * (axis3.Dln * gsub[2].r_cdm1 * gsub[2].r_cdm2 * gsub[2].r_cdm3 + 2.0 * axis3.Ksn * gsub[2].tau_cdm) / axis3.Ksn / axis3.Ktn;
  gsub[2].fwl_cfn2 = -powf(axis3.Dln, 3) * axis3.Jmn * axis3.Rgn / axis3.Ksn / axis3.Ktn;
}

// 回生ブレーキ関連
float CalcVdcMean(int BDN, float Vdc)
{
  static int counter[3] = {0};
  static float Vdc_sum[3] = {0};
  static float Vdc_mean[3] = {0};
  // ループカウントは関数が呼ばれる度に増える
  // 割り込み毎に何回呼ばれているか確認すること, 設定した五万回に特に意味はない.
  if (counter[BDN] < 50000)
  {
    counter[BDN] = counter[BDN] + 1;
    Vdc_sum[BDN] = Vdc_sum[BDN] + Vdc;
    Vdc_mean[BDN] = 0.0;
  }
  else if (counter[BDN] == 50000)
  {
    Vdc_mean[BDN] = Vdc_sum[BDN] / counter[BDN];
    counter[BDN] = counter[BDN] + 1;
  }
  return Vdc_mean[BDN];
}

void BrakeController(Robot *robo)
{
  float Vdc_mean[3] = {0};
  float Vdc_add_ofst = 0.0;

  Vdc_mean[robo->BDN] = CalcVdcMean(robo->BDN, robo->Vdc);
  if (Vdc_mean[robo->BDN] != 0.0)
  {
    if (Vdc_mean[robo->BDN] + Vdc_add_ofst < robo->Vdc)
    {
      robo->MRBR = 2.0;
    }
    else
    {
      robo->MRBR = -2.0;
    }
  }
}

// ランプ位置指令生成関数
float CalcPref2axis(float t_lim, float ql_deg_tilt, int flag)
{
  static int loop_count_num[2] = {0};
  float t = 0.0;
  float qm_ref = 0.0;

  t = (float)Tp * loop_count_num[flag];
  loop_count_num[flag]++;
  if (t <= t_lim)
  {
    qm_ref = axis2.Rgn * PI / 180.0 * ql_deg_tilt * t;
  }
  else
  {
    qm_ref = axis2.Rgn * PI / 180.0 * ql_deg_tilt * t_lim;
  }
  return qm_ref;
}

// ランプ位置指令生成関数(繰り返し動作)
float CalcPrefRep2axis(float t_lim_up, float ql_deg_tilt_up, float t_lim_down, float ql_deg_tilt_down, float t_wait)
{
  static int loop_count_num = 0;
  float t = 0.0;
  float qm_ref = 0.0;

  t = (float)Tp * loop_count_num;
  loop_count_num++;
  if (t <= t_lim_up)
  {
    qm_ref = axis2.Rgn * PI / 180.0 * ql_deg_tilt_up * t;
  }
  else if (t_lim_up < t && t <= t_lim_up + t_wait)
  {
    qm_ref = axis2.Rgn * PI / 180.0 * ql_deg_tilt_up * t_lim_up;
  }
  else if (t_lim_up + t_wait < t && t <= t_lim_up + t_lim_down + t_wait)
  {
    qm_ref = axis2.Rgn * PI / 180.0 * ql_deg_tilt_up * t_lim_up + axis2.Rgn * PI / 180.0 * ql_deg_tilt_down * (t - (t_lim_up + t_wait));
  }
  else if (t_lim_up + t_lim_down + t_wait < t && t <= t_lim_up + t_lim_down + 2.0 * t_wait)
  {
    qm_ref = 0.0;
  }
  else if (t_lim_up + t_lim_down + 2.0 * t_wait < t)
  {
    loop_count_num = 0;
  }
  else
  {
    // 計算ミス
  }
  return qm_ref;
}

// ランプ位置指令生成関数(繰り返し動作)
float CalcPrefRep3axis(float t_lim_up, float ql_deg_tilt_up, float t_lim_down, float ql_deg_tilt_down, float t_wait)
{
  static int loop_count_num = 0;
  float t = 0.0;
  float qm_ref = 0.0;

  t = (float)Tp * loop_count_num;
  loop_count_num++;
  if (t <= t_lim_up)
  {
    qm_ref = axis2.Rgn * PI / 180.0 * ql_deg_tilt_up * t;
  }
  else if (t_lim_up < t && t <= t_lim_up + t_wait)
  {
    qm_ref = axis2.Rgn * PI / 180.0 * ql_deg_tilt_up * t_lim_up;
  }
  else if (t_lim_up + t_wait < t && t <= t_lim_up + t_lim_down + t_wait)
  {
    qm_ref = axis2.Rgn * PI / 180.0 * ql_deg_tilt_up * t_lim_up + axis2.Rgn * PI / 180.0 * ql_deg_tilt_down * (t - (t_lim_up + t_wait));
  }
  else if (t_lim_up + t_lim_down + t_wait < t && t <= t_lim_up + t_lim_down + 2.0 * t_wait)
  {
    qm_ref = 0.0;
  }
  else if (t_lim_up + t_lim_down + 2.0 * t_wait < t)
  {
    loop_count_num = 0;
  }
  else
  {
    // 計算ミス
  }
  return qm_ref;
}

void CalcTauLDyn(Robot axis[])
{
  // 三角関数の定義
  float C1 = 0.0;
  float C2 = 0.0;
  float C3 = 0.0;
  float C22 = 0.0;
  float C23 = 0.0;
  float C223 = 0.0;
  float C2233 = 0.0;

  float S1 = 0.0;
  float S2 = 0.0;
  float S3 = 0.0;
  float S22 = 0.0;
  float S23 = 0.0;
  float S223 = 0.0;
  float S2233 = 0.0;

  C1 = cos(axis1.ql_calc);
  C2 = cos(axis2.ql_calc);
  C3 = cos(axis3.ql_calc);
  C22 = cos(2 * axis2.ql_calc);
  C23 = cos(axis2.ql_calc + axis3.ql_calc);
  C223 = cos(2 * axis2.ql_calc + axis3.ql_calc);
  C2233 = cos(2 * axis2.ql_calc + 2 * axis3.ql_calc);

  S1 = sin(axis1.ql_calc);
  S2 = sin(axis2.ql_calc);
  S3 = sin(axis3.ql_calc);
  S22 = sin(2 * axis2.ql_calc);
  S23 = sin(axis2.ql_calc + axis3.ql_calc);
  S223 = sin(2 * axis2.ql_calc + axis3.ql_calc);
  S2233 = sin(2 * axis2.ql_calc + 2 * axis3.ql_calc);

  // ラグランジュ法に基づく動力学
  // 慣性項
  float H11 = 0.0;
  float H12 = 0.0;
  float H13 = 0.0;
  float H21 = 0.0;
  float H22 = 0.0;
  float H23 = 0.0;
  float H31 = 0.0;
  float H32 = 0.0;
  float H33 = 0.0;
  // 遠心力項・コリオリ力項
  float b111 = 0.0;
  float b112 = 0.0;
  float b113 = 0.0;
  float b121 = 0.0;
  float b122 = 0.0;
  float b123 = 0.0;
  float b131 = 0.0;
  float b132 = 0.0;
  float b133 = 0.0;
  float b211 = 0.0;
  float b212 = 0.0;
  float b213 = 0.0;
  float b221 = 0.0;
  float b222 = 0.0;
  float b223 = 0.0;
  float b231 = 0.0;
  float b232 = 0.0;
  float b233 = 0.0;
  float b311 = 0.0;
  float b312 = 0.0;
  float b313 = 0.0;
  float b321 = 0.0;
  float b322 = 0.0;
  float b323 = 0.0;
  float b331 = 0.0;
  float b332 = 0.0;
  float b333 = 0.0;
  // 重力項
  float G1 = 0.0;
  float G2 = 0.0;
  float G3 = 0.0;

  // 外乱トルクを計算したいので慣性行列の主対角成分はコメントアウト
  // H11 =
  //     dyn.H11p1
  //   + dyn.H11p2*S2
  //   + dyn.H11p3*C2233
  //   + S3*
  //   (
  //       dyn.H11p4*S2
  //     + dyn.H11p5*C2
  //     + dyn.H11p6
  //   )
  //   + dyn.H11p7*S2233
  //   + dyn.H11p8*S223
  //   + C3*
  //   (
  //       dyn.H11p9*S2
  //     + dyn.H11p10*C2
  //     + dyn.H11p11
  //   )
  //   + dyn.H11p12*C223
  //   + dyn.H11p13*C22;

  H12 = -C2 * dyn.H12p1;

  H21 = H12;

  // 外乱トルクを計算したいので慣性行列の主対角成分はコメントアウト
  // H22= dyn.H22p1
  //   + dyn.H22p2*C3
  //   + dyn.H22p3*S3;

  H23 = dyn.H23p1 + dyn.H23p2 * S3 + dyn.H23p3 * C3;

  H32 = H23;

  // 外乱トルクを計算したいので慣性行列の主対角成分はコメントアウト
  // H33 = dyn.H33p1;

  b122 = S2 * dyn.b122p1;
  b112 = dyn.b112p1 * S2233 + dyn.b112p2 * C2233 + dyn.b112p3 * S22 + dyn.b112p4 * S223 + dyn.b112p5 * C23 + dyn.b112p6 * C2 + dyn.b112p7 * S23 + dyn.b112p8 * C223;
  b113 = dyn.b113p1 * S23 + dyn.b113p2 * C23 + dyn.b113p3 * C223 + dyn.b113p4 * S223 + dyn.b113p5 * C3 + dyn.b113p6 * S3 + dyn.b113p7 * C2233 + dyn.b113p8 * S2233;

  b211 = dyn.b211p1 * C23 + dyn.b211p2 * S23 + dyn.b211p3 * C2 + dyn.b211p4 * C2233 + dyn.b211p5 * C223 + dyn.b211p6 * S22 + dyn.b211p7 * S2233 + dyn.b211p8 * S223;
  b233 = dyn.b233p1 * C3 + dyn.b233p2 * S3;
  b223 = 2 * dyn.b223p1 * C3 + dyn.b223p2 * S3;

  b311 = dyn.b311p1 * S23 + dyn.b311p2 * C23 + dyn.b311p3 * C223 + dyn.b311p4 * S223 + dyn.b311p5 * C3 + dyn.b311p6 * S3 + dyn.b311p7 * C2233 + dyn.b311p8 * S2233;
  b322 = dyn.b322p1 * C3 + dyn.b322p2 * S3;

  G2 = dyn.G2p1 * S2 + dyn.G2p2 * S23 + dyn.G2p3 * C23;
  G3 = dyn.G3p1 * S23 + dyn.G3p2 * C23;

  // aL = [a1; a2; a3];
  // H = [H11 H12 H13;
  //      H21 H22 H23;
  //      H31 H32 H33];
  //
  // wLsq = [w1^2; w2^2; w3^2];
  // bcen = [b111 b122 b133;
  //         b211 b222 b233;
  //         b311 b322 b333];
  //
  // wLcr = [w1*w2; w1*w3; w2*w3];
  // bcor = [b112 b113 b123;
  //         b212 b213 b223;
  //         b312 b313 b323];
  //
  // grav = [G1; G2; G3];
  //
  // T = H*aL + bcen*wLsq + 2*bcor*wLcr + grav;

  // 動力学外乱トルクの計算(3軸同時、簡略化)
  axis1.tauLdyn = H12 * axis2.al_calc + b122 * (axis2.wl_calc * axis2.wl_calc) + b112 * axis1.wl_calc * axis2.wl_calc + b113 * axis1.wl_calc * axis3.wl_calc;
  axis2.tauLdyn_z2 = axis2.tauLdyn_z1;
  axis2.tauLdyn_z1 = axis2.tauLdyn;
  axis2.tauLdyn = H21 * axis1.al_calc + H23 * axis3.al_calc + b211 * (axis1.wl_calc * axis1.wl_calc) + b233 * (axis3.wl_calc * axis3.wl_calc) + b223 * axis2.wl_calc * axis3.wl_calc + G2;
  axis3.tauLdyn_z2 = axis3.tauLdyn_z1;
  axis3.tauLdyn_z1 = axis3.tauLdyn;
  axis3.tauLdyn = H32 * axis2.al_calc + b311 * (axis1.wl_calc * axis1.wl_calc) + b322 * (axis2.wl_calc * axis2.wl_calc) + G3;
  // Jlの計算
  // axis1.Jl_calc = H11;
  // axis2.Jl_calc = H22;
  // axis3.Jl_calc = H33;

  // 動力学トルクの計算(3軸同時、簡略化)
  // axis1.tauLdyn = H11*axis1.al_calc + H12*axis2.al_calc + b122*powf(axis2.wl_calc,2) + b112*axis1.wl_calc*axis2.wl_calc + b113*axis1.wl_calc*axis3.wl_calc;
  // axis2.tauLdyn = H21*axis1.al_calc + H22*axis2.al_calc + H23*axis3.al_calc + b211*powf(axis1.wl_calc,2) + b233*powf(axis3.wl_calc,2) + b223*axis2.wl_calc*axis3.wl_calc + G2;
  // axis3.tauLdyn = H32*axis2.al_calc + H33*axis3.al_calc + b311*powf(axis1.wl_calc,2) + b322*powf(axis2.wl_calc,2) + G3;

  // 動力学トルクの計算(3軸同時)
  // *tauLdyn1 = H11*a1 + H12*a2 + H13*a3 + b111*powf(w1,2) + b122*powf(w2,2) + b133*powf(w3,2) + 2.0*(b112*w1*w2 + b113*w1*w3 + b123*w2*w3) + G1;
  // *tauLdyn2 = H21*a1 + H22*a2 + H23*a3 + b211*powf(w1,2) + b222*powf(w2,2) + b233*powf(w3,2) + 2.0*(b212*w1*w2 + b213*w1*w3 + b223*w2*w3) + G2;
  // *tauLdyn3 = H31*a1 + H32*a2 + H33*a3 + b311*powf(w1,2) + b322*powf(w2,2) + b333*powf(w3,2) + 2.0*(b312*w1*w2 + b313*w1*w3 + b323*w2*w3) + G3;

  // 動力学トルクの計算(1軸のみ)
  // *tauLdyn1 = H11*a1 + b111*powf(w1,2);
  // *tauLdyn2 = 0.0;
  // *tauLdyn3 = 0.0;
}

void CalcJl(Robot axis[])
{

  // 三角関数の定義
  float C1 = 0.0;
  float C2 = 0.0;
  float C3 = 0.0;
  float C22 = 0.0;
  float C23 = 0.0;
  float C223 = 0.0;
  float C2233 = 0.0;

  float S1 = 0.0;
  float S2 = 0.0;
  float S3 = 0.0;
  float S22 = 0.0;
  float S23 = 0.0;
  float S223 = 0.0;
  float S2233 = 0.0;

  C2 = cos(axis2.ql);
  C3 = cos(axis3.ql);
  C22 = cos(2 * axis2.ql);
  C223 = cos(2 * axis2.ql + axis3.ql);
  C2233 = cos(2 * axis2.ql + 2 * axis3.ql);

  S2 = sin(axis2.ql);
  S3 = sin(axis3.ql);
  S223 = sin(2 * axis2.ql + axis3.ql);
  S2233 = sin(2 * axis2.ql + 2 * axis3.ql);

  // ラグランジュ法に基づく動力学
  // 慣性項
  float H11 = 0.0;
  float H22 = 0.0;
  float H33 = 0.0;

  H11 = dyn.H11p1 + dyn.H11p2 * S2 + dyn.H11p3 * C2233 + S3 * (dyn.H11p4 * S2 + dyn.H11p5 * C2 + dyn.H11p6) + dyn.H11p7 * S2233 + dyn.H11p8 * S223 + C3 * (dyn.H11p9 * S2 + dyn.H11p10 * C2 + dyn.H11p11) + dyn.H11p12 * C223 + dyn.H11p13 * C22;
  H22 = dyn.H22p1 + dyn.H22p2 * C3 + dyn.H22p3 * S3;
  H33 = dyn.H33p1;

  // Jlの計算
  axis1.Jl_calc_z2 = axis1.Jl_calc_z1;
  axis1.Jl_calc_z1 = axis1.Jl_calc;
  axis1.Jl_calc = H11;
  axis2.Jl_calc_z2 = axis2.Jl_calc_z1;
  axis2.Jl_calc_z1 = axis2.Jl_calc;
  axis2.Jl_calc = H22;
  axis3.Jl_calc_z2 = axis3.Jl_calc_z1;
  axis3.Jl_calc_z1 = axis3.Jl_calc;
  axis3.Jl_calc = H33;
}

void CalcGravIcmp(Robot axis[])
{

  // 三角関数の定義
  float C23 = 0.0;
  float S2 = 0.0;
  float S23 = 0.0;

  C23 = cos(axis2.ql + axis3.ql);
  S2 = sin(axis2.ql);
  S23 = sin(axis2.ql + axis3.ql);

  // ラグランジュ法に基づく動力学
  // 重力項
  // float G1 = 0.0;
  // float G2 = 0.0;
  // float G3 = 0.0;

  axis2.Icmp = (dyn.G2p1 * S2 + dyn.G2p2 * S23 + dyn.G2p3 * C23) / (axis2.Rgn * axis2.Ktn);
  axis3.Icmp = (dyn.G3p1 * S23 + dyn.G3p2 * C23) / (axis3.Rgn * axis3.Ktn);

  // axis2.tauLdyn = dyn.G2p1*S2 +dyn.G2p2*S23 +dyn.G2p3*C23;
  // axis3.tauLdyn = dyn.G3p1*S23 +dyn.G3p2*C23;
}
void CalcDynamicsInit(int flag_dyn_payload)
{
  // 動力学パラメータ
  // 6軸目の各種パラメータ
  // ペイロードにより値が変化するため宣言時は0で初期化
  static float Xntw = 0.0;
  // static float Yntw = 0.0;
  static float Zntw = 0.0;
  static float I6x = 0.0;
  static float I6y = 0.0;
  static float I6z = 0.0;
  static float m6 = 0.0;
  static float X6 = 0.0;
  static float Z6 = 0.0;

  // 無負荷
  if (flag_dyn_payload == 0)
  {
    Xntw = 0.0190;
    // Yntw = 0.0000;
    Zntw = 0.0001;
    I6x = 1.587E-04;
    I6y = 1.564E-04;
    I6z = 1.570E-04;
    m6 = 0.453;
    X6 = Xntw;
    Z6 = Zntw;
  }
  // 7.2kg負荷
  if (flag_dyn_payload == 1)
  {
    // 出典：\\hp77\users\2012\yabuki\PSFS_引継ぎ\PWS送付用データ\先端負荷同定\para_cons.m
    Xntw = 0.046;
    // Yntw = 0.0000;
    Zntw = 0.085;
    I6x = 2.4659E-02;
    I6y = 1.4546E-02;
    I6z = 1.0067E-02;
    m6 = 7.65;
    X6 = Xntw;
    Z6 = Zntw;
  }
  // 3.7kg負荷
  if (flag_dyn_payload == 2)
  {
    // 出典：\\hp77\users\2012\yabuki\PSFS_引継ぎ\PWS送付用データ\先端負荷同定\para_cons.m
    Xntw = 0.0464;
    // Yntw = 0.0000;
    Zntw = 0.0854;
    I6x = 2.4659E-02;
    I6y = 1.4546E-02;
    I6z = 1.0067E-02;
    m6 = 3.7;
    X6 = Xntw;
    Z6 = Zntw;
  }

  const float Lb = 0.16;
  const float Ld = 0.088;
  // const float Lac = 0.2685;
  // const float Lf  = 0.088;
  const float Le = 0.56;
  const float Lh1 = 0.145;
  const float Lg = 0.13;
  const float Lh2 = 0.455;
  const float Lj = 0.2;
  const float Lii = 0.04;

  const float Xrt = 0.0413;
  // const float Zrt  = 0.1266;
  // const float Xua  = -0.0228;
  const float Zua = 0.2382;
  const float Xnfa = 0.0841;
  // const float Ynfa = -0.0105;
  const float Znfa = 0.0564;
  const float Xrw = 0.3124;
  // const float Zrw  = -0.0001;
  const float Xbw = 0.0989;
  const float Zbw = 0.0332;

  const float X1 = Xrt;
  // const float Z1 = Zrt;
  const float Y2 = -Ld;
  const float Z2 = Zua;
  const float X3 = Xnfa;
  const float Z3 = Znfa;
  const float X4 = Xrw;
  const float X5 = Xbw;
  const float Z5 = Zbw;

  // const float I1x = 0;
  // const float I1y = 0;
  const float I1z = 0;
  const float I2x = 0;
  const float I2y = 1.448E+00;
  const float I2z = 0;
  const float I3x = 0;
  const float I3y = 1.716E-01;
  const float I3z = 0;
  const float I4x = 5.303E-03;
  const float I4y = 0;
  const float I4z = 0;
  const float I5x = 1.385E-03;
  const float I5y = 0;
  const float I5z = 0;

  // リンクの質量
  const float m1 = 71.13;
  const float m2 = 26.98;
  const float m3 = 12.96;
  const float m4 = 4.885;
  const float m5 = 1.846;

  // 重力加速度
  const float g = 9.8;

  dyn.H11p1 = +m1 * powf(X1, 2) + 0.5 * m4 * powf(Le, 2) + 0.5 * m6 * powf(Lii, 2) + 0.5 * m6 * powf(Lg, 2) + m6 * Z6 * Lii + m2 * powf(Y2, 2) + m5 * Z5 * Lg + 0.5 * m3 * powf(Le, 2) + 0.5 * m6 * powf(Le, 2) + 0.5 * m5 * powf(Le, 2) + m4 * powf(Lb, 2) + m3 * powf(Lb, 2) + m6 * Z6 * Lg + I1z + 0.5 * m4 * powf(Lh1, 2) + 0.5 * m5 * powf(Lh2, 2) + 0.5 * m5 * powf(Lh1, 2) + 0.5 * I2z + 0.5 * I2x + 0.5 * I3x + 0.5 * I3z + powf(Lb, 2) * m2 + m5 * powf(Lb, 2) + m6 * powf(Lb, 2) + 0.5 * I4x + 0.5 * I4z + 0.5 * I5x + 0.5 * I5z + 0.5 * m6 * powf(Lj, 2) + 0.5 * m6 * powf(Lh2, 2) + 0.5 * m6 * powf(Lh1, 2) + 0.5 * I6x + 0.5 * I6z + 0.5 * m2 * powf(Z2, 2) + 0.5 * m4 * powf(X4, 2) + 0.5 * m5 * powf(Z5, 2) + 0.5 * m5 * powf(X5, 2) + 0.5 * m6 * powf(Z6, 2) + 0.5 * m6 * powf(X6, 2) + m6 * Lj * Lh2 + m6 * X6 * Lh1 + m6 * X6 * Lh2 + m6 * X6 * Lj + m5 * X5 * Lh1 + m5 * Lh2 * Lh1 + m5 * X5 * Lh2 + m6 * Lh2 * Lh1 + m6 * Lj * Lh1 + m4 * X4 * Lh1 + 0.5 * m3 * powf(Z3, 2) + 0.5 * m3 * powf(X3, 2) + m6 * Lii * Lg + 0.5 * m4 * powf(Lg, 2) + 0.5 * m5 * powf(Lg, 2);
  dyn.H11p2 = +2 * m2 * Lb * Z2 + 2 * m5 * Le * Lb + 2 * m6 * Le * Lb + 2 * m3 * Le * Lb + 2 * m4 * Le * Lb;
  dyn.H11p3 = (0.5 * (-m6 * powf(Lii, 2) - m6 * powf(Lg, 2) - 2 * m6 * Z6 * Lii - 2 * m5 * Z5 * Lg - 2 * m6 * Z6 * Lg + m4 * powf(Lh1, 2) + m5 * powf(Lh2, 2) + m5 * powf(Lh1, 2) - I3x + I3z - I4x + I4z - I5x + I5z + m6 * powf(Lj, 2) + m6 * powf(Lh2, 2) + m6 * powf(Lh1, 2) - I6x + I6z + m4 * powf(X4, 2) - m5 * powf(Z5, 2) + m5 * powf(X5, 2) - m6 * powf(Z6, 2) + m6 * powf(X6, 2) + 2 * m6 * Lj * Lh2 + 2 * m6 * X6 * Lh1 + 2 * m6 * X6 * Lh2 + 2 * m6 * X6 * Lj + 2 * m5 * X5 * Lh1 + 2 * m5 * Lh2 * Lh1 + 2 * m5 * X5 * Lh2 + 2 * m6 * Lh2 * Lh1 + 2 * m6 * Lj * Lh1 + 2 * m4 * X4 * Lh1 - m3 * powf(Z3, 2) + m3 * powf(X3, 2) - 2 * m6 * Lii * Lg - m4 * powf(Lg, 2) - m5 * powf(Lg, 2)));
  dyn.H11p4 = -2 * X3 * m3 * Lb - 2 * m5 * Lh1 * Lb - 2 * m6 * Lh1 * Lb - 2 * m6 * Lj * Lb - 2 * m6 * X6 * Lb - 2 * m6 * Lh2 * Lb - 2 * m5 * X5 * Lb - 2 * X4 * m4 * Lb - 2 * m4 * Lh1 * Lb - 2 * m5 * Lh2 * Lb;
  dyn.H11p5 = +2 * m5 * Lg * Lb + 2 * m6 * Z6 * Lb + 2 * m6 * Lii * Lb + 2 * m6 * Lg * Lb + 2 * m5 * Z5 * Lb + 2 * m4 * Lg * Lb + 2 * m3 * Z3 * Lb;
  dyn.H11p6 = -1 * m5 * Lh1 * Le - 1 * m5 * X5 * Le - 1 * m6 * Lj * Le - 1 * X4 * m4 * Le - 1 * m6 * X6 * Le - 1 * m6 * Lh1 * Le - 1 * m5 * Lh2 * Le - 1 * X3 * m3 * Le - 1 * m4 * Lh1 * Le - 1 * m6 * Lh2 * Le;
  dyn.H11p7 = m5 * Lh2 * Lg + m5 * X5 * Z5 + m3 * X3 * Z3 + m4 * X4 * Lg + m6 * Lh2 * Lg + m5 * Z5 * Lh2 + m6 * Z6 * Lh2 + m5 * Lh1 * Lg + m6 * X6 * Lg + m6 * X6 * Z6 + m6 * X6 * Lii + m6 * Lii * Lh1 + m6 * Lj * Lii + m6 * Lii * Lh2 + m6 * Lh1 * Lg + m5 * X5 * Lg + m6 * Z6 * Lh1 + m4 * Lh1 * Lg + m5 * Z5 * Lh1 + m6 * Lj * Lg + m6 * Z6 * Lj;
  dyn.H11p8 = m6 * Lh1 * Le + m5 * Lh2 * Le + X4 * m4 * Le + X3 * m3 * Le + m4 * Lh1 * Le + m6 * Lh2 * Le + m6 * Lj * Le + m5 * X5 * Le + m5 * Lh1 * Le + m6 * X6 * Le;
  dyn.H11p9 = 2 * m3 * Z3 * Lb + 2 * m6 * Z6 * Lb + 2 * m6 * Lg * Lb + 2 * m5 * Z5 * Lb + 2 * m4 * Lg * Lb + 2 * m6 * Lii * Lb + 2 * m5 * Lg * Lb;
  dyn.H11p10 = +2 * m5 * X5 * Lb + 2 * X3 * m3 * Lb + 2 * m6 * Lh1 * Lb + 2 * m5 * Lh2 * Lb + 2 * m5 * Lh1 * Lb + 2 * m6 * X6 * Lb + 2 * m6 * Lh2 * Lb + 2 * m6 * Lj * Lb + 2 * X4 * m4 * Lb + 2 * m4 * Lh1 * Lb;
  dyn.H11p11 = +1 * m4 * Lg * Le + 1 * m6 * Lii * Le + 1 * m3 * Z3 * Le + 1 * m5 * Z5 * Le + 1 * m6 * Lg * Le + 1 * m5 * Lg * Le + 1 * m6 * Z6 * Le;
  dyn.H11p12 = -m5 * Z5 * Le - m4 * Lg * Le - m6 * Lg * Le - m6 * Lii * Le - m6 * Z6 * Le - m3 * Z3 * Le - m5 * Lg * Le;
  dyn.H11p13 = 0.5 * (-m4 * powf(Le, 2) - m2 * powf(Z2, 2) - m3 * powf(Le, 2) + I2z - I2x - m6 * powf(Le, 2) - m5 * powf(Le, 2));

  dyn.H12p1 = m2 * Y2 * Z2;

  dyn.H22p1 = m6 * powf(Lii, 2) + m6 * powf(Lg, 2) + 2 * m6 * Z6 * Lii + 2 * m5 * Z5 * Lg + 2 * m6 * Z6 * Lg + m4 * powf(Lh1, 2) + m5 * powf(Lh2, 2) + m5 * powf(Lh1, 2) + I2y + I3y + I4y + I5y + m6 * powf(Lj, 2) + m6 * powf(Lh2, 2) + m6 * powf(Lh1, 2) + I6y + m5 * powf(Le, 2) + m6 * powf(Le, 2) + m4 * powf(Le, 2) + m3 * powf(Le, 2) + m2 * powf(Z2, 2) + m4 * powf(X4, 2) + m5 * powf(Z5, 2) + m5 * powf(X5, 2) + m6 * powf(Z6, 2) + m6 * powf(X6, 2) + 2 * m6 * Lj * Lh2 + 2 * m6 * X6 * Lh1 + 2 * m6 * X6 * Lh2 + 2 * m6 * X6 * Lj + 2 * m5 * X5 * Lh1 + 2 * m5 * Lh2 * Lh1 + 2 * m5 * X5 * Lh2 + 2 * m6 * Lh2 * Lh1 + 2 * m6 * Lj * Lh1 + 2 * m4 * X4 * Lh1 + m3 * powf(Z3, 2) + m3 * powf(X3, 2) + 2 * m6 * Lii * Lg + m4 * powf(Lg, 2) + m5 * powf(Lg, 2);
  dyn.H22p2 = 2 * m3 * Z3 * Le + 2 * m4 * Lg * Le + 2 * m6 * Z6 * Le + 2 * m6 * Lii * Le + 2 * m6 * Lg * Le + 2 * m5 * Z5 * Le + 2 * m5 * Lg * Le;
  dyn.H22p3 = -2 * m4 * X4 * Le - 2 * m6 * Lh1 * Le - 2 * m5 * X5 * Le - 2 * m6 * Lh2 * Le - 2 * m5 * Lh2 * Le - 2 * m6 * Lj * Le - 2 * m4 * Lh1 * Le - 2 * m3 * X3 * Le - 2 * m6 * X6 * Le - 2 * m5 * Lh1 * Le;

  dyn.H23p1 = m6 * powf(Lii, 2) + m6 * powf(Lg, 2) + 2 * m6 * Z6 * Lii + 2 * m5 * Z5 * Lg + 2 * m6 * Z6 * Lg + m4 * powf(Lh1, 2) + m5 * powf(Lh2, 2) + m5 * powf(Lh1, 2) + I3y + I4y + I5y + m6 * powf(Lj, 2) + m6 * powf(Lh2, 2) + m6 * powf(Lh1, 2) + I6y + m4 * powf(X4, 2) + m5 * powf(Z5, 2) + m5 * powf(X5, 2) + m6 * powf(Z6, 2) + m6 * powf(X6, 2) + 2 * m6 * Lj * Lh2 + 2 * m6 * X6 * Lh1 + 2 * m6 * X6 * Lh2 + 2 * m6 * X6 * Lj + 2 * m5 * X5 * Lh1 + 2 * m5 * Lh2 * Lh1 + 2 * m5 * X5 * Lh2 + 2 * m6 * Lh2 * Lh1 + 2 * m6 * Lj * Lh1 + 2 * m4 * X4 * Lh1 + m3 * powf(Z3, 2) + m3 * powf(X3, 2) + 2 * m6 * Lii * Lg + m4 * powf(Lg, 2) + m5 * powf(Lg, 2);
  dyn.H23p2 = -m5 * Lh1 * Le - m6 * X6 * Le - m6 * Lh1 * Le - m4 * X4 * Le - m6 * Lh2 * Le - m5 * Lh2 * Le - m3 * X3 * Le - m5 * X5 * Le - m6 * Lj * Le - m4 * Lh1 * Le;
  dyn.H23p3 = m6 * Z6 * Le + m6 * Lg * Le + m4 * Lg * Le + m6 * Lii * Le + m5 * Lg * Le + m3 * Z3 * Le + m5 * Z5 * Le;

  dyn.H33p1 = m6 * powf(Lii, 2) + m6 * powf(Lg, 2) + 2 * m6 * Z6 * Lii + 2 * m5 * Z5 * Lg + 2 * m6 * Z6 * Lg + m4 * powf(Lh1, 2) + m5 * powf(Lh2, 2) + m5 * powf(Lh1, 2) + I3y + I4y + I5y + m6 * powf(Lj, 2) + m6 * powf(Lh2, 2) + m6 * powf(Lh1, 2) + I6y + m4 * powf(X4, 2) + m5 * powf(Z5, 2) + m5 * powf(X5, 2) + m6 * powf(Z6, 2) + m6 * powf(X6, 2) + 2 * m6 * Lj * Lh2 + 2 * m6 * X6 * Lh1 + 2 * m6 * X6 * Lh2 + 2 * m6 * X6 * Lj + 2 * m5 * X5 * Lh1 + 2 * m5 * Lh2 * Lh1 + 2 * m5 * X5 * Lh2 + 2 * m6 * Lh2 * Lh1 + 2 * m6 * Lj * Lh1 + 2 * m4 * X4 * Lh1 + m3 * powf(Z3, 2) + m3 * powf(X3, 2) + 2 * m6 * Lii * Lg + m4 * powf(Lg, 2) + m5 * powf(Lg, 2);
  dyn.b122p1 = m2 * Y2 * Z2;

  dyn.b112p1 = 2 * (0.5 * (2 * m6 * Z6 * Lii + 2 * m6 * Z6 * Lg - 2 * m4 * X4 * Lh1 - 2 * m6 * X6 * Lh1 - 2 * m6 * X6 * Lh2 - 2 * m6 * X6 * Lj - 2 * m5 * X5 * Lh1 - 2 * m5 * X5 * Lh2 - 2 * m5 * Lh2 * Lh1 - 2 * m6 * Lj * Lh1 - 2 * m6 * Lj * Lh2 - 2 * m6 * Lh2 * Lh1 + I5x - I5z - I4z + m6 * powf(Lii, 2) + I6x - I6z + m4 * powf(Lg, 2) + m5 * powf(Lg, 2) + m6 * powf(Lg, 2) + m5 * powf(Z5, 2) - m5 * powf(X5, 2) + m6 * powf(Z6, 2) - m6 * powf(X6, 2) - m4 * powf(X4, 2) + 2 * m6 * Lii * Lg + m3 * powf(Z3, 2) - m3 * powf(X3, 2) + I4x - m5 * powf(Lh2, 2) - m4 * powf(Lh1, 2) - m6 * powf(Lh2, 2) - m6 * powf(Lh1, 2) - m6 * powf(Lj, 2) - m5 * powf(Lh1, 2) + 2 * m5 * Z5 * Lg + I3x - I3z));
  dyn.b112p2 = 2 * (0.5 * (2 * m6 * X6 * Lg + 2 * m5 * Z5 * Lh1 + 2 * m6 * Lh1 * Lg + 2 * m6 * Lh2 * Lg + 2 * m6 * X6 * Z6 + 2 * m5 * X5 * Lg + 2 * m5 * Lh2 * Lg + 2 * m4 * Lh1 * Lg + 2 * m5 * X5 * Z5 + 2 * m3 * X3 * Z3 + 2 * m5 * Z5 * Lh2 + 2 * m6 * Lj * Lg + 2 * m4 * X4 * Lg + 2 * m6 * Z6 * Lh2 + 2 * m6 * Lii * Lh2 + 2 * m6 * X6 * Lii + 2 * m6 * Lj * Lii + 2 * m6 * Z6 * Lj + 2 * m5 * Lh1 * Lg + 2 * m6 * Z6 * Lh1 + 2 * m6 * Lii * Lh1));
  dyn.b112p3 = 2 * (0.5 * (m6 * powf(Le, 2) - I2z + m2 * powf(Z2, 2) + I2x + powf(Le, 2) * m3 + m4 * powf(Le, 2) + m5 * powf(Le, 2)));
  dyn.b112p4 = 2 * (0.5 * (2 * m6 * Z6 * Le + 2 * Le * m3 * Z3 + 2 * m5 * Lg * Le + 2 * m4 * Lg * Le + 2 * m6 * Lg * Le + 2 * m5 * Z5 * Le + 2 * m6 * Lii * Le));
  dyn.b112p5 = 2 * (m4 * Lg * Lb + m5 * Lg * Lb + m3 * Z3 * Lb + m6 * Lg * Lb + m6 * Z6 * Lb + m6 * Lii * Lb + m5 * Z5 * Lb);
  dyn.b112p6 = 2 * (m4 * Le * Lb + m6 * Le * Lb + m5 * Le * Lb + Le * m3 * Lb + m2 * Z2 * Lb);
  dyn.b112p7 = 2 * (-m5 * Lh1 * Lb - m6 * Lh1 * Lb - X4 * m4 * Lb - m6 * Lh2 * Lb - X5 * m5 * Lb - m6 * Lj * Lb - m4 * Lh1 * Lb - m5 * Lh2 * Lb - m3 * X3 * Lb - X6 * m6 * Lb);
  dyn.b112p8 = 2 * (0.5 * (2 * m6 * Lj * Le + 2 * m5 * Lh2 * Le + 2 * m6 * X6 * Le + 2 * m4 * X4 * Le + 2 * m5 * X5 * Le + 2 * m4 * Lh1 * Le + 2 * m3 * X3 * Le + 2 * m6 * Lh1 * Le + 2 * m6 * Lh2 * Le + 2 * m5 * Lh1 * Le));

  dyn.b113p1 = 2 * (-X6 * m6 * Lb - m5 * Lh1 * Lb - m6 * Lh1 * Lb - m6 * Lh2 * Lb - X5 * m5 * Lb - m6 * Lj * Lb - m4 * Lh1 * Lb - m3 * X3 * Lb - X4 * m4 * Lb - m5 * Lh2 * Lb);
  dyn.b113p2 = 2 * (+m3 * Z3 * Lb + m6 * Lg * Lb + m6 * Z6 * Lb + m6 * Lii * Lb + m5 * Z5 * Lb + m4 * Lg * Lb + m5 * Lg * Lb);
  dyn.b113p3 = 2 * (0.5 * (m5 * X5 * Le + m6 * Lh1 * Le + m6 * Lh2 * Le + m5 * Lh2 * Le + m4 * X4 * Le + m6 * X6 * Le + m3 * X3 * Le + m4 * Lh1 * Le + m6 * Lj * Le + m5 * Lh1 * Le));
  dyn.b113p4 = 2 * (0.5 * (m6 * Z6 * Le + Le * m3 * Z3 + m5 * Lg * Le + m4 * Lg * Le + m6 * Lg * Le + m5 * Z5 * Le + m6 * Lii * Le));
  dyn.b113p5 = 2 * (0.5 * (-m5 * X5 * Le - m6 * Lh1 * Le - m6 * Lh2 * Le - m5 * Lh2 * Le - m4 * X4 * Le - m6 * X6 * Le - m3 * X3 * Le - m4 * Lh1 * Le - m6 * Lj * Le - m5 * Lh1 * Le));
  dyn.b113p6 = 2 * (0.5 * (-m6 * Z6 * Le - Le * m3 * Z3 - m5 * Lg * Le - m4 * Lg * Le - m6 * Lg * Le - m5 * Z5 * Le - m6 * Lii * Le));
  dyn.b113p7 = 2 * (0.5 * (2 * m6 * X6 * Lg + 2 * m5 * Z5 * Lh1 + 2 * m6 * Lh1 * Lg + 2 * m6 * Lh2 * Lg + 2 * m6 * X6 * Z6 + 2 * m5 * X5 * Lg + 2 * m5 * Lh2 * Lg + 2 * m4 * Lh1 * Lg + 2 * m5 * X5 * Z5 + 2 * m3 * X3 * Z3 + 2 * m5 * Z5 * Lh2 + 2 * m6 * Lj * Lg + 2 * m4 * X4 * Lg + 2 * m6 * Z6 * Lh2 + 2 * m6 * Lii * Lh2 + 2 * m6 * X6 * Lii + 2 * m6 * Lj * Lii + 2 * m6 * Z6 * Lj + 2 * m5 * Lh1 * Lg + 2 * m6 * Z6 * Lh1 + 2 * m6 * Lii * Lh1));
  dyn.b113p8 = 2 * (0.5 * (2 * m6 * Z6 * Lii + 2 * m6 * Z6 * Lg - 2 * m4 * X4 * Lh1 - 2 * m6 * X6 * Lh1 - 2 * m6 * X6 * Lh2 - 2 * m6 * X6 * Lj - 2 * m5 * X5 * Lh1 - 2 * m5 * X5 * Lh2 - 2 * m5 * Lh2 * Lh1 - 2 * m6 * Lj * Lh1 - 2 * m6 * Lj * Lh2 - 2 * m6 * Lh2 * Lh1 + I5x - I5z - I4z + m6 * powf(Lii, 2) + I6x - I6z + m4 * powf(Lg, 2) + m5 * powf(Lg, 2) + m6 * powf(Lg, 2) + m5 * powf(Z5, 2) - m5 * powf(X5, 2) + m6 * powf(Z6, 2) - m6 * powf(X6, 2) - m4 * powf(X4, 2) + 2 * m6 * Lii * Lg + m3 * powf(Z3, 2) - m3 * powf(X3, 2) + I4x - m5 * powf(Lh2, 2) - m4 * powf(Lh1, 2) - m6 * powf(Lh2, 2) - m6 * powf(Lh1, 2) - m6 * powf(Lj, 2) - m5 * powf(Lh1, 2) + 2 * m5 * Z5 * Lg + I3x - I3z));

  dyn.b211p1 = (-m4 * Lg * Lb - m3 * Z3 * Lb - m5 * Z5 * Lb - m6 * Z6 * Lb - m6 * Lii * Lb - m6 * Lg * Lb - m5 * Lg * Lb);
  dyn.b211p2 = (+m4 * Lh1 * Lb + m6 * X6 * Lb + m5 * X5 * Lb + m6 * Lj * Lb + m4 * X4 * Lb + m5 * Lh2 * Lb + m5 * Lh1 * Lb + m6 * Lh2 * Lb + m6 * Lh1 * Lb + m3 * X3 * Lb);
  dyn.b211p3 = (-m5 * Le * Lb - m6 * Le * Lb - m4 * Le * Lb - Le * m3 * Lb - m2 * Z2 * Lb);
  dyn.b211p4 = (0.5 * (-2 * m6 * X6 * Lg - 2 * m5 * Z5 * Lh1 - 2 * m6 * Lh1 * Lg - 2 * m6 * Lh2 * Lg - 2 * m6 * X6 * Z6 - 2 * m5 * X5 * Lg - 2 * m5 * Lh2 * Lg - 2 * m4 * Lh1 * Lg - 2 * m5 * X5 * Z5 - 2 * m3 * X3 * Z3 - 2 * m5 * Z5 * Lh2 - 2 * m6 * Lj * Lg - 2 * m4 * X4 * Lg - 2 * m6 * Z6 * Lh2 - 2 * m6 * Lii * Lh2 - 2 * m6 * X6 * Lii - 2 * m6 * Lj * Lii - 2 * m6 * Z6 * Lj - 2 * m5 * Lh1 * Lg - 2 * m6 * Z6 * Lh1 - 2 * m6 * Lii * Lh1));
  dyn.b211p5 = (0.5 * (-2 * m5 * X5 * Le - 2 * m6 * Lh1 * Le - 2 * m6 * Lh2 * Le - 2 * m5 * Lh2 * Le - 2 * m4 * X4 * Le - 2 * m6 * X6 * Le - 2 * m3 * X3 * Le - 2 * m4 * Lh1 * Le - 2 * m6 * Lj * Le - 2 * m5 * Lh1 * Le));
  dyn.b211p6 = (0.5 * (-powf(Le, 2) * m3 - I2x - m5 * powf(Le, 2) - m2 * powf(Z2, 2) + I2z - m6 * powf(Le, 2) - m4 * powf(Le, 2)));
  dyn.b211p7 = (0.5 * (-2 * m6 * Z6 * Lii - 2 * m6 * Z6 * Lg + 2 * m4 * X4 * Lh1 + 2 * m6 * X6 * Lh1 + 2 * m6 * X6 * Lh2 + 2 * m6 * X6 * Lj + 2 * m5 * X5 * Lh1 + 2 * m5 * X5 * Lh2 + 2 * m5 * Lh2 * Lh1 + 2 * m6 * Lj * Lh1 + 2 * m6 * Lj * Lh2 + 2 * m6 * Lh2 * Lh1 - I5x + I5z + I4z - m6 * powf(Lii, 2) - I6x + I6z - m4 * powf(Lg, 2) - m5 * powf(Lg, 2) - m6 * powf(Lg, 2) - m5 * powf(Z5, 2) + m5 * powf(X5, 2) - m6 * powf(Z6, 2) + m6 * powf(X6, 2) + m4 * powf(X4, 2) - 2 * m6 * Lii * Lg - m3 * powf(Z3, 2) + m3 * powf(X3, 2) - I4x + m5 * powf(Lh2, 2) + m4 * powf(Lh1, 2) + m6 * powf(Lh2, 2) + m6 * powf(Lh1, 2) + m6 * powf(Lj, 2) + m5 * powf(Lh1, 2) - 2 * m5 * Z5 * Lg - I3x + I3z));
  dyn.b211p8 = (0.5 * (-2 * m6 * Lg * Le - 2 * m6 * Z6 * Le - 2 * m6 * Lii * Le - 2 * Le * m3 * Z3 - 2 * m4 * Lg * Le - 2 * m5 * Z5 * Le - 2 * m5 * Lg * Le));

  dyn.b233p1 = (-m5 * X5 * Le - m6 * Lh1 * Le - m6 * Lh2 * Le - m5 * Lh2 * Le - m4 * X4 * Le - m6 * X6 * Le - m3 * X3 * Le - m4 * Lh1 * Le - m6 * Lj * Le - m5 * Lh1 * Le);
  dyn.b233p2 = (-m5 * Lg * Le - m4 * Lg * Le - Le * m3 * Z3 - m6 * Z6 * Le - m5 * Z5 * Le - m6 * Lg * Le - m6 * Lii * Le);

  dyn.b223p1 = (-m5 * X5 * Le - m6 * Lh1 * Le - m6 * Lh2 * Le - m5 * Lh2 * Le - m4 * X4 * Le - m6 * X6 * Le - m3 * X3 * Le - m4 * Lh1 * Le - m6 * Lj * Le - m5 * Lh1 * Le);
  dyn.b223p2 = (-m5 * Lg * Le - m4 * Lg * Le - Le * m3 * Z3 - m6 * Z6 * Le - m5 * Z5 * Le - m6 * Lg * Le - m6 * Lii * Le);

  dyn.b311p1 = (m4 * X4 * Lb + m5 * Lh2 * Lb + m5 * Lh1 * Lb + m4 * Lh1 * Lb + m6 * X6 * Lb + m5 * X5 * Lb + m6 * Lj * Lb + m6 * Lh1 * Lb + m3 * X3 * Lb + m6 * Lh2 * Lb);
  dyn.b311p2 = (-m4 * Lg * Lb - m3 * Z3 * Lb - m5 * Z5 * Lb - m6 * Z6 * Lb - m6 * Lii * Lb - m6 * Lg * Lb - m5 * Lg * Lb);
  dyn.b311p3 = (0.5 * (-m5 * X5 * Le - m6 * Lh1 * Le - m6 * Lh2 * Le - m5 * Lh2 * Le - m4 * X4 * Le - m6 * X6 * Le - m3 * X3 * Le - m4 * Lh1 * Le - m6 * Lj * Le - m5 * Lh1 * Le));
  dyn.b311p4 = (0.5 * (-m5 * Lg * Le - m4 * Lg * Le - Le * m3 * Z3 - m6 * Z6 * Le - m5 * Z5 * Le - m6 * Lg * Le - m6 * Lii * Le));
  dyn.b311p5 = (0.5 * (m6 * Lh1 * Le + m5 * Lh2 * Le + m6 * X6 * Le + m6 * Lh2 * Le + m3 * X3 * Le + m5 * Lh1 * Le + m5 * X5 * Le + m4 * Lh1 * Le + m6 * Lj * Le + m4 * X4 * Le));
  dyn.b311p6 = (0.5 * (m6 * Z6 * Le + Le * m3 * Z3 + m5 * Lg * Le + m4 * Lg * Le + m6 * Lg * Le + m5 * Z5 * Le + m6 * Lii * Le));
  dyn.b311p7 = (0.5 * (-2 * m6 * X6 * Lg - 2 * m5 * Z5 * Lh1 - 2 * m6 * Lh1 * Lg - 2 * m6 * Lh2 * Lg - 2 * m6 * X6 * Z6 - 2 * m5 * X5 * Lg - 2 * m5 * Lh2 * Lg - 2 * m4 * Lh1 * Lg - 2 * m5 * X5 * Z5 - 2 * m3 * X3 * Z3 - 2 * m5 * Z5 * Lh2 - 2 * m6 * Lj * Lg - 2 * m4 * X4 * Lg - 2 * m6 * Z6 * Lh2 - 2 * m6 * Lii * Lh2 - 2 * m6 * X6 * Lii - 2 * m6 * Lj * Lii - 2 * m6 * Z6 * Lj - 2 * m5 * Lh1 * Lg - 2 * m6 * Z6 * Lh1 - 2 * m6 * Lii * Lh1));
  dyn.b311p8 = (0.5 * (-2 * m6 * Z6 * Lii - 2 * m6 * Z6 * Lg + 2 * m4 * X4 * Lh1 + 2 * m6 * X6 * Lh1 + 2 * m6 * X6 * Lh2 + 2 * m6 * X6 * Lj + 2 * m5 * X5 * Lh1 + 2 * m5 * X5 * Lh2 + 2 * m5 * Lh2 * Lh1 + 2 * m6 * Lj * Lh1 + 2 * m6 * Lj * Lh2 + 2 * m6 * Lh2 * Lh1 - I5x + I5z + I4z - m6 * powf(Lii, 2) - I6x + I6z - m4 * powf(Lg, 2) - m5 * powf(Lg, 2) - m6 * powf(Lg, 2) - m5 * powf(Z5, 2) + m5 * powf(X5, 2) - m6 * powf(Z6, 2) + m6 * powf(X6, 2) + m4 * powf(X4, 2) - 2 * m6 * Lii * Lg - m3 * powf(Z3, 2) + m3 * powf(X3, 2) - I4x + m5 * powf(Lh2, 2) + m4 * powf(Lh1, 2) + m6 * powf(Lh2, 2) + m6 * powf(Lh1, 2) + m6 * powf(Lj, 2) + m5 * powf(Lh1, 2) - 2 * m5 * Z5 * Lg - I3x + I3z));
  dyn.b322p1 = (m6 * Lh1 * Le + m5 * Lh2 * Le + m6 * X6 * Le + m6 * Lh2 * Le + m3 * X3 * Le + m5 * Lh1 * Le + m5 * X5 * Le + m4 * Lh1 * Le + m6 * Lj * Le + m4 * X4 * Le);
  dyn.b322p2 = (m6 * Z6 * Le + Le * m3 * Z3 + m5 * Lg * Le + m4 * Lg * Le + m6 * Lg * Le + m5 * Z5 * Le + m6 * Lii * Le);
  dyn.G2p1 = -m5 * g * Le - Z2 * m2 * g - m3 * g * Le - m6 * g * Le - m4 * g * Le;
  dyn.G2p2 = -Z3 * m3 * g - Z5 * m5 * g - m5 * g * Lg - m6 * g * Lg - m6 * g * Lii - m4 * g * Lg - Z6 * m6 * g;
  dyn.G2p3 = -m4 * g * Lh1 - X3 * m3 * g - m5 * g * Lh2 - X4 * m4 * g - X6 * m6 * g - m6 * g * Lh1 - X5 * m5 * g - m6 * g * Lj - m5 * g * Lh1 - m6 * g * Lh2;

  dyn.G3p1 = -Z3 * m3 * g - Z5 * m5 * g - m5 * g * Lg - m6 * g * Lg - m6 * g * Lii - m4 * g * Lg - Z6 * m6 * g;
  dyn.G3p2 = -m4 * g * Lh1 - X3 * m3 * g - m5 * g * Lh2 - X4 * m4 * g - X6 * m6 * g - m6 * g * Lh1 - X5 * m5 * g - m6 * g * Lj - m5 * g * Lh1 - m6 * g * Lh2;
}

/** @brief パラメータ設定
 */
void SetGain(Robot *robo)
{

  // 5軸パラメータ
  // LCR メータ測定値 300Hz (Rはテスターによる測定値)
  // robo[0].KpiQ = 72.0307;    // Q軸PI電流制御器 比例ゲイン
  // robo[0].KiiQ = 3.3822e+04; // Q軸PI電流制御器 積分ゲイン
  // robo[0].KpiD = 62.2126;    // D軸PI電流制御器 比例ゲイン
  // robo[0].KiiD = 3.3822e+04; // D軸PI電流制御器 積分ゲイン
  // robo[0].p = 4;		// 			モータ極対数
  // robo[0].Rd = 7.25;		// [Ω]		d軸抵抗
  // robo[0].Rq = 7.25;		// [Ω]		q軸抵抗
  // robo[0].Ld = 13.695e-3;		// [mH]		d軸インダクタンス
  // robo[0].Lq = 15.800e-3;		// [mH]		q軸インダクタンス
  // robo[0].Phifa = 65.808e-3;		// [Wb]		鎖交磁束数
  // robo[0].Ktn = robo[0].Phifa*robo[0].p;			// [Nm/A]	トルク定数
  // robo[0].Jmn = 1.8e-4;		// [kgm^2]	モータ側慣性モーメント
  // robo[0].Rgn	= 80.0;			// [-] ギア比

  // 5軸目 速度/位置制御ゲイン
  // robo[0].Kvi = 1.0057;
  // robo[0].Kvp = 0.0197;
  // robo[0].Kpp = 12.4346;

  // 電流制御系の帯域 1kHz => 6283 rad/s => 159.1 us (立ち上がり時間)
  // 1軸 LCRメータ測定値　300Hz (Rはテスタで測定)				T = Ts*exp(-Rd/Ld*Ts)/(1-exp(-Rd/Ld*Ts))
  robo[0].KpiQ = 12.8520;  // PI電流制御器 比例ゲイン		KpQ = ( 1-exp(-Wcd*Ts) )/( (Ts + T)/(T*Rq)*(1-exp(-Rq/Lq*Ts)) )
  robo[0].KiiQ = 3.2889e3; // PI電流制御器 積分ゲイン		KiQ = KpQ/T
  robo[0].KpiD = 10.4260;  // PI電流制御器 比例ゲイン		KpD = (1-exp(-Wcd*Ts))/( (Ts+T)/(T*Rd)*(1-exp(-Rd/Ld*Ts)) )
  robo[0].KiiD = 3.2889e3; // PI電流制御器 積分ゲイン		KiD = KpD/T
  robo[0].p = 4;
  robo[0].Rd = 0.64;                           // [Ω]		d軸抵抗
  robo[0].Rq = 0.64;                           // [Ω]		q軸抵抗
  robo[0].Ld = 2.224e-3;                       // [mH]		d軸インダクタンス
  robo[0].Lq = 2.795e-3;                       // [mH]		q軸インダクタンス
  robo[0].Phifa = 0.070504;                    // [Wb]		鎖交磁束数
  robo[0].Ktn = (robo[0].Phifa) * (robo[0].p); // [Nm/A] phaifa * pp	トルク定数
  robo[0].Rgn = 140.254;                       // 1軸ギア比

  robo[0].Jmn = 3.5947e-04;
  robo[0].Dln = 129.6700;
  robo[0].Dmn = 0;
  robo[0].Ksn = 92333;
  robo[0].Jln = 21.6184; // homeから2軸目20deg下げた場合(7.2kg負荷)

  // パナゲイン1軸目(適用値100%)
  robo[0].Kpp = 15;
  robo[0].Kff = 1.400;
  robo[0].Kfb = 0.400;
  robo[0].Kvp = 0.6071;
  robo[0].Kvi = 16.8644;
  // 倍率　
  // 50% 0.0536
  // 80% 0.7953
  robo[0].fwm = 1.0 * (-0.2986);
  robo[0].fqs = 1.0 * 0.2355;
  robo[0].fwl = 1.0 * 3.2483;

  robo[0].obp = -150; // [rad/s] sob極(重根)

  robo[0].ql_max = QL1_MAX * PI / 180.0;
  robo[0].ql_min = QL1_MIN * PI / 180.0;
  robo[0].qm_max = robo[0].ql_max * robo[0].Rgn;
  robo[0].qm_min = robo[0].ql_min * robo[0].Rgn;

  // 2軸 LCRメータ測定周波数  300Hz (Rはテスタで測定)				T = Ts*exp(-Rd/Ld*Ts)/(1-exp(-Rd/Ld*Ts))
  robo[1].KpiQ = 9.1576;   // PI電流制御器 比例ゲイン		KpQ = ( 1-exp(-Wcd*Ts) )/( (Ts + T)/(T*Rq)*(1-exp(-Rq/Lq*Ts)) )
  robo[1].KiiQ = 2.7991e3; // PI電流制御器 積分ゲイン		KiQ = KpQ/T
  robo[1].KpiD = 8.4026;   // PI電流制御器 比例ゲイン		KpD = (1-exp(-Wcd*Ts))/( (Ts+T)/(T*Rd)*(1-exp(-Rd/Ld*Ts)) )
  robo[1].KiiD = 2.7991e3; // PI電流制御器 積分ゲイン		KiD = KpD/T

  robo[1].p = 4;
  robo[1].Rd = 0.6;                            // [Ω]		d軸抵抗
  robo[1].Rq = 0.6;                            // [Ω]		q軸抵抗
  robo[1].Ld = 1.831e-3;                       // [mH]		d軸インダクタンス
  robo[1].Lq = 1.99285e-3;                     // [mH]		q軸インダクタンス
  robo[1].Phifa = 0.073547897136126;           // [Wb] 同定した2軸磁束鎖交数 (10回の2乗平均)
  robo[1].Ktn = (robo[1].Phifa) * (robo[1].p); // [Nm/A] phaifa * pp	トルク定数
  robo[1].Rgn = 121;                           // 2軸ギア比率

  robo[1].Jmn = 4.6370e-04;
  robo[1].Dln = 183.8800;
  robo[1].Dmn = 0;
  robo[1].Ksn = 92831;
  robo[1].Jln = 23.9666; // (7.2kg負荷)

  // 設計ゲイン 標準形 等価時定数 速度:0.05, 位置0.1
  robo[1].Kpp = 15.4593;
  robo[1].Kff = 1.400;
  robo[1].Kfb = 0.400;
  robo[1].Kvp = 0.1265;
  robo[1].Kvi = 3.7963;
  robo[1].fwm = 0.1628;
  robo[1].fqs = -1.4122e3;
  robo[1].fwl = -15.3162;

  // パナゲイン2軸目(適用値100%)
  // robo[1].Kpp = 15;
  // robo[1].Kvp = 1.0356;
  // robo[1].Kvi = 31.6207;
  // robo[1].fwm = 1.0 * (-0.0843);
  // robo[1].fqs = 1.0 * 0.9419;
  // robo[1].fwl = 1.0 * 1.6001;

  robo[1].obp = -150; // [rad/s] sob極(重根)

  robo[1].ql_max = QL2_MAX * PI / 180.0;
  robo[1].ql_min = QL2_MIN * PI / 180.0;
  robo[1].qm_max = robo[1].ql_max * robo[1].Rgn;
  robo[1].qm_min = robo[1].ql_min * robo[1].Rgn;

  // 3軸 LCRメータ測定値　300Hz (Rはテスタで測定)					 T = Ts*exp(-Rd/Ld*Ts)/(1-exp(-Rd/Ld*Ts))
  robo[2].KpiQ = 13.2473e+000; // PI電流制御器 比例ゲイン		KpQ = ( 1-exp(-Wcd*Ts) )/( (Ts + T)/(T*Rq)*(1-exp(-Rq/Lq*Ts)) )
  robo[2].KiiQ = 3.4055e+003;  // PI電流制御器 積分ゲイン		KiQ = KpQ/T
  robo[2].KpiD = 10.5347e+000; // PI電流制御器 比例ゲイン		KpD = (1-exp(-Wcd*Ts))/( (Ts+T)/(T*Rd)*(1-exp(-Rd/Ld*Ts)) )
  robo[2].KiiD = 3.4055e+003;  // PI電流制御器 積分ゲイン		KiD = KpD/T

  robo[2].p = 4;
  robo[2].Rd = 0.73;      // [Ω]		d軸抵抗
  robo[2].Rq = 0.73;      // [Ω]		q軸抵抗
  robo[2].Ld = 2.2945e-3; // [mH]		d軸インダクタンス
  robo[2].Lq = 2.8760e-3; // [mH]		q軸インダクタンス
                          // robo[2].Phifa = 63.1765e-003; // [Wb] 同定した３軸磁束鎖交数 (12回の2乗平均)
  //  robo[2].Phifa = 62e-003; // [Wb] 小さい
  robo[2].Phifa = 0.0631765;                   // [Wb] 洸さん再同定結果 20180606 大きい
                                               // robo[2].Phifa = 0.063; // [Wb] 調整値 めっちゃずれる。多分動摩擦で正確には合わない...とりあえず0.0631765を使うのがいいかも(20201003メモ)
  robo[2].Ktn = (robo[2].Phifa) * (robo[2].p); // [Nm/A] phaifa * pp	トルク定数
  robo[2].Rgn = 121;                           // 3軸ギア比率

  // 溝同定 動力学から再計算 D:\report\2019\1001_3軸目パラメータ同定\動力学計算からJall逆算して3軸目prms同定\calc_3axis_prms.m
  robo[2].Jmn = 2.4640e-04;
  robo[2].Dln = 89.42;
  robo[2].Dmn = 0;
  robo[2].Ksn = 1.7533e+04;
  robo[2].Jln = 8.3562; // home(7.2kg負荷)

  // 設計ゲイン
  robo[2].Kpp = 16.2426;
  robo[2].Kff = 1.400;
  robo[2].Kfb = 0.400;
  robo[2].Kvp = 0.1711;
  robo[2].Kvi = 5.1332;
  robo[2].fwm = -0.0134;
  robo[2].fqs = 107.3696;
  robo[2].fwl = 10.3055;

  // パナゲイン3軸目(適用値100%)
  // robo[2].Kpp = 15;
  // robo[2].Kvp = 0.4427;
  // robo[2].Kvi = 16.8644;
  // robo[2].fwm = 1.0 * (-0.1546);
  // robo[2].fqs = 1.0 * (-1.3186);
  // robo[2].fwl = 1.0 * (-2.3087);

  robo[2].obp = -150; // [rad/s] sob極(重根)

  robo[2].ql_max = QL3_MAX * PI / 180.0;
  robo[2].ql_min = QL3_MIN * PI / 180.0;
  robo[2].qm_max = robo[2].ql_max * robo[2].Rgn;
  robo[2].qm_min = robo[2].ql_min * robo[2].Rgn;
}

float Integrator_acc_ref(float u, const float Ts)
{
  // 加速度指令==>速度指令
  // 積分器の状態量の定義
  static float y = 0.0, yZ1 = 0.0, yZ = 0.0;

  yZ1 = Ts * u + yZ;
  yZ = yZ1;
  y = yZ1;
  return y;
}

float Integrator_w_ref(float u, const float Ts)
{
  // 速度指令==>位置指令
  // 積分器の状態量の定義
  static float y = 0.0, yZ1 = 0.0, yZ = 0.0;

  yZ1 = Ts * u + yZ;
  yZ = yZ1;
  y = yZ1;
  return y;
}

float Integrator_acc_ref2(float u, const float Ts)
{
  // 加速度指令==>速度指令
  // 積分器の状態量の定義
  static float y = 0.0, yZ1 = 0.0, yZ = 0.0;

  yZ1 = Ts * u + yZ;
  yZ = yZ1;
  y = yZ1;
  return y;
}

float Integrator_w_ref2(float u, const float Ts)
{
  // 速度指令==>位置指令
  // 積分器の状態量の定義
  static float y = 0.0, yZ1 = 0.0, yZ = 0.0;

  yZ1 = Ts * u + yZ;
  yZ = yZ1;
  y = yZ1;
  return y;
}
float Integrator_acc_ref3(float u, const float Ts)
{
  // 加速度指令==>速度指令
  // 積分器の状態量の定義
  static float y = 0.0, yZ1 = 0.0, yZ = 0.0;

  yZ1 = Ts * u + yZ;
  yZ = yZ1;
  y = yZ1;
  return y;
}

float Integrator_w_ref3(float u, const float Ts)
{
  // 速度指令==>位置指令
  // 積分器の状態量の定義
  static float y = 0.0, yZ1 = 0.0, yZ = 0.0;

  yZ1 = Ts * u + yZ;
  yZ = yZ1;
  y = yZ1;
  return y;
}