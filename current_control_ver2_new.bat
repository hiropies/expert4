@rem *********************
@rem Makefile for c6657
@rem *********************


@rem *** Path ***
@set PEOS_PATH="C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05"


@rem *** Target File ***
@set TARGET=current_control_ver2_new
@set GOAL=target.btbl


@rem *** Tools Name ***
@set COMPILER_DIR="C:\ti\bin"
@set CC=%COMPILER_DIR%\cl6x
@set LD=%COMPILER_DIR%\cl6x
@set HEX=%COMPILER_DIR%\hex6x
@set NM=%COMPILER_DIR%\nm6x
@set MAKE_DEF=make_def
@set MAKE_FUNCDEF=make_funcdef
@set MAKE_SBL=c6657_make_sbl
@set MAKE_FUNCSBL=c6657_make_funcsbl
@set MAKE_TYP=make_typ


@rem *** Objects & Libraries ***
@set OBJS=^
	current_control_ver2_new.obj ^
	enc.obj

@set LIBS="C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\lib\Main.obj" ^
 "C:\Program Files (x86)\Myway Plus\PE-ViewX\pe-viewx\PEOS\c6657\3_05\lib\mwio4.lib" ^
 "C:\ti\mathlib_c66x_3_0_1_1\lib\mathlib.ae66" ^
 "C:\ti\bin\..\lib\rts6600_elf.lib" ^
 "C:\ti\pdk_C6657_1_1_2_6\packages\ti\csl\lib\ti.csl.ae66" ^
 "C:\ti\pdk_C6657_1_1_2_6\packages\ti\csl\lib\ti.csl.intc.ae66"


@rem *** Others ***
@set SYMBOL=^
	current_control_ver2_new.@sbl ^
	 + enc.@sbl ^
 

@set SYMBOL_CLEAR=^
	current_control_ver2_new.@sbl ^
	enc.@sbl ^
 

@set FUNCSYMBOL=^
	current_control_ver2_new.@funcsbl ^
	 + enc.@funcsbl ^
 

@set FUNCSYMBOL_CLEAR=^
	current_control_ver2_new.@funcsbl ^
	enc.@funcsbl ^
 


@rem *** Flags ***
@set BASE_CFLAGS=-mv6600 --display_error_number --preproc_with_compile --diag_warning=225 --abi=eabi -O2 -i"D:/Desktop/abe??/001_circle_P" -i"C:/Program Files (x86)/Myway Plus/PE-ViewX/pe-viewx/PEOS/c6657/3_05/inc" -i"C:/ti/bin/../include" -i"C:/ti/pdk_C6657_1_1_2_6/packages/ti/csl" -i"C:/ti/mathlib_c66x_3_0_1_1/inc" -i"C:/ti/mathlib_c66x_3_0_1_1/packages" -i"C:/ti/pdk_C6657_1_1_2_6/packages/ti/csl/../.."
@set CFLAGS=%BASE_CFLAGS% -k
@set ASMFLAGS=%BASE_CFLAGS%
@set LDFLAGS=--run_linker --rom_model --map_file=%TARGET%.map -l=%LIBS% -l=%TARGET%.cmd --zero_init=off 
@set HEXFLAGS=-m3 --memwidth=8


@rem *** Delete ***
@echo off
del %OBJS% %TARGET%.out target.btbl %TARGET%.typ %TARGET%.map %TARGET%.def %TARGET%.funcdef %TARGET%.tmp@@ %TARGET%.functmp@@ %TARGET%.all_sym %SYMBOL_CLEAR% %FUNCSYMBOL_CLEAR% 2> nul
@echo on


@rem *** Compile ***
%CC% %CFLAGS% current_control_ver2_new.c
@echo off & if errorlevel 1 goto ERR
@echo on
%MAKE_SBL% current_control_ver2_new.asm current_control_ver2_new.@sbl
@echo off & if errorlevel 1 goto ERR
@echo on
%MAKE_FUNCSBL% current_control_ver2_new.asm current_control_ver2_new.@funcsbl
@echo off & if errorlevel 1 goto ERR
del current_control_ver2_new.asm 2> nul
@echo on


%CC% %CFLAGS% enc.c
@echo off & if errorlevel 1 goto ERR
@echo on
%MAKE_SBL% enc.asm enc.@sbl
@echo off & if errorlevel 1 goto ERR
@echo on
%MAKE_FUNCSBL% enc.asm enc.@funcsbl
@echo off & if errorlevel 1 goto ERR
del enc.asm 2> nul
@echo on


@rem *** Link ***
@echo off
copy %SYMBOL%  %TARGET%.tmp@@ > nul
@echo on
@echo off
copy %FUNCSYMBOL%  %TARGET%.functmp@@ > nul
@echo on
%MAKE_TYP% %TARGET%.tmp@@ current_control_ver2_new.typ
@echo off & if errorlevel 1 goto ERR
@echo on
%LD% -o %OBJS% %LDFLAGS% --output_file=%TARGET%.out
@echo off & if errorlevel 1 goto ERR
@echo on


@rem *** Generates *.def ***
%HEX% -order L linker_image.rmd %TARGET%.out
@echo off & if errorlevel 1 goto ERR
@echo on
%NM% -a %TARGET%.out > %TARGET%.all_sym
@echo off & if errorlevel 1 goto ERR
@echo on
%MAKE_DEF% %TARGET%.typ %PEOS_PATH%\config\Type.cfg %TARGET%.all_sym
@echo off & if errorlevel 1 goto ERR
@echo on
%MAKE_FUNCDEF% %TARGET%.functmp@@ %TARGET%.all_sym
@echo off & if errorlevel 1 goto ERR
del %OBJS% %TARGET%.typ %TARGET%.tmp@@ %TARGET%.functmp@@ %TARGET%.all_sym %SYMBOL_CLEAR% %FUNCSYMBOL_CLEAR% 2> nul


@echo off
exit 0


@rem ** Error Process ***
:ERR
@echo off
del %OBJS% %TARGET%.typ %TARGET%.tmp@@ %TARGET%.functmp@@ %TARGET%.all_sym %SYMBOL_CLEAR% %FUNCSYMBOL_CLEAR% 2> nul
exit 1
