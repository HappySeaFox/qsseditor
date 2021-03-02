#define MyAppName "QSS Editor"
#define MyAppPublisher "Dmitry Baryshev"
#define MyAppURL "https://github.com/smoked-herring/qsseditor"
#define MyAppVersion "0.6.1"

[Setup]
AppId={{A51E7AC1-A31C-40E7-82B3-D1DF32402DF8}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}/releases
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
LicenseFile=LICENSE.txt
OutputDir=.
OutputBaseFilename=qsseditor-setup-{#MyAppVersion}
SetupIconFile=qsseditor.ico
Compression=lzma
SolidCompression=yes
UninstallDisplayName={#MyAppName}
UninstallDisplayIcon={app}\QssEditor.exe
MinVersion=0,6.0
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64

[Languages]
Name: "AAAenglish"; MessagesFile: "compiler:Default.isl"
Name: "BrazilianPortuguesexisl"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: "Catalanxisl"; MessagesFile: "compiler:Languages\Catalan.isl"
Name: "Corsicanxisl"; MessagesFile: "compiler:Languages\Corsican.isl"
Name: "Czechxisl"; MessagesFile: "compiler:Languages\Czech.isl"
Name: "Danishxisl"; MessagesFile: "compiler:Languages\Danish.isl"
Name: "Dutchxisl"; MessagesFile: "compiler:Languages\Dutch.isl"
Name: "Finnishxisl"; MessagesFile: "compiler:Languages\Finnish.isl"
Name: "Frenchxisl"; MessagesFile: "compiler:Languages\French.isl"
Name: "Germanxisl"; MessagesFile: "compiler:Languages\German.isl"
Name: "Hebrewxisl"; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: "Italianxisl"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "Japanesexisl"; MessagesFile: "compiler:Languages\Japanese.isl"
Name: "Norwegianxisl"; MessagesFile: "compiler:Languages\Norwegian.isl"
Name: "Polishxisl"; MessagesFile: "compiler:Languages\Polish.isl"
Name: "Portuguesexisl"; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: "Russianxisl"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "Slovenianxisl"; MessagesFile: "compiler:Languages\Slovenian.isl"
Name: "Spanishxisl"; MessagesFile: "compiler:Languages\Spanish.isl"
Name: "Turkishxisl"; MessagesFile: "compiler:Languages\Turkish.isl"
Name: "Ukrainianxisl"; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; OnlyBelowVersion: 0,6.1

[Files]
Source: "LICENSE.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "QssEditor.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt5PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "imageformats/*.dll"; DestDir: "{app}/imageformats"; Flags: ignoreversion
Source: "platforms/*.dll"; DestDir: "{app}/platforms"; Flags: ignoreversion
Source: "styles/*.dll"; DestDir: "{app}/styles"; Flags: ignoreversion
Source: "translations/*.png"; DestDir: "{app}/translations"; Flags: ignoreversion
Source: "translations/*.qm"; DestDir: "{app}/translations"; Flags: ignoreversion
Source: "translations/translations.conf"; DestDir: "{app}/translations"; Flags: ignoreversion
Source: "vc_redist_2019.x64.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\QssEditor.exe"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\QssEditor.exe"; Tasks: desktopicon

[Run]
Filename: {tmp}\vc_redist_2019.x64.exe; Parameters: "/install /q /norestart"; StatusMsg: "Installing VC++ Redistributable..."
Filename: "{app}\QssEditor.exe"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
;Filename: "{#MyAppURL}/wiki/changelog"; Flags: nowait shellexec

[Code]
procedure CurStepChanged(CurStep: TSetupStep);
var
  ResultCode: Integer;
  Uninstall: String;
  UninstallQuery : String;
begin
  UninstallQuery := ExpandConstant('Software\Microsoft\Windows\CurrentVersion\Uninstall\{#emit SetupSetting("AppId")}_is1');
  if (CurStep = ssInstall) then begin
    if RegQueryStringValue(HKLM, UninstallQuery, 'UninstallString', Uninstall)
      or RegQueryStringValue(HKCU, UninstallQuery, 'UninstallString', Uninstall) then begin
    Uninstall := RemoveQuotes(Uninstall)
    if (FileExists(Uninstall)) AND (not Exec(RemoveQuotes(Uninstall), '/VERYSILENT', '', SW_SHOWNORMAL, ewWaitUntilTerminated, ResultCode)) then begin
      MsgBox(SysErrorMessage(ResultCode), mbCriticalError, MB_OK);
      Abort();
    end;
  end;
end;
end;
