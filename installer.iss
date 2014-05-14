[Setup]
AppName=wxCrafter Integration with Code::Blocks
AppVerName=wxCrafterCB
AppPublisherURL=http://wxcrafter.codelite.org
AppSupportURL=http://wxcrafter.codelite.org
AppUpdatesURL=http://wxcrafter.codelite.org
DefaultDirName={reg:HKCU\Software\CodeBlocks,Path}
DefaultGroupName=wxCrafter
OutputDir=.
OutputBaseFilename=wxcrafter-codeblocks
ChangesEnvironment=yes
FlatComponentsList=yes
SetupIconFile=installer.ico
Compression=lzma/ultra
SolidCompression=true
InternalCompressLevel=ultra
PrivilegesRequired=none
DirExistsWarning=no
DisableDirPage=no
ChangesAssociations=yes

[Components]
Name: "wxCrafterCB"; Description: "Integrating wxCrafter with Code::Blocks IDE"; Types: full; Flags: fixed

[Messages]
SelectDirLabel3 = Please select Code::Blocks installation folder

[Files]
Source: "C:\src\codelite\wxcrafter\Installer\wxcrafter-standlone-setup.exe"; DestDir: "{tmp}"; AfterInstall: RunWxCrafterInstaller
Source: "wxCrafterCB.zip";  DestDir: "{app}\share\codeblocks"; Flags: ignoreversion;                Components: wxCrafterCB
Source: "Release\wxCrafterCB.dll"; DestDir: "{app}\share\codeblocks\plugins"; Flags: ignoreversion; Components: wxCrafterCB
Source: "wx-config.exe"; DestDir: "{app}"; Flags: ignoreversion; Components: wxCrafterCB

[code]
function HasDefaultDir(): Boolean;
var
  PluginsPath: String;
begin
    RegQueryStringValue(HKCU, 'Software\CodeBlocks', 'Path', PluginsPath);
    Result :=  Length( PluginsPath ) > 0;
end;

function ShouldSkipPage(PageID: Integer): Boolean;
begin
  Result := false;
  //if PageID = wpSelectDir Then 
  //begin
  //  Result := (PageID = wpSelectDir) and HasDefaultDir();
  //  if not Result Then
  //  begin
  //    MsgBox('codelite 5.0 could not be located on this machine' + #10#13 + 'Please select codelite plugins directory manualy', mbInformation, MB_OK);
  //  end;
  //end;
end;

procedure RunWxCrafterInstaller;
var
  ResultCode: Integer;
begin
  if not Exec(ExpandConstant('{tmp}\wxcrafter-standlone-setup.exe'), '', '', SW_SHOWNORMAL,
    ewWaitUntilTerminated, ResultCode)
  then
    MsgBox('wxCrafter installer failed to run!' + #13#10 +
      SysErrorMessage(ResultCode), mbError, MB_OK);
end;
