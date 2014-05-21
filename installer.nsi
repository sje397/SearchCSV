; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory,
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install example2.nsi into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "SearchCSVInstall"

; The file to write
OutFile "SearchCSVInstall.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\FutureMusic\SearchCSV"

; Registry key to check for directory (so if you install again, it will
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\FutureMusic\SearchCSV" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "SearchCSV (required)"

  SectionIn RO

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  ; Put file there
  !echo "$%QTDIR%"
  File "..\build-SearchCSV-Desktop_Qt_5_3_0_MinGW_32bit-Release\release\SearchCSV.exe"
  File "logo.ico"
  File "$%QTDIR%\bin\Qt5Core.dll"
  File "$%QTDIR%\bin\Qt5Gui.dll"
  File "$%QTDIR%\bin\Qt5Widgets.dll"
  File "$%QTDIR%\bin\Qt5Network.dll"

  File "$%QTDIR%\bin\libgcc_s_dw2-1.dll"
  File "$%QTDIR%\bin\libwinpthread-1.dll"
  File "$%QTDIR%\bin\libstdc++-6.dll"
  File "$%QTDIR%\bin\icuin52.dll"
  File "$%QTDIR%\bin\icudt52.dll"
  File "$%QTDIR%\bin\icuuc52.dll"

  ; plugins
  SetOutPath $INSTDIR\platforms
  File "$%QTDIR%\plugins\platforms\qminimal.dll"
  File "$%QTDIR%\plugins\platforms\qwindows.dll"

  ; Write the installation path into the registry
  WriteRegStr HKLM "SOFTWARE\SearchCSV" "Install_Dir" "$INSTDIR"

  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SearchCSV" "DisplayName" "SearchCSV"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SearchCSV" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SearchCSV" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SearchCSV" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Future Music"
  CreateShortCut "$SMPROGRAMS\Future Music\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\Future Music\SearchCSV.lnk" "$INSTDIR\SearchCSV.exe" "" "$INSTDIR\SearchCSV.exe" 0

SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"

  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SearchCSV"
  DeleteRegKey HKLM "SOFTWARE\FutureMusic"

  ; Remove files and uninstaller
  Delete "$INSTDIR\*"
  ;Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Future Music\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Future Music\"
  RMDir "$INSTDIR"

SectionEnd
