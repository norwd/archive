unit brainfuck_mainunit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Menus, Buttons, ComCtrls, Math;

type
  TMainForm = class(TForm)
    Code: TMemo;
    butDebug: TButton;
    RunCode: TButton;
    ScrollBox1: TScrollBox;
    Output: TLabel;
    butOptions: TButton;
    butOpenBFScript: TSpeedButton;
    BFScripts: TPopupMenu;
    SelectBFScript1: TMenuItem;
    N1: TMenuItem;
    StatusBar: TStatusBar;
    Label1: TLabel;
    edInput: TEdit;
    Button1: TButton;
    butHaltExec: TButton;
    procedure butDebugClick(Sender: TObject);
    procedure RunCodeClick(Sender: TObject);
    procedure OutputDblClick(Sender: TObject);
    procedure butOptionsClick(Sender: TObject);
    procedure butOpenBFScriptClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure butHaltExecClick(Sender: TObject);
    procedure edInputKeyPress(Sender: TObject; var Key: Char);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    procedure OpenScript (Sender: TObject);
    { Public declarations }
  end;

var
  MainForm     : TMainForm;
  HaltProgram  : Boolean=False;
  DebugProgram : Boolean=False;
  DebugStep    : Boolean=False;

const
  CellCount = 30000;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure AddPopupItem (sItemName: String);
function  GetTimeInMS: DWord;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

implementation

uses brainfuck_options, brainfuck_debug;

{$R *.dfm}

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TMainForm.butDebugClick(Sender: TObject);
begin
  DebugProgram := True;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TMainForm.RunCodeClick(Sender: TObject);
var
  Cells        : array[1..CellCount] of DWord;
  iCellPos     : DWord;
  cTask        : Char;
  iLine        : Word;
  iIndex       : DWord;
  sCode        : String;
  iBegin, iEnd : Array[1..255] of DWord;
  iCodePos     : DWord;
  sInput       : String;
  sOutput      : AnsiString;
  iLoopDepth   : Byte;
  iLoops       : Byte;
  sDebugCode   : String;

  StartTime, FinishTime, TimeTaken : LongInt;

  iInstructionCount : DWord;

begin
  // Checking to see if there's code to run

  if (Code.Lines.Count = 0) then
  begin
    StatusBar.SimpleText := 'No code to run!';
    Exit;
  end;

  // Updating button

  MainForm.RunCode.Enabled := False;

  // Clearing output

  MainForm.Output.Caption := '';

  // Clearing Cells

  for iIndex := 1 to CellCount do
  begin
    Cells[iIndex] := 0;
  end;

  // Putting the code into one big long string

  sCode := '';

  StatusBar.SimpleText := 'Transferring Code';

  for iLine := 0 to Code.Lines.Count do
  begin
    sCode := sCode + Code.Lines[iLine];
  end;

    // Stripping all non-brain fuck chars out of it

    StatusBar.SimpleText := 'Stripping Code';

    iIndex := 1;

    repeat
      if not (Char(sCode[iIndex]) in ['<', '>', '[', ']', '+', '-', '.', ',']) then
      begin
        Delete (sCode, iIndex, 1);
      end
      else
        Inc (iIndex);

    until (iIndex > length(sCode));

    // Initializing values

  iCodePos := 1;
  iCellPos := 1;

  iLoopDepth := 0;
  iInstructionCount := 0;

  HaltProgram := False;
  DebugStep   := False;

  StartTime := GetTimeInMS;

  sInput  := '';
  sOutput := '';


  // Interpreting brainfuck code

  StatusBar.SimpleText := 'Executing Brainfucker';

  repeat
    if iCellPos > CellCount then iCellPos := 1;
    if iCellPos = 0 then iCellPos := CellCount;

    if (iInstructionCount mod 100000=0) then
    begin
      Application.ProcessMessages;
      Output.Caption := sOutput;
    end;

    cTask := Char (sCode[iCodePos]);

    if cTask = '>' then
    begin
      Inc (iCellPos);
      Inc (iCodePos);
    end;

    if cTask = '<' then
    begin
      Dec (iCellPos);
      Inc (iCodePos);
    end;

    if cTask = '+' then
    begin
      Inc (Cells[iCellPos]);
      Inc (iCodePos);

      // Checking size of cell

      if (Cells[iCellPos] = 256) and (Options.radCellSizeByte.Checked = True) then
      begin
        Cells[iCellPos] := 0;
      end;

      if (Cells[iCellPos] = 65536) and (Options.radCEllSizeWord.Checked = True) then
      begin
        Cells[iCellPos] := 0;
      end;
    end;

    if cTask = '-' then
    begin

      if (Cells[iCellPos] = 0) then
      begin
        if (Options.radCellSizeByte.Checked = True) then
        begin
          Cells[iCellPos] := 255;
        end;

        if (Options.radCellSizeWord.Checked = True) then
        begin
          Cells[iCellPos] := 65535;
        end;

        if (Options.radCellSizeDWord.Checked = True) then
        begin
          Dec (Cells[iCellPos]);
        end;
      end
      else
        Dec (Cells[iCellPos]);

      Inc (iCodePos);
    end;

    if cTask = '.' then
    begin
      if Cells[iCellPos] <> 0 then
      begin
        sOutput := sOutput + Chr (Cells[iCellPos]);
      end;

      Inc (iCodePos);

      if (Options.radDot.Checked = True) then
      begin
        Application.ProcessMessages;
        Output.Caption := sOutput;
      end;

      if (Options.radEOL.Checked = True) then
      begin
        if Cells[iCellPos]=10 then
        begin
          Application.ProcessMessages;
          Output.Caption := sOutput;
        end;
      end;
    end;

    if cTask = ',' then
    begin
      if (edInput.Text = '') then
        Output.Caption := sOutput;
        StatusBar.SimpleText := 'The Brainfucker has requested input';

        FocusControl (edInput);

        while (edInput.Text = '') and (HaltProgram=False) do
        begin
          Application.ProcessMessages;
        end;

      if HaltProgram = False then
      begin
        sInput := edInput.Text;

        Cells[iCellPos] := Ord(Char(sInput[1]));

        Delete(sInput, 1, 1);

        edInput.Text := sInput;

        StatusBar.SimpleText := 'Executing Brainfucker';

        Inc (iCodePos);
      end;
    end;

    if cTask = '[' then
    begin
      Inc (iLoopDepth);
      iBegin[iLoopDepth] := iCodePos;

      iIndex := iCodePos;
      iLoops := 1;
      repeat
        Inc (iIndex);

        if (sCode[iIndex] = '[') then
        begin
          Inc (iLoops);
        end;

        if (sCode[iIndex] = ']') then
        begin
          Dec (iLoops);
        end;

      until (sCode[iIndex] = ']') and (iLoops=0);

      iEnd[iLoopDepth] := iIndex;

      if (Cells[iCellPos] = 0) then
      begin
        iCodePos := iEnd[iLoopDepth] + 1;
        Dec (iLoopDepth);
      end
      else
      begin
        Inc (iCodePos);
      end;
    end;

    if cTask = ']' then
    begin
      iCodePos := iBegin[iLoopDepth];
      Dec (iLoopDepth);
    end;

    Inc (iInstructionCount);

    // Checking for Debug

    if (DebugProgram = True) then
    begin
      DebugForm.labCodePos.Caption := IntToStr (iCodePos);
      DebugForm.labCellPos.Caption := IntToStr (iCellPos);
      DebugForm.labCellValue.Caption := IntToStr (Cells[iCellPos]);
      DebugForm.labInstructionCount.Caption := IntToStr (iInstructionCount);

      sDebugCode := sCode;
      Insert (' =::= ', sDebugCode, iCodePos);

      Code.Clear;
      Code.Lines.Add(sDebugCode);
      Code.SelStart := iCodePos;
      Code.SelLength := 1;

      DebugForm.Visible := True;

      repeat
        Application.ProcessMessages;
      until (DebugProgram = False) or (DebugStep = True);

      DebugStep := False;
    end;

  until (iCodePos > length(sCode)) or (HaltProgram = True);

  // Updating caption again

  MainForm.RunCode.Enabled := True;

  if HaltProgram = True then
    StatusBar.SimpleText := 'Brainfucker Halted'
  else
    StatusBar.SimpleText := 'Brainfucker gracefully orgasmed';

  StatusBar.SimpleText := StatusBar.SimpleText + '; '+ Format('%.0n', [RoundTo(iInstructionCount,0)]) + ' instructions executed';

    // Calculating time taken

  FinishTime := GetTimeInMS;

  TimeTaken := FinishTime - StartTime;

  if TimeTaken < 0 then
  begin
    StatusBar.SimpleText := StatusBar.SimpleText + '; Error calculating duration';
  end
  else
  begin
    if TimeTaken=0 then TimeTaken := 1;

    StatusBar.SimpleText := StatusBar.SimpleText + ' in ' + Format('%.0n', [RoundTo(TimeTaken,0)])
                            + ' ms, at ' + Format('%n', [(iInstructionCount/TimeTaken)])
                            + ' instructions per milisecond';
  end;

    // Finalizing

  Output.Caption := sOutput;

  HaltProgram := False;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TMainForm.OutputDblClick(Sender: TObject);
begin
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TMainForm.butOptionsClick(Sender: TObject);
begin
  Options.Visible := True;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TMainForm.butOpenBFScriptClick(Sender: TObject);
var
  SR      : TSearchRec;

begin
  // Populating pop up menu

    // Clearing items and initializing values

  BFScripts.Items.Clear;

    // If no files exist, exit

  if FindFirst ('.\BF\*.b*', faAnyFile, SR) <> 0 then Exit;

  repeat
    AddPopupItem (SR.Name);
  until FindNext (SR) <> 0;

  FindClose (SR);

  // Popping up the pop up menu

  BFScripts.Popup(Mainform.Left + butOpenBFScript.Left + butOpenBFScript.Width, MainForm.Top + butOpenBFScript.Top);
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TMainForm.OpenScript(Sender: TObject);
begin
//  MainForm.Code.Lines.LoadFromFile (MainForm.BFScripts.Items[Tag].Caption);

  With Sender as TMenuItem do
  begin
    Code.Lines.Clear;
    Code.Lines.LoadFromFile('BF\' + Caption);
  end;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure AddPopupItem (sItemName: String);
var
  NewItem : TMenuItem;

begin
  NewItem := TMenuItem.Create(MainForm.PopupMenu);

  MainForm.BFScripts.Items.Add(NewItem);

  NewItem.Caption := sItemName;
  NewItem.OnClick := MainForm.OpenScript;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TMainForm.Button1Click(Sender: TObject);
var
  sByteInput: String[3];

begin
  sByteInput := InputBox ('Insert Byte', 'Enter Ord Value:', '');

  try
    edInput.Text := edInput.Text + Chr (StrToInt (sByteInput));
  except
    on EConvertError do StatusBar.SimpleText := 'Not a valid Byte value!';
  end;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TMainForm.butHaltExecClick(Sender: TObject);
begin
  HaltProgram  := True;
  DebugProgram := False;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TMainForm.edInputKeyPress(Sender: TObject; var Key: Char);
begin
  if Key = Chr(13) then edInput.Text := edInput.Text + Chr(10);
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TMainForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  DebugProgram := False;
  HaltProgram  := True;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

function GetTimeInMS: DWord;
var
  sNow: TDateTime;
  iHours, iMinutes, iSeconds, iMS: Word;

begin
  sNow := Time;

  iHours   := StrToInt (FormatDateTime('h', sNow));
  iMinutes := StrToInt (FormatDateTime('n', sNow));
  iSeconds := StrToInt (FormatDateTime('s', sNow));
  iMS      := StrToInt (FormatDateTime('z', sNow));

  GetTimeInMS := (iHours *60*60*1000) + (iMinutes *60*1000) +
                 (iSeconds *1000)     + iMS;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

end.

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}
{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

