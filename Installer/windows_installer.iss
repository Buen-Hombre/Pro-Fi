; ==============================================================================
; MORI Sounds Pro-Fi - Windows Installer Script (Inno Setup 6)
; ==============================================================================

#ifndef MyAppVersion
  #define MyAppVersion "1.0.0"
#endif

#define MyAppName "Pro-Fi"
#define MyAppPublisher "MORI Sounds"
#define MyAppURL "https://morisounds.com"
#define MyAppExeName "Pro-Fi.exe"

#ifndef BUILD_DIR
  #define BUILD_DIR "..\build\ProLoFi_artefacts\Release"
#endif

[Setup]
AppId={{E6D59A72-4B69-42E1-8B39-16629B0D8F1A}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} v{#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\MORI Sounds\{#MyAppName}
DefaultGroupName=MORI Sounds\{#MyAppName}
DisableProgramGroupPage=yes
OutputDir=dist
OutputBaseFilename=Pro-Fi_v{#MyAppVersion}_Windows_Installer
Compression=lzma2/ultra64
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64
ArchitecturesAllowed=x64compatible
PrivilegesRequired=admin
PrivilegesRequiredOverridesAllowed=commandline
WizardStyle=modern
UninstallDisplayIcon={app}\{#MyAppExeName}

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Types]
Name: "full"; Description: "Full Installation (VST3 & Standalone)"
Name: "vst3only"; Description: "VST3 Plugin Only (for DAWs)"
Name: "custom"; Description: "Custom Installation"; Flags: iscustom

[Components]
Name: "vst3"; Description: "Pro-Fi VST3 64-bit Plugin (C:\Program Files\Common Files\VST3)"; Types: full vst3only custom; Flags: checkablealone
Name: "standalone"; Description: "Pro-Fi Standalone Application"; Types: full custom

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Components: standalone; Flags: unchecked

[Files]
; 64-bit VST3 Plugin Bundle / File
Source: "{#BUILD_DIR}\VST3\Pro-Fi.vst3\*"; DestDir: "{commoncf64}\VST3\Pro-Fi.vst3"; Flags: ignoreversion recursesubdirs createallsubdirs; Components: vst3
; Standalone Executable
Source: "{#BUILD_DIR}\Standalone\Pro-Fi.exe"; DestDir: "{app}"; Flags: ignoreversion; Components: standalone
; Documentation
Source: "..\README.md"; DestDir: "{app}"; DestName: "README.txt"; Flags: ignoreversion; Components: standalone

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Components: standalone
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; Components: standalone

[Run]
Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Filename: "{app}\{#MyAppExeName}"; Flags: nowait postinstall skipifsilent; Components: standalone
