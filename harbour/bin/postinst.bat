@rem
@rem $Id$
@rem

@echo off

rem ---------------------------------------------------------------
rem Copyright 2009 Viktor Szakats (harbour.01 syenar.hu)
rem Copyright 2003 Przemyslaw Czerpak (druzus / at / priv.onet.pl)
rem simple script run after Harbour make install to finish install
rem process
rem
rem See COPYING for licensing terms.
rem ---------------------------------------------------------------

echo Generating %HB_BIN_INSTALL%\hbmk.cfg...
echo # Harbour Make configuration> %HB_BIN_INSTALL%\hbmk.cfg
echo # Generated by Harbour build process>> %HB_BIN_INSTALL%\hbmk.cfg
echo arch=%HB_ARCHITECTURE%>> %HB_BIN_INSTALL%\hbmk.cfg
echo comp=%HB_COMPILER%>> %HB_BIN_INSTALL%\hbmk.cfg
echo.>> %HB_BIN_INSTALL%\hbmk.cfg
echo libpaths=../contrib/%%{hb_name}>> %HB_BIN_INSTALL%\hbmk.cfg
echo libpaths=../contrib/rddsql/%%{hb_name}>> %HB_BIN_INSTALL%\hbmk.cfg
echo libpaths=../addins/%%{hb_name}>> %HB_BIN_INSTALL%\hbmk.cfg
echo libpaths=../examples/%%{hb_name}>> %HB_BIN_INSTALL%\hbmk.cfg

rem ; Post-build installation
set _HB_COPYCMD=%COPYCMD%
set COPYCMD=/Y
if not "%HB_INSTALL_PREFIX%" == "" copy ChangeLog* "%HB_INSTALL_PREFIX%\" > nul
if not "%HB_INSTALL_PREFIX%" == "" copy COPYING    "%HB_INSTALL_PREFIX%\" > nul
if not "%HB_INSTALL_PREFIX%" == "" copy ERRATA     "%HB_INSTALL_PREFIX%\" > nul
if not "%HB_INSTALL_PREFIX%" == "" copy INSTALL    "%HB_INSTALL_PREFIX%\" > nul
if not "%HB_INSTALL_PREFIX%" == "" copy TODO       "%HB_INSTALL_PREFIX%\" > nul
set COPYCMD=%_HB_COPYCMD%
set _HB_COPYCMD=

goto INST_%HB_ARCHITECTURE%

:INST_WIN
:INST_WCE

   rem Windows post install part

   if not "%OS%" == "Windows_NT" echo This Harbour build script requires Windows NT or upper.
   if not "%OS%" == "Windows_NT" goto END

   if "%HB_COMPILER%" == "mingw"    set HB_DYNLIB=yes
   if "%HB_COMPILER%" == "mingw64"  set HB_DYNLIB=yes
   if "%HB_COMPILER%" == "mingwarm" set HB_DYNLIB=yes
   if "%HB_COMPILER%" == "cygwin"   set HB_DYNLIB=yes

   if not "%HB_DYNLIB%" == "yes" goto _SKIP_DLL_BIN

      call %~dp0hb-mkdyn.bat

      setlocal
      if "%HB_BIN_COMPILE%" == "" set HB_BIN_COMPILE=%HB_BIN_INSTALL%
      if exist "%HB_BIN_INSTALL%\*.dll" (
         %HB_BIN_COMPILE%\hbmk2 -q0 -lng=en-EN -shared -o%HB_BIN_INSTALL%\hbrun-dll    %~dp0..\utils\hbrun\hbrun.hbp
         %HB_BIN_COMPILE%\hbmk2 -q0 -lng=en-EN -shared -o%HB_BIN_INSTALL%\hbmk2-dll    %~dp0..\utils\hbmk2\hbmk2.hbp
         %HB_BIN_COMPILE%\hbmk2 -q0 -lng=en-EN -shared -o%HB_BIN_INSTALL%\hbtest-dll   %~dp0..\utils\hbtest\hbtest.hbp
         %HB_BIN_COMPILE%\hbmk2 -q0 -lng=en-EN -shared -o%HB_BIN_INSTALL%\hbi18n-dll   %~dp0..\utils\hbi18n\hbi18n.hbp
         %HB_BIN_COMPILE%\hbmk2 -q0 -lng=en-EN -shared -o%HB_BIN_INSTALL%\hbformat-dll %~dp0..\utils\hbformat\hbformat.hbp
      )
      endlocal

   :_SKIP_DLL_BIN

   rem ; We build this here, because GNU Make wouldn't add the icon.
   setlocal
   if "%HB_BIN_COMPILE%" == "" set HB_BIN_COMPILE=%HB_BIN_INSTALL%
   %HB_BIN_COMPILE%\hbmk2 -q0 -lng=en-EN -o%HB_BIN_INSTALL%\hbrun %~dp0..\utils\hbrun\hbrun.hbp
   endlocal

   if "%HB_BUILD_IMPLIB%" == "yes" call %~dp0hb-mkimp.bat

   goto END

:INST_DOS

   rem DOS post install part
   goto END

:INST_
:END
