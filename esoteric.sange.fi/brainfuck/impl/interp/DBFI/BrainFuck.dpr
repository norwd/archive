program BrainFuck;

uses
  Forms,
  brainfuck_mainunit in 'brainfuck_mainunit.pas' {MainForm},
  brainfuck_options in 'brainfuck_options.pas' {Options},
  brainfuck_debug in 'brainfuck_debug.pas' {DebugForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TOptions, Options);
  Application.CreateForm(TDebugForm, DebugForm);
  Application.Run;
end.
