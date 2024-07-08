unit brainfuck_options;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls;

type
  TOptions = class(TForm)
    radOrgasm: TRadioGroup;
    radDot: TRadioButton;
    radEOL: TRadioButton;
    RadioButton3: TRadioButton;
    butCloseOptions: TButton;
    groupCellSize: TGroupBox;
    radCellSizeByte: TRadioButton;
    radCEllSizeWord: TRadioButton;
    radCellSizeDWord: TRadioButton;
    procedure butCloseOptionsClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Options: TOptions;

implementation

{$R *.dfm}

procedure TOptions.butCloseOptionsClick(Sender: TObject);
begin
  Options.Visible := False;
end;

end.
