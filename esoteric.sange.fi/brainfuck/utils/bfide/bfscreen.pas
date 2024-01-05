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

unit bfScreen;

interface

const
  UPDATE_ALL                 = -1;
  UPDATE_DATA                = $0001;
  UPDATE_STDOUT              = $0002;
  UPDATE_MESSAGES            = $0004;
  UPDATE_LINES               = $0008;
  UPDATE_EDITOR_CURSOR       = $0000; { !!! }
  UPDATE_EDITOR_INSTR_PTR    = $0010;
  UPDATE_EDITOR_CURRENT_LINE = $0020;
  UPDATE_EDITOR_ALL          = $0040;
  UPDATE_EDITOR              = $0070;

procedure update_screen(options: Integer);

implementation

uses
  Crt,
  consts, utils,
  config, bfEmul, bfEdit, bfMsg;

procedure update_screen(options: Integer);
var
  i, j, addr: Integer;
  curline: PString;
begin
  hide_cursor;
  if (options and UPDATE_LINES <> 0) then
    begin
      at(EDITOR_LEFT, DATA_HEIGHT + 1, strmul(ch_ew, EDITOR_WIDTH) + ch_nesw + strmul(ch_ew, DATA_WIDTH + 2), COLOR_LINES);
      for j := DATA_HEIGHT + 2 to SCREEN_HEIGHT do
        at(DATA_LEFT - 2, j, ch_ns, COLOR_LINES);
    end;
  if (options and UPDATE_DATA <> 0) then
    begin
      addr := emulator.data_offset;
      for j := 1 to DATA_HEIGHT do
        begin
          at(DATA_LEFT - 2, j, ch_ns + ' ' + strhex(addr, 4) + ': ', COLOR_LINES);
          for i := 0 to 7 do
            begin
              if (addr + i = emulator.dataptr) then
                at(DATA_LEFT + 6 + 3 * i, j, strhex(emulator.data^[addr + i], 2), COLOR_DATAPTR)
              else
                at(DATA_LEFT + 6 + 3 * i, j, strhex(emulator.data^[addr + i], 2), COLOR_DATA);
              at(DATA_LEFT + 8 + 3 * i, j, ' ', COLOR_DATA);
            end;
          Inc(addr, 8);
        end;
    end;
  if (options and UPDATE_EDITOR <> 0) then
    update_the_editor(options);
  if (options and UPDATE_STDOUT <> 0) then
    begin
      Window(STDOUT_LEFT, STDOUT_TOP, STDOUT_LEFT + STDOUT_WIDTH - 1, STDOUT_TOP + STDOUT_HEIGHT - 1);
      TextAttr := COLOR_STDOUT;
      ClrScr;
      Window(1, 1, SCREEN_WIDTH, SCREEN_HEIGHT);
    end;
  if (options and UPDATE_MESSAGES <> 0) then
    begin
      Window(MESSAGES_LEFT, MESSAGES_TOP, MESSAGES_LEFT + MESSAGES_WIDTH - 1, MESSAGES_TOP + MESSAGES_HEIGHT - 1);
      TextAttr := COLOR_MESSAGES;
      ClrScr;
      Window(1, 1, SCREEN_WIDTH, SCREEN_HEIGHT);
      message.message_pos.line := 1;
    end;
  GotoXY(EDITOR_LINESTART + editor.cursor.col - 1,
         EDITOR_TOP + editor.cursor.line - 1 - editor.start_line);
  show_cursor;
end;

end.
