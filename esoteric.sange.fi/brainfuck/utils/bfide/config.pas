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

unit config;

interface

uses
  Crt;

const
  MAX_CODE_LINES = 1000;
  DATA_SIZE      = $8000;
  LOOPSTACK_SIZE = 1000;

  SCREEN_WIDTH   = 80;
  SCREEN_HEIGHT  = 25;
  DATA_WIDTH     = 29;
  DATA_HEIGHT    = 19;
  DATA_LEFT      = SCREEN_WIDTH - DATA_WIDTH;
  DATA_TOP       = 1;
  EDITOR_HEIGHT  = DATA_HEIGHT;
  EDITOR_WIDTH   = SCREEN_WIDTH - DATA_WIDTH - 3;
  EDITOR_LEFT    = 1;
  EDITOR_TOP     = 1;
  EDITOR_LINEWIDTH = EDITOR_WIDTH - 6;
  EDITOR_LINESTART = EDITOR_LEFT + 6;
  STDOUT_LEFT    = DATA_LEFT - 1;
  STDOUT_TOP     = DATA_TOP + DATA_HEIGHT + 1;
  STDOUT_WIDTH   = 1 + SCREEN_WIDTH - STDOUT_LEFT;
  STDOUT_HEIGHT  = 1 + SCREEN_HEIGHT - STDOUT_TOP;
  MESSAGES_LEFT  = 1;
  MESSAGES_TOP   = EDITOR_TOP + EDITOR_HEIGHT + 1;
  MESSAGES_WIDTH = EDITOR_WIDTH;
  MESSAGES_HEIGHT = 1 + SCREEN_HEIGHT - MESSAGES_TOP;

  COLOR_BG       = blue;
  COLOR_SCREEN   = lightgray + 16 * COLOR_BG;
  COLOR_LINES    = COLOR_SCREEN;
  COLOR_DATAPTR  = yellow + 16 * magenta;
  COLOR_DATA     = COLOR_SCREEN;
  COLOR_STDOUT   = COLOR_SCREEN;
  COLOR_MESSAGES = COLOR_SCREEN;
  COLOR_EDITOR   = COLOR_SCREEN;
  COLOR_COMMAND  = yellow + 16 * COLOR_BG;
  COLOR_COMMENT  = lightgray + 16 * COLOR_BG;
  COLOR_CURRENT  = COLOR_DATAPTR;

implementation

end.
