/* 
 * This is the w4r3z filter, written by Ian Johnston, reaper@muppetlabs.com.  
 * 
 * Copyright (C) 1998  Ian Johnston
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * or copies are available at the GNU website: http://www.gnu.org/
 *
 * Ian Johnston can be reached as reaper@speakeasy.org
 * 
 * 
 * Compilation instructions:
 *
 * $ lex warez.l
 * $ cc lex.yy.c -o warez -lfl -Wall
 *
 * This will produce an executable program 'warez' which will act as a
 * text filter, accepting input on stdin, and printing output on stdout.
 * A common usage might be:
 *
 * warez < textfile > outputfile
 *
 * - or -
 *
 * cat testfile | warez > outputfile
 *
 */


%option warn
%option nounput
%e 2000
%p 5000
%n 1000
%k 500
%a 4000
%o 2000
BW [      ]
EW [      .,;!?]

%{

#include <stdio.h>
#include <time.h>

	char buf[128];

	char * a_array[] = {"4", "4", "4", "a", "a", "A", "|\\", "@"};
#define A_LEN (sizeof(a_array) / sizeof(a_array[0]))
	char * b_array[] = {"8", "b", "b", "B"};
#define B_LEN (sizeof(b_array) / sizeof(b_array[0]))
	char * c_array[] = {"c", "c", "C", "k", "k", "<"};
#define C_LEN (sizeof(c_array) / sizeof(c_array[0]))
	char * d_array[] = {"d", "d", "D", "|)"};
#define D_LEN (sizeof(d_array) / sizeof(d_array[0]))
	char * e_array[] = {"3", "3", "3", "e", "E"};
#define E_LEN (sizeof(e_array) / sizeof(e_array[0]))
	char * f_array[] = {"f", "f", "F", "ph", "ph"};
#define F_LEN (sizeof(f_array) / sizeof(f_array[0]))
	char * g_array[] = {"6", "g", "g", "G"};
#define G_LEN (sizeof(g_array) / sizeof(g_array[0]))
	char * h_array[] = {"h", "h", "H", "|-|"};
#define H_LEN (sizeof(h_array) / sizeof(h_array[0]))
	char * i_array[] = {"1", "i", "I", "!", "Y", "|"};
#define I_LEN (sizeof(i_array) / sizeof(i_array[0]))
	char * j_array[] = {"j", "j", "J", ";"};
#define J_LEN (sizeof(j_array) / sizeof(j_array[0]))
	char * k_array[] = {"k", "k", "K", "|<", "c", "C"};
#define K_LEN (sizeof(k_array) / sizeof(k_array[0]))
	char * l_array[] = {"1", "l", "l", "L"};
#define L_LEN (sizeof(l_array) / sizeof(l_array[0]))
	char * m_array[] = {"m", "m", "M", "|~|"};
#define M_LEN (sizeof(m_array) / sizeof(m_array[0]))
	char * n_array[] = {"n", "n", "n", "n", "N", "N", "|\\|", "gn"};
#define N_LEN (sizeof(n_array) / sizeof(n_array[0]))
	char * o_array[] = {"0", "o", "O", "()", "0", "0"};
#define O_LEN (sizeof(o_array) / sizeof(o_array[0]))
	char * p_array[] = {"p", "P"};
#define P_LEN (sizeof(p_array) / sizeof(p_array[0]))
	char * q_array[] = {"q", "Q"};
#define Q_LEN (sizeof(q_array) / sizeof(q_array[0]))
	char * r_array[] = {"r", "R"};
#define R_LEN (sizeof(r_array) / sizeof(r_array[0]))
	char * s_array[] = {"5", "z", "Z", "s", "S"};
#define S_LEN (sizeof(s_array) / sizeof(s_array[0]))
	char * t_array[] = {"7", "t", "T"};
#define T_LEN (sizeof(t_array) / sizeof(t_array[0]))
	char * u_array[] = {"u", "U"};
#define U_LEN (sizeof(u_array) / sizeof(u_array[0]))
	char * v_array[] = {"v", "v", "V", "\\/"};
#define V_LEN (sizeof(v_array) / sizeof(v_array[0]))
	char * w_array[] = {"w", "w", "W", "W", "\\/\\/"};
#define W_LEN (sizeof(w_array) / sizeof(w_array[0]))
	char * x_array[] = {"x", "X"};
#define X_LEN (sizeof(x_array) / sizeof(x_array[0]))
	char * y_array[] = {"y", "Y"};
#define Y_LEN (sizeof(y_array) / sizeof(y_array[0]))
	char * z_array[] = {"s", "S", "z", "z", "Z"};
#define Z_LEN (sizeof(z_array) / sizeof(z_array[0]))

static void do_rand (char **, int);

%}

%%
[aA]	{ do_rand(a_array, A_LEN); }
[bB]	{ do_rand(b_array, B_LEN); }
[cC]	{ do_rand(c_array, C_LEN); }
[dD]	{ do_rand(d_array, D_LEN); }
[eE]	{ do_rand(e_array, E_LEN); }
[fF]	{ do_rand(f_array, F_LEN); }
[gG]	{ do_rand(g_array, G_LEN); }
[hH]	{ do_rand(h_array, H_LEN); }
[iI]	{ do_rand(i_array, I_LEN); }
[jJ]	{ do_rand(j_array, J_LEN); }
[kK]	{ do_rand(k_array, K_LEN); }
[lL]	{ do_rand(l_array, L_LEN); }
[mM]	{ do_rand(m_array, M_LEN); }
[nN]	{ do_rand(n_array, N_LEN); }
[oO]	{ do_rand(o_array, O_LEN); }
[pP]	{ do_rand(p_array, P_LEN); }
[qQ]	{ do_rand(q_array, Q_LEN); }
[rR]	{ do_rand(r_array, R_LEN); }
[sS]	{ do_rand(s_array, S_LEN); }
[tT]	{ do_rand(t_array, T_LEN); }
[uU]	{ do_rand(u_array, U_LEN); }
[vV]	{ do_rand(v_array, V_LEN); }
[wW]	{ do_rand(w_array, W_LEN); }
[xX]	{ do_rand(x_array, X_LEN); }
[yY]	{ do_rand(y_array, Y_LEN); }
[zZ]	{ do_rand(z_array, Z_LEN); }
" you"	{ printf(" U"); }
You	{ printf("u"); }
" see"	{ printf(" C"); }
See	{ printf("c"); }
" are"	{ printf(" R"); }
Are	{ printf("r"); }
dude	{ printf("d00d"); }
Dude	{ printf("D00d"); }

.	{ printf(yytext); }
\n	{ printf("\n"); }

%%

/* functions and main */

void do_rand(char ** array, int length)
{
	int i = rand() % length;
	fputs(array[i], stdout);
}

int main()
{
	srand(time(NULL));
	yylex();
	return(0);
}

