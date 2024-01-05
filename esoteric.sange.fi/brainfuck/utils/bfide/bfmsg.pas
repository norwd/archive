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

unit bfMsg;

interface

uses
  bfEdit;

type
  TMessage = record
    message_pos: TEditPos; { 1-indiziert }
  end;

const
  message: TMessage = (
    message_pos: (
      line: 1;
      col: 1
    )
  );

procedure write_message(const s: string);
function message_input(const s: string): string;

implementation

uses
  Crt,
  config, utils;

procedure write_message(const s: string);
var
  oldx, oldy: Integer;
begin
  oldx := WhereX;
  oldy := WhereY;
  Window(MESSAGES_LEFT, MESSAGES_TOP, MESSAGES_LEFT + MESSAGES_WIDTH - 1,
         MESSAGES_TOP + MESSAGES_HEIGHT - 1);
  at(message.message_pos.col, message.message_pos.line, s, COLOR_MESSAGES);
  WriteLn;
  message.message_pos.line := WhereY;
  Window(1, 1, SCREEN_WIDTH, SCREEN_HEIGHT);
  GotoXY(oldx, oldy);
end;

function message_input(const s: string): string;
var
  inp: string;
  oldx, oldy: Integer;
begin
  oldx := WhereX;
  oldy := WhereY;
  Window(MESSAGES_LEFT, MESSAGES_TOP, MESSAGES_LEFT + MESSAGES_WIDTH - 1,
         MESSAGES_TOP + MESSAGES_HEIGHT - 1);
  GotoXY(message.message_pos.col, message.message_pos.line);
  Write(s);
  ReadLn(inp);
  message.message_pos.line := WhereY;
  Window(1, 1, SCREEN_WIDTH, SCREEN_HEIGHT);
  message_input := inp;
  GotoXY(oldx, oldy);
end;

end.
