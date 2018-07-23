/*
///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
// FileName	: SO3Setup.nsi
// Creator	: Liu Bing
// Date		: 2008-08-27
// Comment	: JX3Benchmark安装包的NSIS脚本。包括静默安装物理引擎，dx9，拷贝VC运行库
//
///////////////////////////////////////////////////////////////
*/
; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "JX3Benchmark"
!define PRODUCT_VERSION "1.1"
!define PRODUCT_PUBLISHER "Kingsoft, Inc."
!define PRODUCT_WEB_SITE "http://www.kingsoft.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\JX3Benchmark.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_EXE_FILE "JX3Benchmark.exe"
!define UPDATER_EXE_FILE "JxUpdater.exe"

; MUI 1.67 compatible ------
!include "MUI.nsh"
SetCompressor LZMA
;不同的压缩方式
;SetCompressor ZLIB
;SetCompressor BZIP2
SetOverwrite ifnewer

/*ReserveFile "${NSISDIR}\Plugins\InstallOptions.dll"
ReserveFile ".\resource\JX3.ico"
ReserveFile ".\resource\JX3-wizard.bmp"
ReserveFile ".\resource\JX3-head.bmp"
ReserveFile ".\Resource\Licence.txt"*/

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON ".\resource\JX3.ico"
!define MUI_UNICON ".\resource\JX3.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP ".\resource\JX3-wizard.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP ".\resource\JX3-wizard.bmp"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP ".\resource\JX3-head.bmp"
BrandingText "　金山软件：西山居"

;!define MUI_PAGE_CUSTOMFUNCTION_PRE ChangeWinTitle

!define MUI_WELCOMEPAGE_TITLE "\r\n　　欢迎使用 ${PRODUCT_NAME} ${PRODUCT_VERSION}"
!define MUI_WELCOMEPAGE_TEXT "\r\n　　$(^Name) 是一个由西山居工作室制作的性能测试软件，属于体验改善计划的一部分。它用于测试引擎的显卡兼容性及客户端显示效率。它会展示您的电脑在不同设置下可以达到的运行效果，同时收集您的硬件数据供工作室参考，以帮助进一步改善产品。\
\r\n\r\n\r\n\r\n\r\n      这个向导将引导您在电脑上安装 $(^Name) ，需要继续安装请点击 [下一步(N)]，退出安装请点击 [取消(C)]。"

!define MUI_PAGE_HEADER_TEXT "许可协议与隐私声明"
!define MUI_PAGE_HEADER_SUBTEXT "　　在安装 $(^Name) 之前，请仔细阅读下面的$\n“许可协议”和“隐私声明”。"

!define MUI_LICENSEPAGE_TEXT_TOP "请按[Pagn]阅读“许可协议”和“隐私声明”的详细内容。"
!define MUI_LICENSEPAGE_TEXT_BOTTOM "如果您同意“许可协议”和“隐私声明”里的内容，请点击 [我接受 (I)] 继续安装。退出安装请点击 [取消(C)]。"

!define MUI_COMPONENTSPAGE_TEXT_TOP "请勾选您想要安装的组件，并接触勾选您不希望安装的组件。单击[下一步(N)]继续。"

!define MUI_DIRECTORYPAGE_TEXT_TOP " $(^Name) 将被安装在下列文件夹。想要安装到其他文件夹，请点击 [浏览 (B)] 并选择。继续安装请点击 [下一步(N)]，退出安装请点击 [取消(C)]。"

!define MUI_FINISHPAGE_TITLE "已经成功安装 $(^Name) "
!define MUI_FINISHPAGE_TEXT "您已经成功安装 $(^Name) 。"

!define MUI_FINISHPAGE_RUN
!define MUI_FINISHPAGE_RUN_FUNCTION StartProgram
!define MUI_FINISHPAGE_RUN_TEXT "立即运行JX3Benchmark"

;!define MUI_PAGE_CUSTOMFUNCTION_SHOW ChangeFONT
; Welcome page
!insertmacro MUI_PAGE_WELCOME

; License page
!insertmacro MUI_PAGE_LICENSE ".\Resource\Licence.txt"

;!define MUI_PAGE_HEADER_SUBTEXT  "　　请选择您想要安装的 $(^Name) 的所有组件。"
;!insertmacro MUI_PAGE_COMPONENTS

!define MUI_PAGE_HEADER_SUBTEXT  "　　请选择 $(^Name) 的安装文件夹。"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_PAGE_HEADER_SUBTEXT  "　　正在安装 $(^Name) ，该过程可能需要几分钟，请稍候。"
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "SimpChinese"

; MUI end ------
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile ".\${PRODUCT_NAME}SetUp_${PRODUCT_VERSION}.exe"
InstallDir "$PROGRAMFILES\Kingsoft\${PRODUCT_NAME}"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails hide

/*InstType "345678"
InstType "34567642"
Section "主程序" SEC_PROGRAM
SectionIn RO

SectionEnd

Section "IE右键菜单" SEC_IEMENUEXT
messagebox mb_ok ""

SectionEnd

SectionGroup /e "快捷方式" SECGRP_SHORTCUT

Section "桌面" SEC_DESKTOP
InstTypeSetText SECGRP_SHORTCUT "123445"
SectionEnd
Section "开始菜单" SEC_SMPROGRAMS

SectionEnd
SectionGroupEnd*/


Section "主程序" MAIN_SEC
  /*messagebox mb_ok "即将开始 $(^Name) 文件复制与组件安装。$\n请注意以下安装提示：\
$\n1、安装前建议关闭游戏等所有大型应用程序。\
$\n2、安装完成需要3-5分钟时间，这将视你的机器性能而定。\
$\n3、安装过程中请不要点击组件的“取消”按钮，否则将导致程序安装不全，无法运行。\
$\n4、如果不小心点击“取消”按钮，请尝试重新安装解决。"*/
  ;SectionIn RO
  
  SetOutPath $INSTDIR
  SetDetailsPrint Both
  
  File /a /r '.\Resource\FilesToCopy\*.*'

  DetailPrint "正在安装物理引擎，安装过程中请不要点击“取消”按钮..."
  SetDetailsPrint None
  ExecWait '"$INSTDIR\3rdParty\PhysX_6.12.02_SystemSoftware.exe" /qb'
  SetDetailsPrint Both
  DetailPrint "物理引擎安装完成...100%"
  DetailPrint "正在安装DirectX9，请稍候..."
  SetDetailsPrint None
  ExecWait '"$INSTDIR\3rdParty\DX9\DXSetup.exe" /Silent'
  
  SetDetailsPrint Both
  DetailPrint "DirectX9安装完成...100%"
  DetailPrint "正在安装VC8运行库，安装过程中请不要点击“取消”按钮..."
  SetDetailsPrint None
  ExecWait '"$INSTDIR\3rdParty\vcredist_x86.exe" /Q'
  
  SetDetailsPrint Both
  DetailPrint "VC8运行库安装完成...100%"
SectionEnd

Section "桌面" DESK_SHORTCUT_SEC
  CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\${PRODUCT_EXE_FILE}"
SectionEnd

Section "开始菜单" STARTMENU_SHORTCUT_SEC
  CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\${PRODUCT_EXE_FILE}"
SectionEnd

/*Section "快捷栏" QUICK_START_BAR_SEC
  CreateShortCut "$QUICKLAUNCH\${PRODUCT_NAME}.lnk" "$INSTDIR\${PRODUCT_EXE_FILE}"
SectionEnd*/

Section -AdditionalIcons
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\${PRODUCT_EXE_FILE}"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "Path" "$INSTDIR\"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\${PRODUCT_EXE_FILE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

Section Uninstall
  Delete "$QUICKLAUNCH\${PRODUCT_NAME}.lnk"
  Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
  RMDir /r "$SMPROGRAMS\${PRODUCT_NAME}"
  
  Delete "$INSTDIR\ippacw7-5.1.dll"
  Delete "$INSTDIR\ippcc-5.1.dll"
  Delete "$INSTDIR\ippccw7-5.1.dll"
  Delete "$INSTDIR\ippcore-5.1.dll"
  Delete "$INSTDIR\ippi-5.1.dll"
  Delete "$INSTDIR\ippiw7-5.1.dll"
  Delete "$INSTDIR\ipps-5.1.dll"
  Delete "$INSTDIR\ippsw7-5.1.dll"
  Delete "$INSTDIR\ippvc-5.1.dll"
  Delete "$INSTDIR\ippvcw7-5.1.dll"
  Delete "$INSTDIR\IPPVideo.dll"
  Delete "$INSTDIR\JX3Benchmark.exe"
  Delete "$INSTDIR\KG3DEngine.dll"
  Delete "$INSTDIR\KG3DSound.dll"
  Delete "$INSTDIR\libguide40.dll"
  Delete "$INSTDIR\Lua5.dll"
  Delete "$INSTDIR\smoothed.rec"
  Delete "$INSTDIR\usedresource.txt"
  Delete "$INSTDIR\BenchmarkConfig.ini"
  Delete "$INSTDIR\config.ini"
  Delete "$INSTDIR\data.pak"
  Delete "$INSTDIR\Engine_Lua5.dll"
  
  Delete "$INSTDIR\uninst.exe"
  RMDir /r "$INSTDIR\logs"
  RMDir /r "$INSTDIR\3rdParty"
  
  RMdir "$INSTDIR"
  
  ;RMDir /r "$INSTDIR"
  
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${MAIN_SEC} "$(^Name)主程序所需要的所有组件，必须安装。"
  !insertmacro MUI_DESCRIPTION_TEXT ${SHORTCUT_GROUP_SEC} "所有可选快捷启动方式。"
  !insertmacro MUI_DESCRIPTION_TEXT ${STARTMENU_SHORTCUT_SEC} "在开始菜单中建立$(^Name)启动与卸载的链接。"
  !insertmacro MUI_DESCRIPTION_TEXT ${DESK_SHORTCUT_SEC} "在桌面建立$(^Name)的启动链接。"
  !insertmacro MUI_DESCRIPTION_TEXT ${QUICK_START_BAR_SEC} "在快捷栏建立$(^Name)的启动链接"
!insertmacro MUI_FUNCTION_DESCRIPTION_END

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从你的计算机移除。"
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "你确实要完全移除 $(^Name)？" IDYES +2
  Abort
FunctionEnd

Function StartProgram
  ExecShell "open" "$INSTDIR\${PRODUCT_EXE_FILE}"
FunctionEnd

/*Function ChangeWinTitle
  SendMessage $HWNDPARENT ${WM_SETTEXT} 0 "STR:${PRODUCT_NAME} ${PRODUCT_VERSION}"
FunctionEnd

Function ChangeFONT
  GetDlgItem $0 $MUI_HWND 1201
  createFont $1 "Tahoma" "16" "200" /ITALIC # /UNDERLINE /STRIKE
  SendMessage $0 ${WM_SETFONT} $1 0
  
  GetDlgItem $0 $MUI_HWND 1202
  createFont $1 "Tahoma" "10" "100"
  SendMessage $0 ${WM_SETFONT} $1 0
FunctionEnd*/