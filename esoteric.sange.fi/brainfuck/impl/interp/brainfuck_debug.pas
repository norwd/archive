unit brainfuck_debug;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TDebugForm = class(TForm)
    labCodePos: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    labCellPos: TLabel;
    DebugHalt: TButton;
    Button2: TButton;
    Label3: TLabel;
    labInstructionCount: TLabel;
    labCellValue: TLabel;
    Label4: TLabel;
    butDebugStep: TButton;
    procedure DebugHaltClick(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure butDebugStepClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  DebugForm: TDebugForm;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

implementation

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

uses brainfuck_mainunit;

{$R *.dfm}

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TDebugForm.DebugHaltClick(Sender: TObject);
begin
  HaltProgram  := True;
  DebugProgram := False;
  DebugForm.Visible := False;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TDebugForm.Button2Click(Sender: TObject);
begin
  DebugProgram      := False;
  DebugForm.Visible := False;
end;

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}

procedure TDebugForm.butDebugStepClick(Sender: TObject);
begin
  DebugStep := True;
end;

end.

{*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *}
