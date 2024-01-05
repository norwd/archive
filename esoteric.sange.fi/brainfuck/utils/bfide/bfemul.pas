(*
    Brainfuck Integrated Development Environment
    Copyright (C) 2002  Roland Illig <1illig@informatik.uni-hamburg.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*)

unit bfEmul;

interface

uses
  Crt,
  config,
  utils, bfEdit;

const
  bf_literals: String[8] = '+-.,<>[]';

type
  TRunningMode = (rm_stopped, rm_paused, rm_singlestep, rm_endofloop,
                  rm_running, rm_stopping);
  PCode = ^TCode;
  TCode = array [0..MAX_CODE_LINES-1] of PString;
  TCodePtr = record
    line: Integer;
    col: Integer;
  end;
  PData = ^TData;
  TData = array [0..DATA_SIZE-1] of Byte;
  PStack = ^TStack;
  TStack = array [0..LOOPSTACK_SIZE] of TEditPos;

  TEmulator = record
    data: PData;
    code: PCode;
    stack: PStack;
    dataptr: Integer;
    stackptr: Integer;
    codeptr: TCodePtr;
    data_offset: Integer;
    stdout_pos: TEditPos; { 1-indiziert }
    running_mode: TRunningMode;
    need_to_compile: Boolean;
    need_to_reset: Boolean;
  end;

const
  emulator: TEmulator = (
    data: nil;
    code: nil;
    stack: nil;
    dataptr: 0;
    stackptr: 0;
    codeptr: (
      line: 0;
      col: 0
    );
    data_offset: 0;
    stdout_pos: (
      line: 1;
      col: 1
    );
    running_mode: rm_stopped;
    need_to_compile: False
  );

function push(lineno, strpos: Integer): Boolean;
function pop(var lineno, strpos: Integer): Boolean;
function current_instruction: Char;
function find_next_instruction: Boolean;
procedure reset_program(clear_program, reset_rm: Boolean);
procedure go_to_matching_bracket;
procedure bf_write (c: Char);
function execute (c: Char): Boolean;
function execute_step: Boolean;
function rebuild_loop_stack: Boolean;
function load_program (const fname: string): Integer;
function save_program (const fname: string): Integer;

implementation

uses
  bfMsg, bfScreen;

function push(lineno, strpos: Integer): Boolean;
begin
  if (emulator.stackptr >= Low(emulator.stack^)) then
    begin
      emulator.stack^[emulator.stackptr].line := lineno;
      emulator.stack^[emulator.stackptr].col := strpos;
      Dec(emulator.stackptr);
      push := True;
    end
  else
    push := False;
end;

function pop(var lineno, strpos: Integer): Boolean;
begin
  if (emulator.stackptr < High(emulator.stack^)) then
    begin
      Inc(emulator.stackptr);
      lineno := emulator.stack^[emulator.stackptr].line;
      strpos := emulator.stack^[emulator.stackptr].col;
      pop := True;
    end
  else
    pop := False;
end;

function current_instruction: Char;
begin
  if find_next_instruction then
    current_instruction := emulator.code^[emulator.codeptr.line]^
                           [emulator.codeptr.col]
  else
    current_instruction := ' ';
end;

function find_next_instruction: Boolean;
begin
  find_next_instruction := False;
  repeat
    if (emulator.code^[emulator.codeptr.line] = nil) then
      begin
        if (emulator.running_mode <> rm_stopped) then
          begin
            write_message('Program terminated normally.');
            emulator.running_mode := rm_stopping;
          end;
        exit;
      end;
    if (emulator.codeptr.col >
        Length(emulator.code^[emulator.codeptr.line]^)) then
      begin
        Inc(emulator.codeptr.line);
        emulator.codeptr.col := 1;
        continue;
      end;
    if Pos(emulator.code^[emulator.codeptr.line]^
           [emulator.codeptr.col], bf_literals) = 0 then
      begin
        Inc(emulator.codeptr.col);
        continue;
      end;
    break;
  until false;
  find_next_instruction := True;
end;

procedure reset_program(clear_program, reset_rm: Boolean);
begin
  FillChar(emulator.data^, sizeof(emulator.data^), 0);
  if clear_program then
    begin
      FillChar(emulator.code^, sizeof(emulator.code^), 0);
      emulator.code^[0] := strdup('');
      editor.cursor.line := 1;
      editor.cursor.col := 1;
    end;
  FillChar(emulator.stack^, sizeof(emulator.stack^), 0);
  emulator.dataptr := 0;
  emulator.stackptr := High(emulator.stack^);
  emulator.codeptr.line := 0;
  emulator.codeptr.col := 1;
  emulator.need_to_compile := True;
  if (reset_rm) then
    emulator.running_mode := rm_stopping;
  emulator.need_to_reset := False;
  find_next_instruction;
end;

function count_brackets: Integer;
var
  i, j, n: Integer;
  p: PString;
begin
  n := 0;
  j := 0;
  while (emulator.code^[j] <> nil) do
    begin
      p := emulator.code^[j];
      for i := 1 to Length(p^) do
        case p^[i] of
          '[': Inc(n);
          ']':
            begin
              Dec(n);
              if n < 0 then
                begin
                  count_brackets := -1;
                  exit;
                end;
            end;
        end;
      Inc(j);
    end;
  count_brackets := n;
end;

procedure go_to_matching_bracket;
var
  stackptr, wanted_stackptr: Integer;
begin
  stackptr := emulator.stackptr;
  wanted_stackptr := stackptr;
  repeat
    if not find_next_instruction then
      break;
    case emulator.code^[emulator.codeptr.line]^
         [emulator.codeptr.col] of
      '[': Dec(stackptr);
      ']': Inc(stackptr);
    end;
    if (stackptr = wanted_stackptr) then
      break;
    Inc(emulator.codeptr.col);
  until false;
end;

procedure bf_write (c: Char);
begin
  Window(STDOUT_LEFT, STDOUT_TOP, STDOUT_LEFT + STDOUT_WIDTH - 1,
         STDOUT_TOP + STDOUT_HEIGHT - 1);
  at(emulator.stdout_pos.col, emulator.stdout_pos.line,
     c, COLOR_STDOUT);
  emulator.stdout_pos.col := WhereX;
  emulator.stdout_pos.line := WhereY;
  if emulator.stdout_pos.col > STDOUT_WIDTH then
    begin
      emulator.stdout_pos.col := 1;
      Inc(emulator.stdout_pos.line);
    end;
  Window(1, 1, SCREEN_WIDTH, SCREEN_HEIGHT);
end;

function execute (c: Char): Boolean;
var
  line, col: Integer;
begin
  case c of
    '.': bf_write(Chr(emulator.data^[emulator.dataptr]));
    ',': emulator.data^[emulator.dataptr] := Ord(ReadKey);
    '+': Inc(emulator.data^[emulator.dataptr]);
    '-': Dec(emulator.data^[emulator.dataptr]);
    '<':
      begin
        Dec(emulator.dataptr);
        if (emulator.dataptr < 0) then
          begin
            emulator.running_mode := rm_stopping;
            emulator.need_to_reset := True;
            write_message('DataPtr < 0. Program terminated.');
          end;
      end;
    '>': Inc(emulator.dataptr);
    '[':
      begin
        if (emulator.data^[emulator.dataptr] = 0) then
          go_to_matching_bracket
        else
          push(emulator.codeptr.line, emulator.codeptr.col);
      end;
    ']': pop(emulator.codeptr.line, emulator.codeptr.col);
  end;
  execute := True;
  if (c <> ']') then
    begin
      Inc(emulator.codeptr.col);
      execute := find_next_instruction;
    end;
end;

function execute_step: Boolean;
begin
  if (emulator.need_to_compile) then
    if (count_brackets = 0) then
      begin
        emulator.need_to_compile := False;
        rebuild_loop_stack;
      end
    else
      begin
        execute_step := True;
        write_message('Unbalanced brackets.');
        emulator.need_to_reset := True;
        exit;
      end;
  if (emulator.need_to_reset) then
    begin
      reset_program(False, False);
      update_screen(UPDATE_EDITOR_INSTR_PTR or UPDATE_DATA);
    end;
  execute_step := execute(current_instruction);
end;

function rebuild_loop_stack: Boolean;
var
  i, j, tmp: Integer;
begin
  rebuild_loop_stack := False;
  emulator.stackptr := High(emulator.stack^);
  for i := 0 to emulator.codeptr.line - 1 do
    for j := 1 to Length(emulator.code^[i]^) do
      case emulator.code^[i]^[j] of
        '[': push(i, j);
        ']': pop(tmp, tmp);
      end;
  i := emulator.codeptr.line;
  for j := 1 to emulator.codeptr.col do
    case emulator.code^[i]^[j] of
      '[': push(i, j);
      ']': pop(tmp, tmp);
    end;
  rebuild_loop_stack := True;
end;

function load_program (const fname: string): Integer;
var
  f: Text;
  i: Integer;
  s: String;
begin
  load_program := -1;
  Assign(f, fname);
  {$I-}
  Reset(f);
  {$I+}
  if IOResult <> 0 then
    exit;
  for i := Low(emulator.code^) to High(emulator.code^) do
    strkill(emulator.code^[i]);
  reset_program(True, True);
  i := 0;
  while not eof(f) do
    begin
      ReadLn(f, s);
      emulator.code^[i] := strdup(s);
      Inc(i);
    end;
  Close(f);
  find_next_instruction;
  load_program := 0;
  update_screen(UPDATE_EDITOR or UPDATE_DATA or UPDATE_STDOUT);
end;

function save_program (const fname: string): Integer;
var
  f: Text;
  i: Integer;
begin
  save_program := -1;
  Assign(f, fname);
  {$I-}
  Rewrite(f);
  {$I+}
  if IOResult <> 0 then
    exit;
  i := 0;
  while (emulator.code^[i] <> nil) do
    begin
      WriteLn(f, emulator.code^[i]^);
      Inc(i);
    end;
  Close(f);
  save_program := 0;
end;

end.
