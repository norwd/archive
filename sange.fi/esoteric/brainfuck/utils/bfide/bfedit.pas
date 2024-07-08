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

unit bfEdit;

interface

type
  PEditPos = ^TEditPos;
  TEditPos = record
    line: Integer;
    col: Integer;
  end;

  TEditor = record
    start_line: Integer; { 0-indiziert }
    cursor: TEditPos; { line und col 1-indiziert }
  end;

const
  editor: TEditor = (
    start_line: 0;
    cursor: (
      line: 1;
      col: 1
    )
  );

procedure insert_char_here(c: Char);
procedure insert_line_here;
procedure delete_char_before;
procedure delete_char_here;
procedure delete_line_here;
procedure update_the_editor(options: Integer);
procedure editor_down(update: Boolean);
procedure editor_up(update: Boolean);
procedure editor_pgdown(update: Boolean);
procedure editor_pgup(update: Boolean);

implementation

uses
  consts, utils,
  config, bfEmul, bfScreen;

procedure insert_char_here(c: Char);
var
  p: ^PString;
  s: String;
begin
  p := @emulator.code^[editor.cursor.line - 1];
  s := p^^;
  if (Length(s) < EDITOR_LINEWIDTH) then
    begin
      Insert(c, s, editor.cursor.col);
      strkill(p^);
      p^ := strdup(s);
      if (editor.cursor.line - 1 = emulator.codeptr.line) then
        if (emulator.codeptr.col >= editor.cursor.col) then
          Inc(emulator.codeptr.col);
      Inc(editor.cursor.col);
      emulator.need_to_compile := True;
      update_screen(UPDATE_EDITOR_CURRENT_LINE);
    end
  else
    Write(ch_bell);
end;

procedure insert_line_here;
var
  i: Integer;
  s: string;
begin
  i := High(emulator.code^);
  while (i > editor.cursor.line) do
    begin
      emulator.code^[i] := emulator.code^[i - 1];
      Dec(i);
    end;
  Dec(i);
  s := emulator.code^[i]^;
  strkill(emulator.code^[i]);
  emulator.code^[i] := strdup(Copy(s, 1, editor.cursor.col - 1));
  Delete(s, 1, editor.cursor.col - 1);
  emulator.code^[i+1] := strdup(s);
  editor.cursor.col := 1;
  editor_down(False);
  if (emulator.codeptr.line > editor.cursor.line - 1) then
    Inc(emulator.codeptr.line)
  else if (emulator.codeptr.line = editor.cursor.line - 1) then
    if (emulator.codeptr.col >= editor.cursor.col) then
      begin
        Inc(emulator.codeptr.line);
        Dec(emulator.codeptr.col, editor.cursor.col - 1);
      end;
  emulator.need_to_compile := True;
  find_next_instruction;
  update_screen(UPDATE_EDITOR_ALL);
end;

procedure delete_line_before;
begin
  if (editor.cursor.line > 1) then
    begin
      editor_up(False);
      editor.cursor.col := Length(emulator.code^[editor.cursor.line - 1]^) + 1;
      delete_line_here;
    end;
end;

procedure delete_char_before;
var
  p: ^PString;
  s: String;
begin
  p := @emulator.code^[editor.cursor.line - 1];
  s := p^^;
  if (editor.cursor.col > 1) then
    begin
      Delete(s, editor.cursor.col - 1, 1);
      strkill(p^);
      p^ := strdup(s);
      if (editor.cursor.line - 1 = emulator.codeptr.line) then
        if (emulator.codeptr.col >= editor.cursor.col) then
          Dec(emulator.codeptr.col);
      Dec(editor.cursor.col);
      emulator.need_to_compile := True;
      find_next_instruction;
      update_screen(UPDATE_EDITOR_CURRENT_LINE or UPDATE_EDITOR_INSTR_PTR);
    end
  else
    delete_line_before;
end;

procedure delete_line_here;
var
  s: string;
  p: ^PString;
  i, len: Integer;
begin
  p := @emulator.code^[editor.cursor.line - 1];
  if (emulator.code^[editor.cursor.line - 1 + 1] <> nil) then
    begin
      s := p^^ + emulator.code^[editor.cursor.line]^;
      len := Length(p^^);
      strkill(p^);
      strkill(emulator.code^[editor.cursor.line]);
      p^ := strdup(s);
      i := editor.cursor.line;
      while (emulator.code^[i+1] <> nil) do
        begin
          emulator.code^[i] := emulator.code^[i+1];
          Inc(i);
        end;
      emulator.code^[i] := nil;
      if (emulator.codeptr.line > editor.cursor.line - 1) then
        Dec(emulator.codeptr.line);
      if (emulator.codeptr.line = editor.cursor.line - 1) then
        Inc(emulator.codeptr.col, len);
      emulator.need_to_compile := True;
      find_next_instruction;
      update_screen(UPDATE_EDITOR_ALL);
    end;
end;

procedure delete_char_here;
var
  p: ^PString;
  s: String;
begin
  p := @emulator.code^[editor.cursor.line - 1];
  s := p^^;
  if (editor.cursor.col <= Length(s)) then
    begin
      Delete(s, editor.cursor.col, 1);
      strkill(p^);
      p^ := strdup(s);
      if (editor.cursor.line - 1 = emulator.codeptr.line) then
        if (emulator.codeptr.col >= editor.cursor.col) then
          Dec(emulator.codeptr.col);
      emulator.need_to_compile := True;
      find_next_instruction;
      update_screen(UPDATE_EDITOR_CURRENT_LINE or UPDATE_EDITOR_INSTR_PTR);
    end
  else
    delete_line_here;
end;

procedure update_line(n: Integer);
var
  curline: PString;
  i: Integer;
begin
  curline := emulator.code^[n + editor.start_line];
  if (curline <> nil) then
    begin
      at(EDITOR_LEFT, 1 + n, linenumber(1 + n + editor.start_line, 4) + ': ', COLOR_EDITOR);
      for i := 1 to EDITOR_LINEWIDTH do
        if i > Length(curline^) then
          at(EDITOR_LINESTART + i - 1, 1 + n, ' ', COLOR_COMMENT)
        else
          if ((emulator.codeptr.line = n + editor.start_line) and
              (i = emulator.codeptr.col)) then
            at(EDITOR_LINESTART + i - 1, 1 + n, curline^[i], COLOR_CURRENT)
          else if (Pos(curline^[i], bf_literals) <> 0) then
            at(EDITOR_LINESTART + i - 1, 1 + n, curline^[i], COLOR_COMMAND)
          else
            at(EDITOR_LINESTART + i - 1, 1 + n, curline^[i], COLOR_COMMENT);
    end
  else
    at(EDITOR_LEFT, 1 + n, strexpand('', EDITOR_WIDTH), COLOR_EDITOR);
end;

procedure update_the_editor(options: Integer);
var
  j: Integer;
begin
  if (options and UPDATE_EDITOR_ALL <> 0) then
    for j := 0 to EDITOR_HEIGHT - 1 do
      update_line(j)
  else if (options and UPDATE_EDITOR_CURRENT_LINE <> 0) then
    update_line(editor.cursor.line - (editor.start_line + 1));
end;

procedure editor_down(update: Boolean);
begin
  if (emulator.code^[editor.cursor.line] <> nil) then
    begin
      Inc(editor.cursor.line);
      if (editor.cursor.line - editor.start_line > EDITOR_HEIGHT) then
        Inc(editor.start_line);
      if (editor.cursor.col > Length(emulator.code^[editor.cursor.line - 1]^)) then
        editor.cursor.col := Length(emulator.code^[editor.cursor.line - 1]^) + 1;
      if (update) then
        update_screen(UPDATE_EDITOR_ALL);
    end;
end;

procedure editor_up(update: Boolean);
begin
  if (editor.cursor.line > 1) then
    begin
      Dec(editor.cursor.line);
      if (editor.cursor.line - editor.start_line < 1) then
        Dec(editor.start_line);
      if (editor.cursor.col > Length(emulator.code^[editor.cursor.line - 1]^)) then
        editor.cursor.col := Length(emulator.code^[editor.cursor.line - 1]^) + 1;
      if (update) then
        update_screen(UPDATE_EDITOR_ALL);
    end;
end;

procedure editor_pgdown(update: Boolean);
var
  i: Integer;
begin
  for i := 1 to EDITOR_HEIGHT do
    if (emulator.code^[editor.cursor.line] <> nil) then
      begin
        Inc(editor.cursor.line);
        if (emulator.code^[editor.start_line + EDITOR_HEIGHT] <> nil) then
          Inc(editor.start_line);
      end;
  if (editor.cursor.col > Length(emulator.code^[editor.cursor.line - 1]^)) then
    editor.cursor.col := Length(emulator.code^[editor.cursor.line - 1]^) + 1;
  if (update) then
    update_screen(UPDATE_EDITOR_ALL);
end;

procedure editor_pgup(update: Boolean);
var
  i: Integer;
begin
  for i := 1 to EDITOR_HEIGHT do
    if (editor.cursor.line > 1) then
      begin
        Dec(editor.cursor.line);
        if editor.start_line > 0 then
          Dec(editor.start_line);
      end;
  if (editor.cursor.col > Length(emulator.code^[editor.cursor.line - 1]^)) then
    editor.cursor.col := Length(emulator.code^[editor.cursor.line - 1]^) + 1;
  if (update) then
    update_screen(UPDATE_EDITOR_ALL);
end;

end.
