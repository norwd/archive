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

unit utils;

interface

type
  PString = ^String;

procedure strkill(var s: PString);
function strdup(const s: string): PString;
procedure at(x, y: Integer; const s: string; c: Byte);
function strhex(n, stellen: Integer): String;
function itoa(i: Integer): string;
function ltoa(i: LongInt): string;
function strmul(const s: string; n: Integer): string;
function strexpand(s: string; len: Integer): string;
function linenumber(i, len: Integer): string;

procedure hide_cursor;
procedure show_cursor;
function myKeyPressed: Boolean;

implementation

uses
  Crt,
  consts;

const
  cursor_value: Integer = 0;

procedure strkill(var s: PString);
begin
  if ((s <> @str_empty) and (s <> nil)) then
    FreeMem(s, Length(s^) + 1);
  s := nil;
end;

function strdup(const s: string): PString;
var
  p: PString;
begin
  if s = '' then
    strdup := @str_empty
  else
    begin
      GetMem(p, Length(s) + 1);
      Move(s, p^, Length(s) + 1);
      strdup := p;
    end;
end;

procedure at(x, y: Integer; const s: string; c: Byte);
begin
  TextAttr := c;
  GotoXY(x, y);
  Write(s);
end;

function strhex(n, stellen: Integer): String;
var
  s: String;
  i: Integer;
begin
  s := '';
  for i := 0 to stellen-1 do
    s := ch_hexdigit[(n shr (4 * i)) and $0F] + s;
  strhex := s;
end;

function itoa(i: Integer): string;
var
  s: string;
begin
  Str(i, s);
  itoa := s;
end;

function ltoa(i: LongInt): string;
var
  s: string;
begin
  Str(i, s);
  ltoa := s;
end;

function strmul(const s: string; n: Integer): string;
var
  t: string;
begin
  t := '';
  for n := n downto 1 do
    t := t + s;
  strmul := t;
end;

function strexpand(s: string; len: Integer): string;
begin
  while Length(s) < len do
    s := s + ' ';
  strexpand := s;
end;

function linenumber(i, len: Integer): string;
var
  s: string;
begin
  Str(i, s);
  while Length(s) < len do
    s := '0' + s;
  linenumber := s;
end;

procedure hide_cursor;
begin
  Dec(cursor_value);
  if (cursor_value = -1) then
    asm
      mov ah, 0fh
      int 10h
      mov ah, 03h
      int 10h
      or  ch, 20h
      mov ah, 01h
      int 10h
    end;
end;

procedure show_cursor;
begin
  Inc(cursor_value);
  if (cursor_value = 0) then
    asm
      mov ah, 0fh
      int 10h
      mov ah, 03h
      int 10h
      and ch, not 20h
      mov ah, 01h
      int 10h
    end;
end;

function myKeyPressed: Boolean;
{ There's a problem with the original KeyPressed }
{ routine, so I used this.                       }
begin
  myKeyPressed := mem[Seg0040:$001A] <> mem[Seg0040:$001C];
end;

end.