{%MainUnit lazfileutils.pas}

function FilenameIsAbsolute(const TheFilename: string):boolean;
begin
  Result:=FilenameIsUnixAbsolute(TheFilename);
end;

function FileOpenUTF8(Const FileName : string; Mode : Integer) : THandle;
begin
  Result := SysUtils.FileOpen(FileName, Mode);
end;

function FileCreateUTF8(Const FileName : string) : THandle;
begin
  Result := SysUtils.FileCreate(FileName);
end;

function FileCreateUTF8(Const FileName : string; Rights: Cardinal) : THandle;
begin
  Result := SysUtils.FileCreate(FileName, Rights);
end;

function ExpandFileNameUtf8(const FileName: string; {const} BaseDir: String = ''): String;
var
  IsAbs: Boolean;
  CurDir, HomeDir, Fn: String;
begin
  Fn := FileName;
  DoDirSeparators(Fn);
  IsAbs := FileNameIsUnixAbsolute(Fn);
  if (not IsAbs) then
  begin
    CurDir := GetCurrentDirUtf8;
    if ((Length(Fn) > 1) and (Fn[1] = '~') and (Fn[2] = '/')) or (Fn = '~') then
    begin
      {$Hint use GetEnvironmentVariableUTF8}
      HomeDir := SysToUtf8(GetEnvironmentVariable('HOME'));
      if not FileNameIsUnixAbsolute(HomeDir) then
        HomeDir := ExpandFileNameUtf8(HomeDir,'');
      Fn := HomeDir + Copy(Fn,2,length(Fn));
      IsAbs := True;
    end;
  end;
  if IsAbs then
  begin
    Result := ResolveDots(Fn);
  end
  else
  begin
    if (BaseDir = '') then
      Fn := IncludeTrailingPathDelimiter(CurDir) + Fn
    else
      Fn := IncludeTrailingPathDelimiter(BaseDir) + Fn;
    Fn := ResolveDots(Fn);
    //if BaseDir is not absolute then this needs to be expanded as well
    if not FileNameIsUnixAbsolute(Fn) then
      Fn := ExpandFileNameUtf8(Fn, '');
    Result := Fn;
  end;
end;

function GetCurrentDirUTF8: String;
begin
  Result:=SysToUTF8(SysUtils.GetCurrentDir);
end;


procedure InitLazFileUtils;
begin
  //dummy
end;
