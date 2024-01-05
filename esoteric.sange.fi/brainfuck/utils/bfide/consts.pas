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

unit consts;

interface

const
  kb_backspace  = #008;
  kb_ctrl_a     = #001;
  kb_ctrl_b     = #002;
  kb_ctrl_c     = #003;
  kb_ctrl_d     = #004;
  kb_ctrl_e     = #005;
  kb_ctrl_f     = #006;
  kb_ctrl_g     = #007;
  kb_ctrl_h     = #008;
  kb_ctrl_i     = #009;
  kb_ctrl_j     = #010;
  kb_ctrl_k     = #011;
  kb_ctrl_l     = #012;
  kb_ctrl_m     = #013;
  kb_ctrl_n     = #014;
  kb_ctrl_o     = #015;
  kb_ctrl_p     = #016;
  kb_ctrl_q     = #017;
  kb_ctrl_r     = #018;
  kb_ctrl_s     = #019;
  kb_ctrl_t     = #020;
  kb_ctrl_u     = #021;
  kb_ctrl_v     = #022;
  kb_ctrl_w     = #023;
  kb_ctrl_x     = #024;
  kb_ctrl_y     = #025;
  kb_ctrl_z     = #026;

  kb_return     = #013;
  kb_esc        = #027;
  kb_extended   = #000;
  kbx_F1        = #059; kbx_ctrl_F1  = #094;
  kbx_F2        = #060; kbx_ctrl_F2  = #095;
  kbx_F3        = #061;
  kbx_F4        = #062;
  kbx_F5        = #063;
  kbx_F6        = #064;
  kbx_F7        = #065;
  kbx_F8        = #066;
  kbx_F9        = #067;
  kbx_F10       = #068;

  kbx_home      = #071;
  kbx_up        = #072;
  kbx_pgup      = #073;
  kbx_left      = #075;
  kbx_right     = #077;
  kbx_end       = #079;
  kbx_down      = #080;
  kbx_pgdown    = #081;
  kbx_insert    = #082;
  kbx_delete    = #083;

  ch_bell       = #007;
  ch_cr         = #013;
  ch_nl         = #010;
  ch_ns         = '³';
  ch_nsw        = '´';
  ch_nsww       = 'µ';
  ch_nnssw      = '¶';
  ch_ssw        = '·';
  ch_sww        = '¸';
  ch_nnssww     = '¹';
  ch_nnss       = 'º';
  ch_ssww       = '»';
  ch_nnw        = '½';
  ch_nww        = '¾';
  ch_sw         = '¿';
  ch_ne         = 'À';
  ch_new        = 'Á';
  ch_esw        = 'Â';
  ch_nes        = 'Ã';
  ch_ew         = 'Ä';
  ch_nesw       = 'Å';
  ch_nees       = 'Æ';
  ch_nness      = 'Ç';
  ch_nnee       = 'È';
  ch_eess       = 'É';
  ch_nneeww     = 'Ê';
  ch_eessww     = 'Ë';
  ch_nneess     = 'Ì';
  ch_eeww       = 'Í';
  ch_nneessww   = 'Î';
  ch_neeww      = 'Ï';
  ch_nnew       = 'Ð';
  ch_eesww      = 'Ñ';
  ch_essw       = 'Ò';
  ch_nne        = 'Ó';
  ch_nee        = 'Ô';
  ch_ees        = 'Õ';
  ch_ess        = 'Ö';
  ch_nnessw     = '×';
  ch_neesww     = 'Ø';
  ch_nw         = 'Ù';
  ch_es         = 'Ú';
  ch_fill25     = '°';
  ch_fill50     = '±';
  ch_fill75     = '²';
  ch_fill100    = 'Û';
  ch_box        = 'Û';
  ch_botbox     = 'Ü';
  ch_leftbox    = 'Ý';
  ch_rightbox   = 'Þ';
  ch_topbox     = 'ß';

  str_empty: String[1] = '';
  ch_hexdigit: array [0..15] of Char = '0123456789ABCDEF';

implementation

end.
