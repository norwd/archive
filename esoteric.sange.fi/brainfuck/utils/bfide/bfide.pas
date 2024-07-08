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

(*
    The emulator recognized the following keys:

      F7   - one step
      F8   - goto end of loop
      F9   - run contiguously
      C-F2 - terminate the program
      C-N  - clear the editor and start a new file
      C-O  - load a file from disk
      C-S  - save a file to disk
      C-T  - print the value of the current stack pointer
      C-A  - output the size of free memory
      C-C  - clear the messages window (lower left corner)
      C-Q  - quit
*)

uses
  Crt,
  consts, utils,
  config, bfEmul, bfEdit, bfMsg, bfScreen;

procedure init_status;
begin
  new(emulator.data);
  new(emulator.code);
  new(emulator.stack);
end;

procedure load_file;
var
  fname: string;
begin
  if (load_program(message_input('load: ')) = -1) then
    write_message('file not found.');
end;

procedure save_file;
var
  fname: string;
begin
  if (save_program(message_input('save as: ')) = -1) then
    write_message('error saving the file.');
end;

var
  taste, vk_taste: Char;
  i: Integer;
begin
  ClrScr;
  init_status;
  reset_program(True, True);
  update_screen(UPDATE_ALL);
  repeat
    if (myKeyPressed or (emulator.running_mode in [rm_paused, rm_stopped])) then
      begin
        while not myKeyPressed do
          asm sti; hlt; end; { DOS Power Management }
        taste := ReadKey;
        case taste of
          kb_extended: begin
            vk_taste := ReadKey;
            case vk_taste of
              kbx_ctrl_f2:
                begin
                  reset_program(False, True);
                  update_screen(UPDATE_EDITOR_INSTR_PTR or UPDATE_DATA);
                end;
              kbx_f7:
                emulator.running_mode := rm_singlestep;
              kbx_f8:
                emulator.running_mode := rm_endofloop;
              kbx_f9:
                emulator.running_mode := rm_running;
              kbx_down:
                editor_down(True);
              kbx_up:
                editor_up(True);
              kbx_pgdown:
                editor_pgdown(True);
              kbx_pgup:
                editor_pgup(True);
              kbx_home: begin
                editor.cursor.col := 1;
                update_screen(UPDATE_EDITOR_CURSOR);
              end;
              kbx_left: if (editor.cursor.col > 1) then
                begin
                  Dec(editor.cursor.col);
                  update_screen(UPDATE_EDITOR_CURSOR);
                end;
              kbx_end: begin
                editor.cursor.col := Length(emulator.code^
                    [editor.cursor.line - 1]^) + 1;
                update_screen(UPDATE_EDITOR_CURSOR);
              end;
              kbx_right: if (editor.cursor.col < Length(emulator.code^
                    [editor.cursor.line - 1]^) + 1) then
                begin
                  Inc(editor.cursor.col);
                  update_screen(UPDATE_EDITOR_CURSOR);
                end;
              kbx_delete:
                delete_char_here;
              else
                Write(ch_bell);
            end;
          end;
          kb_ctrl_q:
            emulator.running_mode := rm_stopped;
          kb_ctrl_o:
            load_file;
          kb_ctrl_t:
            write_message(itoa(emulator.stackptr));
          kb_ctrl_s:
            save_file;
          #032..#255:
            insert_char_here(taste);
          kb_backspace:
            delete_char_before;
          kb_return:
            insert_line_here;
          kb_ctrl_a:
            write_message('MemAvail: ' + ltoa(MemAvail));
          kb_ctrl_c:
            update_screen(UPDATE_MESSAGES);
          kb_ctrl_n:
            begin
              reset_program(True, True);
              update_screen(UPDATE_ALL);
            end;
          else
            Write(ch_bell);
        end;
      end;
    case emulator.running_mode of
      rm_singlestep:
        begin
          if execute_step then
            emulator.running_mode := rm_paused
          else
            emulator.need_to_reset := True;
          update_screen(UPDATE_EDITOR_INSTR_PTR or UPDATE_DATA);
        end;
      rm_endofloop:
        begin
          if not execute_step then
            begin
              emulator.need_to_reset := True;
              update_screen(UPDATE_EDITOR_INSTR_PTR or UPDATE_DATA);
            end
          else if (current_instruction = '[') then
            begin
              emulator.running_mode := rm_paused;
              update_screen(UPDATE_EDITOR_INSTR_PTR or UPDATE_DATA);
            end;
        end;
      rm_running:
        if not execute_step then
          begin
            emulator.need_to_reset := True;
            update_screen(UPDATE_EDITOR_INSTR_PTR or UPDATE_DATA);
          end;
      rm_stopping:
        begin
          emulator.need_to_reset := True;
          update_screen(UPDATE_EDITOR_INSTR_PTR or UPDATE_DATA);
          emulator.running_mode := rm_stopped;
        end;
    end;
  until taste = kb_ctrl_q;
  TextAttr := $07;
  ClrScr;
end.
