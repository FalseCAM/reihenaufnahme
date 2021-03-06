; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Reihenaufnahme"
#define MyAppVersion "1.0.6"
#define MyAppPublisher "FalseCAM"
#define MyAppURL "http://reihenaufnahme.falsecam.net"
#define MyAppExeName "reihenaufnahme.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{737A10F5-F28F-4D0A-A830-9389EB8FE008}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
; Architecture   (32 | 64)
#define arch "32"
; ( | x64)
ArchitecturesInstallIn64BitMode=

LicenseFile=..\reihenaufnahme\resources\gpl-3.0.txt
OutputBaseFilename=reihenaufnahme-setup-win{#arch}
SetupIconFile=..\reihenaufnahme\resources\icon.ico
Compression=lzma
SolidCompression=yes

WizardImageFile=Wiz.bmp
WizardSmallImageFile=WizSmall.bmp
UninstallDisplayIcon={uninstallexe}
MinVersion=0,5.01

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
; Reihenaufnahme
Source: "..\..\reihenaufnahme-{#arch}bit\reihenaufnahme.exe"; DestDir: "{app}"; Flags: ignoreversion {#arch}bit; Components: Reihenaufnahme
Source: "..\..\reihenaufnahme-{#arch}bit\exiv2.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
Source: "..\..\reihenaufnahme-{#arch}bit\icudt49.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
Source: "..\..\reihenaufnahme-{#arch}bit\icuin49.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
Source: "..\..\reihenaufnahme-{#arch}bit\icuuc49.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
Source: "..\..\reihenaufnahme-{#arch}bit\libexpat.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
Source: "..\..\reihenaufnahme-{#arch}bit\QtCore5.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
Source: "..\..\reihenaufnahme-{#arch}bit\QtGui5.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
Source: "..\..\reihenaufnahme-{#arch}bit\QtNetwork5.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
Source: "..\..\reihenaufnahme-{#arch}bit\QtWidgets5.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
Source: "..\..\reihenaufnahme-{#arch}bit\zlib1.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
Source: "..\..\reihenaufnahme-{#arch}bit\message.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: Reihenaufnahme;
; Imageformats
Source: "..\..\reihenaufnahme-{#arch}bit\imageformats\*"; DestDir: "{app}\imageformats\"; Flags: {#arch}bit; Components: Reihenaufnahme;

; Plugins
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\blur5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\color5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\filechooser5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: Plugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\geotag5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\overlay5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\overlay-text5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: Plugins; 
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\picasa-download5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\picasa-upload5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\previewimage5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: Plugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\rename5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: Plugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\rename-album5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: Plugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\resize5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: Plugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\savefile5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: Plugins;
#if arch == "32"
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\flickr-download5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\plugins\flickr-upload5.dll"; DestDir: "{app}\plugins\"; Flags: {#arch}bit; Components: ExtraPlugins;
#endif

Source: "..\..\reihenaufnahme-{#arch}bit\libeay32.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\libssl32.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\Qt3D5.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\QtLocation5.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\QtPrintSupport5.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\QtSensors5.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\QtWebkit5.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\QtXmlPatterns5.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: ExtraPlugins;
Source: "..\..\reihenaufnahme-{#arch}bit\ssleay32.dll"; DestDir: "{app}"; Flags: {#arch}bit; Components: ExtraPlugins;

; Languages
Source: "..\i18n\*.qm"; DestDir: "{app}\i18n\"; Components: Languages
; Tips
Source: "..\tips\*.txt"; DestDir: "{app}\tips\"; Components: Reihenaufnahme

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Dirs]
Name: "{app}\i18n"; Components: Reihenaufnahme
Name: "{app}\plugins"; Components: Reihenaufnahme
Name: "{app}\imageformats"; Components: Reihenaufnahme
Name: "{app}\tips"; Components: Reihenaufnahme

[Components]
Name: "Reihenaufnahme"; Description: "Main Program"; Types: full custom compact; Flags: fixed
Name: "ExtraPlugins"; Description: "extra plugins"; Types: full
Name: "Languages"; Description: "language files"; Types: full
Name: "Plugins"; Description: "most useable plugins"; Types: full custom compact; Flags: fixed

