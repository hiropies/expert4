;******************************************************************************
;* TMS320C6x C/C++ Codegen                                         PC v7.4.24 *
;* Date/Time created: Thu Mar 13 16:30:35 2025                                *
;******************************************************************************
	.compiler_opts --abi=eabi --c64p_l1d_workaround=off --endian=little --hll_source=on --long_precision_bits=32 --mem_model:code=near --mem_model:const=data --mem_model:data=far_aggregates --object_format=elf --silicon_version=6600 --symdebug:dwarf_version=3 --symdebug:skeletal 

;******************************************************************************
;* GLOBAL FILE PARAMETERS                                                     *
;*                                                                            *
;*   Architecture      : TMS320C66xx                                          *
;*   Optimization      : Enabled at level 2                                   *
;*   Optimizing for    : Speed                                                *
;*                       Based on options: -o2, no -ms                        *
;*   Endian            : Little                                               *
;*   Interrupt Thrshld : Disabled                                             *
;*   Data Access Model : Far Aggregate Data                                   *
;*   Pipelining        : Enabled                                              *
;*   Speculate Loads   : Enabled with threshold = 0                           *
;*   Memory Aliases    : Presume are aliases (pessimistic)                    *
;*   Debug Info        : DWARF Debug for Program Analysis w/Optimization      *
;*                                                                            *
;******************************************************************************

	.asg	A15, FP
	.asg	B14, DP
	.asg	B15, SP
	.global	$bss


$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("current_control_ver2_new.c")
	.dwattr $C$DW$CU, DW_AT_producer("TI TMS320C6x C/C++ Codegen PC v7.4.24 Copyright (c) 1996-2017 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("D:\Desktop\abeé¿å±\20250312_DPD\DPD")

$C$DW$1	.dwtag  DW_TAG_subprogram, DW_AT_name("_spint")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("_spint")
	.dwattr $C$DW$1, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_decl_file("C:/ti/bin/../include/c6x.h")
	.dwattr $C$DW$1, DW_AT_decl_line(0xcc)
	.dwattr $C$DW$1, DW_AT_decl_column(0x0b)
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$16)
	.dwendtag $C$DW$1


$C$DW$3	.dwtag  DW_TAG_subprogram, DW_AT_name("mw_platform_delaycycles")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("mw_platform_delaycycles")
	.dwattr $C$DW$3, DW_AT_declaration
	.dwattr $C$DW$3, DW_AT_external
	.dwattr $C$DW$3, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\mw_platform.h")
	.dwattr $C$DW$3, DW_AT_decl_line(0x166)
	.dwattr $C$DW$3, DW_AT_decl_column(0x06)
$C$DW$4	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$19)
	.dwendtag $C$DW$3


$C$DW$5	.dwtag  DW_TAG_subprogram, DW_AT_name("IRQ_globalEnable")
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("IRQ_globalEnable")
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$5, DW_AT_declaration
	.dwattr $C$DW$5, DW_AT_external
	.dwattr $C$DW$5, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\mwintc.h")
	.dwattr $C$DW$5, DW_AT_decl_line(0x25)
	.dwattr $C$DW$5, DW_AT_decl_column(0x11)

$C$DW$6	.dwtag  DW_TAG_subprogram, DW_AT_name("IRQ_globalDisable")
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("IRQ_globalDisable")
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$6, DW_AT_declaration
	.dwattr $C$DW$6, DW_AT_external
	.dwattr $C$DW$6, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\mwintc.h")
	.dwattr $C$DW$6, DW_AT_decl_line(0x26)
	.dwattr $C$DW$6, DW_AT_decl_column(0x11)

$C$DW$7	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer1_init")
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("C6657_timer1_init")
	.dwattr $C$DW$7, DW_AT_declaration
	.dwattr $C$DW$7, DW_AT_external
	.dwattr $C$DW$7, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$7, DW_AT_decl_line(0xd0)
	.dwattr $C$DW$7, DW_AT_decl_column(0x0d)
$C$DW$8	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$7


$C$DW$9	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer1_start")
	.dwattr $C$DW$9, DW_AT_TI_symbol_name("C6657_timer1_start")
	.dwattr $C$DW$9, DW_AT_declaration
	.dwattr $C$DW$9, DW_AT_external
	.dwattr $C$DW$9, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$9, DW_AT_decl_line(0xd1)
	.dwattr $C$DW$9, DW_AT_decl_column(0x0d)

$C$DW$10	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer1_stop")
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("C6657_timer1_stop")
	.dwattr $C$DW$10, DW_AT_declaration
	.dwattr $C$DW$10, DW_AT_external
	.dwattr $C$DW$10, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$10, DW_AT_decl_line(0xd2)
	.dwattr $C$DW$10, DW_AT_decl_column(0x0d)

$C$DW$11	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer1_read")
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("C6657_timer1_read")
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$11, DW_AT_declaration
	.dwattr $C$DW$11, DW_AT_external
	.dwattr $C$DW$11, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$11, DW_AT_decl_line(0xd4)
	.dwattr $C$DW$11, DW_AT_decl_column(0x0f)

$C$DW$12	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer1_clear")
	.dwattr $C$DW$12, DW_AT_TI_symbol_name("C6657_timer1_clear")
	.dwattr $C$DW$12, DW_AT_declaration
	.dwattr $C$DW$12, DW_AT_external
	.dwattr $C$DW$12, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$12, DW_AT_decl_line(0xd5)
	.dwattr $C$DW$12, DW_AT_decl_column(0x0d)

$C$DW$13	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer1_disable_int")
	.dwattr $C$DW$13, DW_AT_TI_symbol_name("C6657_timer1_disable_int")
	.dwattr $C$DW$13, DW_AT_declaration
	.dwattr $C$DW$13, DW_AT_external
	.dwattr $C$DW$13, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$13, DW_AT_decl_line(0xdc)
	.dwattr $C$DW$13, DW_AT_decl_column(0x0d)

$C$DW$14	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer2_init")
	.dwattr $C$DW$14, DW_AT_TI_symbol_name("C6657_timer2_init")
	.dwattr $C$DW$14, DW_AT_declaration
	.dwattr $C$DW$14, DW_AT_external
	.dwattr $C$DW$14, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$14, DW_AT_decl_line(0xe1)
	.dwattr $C$DW$14, DW_AT_decl_column(0x0d)
$C$DW$15	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$15, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$14


$C$DW$16	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer2_start")
	.dwattr $C$DW$16, DW_AT_TI_symbol_name("C6657_timer2_start")
	.dwattr $C$DW$16, DW_AT_declaration
	.dwattr $C$DW$16, DW_AT_external
	.dwattr $C$DW$16, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$16, DW_AT_decl_line(0xe2)
	.dwattr $C$DW$16, DW_AT_decl_column(0x0d)

$C$DW$17	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer2_stop")
	.dwattr $C$DW$17, DW_AT_TI_symbol_name("C6657_timer2_stop")
	.dwattr $C$DW$17, DW_AT_declaration
	.dwattr $C$DW$17, DW_AT_external
	.dwattr $C$DW$17, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$17, DW_AT_decl_line(0xe3)
	.dwattr $C$DW$17, DW_AT_decl_column(0x0d)

$C$DW$18	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer2_read")
	.dwattr $C$DW$18, DW_AT_TI_symbol_name("C6657_timer2_read")
	.dwattr $C$DW$18, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$18, DW_AT_declaration
	.dwattr $C$DW$18, DW_AT_external
	.dwattr $C$DW$18, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$18, DW_AT_decl_line(0xe5)
	.dwattr $C$DW$18, DW_AT_decl_column(0x0f)

$C$DW$19	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer2_clear")
	.dwattr $C$DW$19, DW_AT_TI_symbol_name("C6657_timer2_clear")
	.dwattr $C$DW$19, DW_AT_declaration
	.dwattr $C$DW$19, DW_AT_external
	.dwattr $C$DW$19, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$19, DW_AT_decl_line(0xe6)
	.dwattr $C$DW$19, DW_AT_decl_column(0x0d)

$C$DW$20	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer2_disable_int")
	.dwattr $C$DW$20, DW_AT_TI_symbol_name("C6657_timer2_disable_int")
	.dwattr $C$DW$20, DW_AT_declaration
	.dwattr $C$DW$20, DW_AT_external
	.dwattr $C$DW$20, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$20, DW_AT_decl_line(0xed)
	.dwattr $C$DW$20, DW_AT_decl_column(0x0d)

$C$DW$21	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer0_init")
	.dwattr $C$DW$21, DW_AT_TI_symbol_name("C6657_timer0_init")
	.dwattr $C$DW$21, DW_AT_declaration
	.dwattr $C$DW$21, DW_AT_external
	.dwattr $C$DW$21, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$21, DW_AT_decl_line(0xf2)
	.dwattr $C$DW$21, DW_AT_decl_column(0x0d)
$C$DW$22	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$22, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$21


$C$DW$23	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer0_start")
	.dwattr $C$DW$23, DW_AT_TI_symbol_name("C6657_timer0_start")
	.dwattr $C$DW$23, DW_AT_declaration
	.dwattr $C$DW$23, DW_AT_external
	.dwattr $C$DW$23, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$23, DW_AT_decl_line(0xf3)
	.dwattr $C$DW$23, DW_AT_decl_column(0x0d)

$C$DW$24	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer0_stop")
	.dwattr $C$DW$24, DW_AT_TI_symbol_name("C6657_timer0_stop")
	.dwattr $C$DW$24, DW_AT_declaration
	.dwattr $C$DW$24, DW_AT_external
	.dwattr $C$DW$24, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$24, DW_AT_decl_line(0xf4)
	.dwattr $C$DW$24, DW_AT_decl_column(0x0d)

$C$DW$25	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer0_read")
	.dwattr $C$DW$25, DW_AT_TI_symbol_name("C6657_timer0_read")
	.dwattr $C$DW$25, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$25, DW_AT_declaration
	.dwattr $C$DW$25, DW_AT_external
	.dwattr $C$DW$25, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$25, DW_AT_decl_line(0xf6)
	.dwattr $C$DW$25, DW_AT_decl_column(0x0f)

$C$DW$26	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer0_clear")
	.dwattr $C$DW$26, DW_AT_TI_symbol_name("C6657_timer0_clear")
	.dwattr $C$DW$26, DW_AT_declaration
	.dwattr $C$DW$26, DW_AT_external
	.dwattr $C$DW$26, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$26, DW_AT_decl_line(0xf7)
	.dwattr $C$DW$26, DW_AT_decl_column(0x0d)

$C$DW$27	.dwtag  DW_TAG_subprogram, DW_AT_name("C6657_timer0_disable_int")
	.dwattr $C$DW$27, DW_AT_TI_symbol_name("C6657_timer0_disable_int")
	.dwattr $C$DW$27, DW_AT_declaration
	.dwattr $C$DW$27, DW_AT_external
	.dwattr $C$DW$27, DW_AT_decl_file("C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\inc\timer_lib.h")
	.dwattr $C$DW$27, DW_AT_decl_line(0xfe)
	.dwattr $C$DW$27, DW_AT_decl_column(0x0d)

$C$DW$28	.dwtag  DW_TAG_subprogram, DW_AT_name("sqrtf")
	.dwattr $C$DW$28, DW_AT_TI_symbol_name("sqrtf")
	.dwattr $C$DW$28, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$28, DW_AT_declaration
	.dwattr $C$DW$28, DW_AT_external
	.dwattr $C$DW$28, DW_AT_decl_file("C:/ti/bin/../include/mathf.h")
	.dwattr $C$DW$28, DW_AT_decl_line(0x91)
	.dwattr $C$DW$28, DW_AT_decl_column(0x10)
$C$DW$29	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$29, DW_AT_type(*$C$DW$T$16)
	.dwendtag $C$DW$28


$C$DW$30	.dwtag  DW_TAG_subprogram, DW_AT_name("expf")
	.dwattr $C$DW$30, DW_AT_TI_symbol_name("expf")
	.dwattr $C$DW$30, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$30, DW_AT_declaration
	.dwattr $C$DW$30, DW_AT_external
	.dwattr $C$DW$30, DW_AT_decl_file("C:/ti/bin/../include/mathf.h")
	.dwattr $C$DW$30, DW_AT_decl_line(0x92)
	.dwattr $C$DW$30, DW_AT_decl_column(0x10)
$C$DW$31	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$31, DW_AT_type(*$C$DW$T$16)
	.dwendtag $C$DW$30


$C$DW$32	.dwtag  DW_TAG_subprogram, DW_AT_name("powf")
	.dwattr $C$DW$32, DW_AT_TI_symbol_name("powf")
	.dwattr $C$DW$32, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$32, DW_AT_declaration
	.dwattr $C$DW$32, DW_AT_external
	.dwattr $C$DW$32, DW_AT_decl_file("C:/ti/bin/../include/mathf.h")
	.dwattr $C$DW$32, DW_AT_decl_line(0x95)
	.dwattr $C$DW$32, DW_AT_decl_column(0x10)
$C$DW$33	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$33, DW_AT_type(*$C$DW$T$16)
$C$DW$34	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$34, DW_AT_type(*$C$DW$T$16)
	.dwendtag $C$DW$32


$C$DW$35	.dwtag  DW_TAG_subprogram, DW_AT_name("atan2f")
	.dwattr $C$DW$35, DW_AT_TI_symbol_name("atan2f")
	.dwattr $C$DW$35, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$35, DW_AT_declaration
	.dwattr $C$DW$35, DW_AT_external
	.dwattr $C$DW$35, DW_AT_decl_file("C:/ti/bin/../include/mathf.h")
	.dwattr $C$DW$35, DW_AT_decl_line(0x9c)
	.dwattr $C$DW$35, DW_AT_decl_column(0x10)
$C$DW$36	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$36, DW_AT_type(*$C$DW$T$16)
$C$DW$37	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$37, DW_AT_type(*$C$DW$T$16)
	.dwendtag $C$DW$35


$C$DW$38	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_init")
	.dwattr $C$DW$38, DW_AT_TI_symbol_name("PEV_init")
	.dwattr $C$DW$38, DW_AT_declaration
	.dwattr $C$DW$38, DW_AT_external
	.dwattr $C$DW$38, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$38, DW_AT_decl_line(0x36)
	.dwattr $C$DW$38, DW_AT_decl_column(0x07)
$C$DW$39	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$39, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$38


$C$DW$40	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_inverter_init")
	.dwattr $C$DW$40, DW_AT_TI_symbol_name("PEV_inverter_init")
	.dwattr $C$DW$40, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$40, DW_AT_declaration
	.dwattr $C$DW$40, DW_AT_external
	.dwattr $C$DW$40, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$40, DW_AT_decl_line(0x4b)
	.dwattr $C$DW$40, DW_AT_decl_column(0x08)
$C$DW$41	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$41, DW_AT_type(*$C$DW$T$102)
$C$DW$42	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$42, DW_AT_type(*$C$DW$T$102)
$C$DW$43	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$43, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$40


$C$DW$44	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_inverter_init_refload_timing")
	.dwattr $C$DW$44, DW_AT_TI_symbol_name("PEV_inverter_init_refload_timing")
	.dwattr $C$DW$44, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$44, DW_AT_declaration
	.dwattr $C$DW$44, DW_AT_external
	.dwattr $C$DW$44, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$44, DW_AT_decl_line(0x4d)
	.dwattr $C$DW$44, DW_AT_decl_column(0x08)
$C$DW$45	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$45, DW_AT_type(*$C$DW$T$102)
$C$DW$46	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$46, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$44


$C$DW$47	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_inverter_start_pwm")
	.dwattr $C$DW$47, DW_AT_TI_symbol_name("PEV_inverter_start_pwm")
	.dwattr $C$DW$47, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$47, DW_AT_declaration
	.dwattr $C$DW$47, DW_AT_external
	.dwattr $C$DW$47, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$47, DW_AT_decl_line(0x4e)
	.dwattr $C$DW$47, DW_AT_decl_column(0x08)
$C$DW$48	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$48, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$47


$C$DW$49	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_inverter_set_uvw")
	.dwattr $C$DW$49, DW_AT_TI_symbol_name("PEV_inverter_set_uvw")
	.dwattr $C$DW$49, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$49, DW_AT_declaration
	.dwattr $C$DW$49, DW_AT_external
	.dwattr $C$DW$49, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$49, DW_AT_decl_line(0x50)
	.dwattr $C$DW$49, DW_AT_decl_column(0x08)
$C$DW$50	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$50, DW_AT_type(*$C$DW$T$102)
$C$DW$51	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$51, DW_AT_type(*$C$DW$T$103)
$C$DW$52	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$52, DW_AT_type(*$C$DW$T$103)
$C$DW$53	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$53, DW_AT_type(*$C$DW$T$103)
$C$DW$54	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$54, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$49


$C$DW$55	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_inverter_set_uvw_br")
	.dwattr $C$DW$55, DW_AT_TI_symbol_name("PEV_inverter_set_uvw_br")
	.dwattr $C$DW$55, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$55, DW_AT_declaration
	.dwattr $C$DW$55, DW_AT_external
	.dwattr $C$DW$55, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$55, DW_AT_decl_line(0x51)
	.dwattr $C$DW$55, DW_AT_decl_column(0x08)
$C$DW$56	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$56, DW_AT_type(*$C$DW$T$102)
$C$DW$57	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$57, DW_AT_type(*$C$DW$T$103)
$C$DW$58	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$58, DW_AT_type(*$C$DW$T$103)
$C$DW$59	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$59, DW_AT_type(*$C$DW$T$103)
$C$DW$60	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$60, DW_AT_type(*$C$DW$T$103)
$C$DW$61	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$61, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$55


$C$DW$62	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_inverter_control_break")
	.dwattr $C$DW$62, DW_AT_TI_symbol_name("PEV_inverter_control_break")
	.dwattr $C$DW$62, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$62, DW_AT_declaration
	.dwattr $C$DW$62, DW_AT_external
	.dwattr $C$DW$62, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$62, DW_AT_decl_line(0x55)
	.dwattr $C$DW$62, DW_AT_decl_column(0x08)
$C$DW$63	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$63, DW_AT_type(*$C$DW$T$102)
$C$DW$64	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$64, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$62


$C$DW$65	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_inverter_init_adtrig_timing")
	.dwattr $C$DW$65, DW_AT_TI_symbol_name("PEV_inverter_init_adtrig_timing")
	.dwattr $C$DW$65, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$65, DW_AT_declaration
	.dwattr $C$DW$65, DW_AT_external
	.dwattr $C$DW$65, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$65, DW_AT_decl_line(0x56)
	.dwattr $C$DW$65, DW_AT_decl_column(0x08)
$C$DW$66	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$66, DW_AT_type(*$C$DW$T$102)
$C$DW$67	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$67, DW_AT_type(*$C$DW$T$102)
$C$DW$68	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$68, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$65


$C$DW$69	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_inverter_enable_int")
	.dwattr $C$DW$69, DW_AT_TI_symbol_name("PEV_inverter_enable_int")
	.dwattr $C$DW$69, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$69, DW_AT_declaration
	.dwattr $C$DW$69, DW_AT_external
	.dwattr $C$DW$69, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$69, DW_AT_decl_line(0x57)
	.dwattr $C$DW$69, DW_AT_decl_column(0x08)
$C$DW$70	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$70, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$69


$C$DW$71	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_ad_set_range")
	.dwattr $C$DW$71, DW_AT_TI_symbol_name("PEV_ad_set_range")
	.dwattr $C$DW$71, DW_AT_declaration
	.dwattr $C$DW$71, DW_AT_external
	.dwattr $C$DW$71, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$71, DW_AT_decl_line(0x6a)
	.dwattr $C$DW$71, DW_AT_decl_column(0x06)
$C$DW$72	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$72, DW_AT_type(*$C$DW$T$102)
$C$DW$73	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$73, DW_AT_type(*$C$DW$T$109)
	.dwendtag $C$DW$71


$C$DW$74	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_ad_set_mode")
	.dwattr $C$DW$74, DW_AT_TI_symbol_name("PEV_ad_set_mode")
	.dwattr $C$DW$74, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$74, DW_AT_declaration
	.dwattr $C$DW$74, DW_AT_external
	.dwattr $C$DW$74, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$74, DW_AT_decl_line(0x6c)
	.dwattr $C$DW$74, DW_AT_decl_column(0x07)
$C$DW$75	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$75, DW_AT_type(*$C$DW$T$102)
$C$DW$76	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$76, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$74


$C$DW$77	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_ad_in_grp")
	.dwattr $C$DW$77, DW_AT_TI_symbol_name("PEV_ad_in_grp")
	.dwattr $C$DW$77, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$77, DW_AT_declaration
	.dwattr $C$DW$77, DW_AT_external
	.dwattr $C$DW$77, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$77, DW_AT_decl_line(0x6d)
	.dwattr $C$DW$77, DW_AT_decl_column(0x07)
$C$DW$78	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$78, DW_AT_type(*$C$DW$T$102)
$C$DW$79	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$79, DW_AT_type(*$C$DW$T$109)
	.dwendtag $C$DW$77


$C$DW$80	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_ad_disable_int")
	.dwattr $C$DW$80, DW_AT_TI_symbol_name("PEV_ad_disable_int")
	.dwattr $C$DW$80, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$80, DW_AT_declaration
	.dwattr $C$DW$80, DW_AT_external
	.dwattr $C$DW$80, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$80, DW_AT_decl_line(0x71)
	.dwattr $C$DW$80, DW_AT_decl_column(0x07)
$C$DW$81	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$81, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$80


$C$DW$82	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_ad_in_st")
	.dwattr $C$DW$82, DW_AT_TI_symbol_name("PEV_ad_in_st")
	.dwattr $C$DW$82, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$82, DW_AT_declaration
	.dwattr $C$DW$82, DW_AT_external
	.dwattr $C$DW$82, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$82, DW_AT_decl_line(0x73)
	.dwattr $C$DW$82, DW_AT_decl_column(0x07)
$C$DW$83	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$83, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$82


$C$DW$84	.dwtag  DW_TAG_subprogram, DW_AT_name("GPI_int_ack_vo")
	.dwattr $C$DW$84, DW_AT_TI_symbol_name("GPI_int_ack_vo")
	.dwattr $C$DW$84, DW_AT_declaration
	.dwattr $C$DW$84, DW_AT_external
	.dwattr $C$DW$84, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$84, DW_AT_decl_line(0x144)
	.dwattr $C$DW$84, DW_AT_decl_column(0x0d)
$C$DW$85	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$85, DW_AT_type(*$C$DW$T$23)
	.dwendtag $C$DW$84


$C$DW$86	.dwtag  DW_TAG_subprogram, DW_AT_name("GPI_setVector_vo")
	.dwattr $C$DW$86, DW_AT_TI_symbol_name("GPI_setVector_vo")
	.dwattr $C$DW$86, DW_AT_declaration
	.dwattr $C$DW$86, DW_AT_external
	.dwattr $C$DW$86, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$86, DW_AT_decl_line(0x146)
	.dwattr $C$DW$86, DW_AT_decl_column(0x0d)
$C$DW$87	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$87, DW_AT_type(*$C$DW$T$23)
$C$DW$88	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$88, DW_AT_type(*$C$DW$T$52)
$C$DW$89	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$89, DW_AT_type(*$C$DW$T$240)
$C$DW$90	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$90, DW_AT_type(*$C$DW$T$56)
	.dwendtag $C$DW$86


$C$DW$91	.dwtag  DW_TAG_subprogram, DW_AT_name("GPI_enable_int_vo")
	.dwattr $C$DW$91, DW_AT_TI_symbol_name("GPI_enable_int_vo")
	.dwattr $C$DW$91, DW_AT_declaration
	.dwattr $C$DW$91, DW_AT_external
	.dwattr $C$DW$91, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$91, DW_AT_decl_line(0x14e)
	.dwattr $C$DW$91, DW_AT_decl_column(0x0d)
$C$DW$92	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$92, DW_AT_type(*$C$DW$T$23)
	.dwendtag $C$DW$91


$C$DW$93	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_int_init")
	.dwattr $C$DW$93, DW_AT_TI_symbol_name("PEV_int_init")
	.dwattr $C$DW$93, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$93, DW_AT_declaration
	.dwattr $C$DW$93, DW_AT_external
	.dwattr $C$DW$93, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$93, DW_AT_decl_line(0x1c3)
	.dwattr $C$DW$93, DW_AT_decl_column(0x09)
$C$DW$94	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$94, DW_AT_type(*$C$DW$T$102)
$C$DW$95	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$95, DW_AT_type(*$C$DW$T$102)
$C$DW$96	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$96, DW_AT_type(*$C$DW$T$102)
$C$DW$97	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$97, DW_AT_type(*$C$DW$T$102)
$C$DW$98	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$98, DW_AT_type(*$C$DW$T$102)
$C$DW$99	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$99, DW_AT_type(*$C$DW$T$102)
$C$DW$100	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$100, DW_AT_type(*$C$DW$T$102)
$C$DW$101	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$101, DW_AT_type(*$C$DW$T$102)
$C$DW$102	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$102, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$93


$C$DW$103	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_sync_pwm_init")
	.dwattr $C$DW$103, DW_AT_TI_symbol_name("PEV_sync_pwm_init")
	.dwattr $C$DW$103, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$103, DW_AT_declaration
	.dwattr $C$DW$103, DW_AT_external
	.dwattr $C$DW$103, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$103, DW_AT_decl_line(0x1c7)
	.dwattr $C$DW$103, DW_AT_decl_column(0x08)
$C$DW$104	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$104, DW_AT_type(*$C$DW$T$102)
$C$DW$105	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$105, DW_AT_type(*$C$DW$T$102)
$C$DW$106	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$106, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$103


$C$DW$107	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_sync_pwm_out")
	.dwattr $C$DW$107, DW_AT_TI_symbol_name("PEV_sync_pwm_out")
	.dwattr $C$DW$107, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$107, DW_AT_declaration
	.dwattr $C$DW$107, DW_AT_external
	.dwattr $C$DW$107, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$107, DW_AT_decl_line(0x1c8)
	.dwattr $C$DW$107, DW_AT_decl_column(0x08)
$C$DW$108	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$108, DW_AT_type(*$C$DW$T$102)
$C$DW$109	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$109, DW_AT_type(*$C$DW$T$102)
$C$DW$110	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$110, DW_AT_type(*$C$DW$T$102)
$C$DW$111	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$111, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$107


$C$DW$112	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_sync_ad_init")
	.dwattr $C$DW$112, DW_AT_TI_symbol_name("PEV_sync_ad_init")
	.dwattr $C$DW$112, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$112, DW_AT_declaration
	.dwattr $C$DW$112, DW_AT_external
	.dwattr $C$DW$112, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$112, DW_AT_decl_line(0x1c9)
	.dwattr $C$DW$112, DW_AT_decl_column(0x08)
$C$DW$113	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$113, DW_AT_type(*$C$DW$T$102)
$C$DW$114	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$114, DW_AT_type(*$C$DW$T$102)
$C$DW$115	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$115, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$112


$C$DW$116	.dwtag  DW_TAG_subprogram, DW_AT_name("PEV_sync_ad_out")
	.dwattr $C$DW$116, DW_AT_TI_symbol_name("PEV_sync_ad_out")
	.dwattr $C$DW$116, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$116, DW_AT_declaration
	.dwattr $C$DW$116, DW_AT_external
	.dwattr $C$DW$116, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$116, DW_AT_decl_line(0x1ca)
	.dwattr $C$DW$116, DW_AT_decl_column(0x08)
$C$DW$117	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$117, DW_AT_type(*$C$DW$T$102)
$C$DW$118	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$118, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$116


$C$DW$119	.dwtag  DW_TAG_subprogram, DW_AT_name("ENC_ss_init")
	.dwattr $C$DW$119, DW_AT_TI_symbol_name("ENC_ss_init")
	.dwattr $C$DW$119, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$119, DW_AT_declaration
	.dwattr $C$DW$119, DW_AT_external
	.dwattr $C$DW$119, DW_AT_decl_file("enc.h")
	.dwattr $C$DW$119, DW_AT_decl_line(0x7e)
	.dwattr $C$DW$119, DW_AT_decl_column(0x07)
$C$DW$120	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$120, DW_AT_type(*$C$DW$T$102)
$C$DW$121	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$121, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$119


$C$DW$122	.dwtag  DW_TAG_subprogram, DW_AT_name("ENC_ss_get_start")
	.dwattr $C$DW$122, DW_AT_TI_symbol_name("ENC_ss_get_start")
	.dwattr $C$DW$122, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$122, DW_AT_declaration
	.dwattr $C$DW$122, DW_AT_external
	.dwattr $C$DW$122, DW_AT_decl_file("enc.h")
	.dwattr $C$DW$122, DW_AT_decl_line(0x87)
	.dwattr $C$DW$122, DW_AT_decl_column(0x07)
$C$DW$123	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$123, DW_AT_type(*$C$DW$T$102)
$C$DW$124	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$124, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$122


$C$DW$125	.dwtag  DW_TAG_subprogram, DW_AT_name("ENC_ss_get_abs")
	.dwattr $C$DW$125, DW_AT_TI_symbol_name("ENC_ss_get_abs")
	.dwattr $C$DW$125, DW_AT_type(*$C$DW$T$102)
	.dwattr $C$DW$125, DW_AT_declaration
	.dwattr $C$DW$125, DW_AT_external
	.dwattr $C$DW$125, DW_AT_decl_file("enc.h")
	.dwattr $C$DW$125, DW_AT_decl_line(0x90)
	.dwattr $C$DW$125, DW_AT_decl_column(0x07)
$C$DW$126	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$126, DW_AT_type(*$C$DW$T$102)
$C$DW$127	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$127, DW_AT_type(*$C$DW$T$102)
	.dwendtag $C$DW$125


$C$DW$128	.dwtag  DW_TAG_subprogram, DW_AT_name("sqrt")
	.dwattr $C$DW$128, DW_AT_TI_symbol_name("sqrt")
	.dwattr $C$DW$128, DW_AT_type(*$C$DW$T$17)
	.dwattr $C$DW$128, DW_AT_declaration
	.dwattr $C$DW$128, DW_AT_external
	.dwattr $C$DW$128, DW_AT_decl_file("C:/ti/bin/../include/math.h")
	.dwattr $C$DW$128, DW_AT_decl_line(0x4c)
	.dwattr $C$DW$128, DW_AT_decl_column(0x11)
$C$DW$129	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$129, DW_AT_type(*$C$DW$T$17)
	.dwendtag $C$DW$128


$C$DW$130	.dwtag  DW_TAG_subprogram, DW_AT_name("sin")
	.dwattr $C$DW$130, DW_AT_TI_symbol_name("sin")
	.dwattr $C$DW$130, DW_AT_type(*$C$DW$T$17)
	.dwattr $C$DW$130, DW_AT_declaration
	.dwattr $C$DW$130, DW_AT_external
	.dwattr $C$DW$130, DW_AT_decl_file("C:/ti/bin/../include/math.h")
	.dwattr $C$DW$130, DW_AT_decl_line(0x51)
	.dwattr $C$DW$130, DW_AT_decl_column(0x11)
$C$DW$131	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$131, DW_AT_type(*$C$DW$T$17)
	.dwendtag $C$DW$130


$C$DW$132	.dwtag  DW_TAG_subprogram, DW_AT_name("cos")
	.dwattr $C$DW$132, DW_AT_TI_symbol_name("cos")
	.dwattr $C$DW$132, DW_AT_type(*$C$DW$T$17)
	.dwattr $C$DW$132, DW_AT_declaration
	.dwattr $C$DW$132, DW_AT_external
	.dwattr $C$DW$132, DW_AT_decl_file("C:/ti/bin/../include/math.h")
	.dwattr $C$DW$132, DW_AT_decl_line(0x52)
	.dwattr $C$DW$132, DW_AT_decl_column(0x11)
$C$DW$133	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$133, DW_AT_type(*$C$DW$T$17)
	.dwendtag $C$DW$132


$C$DW$134	.dwtag  DW_TAG_subprogram, DW_AT_name("acos")
	.dwattr $C$DW$134, DW_AT_TI_symbol_name("acos")
	.dwattr $C$DW$134, DW_AT_type(*$C$DW$T$17)
	.dwattr $C$DW$134, DW_AT_declaration
	.dwattr $C$DW$134, DW_AT_external
	.dwattr $C$DW$134, DW_AT_decl_file("C:/ti/bin/../include/math.h")
	.dwattr $C$DW$134, DW_AT_decl_line(0x55)
	.dwattr $C$DW$134, DW_AT_decl_column(0x11)
$C$DW$135	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$135, DW_AT_type(*$C$DW$T$17)
	.dwendtag $C$DW$134

$C$DW$136	.dwtag  DW_TAG_variable, DW_AT_name("_mwSinTbl")
	.dwattr $C$DW$136, DW_AT_TI_symbol_name("_mwSinTbl")
	.dwattr $C$DW$136, DW_AT_type(*$C$DW$T$390)
	.dwattr $C$DW$136, DW_AT_declaration
	.dwattr $C$DW$136, DW_AT_external
	.dwattr $C$DW$136, DW_AT_decl_file("C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc/mwio4.h")
	.dwattr $C$DW$136, DW_AT_decl_line(0x128)
	.dwattr $C$DW$136, DW_AT_decl_column(0x10)
	.sect	".rodata"
	.align	4
	.elfsym	PI,SYM_SIZE(4)
PI:
	.word	040490fdbh		; PI @ 0

$C$DW$137	.dwtag  DW_TAG_variable, DW_AT_name("PI")
	.dwattr $C$DW$137, DW_AT_TI_symbol_name("PI")
	.dwattr $C$DW$137, DW_AT_type(*$C$DW$T$143)
	.dwattr $C$DW$137, DW_AT_location[DW_OP_addr PI]
	.dwattr $C$DW$137, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$137, DW_AT_decl_line(0x39)
	.dwattr $C$DW$137, DW_AT_decl_column(0x14)
	.sect	".rodata"
	.align	4
	.elfsym	Fs,SYM_SIZE(4)
Fs:
	.word	045fa0000h		; Fs @ 0

$C$DW$138	.dwtag  DW_TAG_variable, DW_AT_name("Fs")
	.dwattr $C$DW$138, DW_AT_TI_symbol_name("Fs")
	.dwattr $C$DW$138, DW_AT_type(*$C$DW$T$143)
	.dwattr $C$DW$138, DW_AT_location[DW_OP_addr Fs]
	.dwattr $C$DW$138, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$138, DW_AT_decl_line(0x3a)
	.dwattr $C$DW$138, DW_AT_decl_column(0x14)
	.sect	".rodata"
	.align	4
	.elfsym	Ts,SYM_SIZE(4)
Ts:
	.word	03903126fh		; Ts @ 0

$C$DW$139	.dwtag  DW_TAG_variable, DW_AT_name("Ts")
	.dwattr $C$DW$139, DW_AT_TI_symbol_name("Ts")
	.dwattr $C$DW$139, DW_AT_type(*$C$DW$T$143)
	.dwattr $C$DW$139, DW_AT_location[DW_OP_addr Ts]
	.dwattr $C$DW$139, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$139, DW_AT_decl_line(0x3b)
	.dwattr $C$DW$139, DW_AT_decl_column(0x14)
	.sect	".rodata"
	.align	4
	.elfsym	Tp,SYM_SIZE(4)
Tp:
	.word	03983126fh		; Tp @ 0

$C$DW$140	.dwtag  DW_TAG_variable, DW_AT_name("Tp")
	.dwattr $C$DW$140, DW_AT_TI_symbol_name("Tp")
	.dwattr $C$DW$140, DW_AT_type(*$C$DW$T$143)
	.dwattr $C$DW$140, DW_AT_location[DW_OP_addr Tp]
	.dwattr $C$DW$140, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$140, DW_AT_decl_line(0x3c)
	.dwattr $C$DW$140, DW_AT_decl_column(0x14)
	.sect	".const:cmd_1_soft"
	.clink
	.align	8
	.elfsym	cmd_1_soft,SYM_SIZE(8)
cmd_1_soft:
	.word	0bf8c0831h		; cmd_1_soft[0] @ 0
	.word	0bf8c0831h		; cmd_1_soft[1] @ 32

$C$DW$141	.dwtag  DW_TAG_variable, DW_AT_name("cmd_1_soft")
	.dwattr $C$DW$141, DW_AT_TI_symbol_name("cmd_1_soft")
	.dwattr $C$DW$141, DW_AT_type(*$C$DW$T$391)
	.dwattr $C$DW$141, DW_AT_location[DW_OP_addr cmd_1_soft]
	.dwattr $C$DW$141, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$141, DW_AT_decl_line(0x3d)
	.dwattr $C$DW$141, DW_AT_decl_column(0x14)
	.sect	".const:cmd_2_soft"
	.clink
	.align	8
	.elfsym	cmd_2_soft,SYM_SIZE(8)
cmd_2_soft:
	.word	042af70a4h		; cmd_2_soft[0] @ 0
	.word	042af70a4h		; cmd_2_soft[1] @ 32

$C$DW$142	.dwtag  DW_TAG_variable, DW_AT_name("cmd_2_soft")
	.dwattr $C$DW$142, DW_AT_TI_symbol_name("cmd_2_soft")
	.dwattr $C$DW$142, DW_AT_type(*$C$DW$T$391)
	.dwattr $C$DW$142, DW_AT_location[DW_OP_addr cmd_2_soft]
	.dwattr $C$DW$142, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$142, DW_AT_decl_line(0x3e)
	.dwattr $C$DW$142, DW_AT_decl_column(0x14)
	.sect	".const:cmd_3_soft"
	.clink
	.align	8
	.elfsym	cmd_3_soft,SYM_SIZE(8)
cmd_3_soft:
	.word	0bec6a7f0h		; cmd_3_soft[0] @ 0
	.word	0bec6a7f0h		; cmd_3_soft[1] @ 32

$C$DW$143	.dwtag  DW_TAG_variable, DW_AT_name("cmd_3_soft")
	.dwattr $C$DW$143, DW_AT_TI_symbol_name("cmd_3_soft")
	.dwattr $C$DW$143, DW_AT_type(*$C$DW$T$391)
	.dwattr $C$DW$143, DW_AT_location[DW_OP_addr cmd_3_soft]
	.dwattr $C$DW$143, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$143, DW_AT_decl_line(0x3f)
	.dwattr $C$DW$143, DW_AT_decl_column(0x14)
	.sect	".rodata"
	.align	4
	.elfsym	scale_fast,SYM_SIZE(4)
scale_fast:
	.word	040f00000h		; scale_fast @ 0

$C$DW$144	.dwtag  DW_TAG_variable, DW_AT_name("scale_fast")
	.dwattr $C$DW$144, DW_AT_TI_symbol_name("scale_fast")
	.dwattr $C$DW$144, DW_AT_type(*$C$DW$T$143)
	.dwattr $C$DW$144, DW_AT_location[DW_OP_addr scale_fast]
	.dwattr $C$DW$144, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$144, DW_AT_decl_line(0x44)
	.dwattr $C$DW$144, DW_AT_decl_column(0x14)
	.sect	".rodata"
	.align	4
	.elfsym	scale_slow,SYM_SIZE(4)
scale_slow:
	.word	040f00000h		; scale_slow @ 0

$C$DW$145	.dwtag  DW_TAG_variable, DW_AT_name("scale_slow")
	.dwattr $C$DW$145, DW_AT_TI_symbol_name("scale_slow")
	.dwattr $C$DW$145, DW_AT_type(*$C$DW$T$143)
	.dwattr $C$DW$145, DW_AT_location[DW_OP_addr scale_slow]
	.dwattr $C$DW$145, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$145, DW_AT_decl_line(0x45)
	.dwattr $C$DW$145, DW_AT_decl_column(0x14)
	.sect	".fardata:start_hand", RW
	.clink
	.align	8
	.elfsym	start_hand,SYM_SIZE(12)
start_hand:
	.word	03fa32618h		; start_hand[0] @ 0
	.word	0bc23d70ah		; start_hand[1] @ 32
	.word	03e7c84b6h		; start_hand[2] @ 64

$C$DW$146	.dwtag  DW_TAG_variable, DW_AT_name("start_hand")
	.dwattr $C$DW$146, DW_AT_TI_symbol_name("start_hand")
	.dwattr $C$DW$146, DW_AT_type(*$C$DW$T$421)
	.dwattr $C$DW$146, DW_AT_location[DW_OP_addr start_hand]
	.dwattr $C$DW$146, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$146, DW_AT_decl_line(0x46)
	.dwattr $C$DW$146, DW_AT_decl_column(0x0e)
	.sect	".rodata"
	.align	4
	.elfsym	Td,SYM_SIZE(4)
Td:
	.word	0368637bdh		; Td @ 0

$C$DW$147	.dwtag  DW_TAG_variable, DW_AT_name("Td")
	.dwattr $C$DW$147, DW_AT_TI_symbol_name("Td")
	.dwattr $C$DW$147, DW_AT_type(*$C$DW$T$143)
	.dwattr $C$DW$147, DW_AT_location[DW_OP_addr Td]
	.dwattr $C$DW$147, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$147, DW_AT_decl_line(0x52)
	.dwattr $C$DW$147, DW_AT_decl_column(0x14)
	.global	range
	.sect	".fardata:range", RW
	.clink
	.align	8
	.elfsym	range,SYM_SIZE(32)
range:
	.word	040a00000h		; range[0] @ 0
	.word	040a00000h		; range[1] @ 32
	.word	040a00000h		; range[2] @ 64
	.word	040a00000h		; range[3] @ 96
	.word	040a00000h		; range[4] @ 128
	.word	040a00000h		; range[5] @ 160
	.word	040a00000h		; range[6] @ 192
	.word	040a00000h		; range[7] @ 224

$C$DW$148	.dwtag  DW_TAG_variable, DW_AT_name("range")
	.dwattr $C$DW$148, DW_AT_TI_symbol_name("range")
	.dwattr $C$DW$148, DW_AT_location[DW_OP_addr range]
	.dwattr $C$DW$148, DW_AT_type(*$C$DW$T$422)
	.dwattr $C$DW$148, DW_AT_external
	.dwattr $C$DW$148, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$148, DW_AT_decl_line(0x53)
	.dwattr $C$DW$148, DW_AT_decl_column(0x07)
	.global	WAVE_INIT_COUNT
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_INIT_COUNT,SYM_SIZE(4)
WAVE_INIT_COUNT:
	.bits	0,32			; WAVE_INIT_COUNT @ 0

$C$DW$149	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_INIT_COUNT")
	.dwattr $C$DW$149, DW_AT_TI_symbol_name("WAVE_INIT_COUNT")
	.dwattr $C$DW$149, DW_AT_location[DW_OP_addr WAVE_INIT_COUNT]
	.dwattr $C$DW$149, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$149, DW_AT_external
	.dwattr $C$DW$149, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$149, DW_AT_decl_line(0x5c)
	.dwattr $C$DW$149, DW_AT_decl_column(0x0e)
	.global	WAVE_FIL_Y
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_FIL_Y,SYM_SIZE(4)
WAVE_FIL_Y:
	.word	000000000h		; WAVE_FIL_Y @ 0

$C$DW$150	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_FIL_Y")
	.dwattr $C$DW$150, DW_AT_TI_symbol_name("WAVE_FIL_Y")
	.dwattr $C$DW$150, DW_AT_location[DW_OP_addr WAVE_FIL_Y]
	.dwattr $C$DW$150, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$150, DW_AT_external
	.dwattr $C$DW$150, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$150, DW_AT_decl_line(0x5d)
	.dwattr $C$DW$150, DW_AT_decl_column(0x10)
	.global	flag_cont_start
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_cont_start,SYM_SIZE(4)
flag_cont_start:
	.bits	0,32			; flag_cont_start @ 0

$C$DW$151	.dwtag  DW_TAG_variable, DW_AT_name("flag_cont_start")
	.dwattr $C$DW$151, DW_AT_TI_symbol_name("flag_cont_start")
	.dwattr $C$DW$151, DW_AT_location[DW_OP_addr flag_cont_start]
	.dwattr $C$DW$151, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$151, DW_AT_external
	.dwattr $C$DW$151, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$151, DW_AT_decl_line(0x5f)
	.dwattr $C$DW$151, DW_AT_decl_column(0x0e)
	.global	flag_dead
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_dead,SYM_SIZE(4)
flag_dead:
	.word	03f800000h		; flag_dead @ 0

$C$DW$152	.dwtag  DW_TAG_variable, DW_AT_name("flag_dead")
	.dwattr $C$DW$152, DW_AT_TI_symbol_name("flag_dead")
	.dwattr $C$DW$152, DW_AT_location[DW_OP_addr flag_dead]
	.dwattr $C$DW$152, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$152, DW_AT_external
	.dwattr $C$DW$152, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$152, DW_AT_decl_line(0x60)
	.dwattr $C$DW$152, DW_AT_decl_column(0x10)
	.global	flag_dyn_payload
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_dyn_payload,SYM_SIZE(4)
flag_dyn_payload:
	.bits	1,32			; flag_dyn_payload @ 0

$C$DW$153	.dwtag  DW_TAG_variable, DW_AT_name("flag_dyn_payload")
	.dwattr $C$DW$153, DW_AT_TI_symbol_name("flag_dyn_payload")
	.dwattr $C$DW$153, DW_AT_location[DW_OP_addr flag_dyn_payload]
	.dwattr $C$DW$153, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$153, DW_AT_external
	.dwattr $C$DW$153, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$153, DW_AT_decl_line(0x61)
	.dwattr $C$DW$153, DW_AT_decl_column(0x0e)
	.global	flag_CalcHandCmd
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_CalcHandCmd,SYM_SIZE(4)
flag_CalcHandCmd:
	.bits	0,32			; flag_CalcHandCmd @ 0

$C$DW$154	.dwtag  DW_TAG_variable, DW_AT_name("flag_CalcHandCmd")
	.dwattr $C$DW$154, DW_AT_TI_symbol_name("flag_CalcHandCmd")
	.dwattr $C$DW$154, DW_AT_location[DW_OP_addr flag_CalcHandCmd]
	.dwattr $C$DW$154, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$154, DW_AT_external
	.dwattr $C$DW$154, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$154, DW_AT_decl_line(0x62)
	.dwattr $C$DW$154, DW_AT_decl_column(0x0e)
	.global	flag_debug
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_debug,SYM_SIZE(4)
flag_debug:
	.bits	0,32			; flag_debug @ 0

$C$DW$155	.dwtag  DW_TAG_variable, DW_AT_name("flag_debug")
	.dwattr $C$DW$155, DW_AT_TI_symbol_name("flag_debug")
	.dwattr $C$DW$155, DW_AT_location[DW_OP_addr flag_debug]
	.dwattr $C$DW$155, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$155, DW_AT_external
	.dwattr $C$DW$155, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$155, DW_AT_decl_line(0x63)
	.dwattr $C$DW$155, DW_AT_decl_column(0x0e)
	.global	flag_pv
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_pv,SYM_SIZE(4)
flag_pv:
	.bits	0,32			; flag_pv @ 0

$C$DW$156	.dwtag  DW_TAG_variable, DW_AT_name("flag_pv")
	.dwattr $C$DW$156, DW_AT_TI_symbol_name("flag_pv")
	.dwattr $C$DW$156, DW_AT_location[DW_OP_addr flag_pv]
	.dwattr $C$DW$156, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$156, DW_AT_external
	.dwattr $C$DW$156, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$156, DW_AT_decl_line(0x64)
	.dwattr $C$DW$156, DW_AT_decl_column(0x0e)
	.global	flag_delay
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_delay,SYM_SIZE(4)
flag_delay:
	.bits	0,32			; flag_delay @ 0

$C$DW$157	.dwtag  DW_TAG_variable, DW_AT_name("flag_delay")
	.dwattr $C$DW$157, DW_AT_TI_symbol_name("flag_delay")
	.dwattr $C$DW$157, DW_AT_location[DW_OP_addr flag_delay]
	.dwattr $C$DW$157, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$157, DW_AT_external
	.dwattr $C$DW$157, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$157, DW_AT_decl_line(0x65)
	.dwattr $C$DW$157, DW_AT_decl_column(0x0e)
	.global	flag_Vdc_setted
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_Vdc_setted,SYM_SIZE(4)
flag_Vdc_setted:
	.bits	0,32			; flag_Vdc_setted @ 0

$C$DW$158	.dwtag  DW_TAG_variable, DW_AT_name("flag_Vdc_setted")
	.dwattr $C$DW$158, DW_AT_TI_symbol_name("flag_Vdc_setted")
	.dwattr $C$DW$158, DW_AT_location[DW_OP_addr flag_Vdc_setted]
	.dwattr $C$DW$158, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$158, DW_AT_external
	.dwattr $C$DW$158, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$158, DW_AT_decl_line(0x66)
	.dwattr $C$DW$158, DW_AT_decl_column(0x0e)
	.global	flag_FBgain
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_FBgain,SYM_SIZE(4)
flag_FBgain:
	.bits	1,32			; flag_FBgain @ 0

$C$DW$159	.dwtag  DW_TAG_variable, DW_AT_name("flag_FBgain")
	.dwattr $C$DW$159, DW_AT_TI_symbol_name("flag_FBgain")
	.dwattr $C$DW$159, DW_AT_location[DW_OP_addr flag_FBgain]
	.dwattr $C$DW$159, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$159, DW_AT_external
	.dwattr $C$DW$159, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$159, DW_AT_decl_line(0x67)
	.dwattr $C$DW$159, DW_AT_decl_column(0x0e)
	.global	flag_PPgain
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_PPgain,SYM_SIZE(4)
flag_PPgain:
	.bits	2,32			; flag_PPgain @ 0

$C$DW$160	.dwtag  DW_TAG_variable, DW_AT_name("flag_PPgain")
	.dwattr $C$DW$160, DW_AT_TI_symbol_name("flag_PPgain")
	.dwattr $C$DW$160, DW_AT_location[DW_OP_addr flag_PPgain]
	.dwattr $C$DW$160, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$160, DW_AT_external
	.dwattr $C$DW$160, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$160, DW_AT_decl_line(0x68)
	.dwattr $C$DW$160, DW_AT_decl_column(0x0e)
	.global	flag_FF
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_FF,SYM_SIZE(4)
flag_FF:
	.bits	0,32			; flag_FF @ 0

$C$DW$161	.dwtag  DW_TAG_variable, DW_AT_name("flag_FF")
	.dwattr $C$DW$161, DW_AT_TI_symbol_name("flag_FF")
	.dwattr $C$DW$161, DW_AT_location[DW_OP_addr flag_FF]
	.dwattr $C$DW$161, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$161, DW_AT_external
	.dwattr $C$DW$161, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$161, DW_AT_decl_line(0x69)
	.dwattr $C$DW$161, DW_AT_decl_column(0x0e)
	.global	flag_SOB
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_SOB,SYM_SIZE(4)
flag_SOB:
	.bits	0,32			; flag_SOB @ 0

$C$DW$162	.dwtag  DW_TAG_variable, DW_AT_name("flag_SOB")
	.dwattr $C$DW$162, DW_AT_TI_symbol_name("flag_SOB")
	.dwattr $C$DW$162, DW_AT_location[DW_OP_addr flag_SOB]
	.dwattr $C$DW$162, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$162, DW_AT_external
	.dwattr $C$DW$162, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$162, DW_AT_decl_line(0x6a)
	.dwattr $C$DW$162, DW_AT_decl_column(0x0e)
	.global	counter_2
	.sect	".neardata", RW
	.align	4
	.elfsym	counter_2,SYM_SIZE(4)
counter_2:
	.bits	0,32			; counter_2 @ 0

$C$DW$163	.dwtag  DW_TAG_variable, DW_AT_name("counter_2")
	.dwattr $C$DW$163, DW_AT_TI_symbol_name("counter_2")
	.dwattr $C$DW$163, DW_AT_location[DW_OP_addr counter_2]
	.dwattr $C$DW$163, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$163, DW_AT_external
	.dwattr $C$DW$163, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$163, DW_AT_decl_line(0x6b)
	.dwattr $C$DW$163, DW_AT_decl_column(0x0e)
	.global	WAVE_LoopCount
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_LoopCount,SYM_SIZE(4)
WAVE_LoopCount:
	.bits	1,32			; WAVE_LoopCount @ 0

$C$DW$164	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_LoopCount")
	.dwattr $C$DW$164, DW_AT_TI_symbol_name("WAVE_LoopCount")
	.dwattr $C$DW$164, DW_AT_location[DW_OP_addr WAVE_LoopCount]
	.dwattr $C$DW$164, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$164, DW_AT_external
	.dwattr $C$DW$164, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$164, DW_AT_decl_line(0x6c)
	.dwattr $C$DW$164, DW_AT_decl_column(0x0e)
	.global	flag_FF_triple
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_FF_triple,SYM_SIZE(4)
flag_FF_triple:
	.bits	0,32			; flag_FF_triple @ 0

$C$DW$165	.dwtag  DW_TAG_variable, DW_AT_name("flag_FF_triple")
	.dwattr $C$DW$165, DW_AT_TI_symbol_name("flag_FF_triple")
	.dwattr $C$DW$165, DW_AT_location[DW_OP_addr flag_FF_triple]
	.dwattr $C$DW$165, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$165, DW_AT_external
	.dwattr $C$DW$165, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$165, DW_AT_decl_line(0x6d)
	.dwattr $C$DW$165, DW_AT_decl_column(0x0e)
	.global	flag_cmd_end
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_cmd_end,SYM_SIZE(4)
flag_cmd_end:
	.bits	0,32			; flag_cmd_end @ 0

$C$DW$166	.dwtag  DW_TAG_variable, DW_AT_name("flag_cmd_end")
	.dwattr $C$DW$166, DW_AT_TI_symbol_name("flag_cmd_end")
	.dwattr $C$DW$166, DW_AT_location[DW_OP_addr flag_cmd_end]
	.dwattr $C$DW$166, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$166, DW_AT_external
	.dwattr $C$DW$166, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$166, DW_AT_decl_line(0x6e)
	.dwattr $C$DW$166, DW_AT_decl_column(0x0e)
	.global	WAVE_Timer0
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Timer0,SYM_SIZE(4)
WAVE_Timer0:
	.word	000000000h		; WAVE_Timer0 @ 0

$C$DW$167	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Timer0")
	.dwattr $C$DW$167, DW_AT_TI_symbol_name("WAVE_Timer0")
	.dwattr $C$DW$167, DW_AT_location[DW_OP_addr WAVE_Timer0]
	.dwattr $C$DW$167, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$167, DW_AT_external
	.dwattr $C$DW$167, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$167, DW_AT_decl_line(0x70)
	.dwattr $C$DW$167, DW_AT_decl_column(0x10)
	.global	WAVE_Timer1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Timer1,SYM_SIZE(4)
WAVE_Timer1:
	.word	000000000h		; WAVE_Timer1 @ 0

$C$DW$168	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Timer1")
	.dwattr $C$DW$168, DW_AT_TI_symbol_name("WAVE_Timer1")
	.dwattr $C$DW$168, DW_AT_location[DW_OP_addr WAVE_Timer1]
	.dwattr $C$DW$168, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$168, DW_AT_external
	.dwattr $C$DW$168, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$168, DW_AT_decl_line(0x71)
	.dwattr $C$DW$168, DW_AT_decl_column(0x10)
	.global	WAVE_Timer2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Timer2,SYM_SIZE(4)
WAVE_Timer2:
	.word	000000000h		; WAVE_Timer2 @ 0

$C$DW$169	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Timer2")
	.dwattr $C$DW$169, DW_AT_TI_symbol_name("WAVE_Timer2")
	.dwattr $C$DW$169, DW_AT_location[DW_OP_addr WAVE_Timer2]
	.dwattr $C$DW$169, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$169, DW_AT_external
	.dwattr $C$DW$169, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$169, DW_AT_decl_line(0x72)
	.dwattr $C$DW$169, DW_AT_decl_column(0x10)
	.global	WAVE_TimeGetEnc
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeGetEnc,SYM_SIZE(4)
WAVE_TimeGetEnc:
	.word	000000000h		; WAVE_TimeGetEnc @ 0

$C$DW$170	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeGetEnc")
	.dwattr $C$DW$170, DW_AT_TI_symbol_name("WAVE_TimeGetEnc")
	.dwattr $C$DW$170, DW_AT_location[DW_OP_addr WAVE_TimeGetEnc]
	.dwattr $C$DW$170, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$170, DW_AT_external
	.dwattr $C$DW$170, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$170, DW_AT_decl_line(0x74)
	.dwattr $C$DW$170, DW_AT_decl_column(0x10)
	.global	WAVE_TimeSetWm
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeSetWm,SYM_SIZE(4)
WAVE_TimeSetWm:
	.word	000000000h		; WAVE_TimeSetWm @ 0

$C$DW$171	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeSetWm")
	.dwattr $C$DW$171, DW_AT_TI_symbol_name("WAVE_TimeSetWm")
	.dwattr $C$DW$171, DW_AT_location[DW_OP_addr WAVE_TimeSetWm]
	.dwattr $C$DW$171, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$171, DW_AT_external
	.dwattr $C$DW$171, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$171, DW_AT_decl_line(0x75)
	.dwattr $C$DW$171, DW_AT_decl_column(0x10)
	.global	WAVE_TimeConv2dq
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeConv2dq,SYM_SIZE(4)
WAVE_TimeConv2dq:
	.word	000000000h		; WAVE_TimeConv2dq @ 0

$C$DW$172	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeConv2dq")
	.dwattr $C$DW$172, DW_AT_TI_symbol_name("WAVE_TimeConv2dq")
	.dwattr $C$DW$172, DW_AT_location[DW_OP_addr WAVE_TimeConv2dq]
	.dwattr $C$DW$172, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$172, DW_AT_external
	.dwattr $C$DW$172, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$172, DW_AT_decl_line(0x76)
	.dwattr $C$DW$172, DW_AT_decl_column(0x10)
	.global	WAVE_TimeResRatch
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeResRatch,SYM_SIZE(4)
WAVE_TimeResRatch:
	.word	000000000h		; WAVE_TimeResRatch @ 0

$C$DW$173	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeResRatch")
	.dwattr $C$DW$173, DW_AT_TI_symbol_name("WAVE_TimeResRatch")
	.dwattr $C$DW$173, DW_AT_location[DW_OP_addr WAVE_TimeResRatch]
	.dwattr $C$DW$173, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$173, DW_AT_external
	.dwattr $C$DW$173, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$173, DW_AT_decl_line(0x77)
	.dwattr $C$DW$173, DW_AT_decl_column(0x10)
	.global	WAVE_TimeJl
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeJl,SYM_SIZE(4)
WAVE_TimeJl:
	.word	000000000h		; WAVE_TimeJl @ 0

$C$DW$174	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeJl")
	.dwattr $C$DW$174, DW_AT_TI_symbol_name("WAVE_TimeJl")
	.dwattr $C$DW$174, DW_AT_location[DW_OP_addr WAVE_TimeJl]
	.dwattr $C$DW$174, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$174, DW_AT_external
	.dwattr $C$DW$174, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$174, DW_AT_decl_line(0x78)
	.dwattr $C$DW$174, DW_AT_decl_column(0x10)
	.global	WAVE_TimeGain
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeGain,SYM_SIZE(4)
WAVE_TimeGain:
	.word	000000000h		; WAVE_TimeGain @ 0

$C$DW$175	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeGain")
	.dwattr $C$DW$175, DW_AT_TI_symbol_name("WAVE_TimeGain")
	.dwattr $C$DW$175, DW_AT_location[DW_OP_addr WAVE_TimeGain]
	.dwattr $C$DW$175, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$175, DW_AT_external
	.dwattr $C$DW$175, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$175, DW_AT_decl_line(0x79)
	.dwattr $C$DW$175, DW_AT_decl_column(0x10)
	.global	WAVE_TimeWrInit
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeWrInit,SYM_SIZE(4)
WAVE_TimeWrInit:
	.word	000000000h		; WAVE_TimeWrInit @ 0

$C$DW$176	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeWrInit")
	.dwattr $C$DW$176, DW_AT_TI_symbol_name("WAVE_TimeWrInit")
	.dwattr $C$DW$176, DW_AT_location[DW_OP_addr WAVE_TimeWrInit]
	.dwattr $C$DW$176, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$176, DW_AT_external
	.dwattr $C$DW$176, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$176, DW_AT_decl_line(0x7a)
	.dwattr $C$DW$176, DW_AT_decl_column(0x10)
	.global	WAVE_TimeWr
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeWr,SYM_SIZE(4)
WAVE_TimeWr:
	.word	000000000h		; WAVE_TimeWr @ 0

$C$DW$177	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeWr")
	.dwattr $C$DW$177, DW_AT_TI_symbol_name("WAVE_TimeWr")
	.dwattr $C$DW$177, DW_AT_location[DW_OP_addr WAVE_TimeWr]
	.dwattr $C$DW$177, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$177, DW_AT_external
	.dwattr $C$DW$177, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$177, DW_AT_decl_line(0x7b)
	.dwattr $C$DW$177, DW_AT_decl_column(0x10)
	.global	WAVE_TimeTauLdyn
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeTauLdyn,SYM_SIZE(4)
WAVE_TimeTauLdyn:
	.word	000000000h		; WAVE_TimeTauLdyn @ 0

$C$DW$178	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeTauLdyn")
	.dwattr $C$DW$178, DW_AT_TI_symbol_name("WAVE_TimeTauLdyn")
	.dwattr $C$DW$178, DW_AT_location[DW_OP_addr WAVE_TimeTauLdyn]
	.dwattr $C$DW$178, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$178, DW_AT_external
	.dwattr $C$DW$178, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$178, DW_AT_decl_line(0x7c)
	.dwattr $C$DW$178, DW_AT_decl_column(0x10)
	.global	WAVE_TimeTm
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeTm,SYM_SIZE(4)
WAVE_TimeTm:
	.word	000000000h		; WAVE_TimeTm @ 0

$C$DW$179	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeTm")
	.dwattr $C$DW$179, DW_AT_TI_symbol_name("WAVE_TimeTm")
	.dwattr $C$DW$179, DW_AT_location[DW_OP_addr WAVE_TimeTm]
	.dwattr $C$DW$179, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$179, DW_AT_external
	.dwattr $C$DW$179, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$179, DW_AT_decl_line(0x7d)
	.dwattr $C$DW$179, DW_AT_decl_column(0x10)
	.global	WAVE_TimeGrav
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeGrav,SYM_SIZE(4)
WAVE_TimeGrav:
	.word	000000000h		; WAVE_TimeGrav @ 0

$C$DW$180	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeGrav")
	.dwattr $C$DW$180, DW_AT_TI_symbol_name("WAVE_TimeGrav")
	.dwattr $C$DW$180, DW_AT_location[DW_OP_addr WAVE_TimeGrav]
	.dwattr $C$DW$180, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$180, DW_AT_external
	.dwattr $C$DW$180, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$180, DW_AT_decl_line(0x7e)
	.dwattr $C$DW$180, DW_AT_decl_column(0x10)
	.global	WAVE_TimeSOB
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeSOB,SYM_SIZE(4)
WAVE_TimeSOB:
	.word	000000000h		; WAVE_TimeSOB @ 0

$C$DW$181	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeSOB")
	.dwattr $C$DW$181, DW_AT_TI_symbol_name("WAVE_TimeSOB")
	.dwattr $C$DW$181, DW_AT_location[DW_OP_addr WAVE_TimeSOB]
	.dwattr $C$DW$181, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$181, DW_AT_external
	.dwattr $C$DW$181, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$181, DW_AT_decl_line(0x7f)
	.dwattr $C$DW$181, DW_AT_decl_column(0x10)
	.global	WAVE_TimeP_PI
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeP_PI,SYM_SIZE(4)
WAVE_TimeP_PI:
	.word	000000000h		; WAVE_TimeP_PI @ 0

$C$DW$182	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeP_PI")
	.dwattr $C$DW$182, DW_AT_TI_symbol_name("WAVE_TimeP_PI")
	.dwattr $C$DW$182, DW_AT_location[DW_OP_addr WAVE_TimeP_PI]
	.dwattr $C$DW$182, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$182, DW_AT_external
	.dwattr $C$DW$182, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$182, DW_AT_decl_line(0x80)
	.dwattr $C$DW$182, DW_AT_decl_column(0x10)
	.global	WAVE_TimeACC
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeACC,SYM_SIZE(4)
WAVE_TimeACC:
	.word	000000000h		; WAVE_TimeACC @ 0

$C$DW$183	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeACC")
	.dwattr $C$DW$183, DW_AT_TI_symbol_name("WAVE_TimeACC")
	.dwattr $C$DW$183, DW_AT_location[DW_OP_addr WAVE_TimeACC]
	.dwattr $C$DW$183, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$183, DW_AT_external
	.dwattr $C$DW$183, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$183, DW_AT_decl_line(0x81)
	.dwattr $C$DW$183, DW_AT_decl_column(0x10)
	.global	WAVE_TimeConv2uvw
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeConv2uvw,SYM_SIZE(4)
WAVE_TimeConv2uvw:
	.word	000000000h		; WAVE_TimeConv2uvw @ 0

$C$DW$184	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeConv2uvw")
	.dwattr $C$DW$184, DW_AT_TI_symbol_name("WAVE_TimeConv2uvw")
	.dwattr $C$DW$184, DW_AT_location[DW_OP_addr WAVE_TimeConv2uvw]
	.dwattr $C$DW$184, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$184, DW_AT_external
	.dwattr $C$DW$184, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$184, DW_AT_decl_line(0x82)
	.dwattr $C$DW$184, DW_AT_decl_column(0x10)
	.global	WAVE_TimeInsert
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeInsert,SYM_SIZE(4)
WAVE_TimeInsert:
	.word	000000000h		; WAVE_TimeInsert @ 0

$C$DW$185	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeInsert")
	.dwattr $C$DW$185, DW_AT_TI_symbol_name("WAVE_TimeInsert")
	.dwattr $C$DW$185, DW_AT_location[DW_OP_addr WAVE_TimeInsert]
	.dwattr $C$DW$185, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$185, DW_AT_external
	.dwattr $C$DW$185, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$185, DW_AT_decl_line(0x83)
	.dwattr $C$DW$185, DW_AT_decl_column(0x10)
	.global	WAVE_TimeCalcCmd
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeCalcCmd,SYM_SIZE(4)
WAVE_TimeCalcCmd:
	.word	000000000h		; WAVE_TimeCalcCmd @ 0

$C$DW$186	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeCalcCmd")
	.dwattr $C$DW$186, DW_AT_TI_symbol_name("WAVE_TimeCalcCmd")
	.dwattr $C$DW$186, DW_AT_location[DW_OP_addr WAVE_TimeCalcCmd]
	.dwattr $C$DW$186, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$186, DW_AT_external
	.dwattr $C$DW$186, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$186, DW_AT_decl_line(0x84)
	.dwattr $C$DW$186, DW_AT_decl_column(0x10)
	.global	WAVE_TimeCalcInvCmd
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_TimeCalcInvCmd,SYM_SIZE(4)
WAVE_TimeCalcInvCmd:
	.word	000000000h		; WAVE_TimeCalcInvCmd @ 0

$C$DW$187	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TimeCalcInvCmd")
	.dwattr $C$DW$187, DW_AT_TI_symbol_name("WAVE_TimeCalcInvCmd")
	.dwattr $C$DW$187, DW_AT_location[DW_OP_addr WAVE_TimeCalcInvCmd]
	.dwattr $C$DW$187, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$187, DW_AT_external
	.dwattr $C$DW$187, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$187, DW_AT_decl_line(0x85)
	.dwattr $C$DW$187, DW_AT_decl_column(0x10)
	.global	WAVE_Joint1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Joint1,SYM_SIZE(4)
WAVE_Joint1:
	.word	000000000h		; WAVE_Joint1 @ 0

$C$DW$188	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Joint1")
	.dwattr $C$DW$188, DW_AT_TI_symbol_name("WAVE_Joint1")
	.dwattr $C$DW$188, DW_AT_location[DW_OP_addr WAVE_Joint1]
	.dwattr $C$DW$188, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$188, DW_AT_external
	.dwattr $C$DW$188, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$188, DW_AT_decl_line(0x87)
	.dwattr $C$DW$188, DW_AT_decl_column(0x10)
	.global	WAVE_Joint2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Joint2,SYM_SIZE(4)
WAVE_Joint2:
	.word	000000000h		; WAVE_Joint2 @ 0

$C$DW$189	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Joint2")
	.dwattr $C$DW$189, DW_AT_TI_symbol_name("WAVE_Joint2")
	.dwattr $C$DW$189, DW_AT_location[DW_OP_addr WAVE_Joint2]
	.dwattr $C$DW$189, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$189, DW_AT_external
	.dwattr $C$DW$189, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$189, DW_AT_decl_line(0x88)
	.dwattr $C$DW$189, DW_AT_decl_column(0x10)
	.global	WAVE_Joint3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Joint3,SYM_SIZE(4)
WAVE_Joint3:
	.word	000000000h		; WAVE_Joint3 @ 0

$C$DW$190	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Joint3")
	.dwattr $C$DW$190, DW_AT_TI_symbol_name("WAVE_Joint3")
	.dwattr $C$DW$190, DW_AT_location[DW_OP_addr WAVE_Joint3]
	.dwattr $C$DW$190, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$190, DW_AT_external
	.dwattr $C$DW$190, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$190, DW_AT_decl_line(0x89)
	.dwattr $C$DW$190, DW_AT_decl_column(0x10)
	.global	WAVE_HandX
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_HandX,SYM_SIZE(4)
WAVE_HandX:
	.word	000000000h		; WAVE_HandX @ 0

$C$DW$191	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_HandX")
	.dwattr $C$DW$191, DW_AT_TI_symbol_name("WAVE_HandX")
	.dwattr $C$DW$191, DW_AT_location[DW_OP_addr WAVE_HandX]
	.dwattr $C$DW$191, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$191, DW_AT_external
	.dwattr $C$DW$191, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$191, DW_AT_decl_line(0x8a)
	.dwattr $C$DW$191, DW_AT_decl_column(0x10)
	.global	WAVE_HandY
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_HandY,SYM_SIZE(4)
WAVE_HandY:
	.word	000000000h		; WAVE_HandY @ 0

$C$DW$192	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_HandY")
	.dwattr $C$DW$192, DW_AT_TI_symbol_name("WAVE_HandY")
	.dwattr $C$DW$192, DW_AT_location[DW_OP_addr WAVE_HandY]
	.dwattr $C$DW$192, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$192, DW_AT_external
	.dwattr $C$DW$192, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$192, DW_AT_decl_line(0x8b)
	.dwattr $C$DW$192, DW_AT_decl_column(0x10)
	.global	WAVE_HandZ
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_HandZ,SYM_SIZE(4)
WAVE_HandZ:
	.word	000000000h		; WAVE_HandZ @ 0

$C$DW$193	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_HandZ")
	.dwattr $C$DW$193, DW_AT_TI_symbol_name("WAVE_HandZ")
	.dwattr $C$DW$193, DW_AT_location[DW_OP_addr WAVE_HandZ]
	.dwattr $C$DW$193, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$193, DW_AT_external
	.dwattr $C$DW$193, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$193, DW_AT_decl_line(0x8c)
	.dwattr $C$DW$193, DW_AT_decl_column(0x10)
	.global	WAVE_fx
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fx,SYM_SIZE(4)
WAVE_fx:
	.word	000000000h		; WAVE_fx @ 0

$C$DW$194	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fx")
	.dwattr $C$DW$194, DW_AT_TI_symbol_name("WAVE_fx")
	.dwattr $C$DW$194, DW_AT_location[DW_OP_addr WAVE_fx]
	.dwattr $C$DW$194, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$194, DW_AT_external
	.dwattr $C$DW$194, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$194, DW_AT_decl_line(0x8d)
	.dwattr $C$DW$194, DW_AT_decl_column(0x10)
	.global	WAVE_fy
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fy,SYM_SIZE(4)
WAVE_fy:
	.word	000000000h		; WAVE_fy @ 0

$C$DW$195	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fy")
	.dwattr $C$DW$195, DW_AT_TI_symbol_name("WAVE_fy")
	.dwattr $C$DW$195, DW_AT_location[DW_OP_addr WAVE_fy]
	.dwattr $C$DW$195, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$195, DW_AT_external
	.dwattr $C$DW$195, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$195, DW_AT_decl_line(0x8e)
	.dwattr $C$DW$195, DW_AT_decl_column(0x10)
	.global	WAVE_fz
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fz,SYM_SIZE(4)
WAVE_fz:
	.word	000000000h		; WAVE_fz @ 0

$C$DW$196	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fz")
	.dwattr $C$DW$196, DW_AT_TI_symbol_name("WAVE_fz")
	.dwattr $C$DW$196, DW_AT_location[DW_OP_addr WAVE_fz]
	.dwattr $C$DW$196, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$196, DW_AT_external
	.dwattr $C$DW$196, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$196, DW_AT_decl_line(0x8f)
	.dwattr $C$DW$196, DW_AT_decl_column(0x10)
	.global	flag_reposition
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_reposition,SYM_SIZE(4)
flag_reposition:
	.bits	0,32			; flag_reposition @ 0

$C$DW$197	.dwtag  DW_TAG_variable, DW_AT_name("flag_reposition")
	.dwattr $C$DW$197, DW_AT_TI_symbol_name("flag_reposition")
	.dwattr $C$DW$197, DW_AT_location[DW_OP_addr flag_reposition]
	.dwattr $C$DW$197, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$197, DW_AT_external
	.dwattr $C$DW$197, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$197, DW_AT_decl_line(0x91)
	.dwattr $C$DW$197, DW_AT_decl_column(0x0e)
	.global	flag_first_go
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_first_go,SYM_SIZE(4)
flag_first_go:
	.bits	0,32			; flag_first_go @ 0

$C$DW$198	.dwtag  DW_TAG_variable, DW_AT_name("flag_first_go")
	.dwattr $C$DW$198, DW_AT_TI_symbol_name("flag_first_go")
	.dwattr $C$DW$198, DW_AT_location[DW_OP_addr flag_first_go]
	.dwattr $C$DW$198, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$198, DW_AT_external
	.dwattr $C$DW$198, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$198, DW_AT_decl_line(0x92)
	.dwattr $C$DW$198, DW_AT_decl_column(0x0e)
	.global	flag_first_back
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_first_back,SYM_SIZE(4)
flag_first_back:
	.bits	1,32			; flag_first_back @ 0

$C$DW$199	.dwtag  DW_TAG_variable, DW_AT_name("flag_first_back")
	.dwattr $C$DW$199, DW_AT_TI_symbol_name("flag_first_back")
	.dwattr $C$DW$199, DW_AT_location[DW_OP_addr flag_first_back]
	.dwattr $C$DW$199, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$199, DW_AT_external
	.dwattr $C$DW$199, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$199, DW_AT_decl_line(0x93)
	.dwattr $C$DW$199, DW_AT_decl_column(0x0e)
	.global	flag_hard
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_hard,SYM_SIZE(4)
flag_hard:
	.bits	0,32			; flag_hard @ 0

$C$DW$200	.dwtag  DW_TAG_variable, DW_AT_name("flag_hard")
	.dwattr $C$DW$200, DW_AT_TI_symbol_name("flag_hard")
	.dwattr $C$DW$200, DW_AT_location[DW_OP_addr flag_hard]
	.dwattr $C$DW$200, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$200, DW_AT_external
	.dwattr $C$DW$200, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$200, DW_AT_decl_line(0x94)
	.dwattr $C$DW$200, DW_AT_decl_column(0x0e)
	.global	flag_CircleStart1
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_CircleStart1,SYM_SIZE(4)
flag_CircleStart1:
	.bits	0,32			; flag_CircleStart1 @ 0

$C$DW$201	.dwtag  DW_TAG_variable, DW_AT_name("flag_CircleStart1")
	.dwattr $C$DW$201, DW_AT_TI_symbol_name("flag_CircleStart1")
	.dwattr $C$DW$201, DW_AT_location[DW_OP_addr flag_CircleStart1]
	.dwattr $C$DW$201, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$201, DW_AT_external
	.dwattr $C$DW$201, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$201, DW_AT_decl_line(0x95)
	.dwattr $C$DW$201, DW_AT_decl_column(0x0e)
	.global	flag_CircleStart2
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_CircleStart2,SYM_SIZE(4)
flag_CircleStart2:
	.bits	0,32			; flag_CircleStart2 @ 0

$C$DW$202	.dwtag  DW_TAG_variable, DW_AT_name("flag_CircleStart2")
	.dwattr $C$DW$202, DW_AT_TI_symbol_name("flag_CircleStart2")
	.dwattr $C$DW$202, DW_AT_location[DW_OP_addr flag_CircleStart2]
	.dwattr $C$DW$202, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$202, DW_AT_external
	.dwattr $C$DW$202, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$202, DW_AT_decl_line(0x96)
	.dwattr $C$DW$202, DW_AT_decl_column(0x0e)
	.global	flag_CircleStart3
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_CircleStart3,SYM_SIZE(4)
flag_CircleStart3:
	.bits	0,32			; flag_CircleStart3 @ 0

$C$DW$203	.dwtag  DW_TAG_variable, DW_AT_name("flag_CircleStart3")
	.dwattr $C$DW$203, DW_AT_TI_symbol_name("flag_CircleStart3")
	.dwattr $C$DW$203, DW_AT_location[DW_OP_addr flag_CircleStart3]
	.dwattr $C$DW$203, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$203, DW_AT_external
	.dwattr $C$DW$203, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$203, DW_AT_decl_line(0x97)
	.dwattr $C$DW$203, DW_AT_decl_column(0x0e)
	.global	flag_end1
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_end1,SYM_SIZE(4)
flag_end1:
	.bits	0,32			; flag_end1 @ 0

$C$DW$204	.dwtag  DW_TAG_variable, DW_AT_name("flag_end1")
	.dwattr $C$DW$204, DW_AT_TI_symbol_name("flag_end1")
	.dwattr $C$DW$204, DW_AT_location[DW_OP_addr flag_end1]
	.dwattr $C$DW$204, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$204, DW_AT_external
	.dwattr $C$DW$204, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$204, DW_AT_decl_line(0x98)
	.dwattr $C$DW$204, DW_AT_decl_column(0x0e)
	.global	flag_end2
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_end2,SYM_SIZE(4)
flag_end2:
	.bits	0,32			; flag_end2 @ 0

$C$DW$205	.dwtag  DW_TAG_variable, DW_AT_name("flag_end2")
	.dwattr $C$DW$205, DW_AT_TI_symbol_name("flag_end2")
	.dwattr $C$DW$205, DW_AT_location[DW_OP_addr flag_end2]
	.dwattr $C$DW$205, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$205, DW_AT_external
	.dwattr $C$DW$205, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$205, DW_AT_decl_line(0x99)
	.dwattr $C$DW$205, DW_AT_decl_column(0x0e)
	.global	flag_end3
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_end3,SYM_SIZE(4)
flag_end3:
	.bits	0,32			; flag_end3 @ 0

$C$DW$206	.dwtag  DW_TAG_variable, DW_AT_name("flag_end3")
	.dwattr $C$DW$206, DW_AT_TI_symbol_name("flag_end3")
	.dwattr $C$DW$206, DW_AT_location[DW_OP_addr flag_end3]
	.dwattr $C$DW$206, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$206, DW_AT_external
	.dwattr $C$DW$206, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$206, DW_AT_decl_line(0x9a)
	.dwattr $C$DW$206, DW_AT_decl_column(0x0e)
	.global	flag_on
	.sect	".neardata", RW
	.align	4
	.elfsym	flag_on,SYM_SIZE(4)
flag_on:
	.bits	0,32			; flag_on @ 0

$C$DW$207	.dwtag  DW_TAG_variable, DW_AT_name("flag_on")
	.dwattr $C$DW$207, DW_AT_TI_symbol_name("flag_on")
	.dwattr $C$DW$207, DW_AT_location[DW_OP_addr flag_on]
	.dwattr $C$DW$207, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$207, DW_AT_external
	.dwattr $C$DW$207, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$207, DW_AT_decl_line(0x9b)
	.dwattr $C$DW$207, DW_AT_decl_column(0x0e)
	.global	start_go1
	.sect	".neardata", RW
	.align	4
	.elfsym	start_go1,SYM_SIZE(4)
start_go1:
	.word	000000000h		; start_go1 @ 0

$C$DW$208	.dwtag  DW_TAG_variable, DW_AT_name("start_go1")
	.dwattr $C$DW$208, DW_AT_TI_symbol_name("start_go1")
	.dwattr $C$DW$208, DW_AT_location[DW_OP_addr start_go1]
	.dwattr $C$DW$208, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$208, DW_AT_external
	.dwattr $C$DW$208, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$208, DW_AT_decl_line(0x9c)
	.dwattr $C$DW$208, DW_AT_decl_column(0x10)
	.global	start_go2
	.sect	".neardata", RW
	.align	4
	.elfsym	start_go2,SYM_SIZE(4)
start_go2:
	.word	000000000h		; start_go2 @ 0

$C$DW$209	.dwtag  DW_TAG_variable, DW_AT_name("start_go2")
	.dwattr $C$DW$209, DW_AT_TI_symbol_name("start_go2")
	.dwattr $C$DW$209, DW_AT_location[DW_OP_addr start_go2]
	.dwattr $C$DW$209, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$209, DW_AT_external
	.dwattr $C$DW$209, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$209, DW_AT_decl_line(0x9d)
	.dwattr $C$DW$209, DW_AT_decl_column(0x10)
	.global	start_go3
	.sect	".neardata", RW
	.align	4
	.elfsym	start_go3,SYM_SIZE(4)
start_go3:
	.word	000000000h		; start_go3 @ 0

$C$DW$210	.dwtag  DW_TAG_variable, DW_AT_name("start_go3")
	.dwattr $C$DW$210, DW_AT_TI_symbol_name("start_go3")
	.dwattr $C$DW$210, DW_AT_location[DW_OP_addr start_go3]
	.dwattr $C$DW$210, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$210, DW_AT_external
	.dwattr $C$DW$210, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$210, DW_AT_decl_line(0x9e)
	.dwattr $C$DW$210, DW_AT_decl_column(0x10)
	.global	start_back1
	.sect	".neardata", RW
	.align	4
	.elfsym	start_back1,SYM_SIZE(4)
start_back1:
	.word	000000000h		; start_back1 @ 0

$C$DW$211	.dwtag  DW_TAG_variable, DW_AT_name("start_back1")
	.dwattr $C$DW$211, DW_AT_TI_symbol_name("start_back1")
	.dwattr $C$DW$211, DW_AT_location[DW_OP_addr start_back1]
	.dwattr $C$DW$211, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$211, DW_AT_external
	.dwattr $C$DW$211, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$211, DW_AT_decl_line(0x9f)
	.dwattr $C$DW$211, DW_AT_decl_column(0x10)
	.global	start_back2
	.sect	".neardata", RW
	.align	4
	.elfsym	start_back2,SYM_SIZE(4)
start_back2:
	.word	000000000h		; start_back2 @ 0

$C$DW$212	.dwtag  DW_TAG_variable, DW_AT_name("start_back2")
	.dwattr $C$DW$212, DW_AT_TI_symbol_name("start_back2")
	.dwattr $C$DW$212, DW_AT_location[DW_OP_addr start_back2]
	.dwattr $C$DW$212, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$212, DW_AT_external
	.dwattr $C$DW$212, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$212, DW_AT_decl_line(0xa0)
	.dwattr $C$DW$212, DW_AT_decl_column(0x10)
	.global	start_back3
	.sect	".neardata", RW
	.align	4
	.elfsym	start_back3,SYM_SIZE(4)
start_back3:
	.word	000000000h		; start_back3 @ 0

$C$DW$213	.dwtag  DW_TAG_variable, DW_AT_name("start_back3")
	.dwattr $C$DW$213, DW_AT_TI_symbol_name("start_back3")
	.dwattr $C$DW$213, DW_AT_location[DW_OP_addr start_back3]
	.dwattr $C$DW$213, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$213, DW_AT_external
	.dwattr $C$DW$213, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$213, DW_AT_decl_line(0xa1)
	.dwattr $C$DW$213, DW_AT_decl_column(0x10)
	.global	Ref_Iq_ref_direct
	.sect	".neardata", RW
	.align	4
	.elfsym	Ref_Iq_ref_direct,SYM_SIZE(4)
Ref_Iq_ref_direct:
	.word	000000000h		; Ref_Iq_ref_direct @ 0

$C$DW$214	.dwtag  DW_TAG_variable, DW_AT_name("Ref_Iq_ref_direct")
	.dwattr $C$DW$214, DW_AT_TI_symbol_name("Ref_Iq_ref_direct")
	.dwattr $C$DW$214, DW_AT_location[DW_OP_addr Ref_Iq_ref_direct]
	.dwattr $C$DW$214, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$214, DW_AT_external
	.dwattr $C$DW$214, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$214, DW_AT_decl_line(0xa4)
	.dwattr $C$DW$214, DW_AT_decl_column(0x07)
	.global	Ref_wM_direct
	.sect	".neardata", RW
	.align	4
	.elfsym	Ref_wM_direct,SYM_SIZE(4)
Ref_wM_direct:
	.word	000000000h		; Ref_wM_direct @ 0

$C$DW$215	.dwtag  DW_TAG_variable, DW_AT_name("Ref_wM_direct")
	.dwattr $C$DW$215, DW_AT_TI_symbol_name("Ref_wM_direct")
	.dwattr $C$DW$215, DW_AT_location[DW_OP_addr Ref_wM_direct]
	.dwattr $C$DW$215, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$215, DW_AT_external
	.dwattr $C$DW$215, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$215, DW_AT_decl_line(0xa5)
	.dwattr $C$DW$215, DW_AT_decl_column(0x07)
	.global	Iq_off
	.sect	".neardata", RW
	.align	4
	.elfsym	Iq_off,SYM_SIZE(4)
Iq_off:
	.word	000000000h		; Iq_off @ 0

$C$DW$216	.dwtag  DW_TAG_variable, DW_AT_name("Iq_off")
	.dwattr $C$DW$216, DW_AT_TI_symbol_name("Iq_off")
	.dwattr $C$DW$216, DW_AT_location[DW_OP_addr Iq_off]
	.dwattr $C$DW$216, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$216, DW_AT_external
	.dwattr $C$DW$216, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$216, DW_AT_decl_line(0xa6)
	.dwattr $C$DW$216, DW_AT_decl_column(0x07)
	.global	Flag_ARCS_start
	.sect	".neardata", RW
	.align	4
	.elfsym	Flag_ARCS_start,SYM_SIZE(4)
Flag_ARCS_start:
	.bits	0,32			; Flag_ARCS_start @ 0

$C$DW$217	.dwtag  DW_TAG_variable, DW_AT_name("Flag_ARCS_start")
	.dwattr $C$DW$217, DW_AT_TI_symbol_name("Flag_ARCS_start")
	.dwattr $C$DW$217, DW_AT_location[DW_OP_addr Flag_ARCS_start]
	.dwattr $C$DW$217, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$217, DW_AT_external
	.dwattr $C$DW$217, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$217, DW_AT_decl_line(0xa7)
	.dwattr $C$DW$217, DW_AT_decl_column(0x05)
	.global	Flag_ARCS_clear
	.sect	".neardata", RW
	.align	4
	.elfsym	Flag_ARCS_clear,SYM_SIZE(4)
Flag_ARCS_clear:
	.bits	0,32			; Flag_ARCS_clear @ 0

$C$DW$218	.dwtag  DW_TAG_variable, DW_AT_name("Flag_ARCS_clear")
	.dwattr $C$DW$218, DW_AT_TI_symbol_name("Flag_ARCS_clear")
	.dwattr $C$DW$218, DW_AT_location[DW_OP_addr Flag_ARCS_clear]
	.dwattr $C$DW$218, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$218, DW_AT_external
	.dwattr $C$DW$218, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$218, DW_AT_decl_line(0xa8)
	.dwattr $C$DW$218, DW_AT_decl_column(0x05)
	.global	ref_wm_direct
	.sect	".neardata", RW
	.align	4
	.elfsym	ref_wm_direct,SYM_SIZE(4)
ref_wm_direct:
	.word	000000000h		; ref_wm_direct @ 0

$C$DW$219	.dwtag  DW_TAG_variable, DW_AT_name("ref_wm_direct")
	.dwattr $C$DW$219, DW_AT_TI_symbol_name("ref_wm_direct")
	.dwattr $C$DW$219, DW_AT_location[DW_OP_addr ref_wm_direct]
	.dwattr $C$DW$219, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$219, DW_AT_external
	.dwattr $C$DW$219, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$219, DW_AT_decl_line(0xab)
	.dwattr $C$DW$219, DW_AT_decl_column(0x10)
	.global	debug_theta
	.sect	".neardata", RW
	.align	4
	.elfsym	debug_theta,SYM_SIZE(4)
debug_theta:
	.bits	0,32			; debug_theta @ 0

$C$DW$220	.dwtag  DW_TAG_variable, DW_AT_name("debug_theta")
	.dwattr $C$DW$220, DW_AT_TI_symbol_name("debug_theta")
	.dwattr $C$DW$220, DW_AT_location[DW_OP_addr debug_theta]
	.dwattr $C$DW$220, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$220, DW_AT_external
	.dwattr $C$DW$220, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$220, DW_AT_decl_line(0xac)
	.dwattr $C$DW$220, DW_AT_decl_column(0x0e)
	.global	load_angle_limit_deg1
	.sect	".neardata", RW
	.align	4
	.elfsym	load_angle_limit_deg1,SYM_SIZE(4)
load_angle_limit_deg1:
	.word	000000000h		; load_angle_limit_deg1 @ 0

$C$DW$221	.dwtag  DW_TAG_variable, DW_AT_name("load_angle_limit_deg1")
	.dwattr $C$DW$221, DW_AT_TI_symbol_name("load_angle_limit_deg1")
	.dwattr $C$DW$221, DW_AT_location[DW_OP_addr load_angle_limit_deg1]
	.dwattr $C$DW$221, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$221, DW_AT_external
	.dwattr $C$DW$221, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$221, DW_AT_decl_line(0xad)
	.dwattr $C$DW$221, DW_AT_decl_column(0x10)
	.global	load_angle_limit_deg2
	.sect	".neardata", RW
	.align	4
	.elfsym	load_angle_limit_deg2,SYM_SIZE(4)
load_angle_limit_deg2:
	.word	000000000h		; load_angle_limit_deg2 @ 0

$C$DW$222	.dwtag  DW_TAG_variable, DW_AT_name("load_angle_limit_deg2")
	.dwattr $C$DW$222, DW_AT_TI_symbol_name("load_angle_limit_deg2")
	.dwattr $C$DW$222, DW_AT_location[DW_OP_addr load_angle_limit_deg2]
	.dwattr $C$DW$222, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$222, DW_AT_external
	.dwattr $C$DW$222, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$222, DW_AT_decl_line(0xae)
	.dwattr $C$DW$222, DW_AT_decl_column(0x10)
	.global	load_angle_limit_deg3
	.sect	".neardata", RW
	.align	4
	.elfsym	load_angle_limit_deg3,SYM_SIZE(4)
load_angle_limit_deg3:
	.word	000000000h		; load_angle_limit_deg3 @ 0

$C$DW$223	.dwtag  DW_TAG_variable, DW_AT_name("load_angle_limit_deg3")
	.dwattr $C$DW$223, DW_AT_TI_symbol_name("load_angle_limit_deg3")
	.dwattr $C$DW$223, DW_AT_location[DW_OP_addr load_angle_limit_deg3]
	.dwattr $C$DW$223, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$223, DW_AT_external
	.dwattr $C$DW$223, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$223, DW_AT_decl_line(0xaf)
	.dwattr $C$DW$223, DW_AT_decl_column(0x10)
	.global	load_angle_limit_deg5
	.sect	".neardata", RW
	.align	4
	.elfsym	load_angle_limit_deg5,SYM_SIZE(4)
load_angle_limit_deg5:
	.word	000000000h		; load_angle_limit_deg5 @ 0

$C$DW$224	.dwtag  DW_TAG_variable, DW_AT_name("load_angle_limit_deg5")
	.dwattr $C$DW$224, DW_AT_TI_symbol_name("load_angle_limit_deg5")
	.dwattr $C$DW$224, DW_AT_location[DW_OP_addr load_angle_limit_deg5]
	.dwattr $C$DW$224, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$224, DW_AT_external
	.dwattr $C$DW$224, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$224, DW_AT_decl_line(0xb0)
	.dwattr $C$DW$224, DW_AT_decl_column(0x10)
	.global	load_angle_limit_rad1
	.sect	".neardata", RW
	.align	4
	.elfsym	load_angle_limit_rad1,SYM_SIZE(4)
load_angle_limit_rad1:
	.word	000000000h		; load_angle_limit_rad1 @ 0

$C$DW$225	.dwtag  DW_TAG_variable, DW_AT_name("load_angle_limit_rad1")
	.dwattr $C$DW$225, DW_AT_TI_symbol_name("load_angle_limit_rad1")
	.dwattr $C$DW$225, DW_AT_location[DW_OP_addr load_angle_limit_rad1]
	.dwattr $C$DW$225, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$225, DW_AT_external
	.dwattr $C$DW$225, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$225, DW_AT_decl_line(0xb1)
	.dwattr $C$DW$225, DW_AT_decl_column(0x10)
	.global	load_angle_limit_rad2
	.sect	".neardata", RW
	.align	4
	.elfsym	load_angle_limit_rad2,SYM_SIZE(4)
load_angle_limit_rad2:
	.word	000000000h		; load_angle_limit_rad2 @ 0

$C$DW$226	.dwtag  DW_TAG_variable, DW_AT_name("load_angle_limit_rad2")
	.dwattr $C$DW$226, DW_AT_TI_symbol_name("load_angle_limit_rad2")
	.dwattr $C$DW$226, DW_AT_location[DW_OP_addr load_angle_limit_rad2]
	.dwattr $C$DW$226, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$226, DW_AT_external
	.dwattr $C$DW$226, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$226, DW_AT_decl_line(0xb2)
	.dwattr $C$DW$226, DW_AT_decl_column(0x10)
	.global	load_angle_limit_rad3
	.sect	".neardata", RW
	.align	4
	.elfsym	load_angle_limit_rad3,SYM_SIZE(4)
load_angle_limit_rad3:
	.word	000000000h		; load_angle_limit_rad3 @ 0

$C$DW$227	.dwtag  DW_TAG_variable, DW_AT_name("load_angle_limit_rad3")
	.dwattr $C$DW$227, DW_AT_TI_symbol_name("load_angle_limit_rad3")
	.dwattr $C$DW$227, DW_AT_location[DW_OP_addr load_angle_limit_rad3]
	.dwattr $C$DW$227, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$227, DW_AT_external
	.dwattr $C$DW$227, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$227, DW_AT_decl_line(0xb3)
	.dwattr $C$DW$227, DW_AT_decl_column(0x10)
	.global	load_angle_limit_rad5
	.sect	".neardata", RW
	.align	4
	.elfsym	load_angle_limit_rad5,SYM_SIZE(4)
load_angle_limit_rad5:
	.word	000000000h		; load_angle_limit_rad5 @ 0

$C$DW$228	.dwtag  DW_TAG_variable, DW_AT_name("load_angle_limit_rad5")
	.dwattr $C$DW$228, DW_AT_TI_symbol_name("load_angle_limit_rad5")
	.dwattr $C$DW$228, DW_AT_location[DW_OP_addr load_angle_limit_rad5]
	.dwattr $C$DW$228, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$228, DW_AT_external
	.dwattr $C$DW$228, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$228, DW_AT_decl_line(0xb4)
	.dwattr $C$DW$228, DW_AT_decl_column(0x10)
	.global	left_rotation_flag
	.sect	".neardata", RW
	.align	4
	.elfsym	left_rotation_flag,SYM_SIZE(4)
left_rotation_flag:
	.bits	1,32			; left_rotation_flag @ 0

$C$DW$229	.dwtag  DW_TAG_variable, DW_AT_name("left_rotation_flag")
	.dwattr $C$DW$229, DW_AT_TI_symbol_name("left_rotation_flag")
	.dwattr $C$DW$229, DW_AT_location[DW_OP_addr left_rotation_flag]
	.dwattr $C$DW$229, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$229, DW_AT_external
	.dwattr $C$DW$229, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$229, DW_AT_decl_line(0xb5)
	.dwattr $C$DW$229, DW_AT_decl_column(0x0e)
	.global	right_rotation_flag
	.sect	".neardata", RW
	.align	4
	.elfsym	right_rotation_flag,SYM_SIZE(4)
right_rotation_flag:
	.bits	0,32			; right_rotation_flag @ 0

$C$DW$230	.dwtag  DW_TAG_variable, DW_AT_name("right_rotation_flag")
	.dwattr $C$DW$230, DW_AT_TI_symbol_name("right_rotation_flag")
	.dwattr $C$DW$230, DW_AT_location[DW_OP_addr right_rotation_flag]
	.dwattr $C$DW$230, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$230, DW_AT_external
	.dwattr $C$DW$230, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$230, DW_AT_decl_line(0xb6)
	.dwattr $C$DW$230, DW_AT_decl_column(0x0e)
	.global	down_rotation_flag2
	.sect	".neardata", RW
	.align	4
	.elfsym	down_rotation_flag2,SYM_SIZE(4)
down_rotation_flag2:
	.bits	1,32			; down_rotation_flag2 @ 0

$C$DW$231	.dwtag  DW_TAG_variable, DW_AT_name("down_rotation_flag2")
	.dwattr $C$DW$231, DW_AT_TI_symbol_name("down_rotation_flag2")
	.dwattr $C$DW$231, DW_AT_location[DW_OP_addr down_rotation_flag2]
	.dwattr $C$DW$231, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$231, DW_AT_external
	.dwattr $C$DW$231, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$231, DW_AT_decl_line(0xb7)
	.dwattr $C$DW$231, DW_AT_decl_column(0x0e)
	.global	up_rotation_flag2
	.sect	".neardata", RW
	.align	4
	.elfsym	up_rotation_flag2,SYM_SIZE(4)
up_rotation_flag2:
	.bits	0,32			; up_rotation_flag2 @ 0

$C$DW$232	.dwtag  DW_TAG_variable, DW_AT_name("up_rotation_flag2")
	.dwattr $C$DW$232, DW_AT_TI_symbol_name("up_rotation_flag2")
	.dwattr $C$DW$232, DW_AT_location[DW_OP_addr up_rotation_flag2]
	.dwattr $C$DW$232, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$232, DW_AT_external
	.dwattr $C$DW$232, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$232, DW_AT_decl_line(0xb8)
	.dwattr $C$DW$232, DW_AT_decl_column(0x0e)
	.global	down_rotation_flag3
	.sect	".neardata", RW
	.align	4
	.elfsym	down_rotation_flag3,SYM_SIZE(4)
down_rotation_flag3:
	.bits	1,32			; down_rotation_flag3 @ 0

$C$DW$233	.dwtag  DW_TAG_variable, DW_AT_name("down_rotation_flag3")
	.dwattr $C$DW$233, DW_AT_TI_symbol_name("down_rotation_flag3")
	.dwattr $C$DW$233, DW_AT_location[DW_OP_addr down_rotation_flag3]
	.dwattr $C$DW$233, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$233, DW_AT_external
	.dwattr $C$DW$233, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$233, DW_AT_decl_line(0xb9)
	.dwattr $C$DW$233, DW_AT_decl_column(0x0e)
	.global	up_rotation_flag3
	.sect	".neardata", RW
	.align	4
	.elfsym	up_rotation_flag3,SYM_SIZE(4)
up_rotation_flag3:
	.bits	0,32			; up_rotation_flag3 @ 0

$C$DW$234	.dwtag  DW_TAG_variable, DW_AT_name("up_rotation_flag3")
	.dwattr $C$DW$234, DW_AT_TI_symbol_name("up_rotation_flag3")
	.dwattr $C$DW$234, DW_AT_location[DW_OP_addr up_rotation_flag3]
	.dwattr $C$DW$234, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$234, DW_AT_external
	.dwattr $C$DW$234, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$234, DW_AT_decl_line(0xba)
	.dwattr $C$DW$234, DW_AT_decl_column(0x0e)
	.global	down_rotation_flag5
	.sect	".neardata", RW
	.align	4
	.elfsym	down_rotation_flag5,SYM_SIZE(4)
down_rotation_flag5:
	.bits	1,32			; down_rotation_flag5 @ 0

$C$DW$235	.dwtag  DW_TAG_variable, DW_AT_name("down_rotation_flag5")
	.dwattr $C$DW$235, DW_AT_TI_symbol_name("down_rotation_flag5")
	.dwattr $C$DW$235, DW_AT_location[DW_OP_addr down_rotation_flag5]
	.dwattr $C$DW$235, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$235, DW_AT_external
	.dwattr $C$DW$235, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$235, DW_AT_decl_line(0xbb)
	.dwattr $C$DW$235, DW_AT_decl_column(0x0e)
	.global	up_rotation_flag5
	.sect	".neardata", RW
	.align	4
	.elfsym	up_rotation_flag5,SYM_SIZE(4)
up_rotation_flag5:
	.bits	0,32			; up_rotation_flag5 @ 0

$C$DW$236	.dwtag  DW_TAG_variable, DW_AT_name("up_rotation_flag5")
	.dwattr $C$DW$236, DW_AT_TI_symbol_name("up_rotation_flag5")
	.dwattr $C$DW$236, DW_AT_location[DW_OP_addr up_rotation_flag5]
	.dwattr $C$DW$236, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$236, DW_AT_external
	.dwattr $C$DW$236, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$236, DW_AT_decl_line(0xbc)
	.dwattr $C$DW$236, DW_AT_decl_column(0x0e)
	.global	WAVE_MRU1
	.bss	WAVE_MRU1,4,4
$C$DW$237	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRU1")
	.dwattr $C$DW$237, DW_AT_TI_symbol_name("WAVE_MRU1")
	.dwattr $C$DW$237, DW_AT_location[DW_OP_addr WAVE_MRU1]
	.dwattr $C$DW$237, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$237, DW_AT_external
	.dwattr $C$DW$237, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$237, DW_AT_decl_line(0xbf)
	.dwattr $C$DW$237, DW_AT_decl_column(0x10)
	.global	WAVE_MRV1
	.bss	WAVE_MRV1,4,4
$C$DW$238	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRV1")
	.dwattr $C$DW$238, DW_AT_TI_symbol_name("WAVE_MRV1")
	.dwattr $C$DW$238, DW_AT_location[DW_OP_addr WAVE_MRV1]
	.dwattr $C$DW$238, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$238, DW_AT_external
	.dwattr $C$DW$238, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$238, DW_AT_decl_line(0xc0)
	.dwattr $C$DW$238, DW_AT_decl_column(0x10)
	.global	WAVE_MRW1
	.bss	WAVE_MRW1,4,4
$C$DW$239	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRW1")
	.dwattr $C$DW$239, DW_AT_TI_symbol_name("WAVE_MRW1")
	.dwattr $C$DW$239, DW_AT_location[DW_OP_addr WAVE_MRW1]
	.dwattr $C$DW$239, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$239, DW_AT_external
	.dwattr $C$DW$239, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$239, DW_AT_decl_line(0xc1)
	.dwattr $C$DW$239, DW_AT_decl_column(0x10)
	.global	WAVE_MRU2
	.bss	WAVE_MRU2,4,4
$C$DW$240	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRU2")
	.dwattr $C$DW$240, DW_AT_TI_symbol_name("WAVE_MRU2")
	.dwattr $C$DW$240, DW_AT_location[DW_OP_addr WAVE_MRU2]
	.dwattr $C$DW$240, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$240, DW_AT_external
	.dwattr $C$DW$240, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$240, DW_AT_decl_line(0xc2)
	.dwattr $C$DW$240, DW_AT_decl_column(0x10)
	.global	WAVE_MRV2
	.bss	WAVE_MRV2,4,4
$C$DW$241	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRV2")
	.dwattr $C$DW$241, DW_AT_TI_symbol_name("WAVE_MRV2")
	.dwattr $C$DW$241, DW_AT_location[DW_OP_addr WAVE_MRV2]
	.dwattr $C$DW$241, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$241, DW_AT_external
	.dwattr $C$DW$241, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$241, DW_AT_decl_line(0xc3)
	.dwattr $C$DW$241, DW_AT_decl_column(0x10)
	.global	WAVE_MRW2
	.bss	WAVE_MRW2,4,4
$C$DW$242	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRW2")
	.dwattr $C$DW$242, DW_AT_TI_symbol_name("WAVE_MRW2")
	.dwattr $C$DW$242, DW_AT_location[DW_OP_addr WAVE_MRW2]
	.dwattr $C$DW$242, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$242, DW_AT_external
	.dwattr $C$DW$242, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$242, DW_AT_decl_line(0xc4)
	.dwattr $C$DW$242, DW_AT_decl_column(0x10)
	.global	WAVE_MRU3
	.bss	WAVE_MRU3,4,4
$C$DW$243	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRU3")
	.dwattr $C$DW$243, DW_AT_TI_symbol_name("WAVE_MRU3")
	.dwattr $C$DW$243, DW_AT_location[DW_OP_addr WAVE_MRU3]
	.dwattr $C$DW$243, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$243, DW_AT_external
	.dwattr $C$DW$243, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$243, DW_AT_decl_line(0xc5)
	.dwattr $C$DW$243, DW_AT_decl_column(0x10)
	.global	WAVE_MRV3
	.bss	WAVE_MRV3,4,4
$C$DW$244	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRV3")
	.dwattr $C$DW$244, DW_AT_TI_symbol_name("WAVE_MRV3")
	.dwattr $C$DW$244, DW_AT_location[DW_OP_addr WAVE_MRV3]
	.dwattr $C$DW$244, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$244, DW_AT_external
	.dwattr $C$DW$244, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$244, DW_AT_decl_line(0xc6)
	.dwattr $C$DW$244, DW_AT_decl_column(0x10)
	.global	WAVE_MRW3
	.bss	WAVE_MRW3,4,4
$C$DW$245	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRW3")
	.dwattr $C$DW$245, DW_AT_TI_symbol_name("WAVE_MRW3")
	.dwattr $C$DW$245, DW_AT_location[DW_OP_addr WAVE_MRW3]
	.dwattr $C$DW$245, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$245, DW_AT_external
	.dwattr $C$DW$245, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$245, DW_AT_decl_line(0xc7)
	.dwattr $C$DW$245, DW_AT_decl_column(0x10)
	.global	WAVE_MRBR1
	.bss	WAVE_MRBR1,4,4
$C$DW$246	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRBR1")
	.dwattr $C$DW$246, DW_AT_TI_symbol_name("WAVE_MRBR1")
	.dwattr $C$DW$246, DW_AT_location[DW_OP_addr WAVE_MRBR1]
	.dwattr $C$DW$246, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$246, DW_AT_external
	.dwattr $C$DW$246, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$246, DW_AT_decl_line(0xca)
	.dwattr $C$DW$246, DW_AT_decl_column(0x10)
	.global	WAVE_MRBR2
	.bss	WAVE_MRBR2,4,4
$C$DW$247	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRBR2")
	.dwattr $C$DW$247, DW_AT_TI_symbol_name("WAVE_MRBR2")
	.dwattr $C$DW$247, DW_AT_location[DW_OP_addr WAVE_MRBR2]
	.dwattr $C$DW$247, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$247, DW_AT_external
	.dwattr $C$DW$247, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$247, DW_AT_decl_line(0xcb)
	.dwattr $C$DW$247, DW_AT_decl_column(0x10)
	.global	WAVE_MRBR3
	.bss	WAVE_MRBR3,4,4
$C$DW$248	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_MRBR3")
	.dwattr $C$DW$248, DW_AT_TI_symbol_name("WAVE_MRBR3")
	.dwattr $C$DW$248, DW_AT_location[DW_OP_addr WAVE_MRBR3]
	.dwattr $C$DW$248, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$248, DW_AT_external
	.dwattr $C$DW$248, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$248, DW_AT_decl_line(0xcc)
	.dwattr $C$DW$248, DW_AT_decl_column(0x10)
	.global	WAVE_Kpp1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Kpp1,SYM_SIZE(4)
WAVE_Kpp1:
	.word	000000000h		; WAVE_Kpp1 @ 0

$C$DW$249	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Kpp1")
	.dwattr $C$DW$249, DW_AT_TI_symbol_name("WAVE_Kpp1")
	.dwattr $C$DW$249, DW_AT_location[DW_OP_addr WAVE_Kpp1]
	.dwattr $C$DW$249, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$249, DW_AT_external
	.dwattr $C$DW$249, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$249, DW_AT_decl_line(0xd0)
	.dwattr $C$DW$249, DW_AT_decl_column(0x10)
	.global	WAVE_Kvp1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Kvp1,SYM_SIZE(4)
WAVE_Kvp1:
	.word	000000000h		; WAVE_Kvp1 @ 0

$C$DW$250	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Kvp1")
	.dwattr $C$DW$250, DW_AT_TI_symbol_name("WAVE_Kvp1")
	.dwattr $C$DW$250, DW_AT_location[DW_OP_addr WAVE_Kvp1]
	.dwattr $C$DW$250, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$250, DW_AT_external
	.dwattr $C$DW$250, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$250, DW_AT_decl_line(0xd1)
	.dwattr $C$DW$250, DW_AT_decl_column(0x10)
	.global	WAVE_Kvi1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Kvi1,SYM_SIZE(4)
WAVE_Kvi1:
	.word	000000000h		; WAVE_Kvi1 @ 0

$C$DW$251	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Kvi1")
	.dwattr $C$DW$251, DW_AT_TI_symbol_name("WAVE_Kvi1")
	.dwattr $C$DW$251, DW_AT_location[DW_OP_addr WAVE_Kvi1]
	.dwattr $C$DW$251, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$251, DW_AT_external
	.dwattr $C$DW$251, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$251, DW_AT_decl_line(0xd2)
	.dwattr $C$DW$251, DW_AT_decl_column(0x10)
	.global	WAVE_fwm1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fwm1,SYM_SIZE(4)
WAVE_fwm1:
	.word	000000000h		; WAVE_fwm1 @ 0

$C$DW$252	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fwm1")
	.dwattr $C$DW$252, DW_AT_TI_symbol_name("WAVE_fwm1")
	.dwattr $C$DW$252, DW_AT_location[DW_OP_addr WAVE_fwm1]
	.dwattr $C$DW$252, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$252, DW_AT_external
	.dwattr $C$DW$252, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$252, DW_AT_decl_line(0xd3)
	.dwattr $C$DW$252, DW_AT_decl_column(0x10)
	.global	WAVE_fqs1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fqs1,SYM_SIZE(4)
WAVE_fqs1:
	.word	000000000h		; WAVE_fqs1 @ 0

$C$DW$253	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fqs1")
	.dwattr $C$DW$253, DW_AT_TI_symbol_name("WAVE_fqs1")
	.dwattr $C$DW$253, DW_AT_location[DW_OP_addr WAVE_fqs1]
	.dwattr $C$DW$253, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$253, DW_AT_external
	.dwattr $C$DW$253, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$253, DW_AT_decl_line(0xd4)
	.dwattr $C$DW$253, DW_AT_decl_column(0x10)
	.global	WAVE_fwl1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fwl1,SYM_SIZE(4)
WAVE_fwl1:
	.word	000000000h		; WAVE_fwl1 @ 0

$C$DW$254	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fwl1")
	.dwattr $C$DW$254, DW_AT_TI_symbol_name("WAVE_fwl1")
	.dwattr $C$DW$254, DW_AT_location[DW_OP_addr WAVE_fwl1]
	.dwattr $C$DW$254, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$254, DW_AT_external
	.dwattr $C$DW$254, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$254, DW_AT_decl_line(0xd5)
	.dwattr $C$DW$254, DW_AT_decl_column(0x10)
	.global	WAVE_Kpp3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Kpp3,SYM_SIZE(4)
WAVE_Kpp3:
	.word	000000000h		; WAVE_Kpp3 @ 0

$C$DW$255	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Kpp3")
	.dwattr $C$DW$255, DW_AT_TI_symbol_name("WAVE_Kpp3")
	.dwattr $C$DW$255, DW_AT_location[DW_OP_addr WAVE_Kpp3]
	.dwattr $C$DW$255, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$255, DW_AT_external
	.dwattr $C$DW$255, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$255, DW_AT_decl_line(0xd7)
	.dwattr $C$DW$255, DW_AT_decl_column(0x10)
	.global	WAVE_Kvp3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Kvp3,SYM_SIZE(4)
WAVE_Kvp3:
	.word	000000000h		; WAVE_Kvp3 @ 0

$C$DW$256	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Kvp3")
	.dwattr $C$DW$256, DW_AT_TI_symbol_name("WAVE_Kvp3")
	.dwattr $C$DW$256, DW_AT_location[DW_OP_addr WAVE_Kvp3]
	.dwattr $C$DW$256, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$256, DW_AT_external
	.dwattr $C$DW$256, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$256, DW_AT_decl_line(0xd8)
	.dwattr $C$DW$256, DW_AT_decl_column(0x10)
	.global	WAVE_Kvi3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Kvi3,SYM_SIZE(4)
WAVE_Kvi3:
	.word	000000000h		; WAVE_Kvi3 @ 0

$C$DW$257	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Kvi3")
	.dwattr $C$DW$257, DW_AT_TI_symbol_name("WAVE_Kvi3")
	.dwattr $C$DW$257, DW_AT_location[DW_OP_addr WAVE_Kvi3]
	.dwattr $C$DW$257, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$257, DW_AT_external
	.dwattr $C$DW$257, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$257, DW_AT_decl_line(0xd9)
	.dwattr $C$DW$257, DW_AT_decl_column(0x10)
	.global	WAVE_fwm3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fwm3,SYM_SIZE(4)
WAVE_fwm3:
	.word	000000000h		; WAVE_fwm3 @ 0

$C$DW$258	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fwm3")
	.dwattr $C$DW$258, DW_AT_TI_symbol_name("WAVE_fwm3")
	.dwattr $C$DW$258, DW_AT_location[DW_OP_addr WAVE_fwm3]
	.dwattr $C$DW$258, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$258, DW_AT_external
	.dwattr $C$DW$258, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$258, DW_AT_decl_line(0xda)
	.dwattr $C$DW$258, DW_AT_decl_column(0x10)
	.global	WAVE_fqs3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fqs3,SYM_SIZE(4)
WAVE_fqs3:
	.word	000000000h		; WAVE_fqs3 @ 0

$C$DW$259	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fqs3")
	.dwattr $C$DW$259, DW_AT_TI_symbol_name("WAVE_fqs3")
	.dwattr $C$DW$259, DW_AT_location[DW_OP_addr WAVE_fqs3]
	.dwattr $C$DW$259, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$259, DW_AT_external
	.dwattr $C$DW$259, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$259, DW_AT_decl_line(0xdb)
	.dwattr $C$DW$259, DW_AT_decl_column(0x10)
	.global	WAVE_fwl3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fwl3,SYM_SIZE(4)
WAVE_fwl3:
	.word	000000000h		; WAVE_fwl3 @ 0

$C$DW$260	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fwl3")
	.dwattr $C$DW$260, DW_AT_TI_symbol_name("WAVE_fwl3")
	.dwattr $C$DW$260, DW_AT_location[DW_OP_addr WAVE_fwl3]
	.dwattr $C$DW$260, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$260, DW_AT_external
	.dwattr $C$DW$260, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$260, DW_AT_decl_line(0xdc)
	.dwattr $C$DW$260, DW_AT_decl_column(0x10)
	.global	WAVE_Kpp2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Kpp2,SYM_SIZE(4)
WAVE_Kpp2:
	.word	000000000h		; WAVE_Kpp2 @ 0

$C$DW$261	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Kpp2")
	.dwattr $C$DW$261, DW_AT_TI_symbol_name("WAVE_Kpp2")
	.dwattr $C$DW$261, DW_AT_location[DW_OP_addr WAVE_Kpp2]
	.dwattr $C$DW$261, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$261, DW_AT_external
	.dwattr $C$DW$261, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$261, DW_AT_decl_line(0xde)
	.dwattr $C$DW$261, DW_AT_decl_column(0x10)
	.global	WAVE_Kvp2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Kvp2,SYM_SIZE(4)
WAVE_Kvp2:
	.word	000000000h		; WAVE_Kvp2 @ 0

$C$DW$262	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Kvp2")
	.dwattr $C$DW$262, DW_AT_TI_symbol_name("WAVE_Kvp2")
	.dwattr $C$DW$262, DW_AT_location[DW_OP_addr WAVE_Kvp2]
	.dwattr $C$DW$262, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$262, DW_AT_external
	.dwattr $C$DW$262, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$262, DW_AT_decl_line(0xdf)
	.dwattr $C$DW$262, DW_AT_decl_column(0x10)
	.global	WAVE_Kvi2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Kvi2,SYM_SIZE(4)
WAVE_Kvi2:
	.word	000000000h		; WAVE_Kvi2 @ 0

$C$DW$263	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Kvi2")
	.dwattr $C$DW$263, DW_AT_TI_symbol_name("WAVE_Kvi2")
	.dwattr $C$DW$263, DW_AT_location[DW_OP_addr WAVE_Kvi2]
	.dwattr $C$DW$263, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$263, DW_AT_external
	.dwattr $C$DW$263, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$263, DW_AT_decl_line(0xe0)
	.dwattr $C$DW$263, DW_AT_decl_column(0x10)
	.global	WAVE_fwm2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fwm2,SYM_SIZE(4)
WAVE_fwm2:
	.word	000000000h		; WAVE_fwm2 @ 0

$C$DW$264	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fwm2")
	.dwattr $C$DW$264, DW_AT_TI_symbol_name("WAVE_fwm2")
	.dwattr $C$DW$264, DW_AT_location[DW_OP_addr WAVE_fwm2]
	.dwattr $C$DW$264, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$264, DW_AT_external
	.dwattr $C$DW$264, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$264, DW_AT_decl_line(0xe1)
	.dwattr $C$DW$264, DW_AT_decl_column(0x10)
	.global	WAVE_fqs2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fqs2,SYM_SIZE(4)
WAVE_fqs2:
	.word	000000000h		; WAVE_fqs2 @ 0

$C$DW$265	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fqs2")
	.dwattr $C$DW$265, DW_AT_TI_symbol_name("WAVE_fqs2")
	.dwattr $C$DW$265, DW_AT_location[DW_OP_addr WAVE_fqs2]
	.dwattr $C$DW$265, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$265, DW_AT_external
	.dwattr $C$DW$265, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$265, DW_AT_decl_line(0xe2)
	.dwattr $C$DW$265, DW_AT_decl_column(0x10)
	.global	WAVE_fwl2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_fwl2,SYM_SIZE(4)
WAVE_fwl2:
	.word	000000000h		; WAVE_fwl2 @ 0

$C$DW$266	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_fwl2")
	.dwattr $C$DW$266, DW_AT_TI_symbol_name("WAVE_fwl2")
	.dwattr $C$DW$266, DW_AT_location[DW_OP_addr WAVE_fwl2]
	.dwattr $C$DW$266, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$266, DW_AT_external
	.dwattr $C$DW$266, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$266, DW_AT_decl_line(0xe3)
	.dwattr $C$DW$266, DW_AT_decl_column(0x10)
	.global	WAVE_tauLdyn1
	.bss	WAVE_tauLdyn1,4,4
$C$DW$267	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_tauLdyn1")
	.dwattr $C$DW$267, DW_AT_TI_symbol_name("WAVE_tauLdyn1")
	.dwattr $C$DW$267, DW_AT_location[DW_OP_addr WAVE_tauLdyn1]
	.dwattr $C$DW$267, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$267, DW_AT_external
	.dwattr $C$DW$267, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$267, DW_AT_decl_line(0xe6)
	.dwattr $C$DW$267, DW_AT_decl_column(0x10)
	.global	WAVE_tauLdyn2
	.bss	WAVE_tauLdyn2,4,4
$C$DW$268	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_tauLdyn2")
	.dwattr $C$DW$268, DW_AT_TI_symbol_name("WAVE_tauLdyn2")
	.dwattr $C$DW$268, DW_AT_location[DW_OP_addr WAVE_tauLdyn2]
	.dwattr $C$DW$268, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$268, DW_AT_external
	.dwattr $C$DW$268, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$268, DW_AT_decl_line(0xe7)
	.dwattr $C$DW$268, DW_AT_decl_column(0x10)
	.global	WAVE_tauLdyn3
	.bss	WAVE_tauLdyn3,4,4
$C$DW$269	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_tauLdyn3")
	.dwattr $C$DW$269, DW_AT_TI_symbol_name("WAVE_tauLdyn3")
	.dwattr $C$DW$269, DW_AT_location[DW_OP_addr WAVE_tauLdyn3]
	.dwattr $C$DW$269, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$269, DW_AT_external
	.dwattr $C$DW$269, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$269, DW_AT_decl_line(0xe8)
	.dwattr $C$DW$269, DW_AT_decl_column(0x10)
	.global	WAVE_Jl_calc1
	.bss	WAVE_Jl_calc1,4,4
$C$DW$270	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Jl_calc1")
	.dwattr $C$DW$270, DW_AT_TI_symbol_name("WAVE_Jl_calc1")
	.dwattr $C$DW$270, DW_AT_location[DW_OP_addr WAVE_Jl_calc1]
	.dwattr $C$DW$270, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$270, DW_AT_external
	.dwattr $C$DW$270, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$270, DW_AT_decl_line(0xea)
	.dwattr $C$DW$270, DW_AT_decl_column(0x10)
	.global	WAVE_Jl_calc2
	.bss	WAVE_Jl_calc2,4,4
$C$DW$271	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Jl_calc2")
	.dwattr $C$DW$271, DW_AT_TI_symbol_name("WAVE_Jl_calc2")
	.dwattr $C$DW$271, DW_AT_location[DW_OP_addr WAVE_Jl_calc2]
	.dwattr $C$DW$271, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$271, DW_AT_external
	.dwattr $C$DW$271, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$271, DW_AT_decl_line(0xeb)
	.dwattr $C$DW$271, DW_AT_decl_column(0x10)
	.global	WAVE_Jl_calc3
	.bss	WAVE_Jl_calc3,4,4
$C$DW$272	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Jl_calc3")
	.dwattr $C$DW$272, DW_AT_TI_symbol_name("WAVE_Jl_calc3")
	.dwattr $C$DW$272, DW_AT_location[DW_OP_addr WAVE_Jl_calc3]
	.dwattr $C$DW$272, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$272, DW_AT_external
	.dwattr $C$DW$272, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$272, DW_AT_decl_line(0xec)
	.dwattr $C$DW$272, DW_AT_decl_column(0x10)
	.global	WAVE_al_calc1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_al_calc1,SYM_SIZE(4)
WAVE_al_calc1:
	.word	000000000h		; WAVE_al_calc1 @ 0

$C$DW$273	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_al_calc1")
	.dwattr $C$DW$273, DW_AT_TI_symbol_name("WAVE_al_calc1")
	.dwattr $C$DW$273, DW_AT_location[DW_OP_addr WAVE_al_calc1]
	.dwattr $C$DW$273, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$273, DW_AT_external
	.dwattr $C$DW$273, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$273, DW_AT_decl_line(0xef)
	.dwattr $C$DW$273, DW_AT_decl_column(0x10)
	.global	WAVE_wl_calc1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wl_calc1,SYM_SIZE(4)
WAVE_wl_calc1:
	.word	000000000h		; WAVE_wl_calc1 @ 0

$C$DW$274	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wl_calc1")
	.dwattr $C$DW$274, DW_AT_TI_symbol_name("WAVE_wl_calc1")
	.dwattr $C$DW$274, DW_AT_location[DW_OP_addr WAVE_wl_calc1]
	.dwattr $C$DW$274, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$274, DW_AT_external
	.dwattr $C$DW$274, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$274, DW_AT_decl_line(0xf0)
	.dwattr $C$DW$274, DW_AT_decl_column(0x10)
	.global	WAVE_ql_calc1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_ql_calc1,SYM_SIZE(4)
WAVE_ql_calc1:
	.word	000000000h		; WAVE_ql_calc1 @ 0

$C$DW$275	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ql_calc1")
	.dwattr $C$DW$275, DW_AT_TI_symbol_name("WAVE_ql_calc1")
	.dwattr $C$DW$275, DW_AT_location[DW_OP_addr WAVE_ql_calc1]
	.dwattr $C$DW$275, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$275, DW_AT_external
	.dwattr $C$DW$275, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$275, DW_AT_decl_line(0xf1)
	.dwattr $C$DW$275, DW_AT_decl_column(0x10)
	.global	WAVE_wm_calc1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wm_calc1,SYM_SIZE(4)
WAVE_wm_calc1:
	.word	000000000h		; WAVE_wm_calc1 @ 0

$C$DW$276	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_calc1")
	.dwattr $C$DW$276, DW_AT_TI_symbol_name("WAVE_wm_calc1")
	.dwattr $C$DW$276, DW_AT_location[DW_OP_addr WAVE_wm_calc1]
	.dwattr $C$DW$276, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$276, DW_AT_external
	.dwattr $C$DW$276, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$276, DW_AT_decl_line(0xf2)
	.dwattr $C$DW$276, DW_AT_decl_column(0x10)
	.global	WAVE_al_calc2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_al_calc2,SYM_SIZE(4)
WAVE_al_calc2:
	.word	000000000h		; WAVE_al_calc2 @ 0

$C$DW$277	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_al_calc2")
	.dwattr $C$DW$277, DW_AT_TI_symbol_name("WAVE_al_calc2")
	.dwattr $C$DW$277, DW_AT_location[DW_OP_addr WAVE_al_calc2]
	.dwattr $C$DW$277, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$277, DW_AT_external
	.dwattr $C$DW$277, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$277, DW_AT_decl_line(0xf3)
	.dwattr $C$DW$277, DW_AT_decl_column(0x10)
	.global	WAVE_wl_calc2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wl_calc2,SYM_SIZE(4)
WAVE_wl_calc2:
	.word	000000000h		; WAVE_wl_calc2 @ 0

$C$DW$278	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wl_calc2")
	.dwattr $C$DW$278, DW_AT_TI_symbol_name("WAVE_wl_calc2")
	.dwattr $C$DW$278, DW_AT_location[DW_OP_addr WAVE_wl_calc2]
	.dwattr $C$DW$278, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$278, DW_AT_external
	.dwattr $C$DW$278, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$278, DW_AT_decl_line(0xf4)
	.dwattr $C$DW$278, DW_AT_decl_column(0x10)
	.global	WAVE_ql_calc2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_ql_calc2,SYM_SIZE(4)
WAVE_ql_calc2:
	.word	000000000h		; WAVE_ql_calc2 @ 0

$C$DW$279	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ql_calc2")
	.dwattr $C$DW$279, DW_AT_TI_symbol_name("WAVE_ql_calc2")
	.dwattr $C$DW$279, DW_AT_location[DW_OP_addr WAVE_ql_calc2]
	.dwattr $C$DW$279, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$279, DW_AT_external
	.dwattr $C$DW$279, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$279, DW_AT_decl_line(0xf5)
	.dwattr $C$DW$279, DW_AT_decl_column(0x10)
	.global	WAVE_wm_calc2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wm_calc2,SYM_SIZE(4)
WAVE_wm_calc2:
	.word	000000000h		; WAVE_wm_calc2 @ 0

$C$DW$280	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_calc2")
	.dwattr $C$DW$280, DW_AT_TI_symbol_name("WAVE_wm_calc2")
	.dwattr $C$DW$280, DW_AT_location[DW_OP_addr WAVE_wm_calc2]
	.dwattr $C$DW$280, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$280, DW_AT_external
	.dwattr $C$DW$280, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$280, DW_AT_decl_line(0xf6)
	.dwattr $C$DW$280, DW_AT_decl_column(0x10)
	.global	WAVE_al_calc3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_al_calc3,SYM_SIZE(4)
WAVE_al_calc3:
	.word	000000000h		; WAVE_al_calc3 @ 0

$C$DW$281	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_al_calc3")
	.dwattr $C$DW$281, DW_AT_TI_symbol_name("WAVE_al_calc3")
	.dwattr $C$DW$281, DW_AT_location[DW_OP_addr WAVE_al_calc3]
	.dwattr $C$DW$281, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$281, DW_AT_external
	.dwattr $C$DW$281, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$281, DW_AT_decl_line(0xf7)
	.dwattr $C$DW$281, DW_AT_decl_column(0x10)
	.global	WAVE_wl_calc3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wl_calc3,SYM_SIZE(4)
WAVE_wl_calc3:
	.word	000000000h		; WAVE_wl_calc3 @ 0

$C$DW$282	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wl_calc3")
	.dwattr $C$DW$282, DW_AT_TI_symbol_name("WAVE_wl_calc3")
	.dwattr $C$DW$282, DW_AT_location[DW_OP_addr WAVE_wl_calc3]
	.dwattr $C$DW$282, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$282, DW_AT_external
	.dwattr $C$DW$282, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$282, DW_AT_decl_line(0xf8)
	.dwattr $C$DW$282, DW_AT_decl_column(0x10)
	.global	WAVE_ql_calc3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_ql_calc3,SYM_SIZE(4)
WAVE_ql_calc3:
	.word	000000000h		; WAVE_ql_calc3 @ 0

$C$DW$283	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ql_calc3")
	.dwattr $C$DW$283, DW_AT_TI_symbol_name("WAVE_ql_calc3")
	.dwattr $C$DW$283, DW_AT_location[DW_OP_addr WAVE_ql_calc3]
	.dwattr $C$DW$283, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$283, DW_AT_external
	.dwattr $C$DW$283, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$283, DW_AT_decl_line(0xf9)
	.dwattr $C$DW$283, DW_AT_decl_column(0x10)
	.global	WAVE_wm_calc3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wm_calc3,SYM_SIZE(4)
WAVE_wm_calc3:
	.word	000000000h		; WAVE_wm_calc3 @ 0

$C$DW$284	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_calc3")
	.dwattr $C$DW$284, DW_AT_TI_symbol_name("WAVE_wm_calc3")
	.dwattr $C$DW$284, DW_AT_location[DW_OP_addr WAVE_wm_calc3]
	.dwattr $C$DW$284, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$284, DW_AT_external
	.dwattr $C$DW$284, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$284, DW_AT_decl_line(0xfa)
	.dwattr $C$DW$284, DW_AT_decl_column(0x10)
	.global	WAVE_al_calc_DPD1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_al_calc_DPD1,SYM_SIZE(4)
WAVE_al_calc_DPD1:
	.word	000000000h		; WAVE_al_calc_DPD1 @ 0

$C$DW$285	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_al_calc_DPD1")
	.dwattr $C$DW$285, DW_AT_TI_symbol_name("WAVE_al_calc_DPD1")
	.dwattr $C$DW$285, DW_AT_location[DW_OP_addr WAVE_al_calc_DPD1]
	.dwattr $C$DW$285, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$285, DW_AT_external
	.dwattr $C$DW$285, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$285, DW_AT_decl_line(0xfc)
	.dwattr $C$DW$285, DW_AT_decl_column(0x10)
	.global	WAVE_wl_calc_DPD1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wl_calc_DPD1,SYM_SIZE(4)
WAVE_wl_calc_DPD1:
	.word	000000000h		; WAVE_wl_calc_DPD1 @ 0

$C$DW$286	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wl_calc_DPD1")
	.dwattr $C$DW$286, DW_AT_TI_symbol_name("WAVE_wl_calc_DPD1")
	.dwattr $C$DW$286, DW_AT_location[DW_OP_addr WAVE_wl_calc_DPD1]
	.dwattr $C$DW$286, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$286, DW_AT_external
	.dwattr $C$DW$286, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$286, DW_AT_decl_line(0xfd)
	.dwattr $C$DW$286, DW_AT_decl_column(0x10)
	.global	WAVE_ql_calc_DPD1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_ql_calc_DPD1,SYM_SIZE(4)
WAVE_ql_calc_DPD1:
	.word	000000000h		; WAVE_ql_calc_DPD1 @ 0

$C$DW$287	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ql_calc_DPD1")
	.dwattr $C$DW$287, DW_AT_TI_symbol_name("WAVE_ql_calc_DPD1")
	.dwattr $C$DW$287, DW_AT_location[DW_OP_addr WAVE_ql_calc_DPD1]
	.dwattr $C$DW$287, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$287, DW_AT_external
	.dwattr $C$DW$287, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$287, DW_AT_decl_line(0xfe)
	.dwattr $C$DW$287, DW_AT_decl_column(0x10)
	.global	WAVE_wm_calc_DPD1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wm_calc_DPD1,SYM_SIZE(4)
WAVE_wm_calc_DPD1:
	.word	000000000h		; WAVE_wm_calc_DPD1 @ 0

$C$DW$288	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_calc_DPD1")
	.dwattr $C$DW$288, DW_AT_TI_symbol_name("WAVE_wm_calc_DPD1")
	.dwattr $C$DW$288, DW_AT_location[DW_OP_addr WAVE_wm_calc_DPD1]
	.dwattr $C$DW$288, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$288, DW_AT_external
	.dwattr $C$DW$288, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$288, DW_AT_decl_line(0xff)
	.dwattr $C$DW$288, DW_AT_decl_column(0x10)
	.global	WAVE_al_calc_DPD2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_al_calc_DPD2,SYM_SIZE(4)
WAVE_al_calc_DPD2:
	.word	000000000h		; WAVE_al_calc_DPD2 @ 0

$C$DW$289	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_al_calc_DPD2")
	.dwattr $C$DW$289, DW_AT_TI_symbol_name("WAVE_al_calc_DPD2")
	.dwattr $C$DW$289, DW_AT_location[DW_OP_addr WAVE_al_calc_DPD2]
	.dwattr $C$DW$289, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$289, DW_AT_external
	.dwattr $C$DW$289, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$289, DW_AT_decl_line(0x100)
	.dwattr $C$DW$289, DW_AT_decl_column(0x10)
	.global	WAVE_wl_calc_DPD2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wl_calc_DPD2,SYM_SIZE(4)
WAVE_wl_calc_DPD2:
	.word	000000000h		; WAVE_wl_calc_DPD2 @ 0

$C$DW$290	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wl_calc_DPD2")
	.dwattr $C$DW$290, DW_AT_TI_symbol_name("WAVE_wl_calc_DPD2")
	.dwattr $C$DW$290, DW_AT_location[DW_OP_addr WAVE_wl_calc_DPD2]
	.dwattr $C$DW$290, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$290, DW_AT_external
	.dwattr $C$DW$290, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$290, DW_AT_decl_line(0x101)
	.dwattr $C$DW$290, DW_AT_decl_column(0x10)
	.global	WAVE_ql_calc_DPD2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_ql_calc_DPD2,SYM_SIZE(4)
WAVE_ql_calc_DPD2:
	.word	000000000h		; WAVE_ql_calc_DPD2 @ 0

$C$DW$291	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ql_calc_DPD2")
	.dwattr $C$DW$291, DW_AT_TI_symbol_name("WAVE_ql_calc_DPD2")
	.dwattr $C$DW$291, DW_AT_location[DW_OP_addr WAVE_ql_calc_DPD2]
	.dwattr $C$DW$291, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$291, DW_AT_external
	.dwattr $C$DW$291, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$291, DW_AT_decl_line(0x102)
	.dwattr $C$DW$291, DW_AT_decl_column(0x10)
	.global	WAVE_wm_calc_DPD2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wm_calc_DPD2,SYM_SIZE(4)
WAVE_wm_calc_DPD2:
	.word	000000000h		; WAVE_wm_calc_DPD2 @ 0

$C$DW$292	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_calc_DPD2")
	.dwattr $C$DW$292, DW_AT_TI_symbol_name("WAVE_wm_calc_DPD2")
	.dwattr $C$DW$292, DW_AT_location[DW_OP_addr WAVE_wm_calc_DPD2]
	.dwattr $C$DW$292, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$292, DW_AT_external
	.dwattr $C$DW$292, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$292, DW_AT_decl_line(0x103)
	.dwattr $C$DW$292, DW_AT_decl_column(0x10)
	.global	WAVE_al_calc_DPD3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_al_calc_DPD3,SYM_SIZE(4)
WAVE_al_calc_DPD3:
	.word	000000000h		; WAVE_al_calc_DPD3 @ 0

$C$DW$293	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_al_calc_DPD3")
	.dwattr $C$DW$293, DW_AT_TI_symbol_name("WAVE_al_calc_DPD3")
	.dwattr $C$DW$293, DW_AT_location[DW_OP_addr WAVE_al_calc_DPD3]
	.dwattr $C$DW$293, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$293, DW_AT_external
	.dwattr $C$DW$293, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$293, DW_AT_decl_line(0x104)
	.dwattr $C$DW$293, DW_AT_decl_column(0x10)
	.global	WAVE_wl_calc_DPD3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wl_calc_DPD3,SYM_SIZE(4)
WAVE_wl_calc_DPD3:
	.word	000000000h		; WAVE_wl_calc_DPD3 @ 0

$C$DW$294	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wl_calc_DPD3")
	.dwattr $C$DW$294, DW_AT_TI_symbol_name("WAVE_wl_calc_DPD3")
	.dwattr $C$DW$294, DW_AT_location[DW_OP_addr WAVE_wl_calc_DPD3]
	.dwattr $C$DW$294, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$294, DW_AT_external
	.dwattr $C$DW$294, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$294, DW_AT_decl_line(0x105)
	.dwattr $C$DW$294, DW_AT_decl_column(0x10)
	.global	WAVE_ql_calc_DPD3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_ql_calc_DPD3,SYM_SIZE(4)
WAVE_ql_calc_DPD3:
	.word	000000000h		; WAVE_ql_calc_DPD3 @ 0

$C$DW$295	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ql_calc_DPD3")
	.dwattr $C$DW$295, DW_AT_TI_symbol_name("WAVE_ql_calc_DPD3")
	.dwattr $C$DW$295, DW_AT_location[DW_OP_addr WAVE_ql_calc_DPD3]
	.dwattr $C$DW$295, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$295, DW_AT_external
	.dwattr $C$DW$295, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$295, DW_AT_decl_line(0x106)
	.dwattr $C$DW$295, DW_AT_decl_column(0x10)
	.global	WAVE_wm_calc_DPD3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_wm_calc_DPD3,SYM_SIZE(4)
WAVE_wm_calc_DPD3:
	.word	000000000h		; WAVE_wm_calc_DPD3 @ 0

$C$DW$296	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_calc_DPD3")
	.dwattr $C$DW$296, DW_AT_TI_symbol_name("WAVE_wm_calc_DPD3")
	.dwattr $C$DW$296, DW_AT_location[DW_OP_addr WAVE_wm_calc_DPD3]
	.dwattr $C$DW$296, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$296, DW_AT_external
	.dwattr $C$DW$296, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$296, DW_AT_decl_line(0x107)
	.dwattr $C$DW$296, DW_AT_decl_column(0x10)
	.global	WAVE_est_wm1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_wm1,SYM_SIZE(4)
WAVE_est_wm1:
	.word	000000000h		; WAVE_est_wm1 @ 0

$C$DW$297	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_wm1")
	.dwattr $C$DW$297, DW_AT_TI_symbol_name("WAVE_est_wm1")
	.dwattr $C$DW$297, DW_AT_location[DW_OP_addr WAVE_est_wm1]
	.dwattr $C$DW$297, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$297, DW_AT_external
	.dwattr $C$DW$297, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$297, DW_AT_decl_line(0x109)
	.dwattr $C$DW$297, DW_AT_decl_column(0x10)
	.global	WAVE_est_qs1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_qs1,SYM_SIZE(4)
WAVE_est_qs1:
	.word	000000000h		; WAVE_est_qs1 @ 0

$C$DW$298	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_qs1")
	.dwattr $C$DW$298, DW_AT_TI_symbol_name("WAVE_est_qs1")
	.dwattr $C$DW$298, DW_AT_location[DW_OP_addr WAVE_est_qs1]
	.dwattr $C$DW$298, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$298, DW_AT_external
	.dwattr $C$DW$298, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$298, DW_AT_decl_line(0x10a)
	.dwattr $C$DW$298, DW_AT_decl_column(0x10)
	.global	WAVE_est_wl1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_wl1,SYM_SIZE(4)
WAVE_est_wl1:
	.word	000000000h		; WAVE_est_wl1 @ 0

$C$DW$299	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_wl1")
	.dwattr $C$DW$299, DW_AT_TI_symbol_name("WAVE_est_wl1")
	.dwattr $C$DW$299, DW_AT_location[DW_OP_addr WAVE_est_wl1]
	.dwattr $C$DW$299, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$299, DW_AT_external
	.dwattr $C$DW$299, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$299, DW_AT_decl_line(0x10b)
	.dwattr $C$DW$299, DW_AT_decl_column(0x10)
	.global	WAVE_est_wm2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_wm2,SYM_SIZE(4)
WAVE_est_wm2:
	.word	000000000h		; WAVE_est_wm2 @ 0

$C$DW$300	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_wm2")
	.dwattr $C$DW$300, DW_AT_TI_symbol_name("WAVE_est_wm2")
	.dwattr $C$DW$300, DW_AT_location[DW_OP_addr WAVE_est_wm2]
	.dwattr $C$DW$300, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$300, DW_AT_external
	.dwattr $C$DW$300, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$300, DW_AT_decl_line(0x10c)
	.dwattr $C$DW$300, DW_AT_decl_column(0x10)
	.global	WAVE_est_qs2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_qs2,SYM_SIZE(4)
WAVE_est_qs2:
	.word	000000000h		; WAVE_est_qs2 @ 0

$C$DW$301	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_qs2")
	.dwattr $C$DW$301, DW_AT_TI_symbol_name("WAVE_est_qs2")
	.dwattr $C$DW$301, DW_AT_location[DW_OP_addr WAVE_est_qs2]
	.dwattr $C$DW$301, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$301, DW_AT_external
	.dwattr $C$DW$301, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$301, DW_AT_decl_line(0x10d)
	.dwattr $C$DW$301, DW_AT_decl_column(0x10)
	.global	WAVE_est_wl2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_wl2,SYM_SIZE(4)
WAVE_est_wl2:
	.word	000000000h		; WAVE_est_wl2 @ 0

$C$DW$302	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_wl2")
	.dwattr $C$DW$302, DW_AT_TI_symbol_name("WAVE_est_wl2")
	.dwattr $C$DW$302, DW_AT_location[DW_OP_addr WAVE_est_wl2]
	.dwattr $C$DW$302, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$302, DW_AT_external
	.dwattr $C$DW$302, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$302, DW_AT_decl_line(0x10e)
	.dwattr $C$DW$302, DW_AT_decl_column(0x10)
	.global	WAVE_est_wm3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_wm3,SYM_SIZE(4)
WAVE_est_wm3:
	.word	000000000h		; WAVE_est_wm3 @ 0

$C$DW$303	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_wm3")
	.dwattr $C$DW$303, DW_AT_TI_symbol_name("WAVE_est_wm3")
	.dwattr $C$DW$303, DW_AT_location[DW_OP_addr WAVE_est_wm3]
	.dwattr $C$DW$303, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$303, DW_AT_external
	.dwattr $C$DW$303, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$303, DW_AT_decl_line(0x10f)
	.dwattr $C$DW$303, DW_AT_decl_column(0x10)
	.global	WAVE_est_qs3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_qs3,SYM_SIZE(4)
WAVE_est_qs3:
	.word	000000000h		; WAVE_est_qs3 @ 0

$C$DW$304	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_qs3")
	.dwattr $C$DW$304, DW_AT_TI_symbol_name("WAVE_est_qs3")
	.dwattr $C$DW$304, DW_AT_location[DW_OP_addr WAVE_est_qs3]
	.dwattr $C$DW$304, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$304, DW_AT_external
	.dwattr $C$DW$304, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$304, DW_AT_decl_line(0x110)
	.dwattr $C$DW$304, DW_AT_decl_column(0x10)
	.global	WAVE_est_wl3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_wl3,SYM_SIZE(4)
WAVE_est_wl3:
	.word	000000000h		; WAVE_est_wl3 @ 0

$C$DW$305	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_wl3")
	.dwattr $C$DW$305, DW_AT_TI_symbol_name("WAVE_est_wl3")
	.dwattr $C$DW$305, DW_AT_location[DW_OP_addr WAVE_est_wl3]
	.dwattr $C$DW$305, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$305, DW_AT_external
	.dwattr $C$DW$305, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$305, DW_AT_decl_line(0x111)
	.dwattr $C$DW$305, DW_AT_decl_column(0x10)
	.global	WAVE_est_conv_wm1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_conv_wm1,SYM_SIZE(4)
WAVE_est_conv_wm1:
	.word	000000000h		; WAVE_est_conv_wm1 @ 0

$C$DW$306	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_conv_wm1")
	.dwattr $C$DW$306, DW_AT_TI_symbol_name("WAVE_est_conv_wm1")
	.dwattr $C$DW$306, DW_AT_location[DW_OP_addr WAVE_est_conv_wm1]
	.dwattr $C$DW$306, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$306, DW_AT_external
	.dwattr $C$DW$306, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$306, DW_AT_decl_line(0x113)
	.dwattr $C$DW$306, DW_AT_decl_column(0x10)
	.global	WAVE_est_conv_qs1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_conv_qs1,SYM_SIZE(4)
WAVE_est_conv_qs1:
	.word	000000000h		; WAVE_est_conv_qs1 @ 0

$C$DW$307	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_conv_qs1")
	.dwattr $C$DW$307, DW_AT_TI_symbol_name("WAVE_est_conv_qs1")
	.dwattr $C$DW$307, DW_AT_location[DW_OP_addr WAVE_est_conv_qs1]
	.dwattr $C$DW$307, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$307, DW_AT_external
	.dwattr $C$DW$307, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$307, DW_AT_decl_line(0x114)
	.dwattr $C$DW$307, DW_AT_decl_column(0x10)
	.global	WAVE_est_conv_wl1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_conv_wl1,SYM_SIZE(4)
WAVE_est_conv_wl1:
	.word	000000000h		; WAVE_est_conv_wl1 @ 0

$C$DW$308	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_conv_wl1")
	.dwattr $C$DW$308, DW_AT_TI_symbol_name("WAVE_est_conv_wl1")
	.dwattr $C$DW$308, DW_AT_location[DW_OP_addr WAVE_est_conv_wl1]
	.dwattr $C$DW$308, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$308, DW_AT_external
	.dwattr $C$DW$308, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$308, DW_AT_decl_line(0x115)
	.dwattr $C$DW$308, DW_AT_decl_column(0x10)
	.global	WAVE_est_conv_wm2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_conv_wm2,SYM_SIZE(4)
WAVE_est_conv_wm2:
	.word	000000000h		; WAVE_est_conv_wm2 @ 0

$C$DW$309	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_conv_wm2")
	.dwattr $C$DW$309, DW_AT_TI_symbol_name("WAVE_est_conv_wm2")
	.dwattr $C$DW$309, DW_AT_location[DW_OP_addr WAVE_est_conv_wm2]
	.dwattr $C$DW$309, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$309, DW_AT_external
	.dwattr $C$DW$309, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$309, DW_AT_decl_line(0x116)
	.dwattr $C$DW$309, DW_AT_decl_column(0x10)
	.global	WAVE_est_conv_qs2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_conv_qs2,SYM_SIZE(4)
WAVE_est_conv_qs2:
	.word	000000000h		; WAVE_est_conv_qs2 @ 0

$C$DW$310	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_conv_qs2")
	.dwattr $C$DW$310, DW_AT_TI_symbol_name("WAVE_est_conv_qs2")
	.dwattr $C$DW$310, DW_AT_location[DW_OP_addr WAVE_est_conv_qs2]
	.dwattr $C$DW$310, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$310, DW_AT_external
	.dwattr $C$DW$310, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$310, DW_AT_decl_line(0x117)
	.dwattr $C$DW$310, DW_AT_decl_column(0x10)
	.global	WAVE_est_conv_wl2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_conv_wl2,SYM_SIZE(4)
WAVE_est_conv_wl2:
	.word	000000000h		; WAVE_est_conv_wl2 @ 0

$C$DW$311	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_conv_wl2")
	.dwattr $C$DW$311, DW_AT_TI_symbol_name("WAVE_est_conv_wl2")
	.dwattr $C$DW$311, DW_AT_location[DW_OP_addr WAVE_est_conv_wl2]
	.dwattr $C$DW$311, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$311, DW_AT_external
	.dwattr $C$DW$311, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$311, DW_AT_decl_line(0x118)
	.dwattr $C$DW$311, DW_AT_decl_column(0x10)
	.global	WAVE_est_conv_wm3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_conv_wm3,SYM_SIZE(4)
WAVE_est_conv_wm3:
	.word	000000000h		; WAVE_est_conv_wm3 @ 0

$C$DW$312	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_conv_wm3")
	.dwattr $C$DW$312, DW_AT_TI_symbol_name("WAVE_est_conv_wm3")
	.dwattr $C$DW$312, DW_AT_location[DW_OP_addr WAVE_est_conv_wm3]
	.dwattr $C$DW$312, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$312, DW_AT_external
	.dwattr $C$DW$312, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$312, DW_AT_decl_line(0x119)
	.dwattr $C$DW$312, DW_AT_decl_column(0x10)
	.global	WAVE_est_conv_qs3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_conv_qs3,SYM_SIZE(4)
WAVE_est_conv_qs3:
	.word	000000000h		; WAVE_est_conv_qs3 @ 0

$C$DW$313	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_conv_qs3")
	.dwattr $C$DW$313, DW_AT_TI_symbol_name("WAVE_est_conv_qs3")
	.dwattr $C$DW$313, DW_AT_location[DW_OP_addr WAVE_est_conv_qs3]
	.dwattr $C$DW$313, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$313, DW_AT_external
	.dwattr $C$DW$313, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$313, DW_AT_decl_line(0x11a)
	.dwattr $C$DW$313, DW_AT_decl_column(0x10)
	.global	WAVE_est_conv_wl3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_conv_wl3,SYM_SIZE(4)
WAVE_est_conv_wl3:
	.word	000000000h		; WAVE_est_conv_wl3 @ 0

$C$DW$314	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_conv_wl3")
	.dwattr $C$DW$314, DW_AT_TI_symbol_name("WAVE_est_conv_wl3")
	.dwattr $C$DW$314, DW_AT_location[DW_OP_addr WAVE_est_conv_wl3]
	.dwattr $C$DW$314, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$314, DW_AT_external
	.dwattr $C$DW$314, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$314, DW_AT_decl_line(0x11b)
	.dwattr $C$DW$314, DW_AT_decl_column(0x10)
	.global	WAVE_est_prop_wm1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_prop_wm1,SYM_SIZE(4)
WAVE_est_prop_wm1:
	.word	000000000h		; WAVE_est_prop_wm1 @ 0

$C$DW$315	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_prop_wm1")
	.dwattr $C$DW$315, DW_AT_TI_symbol_name("WAVE_est_prop_wm1")
	.dwattr $C$DW$315, DW_AT_location[DW_OP_addr WAVE_est_prop_wm1]
	.dwattr $C$DW$315, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$315, DW_AT_external
	.dwattr $C$DW$315, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$315, DW_AT_decl_line(0x11d)
	.dwattr $C$DW$315, DW_AT_decl_column(0x10)
	.global	WAVE_est_prop_qs1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_prop_qs1,SYM_SIZE(4)
WAVE_est_prop_qs1:
	.word	000000000h		; WAVE_est_prop_qs1 @ 0

$C$DW$316	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_prop_qs1")
	.dwattr $C$DW$316, DW_AT_TI_symbol_name("WAVE_est_prop_qs1")
	.dwattr $C$DW$316, DW_AT_location[DW_OP_addr WAVE_est_prop_qs1]
	.dwattr $C$DW$316, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$316, DW_AT_external
	.dwattr $C$DW$316, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$316, DW_AT_decl_line(0x11e)
	.dwattr $C$DW$316, DW_AT_decl_column(0x10)
	.global	WAVE_est_prop_wl1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_prop_wl1,SYM_SIZE(4)
WAVE_est_prop_wl1:
	.word	000000000h		; WAVE_est_prop_wl1 @ 0

$C$DW$317	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_prop_wl1")
	.dwattr $C$DW$317, DW_AT_TI_symbol_name("WAVE_est_prop_wl1")
	.dwattr $C$DW$317, DW_AT_location[DW_OP_addr WAVE_est_prop_wl1]
	.dwattr $C$DW$317, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$317, DW_AT_external
	.dwattr $C$DW$317, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$317, DW_AT_decl_line(0x11f)
	.dwattr $C$DW$317, DW_AT_decl_column(0x10)
	.global	WAVE_est_prop_wm2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_prop_wm2,SYM_SIZE(4)
WAVE_est_prop_wm2:
	.word	000000000h		; WAVE_est_prop_wm2 @ 0

$C$DW$318	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_prop_wm2")
	.dwattr $C$DW$318, DW_AT_TI_symbol_name("WAVE_est_prop_wm2")
	.dwattr $C$DW$318, DW_AT_location[DW_OP_addr WAVE_est_prop_wm2]
	.dwattr $C$DW$318, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$318, DW_AT_external
	.dwattr $C$DW$318, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$318, DW_AT_decl_line(0x120)
	.dwattr $C$DW$318, DW_AT_decl_column(0x10)
	.global	WAVE_est_prop_qs2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_prop_qs2,SYM_SIZE(4)
WAVE_est_prop_qs2:
	.word	000000000h		; WAVE_est_prop_qs2 @ 0

$C$DW$319	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_prop_qs2")
	.dwattr $C$DW$319, DW_AT_TI_symbol_name("WAVE_est_prop_qs2")
	.dwattr $C$DW$319, DW_AT_location[DW_OP_addr WAVE_est_prop_qs2]
	.dwattr $C$DW$319, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$319, DW_AT_external
	.dwattr $C$DW$319, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$319, DW_AT_decl_line(0x121)
	.dwattr $C$DW$319, DW_AT_decl_column(0x10)
	.global	WAVE_est_prop_wl2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_prop_wl2,SYM_SIZE(4)
WAVE_est_prop_wl2:
	.word	000000000h		; WAVE_est_prop_wl2 @ 0

$C$DW$320	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_prop_wl2")
	.dwattr $C$DW$320, DW_AT_TI_symbol_name("WAVE_est_prop_wl2")
	.dwattr $C$DW$320, DW_AT_location[DW_OP_addr WAVE_est_prop_wl2]
	.dwattr $C$DW$320, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$320, DW_AT_external
	.dwattr $C$DW$320, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$320, DW_AT_decl_line(0x122)
	.dwattr $C$DW$320, DW_AT_decl_column(0x10)
	.global	WAVE_est_prop_wm3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_prop_wm3,SYM_SIZE(4)
WAVE_est_prop_wm3:
	.word	000000000h		; WAVE_est_prop_wm3 @ 0

$C$DW$321	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_prop_wm3")
	.dwattr $C$DW$321, DW_AT_TI_symbol_name("WAVE_est_prop_wm3")
	.dwattr $C$DW$321, DW_AT_location[DW_OP_addr WAVE_est_prop_wm3]
	.dwattr $C$DW$321, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$321, DW_AT_external
	.dwattr $C$DW$321, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$321, DW_AT_decl_line(0x123)
	.dwattr $C$DW$321, DW_AT_decl_column(0x10)
	.global	WAVE_est_prop_qs3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_prop_qs3,SYM_SIZE(4)
WAVE_est_prop_qs3:
	.word	000000000h		; WAVE_est_prop_qs3 @ 0

$C$DW$322	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_prop_qs3")
	.dwattr $C$DW$322, DW_AT_TI_symbol_name("WAVE_est_prop_qs3")
	.dwattr $C$DW$322, DW_AT_location[DW_OP_addr WAVE_est_prop_qs3]
	.dwattr $C$DW$322, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$322, DW_AT_external
	.dwattr $C$DW$322, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$322, DW_AT_decl_line(0x124)
	.dwattr $C$DW$322, DW_AT_decl_column(0x10)
	.global	WAVE_est_prop_wl3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_prop_wl3,SYM_SIZE(4)
WAVE_est_prop_wl3:
	.word	000000000h		; WAVE_est_prop_wl3 @ 0

$C$DW$323	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_prop_wl3")
	.dwattr $C$DW$323, DW_AT_TI_symbol_name("WAVE_est_prop_wl3")
	.dwattr $C$DW$323, DW_AT_location[DW_OP_addr WAVE_est_prop_wl3]
	.dwattr $C$DW$323, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$323, DW_AT_external
	.dwattr $C$DW$323, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$323, DW_AT_decl_line(0x125)
	.dwattr $C$DW$323, DW_AT_decl_column(0x10)
	.global	WAVE_est_ISOB_wm1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_ISOB_wm1,SYM_SIZE(4)
WAVE_est_ISOB_wm1:
	.word	000000000h		; WAVE_est_ISOB_wm1 @ 0

$C$DW$324	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_ISOB_wm1")
	.dwattr $C$DW$324, DW_AT_TI_symbol_name("WAVE_est_ISOB_wm1")
	.dwattr $C$DW$324, DW_AT_location[DW_OP_addr WAVE_est_ISOB_wm1]
	.dwattr $C$DW$324, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$324, DW_AT_external
	.dwattr $C$DW$324, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$324, DW_AT_decl_line(0x127)
	.dwattr $C$DW$324, DW_AT_decl_column(0x10)
	.global	WAVE_est_ISOB_qs1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_ISOB_qs1,SYM_SIZE(4)
WAVE_est_ISOB_qs1:
	.word	000000000h		; WAVE_est_ISOB_qs1 @ 0

$C$DW$325	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_ISOB_qs1")
	.dwattr $C$DW$325, DW_AT_TI_symbol_name("WAVE_est_ISOB_qs1")
	.dwattr $C$DW$325, DW_AT_location[DW_OP_addr WAVE_est_ISOB_qs1]
	.dwattr $C$DW$325, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$325, DW_AT_external
	.dwattr $C$DW$325, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$325, DW_AT_decl_line(0x128)
	.dwattr $C$DW$325, DW_AT_decl_column(0x10)
	.global	WAVE_est_ISOB_wl1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_ISOB_wl1,SYM_SIZE(4)
WAVE_est_ISOB_wl1:
	.word	000000000h		; WAVE_est_ISOB_wl1 @ 0

$C$DW$326	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_ISOB_wl1")
	.dwattr $C$DW$326, DW_AT_TI_symbol_name("WAVE_est_ISOB_wl1")
	.dwattr $C$DW$326, DW_AT_location[DW_OP_addr WAVE_est_ISOB_wl1]
	.dwattr $C$DW$326, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$326, DW_AT_external
	.dwattr $C$DW$326, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$326, DW_AT_decl_line(0x129)
	.dwattr $C$DW$326, DW_AT_decl_column(0x10)
	.global	WAVE_est_ISOB_wm2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_ISOB_wm2,SYM_SIZE(4)
WAVE_est_ISOB_wm2:
	.word	000000000h		; WAVE_est_ISOB_wm2 @ 0

$C$DW$327	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_ISOB_wm2")
	.dwattr $C$DW$327, DW_AT_TI_symbol_name("WAVE_est_ISOB_wm2")
	.dwattr $C$DW$327, DW_AT_location[DW_OP_addr WAVE_est_ISOB_wm2]
	.dwattr $C$DW$327, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$327, DW_AT_external
	.dwattr $C$DW$327, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$327, DW_AT_decl_line(0x12a)
	.dwattr $C$DW$327, DW_AT_decl_column(0x10)
	.global	WAVE_est_ISOB_qs2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_ISOB_qs2,SYM_SIZE(4)
WAVE_est_ISOB_qs2:
	.word	000000000h		; WAVE_est_ISOB_qs2 @ 0

$C$DW$328	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_ISOB_qs2")
	.dwattr $C$DW$328, DW_AT_TI_symbol_name("WAVE_est_ISOB_qs2")
	.dwattr $C$DW$328, DW_AT_location[DW_OP_addr WAVE_est_ISOB_qs2]
	.dwattr $C$DW$328, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$328, DW_AT_external
	.dwattr $C$DW$328, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$328, DW_AT_decl_line(0x12b)
	.dwattr $C$DW$328, DW_AT_decl_column(0x10)
	.global	WAVE_est_ISOB_wl2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_ISOB_wl2,SYM_SIZE(4)
WAVE_est_ISOB_wl2:
	.word	000000000h		; WAVE_est_ISOB_wl2 @ 0

$C$DW$329	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_ISOB_wl2")
	.dwattr $C$DW$329, DW_AT_TI_symbol_name("WAVE_est_ISOB_wl2")
	.dwattr $C$DW$329, DW_AT_location[DW_OP_addr WAVE_est_ISOB_wl2]
	.dwattr $C$DW$329, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$329, DW_AT_external
	.dwattr $C$DW$329, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$329, DW_AT_decl_line(0x12c)
	.dwattr $C$DW$329, DW_AT_decl_column(0x10)
	.global	WAVE_est_ISOB_wm3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_ISOB_wm3,SYM_SIZE(4)
WAVE_est_ISOB_wm3:
	.word	000000000h		; WAVE_est_ISOB_wm3 @ 0

$C$DW$330	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_ISOB_wm3")
	.dwattr $C$DW$330, DW_AT_TI_symbol_name("WAVE_est_ISOB_wm3")
	.dwattr $C$DW$330, DW_AT_location[DW_OP_addr WAVE_est_ISOB_wm3]
	.dwattr $C$DW$330, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$330, DW_AT_external
	.dwattr $C$DW$330, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$330, DW_AT_decl_line(0x12d)
	.dwattr $C$DW$330, DW_AT_decl_column(0x10)
	.global	WAVE_est_ISOB_qs3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_ISOB_qs3,SYM_SIZE(4)
WAVE_est_ISOB_qs3:
	.word	000000000h		; WAVE_est_ISOB_qs3 @ 0

$C$DW$331	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_ISOB_qs3")
	.dwattr $C$DW$331, DW_AT_TI_symbol_name("WAVE_est_ISOB_qs3")
	.dwattr $C$DW$331, DW_AT_location[DW_OP_addr WAVE_est_ISOB_qs3]
	.dwattr $C$DW$331, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$331, DW_AT_external
	.dwattr $C$DW$331, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$331, DW_AT_decl_line(0x12e)
	.dwattr $C$DW$331, DW_AT_decl_column(0x10)
	.global	WAVE_est_ISOB_wl3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_est_ISOB_wl3,SYM_SIZE(4)
WAVE_est_ISOB_wl3:
	.word	000000000h		; WAVE_est_ISOB_wl3 @ 0

$C$DW$332	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_est_ISOB_wl3")
	.dwattr $C$DW$332, DW_AT_TI_symbol_name("WAVE_est_ISOB_wl3")
	.dwattr $C$DW$332, DW_AT_location[DW_OP_addr WAVE_est_ISOB_wl3]
	.dwattr $C$DW$332, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$332, DW_AT_external
	.dwattr $C$DW$332, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$332, DW_AT_decl_line(0x12f)
	.dwattr $C$DW$332, DW_AT_decl_column(0x10)
	.global	WAVE_IresU1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_IresU1,SYM_SIZE(4)
WAVE_IresU1:
	.word	000000000h		; WAVE_IresU1 @ 0

$C$DW$333	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresU1")
	.dwattr $C$DW$333, DW_AT_TI_symbol_name("WAVE_IresU1")
	.dwattr $C$DW$333, DW_AT_location[DW_OP_addr WAVE_IresU1]
	.dwattr $C$DW$333, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$333, DW_AT_external
	.dwattr $C$DW$333, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$333, DW_AT_decl_line(0x135)
	.dwattr $C$DW$333, DW_AT_decl_column(0x10)
	.global	WAVE_IresU2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_IresU2,SYM_SIZE(4)
WAVE_IresU2:
	.word	000000000h		; WAVE_IresU2 @ 0

$C$DW$334	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresU2")
	.dwattr $C$DW$334, DW_AT_TI_symbol_name("WAVE_IresU2")
	.dwattr $C$DW$334, DW_AT_location[DW_OP_addr WAVE_IresU2]
	.dwattr $C$DW$334, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$334, DW_AT_external
	.dwattr $C$DW$334, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$334, DW_AT_decl_line(0x136)
	.dwattr $C$DW$334, DW_AT_decl_column(0x10)
	.global	WAVE_IresU3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_IresU3,SYM_SIZE(4)
WAVE_IresU3:
	.word	000000000h		; WAVE_IresU3 @ 0

$C$DW$335	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresU3")
	.dwattr $C$DW$335, DW_AT_TI_symbol_name("WAVE_IresU3")
	.dwattr $C$DW$335, DW_AT_location[DW_OP_addr WAVE_IresU3]
	.dwattr $C$DW$335, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$335, DW_AT_external
	.dwattr $C$DW$335, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$335, DW_AT_decl_line(0x137)
	.dwattr $C$DW$335, DW_AT_decl_column(0x10)
	.global	WAVE_IresV1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_IresV1,SYM_SIZE(4)
WAVE_IresV1:
	.word	000000000h		; WAVE_IresV1 @ 0

$C$DW$336	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresV1")
	.dwattr $C$DW$336, DW_AT_TI_symbol_name("WAVE_IresV1")
	.dwattr $C$DW$336, DW_AT_location[DW_OP_addr WAVE_IresV1]
	.dwattr $C$DW$336, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$336, DW_AT_external
	.dwattr $C$DW$336, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$336, DW_AT_decl_line(0x138)
	.dwattr $C$DW$336, DW_AT_decl_column(0x10)
	.global	WAVE_IresV2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_IresV2,SYM_SIZE(4)
WAVE_IresV2:
	.word	000000000h		; WAVE_IresV2 @ 0

$C$DW$337	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresV2")
	.dwattr $C$DW$337, DW_AT_TI_symbol_name("WAVE_IresV2")
	.dwattr $C$DW$337, DW_AT_location[DW_OP_addr WAVE_IresV2]
	.dwattr $C$DW$337, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$337, DW_AT_external
	.dwattr $C$DW$337, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$337, DW_AT_decl_line(0x139)
	.dwattr $C$DW$337, DW_AT_decl_column(0x10)
	.global	WAVE_IresV3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_IresV3,SYM_SIZE(4)
WAVE_IresV3:
	.word	000000000h		; WAVE_IresV3 @ 0

$C$DW$338	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresV3")
	.dwattr $C$DW$338, DW_AT_TI_symbol_name("WAVE_IresV3")
	.dwattr $C$DW$338, DW_AT_location[DW_OP_addr WAVE_IresV3]
	.dwattr $C$DW$338, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$338, DW_AT_external
	.dwattr $C$DW$338, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$338, DW_AT_decl_line(0x13a)
	.dwattr $C$DW$338, DW_AT_decl_column(0x10)
	.global	WAVE_IresW1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_IresW1,SYM_SIZE(4)
WAVE_IresW1:
	.word	000000000h		; WAVE_IresW1 @ 0

$C$DW$339	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresW1")
	.dwattr $C$DW$339, DW_AT_TI_symbol_name("WAVE_IresW1")
	.dwattr $C$DW$339, DW_AT_location[DW_OP_addr WAVE_IresW1]
	.dwattr $C$DW$339, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$339, DW_AT_external
	.dwattr $C$DW$339, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$339, DW_AT_decl_line(0x13b)
	.dwattr $C$DW$339, DW_AT_decl_column(0x10)
	.global	WAVE_IresW2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_IresW2,SYM_SIZE(4)
WAVE_IresW2:
	.word	000000000h		; WAVE_IresW2 @ 0

$C$DW$340	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresW2")
	.dwattr $C$DW$340, DW_AT_TI_symbol_name("WAVE_IresW2")
	.dwattr $C$DW$340, DW_AT_location[DW_OP_addr WAVE_IresW2]
	.dwattr $C$DW$340, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$340, DW_AT_external
	.dwattr $C$DW$340, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$340, DW_AT_decl_line(0x13c)
	.dwattr $C$DW$340, DW_AT_decl_column(0x10)
	.global	WAVE_IresW3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_IresW3,SYM_SIZE(4)
WAVE_IresW3:
	.word	000000000h		; WAVE_IresW3 @ 0

$C$DW$341	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresW3")
	.dwattr $C$DW$341, DW_AT_TI_symbol_name("WAVE_IresW3")
	.dwattr $C$DW$341, DW_AT_location[DW_OP_addr WAVE_IresW3]
	.dwattr $C$DW$341, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$341, DW_AT_external
	.dwattr $C$DW$341, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$341, DW_AT_decl_line(0x13d)
	.dwattr $C$DW$341, DW_AT_decl_column(0x10)
	.global	WAVE_IresD1
	.bss	WAVE_IresD1,4,4
$C$DW$342	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresD1")
	.dwattr $C$DW$342, DW_AT_TI_symbol_name("WAVE_IresD1")
	.dwattr $C$DW$342, DW_AT_location[DW_OP_addr WAVE_IresD1]
	.dwattr $C$DW$342, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$342, DW_AT_external
	.dwattr $C$DW$342, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$342, DW_AT_decl_line(0x140)
	.dwattr $C$DW$342, DW_AT_decl_column(0x10)
	.global	WAVE_IresD2
	.bss	WAVE_IresD2,4,4
$C$DW$343	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresD2")
	.dwattr $C$DW$343, DW_AT_TI_symbol_name("WAVE_IresD2")
	.dwattr $C$DW$343, DW_AT_location[DW_OP_addr WAVE_IresD2]
	.dwattr $C$DW$343, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$343, DW_AT_external
	.dwattr $C$DW$343, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$343, DW_AT_decl_line(0x141)
	.dwattr $C$DW$343, DW_AT_decl_column(0x10)
	.global	WAVE_IresD3
	.bss	WAVE_IresD3,4,4
$C$DW$344	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresD3")
	.dwattr $C$DW$344, DW_AT_TI_symbol_name("WAVE_IresD3")
	.dwattr $C$DW$344, DW_AT_location[DW_OP_addr WAVE_IresD3]
	.dwattr $C$DW$344, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$344, DW_AT_external
	.dwattr $C$DW$344, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$344, DW_AT_decl_line(0x142)
	.dwattr $C$DW$344, DW_AT_decl_column(0x10)
	.global	WAVE_IresQ1
	.bss	WAVE_IresQ1,4,4
$C$DW$345	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresQ1")
	.dwattr $C$DW$345, DW_AT_TI_symbol_name("WAVE_IresQ1")
	.dwattr $C$DW$345, DW_AT_location[DW_OP_addr WAVE_IresQ1]
	.dwattr $C$DW$345, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$345, DW_AT_external
	.dwattr $C$DW$345, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$345, DW_AT_decl_line(0x143)
	.dwattr $C$DW$345, DW_AT_decl_column(0x10)
	.global	WAVE_IresQ2
	.bss	WAVE_IresQ2,4,4
$C$DW$346	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresQ2")
	.dwattr $C$DW$346, DW_AT_TI_symbol_name("WAVE_IresQ2")
	.dwattr $C$DW$346, DW_AT_location[DW_OP_addr WAVE_IresQ2]
	.dwattr $C$DW$346, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$346, DW_AT_external
	.dwattr $C$DW$346, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$346, DW_AT_decl_line(0x144)
	.dwattr $C$DW$346, DW_AT_decl_column(0x10)
	.global	WAVE_IresQ3
	.bss	WAVE_IresQ3,4,4
$C$DW$347	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IresQ3")
	.dwattr $C$DW$347, DW_AT_TI_symbol_name("WAVE_IresQ3")
	.dwattr $C$DW$347, DW_AT_location[DW_OP_addr WAVE_IresQ3]
	.dwattr $C$DW$347, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$347, DW_AT_external
	.dwattr $C$DW$347, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$347, DW_AT_decl_line(0x145)
	.dwattr $C$DW$347, DW_AT_decl_column(0x10)
	.global	WAVE_Vdc1
	.bss	WAVE_Vdc1,4,4
$C$DW$348	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Vdc1")
	.dwattr $C$DW$348, DW_AT_TI_symbol_name("WAVE_Vdc1")
	.dwattr $C$DW$348, DW_AT_location[DW_OP_addr WAVE_Vdc1]
	.dwattr $C$DW$348, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$348, DW_AT_external
	.dwattr $C$DW$348, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$348, DW_AT_decl_line(0x148)
	.dwattr $C$DW$348, DW_AT_decl_column(0x10)
	.global	WAVE_Vdc2
	.bss	WAVE_Vdc2,4,4
$C$DW$349	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Vdc2")
	.dwattr $C$DW$349, DW_AT_TI_symbol_name("WAVE_Vdc2")
	.dwattr $C$DW$349, DW_AT_location[DW_OP_addr WAVE_Vdc2]
	.dwattr $C$DW$349, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$349, DW_AT_external
	.dwattr $C$DW$349, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$349, DW_AT_decl_line(0x149)
	.dwattr $C$DW$349, DW_AT_decl_column(0x10)
	.global	WAVE_Vdc3
	.bss	WAVE_Vdc3,4,4
$C$DW$350	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Vdc3")
	.dwattr $C$DW$350, DW_AT_TI_symbol_name("WAVE_Vdc3")
	.dwattr $C$DW$350, DW_AT_location[DW_OP_addr WAVE_Vdc3]
	.dwattr $C$DW$350, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$350, DW_AT_external
	.dwattr $C$DW$350, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$350, DW_AT_decl_line(0x14a)
	.dwattr $C$DW$350, DW_AT_decl_column(0x10)
	.global	WAVE_Idc1
	.bss	WAVE_Idc1,4,4
$C$DW$351	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Idc1")
	.dwattr $C$DW$351, DW_AT_TI_symbol_name("WAVE_Idc1")
	.dwattr $C$DW$351, DW_AT_location[DW_OP_addr WAVE_Idc1]
	.dwattr $C$DW$351, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$351, DW_AT_external
	.dwattr $C$DW$351, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$351, DW_AT_decl_line(0x14d)
	.dwattr $C$DW$351, DW_AT_decl_column(0x10)
	.global	WAVE_Idc2
	.bss	WAVE_Idc2,4,4
$C$DW$352	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Idc2")
	.dwattr $C$DW$352, DW_AT_TI_symbol_name("WAVE_Idc2")
	.dwattr $C$DW$352, DW_AT_location[DW_OP_addr WAVE_Idc2]
	.dwattr $C$DW$352, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$352, DW_AT_external
	.dwattr $C$DW$352, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$352, DW_AT_decl_line(0x14e)
	.dwattr $C$DW$352, DW_AT_decl_column(0x10)
	.global	WAVE_Idc3
	.bss	WAVE_Idc3,4,4
$C$DW$353	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Idc3")
	.dwattr $C$DW$353, DW_AT_TI_symbol_name("WAVE_Idc3")
	.dwattr $C$DW$353, DW_AT_location[DW_OP_addr WAVE_Idc3]
	.dwattr $C$DW$353, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$353, DW_AT_external
	.dwattr $C$DW$353, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$353, DW_AT_decl_line(0x14f)
	.dwattr $C$DW$353, DW_AT_decl_column(0x10)
	.global	WAVE_ENC_temp1
	.bss	WAVE_ENC_temp1,4,4
$C$DW$354	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ENC_temp1")
	.dwattr $C$DW$354, DW_AT_TI_symbol_name("WAVE_ENC_temp1")
	.dwattr $C$DW$354, DW_AT_location[DW_OP_addr WAVE_ENC_temp1]
	.dwattr $C$DW$354, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$354, DW_AT_external
	.dwattr $C$DW$354, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$354, DW_AT_decl_line(0x152)
	.dwattr $C$DW$354, DW_AT_decl_column(0x0e)
	.global	WAVE_ENC_temp2
	.bss	WAVE_ENC_temp2,4,4
$C$DW$355	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ENC_temp2")
	.dwattr $C$DW$355, DW_AT_TI_symbol_name("WAVE_ENC_temp2")
	.dwattr $C$DW$355, DW_AT_location[DW_OP_addr WAVE_ENC_temp2]
	.dwattr $C$DW$355, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$355, DW_AT_external
	.dwattr $C$DW$355, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$355, DW_AT_decl_line(0x153)
	.dwattr $C$DW$355, DW_AT_decl_column(0x0e)
	.global	WAVE_ENC_temp3
	.bss	WAVE_ENC_temp3,4,4
$C$DW$356	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ENC_temp3")
	.dwattr $C$DW$356, DW_AT_TI_symbol_name("WAVE_ENC_temp3")
	.dwattr $C$DW$356, DW_AT_location[DW_OP_addr WAVE_ENC_temp3]
	.dwattr $C$DW$356, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$356, DW_AT_external
	.dwattr $C$DW$356, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$356, DW_AT_decl_line(0x154)
	.dwattr $C$DW$356, DW_AT_decl_column(0x0e)
	.global	WAVE_ENC1
	.bss	WAVE_ENC1,4,4
$C$DW$357	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ENC1")
	.dwattr $C$DW$357, DW_AT_TI_symbol_name("WAVE_ENC1")
	.dwattr $C$DW$357, DW_AT_location[DW_OP_addr WAVE_ENC1]
	.dwattr $C$DW$357, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$357, DW_AT_external
	.dwattr $C$DW$357, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$357, DW_AT_decl_line(0x155)
	.dwattr $C$DW$357, DW_AT_decl_column(0x0e)
	.global	WAVE_ENC2
	.bss	WAVE_ENC2,4,4
$C$DW$358	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ENC2")
	.dwattr $C$DW$358, DW_AT_TI_symbol_name("WAVE_ENC2")
	.dwattr $C$DW$358, DW_AT_location[DW_OP_addr WAVE_ENC2]
	.dwattr $C$DW$358, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$358, DW_AT_external
	.dwattr $C$DW$358, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$358, DW_AT_decl_line(0x156)
	.dwattr $C$DW$358, DW_AT_decl_column(0x0e)
	.global	WAVE_ENC3
	.bss	WAVE_ENC3,4,4
$C$DW$359	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ENC3")
	.dwattr $C$DW$359, DW_AT_TI_symbol_name("WAVE_ENC3")
	.dwattr $C$DW$359, DW_AT_location[DW_OP_addr WAVE_ENC3]
	.dwattr $C$DW$359, DW_AT_type(*$C$DW$T$312)
	.dwattr $C$DW$359, DW_AT_external
	.dwattr $C$DW$359, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$359, DW_AT_decl_line(0x157)
	.dwattr $C$DW$359, DW_AT_decl_column(0x0e)
	.global	WAVE_theta_rm1
	.bss	WAVE_theta_rm1,4,4
$C$DW$360	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_rm1")
	.dwattr $C$DW$360, DW_AT_TI_symbol_name("WAVE_theta_rm1")
	.dwattr $C$DW$360, DW_AT_location[DW_OP_addr WAVE_theta_rm1]
	.dwattr $C$DW$360, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$360, DW_AT_external
	.dwattr $C$DW$360, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$360, DW_AT_decl_line(0x158)
	.dwattr $C$DW$360, DW_AT_decl_column(0x10)
	.global	WAVE_theta_rm2
	.bss	WAVE_theta_rm2,4,4
$C$DW$361	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_rm2")
	.dwattr $C$DW$361, DW_AT_TI_symbol_name("WAVE_theta_rm2")
	.dwattr $C$DW$361, DW_AT_location[DW_OP_addr WAVE_theta_rm2]
	.dwattr $C$DW$361, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$361, DW_AT_external
	.dwattr $C$DW$361, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$361, DW_AT_decl_line(0x159)
	.dwattr $C$DW$361, DW_AT_decl_column(0x10)
	.global	WAVE_theta_rm3
	.bss	WAVE_theta_rm3,4,4
$C$DW$362	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_rm3")
	.dwattr $C$DW$362, DW_AT_TI_symbol_name("WAVE_theta_rm3")
	.dwattr $C$DW$362, DW_AT_location[DW_OP_addr WAVE_theta_rm3]
	.dwattr $C$DW$362, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$362, DW_AT_external
	.dwattr $C$DW$362, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$362, DW_AT_decl_line(0x15a)
	.dwattr $C$DW$362, DW_AT_decl_column(0x10)
	.global	WAVE_theta_rm_ref1
	.bss	WAVE_theta_rm_ref1,4,4
$C$DW$363	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_rm_ref1")
	.dwattr $C$DW$363, DW_AT_TI_symbol_name("WAVE_theta_rm_ref1")
	.dwattr $C$DW$363, DW_AT_location[DW_OP_addr WAVE_theta_rm_ref1]
	.dwattr $C$DW$363, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$363, DW_AT_external
	.dwattr $C$DW$363, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$363, DW_AT_decl_line(0x15b)
	.dwattr $C$DW$363, DW_AT_decl_column(0x10)
	.global	WAVE_theta_rm_ref2
	.bss	WAVE_theta_rm_ref2,4,4
$C$DW$364	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_rm_ref2")
	.dwattr $C$DW$364, DW_AT_TI_symbol_name("WAVE_theta_rm_ref2")
	.dwattr $C$DW$364, DW_AT_location[DW_OP_addr WAVE_theta_rm_ref2]
	.dwattr $C$DW$364, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$364, DW_AT_external
	.dwattr $C$DW$364, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$364, DW_AT_decl_line(0x15c)
	.dwattr $C$DW$364, DW_AT_decl_column(0x10)
	.global	WAVE_theta_rm_ref3
	.bss	WAVE_theta_rm_ref3,4,4
$C$DW$365	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_rm_ref3")
	.dwattr $C$DW$365, DW_AT_TI_symbol_name("WAVE_theta_rm_ref3")
	.dwattr $C$DW$365, DW_AT_location[DW_OP_addr WAVE_theta_rm_ref3]
	.dwattr $C$DW$365, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$365, DW_AT_external
	.dwattr $C$DW$365, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$365, DW_AT_decl_line(0x15d)
	.dwattr $C$DW$365, DW_AT_decl_column(0x10)
	.global	WAVE_theta_rm_full1
	.bss	WAVE_theta_rm_full1,4,4
$C$DW$366	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_rm_full1")
	.dwattr $C$DW$366, DW_AT_TI_symbol_name("WAVE_theta_rm_full1")
	.dwattr $C$DW$366, DW_AT_location[DW_OP_addr WAVE_theta_rm_full1]
	.dwattr $C$DW$366, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$366, DW_AT_external
	.dwattr $C$DW$366, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$366, DW_AT_decl_line(0x15e)
	.dwattr $C$DW$366, DW_AT_decl_column(0x10)
	.global	WAVE_theta_rm_full2
	.bss	WAVE_theta_rm_full2,4,4
$C$DW$367	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_rm_full2")
	.dwattr $C$DW$367, DW_AT_TI_symbol_name("WAVE_theta_rm_full2")
	.dwattr $C$DW$367, DW_AT_location[DW_OP_addr WAVE_theta_rm_full2]
	.dwattr $C$DW$367, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$367, DW_AT_external
	.dwattr $C$DW$367, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$367, DW_AT_decl_line(0x15f)
	.dwattr $C$DW$367, DW_AT_decl_column(0x10)
	.global	WAVE_theta_rm_full3
	.bss	WAVE_theta_rm_full3,4,4
$C$DW$368	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_rm_full3")
	.dwattr $C$DW$368, DW_AT_TI_symbol_name("WAVE_theta_rm_full3")
	.dwattr $C$DW$368, DW_AT_location[DW_OP_addr WAVE_theta_rm_full3]
	.dwattr $C$DW$368, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$368, DW_AT_external
	.dwattr $C$DW$368, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$368, DW_AT_decl_line(0x160)
	.dwattr $C$DW$368, DW_AT_decl_column(0x10)
	.global	WAVE_theta_re1
	.bss	WAVE_theta_re1,4,4
$C$DW$369	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_re1")
	.dwattr $C$DW$369, DW_AT_TI_symbol_name("WAVE_theta_re1")
	.dwattr $C$DW$369, DW_AT_location[DW_OP_addr WAVE_theta_re1]
	.dwattr $C$DW$369, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$369, DW_AT_external
	.dwattr $C$DW$369, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$369, DW_AT_decl_line(0x161)
	.dwattr $C$DW$369, DW_AT_decl_column(0x10)
	.global	WAVE_theta_re2
	.bss	WAVE_theta_re2,4,4
$C$DW$370	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_re2")
	.dwattr $C$DW$370, DW_AT_TI_symbol_name("WAVE_theta_re2")
	.dwattr $C$DW$370, DW_AT_location[DW_OP_addr WAVE_theta_re2]
	.dwattr $C$DW$370, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$370, DW_AT_external
	.dwattr $C$DW$370, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$370, DW_AT_decl_line(0x162)
	.dwattr $C$DW$370, DW_AT_decl_column(0x10)
	.global	WAVE_theta_re3
	.bss	WAVE_theta_re3,4,4
$C$DW$371	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_theta_re3")
	.dwattr $C$DW$371, DW_AT_TI_symbol_name("WAVE_theta_re3")
	.dwattr $C$DW$371, DW_AT_location[DW_OP_addr WAVE_theta_re3]
	.dwattr $C$DW$371, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$371, DW_AT_external
	.dwattr $C$DW$371, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$371, DW_AT_decl_line(0x163)
	.dwattr $C$DW$371, DW_AT_decl_column(0x10)
	.global	WAVE_TRG_WM1
	.bss	WAVE_TRG_WM1,4,4
$C$DW$372	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TRG_WM1")
	.dwattr $C$DW$372, DW_AT_TI_symbol_name("WAVE_TRG_WM1")
	.dwattr $C$DW$372, DW_AT_location[DW_OP_addr WAVE_TRG_WM1]
	.dwattr $C$DW$372, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$372, DW_AT_external
	.dwattr $C$DW$372, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$372, DW_AT_decl_line(0x165)
	.dwattr $C$DW$372, DW_AT_decl_column(0x10)
	.global	WAVE_TRG_WM2
	.bss	WAVE_TRG_WM2,4,4
$C$DW$373	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TRG_WM2")
	.dwattr $C$DW$373, DW_AT_TI_symbol_name("WAVE_TRG_WM2")
	.dwattr $C$DW$373, DW_AT_location[DW_OP_addr WAVE_TRG_WM2]
	.dwattr $C$DW$373, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$373, DW_AT_external
	.dwattr $C$DW$373, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$373, DW_AT_decl_line(0x166)
	.dwattr $C$DW$373, DW_AT_decl_column(0x10)
	.global	WAVE_TRG_WM3
	.bss	WAVE_TRG_WM3,4,4
$C$DW$374	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_TRG_WM3")
	.dwattr $C$DW$374, DW_AT_TI_symbol_name("WAVE_TRG_WM3")
	.dwattr $C$DW$374, DW_AT_location[DW_OP_addr WAVE_TRG_WM3]
	.dwattr $C$DW$374, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$374, DW_AT_external
	.dwattr $C$DW$374, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$374, DW_AT_decl_line(0x167)
	.dwattr $C$DW$374, DW_AT_decl_column(0x10)
	.global	WAVE_wm1
	.bss	WAVE_wm1,4,4
$C$DW$375	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm1")
	.dwattr $C$DW$375, DW_AT_TI_symbol_name("WAVE_wm1")
	.dwattr $C$DW$375, DW_AT_location[DW_OP_addr WAVE_wm1]
	.dwattr $C$DW$375, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$375, DW_AT_external
	.dwattr $C$DW$375, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$375, DW_AT_decl_line(0x168)
	.dwattr $C$DW$375, DW_AT_decl_column(0x10)
	.global	WAVE_wm2
	.bss	WAVE_wm2,4,4
$C$DW$376	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm2")
	.dwattr $C$DW$376, DW_AT_TI_symbol_name("WAVE_wm2")
	.dwattr $C$DW$376, DW_AT_location[DW_OP_addr WAVE_wm2]
	.dwattr $C$DW$376, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$376, DW_AT_external
	.dwattr $C$DW$376, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$376, DW_AT_decl_line(0x169)
	.dwattr $C$DW$376, DW_AT_decl_column(0x10)
	.global	WAVE_wm3
	.bss	WAVE_wm3,4,4
$C$DW$377	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm3")
	.dwattr $C$DW$377, DW_AT_TI_symbol_name("WAVE_wm3")
	.dwattr $C$DW$377, DW_AT_location[DW_OP_addr WAVE_wm3]
	.dwattr $C$DW$377, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$377, DW_AT_external
	.dwattr $C$DW$377, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$377, DW_AT_decl_line(0x16a)
	.dwattr $C$DW$377, DW_AT_decl_column(0x10)
	.global	WAVE_wm_ref_org
	.bss	WAVE_wm_ref_org,4,4
$C$DW$378	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_ref_org")
	.dwattr $C$DW$378, DW_AT_TI_symbol_name("WAVE_wm_ref_org")
	.dwattr $C$DW$378, DW_AT_location[DW_OP_addr WAVE_wm_ref_org]
	.dwattr $C$DW$378, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$378, DW_AT_external
	.dwattr $C$DW$378, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$378, DW_AT_decl_line(0x16b)
	.dwattr $C$DW$378, DW_AT_decl_column(0x10)
	.global	WAVE_wm_ref1
	.bss	WAVE_wm_ref1,4,4
$C$DW$379	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_ref1")
	.dwattr $C$DW$379, DW_AT_TI_symbol_name("WAVE_wm_ref1")
	.dwattr $C$DW$379, DW_AT_location[DW_OP_addr WAVE_wm_ref1]
	.dwattr $C$DW$379, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$379, DW_AT_external
	.dwattr $C$DW$379, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$379, DW_AT_decl_line(0x16c)
	.dwattr $C$DW$379, DW_AT_decl_column(0x10)
	.global	WAVE_wm_ref2
	.bss	WAVE_wm_ref2,4,4
$C$DW$380	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_ref2")
	.dwattr $C$DW$380, DW_AT_TI_symbol_name("WAVE_wm_ref2")
	.dwattr $C$DW$380, DW_AT_location[DW_OP_addr WAVE_wm_ref2]
	.dwattr $C$DW$380, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$380, DW_AT_external
	.dwattr $C$DW$380, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$380, DW_AT_decl_line(0x16d)
	.dwattr $C$DW$380, DW_AT_decl_column(0x10)
	.global	WAVE_wm_ref3
	.bss	WAVE_wm_ref3,4,4
$C$DW$381	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_ref3")
	.dwattr $C$DW$381, DW_AT_TI_symbol_name("WAVE_wm_ref3")
	.dwattr $C$DW$381, DW_AT_location[DW_OP_addr WAVE_wm_ref3]
	.dwattr $C$DW$381, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$381, DW_AT_external
	.dwattr $C$DW$381, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$381, DW_AT_decl_line(0x16e)
	.dwattr $C$DW$381, DW_AT_decl_column(0x10)
	.global	WAVE_wm_cmd1
	.bss	WAVE_wm_cmd1,4,4
$C$DW$382	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_cmd1")
	.dwattr $C$DW$382, DW_AT_TI_symbol_name("WAVE_wm_cmd1")
	.dwattr $C$DW$382, DW_AT_location[DW_OP_addr WAVE_wm_cmd1]
	.dwattr $C$DW$382, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$382, DW_AT_external
	.dwattr $C$DW$382, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$382, DW_AT_decl_line(0x16f)
	.dwattr $C$DW$382, DW_AT_decl_column(0x10)
	.global	WAVE_wm_cmd2
	.bss	WAVE_wm_cmd2,4,4
$C$DW$383	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_cmd2")
	.dwattr $C$DW$383, DW_AT_TI_symbol_name("WAVE_wm_cmd2")
	.dwattr $C$DW$383, DW_AT_location[DW_OP_addr WAVE_wm_cmd2]
	.dwattr $C$DW$383, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$383, DW_AT_external
	.dwattr $C$DW$383, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$383, DW_AT_decl_line(0x170)
	.dwattr $C$DW$383, DW_AT_decl_column(0x10)
	.global	WAVE_wm_cmd3
	.bss	WAVE_wm_cmd3,4,4
$C$DW$384	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_cmd3")
	.dwattr $C$DW$384, DW_AT_TI_symbol_name("WAVE_wm_cmd3")
	.dwattr $C$DW$384, DW_AT_location[DW_OP_addr WAVE_wm_cmd3]
	.dwattr $C$DW$384, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$384, DW_AT_external
	.dwattr $C$DW$384, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$384, DW_AT_decl_line(0x171)
	.dwattr $C$DW$384, DW_AT_decl_column(0x10)
	.global	WAVE_qm1
	.bss	WAVE_qm1,4,4
$C$DW$385	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_qm1")
	.dwattr $C$DW$385, DW_AT_TI_symbol_name("WAVE_qm1")
	.dwattr $C$DW$385, DW_AT_location[DW_OP_addr WAVE_qm1]
	.dwattr $C$DW$385, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$385, DW_AT_external
	.dwattr $C$DW$385, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$385, DW_AT_decl_line(0x172)
	.dwattr $C$DW$385, DW_AT_decl_column(0x10)
	.global	WAVE_qm2
	.bss	WAVE_qm2,4,4
$C$DW$386	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_qm2")
	.dwattr $C$DW$386, DW_AT_TI_symbol_name("WAVE_qm2")
	.dwattr $C$DW$386, DW_AT_location[DW_OP_addr WAVE_qm2]
	.dwattr $C$DW$386, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$386, DW_AT_external
	.dwattr $C$DW$386, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$386, DW_AT_decl_line(0x173)
	.dwattr $C$DW$386, DW_AT_decl_column(0x10)
	.global	WAVE_qm3
	.bss	WAVE_qm3,4,4
$C$DW$387	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_qm3")
	.dwattr $C$DW$387, DW_AT_TI_symbol_name("WAVE_qm3")
	.dwattr $C$DW$387, DW_AT_location[DW_OP_addr WAVE_qm3]
	.dwattr $C$DW$387, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$387, DW_AT_external
	.dwattr $C$DW$387, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$387, DW_AT_decl_line(0x174)
	.dwattr $C$DW$387, DW_AT_decl_column(0x10)
	.global	WAVE_qm_ref1
	.bss	WAVE_qm_ref1,4,4
$C$DW$388	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_qm_ref1")
	.dwattr $C$DW$388, DW_AT_TI_symbol_name("WAVE_qm_ref1")
	.dwattr $C$DW$388, DW_AT_location[DW_OP_addr WAVE_qm_ref1]
	.dwattr $C$DW$388, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$388, DW_AT_external
	.dwattr $C$DW$388, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$388, DW_AT_decl_line(0x175)
	.dwattr $C$DW$388, DW_AT_decl_column(0x10)
	.global	WAVE_qm_ref2
	.bss	WAVE_qm_ref2,4,4
$C$DW$389	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_qm_ref2")
	.dwattr $C$DW$389, DW_AT_TI_symbol_name("WAVE_qm_ref2")
	.dwattr $C$DW$389, DW_AT_location[DW_OP_addr WAVE_qm_ref2]
	.dwattr $C$DW$389, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$389, DW_AT_external
	.dwattr $C$DW$389, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$389, DW_AT_decl_line(0x176)
	.dwattr $C$DW$389, DW_AT_decl_column(0x10)
	.global	WAVE_qm_ref3
	.bss	WAVE_qm_ref3,4,4
$C$DW$390	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_qm_ref3")
	.dwattr $C$DW$390, DW_AT_TI_symbol_name("WAVE_qm_ref3")
	.dwattr $C$DW$390, DW_AT_location[DW_OP_addr WAVE_qm_ref3]
	.dwattr $C$DW$390, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$390, DW_AT_external
	.dwattr $C$DW$390, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$390, DW_AT_decl_line(0x177)
	.dwattr $C$DW$390, DW_AT_decl_column(0x10)
	.global	WAVE_ql1
	.bss	WAVE_ql1,4,4
$C$DW$391	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ql1")
	.dwattr $C$DW$391, DW_AT_TI_symbol_name("WAVE_ql1")
	.dwattr $C$DW$391, DW_AT_location[DW_OP_addr WAVE_ql1]
	.dwattr $C$DW$391, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$391, DW_AT_external
	.dwattr $C$DW$391, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$391, DW_AT_decl_line(0x178)
	.dwattr $C$DW$391, DW_AT_decl_column(0x10)
	.global	WAVE_ql2
	.bss	WAVE_ql2,4,4
$C$DW$392	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ql2")
	.dwattr $C$DW$392, DW_AT_TI_symbol_name("WAVE_ql2")
	.dwattr $C$DW$392, DW_AT_location[DW_OP_addr WAVE_ql2]
	.dwattr $C$DW$392, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$392, DW_AT_external
	.dwattr $C$DW$392, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$392, DW_AT_decl_line(0x179)
	.dwattr $C$DW$392, DW_AT_decl_column(0x10)
	.global	WAVE_ql3
	.bss	WAVE_ql3,4,4
$C$DW$393	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ql3")
	.dwattr $C$DW$393, DW_AT_TI_symbol_name("WAVE_ql3")
	.dwattr $C$DW$393, DW_AT_location[DW_OP_addr WAVE_ql3]
	.dwattr $C$DW$393, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$393, DW_AT_external
	.dwattr $C$DW$393, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$393, DW_AT_decl_line(0x17a)
	.dwattr $C$DW$393, DW_AT_decl_column(0x10)
	.global	WAVE_Iq1
	.bss	WAVE_Iq1,4,4
$C$DW$394	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Iq1")
	.dwattr $C$DW$394, DW_AT_TI_symbol_name("WAVE_Iq1")
	.dwattr $C$DW$394, DW_AT_location[DW_OP_addr WAVE_Iq1]
	.dwattr $C$DW$394, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$394, DW_AT_external
	.dwattr $C$DW$394, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$394, DW_AT_decl_line(0x17b)
	.dwattr $C$DW$394, DW_AT_decl_column(0x10)
	.global	WAVE_Iq2
	.bss	WAVE_Iq2,4,4
$C$DW$395	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Iq2")
	.dwattr $C$DW$395, DW_AT_TI_symbol_name("WAVE_Iq2")
	.dwattr $C$DW$395, DW_AT_location[DW_OP_addr WAVE_Iq2]
	.dwattr $C$DW$395, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$395, DW_AT_external
	.dwattr $C$DW$395, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$395, DW_AT_decl_line(0x17c)
	.dwattr $C$DW$395, DW_AT_decl_column(0x10)
	.global	WAVE_Iq3
	.bss	WAVE_Iq3,4,4
$C$DW$396	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Iq3")
	.dwattr $C$DW$396, DW_AT_TI_symbol_name("WAVE_Iq3")
	.dwattr $C$DW$396, DW_AT_location[DW_OP_addr WAVE_Iq3]
	.dwattr $C$DW$396, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$396, DW_AT_external
	.dwattr $C$DW$396, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$396, DW_AT_decl_line(0x17d)
	.dwattr $C$DW$396, DW_AT_decl_column(0x10)
	.global	WAVE_Isfb1
	.bss	WAVE_Isfb1,4,4
$C$DW$397	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Isfb1")
	.dwattr $C$DW$397, DW_AT_TI_symbol_name("WAVE_Isfb1")
	.dwattr $C$DW$397, DW_AT_location[DW_OP_addr WAVE_Isfb1]
	.dwattr $C$DW$397, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$397, DW_AT_external
	.dwattr $C$DW$397, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$397, DW_AT_decl_line(0x17e)
	.dwattr $C$DW$397, DW_AT_decl_column(0x10)
	.global	WAVE_Isfb2
	.bss	WAVE_Isfb2,4,4
$C$DW$398	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Isfb2")
	.dwattr $C$DW$398, DW_AT_TI_symbol_name("WAVE_Isfb2")
	.dwattr $C$DW$398, DW_AT_location[DW_OP_addr WAVE_Isfb2]
	.dwattr $C$DW$398, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$398, DW_AT_external
	.dwattr $C$DW$398, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$398, DW_AT_decl_line(0x17f)
	.dwattr $C$DW$398, DW_AT_decl_column(0x10)
	.global	WAVE_Isfb3
	.bss	WAVE_Isfb3,4,4
$C$DW$399	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Isfb3")
	.dwattr $C$DW$399, DW_AT_TI_symbol_name("WAVE_Isfb3")
	.dwattr $C$DW$399, DW_AT_location[DW_OP_addr WAVE_Isfb3]
	.dwattr $C$DW$399, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$399, DW_AT_external
	.dwattr $C$DW$399, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$399, DW_AT_decl_line(0x180)
	.dwattr $C$DW$399, DW_AT_decl_column(0x10)
	.global	WAVE_jark1
	.bss	WAVE_jark1,4,4
$C$DW$400	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_jark1")
	.dwattr $C$DW$400, DW_AT_TI_symbol_name("WAVE_jark1")
	.dwattr $C$DW$400, DW_AT_location[DW_OP_addr WAVE_jark1]
	.dwattr $C$DW$400, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$400, DW_AT_external
	.dwattr $C$DW$400, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$400, DW_AT_decl_line(0x182)
	.dwattr $C$DW$400, DW_AT_decl_column(0x10)
	.global	WAVE_jark2
	.bss	WAVE_jark2,4,4
$C$DW$401	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_jark2")
	.dwattr $C$DW$401, DW_AT_TI_symbol_name("WAVE_jark2")
	.dwattr $C$DW$401, DW_AT_location[DW_OP_addr WAVE_jark2]
	.dwattr $C$DW$401, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$401, DW_AT_external
	.dwattr $C$DW$401, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$401, DW_AT_decl_line(0x183)
	.dwattr $C$DW$401, DW_AT_decl_column(0x10)
	.global	WAVE_jark3
	.bss	WAVE_jark3,4,4
$C$DW$402	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_jark3")
	.dwattr $C$DW$402, DW_AT_TI_symbol_name("WAVE_jark3")
	.dwattr $C$DW$402, DW_AT_location[DW_OP_addr WAVE_jark3]
	.dwattr $C$DW$402, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$402, DW_AT_external
	.dwattr $C$DW$402, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$402, DW_AT_decl_line(0x184)
	.dwattr $C$DW$402, DW_AT_decl_column(0x10)
	.global	WAVE_am_TriAccCmd1
	.bss	WAVE_am_TriAccCmd1,4,4
$C$DW$403	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_am_TriAccCmd1")
	.dwattr $C$DW$403, DW_AT_TI_symbol_name("WAVE_am_TriAccCmd1")
	.dwattr $C$DW$403, DW_AT_location[DW_OP_addr WAVE_am_TriAccCmd1]
	.dwattr $C$DW$403, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$403, DW_AT_external
	.dwattr $C$DW$403, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$403, DW_AT_decl_line(0x185)
	.dwattr $C$DW$403, DW_AT_decl_column(0x10)
	.global	WAVE_am_TriAccCmd2
	.bss	WAVE_am_TriAccCmd2,4,4
$C$DW$404	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_am_TriAccCmd2")
	.dwattr $C$DW$404, DW_AT_TI_symbol_name("WAVE_am_TriAccCmd2")
	.dwattr $C$DW$404, DW_AT_location[DW_OP_addr WAVE_am_TriAccCmd2]
	.dwattr $C$DW$404, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$404, DW_AT_external
	.dwattr $C$DW$404, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$404, DW_AT_decl_line(0x186)
	.dwattr $C$DW$404, DW_AT_decl_column(0x10)
	.global	WAVE_am_TriAccCmd3
	.bss	WAVE_am_TriAccCmd3,4,4
$C$DW$405	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_am_TriAccCmd3")
	.dwattr $C$DW$405, DW_AT_TI_symbol_name("WAVE_am_TriAccCmd3")
	.dwattr $C$DW$405, DW_AT_location[DW_OP_addr WAVE_am_TriAccCmd3]
	.dwattr $C$DW$405, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$405, DW_AT_external
	.dwattr $C$DW$405, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$405, DW_AT_decl_line(0x187)
	.dwattr $C$DW$405, DW_AT_decl_column(0x10)
	.global	WAVE_wm_TriAccCmd1
	.bss	WAVE_wm_TriAccCmd1,4,4
$C$DW$406	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_TriAccCmd1")
	.dwattr $C$DW$406, DW_AT_TI_symbol_name("WAVE_wm_TriAccCmd1")
	.dwattr $C$DW$406, DW_AT_location[DW_OP_addr WAVE_wm_TriAccCmd1]
	.dwattr $C$DW$406, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$406, DW_AT_external
	.dwattr $C$DW$406, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$406, DW_AT_decl_line(0x188)
	.dwattr $C$DW$406, DW_AT_decl_column(0x10)
	.global	WAVE_wm_TriAccCmd2
	.bss	WAVE_wm_TriAccCmd2,4,4
$C$DW$407	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_TriAccCmd2")
	.dwattr $C$DW$407, DW_AT_TI_symbol_name("WAVE_wm_TriAccCmd2")
	.dwattr $C$DW$407, DW_AT_location[DW_OP_addr WAVE_wm_TriAccCmd2]
	.dwattr $C$DW$407, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$407, DW_AT_external
	.dwattr $C$DW$407, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$407, DW_AT_decl_line(0x189)
	.dwattr $C$DW$407, DW_AT_decl_column(0x10)
	.global	WAVE_wm_TriAccCmd3
	.bss	WAVE_wm_TriAccCmd3,4,4
$C$DW$408	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_wm_TriAccCmd3")
	.dwattr $C$DW$408, DW_AT_TI_symbol_name("WAVE_wm_TriAccCmd3")
	.dwattr $C$DW$408, DW_AT_location[DW_OP_addr WAVE_wm_TriAccCmd3]
	.dwattr $C$DW$408, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$408, DW_AT_external
	.dwattr $C$DW$408, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$408, DW_AT_decl_line(0x18a)
	.dwattr $C$DW$408, DW_AT_decl_column(0x10)
	.global	WAVE_qm_TriAccCmd1
	.bss	WAVE_qm_TriAccCmd1,4,4
$C$DW$409	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_qm_TriAccCmd1")
	.dwattr $C$DW$409, DW_AT_TI_symbol_name("WAVE_qm_TriAccCmd1")
	.dwattr $C$DW$409, DW_AT_location[DW_OP_addr WAVE_qm_TriAccCmd1]
	.dwattr $C$DW$409, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$409, DW_AT_external
	.dwattr $C$DW$409, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$409, DW_AT_decl_line(0x18b)
	.dwattr $C$DW$409, DW_AT_decl_column(0x10)
	.global	WAVE_qm_TriAccCmd2
	.bss	WAVE_qm_TriAccCmd2,4,4
$C$DW$410	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_qm_TriAccCmd2")
	.dwattr $C$DW$410, DW_AT_TI_symbol_name("WAVE_qm_TriAccCmd2")
	.dwattr $C$DW$410, DW_AT_location[DW_OP_addr WAVE_qm_TriAccCmd2]
	.dwattr $C$DW$410, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$410, DW_AT_external
	.dwattr $C$DW$410, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$410, DW_AT_decl_line(0x18c)
	.dwattr $C$DW$410, DW_AT_decl_column(0x10)
	.global	WAVE_qm_TriAccCmd3
	.bss	WAVE_qm_TriAccCmd3,4,4
$C$DW$411	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_qm_TriAccCmd3")
	.dwattr $C$DW$411, DW_AT_TI_symbol_name("WAVE_qm_TriAccCmd3")
	.dwattr $C$DW$411, DW_AT_location[DW_OP_addr WAVE_qm_TriAccCmd3]
	.dwattr $C$DW$411, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$411, DW_AT_external
	.dwattr $C$DW$411, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$411, DW_AT_decl_line(0x18d)
	.dwattr $C$DW$411, DW_AT_decl_column(0x10)
	.global	WAVE_ACC_LW8079
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_ACC_LW8079,SYM_SIZE(4)
WAVE_ACC_LW8079:
	.word	000000000h		; WAVE_ACC_LW8079 @ 0

$C$DW$412	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ACC_LW8079")
	.dwattr $C$DW$412, DW_AT_TI_symbol_name("WAVE_ACC_LW8079")
	.dwattr $C$DW$412, DW_AT_location[DW_OP_addr WAVE_ACC_LW8079]
	.dwattr $C$DW$412, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$412, DW_AT_external
	.dwattr $C$DW$412, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$412, DW_AT_decl_line(0x190)
	.dwattr $C$DW$412, DW_AT_decl_column(0x10)
	.global	WAVE_ACC_LW8174
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_ACC_LW8174,SYM_SIZE(4)
WAVE_ACC_LW8174:
	.word	000000000h		; WAVE_ACC_LW8174 @ 0

$C$DW$413	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ACC_LW8174")
	.dwattr $C$DW$413, DW_AT_TI_symbol_name("WAVE_ACC_LW8174")
	.dwattr $C$DW$413, DW_AT_location[DW_OP_addr WAVE_ACC_LW8174]
	.dwattr $C$DW$413, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$413, DW_AT_external
	.dwattr $C$DW$413, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$413, DW_AT_decl_line(0x191)
	.dwattr $C$DW$413, DW_AT_decl_column(0x10)
	.global	WAVE_ACC_LW8174_axis
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_ACC_LW8174_axis,SYM_SIZE(4)
WAVE_ACC_LW8174_axis:
	.word	000000000h		; WAVE_ACC_LW8174_axis @ 0

$C$DW$414	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ACC_LW8174_axis")
	.dwattr $C$DW$414, DW_AT_TI_symbol_name("WAVE_ACC_LW8174_axis")
	.dwattr $C$DW$414, DW_AT_location[DW_OP_addr WAVE_ACC_LW8174_axis]
	.dwattr $C$DW$414, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$414, DW_AT_external
	.dwattr $C$DW$414, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$414, DW_AT_decl_line(0x192)
	.dwattr $C$DW$414, DW_AT_decl_column(0x10)
	.global	WAVE_Fz
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_Fz,SYM_SIZE(4)
WAVE_Fz:
	.word	000000000h		; WAVE_Fz @ 0

$C$DW$415	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Fz")
	.dwattr $C$DW$415, DW_AT_TI_symbol_name("WAVE_Fz")
	.dwattr $C$DW$415, DW_AT_location[DW_OP_addr WAVE_Fz]
	.dwattr $C$DW$415, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$415, DW_AT_external
	.dwattr $C$DW$415, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$415, DW_AT_decl_line(0x193)
	.dwattr $C$DW$415, DW_AT_decl_column(0x10)
	.global	WAVE_WSX
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_WSX,SYM_SIZE(4)
WAVE_WSX:
	.word	000000000h		; WAVE_WSX @ 0

$C$DW$416	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_WSX")
	.dwattr $C$DW$416, DW_AT_TI_symbol_name("WAVE_WSX")
	.dwattr $C$DW$416, DW_AT_location[DW_OP_addr WAVE_WSX]
	.dwattr $C$DW$416, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$416, DW_AT_external
	.dwattr $C$DW$416, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$416, DW_AT_decl_line(0x194)
	.dwattr $C$DW$416, DW_AT_decl_column(0x10)
	.global	WAVE_WSY
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_WSY,SYM_SIZE(4)
WAVE_WSY:
	.word	000000000h		; WAVE_WSY @ 0

$C$DW$417	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_WSY")
	.dwattr $C$DW$417, DW_AT_TI_symbol_name("WAVE_WSY")
	.dwattr $C$DW$417, DW_AT_location[DW_OP_addr WAVE_WSY]
	.dwattr $C$DW$417, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$417, DW_AT_external
	.dwattr $C$DW$417, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$417, DW_AT_decl_line(0x195)
	.dwattr $C$DW$417, DW_AT_decl_column(0x10)
	.global	WAVE_WSZ
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_WSZ,SYM_SIZE(4)
WAVE_WSZ:
	.word	000000000h		; WAVE_WSZ @ 0

$C$DW$418	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_WSZ")
	.dwattr $C$DW$418, DW_AT_TI_symbol_name("WAVE_WSZ")
	.dwattr $C$DW$418, DW_AT_location[DW_OP_addr WAVE_WSZ]
	.dwattr $C$DW$418, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$418, DW_AT_external
	.dwattr $C$DW$418, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$418, DW_AT_decl_line(0x196)
	.dwattr $C$DW$418, DW_AT_decl_column(0x10)
	.global	WAVE_VrefU1
	.bss	WAVE_VrefU1,4,4
$C$DW$419	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefU1")
	.dwattr $C$DW$419, DW_AT_TI_symbol_name("WAVE_VrefU1")
	.dwattr $C$DW$419, DW_AT_location[DW_OP_addr WAVE_VrefU1]
	.dwattr $C$DW$419, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$419, DW_AT_external
	.dwattr $C$DW$419, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$419, DW_AT_decl_line(0x19c)
	.dwattr $C$DW$419, DW_AT_decl_column(0x10)
	.global	WAVE_VrefV1
	.bss	WAVE_VrefV1,4,4
$C$DW$420	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefV1")
	.dwattr $C$DW$420, DW_AT_TI_symbol_name("WAVE_VrefV1")
	.dwattr $C$DW$420, DW_AT_location[DW_OP_addr WAVE_VrefV1]
	.dwattr $C$DW$420, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$420, DW_AT_external
	.dwattr $C$DW$420, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$420, DW_AT_decl_line(0x19d)
	.dwattr $C$DW$420, DW_AT_decl_column(0x10)
	.global	WAVE_VrefW1
	.bss	WAVE_VrefW1,4,4
$C$DW$421	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefW1")
	.dwattr $C$DW$421, DW_AT_TI_symbol_name("WAVE_VrefW1")
	.dwattr $C$DW$421, DW_AT_location[DW_OP_addr WAVE_VrefW1]
	.dwattr $C$DW$421, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$421, DW_AT_external
	.dwattr $C$DW$421, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$421, DW_AT_decl_line(0x19e)
	.dwattr $C$DW$421, DW_AT_decl_column(0x10)
	.global	WAVE_VrefU2
	.bss	WAVE_VrefU2,4,4
$C$DW$422	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefU2")
	.dwattr $C$DW$422, DW_AT_TI_symbol_name("WAVE_VrefU2")
	.dwattr $C$DW$422, DW_AT_location[DW_OP_addr WAVE_VrefU2]
	.dwattr $C$DW$422, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$422, DW_AT_external
	.dwattr $C$DW$422, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$422, DW_AT_decl_line(0x19f)
	.dwattr $C$DW$422, DW_AT_decl_column(0x10)
	.global	WAVE_VrefV2
	.bss	WAVE_VrefV2,4,4
$C$DW$423	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefV2")
	.dwattr $C$DW$423, DW_AT_TI_symbol_name("WAVE_VrefV2")
	.dwattr $C$DW$423, DW_AT_location[DW_OP_addr WAVE_VrefV2]
	.dwattr $C$DW$423, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$423, DW_AT_external
	.dwattr $C$DW$423, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$423, DW_AT_decl_line(0x1a0)
	.dwattr $C$DW$423, DW_AT_decl_column(0x10)
	.global	WAVE_VrefW2
	.bss	WAVE_VrefW2,4,4
$C$DW$424	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefW2")
	.dwattr $C$DW$424, DW_AT_TI_symbol_name("WAVE_VrefW2")
	.dwattr $C$DW$424, DW_AT_location[DW_OP_addr WAVE_VrefW2]
	.dwattr $C$DW$424, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$424, DW_AT_external
	.dwattr $C$DW$424, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$424, DW_AT_decl_line(0x1a1)
	.dwattr $C$DW$424, DW_AT_decl_column(0x10)
	.global	WAVE_VrefU3
	.bss	WAVE_VrefU3,4,4
$C$DW$425	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefU3")
	.dwattr $C$DW$425, DW_AT_TI_symbol_name("WAVE_VrefU3")
	.dwattr $C$DW$425, DW_AT_location[DW_OP_addr WAVE_VrefU3]
	.dwattr $C$DW$425, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$425, DW_AT_external
	.dwattr $C$DW$425, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$425, DW_AT_decl_line(0x1a2)
	.dwattr $C$DW$425, DW_AT_decl_column(0x10)
	.global	WAVE_VrefV3
	.bss	WAVE_VrefV3,4,4
$C$DW$426	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefV3")
	.dwattr $C$DW$426, DW_AT_TI_symbol_name("WAVE_VrefV3")
	.dwattr $C$DW$426, DW_AT_location[DW_OP_addr WAVE_VrefV3]
	.dwattr $C$DW$426, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$426, DW_AT_external
	.dwattr $C$DW$426, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$426, DW_AT_decl_line(0x1a3)
	.dwattr $C$DW$426, DW_AT_decl_column(0x10)
	.global	WAVE_VrefW3
	.bss	WAVE_VrefW3,4,4
$C$DW$427	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefW3")
	.dwattr $C$DW$427, DW_AT_TI_symbol_name("WAVE_VrefW3")
	.dwattr $C$DW$427, DW_AT_location[DW_OP_addr WAVE_VrefW3]
	.dwattr $C$DW$427, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$427, DW_AT_external
	.dwattr $C$DW$427, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$427, DW_AT_decl_line(0x1a4)
	.dwattr $C$DW$427, DW_AT_decl_column(0x10)
	.global	WAVE_vu_ref_stand1
	.bss	WAVE_vu_ref_stand1,4,4
$C$DW$428	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vu_ref_stand1")
	.dwattr $C$DW$428, DW_AT_TI_symbol_name("WAVE_vu_ref_stand1")
	.dwattr $C$DW$428, DW_AT_location[DW_OP_addr WAVE_vu_ref_stand1]
	.dwattr $C$DW$428, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$428, DW_AT_external
	.dwattr $C$DW$428, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$428, DW_AT_decl_line(0x1a6)
	.dwattr $C$DW$428, DW_AT_decl_column(0x10)
	.global	WAVE_vv_ref_stand1
	.bss	WAVE_vv_ref_stand1,4,4
$C$DW$429	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vv_ref_stand1")
	.dwattr $C$DW$429, DW_AT_TI_symbol_name("WAVE_vv_ref_stand1")
	.dwattr $C$DW$429, DW_AT_location[DW_OP_addr WAVE_vv_ref_stand1]
	.dwattr $C$DW$429, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$429, DW_AT_external
	.dwattr $C$DW$429, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$429, DW_AT_decl_line(0x1a7)
	.dwattr $C$DW$429, DW_AT_decl_column(0x10)
	.global	WAVE_vw_ref_stand1
	.bss	WAVE_vw_ref_stand1,4,4
$C$DW$430	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vw_ref_stand1")
	.dwattr $C$DW$430, DW_AT_TI_symbol_name("WAVE_vw_ref_stand1")
	.dwattr $C$DW$430, DW_AT_location[DW_OP_addr WAVE_vw_ref_stand1]
	.dwattr $C$DW$430, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$430, DW_AT_external
	.dwattr $C$DW$430, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$430, DW_AT_decl_line(0x1a8)
	.dwattr $C$DW$430, DW_AT_decl_column(0x10)
	.global	WAVE_vu_ref_stand2
	.bss	WAVE_vu_ref_stand2,4,4
$C$DW$431	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vu_ref_stand2")
	.dwattr $C$DW$431, DW_AT_TI_symbol_name("WAVE_vu_ref_stand2")
	.dwattr $C$DW$431, DW_AT_location[DW_OP_addr WAVE_vu_ref_stand2]
	.dwattr $C$DW$431, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$431, DW_AT_external
	.dwattr $C$DW$431, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$431, DW_AT_decl_line(0x1a9)
	.dwattr $C$DW$431, DW_AT_decl_column(0x10)
	.global	WAVE_vv_ref_stand2
	.bss	WAVE_vv_ref_stand2,4,4
$C$DW$432	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vv_ref_stand2")
	.dwattr $C$DW$432, DW_AT_TI_symbol_name("WAVE_vv_ref_stand2")
	.dwattr $C$DW$432, DW_AT_location[DW_OP_addr WAVE_vv_ref_stand2]
	.dwattr $C$DW$432, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$432, DW_AT_external
	.dwattr $C$DW$432, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$432, DW_AT_decl_line(0x1aa)
	.dwattr $C$DW$432, DW_AT_decl_column(0x10)
	.global	WAVE_vw_ref_stand2
	.bss	WAVE_vw_ref_stand2,4,4
$C$DW$433	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vw_ref_stand2")
	.dwattr $C$DW$433, DW_AT_TI_symbol_name("WAVE_vw_ref_stand2")
	.dwattr $C$DW$433, DW_AT_location[DW_OP_addr WAVE_vw_ref_stand2]
	.dwattr $C$DW$433, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$433, DW_AT_external
	.dwattr $C$DW$433, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$433, DW_AT_decl_line(0x1ab)
	.dwattr $C$DW$433, DW_AT_decl_column(0x10)
	.global	WAVE_vu_ref_stand3
	.bss	WAVE_vu_ref_stand3,4,4
$C$DW$434	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vu_ref_stand3")
	.dwattr $C$DW$434, DW_AT_TI_symbol_name("WAVE_vu_ref_stand3")
	.dwattr $C$DW$434, DW_AT_location[DW_OP_addr WAVE_vu_ref_stand3]
	.dwattr $C$DW$434, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$434, DW_AT_external
	.dwattr $C$DW$434, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$434, DW_AT_decl_line(0x1ac)
	.dwattr $C$DW$434, DW_AT_decl_column(0x10)
	.global	WAVE_vv_ref_stand3
	.bss	WAVE_vv_ref_stand3,4,4
$C$DW$435	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vv_ref_stand3")
	.dwattr $C$DW$435, DW_AT_TI_symbol_name("WAVE_vv_ref_stand3")
	.dwattr $C$DW$435, DW_AT_location[DW_OP_addr WAVE_vv_ref_stand3]
	.dwattr $C$DW$435, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$435, DW_AT_external
	.dwattr $C$DW$435, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$435, DW_AT_decl_line(0x1ad)
	.dwattr $C$DW$435, DW_AT_decl_column(0x10)
	.global	WAVE_vw_ref_stand3
	.bss	WAVE_vw_ref_stand3,4,4
$C$DW$436	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vw_ref_stand3")
	.dwattr $C$DW$436, DW_AT_TI_symbol_name("WAVE_vw_ref_stand3")
	.dwattr $C$DW$436, DW_AT_location[DW_OP_addr WAVE_vw_ref_stand3]
	.dwattr $C$DW$436, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$436, DW_AT_external
	.dwattr $C$DW$436, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$436, DW_AT_decl_line(0x1ae)
	.dwattr $C$DW$436, DW_AT_decl_column(0x10)
	.global	WAVE_IrefD1
	.bss	WAVE_IrefD1,4,4
$C$DW$437	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IrefD1")
	.dwattr $C$DW$437, DW_AT_TI_symbol_name("WAVE_IrefD1")
	.dwattr $C$DW$437, DW_AT_location[DW_OP_addr WAVE_IrefD1]
	.dwattr $C$DW$437, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$437, DW_AT_external
	.dwattr $C$DW$437, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$437, DW_AT_decl_line(0x1b0)
	.dwattr $C$DW$437, DW_AT_decl_column(0x10)
	.global	WAVE_IrefD2
	.bss	WAVE_IrefD2,4,4
$C$DW$438	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IrefD2")
	.dwattr $C$DW$438, DW_AT_TI_symbol_name("WAVE_IrefD2")
	.dwattr $C$DW$438, DW_AT_location[DW_OP_addr WAVE_IrefD2]
	.dwattr $C$DW$438, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$438, DW_AT_external
	.dwattr $C$DW$438, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$438, DW_AT_decl_line(0x1b1)
	.dwattr $C$DW$438, DW_AT_decl_column(0x10)
	.global	WAVE_IrefD3
	.bss	WAVE_IrefD3,4,4
$C$DW$439	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IrefD3")
	.dwattr $C$DW$439, DW_AT_TI_symbol_name("WAVE_IrefD3")
	.dwattr $C$DW$439, DW_AT_location[DW_OP_addr WAVE_IrefD3]
	.dwattr $C$DW$439, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$439, DW_AT_external
	.dwattr $C$DW$439, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$439, DW_AT_decl_line(0x1b2)
	.dwattr $C$DW$439, DW_AT_decl_column(0x10)
	.global	WAVE_IrefQ1
	.bss	WAVE_IrefQ1,4,4
$C$DW$440	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IrefQ1")
	.dwattr $C$DW$440, DW_AT_TI_symbol_name("WAVE_IrefQ1")
	.dwattr $C$DW$440, DW_AT_location[DW_OP_addr WAVE_IrefQ1]
	.dwattr $C$DW$440, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$440, DW_AT_external
	.dwattr $C$DW$440, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$440, DW_AT_decl_line(0x1b3)
	.dwattr $C$DW$440, DW_AT_decl_column(0x10)
	.global	WAVE_IrefQ2
	.bss	WAVE_IrefQ2,4,4
$C$DW$441	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IrefQ2")
	.dwattr $C$DW$441, DW_AT_TI_symbol_name("WAVE_IrefQ2")
	.dwattr $C$DW$441, DW_AT_location[DW_OP_addr WAVE_IrefQ2]
	.dwattr $C$DW$441, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$441, DW_AT_external
	.dwattr $C$DW$441, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$441, DW_AT_decl_line(0x1b4)
	.dwattr $C$DW$441, DW_AT_decl_column(0x10)
	.global	WAVE_IrefQ3
	.bss	WAVE_IrefQ3,4,4
$C$DW$442	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_IrefQ3")
	.dwattr $C$DW$442, DW_AT_TI_symbol_name("WAVE_IrefQ3")
	.dwattr $C$DW$442, DW_AT_location[DW_OP_addr WAVE_IrefQ3]
	.dwattr $C$DW$442, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$442, DW_AT_external
	.dwattr $C$DW$442, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$442, DW_AT_decl_line(0x1b5)
	.dwattr $C$DW$442, DW_AT_decl_column(0x10)
	.global	WAVE_VrefD_dcpl1
	.bss	WAVE_VrefD_dcpl1,4,4
$C$DW$443	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefD_dcpl1")
	.dwattr $C$DW$443, DW_AT_TI_symbol_name("WAVE_VrefD_dcpl1")
	.dwattr $C$DW$443, DW_AT_location[DW_OP_addr WAVE_VrefD_dcpl1]
	.dwattr $C$DW$443, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$443, DW_AT_external
	.dwattr $C$DW$443, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$443, DW_AT_decl_line(0x1b7)
	.dwattr $C$DW$443, DW_AT_decl_column(0x10)
	.global	WAVE_VrefQ_dcpl1
	.bss	WAVE_VrefQ_dcpl1,4,4
$C$DW$444	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefQ_dcpl1")
	.dwattr $C$DW$444, DW_AT_TI_symbol_name("WAVE_VrefQ_dcpl1")
	.dwattr $C$DW$444, DW_AT_location[DW_OP_addr WAVE_VrefQ_dcpl1]
	.dwattr $C$DW$444, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$444, DW_AT_external
	.dwattr $C$DW$444, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$444, DW_AT_decl_line(0x1b8)
	.dwattr $C$DW$444, DW_AT_decl_column(0x10)
	.global	WAVE_VrefD_dcpl2
	.bss	WAVE_VrefD_dcpl2,4,4
$C$DW$445	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefD_dcpl2")
	.dwattr $C$DW$445, DW_AT_TI_symbol_name("WAVE_VrefD_dcpl2")
	.dwattr $C$DW$445, DW_AT_location[DW_OP_addr WAVE_VrefD_dcpl2]
	.dwattr $C$DW$445, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$445, DW_AT_external
	.dwattr $C$DW$445, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$445, DW_AT_decl_line(0x1b9)
	.dwattr $C$DW$445, DW_AT_decl_column(0x10)
	.global	WAVE_VrefQ_dcpl2
	.bss	WAVE_VrefQ_dcpl2,4,4
$C$DW$446	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefQ_dcpl2")
	.dwattr $C$DW$446, DW_AT_TI_symbol_name("WAVE_VrefQ_dcpl2")
	.dwattr $C$DW$446, DW_AT_location[DW_OP_addr WAVE_VrefQ_dcpl2]
	.dwattr $C$DW$446, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$446, DW_AT_external
	.dwattr $C$DW$446, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$446, DW_AT_decl_line(0x1ba)
	.dwattr $C$DW$446, DW_AT_decl_column(0x10)
	.global	WAVE_VrefD_dcpl3
	.bss	WAVE_VrefD_dcpl3,4,4
$C$DW$447	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefD_dcpl3")
	.dwattr $C$DW$447, DW_AT_TI_symbol_name("WAVE_VrefD_dcpl3")
	.dwattr $C$DW$447, DW_AT_location[DW_OP_addr WAVE_VrefD_dcpl3]
	.dwattr $C$DW$447, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$447, DW_AT_external
	.dwattr $C$DW$447, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$447, DW_AT_decl_line(0x1bb)
	.dwattr $C$DW$447, DW_AT_decl_column(0x10)
	.global	WAVE_VrefQ_dcpl3
	.bss	WAVE_VrefQ_dcpl3,4,4
$C$DW$448	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefQ_dcpl3")
	.dwattr $C$DW$448, DW_AT_TI_symbol_name("WAVE_VrefQ_dcpl3")
	.dwattr $C$DW$448, DW_AT_location[DW_OP_addr WAVE_VrefQ_dcpl3]
	.dwattr $C$DW$448, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$448, DW_AT_external
	.dwattr $C$DW$448, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$448, DW_AT_decl_line(0x1bc)
	.dwattr $C$DW$448, DW_AT_decl_column(0x10)
	.global	WAVE_VrefD1
	.bss	WAVE_VrefD1,4,4
$C$DW$449	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefD1")
	.dwattr $C$DW$449, DW_AT_TI_symbol_name("WAVE_VrefD1")
	.dwattr $C$DW$449, DW_AT_location[DW_OP_addr WAVE_VrefD1]
	.dwattr $C$DW$449, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$449, DW_AT_external
	.dwattr $C$DW$449, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$449, DW_AT_decl_line(0x1be)
	.dwattr $C$DW$449, DW_AT_decl_column(0x10)
	.global	WAVE_VrefQ1
	.bss	WAVE_VrefQ1,4,4
$C$DW$450	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefQ1")
	.dwattr $C$DW$450, DW_AT_TI_symbol_name("WAVE_VrefQ1")
	.dwattr $C$DW$450, DW_AT_location[DW_OP_addr WAVE_VrefQ1]
	.dwattr $C$DW$450, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$450, DW_AT_external
	.dwattr $C$DW$450, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$450, DW_AT_decl_line(0x1bf)
	.dwattr $C$DW$450, DW_AT_decl_column(0x10)
	.global	WAVE_VrefD2
	.bss	WAVE_VrefD2,4,4
$C$DW$451	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefD2")
	.dwattr $C$DW$451, DW_AT_TI_symbol_name("WAVE_VrefD2")
	.dwattr $C$DW$451, DW_AT_location[DW_OP_addr WAVE_VrefD2]
	.dwattr $C$DW$451, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$451, DW_AT_external
	.dwattr $C$DW$451, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$451, DW_AT_decl_line(0x1c0)
	.dwattr $C$DW$451, DW_AT_decl_column(0x10)
	.global	WAVE_VrefQ2
	.bss	WAVE_VrefQ2,4,4
$C$DW$452	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefQ2")
	.dwattr $C$DW$452, DW_AT_TI_symbol_name("WAVE_VrefQ2")
	.dwattr $C$DW$452, DW_AT_location[DW_OP_addr WAVE_VrefQ2]
	.dwattr $C$DW$452, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$452, DW_AT_external
	.dwattr $C$DW$452, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$452, DW_AT_decl_line(0x1c1)
	.dwattr $C$DW$452, DW_AT_decl_column(0x10)
	.global	WAVE_VrefD3
	.bss	WAVE_VrefD3,4,4
$C$DW$453	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefD3")
	.dwattr $C$DW$453, DW_AT_TI_symbol_name("WAVE_VrefD3")
	.dwattr $C$DW$453, DW_AT_location[DW_OP_addr WAVE_VrefD3]
	.dwattr $C$DW$453, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$453, DW_AT_external
	.dwattr $C$DW$453, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$453, DW_AT_decl_line(0x1c2)
	.dwattr $C$DW$453, DW_AT_decl_column(0x10)
	.global	WAVE_VrefQ3
	.bss	WAVE_VrefQ3,4,4
$C$DW$454	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VrefQ3")
	.dwattr $C$DW$454, DW_AT_TI_symbol_name("WAVE_VrefQ3")
	.dwattr $C$DW$454, DW_AT_location[DW_OP_addr WAVE_VrefQ3]
	.dwattr $C$DW$454, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$454, DW_AT_external
	.dwattr $C$DW$454, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$454, DW_AT_decl_line(0x1c3)
	.dwattr $C$DW$454, DW_AT_decl_column(0x10)
	.global	WAVE_vd_lim_dif1
	.bss	WAVE_vd_lim_dif1,4,4
$C$DW$455	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vd_lim_dif1")
	.dwattr $C$DW$455, DW_AT_TI_symbol_name("WAVE_vd_lim_dif1")
	.dwattr $C$DW$455, DW_AT_location[DW_OP_addr WAVE_vd_lim_dif1]
	.dwattr $C$DW$455, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$455, DW_AT_external
	.dwattr $C$DW$455, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$455, DW_AT_decl_line(0x1c5)
	.dwattr $C$DW$455, DW_AT_decl_column(0x10)
	.global	WAVE_vq_lim_dif1
	.bss	WAVE_vq_lim_dif1,4,4
$C$DW$456	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vq_lim_dif1")
	.dwattr $C$DW$456, DW_AT_TI_symbol_name("WAVE_vq_lim_dif1")
	.dwattr $C$DW$456, DW_AT_location[DW_OP_addr WAVE_vq_lim_dif1]
	.dwattr $C$DW$456, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$456, DW_AT_external
	.dwattr $C$DW$456, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$456, DW_AT_decl_line(0x1c6)
	.dwattr $C$DW$456, DW_AT_decl_column(0x10)
	.global	WAVE_vd_lim_dif2
	.bss	WAVE_vd_lim_dif2,4,4
$C$DW$457	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vd_lim_dif2")
	.dwattr $C$DW$457, DW_AT_TI_symbol_name("WAVE_vd_lim_dif2")
	.dwattr $C$DW$457, DW_AT_location[DW_OP_addr WAVE_vd_lim_dif2]
	.dwattr $C$DW$457, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$457, DW_AT_external
	.dwattr $C$DW$457, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$457, DW_AT_decl_line(0x1c7)
	.dwattr $C$DW$457, DW_AT_decl_column(0x10)
	.global	WAVE_vq_lim_dif2
	.bss	WAVE_vq_lim_dif2,4,4
$C$DW$458	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vq_lim_dif2")
	.dwattr $C$DW$458, DW_AT_TI_symbol_name("WAVE_vq_lim_dif2")
	.dwattr $C$DW$458, DW_AT_location[DW_OP_addr WAVE_vq_lim_dif2]
	.dwattr $C$DW$458, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$458, DW_AT_external
	.dwattr $C$DW$458, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$458, DW_AT_decl_line(0x1c8)
	.dwattr $C$DW$458, DW_AT_decl_column(0x10)
	.global	WAVE_vd_lim_dif3
	.bss	WAVE_vd_lim_dif3,4,4
$C$DW$459	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vd_lim_dif3")
	.dwattr $C$DW$459, DW_AT_TI_symbol_name("WAVE_vd_lim_dif3")
	.dwattr $C$DW$459, DW_AT_location[DW_OP_addr WAVE_vd_lim_dif3]
	.dwattr $C$DW$459, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$459, DW_AT_external
	.dwattr $C$DW$459, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$459, DW_AT_decl_line(0x1c9)
	.dwattr $C$DW$459, DW_AT_decl_column(0x10)
	.global	WAVE_vq_lim_dif3
	.bss	WAVE_vq_lim_dif3,4,4
$C$DW$460	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_vq_lim_dif3")
	.dwattr $C$DW$460, DW_AT_TI_symbol_name("WAVE_vq_lim_dif3")
	.dwattr $C$DW$460, DW_AT_location[DW_OP_addr WAVE_vq_lim_dif3]
	.dwattr $C$DW$460, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$460, DW_AT_external
	.dwattr $C$DW$460, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$460, DW_AT_decl_line(0x1ca)
	.dwattr $C$DW$460, DW_AT_decl_column(0x10)
	.global	WAVE_U_modulation
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_U_modulation,SYM_SIZE(4)
WAVE_U_modulation:
	.word	000000000h		; WAVE_U_modulation @ 0

$C$DW$461	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_U_modulation")
	.dwattr $C$DW$461, DW_AT_TI_symbol_name("WAVE_U_modulation")
	.dwattr $C$DW$461, DW_AT_location[DW_OP_addr WAVE_U_modulation]
	.dwattr $C$DW$461, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$461, DW_AT_external
	.dwattr $C$DW$461, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$461, DW_AT_decl_line(0x1cc)
	.dwattr $C$DW$461, DW_AT_decl_column(0x10)
	.global	WAVE_V_modulation
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_V_modulation,SYM_SIZE(4)
WAVE_V_modulation:
	.word	000000000h		; WAVE_V_modulation @ 0

$C$DW$462	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_V_modulation")
	.dwattr $C$DW$462, DW_AT_TI_symbol_name("WAVE_V_modulation")
	.dwattr $C$DW$462, DW_AT_location[DW_OP_addr WAVE_V_modulation]
	.dwattr $C$DW$462, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$462, DW_AT_external
	.dwattr $C$DW$462, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$462, DW_AT_decl_line(0x1cd)
	.dwattr $C$DW$462, DW_AT_decl_column(0x10)
	.global	WAVE_W_modulation
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_W_modulation,SYM_SIZE(4)
WAVE_W_modulation:
	.word	000000000h		; WAVE_W_modulation @ 0

$C$DW$463	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_W_modulation")
	.dwattr $C$DW$463, DW_AT_TI_symbol_name("WAVE_W_modulation")
	.dwattr $C$DW$463, DW_AT_location[DW_OP_addr WAVE_W_modulation]
	.dwattr $C$DW$463, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$463, DW_AT_external
	.dwattr $C$DW$463, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$463, DW_AT_decl_line(0x1ce)
	.dwattr $C$DW$463, DW_AT_decl_column(0x10)
	.global	WAVE_omega_rm1
	.bss	WAVE_omega_rm1,4,4
$C$DW$464	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_omega_rm1")
	.dwattr $C$DW$464, DW_AT_TI_symbol_name("WAVE_omega_rm1")
	.dwattr $C$DW$464, DW_AT_location[DW_OP_addr WAVE_omega_rm1]
	.dwattr $C$DW$464, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$464, DW_AT_external
	.dwattr $C$DW$464, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$464, DW_AT_decl_line(0x1d0)
	.dwattr $C$DW$464, DW_AT_decl_column(0x10)
	.global	WAVE_omega_rm2
	.bss	WAVE_omega_rm2,4,4
$C$DW$465	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_omega_rm2")
	.dwattr $C$DW$465, DW_AT_TI_symbol_name("WAVE_omega_rm2")
	.dwattr $C$DW$465, DW_AT_location[DW_OP_addr WAVE_omega_rm2]
	.dwattr $C$DW$465, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$465, DW_AT_external
	.dwattr $C$DW$465, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$465, DW_AT_decl_line(0x1d1)
	.dwattr $C$DW$465, DW_AT_decl_column(0x10)
	.global	WAVE_omega_rm3
	.bss	WAVE_omega_rm3,4,4
$C$DW$466	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_omega_rm3")
	.dwattr $C$DW$466, DW_AT_TI_symbol_name("WAVE_omega_rm3")
	.dwattr $C$DW$466, DW_AT_location[DW_OP_addr WAVE_omega_rm3]
	.dwattr $C$DW$466, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$466, DW_AT_external
	.dwattr $C$DW$466, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$466, DW_AT_decl_line(0x1d2)
	.dwattr $C$DW$466, DW_AT_decl_column(0x10)
	.global	WAVE_omega_rm1_ref
	.bss	WAVE_omega_rm1_ref,4,4
$C$DW$467	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_omega_rm1_ref")
	.dwattr $C$DW$467, DW_AT_TI_symbol_name("WAVE_omega_rm1_ref")
	.dwattr $C$DW$467, DW_AT_location[DW_OP_addr WAVE_omega_rm1_ref]
	.dwattr $C$DW$467, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$467, DW_AT_external
	.dwattr $C$DW$467, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$467, DW_AT_decl_line(0x1d4)
	.dwattr $C$DW$467, DW_AT_decl_column(0x10)
	.global	WAVE_omega_rm2_ref
	.bss	WAVE_omega_rm2_ref,4,4
$C$DW$468	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_omega_rm2_ref")
	.dwattr $C$DW$468, DW_AT_TI_symbol_name("WAVE_omega_rm2_ref")
	.dwattr $C$DW$468, DW_AT_location[DW_OP_addr WAVE_omega_rm2_ref]
	.dwattr $C$DW$468, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$468, DW_AT_external
	.dwattr $C$DW$468, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$468, DW_AT_decl_line(0x1d5)
	.dwattr $C$DW$468, DW_AT_decl_column(0x10)
	.global	WAVE_omega_rm3_ref
	.bss	WAVE_omega_rm3_ref,4,4
$C$DW$469	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_omega_rm3_ref")
	.dwattr $C$DW$469, DW_AT_TI_symbol_name("WAVE_omega_rm3_ref")
	.dwattr $C$DW$469, DW_AT_location[DW_OP_addr WAVE_omega_rm3_ref]
	.dwattr $C$DW$469, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$469, DW_AT_external
	.dwattr $C$DW$469, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$469, DW_AT_decl_line(0x1d6)
	.dwattr $C$DW$469, DW_AT_decl_column(0x10)
	.global	WAVE_Tq1
	.bss	WAVE_Tq1,4,4
$C$DW$470	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Tq1")
	.dwattr $C$DW$470, DW_AT_TI_symbol_name("WAVE_Tq1")
	.dwattr $C$DW$470, DW_AT_location[DW_OP_addr WAVE_Tq1]
	.dwattr $C$DW$470, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$470, DW_AT_external
	.dwattr $C$DW$470, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$470, DW_AT_decl_line(0x1d8)
	.dwattr $C$DW$470, DW_AT_decl_column(0x10)
	.global	WAVE_Tq2
	.bss	WAVE_Tq2,4,4
$C$DW$471	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Tq2")
	.dwattr $C$DW$471, DW_AT_TI_symbol_name("WAVE_Tq2")
	.dwattr $C$DW$471, DW_AT_location[DW_OP_addr WAVE_Tq2]
	.dwattr $C$DW$471, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$471, DW_AT_external
	.dwattr $C$DW$471, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$471, DW_AT_decl_line(0x1d9)
	.dwattr $C$DW$471, DW_AT_decl_column(0x10)
	.global	WAVE_Tq3
	.bss	WAVE_Tq3,4,4
$C$DW$472	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Tq3")
	.dwattr $C$DW$472, DW_AT_TI_symbol_name("WAVE_Tq3")
	.dwattr $C$DW$472, DW_AT_location[DW_OP_addr WAVE_Tq3]
	.dwattr $C$DW$472, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$472, DW_AT_external
	.dwattr $C$DW$472, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$472, DW_AT_decl_line(0x1da)
	.dwattr $C$DW$472, DW_AT_decl_column(0x10)
	.global	WAVE_Icmp1
	.bss	WAVE_Icmp1,4,4
$C$DW$473	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Icmp1")
	.dwattr $C$DW$473, DW_AT_TI_symbol_name("WAVE_Icmp1")
	.dwattr $C$DW$473, DW_AT_location[DW_OP_addr WAVE_Icmp1]
	.dwattr $C$DW$473, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$473, DW_AT_external
	.dwattr $C$DW$473, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$473, DW_AT_decl_line(0x1dc)
	.dwattr $C$DW$473, DW_AT_decl_column(0x10)
	.global	WAVE_Icmp2
	.bss	WAVE_Icmp2,4,4
$C$DW$474	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Icmp2")
	.dwattr $C$DW$474, DW_AT_TI_symbol_name("WAVE_Icmp2")
	.dwattr $C$DW$474, DW_AT_location[DW_OP_addr WAVE_Icmp2]
	.dwattr $C$DW$474, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$474, DW_AT_external
	.dwattr $C$DW$474, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$474, DW_AT_decl_line(0x1dd)
	.dwattr $C$DW$474, DW_AT_decl_column(0x10)
	.global	WAVE_Icmp3
	.bss	WAVE_Icmp3,4,4
$C$DW$475	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Icmp3")
	.dwattr $C$DW$475, DW_AT_TI_symbol_name("WAVE_Icmp3")
	.dwattr $C$DW$475, DW_AT_location[DW_OP_addr WAVE_Icmp3]
	.dwattr $C$DW$475, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$475, DW_AT_external
	.dwattr $C$DW$475, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$475, DW_AT_decl_line(0x1de)
	.dwattr $C$DW$475, DW_AT_decl_column(0x10)
	.global	ref_Iq_direct1
	.sect	".neardata", RW
	.align	4
	.elfsym	ref_Iq_direct1,SYM_SIZE(4)
ref_Iq_direct1:
	.word	000000000h		; ref_Iq_direct1 @ 0

$C$DW$476	.dwtag  DW_TAG_variable, DW_AT_name("ref_Iq_direct1")
	.dwattr $C$DW$476, DW_AT_TI_symbol_name("ref_Iq_direct1")
	.dwattr $C$DW$476, DW_AT_location[DW_OP_addr ref_Iq_direct1]
	.dwattr $C$DW$476, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$476, DW_AT_external
	.dwattr $C$DW$476, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$476, DW_AT_decl_line(0x1e0)
	.dwattr $C$DW$476, DW_AT_decl_column(0x10)
	.global	ref_Iq_direct2
	.sect	".neardata", RW
	.align	4
	.elfsym	ref_Iq_direct2,SYM_SIZE(4)
ref_Iq_direct2:
	.word	000000000h		; ref_Iq_direct2 @ 0

$C$DW$477	.dwtag  DW_TAG_variable, DW_AT_name("ref_Iq_direct2")
	.dwattr $C$DW$477, DW_AT_TI_symbol_name("ref_Iq_direct2")
	.dwattr $C$DW$477, DW_AT_location[DW_OP_addr ref_Iq_direct2]
	.dwattr $C$DW$477, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$477, DW_AT_external
	.dwattr $C$DW$477, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$477, DW_AT_decl_line(0x1e1)
	.dwattr $C$DW$477, DW_AT_decl_column(0x10)
	.global	ref_Iq_direct3
	.sect	".neardata", RW
	.align	4
	.elfsym	ref_Iq_direct3,SYM_SIZE(4)
ref_Iq_direct3:
	.word	000000000h		; ref_Iq_direct3 @ 0

$C$DW$478	.dwtag  DW_TAG_variable, DW_AT_name("ref_Iq_direct3")
	.dwattr $C$DW$478, DW_AT_TI_symbol_name("ref_Iq_direct3")
	.dwattr $C$DW$478, DW_AT_location[DW_OP_addr ref_Iq_direct3]
	.dwattr $C$DW$478, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$478, DW_AT_external
	.dwattr $C$DW$478, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$478, DW_AT_decl_line(0x1e2)
	.dwattr $C$DW$478, DW_AT_decl_column(0x10)
	.global	ref_Iq_freq_direct1
	.bss	ref_Iq_freq_direct1,4,4
$C$DW$479	.dwtag  DW_TAG_variable, DW_AT_name("ref_Iq_freq_direct1")
	.dwattr $C$DW$479, DW_AT_TI_symbol_name("ref_Iq_freq_direct1")
	.dwattr $C$DW$479, DW_AT_location[DW_OP_addr ref_Iq_freq_direct1]
	.dwattr $C$DW$479, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$479, DW_AT_external
	.dwattr $C$DW$479, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$479, DW_AT_decl_line(0x1e4)
	.dwattr $C$DW$479, DW_AT_decl_column(0x10)
	.global	ref_Iq_freq_direct2
	.bss	ref_Iq_freq_direct2,4,4
$C$DW$480	.dwtag  DW_TAG_variable, DW_AT_name("ref_Iq_freq_direct2")
	.dwattr $C$DW$480, DW_AT_TI_symbol_name("ref_Iq_freq_direct2")
	.dwattr $C$DW$480, DW_AT_location[DW_OP_addr ref_Iq_freq_direct2]
	.dwattr $C$DW$480, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$480, DW_AT_external
	.dwattr $C$DW$480, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$480, DW_AT_decl_line(0x1e5)
	.dwattr $C$DW$480, DW_AT_decl_column(0x10)
	.global	ref_Iq_freq_direct3
	.bss	ref_Iq_freq_direct3,4,4
$C$DW$481	.dwtag  DW_TAG_variable, DW_AT_name("ref_Iq_freq_direct3")
	.dwattr $C$DW$481, DW_AT_TI_symbol_name("ref_Iq_freq_direct3")
	.dwattr $C$DW$481, DW_AT_location[DW_OP_addr ref_Iq_freq_direct3]
	.dwattr $C$DW$481, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$481, DW_AT_external
	.dwattr $C$DW$481, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$481, DW_AT_decl_line(0x1e6)
	.dwattr $C$DW$481, DW_AT_decl_column(0x10)
	.global	WAVE_Iff_1
	.bss	WAVE_Iff_1,4,4
$C$DW$482	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Iff_1")
	.dwattr $C$DW$482, DW_AT_TI_symbol_name("WAVE_Iff_1")
	.dwattr $C$DW$482, DW_AT_location[DW_OP_addr WAVE_Iff_1]
	.dwattr $C$DW$482, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$482, DW_AT_external
	.dwattr $C$DW$482, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$482, DW_AT_decl_line(0x1e8)
	.dwattr $C$DW$482, DW_AT_decl_column(0x10)
	.global	WAVE_Iff_2
	.bss	WAVE_Iff_2,4,4
$C$DW$483	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Iff_2")
	.dwattr $C$DW$483, DW_AT_TI_symbol_name("WAVE_Iff_2")
	.dwattr $C$DW$483, DW_AT_location[DW_OP_addr WAVE_Iff_2]
	.dwattr $C$DW$483, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$483, DW_AT_external
	.dwattr $C$DW$483, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$483, DW_AT_decl_line(0x1e9)
	.dwattr $C$DW$483, DW_AT_decl_column(0x10)
	.global	WAVE_Iff_3
	.bss	WAVE_Iff_3,4,4
$C$DW$484	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Iff_3")
	.dwattr $C$DW$484, DW_AT_TI_symbol_name("WAVE_Iff_3")
	.dwattr $C$DW$484, DW_AT_location[DW_OP_addr WAVE_Iff_3]
	.dwattr $C$DW$484, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$484, DW_AT_external
	.dwattr $C$DW$484, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$484, DW_AT_decl_line(0x1ea)
	.dwattr $C$DW$484, DW_AT_decl_column(0x10)
	.global	WAVE_tauL_dyn_2nd
	.bss	WAVE_tauL_dyn_2nd,4,4
$C$DW$485	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_tauL_dyn_2nd")
	.dwattr $C$DW$485, DW_AT_TI_symbol_name("WAVE_tauL_dyn_2nd")
	.dwattr $C$DW$485, DW_AT_location[DW_OP_addr WAVE_tauL_dyn_2nd]
	.dwattr $C$DW$485, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$485, DW_AT_external
	.dwattr $C$DW$485, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$485, DW_AT_decl_line(0x1ec)
	.dwattr $C$DW$485, DW_AT_decl_column(0x10)
	.global	WAVE_VWX
	.bss	WAVE_VWX,4,4
$C$DW$486	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VWX")
	.dwattr $C$DW$486, DW_AT_TI_symbol_name("WAVE_VWX")
	.dwattr $C$DW$486, DW_AT_location[DW_OP_addr WAVE_VWX]
	.dwattr $C$DW$486, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$486, DW_AT_external
	.dwattr $C$DW$486, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$486, DW_AT_decl_line(0x1ee)
	.dwattr $C$DW$486, DW_AT_decl_column(0x10)
	.global	WAVE_VWY
	.bss	WAVE_VWY,4,4
$C$DW$487	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VWY")
	.dwattr $C$DW$487, DW_AT_TI_symbol_name("WAVE_VWY")
	.dwattr $C$DW$487, DW_AT_location[DW_OP_addr WAVE_VWY]
	.dwattr $C$DW$487, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$487, DW_AT_external
	.dwattr $C$DW$487, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$487, DW_AT_decl_line(0x1ef)
	.dwattr $C$DW$487, DW_AT_decl_column(0x10)
	.global	WAVE_VWZ
	.bss	WAVE_VWZ,4,4
$C$DW$488	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VWZ")
	.dwattr $C$DW$488, DW_AT_TI_symbol_name("WAVE_VWZ")
	.dwattr $C$DW$488, DW_AT_location[DW_OP_addr WAVE_VWZ]
	.dwattr $C$DW$488, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$488, DW_AT_external
	.dwattr $C$DW$488, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$488, DW_AT_decl_line(0x1f0)
	.dwattr $C$DW$488, DW_AT_decl_column(0x10)
	.global	WAVE_AccCmd1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_AccCmd1,SYM_SIZE(4)
WAVE_AccCmd1:
	.word	000000000h		; WAVE_AccCmd1 @ 0

$C$DW$489	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_AccCmd1")
	.dwattr $C$DW$489, DW_AT_TI_symbol_name("WAVE_AccCmd1")
	.dwattr $C$DW$489, DW_AT_location[DW_OP_addr WAVE_AccCmd1]
	.dwattr $C$DW$489, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$489, DW_AT_external
	.dwattr $C$DW$489, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$489, DW_AT_decl_line(0x1f2)
	.dwattr $C$DW$489, DW_AT_decl_column(0x10)
	.global	WAVE_VelCmd1
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_VelCmd1,SYM_SIZE(4)
WAVE_VelCmd1:
	.word	000000000h		; WAVE_VelCmd1 @ 0

$C$DW$490	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VelCmd1")
	.dwattr $C$DW$490, DW_AT_TI_symbol_name("WAVE_VelCmd1")
	.dwattr $C$DW$490, DW_AT_location[DW_OP_addr WAVE_VelCmd1]
	.dwattr $C$DW$490, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$490, DW_AT_external
	.dwattr $C$DW$490, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$490, DW_AT_decl_line(0x1f3)
	.dwattr $C$DW$490, DW_AT_decl_column(0x10)
	.global	WAVE_AccCmd2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_AccCmd2,SYM_SIZE(4)
WAVE_AccCmd2:
	.word	000000000h		; WAVE_AccCmd2 @ 0

$C$DW$491	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_AccCmd2")
	.dwattr $C$DW$491, DW_AT_TI_symbol_name("WAVE_AccCmd2")
	.dwattr $C$DW$491, DW_AT_location[DW_OP_addr WAVE_AccCmd2]
	.dwattr $C$DW$491, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$491, DW_AT_external
	.dwattr $C$DW$491, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$491, DW_AT_decl_line(0x1f4)
	.dwattr $C$DW$491, DW_AT_decl_column(0x10)
	.global	WAVE_VelCmd2
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_VelCmd2,SYM_SIZE(4)
WAVE_VelCmd2:
	.word	000000000h		; WAVE_VelCmd2 @ 0

$C$DW$492	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VelCmd2")
	.dwattr $C$DW$492, DW_AT_TI_symbol_name("WAVE_VelCmd2")
	.dwattr $C$DW$492, DW_AT_location[DW_OP_addr WAVE_VelCmd2]
	.dwattr $C$DW$492, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$492, DW_AT_external
	.dwattr $C$DW$492, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$492, DW_AT_decl_line(0x1f5)
	.dwattr $C$DW$492, DW_AT_decl_column(0x10)
	.global	WAVE_AccCmd3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_AccCmd3,SYM_SIZE(4)
WAVE_AccCmd3:
	.word	000000000h		; WAVE_AccCmd3 @ 0

$C$DW$493	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_AccCmd3")
	.dwattr $C$DW$493, DW_AT_TI_symbol_name("WAVE_AccCmd3")
	.dwattr $C$DW$493, DW_AT_location[DW_OP_addr WAVE_AccCmd3]
	.dwattr $C$DW$493, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$493, DW_AT_external
	.dwattr $C$DW$493, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$493, DW_AT_decl_line(0x1f6)
	.dwattr $C$DW$493, DW_AT_decl_column(0x10)
	.global	WAVE_VelCmd3
	.sect	".neardata", RW
	.align	4
	.elfsym	WAVE_VelCmd3,SYM_SIZE(4)
WAVE_VelCmd3:
	.word	000000000h		; WAVE_VelCmd3 @ 0

$C$DW$494	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_VelCmd3")
	.dwattr $C$DW$494, DW_AT_TI_symbol_name("WAVE_VelCmd3")
	.dwattr $C$DW$494, DW_AT_location[DW_OP_addr WAVE_VelCmd3]
	.dwattr $C$DW$494, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$494, DW_AT_external
	.dwattr $C$DW$494, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$494, DW_AT_decl_line(0x1f7)
	.dwattr $C$DW$494, DW_AT_decl_column(0x10)
	.global	WAVE_Enc_error
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	4
	.elfsym	WAVE_Enc_error,SYM_SIZE(4)
WAVE_Enc_error:
	.bits	0,32			; WAVE_Enc_error @ 0

$C$DW$495	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Enc_error")
	.dwattr $C$DW$495, DW_AT_TI_symbol_name("WAVE_Enc_error")
	.dwattr $C$DW$495, DW_AT_location[DW_OP_addr WAVE_Enc_error]
	.dwattr $C$DW$495, DW_AT_type(*$C$DW$T$299)
	.dwattr $C$DW$495, DW_AT_external
	.dwattr $C$DW$495, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$495, DW_AT_decl_line(0x1ff)
	.dwattr $C$DW$495, DW_AT_decl_column(0x10)
	.global	WAVE_ofst_Iu
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	4
	.elfsym	WAVE_ofst_Iu,SYM_SIZE(4)
WAVE_ofst_Iu:
	.word	000000000h		; WAVE_ofst_Iu @ 0

$C$DW$496	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ofst_Iu")
	.dwattr $C$DW$496, DW_AT_TI_symbol_name("WAVE_ofst_Iu")
	.dwattr $C$DW$496, DW_AT_location[DW_OP_addr WAVE_ofst_Iu]
	.dwattr $C$DW$496, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$496, DW_AT_external
	.dwattr $C$DW$496, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$496, DW_AT_decl_line(0x200)
	.dwattr $C$DW$496, DW_AT_decl_column(0x10)
	.global	WAVE_ofst_Iv
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	4
	.elfsym	WAVE_ofst_Iv,SYM_SIZE(4)
WAVE_ofst_Iv:
	.word	000000000h		; WAVE_ofst_Iv @ 0

$C$DW$497	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ofst_Iv")
	.dwattr $C$DW$497, DW_AT_TI_symbol_name("WAVE_ofst_Iv")
	.dwattr $C$DW$497, DW_AT_location[DW_OP_addr WAVE_ofst_Iv]
	.dwattr $C$DW$497, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$497, DW_AT_external
	.dwattr $C$DW$497, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$497, DW_AT_decl_line(0x201)
	.dwattr $C$DW$497, DW_AT_decl_column(0x10)
	.global	WAVE_ofst_Iw
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	4
	.elfsym	WAVE_ofst_Iw,SYM_SIZE(4)
WAVE_ofst_Iw:
	.word	000000000h		; WAVE_ofst_Iw @ 0

$C$DW$498	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_ofst_Iw")
	.dwattr $C$DW$498, DW_AT_TI_symbol_name("WAVE_ofst_Iw")
	.dwattr $C$DW$498, DW_AT_location[DW_OP_addr WAVE_ofst_Iw]
	.dwattr $C$DW$498, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$498, DW_AT_external
	.dwattr $C$DW$498, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$498, DW_AT_decl_line(0x202)
	.dwattr $C$DW$498, DW_AT_decl_column(0x10)
	.global	WAVE_Vdc_ofst
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	4
	.elfsym	WAVE_Vdc_ofst,SYM_SIZE(4)
WAVE_Vdc_ofst:
	.word	000000000h		; WAVE_Vdc_ofst @ 0

$C$DW$499	.dwtag  DW_TAG_variable, DW_AT_name("WAVE_Vdc_ofst")
	.dwattr $C$DW$499, DW_AT_TI_symbol_name("WAVE_Vdc_ofst")
	.dwattr $C$DW$499, DW_AT_location[DW_OP_addr WAVE_Vdc_ofst]
	.dwattr $C$DW$499, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$499, DW_AT_external
	.dwattr $C$DW$499, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$499, DW_AT_decl_line(0x203)
	.dwattr $C$DW$499, DW_AT_decl_column(0x10)
	.global	debug
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	8
	.elfsym	debug,SYM_SIZE(16)
debug:
	.word	0bf800000h		; debug[0] @ 0
	.space	12

$C$DW$500	.dwtag  DW_TAG_variable, DW_AT_name("debug")
	.dwattr $C$DW$500, DW_AT_TI_symbol_name("debug")
	.dwattr $C$DW$500, DW_AT_location[DW_OP_addr debug]
	.dwattr $C$DW$500, DW_AT_type(*$C$DW$T$396)
	.dwattr $C$DW$500, DW_AT_external
	.dwattr $C$DW$500, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$500, DW_AT_decl_line(0x205)
	.dwattr $C$DW$500, DW_AT_decl_column(0x10)
	.global	debug2
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	8
	.elfsym	debug2,SYM_SIZE(16)
debug2:
	.word	0bf800000h		; debug2[0] @ 0
	.space	12

$C$DW$501	.dwtag  DW_TAG_variable, DW_AT_name("debug2")
	.dwattr $C$DW$501, DW_AT_TI_symbol_name("debug2")
	.dwattr $C$DW$501, DW_AT_location[DW_OP_addr debug2]
	.dwattr $C$DW$501, DW_AT_type(*$C$DW$T$396)
	.dwattr $C$DW$501, DW_AT_external
	.dwattr $C$DW$501, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$501, DW_AT_decl_line(0x206)
	.dwattr $C$DW$501, DW_AT_decl_column(0x10)
	.global	debug3
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	8
	.elfsym	debug3,SYM_SIZE(16)
debug3:
	.word	0bf800000h		; debug3[0] @ 0
	.space	12

$C$DW$502	.dwtag  DW_TAG_variable, DW_AT_name("debug3")
	.dwattr $C$DW$502, DW_AT_TI_symbol_name("debug3")
	.dwattr $C$DW$502, DW_AT_location[DW_OP_addr debug3]
	.dwattr $C$DW$502, DW_AT_type(*$C$DW$T$396)
	.dwattr $C$DW$502, DW_AT_external
	.dwattr $C$DW$502, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$502, DW_AT_decl_line(0x207)
	.dwattr $C$DW$502, DW_AT_decl_column(0x10)
	.global	ad1
ad1:	.usect	".DATA_ON_HIGHER_SPEED:uninit",4,4
$C$DW$503	.dwtag  DW_TAG_variable, DW_AT_name("ad1")
	.dwattr $C$DW$503, DW_AT_TI_symbol_name("ad1")
	.dwattr $C$DW$503, DW_AT_location[DW_OP_addr ad1]
	.dwattr $C$DW$503, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$503, DW_AT_external
	.dwattr $C$DW$503, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$503, DW_AT_decl_line(0x208)
	.dwattr $C$DW$503, DW_AT_decl_column(0x10)
	.global	ad2
ad2:	.usect	".DATA_ON_HIGHER_SPEED:uninit",4,4
$C$DW$504	.dwtag  DW_TAG_variable, DW_AT_name("ad2")
	.dwattr $C$DW$504, DW_AT_TI_symbol_name("ad2")
	.dwattr $C$DW$504, DW_AT_location[DW_OP_addr ad2]
	.dwattr $C$DW$504, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$504, DW_AT_external
	.dwattr $C$DW$504, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$504, DW_AT_decl_line(0x209)
	.dwattr $C$DW$504, DW_AT_decl_column(0x10)
	.global	ad3
ad3:	.usect	".DATA_ON_HIGHER_SPEED:uninit",4,4
$C$DW$505	.dwtag  DW_TAG_variable, DW_AT_name("ad3")
	.dwattr $C$DW$505, DW_AT_TI_symbol_name("ad3")
	.dwattr $C$DW$505, DW_AT_location[DW_OP_addr ad3]
	.dwattr $C$DW$505, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$505, DW_AT_external
	.dwattr $C$DW$505, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$505, DW_AT_decl_line(0x20a)
	.dwattr $C$DW$505, DW_AT_decl_column(0x10)
	.global	ModRatioU
ModRatioU:	.usect	".DATA_ON_HIGHER_SPEED:uninit",4,4
$C$DW$506	.dwtag  DW_TAG_variable, DW_AT_name("ModRatioU")
	.dwattr $C$DW$506, DW_AT_TI_symbol_name("ModRatioU")
	.dwattr $C$DW$506, DW_AT_location[DW_OP_addr ModRatioU]
	.dwattr $C$DW$506, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$506, DW_AT_external
	.dwattr $C$DW$506, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$506, DW_AT_decl_line(0x210)
	.dwattr $C$DW$506, DW_AT_decl_column(0x10)
	.global	ModRatioV
ModRatioV:	.usect	".DATA_ON_HIGHER_SPEED:uninit",4,4
$C$DW$507	.dwtag  DW_TAG_variable, DW_AT_name("ModRatioV")
	.dwattr $C$DW$507, DW_AT_TI_symbol_name("ModRatioV")
	.dwattr $C$DW$507, DW_AT_location[DW_OP_addr ModRatioV]
	.dwattr $C$DW$507, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$507, DW_AT_external
	.dwattr $C$DW$507, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$507, DW_AT_decl_line(0x211)
	.dwattr $C$DW$507, DW_AT_decl_column(0x10)
	.global	ModRatioW
ModRatioW:	.usect	".DATA_ON_HIGHER_SPEED:uninit",4,4
$C$DW$508	.dwtag  DW_TAG_variable, DW_AT_name("ModRatioW")
	.dwattr $C$DW$508, DW_AT_TI_symbol_name("ModRatioW")
	.dwattr $C$DW$508, DW_AT_location[DW_OP_addr ModRatioW]
	.dwattr $C$DW$508, DW_AT_type(*$C$DW$T$144)
	.dwattr $C$DW$508, DW_AT_external
	.dwattr $C$DW$508, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$508, DW_AT_decl_line(0x212)
	.dwattr $C$DW$508, DW_AT_decl_column(0x10)
	.global	joint
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	8
	.elfsym	joint,SYM_SIZE(1620)
joint:
	.bits	0,32			; joint[0].BDN @ 0
	.space	1616

$C$DW$509	.dwtag  DW_TAG_variable, DW_AT_name("joint")
	.dwattr $C$DW$509, DW_AT_TI_symbol_name("joint")
	.dwattr $C$DW$509, DW_AT_location[DW_OP_addr joint]
	.dwattr $C$DW$509, DW_AT_type(*$C$DW$T$463)
	.dwattr $C$DW$509, DW_AT_external
	.dwattr $C$DW$509, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$509, DW_AT_decl_line(0x2a6)
	.dwattr $C$DW$509, DW_AT_decl_column(0x07)
	.global	ob_sub
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	8
	.elfsym	ob_sub,SYM_SIZE(348)
ob_sub:
	.word	000000000h		; ob_sub[0].a11cf @ 0
	.space	344

$C$DW$510	.dwtag  DW_TAG_variable, DW_AT_name("ob_sub")
	.dwattr $C$DW$510, DW_AT_TI_symbol_name("ob_sub")
	.dwattr $C$DW$510, DW_AT_location[DW_OP_addr ob_sub]
	.dwattr $C$DW$510, DW_AT_type(*$C$DW$T$447)
	.dwattr $C$DW$510, DW_AT_external
	.dwattr $C$DW$510, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$510, DW_AT_decl_line(0x2c1)
	.dwattr $C$DW$510, DW_AT_decl_column(0x17)
	.global	Wr_sub
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	8
	.elfsym	Wr_sub,SYM_SIZE(792)
Wr_sub:
	.word	000000000h		; Wr_sub[0].a11cf @ 0
	.space	788

$C$DW$511	.dwtag  DW_TAG_variable, DW_AT_name("Wr_sub")
	.dwattr $C$DW$511, DW_AT_TI_symbol_name("Wr_sub")
	.dwattr $C$DW$511, DW_AT_location[DW_OP_addr Wr_sub]
	.dwattr $C$DW$511, DW_AT_type(*$C$DW$T$452)
	.dwattr $C$DW$511, DW_AT_external
	.dwattr $C$DW$511, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$511, DW_AT_decl_line(0x2e8)
	.dwattr $C$DW$511, DW_AT_decl_column(0x15)
	.global	Wr_DPD
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	8
	.elfsym	Wr_DPD,SYM_SIZE(792)
Wr_DPD:
	.word	000000000h		; Wr_DPD[0].a11cf @ 0
	.space	788

$C$DW$512	.dwtag  DW_TAG_variable, DW_AT_name("Wr_DPD")
	.dwattr $C$DW$512, DW_AT_TI_symbol_name("Wr_DPD")
	.dwattr $C$DW$512, DW_AT_location[DW_OP_addr Wr_DPD]
	.dwattr $C$DW$512, DW_AT_type(*$C$DW$T$452)
	.dwattr $C$DW$512, DW_AT_external
	.dwattr $C$DW$512, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$512, DW_AT_decl_line(0x2e9)
	.dwattr $C$DW$512, DW_AT_decl_column(0x15)
	.global	dyn
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	4
	.elfsym	dyn,SYM_SIZE(260)
dyn:
	.word	000000000h		; dyn.H11p1 @ 0
	.space	256

$C$DW$513	.dwtag  DW_TAG_variable, DW_AT_name("dyn")
	.dwattr $C$DW$513, DW_AT_TI_symbol_name("dyn")
	.dwattr $C$DW$513, DW_AT_location[DW_OP_addr dyn]
	.dwattr $C$DW$513, DW_AT_type(*$C$DW$T$473)
	.dwattr $C$DW$513, DW_AT_external
	.dwattr $C$DW$513, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$513, DW_AT_decl_line(0x30b)
	.dwattr $C$DW$513, DW_AT_decl_column(0x10)
	.global	tri
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	8
	.elfsym	tri,SYM_SIZE(120)
tri:
	.word	000000000h		; tri[0].a_time_full @ 0
	.space	116

$C$DW$514	.dwtag  DW_TAG_variable, DW_AT_name("tri")
	.dwattr $C$DW$514, DW_AT_TI_symbol_name("tri")
	.dwattr $C$DW$514, DW_AT_location[DW_OP_addr tri]
	.dwattr $C$DW$514, DW_AT_type(*$C$DW$T$472)
	.dwattr $C$DW$514, DW_AT_external
	.dwattr $C$DW$514, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$514, DW_AT_decl_line(0x31e)
	.dwattr $C$DW$514, DW_AT_decl_column(0x25)
	.global	gsub
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	8
	.elfsym	gsub,SYM_SIZE(324)
gsub:
	.word	000000000h		; gsub[0].Kvp_cfp1 @ 0
	.space	320

$C$DW$515	.dwtag  DW_TAG_variable, DW_AT_name("gsub")
	.dwattr $C$DW$515, DW_AT_TI_symbol_name("gsub")
	.dwattr $C$DW$515, DW_AT_location[DW_OP_addr gsub]
	.dwattr $C$DW$515, DW_AT_type(*$C$DW$T$227)
	.dwattr $C$DW$515, DW_AT_external
	.dwattr $C$DW$515, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$515, DW_AT_decl_line(0x340)
	.dwattr $C$DW$515, DW_AT_decl_column(0x0e)
	.global	Tm_sub
	.sect	".DATA_ON_HIGHER_SPEED:init", RW
	.align	8
	.elfsym	Tm_sub,SYM_SIZE(72)
Tm_sub:
	.word	000000000h		; Tm_sub[0].den_0 @ 0
	.space	68

$C$DW$516	.dwtag  DW_TAG_variable, DW_AT_name("Tm_sub")
	.dwattr $C$DW$516, DW_AT_TI_symbol_name("Tm_sub")
	.dwattr $C$DW$516, DW_AT_location[DW_OP_addr Tm_sub]
	.dwattr $C$DW$516, DW_AT_type(*$C$DW$T$443)
	.dwattr $C$DW$516, DW_AT_external
	.dwattr $C$DW$516, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$516, DW_AT_decl_line(0x34f)
	.dwattr $C$DW$516, DW_AT_decl_column(0x15)
	.global	sen
	.sect	".fardata:sen", RW
	.clink
	.align	8
	.elfsym	sen,SYM_SIZE(288)
sen:
	.word	000000000h		; sen[0].VtoVdc @ 0
	.space	284

$C$DW$517	.dwtag  DW_TAG_variable, DW_AT_name("sen")
	.dwattr $C$DW$517, DW_AT_TI_symbol_name("sen")
	.dwattr $C$DW$517, DW_AT_location[DW_OP_addr sen]
	.dwattr $C$DW$517, DW_AT_type(*$C$DW$T$457)
	.dwattr $C$DW$517, DW_AT_external
	.dwattr $C$DW$517, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$517, DW_AT_decl_line(0x37f)
	.dwattr $C$DW$517, DW_AT_decl_column(0x08)
	.global	LPF_motor
	.sect	".fardata:LPF_motor", RW
	.clink
	.align	8
	.elfsym	LPF_motor,SYM_SIZE(132)
LPF_motor:
	.bits	0,32			; LPF_motor[0].Num @ 0
	.space	128

$C$DW$518	.dwtag  DW_TAG_variable, DW_AT_name("LPF_motor")
	.dwattr $C$DW$518, DW_AT_TI_symbol_name("LPF_motor")
	.dwattr $C$DW$518, DW_AT_location[DW_OP_addr LPF_motor]
	.dwattr $C$DW$518, DW_AT_type(*$C$DW$T$216)
	.dwattr $C$DW$518, DW_AT_external
	.dwattr $C$DW$518, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$518, DW_AT_decl_line(0x38e)
	.dwattr $C$DW$518, DW_AT_decl_column(0x0b)
	.global	LPF_cmd
	.sect	".fardata:LPF_cmd", RW
	.clink
	.align	8
	.elfsym	LPF_cmd,SYM_SIZE(132)
LPF_cmd:
	.bits	0,32			; LPF_cmd[0].Num @ 0
	.space	128

$C$DW$519	.dwtag  DW_TAG_variable, DW_AT_name("LPF_cmd")
	.dwattr $C$DW$519, DW_AT_TI_symbol_name("LPF_cmd")
	.dwattr $C$DW$519, DW_AT_location[DW_OP_addr LPF_cmd]
	.dwattr $C$DW$519, DW_AT_type(*$C$DW$T$216)
	.dwattr $C$DW$519, DW_AT_external
	.dwattr $C$DW$519, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$519, DW_AT_decl_line(0x38f)
	.dwattr $C$DW$519, DW_AT_decl_column(0x0b)
	.global	q_current
	.sect	".fardata:q_current", RW
	.clink
	.align	8
	.elfsym	q_current,SYM_SIZE(72)
q_current:
	.word	000000000h		; q_current[0].uZ1 @ 0
	.space	68

$C$DW$520	.dwtag  DW_TAG_variable, DW_AT_name("q_current")
	.dwattr $C$DW$520, DW_AT_TI_symbol_name("q_current")
	.dwattr $C$DW$520, DW_AT_location[DW_OP_addr q_current]
	.dwattr $C$DW$520, DW_AT_type(*$C$DW$T$468)
	.dwattr $C$DW$520, DW_AT_external
	.dwattr $C$DW$520, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$520, DW_AT_decl_line(0x3f4)
	.dwattr $C$DW$520, DW_AT_decl_column(0x0c)
	.global	d_current
	.sect	".fardata:d_current", RW
	.clink
	.align	8
	.elfsym	d_current,SYM_SIZE(72)
d_current:
	.word	000000000h		; d_current[0].uZ1 @ 0
	.space	68

$C$DW$521	.dwtag  DW_TAG_variable, DW_AT_name("d_current")
	.dwattr $C$DW$521, DW_AT_TI_symbol_name("d_current")
	.dwattr $C$DW$521, DW_AT_location[DW_OP_addr d_current]
	.dwattr $C$DW$521, DW_AT_type(*$C$DW$T$468)
	.dwattr $C$DW$521, DW_AT_external
	.dwattr $C$DW$521, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$521, DW_AT_decl_line(0x3f5)
	.dwattr $C$DW$521, DW_AT_decl_column(0x0c)
	.global	velocity
	.sect	".fardata:velocity", RW
	.clink
	.align	8
	.elfsym	velocity,SYM_SIZE(72)
velocity:
	.word	000000000h		; velocity[0].uZ1 @ 0
	.space	68

$C$DW$522	.dwtag  DW_TAG_variable, DW_AT_name("velocity")
	.dwattr $C$DW$522, DW_AT_TI_symbol_name("velocity")
	.dwattr $C$DW$522, DW_AT_location[DW_OP_addr velocity]
	.dwattr $C$DW$522, DW_AT_type(*$C$DW$T$468)
	.dwattr $C$DW$522, DW_AT_external
	.dwattr $C$DW$522, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$522, DW_AT_decl_line(0x3f7)
	.dwattr $C$DW$522, DW_AT_decl_column(0x0c)
	.global	position
	.sect	".fardata:position", RW
	.clink
	.align	8
	.elfsym	position,SYM_SIZE(72)
position:
	.word	000000000h		; position[0].uZ1 @ 0
	.space	68

$C$DW$523	.dwtag  DW_TAG_variable, DW_AT_name("position")
	.dwattr $C$DW$523, DW_AT_TI_symbol_name("position")
	.dwattr $C$DW$523, DW_AT_location[DW_OP_addr position]
	.dwattr $C$DW$523, DW_AT_type(*$C$DW$T$468)
	.dwattr $C$DW$523, DW_AT_external
	.dwattr $C$DW$523, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$523, DW_AT_decl_line(0x3f8)
	.dwattr $C$DW$523, DW_AT_decl_column(0x0c)
	.global	force
	.sect	".fardata:force", RW
	.clink
	.align	8
	.elfsym	force,SYM_SIZE(72)
force:
	.word	000000000h		; force[0].uZ1 @ 0
	.space	68

$C$DW$524	.dwtag  DW_TAG_variable, DW_AT_name("force")
	.dwattr $C$DW$524, DW_AT_TI_symbol_name("force")
	.dwattr $C$DW$524, DW_AT_location[DW_OP_addr force]
	.dwattr $C$DW$524, DW_AT_type(*$C$DW$T$468)
	.dwattr $C$DW$524, DW_AT_external
	.dwattr $C$DW$524, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$524, DW_AT_decl_line(0x3fa)
	.dwattr $C$DW$524, DW_AT_decl_column(0x0c)
	.sect	".neardata", RW
	.align	4
	.elfsym	LoopCount$1,SYM_SIZE(4)
LoopCount$1:
	.bits	0,32			; LoopCount$1 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	t$2,SYM_SIZE(4)
t$2:
	.word	000000000h		; t$2 @ 0

	.sect	".fardata:hand_cmd$3", RW
	.clink
	.align	8
	.elfsym	hand_cmd$3,SYM_SIZE(12)
hand_cmd$3:
	.word	000000000h		; hand_cmd$3[0] @ 0
	.word	000000000h		; hand_cmd$3[1] @ 32
	.word	000000000h		; hand_cmd$3[2] @ 64

	.sect	".fardata:joint_cmd$4", RW
	.clink
	.align	8
	.elfsym	joint_cmd$4,SYM_SIZE(12)
joint_cmd$4:
	.word	000000000h		; joint_cmd$4[0] @ 0
	.word	000000000h		; joint_cmd$4[1] @ 32
	.word	000000000h		; joint_cmd$4[2] @ 64

	.sect	".fardata:motor_cmd$5", RW
	.clink
	.align	8
	.elfsym	motor_cmd$5,SYM_SIZE(12)
motor_cmd$5:
	.word	000000000h		; motor_cmd$5[0] @ 0
	.word	000000000h		; motor_cmd$5[1] @ 32
	.word	000000000h		; motor_cmd$5[2] @ 64

	.sect	".fardata:motor_vel_cmd$6", RW
	.clink
	.align	8
	.elfsym	motor_vel_cmd$6,SYM_SIZE(12)
motor_vel_cmd$6:
	.word	000000000h		; motor_vel_cmd$6[0] @ 0
	.word	000000000h		; motor_vel_cmd$6[1] @ 32
	.word	000000000h		; motor_vel_cmd$6[2] @ 64

	.sect	".neardata", RW
	.align	4
	.elfsym	flag_fin$7,SYM_SIZE(4)
flag_fin$7:
	.bits	0,32			; flag_fin$7 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	wait_cmd$8,SYM_SIZE(4)
wait_cmd$8:
	.word	040400000h		; wait_cmd$8 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	speed$9,SYM_SIZE(4)
speed$9:
	.word	041200000h		; speed$9 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	flag_loop$10,SYM_SIZE(4)
flag_loop$10:
	.bits	0,32			; flag_loop$10 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	filter$11,SYM_SIZE(4)
filter$11:
	.bits	0,32			; filter$11 @ 0

	.bss	flag$12,4,4
	.sect	".neardata", RW
	.align	4
	.elfsym	reset$13,SYM_SIZE(4)
reset$13:
	.bits	1,32			; reset$13 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	time_wait$14,SYM_SIZE(4)
time_wait$14:
	.word	040400000h		; time_wait$14 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	speed_hand$15,SYM_SIZE(4)
speed_hand$15:
	.word	041200000h		; speed_hand$15 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	flag_loop$16,SYM_SIZE(4)
flag_loop$16:
	.bits	1,32			; flag_loop$16 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	filter_reset$17,SYM_SIZE(4)
filter_reset$17:
	.bits	0,32			; filter_reset$17 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	flag_fin$18,SYM_SIZE(4)
flag_fin$18:
	.bits	0,32			; flag_fin$18 @ 0


$C$DW$525	.dwtag  DW_TAG_subprogram, DW_AT_name("memset")
	.dwattr $C$DW$525, DW_AT_TI_symbol_name("memset")
	.dwattr $C$DW$525, DW_AT_type(*$C$DW$T$3)
	.dwattr $C$DW$525, DW_AT_declaration
	.dwattr $C$DW$525, DW_AT_external
	.sect	".const:$P$T0$19"
	.clink
	.align	8
	.elfsym	$P$T0$19,SYM_SIZE(12)
$P$T0$19:
	.word	000000000h		; $P$T0$19[0] @ 0
	.space	8

$C$DW$526	.dwtag  DW_TAG_variable, DW_AT_name("$P$T0$19")
	.dwattr $C$DW$526, DW_AT_TI_symbol_name("$P$T0$19")
	.dwattr $C$DW$526, DW_AT_type(*$C$DW$T$393)
	.dwattr $C$DW$526, DW_AT_location[DW_OP_addr $P$T0$19]
	.dwattr $C$DW$526, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$526, DW_AT_decl_line(0x9b9)
	.dwattr $C$DW$526, DW_AT_decl_column(0x09)
	.sect	".const:$P$T1$20"
	.clink
	.align	8
	.elfsym	$P$T1$20,SYM_SIZE(32)
$P$T1$20:
	.word	000000000h		; $P$T1$20[0] @ 0
	.space	28

$C$DW$527	.dwtag  DW_TAG_variable, DW_AT_name("$P$T1$20")
	.dwattr $C$DW$527, DW_AT_TI_symbol_name("$P$T1$20")
	.dwattr $C$DW$527, DW_AT_type(*$C$DW$T$394)
	.dwattr $C$DW$527, DW_AT_location[DW_OP_addr $P$T1$20]
	.dwattr $C$DW$527, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$527, DW_AT_decl_line(0xa18)
	.dwattr $C$DW$527, DW_AT_decl_column(0x09)
	.sect	".const:$P$T2$21"
	.clink
	.align	8
	.elfsym	$P$T2$21,SYM_SIZE(32)
$P$T2$21:
	.word	000000000h		; $P$T2$21[0] @ 0
	.space	28

$C$DW$528	.dwtag  DW_TAG_variable, DW_AT_name("$P$T2$21")
	.dwattr $C$DW$528, DW_AT_TI_symbol_name("$P$T2$21")
	.dwattr $C$DW$528, DW_AT_type(*$C$DW$T$394)
	.dwattr $C$DW$528, DW_AT_location[DW_OP_addr $P$T2$21]
	.dwattr $C$DW$528, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$528, DW_AT_decl_line(0xa6f)
	.dwattr $C$DW$528, DW_AT_decl_column(0x09)
	.sect	".neardata", RW
	.align	4
	.elfsym	_uZ1$22,SYM_SIZE(4)
_uZ1$22:
	.word	000000000h		; _uZ1$22 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	_yZ1$23,SYM_SIZE(4)
_yZ1$23:
	.word	000000000h		; _yZ1$23 @ 0

	.sect	".fardata:est_wM_Z1$24", RW
	.clink
	.align	8
	.elfsym	est_wM_Z1$24,SYM_SIZE(12)
est_wM_Z1$24:
	.word	000000000h		; est_wM_Z1$24[0] @ 0
	.space	8

	.sect	".fardata:est_Qs_Z1$25", RW
	.clink
	.align	8
	.elfsym	est_Qs_Z1$25,SYM_SIZE(12)
est_Qs_Z1$25:
	.word	000000000h		; est_Qs_Z1$25[0] @ 0
	.space	8

	.sect	".fardata:est_wL_Z1$26", RW
	.clink
	.align	8
	.elfsym	est_wL_Z1$26,SYM_SIZE(12)
est_wL_Z1$26:
	.word	000000000h		; est_wL_Z1$26[0] @ 0
	.space	8

	.sect	".fardata:est_wM_Z$27", RW
	.clink
	.align	8
	.elfsym	est_wM_Z$27,SYM_SIZE(12)
est_wM_Z$27:
	.word	000000000h		; est_wM_Z$27[0] @ 0
	.space	8

	.sect	".fardata:est_Qs_Z$28", RW
	.clink
	.align	8
	.elfsym	est_Qs_Z$28,SYM_SIZE(12)
est_Qs_Z$28:
	.word	000000000h		; est_Qs_Z$28[0] @ 0
	.space	8

	.sect	".fardata:est_wL_Z$29", RW
	.clink
	.align	8
	.elfsym	est_wL_Z$29,SYM_SIZE(12)
est_wL_Z$29:
	.word	000000000h		; est_wL_Z$29[0] @ 0
	.space	8

	.sect	".fardata:wm_Z$30", RW
	.clink
	.align	8
	.elfsym	wm_Z$30,SYM_SIZE(12)
wm_Z$30:
	.word	000000000h		; wm_Z$30[0] @ 0
	.space	8

	.sect	".fardata:qs_Z$31", RW
	.clink
	.align	8
	.elfsym	qs_Z$31,SYM_SIZE(12)
qs_Z$31:
	.word	000000000h		; qs_Z$31[0] @ 0
	.space	8

	.sect	".fardata:wl_Z$32", RW
	.clink
	.align	8
	.elfsym	wl_Z$32,SYM_SIZE(12)
wl_Z$32:
	.word	000000000h		; wl_Z$32[0] @ 0
	.space	8

	.sect	".fardata:wm_Z1$33", RW
	.clink
	.align	8
	.elfsym	wm_Z1$33,SYM_SIZE(12)
wm_Z1$33:
	.word	000000000h		; wm_Z1$33[0] @ 0
	.space	8

	.sect	".fardata:qs_Z1$34", RW
	.clink
	.align	8
	.elfsym	qs_Z1$34,SYM_SIZE(12)
qs_Z1$34:
	.word	000000000h		; qs_Z1$34[0] @ 0
	.space	8

	.sect	".fardata:wl_Z1$35", RW
	.clink
	.align	8
	.elfsym	wl_Z1$35,SYM_SIZE(12)
wl_Z1$35:
	.word	000000000h		; wl_Z1$35[0] @ 0
	.space	8

	.sect	".fardata:wm_Z$36", RW
	.clink
	.align	8
	.elfsym	wm_Z$36,SYM_SIZE(12)
wm_Z$36:
	.word	000000000h		; wm_Z$36[0] @ 0
	.space	8

	.sect	".fardata:qs_Z$37", RW
	.clink
	.align	8
	.elfsym	qs_Z$37,SYM_SIZE(12)
qs_Z$37:
	.word	000000000h		; qs_Z$37[0] @ 0
	.space	8

	.sect	".fardata:wl_Z$38", RW
	.clink
	.align	8
	.elfsym	wl_Z$38,SYM_SIZE(12)
wl_Z$38:
	.word	000000000h		; wl_Z$38[0] @ 0
	.space	8

	.sect	".fardata:wm_Z1$39", RW
	.clink
	.align	8
	.elfsym	wm_Z1$39,SYM_SIZE(12)
wm_Z1$39:
	.word	000000000h		; wm_Z1$39[0] @ 0
	.space	8

	.sect	".fardata:qs_Z1$40", RW
	.clink
	.align	8
	.elfsym	qs_Z1$40,SYM_SIZE(12)
qs_Z1$40:
	.word	000000000h		; qs_Z1$40[0] @ 0
	.space	8

	.sect	".fardata:wl_Z1$41", RW
	.clink
	.align	8
	.elfsym	wl_Z1$41,SYM_SIZE(12)
wl_Z1$41:
	.word	000000000h		; wl_Z1$41[0] @ 0
	.space	8

	.sect	".neardata", RW
	.align	4
	.elfsym	y_0$42,SYM_SIZE(4)
y_0$42:
	.word	000000000h		; y_0$42 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y_1$43,SYM_SIZE(4)
y_1$43:
	.word	000000000h		; y_1$43 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y_2$44,SYM_SIZE(4)
y_2$44:
	.word	000000000h		; y_2$44 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	uZ1_0$45,SYM_SIZE(4)
uZ1_0$45:
	.word	000000000h		; uZ1_0$45 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	uZ1_1$46,SYM_SIZE(4)
uZ1_1$46:
	.word	000000000h		; uZ1_1$46 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	uZ1_2$47,SYM_SIZE(4)
uZ1_2$47:
	.word	000000000h		; uZ1_2$47 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	uZ2_0$48,SYM_SIZE(4)
uZ2_0$48:
	.word	000000000h		; uZ2_0$48 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	uZ2_1$49,SYM_SIZE(4)
uZ2_1$49:
	.word	000000000h		; uZ2_1$49 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	uZ2_2$50,SYM_SIZE(4)
uZ2_2$50:
	.word	000000000h		; uZ2_2$50 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	a_0$51,SYM_SIZE(4)
a_0$51:
	.word	000000000h		; a_0$51 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	a_1$52,SYM_SIZE(4)
a_1$52:
	.word	000000000h		; a_1$52 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	a_2$53,SYM_SIZE(4)
a_2$53:
	.word	000000000h		; a_2$53 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Tall$54,SYM_SIZE(4)
Tall$54:
	.word	000000000h		; Tall$54 @ 0

	.sect	".fardata:goalZ$55", RW
	.clink
	.align	8
	.elfsym	goalZ$55,SYM_SIZE(12)
goalZ$55:
	.word	000000000h		; goalZ$55[0] @ 0
	.word	000000000h		; goalZ$55[1] @ 32
	.word	000000000h		; goalZ$55[2] @ 64

	.sect	".neardata", RW
	.align	4
	.elfsym	fx$59,SYM_SIZE(4)
fx$59:
	.word	000000000h		; fx$59 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	fy$60,SYM_SIZE(4)
fy$60:
	.word	000000000h		; fy$60 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	fz$61,SYM_SIZE(4)
fz$61:
	.word	000000000h		; fz$61 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	flag_init$62,SYM_SIZE(4)
flag_init$62:
	.bits	0,32			; flag_init$62 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Tall$63,SYM_SIZE(4)
Tall$63:
	.word	000000000h		; Tall$63 @ 0

	.sect	".fardata:goalZ$64", RW
	.clink
	.align	8
	.elfsym	goalZ$64,SYM_SIZE(12)
goalZ$64:
	.word	000000000h		; goalZ$64[0] @ 0
	.word	000000000h		; goalZ$64[1] @ 32
	.word	000000000h		; goalZ$64[2] @ 64

	.bss	fxZ$65,4,4
	.bss	fyZ$66,4,4
	.bss	fzZ$67,4,4
	.sect	".neardata", RW
	.align	4
	.elfsym	fx$68,SYM_SIZE(4)
fx$68:
	.word	000000000h		; fx$68 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	fy$69,SYM_SIZE(4)
fy$69:
	.word	000000000h		; fy$69 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	fz$70,SYM_SIZE(4)
fz$70:
	.word	000000000h		; fz$70 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	flag_init$71,SYM_SIZE(4)
flag_init$71:
	.bits	0,32			; flag_init$71 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Tall$72,SYM_SIZE(4)
Tall$72:
	.word	000000000h		; Tall$72 @ 0

	.sect	".fardata:goalZ$73", RW
	.clink
	.align	8
	.elfsym	goalZ$73,SYM_SIZE(12)
goalZ$73:
	.word	000000000h		; goalZ$73[0] @ 0
	.word	000000000h		; goalZ$73[1] @ 32
	.word	000000000h		; goalZ$73[2] @ 64

	.bss	fxZ$74,4,4
	.bss	fyZ$75,4,4
	.bss	fzZ$76,4,4
	.sect	".neardata", RW
	.align	4
	.elfsym	fx$77,SYM_SIZE(4)
fx$77:
	.word	000000000h		; fx$77 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	fy$78,SYM_SIZE(4)
fy$78:
	.word	000000000h		; fy$78 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	fz$79,SYM_SIZE(4)
fz$79:
	.word	000000000h		; fz$79 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	flag_init$80,SYM_SIZE(4)
flag_init$80:
	.bits	0,32			; flag_init$80 @ 0

motorZ$81:	.usect	".far",12,8
	.sect	".fardata:p1$82", RW
	.clink
	.align	8
	.elfsym	p1$82,SYM_SIZE(12)
p1$82:
	.word	000000000h		; p1$82[0] @ 0
	.word	000000000h		; p1$82[1] @ 32
	.word	000000000h		; p1$82[2] @ 64

	.sect	".neardata", RW
	.align	4
	.elfsym	Lp2h$83,SYM_SIZE(4)
Lp2h$83:
	.word	000000000h		; Lp2h$83 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Lg2h$84,SYM_SIZE(4)
Lg2h$84:
	.word	000000000h		; Lg2h$84 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Phi1$85,SYM_SIZE(4)
Phi1$85:
	.word	000000000h		; Phi1$85 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Phi2$86,SYM_SIZE(4)
Phi2$86:
	.word	000000000h		; Phi2$86 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Phi3$87,SYM_SIZE(4)
Phi3$87:
	.word	000000000h		; Phi3$87 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Phi4$88,SYM_SIZE(4)
Phi4$88:
	.word	000000000h		; Phi4$88 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	flag_init$89,SYM_SIZE(4)
flag_init$89:
	.bits	0,32			; flag_init$89 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y$90,SYM_SIZE(4)
y$90:
	.word	000000000h		; y$90 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ1$91,SYM_SIZE(4)
yZ1$91:
	.word	000000000h		; yZ1$91 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Tall$92,SYM_SIZE(4)
Tall$92:
	.word	000000000h		; Tall$92 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	j$93,SYM_SIZE(4)
j$93:
	.bits	0,32			; j$93 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	k$94,SYM_SIZE(4)
k$94:
	.bits	0,32			; k$94 @ 0

	.bss	Ts_data$95,4,4
	.sect	".neardata", RW
	.align	4
	.elfsym	scale1$96,SYM_SIZE(4)
scale1$96:
	.word	040400000h		; scale1$96 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y$97,SYM_SIZE(4)
y$97:
	.word	000000000h		; y$97 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ1$98,SYM_SIZE(4)
yZ1$98:
	.word	000000000h		; yZ1$98 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Tall$99,SYM_SIZE(4)
Tall$99:
	.word	000000000h		; Tall$99 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	j$100,SYM_SIZE(4)
j$100:
	.bits	0,32			; j$100 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	k$101,SYM_SIZE(4)
k$101:
	.bits	0,32			; k$101 @ 0

	.bss	Ts_data$102,4,4
	.sect	".neardata", RW
	.align	4
	.elfsym	scale2$103,SYM_SIZE(4)
scale2$103:
	.word	040400000h		; scale2$103 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y$104,SYM_SIZE(4)
y$104:
	.word	000000000h		; y$104 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ1$105,SYM_SIZE(4)
yZ1$105:
	.word	000000000h		; yZ1$105 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Tall$106,SYM_SIZE(4)
Tall$106:
	.word	000000000h		; Tall$106 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	j$107,SYM_SIZE(4)
j$107:
	.bits	0,32			; j$107 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	k$108,SYM_SIZE(4)
k$108:
	.bits	0,32			; k$108 @ 0

	.bss	Ts_data$109,4,4
	.sect	".neardata", RW
	.align	4
	.elfsym	scale3$110,SYM_SIZE(4)
scale3$110:
	.word	040400000h		; scale3$110 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	t_all$111,SYM_SIZE(4)
t_all$111:
	.word	000000000h		; t_all$111 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	t$112,SYM_SIZE(4)
t$112:
	.bits	0,32			; t$112 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	a$113,SYM_SIZE(4)
a$113:
	.word	000000000h		; a$113 @ 0

	.bss	aZ1$114,4,4
	.sect	".neardata", RW
	.align	4
	.elfsym	w$115,SYM_SIZE(4)
w$115:
	.word	000000000h		; w$115 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	wZ1$116,SYM_SIZE(4)
wZ1$116:
	.word	000000000h		; wZ1$116 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	z$117,SYM_SIZE(4)
z$117:
	.word	000000000h		; z$117 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	zZ1$118,SYM_SIZE(4)
zZ1$118:
	.word	000000000h		; zZ1$118 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	z_state$119,SYM_SIZE(4)
z_state$119:
	.word	000000000h		; z_state$119 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	t_all$120,SYM_SIZE(4)
t_all$120:
	.word	000000000h		; t_all$120 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	t$121,SYM_SIZE(4)
t$121:
	.bits	0,32			; t$121 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	a$122,SYM_SIZE(4)
a$122:
	.word	000000000h		; a$122 @ 0

	.bss	aZ1$123,4,4
	.sect	".neardata", RW
	.align	4
	.elfsym	w$124,SYM_SIZE(4)
w$124:
	.word	000000000h		; w$124 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	wZ1$125,SYM_SIZE(4)
wZ1$125:
	.word	000000000h		; wZ1$125 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	z$126,SYM_SIZE(4)
z$126:
	.word	000000000h		; z$126 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	zZ1$127,SYM_SIZE(4)
zZ1$127:
	.word	000000000h		; zZ1$127 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	z_state$128,SYM_SIZE(4)
z_state$128:
	.word	000000000h		; z_state$128 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	t_all$129,SYM_SIZE(4)
t_all$129:
	.word	000000000h		; t_all$129 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	t$130,SYM_SIZE(4)
t$130:
	.bits	0,32			; t$130 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	a$131,SYM_SIZE(4)
a$131:
	.word	000000000h		; a$131 @ 0

	.bss	aZ1$132,4,4
	.sect	".neardata", RW
	.align	4
	.elfsym	w$133,SYM_SIZE(4)
w$133:
	.word	000000000h		; w$133 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	wZ1$134,SYM_SIZE(4)
wZ1$134:
	.word	000000000h		; wZ1$134 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	z$135,SYM_SIZE(4)
z$135:
	.word	000000000h		; z$135 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	zZ1$136,SYM_SIZE(4)
zZ1$136:
	.word	000000000h		; zZ1$136 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	z_state$137,SYM_SIZE(4)
z_state$137:
	.word	000000000h		; z_state$137 @ 0

	.sect	".fardata:wm_prev$138", RW
	.clink
	.align	8
	.elfsym	wm_prev$138,SYM_SIZE(12)
wm_prev$138:
	.word	000000000h		; wm_prev$138[0] @ 0
	.space	8

	.sect	".fardata:qm_prev$139", RW
	.clink
	.align	8
	.elfsym	qm_prev$139,SYM_SIZE(12)
qm_prev$139:
	.word	000000000h		; qm_prev$139[0] @ 0
	.space	8

	.sect	".fardata:loop_count_num$140", RW
	.clink
	.align	8
	.elfsym	loop_count_num$140,SYM_SIZE(12)
loop_count_num$140:
	.bits	0,32			; loop_count_num$140[0] @ 0
	.space	8

	.sect	".fardata:sign_invers$141", RW
	.clink
	.align	8
	.elfsym	sign_invers$141,SYM_SIZE(12)
sign_invers$141:
	.bits	1,32			; sign_invers$141[0] @ 0
	.bits	1,32			; sign_invers$141[1] @ 32
	.bits	1,32			; sign_invers$141[2] @ 64

	.sect	".fardata:wm_Z$142", RW
	.clink
	.align	8
	.elfsym	wm_Z$142,SYM_SIZE(12)
wm_Z$142:
	.word	000000000h		; wm_Z$142[0] @ 0
	.space	8

	.sect	".fardata:qm_Z$143", RW
	.clink
	.align	8
	.elfsym	qm_Z$143,SYM_SIZE(12)
qm_Z$143:
	.word	000000000h		; qm_Z$143[0] @ 0
	.space	8

	.sect	".fardata:qs_Z$144", RW
	.clink
	.align	8
	.elfsym	qs_Z$144,SYM_SIZE(12)
qs_Z$144:
	.word	000000000h		; qs_Z$144[0] @ 0
	.space	8

	.sect	".fardata:wl_Z$145", RW
	.clink
	.align	8
	.elfsym	wl_Z$145,SYM_SIZE(12)
wl_Z$145:
	.word	000000000h		; wl_Z$145[0] @ 0
	.space	8

	.sect	".fardata:ql_Z$146", RW
	.clink
	.align	8
	.elfsym	ql_Z$146,SYM_SIZE(12)
ql_Z$146:
	.word	000000000h		; ql_Z$146[0] @ 0
	.space	8

	.sect	".fardata:z_Z$147", RW
	.clink
	.align	8
	.elfsym	z_Z$147,SYM_SIZE(12)
z_Z$147:
	.word	000000000h		; z_Z$147[0] @ 0
	.space	8

	.sect	".fardata:wm_Z1$148", RW
	.clink
	.align	8
	.elfsym	wm_Z1$148,SYM_SIZE(12)
wm_Z1$148:
	.word	000000000h		; wm_Z1$148[0] @ 0
	.space	8

	.sect	".fardata:qm_Z1$149", RW
	.clink
	.align	8
	.elfsym	qm_Z1$149,SYM_SIZE(12)
qm_Z1$149:
	.word	000000000h		; qm_Z1$149[0] @ 0
	.space	8

	.sect	".fardata:qs_Z1$150", RW
	.clink
	.align	8
	.elfsym	qs_Z1$150,SYM_SIZE(12)
qs_Z1$150:
	.word	000000000h		; qs_Z1$150[0] @ 0
	.space	8

	.sect	".fardata:wl_Z1$151", RW
	.clink
	.align	8
	.elfsym	wl_Z1$151,SYM_SIZE(12)
wl_Z1$151:
	.word	000000000h		; wl_Z1$151[0] @ 0
	.space	8

	.sect	".fardata:ql_Z1$152", RW
	.clink
	.align	8
	.elfsym	ql_Z1$152,SYM_SIZE(12)
ql_Z1$152:
	.word	000000000h		; ql_Z1$152[0] @ 0
	.space	8

	.sect	".fardata:z_Z1$153", RW
	.clink
	.align	8
	.elfsym	z_Z1$153,SYM_SIZE(12)
z_Z1$153:
	.word	000000000h		; z_Z1$153[0] @ 0
	.space	8

	.sect	".fardata:wm_Z$154", RW
	.clink
	.align	8
	.elfsym	wm_Z$154,SYM_SIZE(12)
wm_Z$154:
	.word	000000000h		; wm_Z$154[0] @ 0
	.space	8

	.sect	".fardata:qm_Z$155", RW
	.clink
	.align	8
	.elfsym	qm_Z$155,SYM_SIZE(12)
qm_Z$155:
	.word	000000000h		; qm_Z$155[0] @ 0
	.space	8

	.sect	".fardata:qs_Z$156", RW
	.clink
	.align	8
	.elfsym	qs_Z$156,SYM_SIZE(12)
qs_Z$156:
	.word	000000000h		; qs_Z$156[0] @ 0
	.space	8

	.sect	".fardata:wl_Z$157", RW
	.clink
	.align	8
	.elfsym	wl_Z$157,SYM_SIZE(12)
wl_Z$157:
	.word	000000000h		; wl_Z$157[0] @ 0
	.space	8

	.sect	".fardata:ql_Z$158", RW
	.clink
	.align	8
	.elfsym	ql_Z$158,SYM_SIZE(12)
ql_Z$158:
	.word	000000000h		; ql_Z$158[0] @ 0
	.space	8

	.sect	".fardata:n_Z$159", RW
	.clink
	.align	8
	.elfsym	n_Z$159,SYM_SIZE(12)
n_Z$159:
	.word	000000000h		; n_Z$159[0] @ 0
	.space	8

	.sect	".fardata:m_Z$160", RW
	.clink
	.align	8
	.elfsym	m_Z$160,SYM_SIZE(12)
m_Z$160:
	.word	000000000h		; m_Z$160[0] @ 0
	.space	8

	.sect	".fardata:wm_Z1$161", RW
	.clink
	.align	8
	.elfsym	wm_Z1$161,SYM_SIZE(12)
wm_Z1$161:
	.word	000000000h		; wm_Z1$161[0] @ 0
	.space	8

	.sect	".fardata:qm_Z1$162", RW
	.clink
	.align	8
	.elfsym	qm_Z1$162,SYM_SIZE(12)
qm_Z1$162:
	.word	000000000h		; qm_Z1$162[0] @ 0
	.space	8

	.sect	".fardata:qs_Z1$163", RW
	.clink
	.align	8
	.elfsym	qs_Z1$163,SYM_SIZE(12)
qs_Z1$163:
	.word	000000000h		; qs_Z1$163[0] @ 0
	.space	8

	.sect	".fardata:wl_Z1$164", RW
	.clink
	.align	8
	.elfsym	wl_Z1$164,SYM_SIZE(12)
wl_Z1$164:
	.word	000000000h		; wl_Z1$164[0] @ 0
	.space	8

	.sect	".fardata:ql_Z1$165", RW
	.clink
	.align	8
	.elfsym	ql_Z1$165,SYM_SIZE(12)
ql_Z1$165:
	.word	000000000h		; ql_Z1$165[0] @ 0
	.space	8

	.sect	".fardata:n_Z1$166", RW
	.clink
	.align	8
	.elfsym	n_Z1$166,SYM_SIZE(12)
n_Z1$166:
	.word	000000000h		; n_Z1$166[0] @ 0
	.space	8

	.sect	".fardata:m_Z1$167", RW
	.clink
	.align	8
	.elfsym	m_Z1$167,SYM_SIZE(12)
m_Z1$167:
	.word	000000000h		; m_Z1$167[0] @ 0
	.space	8

	.sect	".fardata:counter$168", RW
	.clink
	.align	8
	.elfsym	counter$168,SYM_SIZE(12)
counter$168:
	.bits	0,32			; counter$168[0] @ 0
	.space	8

	.sect	".fardata:Vdc_sum$169", RW
	.clink
	.align	8
	.elfsym	Vdc_sum$169,SYM_SIZE(12)
Vdc_sum$169:
	.word	000000000h		; Vdc_sum$169[0] @ 0
	.space	8

	.sect	".fardata:Vdc_mean$170", RW
	.clink
	.align	8
	.elfsym	Vdc_mean$170,SYM_SIZE(12)
Vdc_mean$170:
	.word	000000000h		; Vdc_mean$170[0] @ 0
	.space	8

	.sect	".const:$P$T3$171"
	.clink
	.align	8
	.elfsym	$P$T3$171,SYM_SIZE(12)
$P$T3$171:
	.word	000000000h		; $P$T3$171[0] @ 0
	.space	8

$C$DW$529	.dwtag  DW_TAG_variable, DW_AT_name("$P$T3$171")
	.dwattr $C$DW$529, DW_AT_TI_symbol_name("$P$T3$171")
	.dwattr $C$DW$529, DW_AT_type(*$C$DW$T$393)
	.dwattr $C$DW$529, DW_AT_location[DW_OP_addr $P$T3$171]
	.dwattr $C$DW$529, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$529, DW_AT_decl_line(0x16bb)
	.dwattr $C$DW$529, DW_AT_decl_column(0x09)
	.sect	".fardata:loop_count_num$172", RW
	.clink
	.align	8
	.elfsym	loop_count_num$172,SYM_SIZE(8)
loop_count_num$172:
	.bits	0,32			; loop_count_num$172[0] @ 0
	.bits	0,32

	.sect	".neardata", RW
	.align	4
	.elfsym	loop_count_num$173,SYM_SIZE(4)
loop_count_num$173:
	.bits	0,32			; loop_count_num$173 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	loop_count_num$174,SYM_SIZE(4)
loop_count_num$174:
	.bits	0,32			; loop_count_num$174 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Xntw$175,SYM_SIZE(4)
Xntw$175:
	.word	000000000h		; Xntw$175 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Zntw$176,SYM_SIZE(4)
Zntw$176:
	.word	000000000h		; Zntw$176 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	I6x$177,SYM_SIZE(4)
I6x$177:
	.word	000000000h		; I6x$177 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	I6y$178,SYM_SIZE(4)
I6y$178:
	.word	000000000h		; I6y$178 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	I6z$179,SYM_SIZE(4)
I6z$179:
	.word	000000000h		; I6z$179 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	m6$180,SYM_SIZE(4)
m6$180:
	.word	000000000h		; m6$180 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	X6$181,SYM_SIZE(4)
X6$181:
	.word	000000000h		; X6$181 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	Z6$182,SYM_SIZE(4)
Z6$182:
	.word	000000000h		; Z6$182 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y$183,SYM_SIZE(4)
y$183:
	.word	000000000h		; y$183 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ1$184,SYM_SIZE(4)
yZ1$184:
	.word	000000000h		; yZ1$184 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ$185,SYM_SIZE(4)
yZ$185:
	.word	000000000h		; yZ$185 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y$186,SYM_SIZE(4)
y$186:
	.word	000000000h		; y$186 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ1$187,SYM_SIZE(4)
yZ1$187:
	.word	000000000h		; yZ1$187 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ$188,SYM_SIZE(4)
yZ$188:
	.word	000000000h		; yZ$188 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y$189,SYM_SIZE(4)
y$189:
	.word	000000000h		; y$189 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ1$190,SYM_SIZE(4)
yZ1$190:
	.word	000000000h		; yZ1$190 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ$191,SYM_SIZE(4)
yZ$191:
	.word	000000000h		; yZ$191 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y$192,SYM_SIZE(4)
y$192:
	.word	000000000h		; y$192 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ1$193,SYM_SIZE(4)
yZ1$193:
	.word	000000000h		; yZ1$193 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ$194,SYM_SIZE(4)
yZ$194:
	.word	000000000h		; yZ$194 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y$195,SYM_SIZE(4)
y$195:
	.word	000000000h		; y$195 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ1$196,SYM_SIZE(4)
yZ1$196:
	.word	000000000h		; yZ1$196 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ$197,SYM_SIZE(4)
yZ$197:
	.word	000000000h		; yZ$197 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	y$198,SYM_SIZE(4)
y$198:
	.word	000000000h		; y$198 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ1$199,SYM_SIZE(4)
yZ1$199:
	.word	000000000h		; yZ1$199 @ 0

	.sect	".neardata", RW
	.align	4
	.elfsym	yZ$200,SYM_SIZE(4)
yZ$200:
	.word	000000000h		; yZ$200 @ 0

;	C:\ti\bin\opt6x.exe C:\\Users\\TATSUDA\\AppData\\Local\\Temp\\{ED7B7745-D170-400E-9978-930F61E59C7B} C:\\Users\\TATSUDA\\AppData\\Local\\Temp\\{8F64DE1C-77DF-4938-B07A-CC5B9562899E} 
	.sect	".text"
	.clink
	.global	backward_diff

$C$DW$530	.dwtag  DW_TAG_subprogram, DW_AT_name("backward_diff")
	.dwattr $C$DW$530, DW_AT_low_pc(backward_diff)
	.dwattr $C$DW$530, DW_AT_high_pc(0x00)
	.dwattr $C$DW$530, DW_AT_TI_symbol_name("backward_diff")
	.dwattr $C$DW$530, DW_AT_external
	.dwattr $C$DW$530, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$530, DW_AT_TI_begin_file("current_control_ver2_new.c")
	.dwattr $C$DW$530, DW_AT_TI_begin_line(0x1026)
	.dwattr $C$DW$530, DW_AT_TI_begin_column(0x07)
	.dwattr $C$DW$530, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$530, DW_AT_decl_line(0x1026)
	.dwattr $C$DW$530, DW_AT_decl_column(0x07)
	.dwattr $C$DW$530, DW_AT_TI_max_frame_size(0x08)
	.dwattr $C$DW$530, DW_AT_frame_base[DW_OP_breg31 8]
	.dwattr $C$DW$530, DW_AT_TI_skeletal
	.dwpsn	file "current_control_ver2_new.c",line 4135,column 1,is_stmt,address backward_diff,isa 0
$C$DW$531	.dwtag  DW_TAG_formal_parameter, DW_AT_name("x")
	.dwattr $C$DW$531, DW_AT_TI_symbol_name("x")
	.dwattr $C$DW$531, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$531, DW_AT_location[DW_OP_reg4]
$C$DW$532	.dwtag  DW_TAG_formal_parameter, DW_AT_name("xZ")
	.dwattr $C$DW$532, DW_AT_TI_symbol_name("xZ")
	.dwattr $C$DW$532, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$532, DW_AT_location[DW_OP_reg20]
$C$DW$533	.dwtag  DW_TAG_formal_parameter, DW_AT_name("dt")
	.dwattr $C$DW$533, DW_AT_TI_symbol_name("dt")
	.dwattr $C$DW$533, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$533, DW_AT_location[DW_OP_reg6]

;******************************************************************************
;* FUNCTION NAME: backward_diff                                               *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,B0,B1,B2,B3,B4,B5,B6,  *
;*                           B7,B8,B9,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,*
;*                           A26,A27,A28,A29,A30,A31,B16,B17,B18,B19,B20,B21, *
;*                           B22,B23,B24,B25,B26,B27,B28,B29,B30,B31          *
;*   Regs Used         : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,B0,B1,B2,B3,B4,B5,B6,  *
;*                           B7,B8,B9,DP,SP,A16,A17,A18,A19,A20,A21,A22,A23,  *
;*                           A24,A25,A26,A27,A28,A29,A30,A31,B16,B17,B18,B19, *
;*                           B20,B21,B22,B23,B24,B25,B26,B27,B28,B29,B30,B31  *
;*   Local Frame Size  : 0 Args + 0 Auto + 4 Save = 4 byte                    *
;******************************************************************************
backward_diff:
;** --------------------------------------------------------------------------*
$C$DW$534	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$534, DW_AT_low_pc(0x00)
	.dwattr $C$DW$534, DW_AT_TI_call
	.dwattr $C$DW$534, DW_AT_TI_return
           CALLRET .S1     __c6xabi_divf     ; |4136| 
           FSUBSP  .L1X    A4,B4,A4          ; |4136| 
           MV      .L2X    A6,B4             ; |4136| 
	.dwpsn	file "current_control_ver2_new.c",line 4137,column 1,is_stmt,isa 0
           NOP             3
$C$RL0:    ; CALL-RETURN OCCURS {__c6xabi_divf} 0  ; |4136| 
	.dwattr $C$DW$530, DW_AT_TI_end_file("current_control_ver2_new.c")
	.dwattr $C$DW$530, DW_AT_TI_end_line(0x1029)
	.dwattr $C$DW$530, DW_AT_TI_end_column(0x01)
	.dwendtag $C$DW$530

	.sect	".text"
	.clink
	.global	VconPI5Axis

$C$DW$535	.dwtag  DW_TAG_subprogram, DW_AT_name("VconPI5Axis")
	.dwattr $C$DW$535, DW_AT_low_pc(VconPI5Axis)
	.dwattr $C$DW$535, DW_AT_high_pc(0x00)
	.dwattr $C$DW$535, DW_AT_TI_symbol_name("VconPI5Axis")
	.dwattr $C$DW$535, DW_AT_external
	.dwattr $C$DW$535, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$535, DW_AT_TI_begin_file("current_control_ver2_new.c")
	.dwattr $C$DW$535, DW_AT_TI_begin_line(0xab8)
	.dwattr $C$DW$535, DW_AT_TI_begin_column(0x07)
	.dwattr $C$DW$535, DW_AT_decl_file("current_control_ver2_new.c")
	.dwattr $C$DW$535, DW_AT_decl_line(0xab8)
	.dwattr $C$DW$535, DW_AT_decl_column(0x07)
	.dwattr $C$DW$535, DW_AT_TI_max_frame_size(0x00)
	.dwattr $C$DW$535, DW_AT_frame_base[DW_OP_breg31 0]
	.dwattr $C$DW$535, DW_AT_TI_skeletal
	.dwpsn	file "current_control_ver2_new.c",line 2745,column 1,is_stmt,address VconPI5Axis,isa 0
$C$DW$536	.dwtag  DW_TAG_formal_parameter, DW_AT_name("u")
	.dwattr $C$DW$536, DW_AT_TI_symbol_name("u")
	.dwattr $C$DW$536, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$536, DW_AT_location[DW_OP_reg4]
$C$DW$537	.dwtag  DW_TAG_formal_parameter, DW_AT_name("Kp")
	.dwattr $C$DW$537, DW_AT_TI_symbol_name("Kp")
	.dwattr $C$DW$537, DW_AT_type(*$C$DW$T$143)
	.dwattr $C$DW$537, DW_AT_location[DW_OP_reg20]
$C$DW$538	.dwtag  DW_TAG_formal_parameter, DW_AT_name("Ki")
	.dwattr $C$DW$538, DW_AT_TI_symbol_name("Ki")
	.dwattr $C$DW$538, DW_AT_type(*$C$DW$T$143)
	.dwattr $C$DW$538, DW_AT_location[DW_OP_reg6]

;******************************************************************************
;* FUNCTION NAME: VconPI5Axis                                                 *
;*                                                                            *
;*   Regs Modified     : A3,A4,B4,B5,B6                                       *
;*   Regs Used         : A3,A4,A6,B3,B4,B5,B6,DP                              *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                    *
;******************************************************************************
VconPI5Axis:
;** --------------------------------------------------------------------------*
           MVKL    .S1     0x3903126f,A3
           MVKH    .S1     0x3903126f,A3
           MPYSP   .M1     A3,A6,A3          ; |2749| 
           LDW     .D2T2   *+DP(_uZ1$22),B5  ; |2749| 
           STW     .D2T1   A4,*+DP(_uZ1$22)  ; |2751| 
           NOP             2
           FADDSP  .L2X    A3,B4,B6          ; |2749| 
           MPYSP   .M2     B4,B5,B4          ; |2749| 
           LDW     .D2T2   *+DP(_yZ1$23),B5  ; |2749| 
           MPYSP   .M2X    A4,B6,B6          ; |2749| 
           NOP             4
           FSUBSP  .L2     B6,B4,B4          ; |2749| 
           NOP             1
$C$DW$539	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$539, DW_AT_low_pc(0x00)
	.dwattr $C$DW$539, DW_AT_TI_return
           RET     .S2     B3                ; |2753| 
           FADDSP  .L2     B5,B4,B4          ; |2749| 
           NOP             3
	.dwpsn	file "current_control_ver2_new.c",line 2753,column 1,is_stmt,isa 0

           STW     .D2T2   B4,*+DP(_yZ1$23)  ; |2750| 
||         MV      .L1X    B4,A4             ; |2752| 

           ; BRANCH OCCURS {B3}              ; |2753| 
	.dwattr $C$DW$535, DW_AT_TI_end_file("current_control_ver2_new.c")
	.dwattr $C$DW$535, DW_AT_TI_end_line(0xac1)
	.dwattr $C$DW$535, DW_AT_TI_end_column(0x01)
	.dwendtag $C$DW$535

