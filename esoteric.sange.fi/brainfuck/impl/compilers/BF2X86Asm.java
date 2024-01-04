/*
 *  BF2X86Asm
 *  Copyright (C) 2003 Thomas Cort
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

/*
 * Program Name:  BF2X86Asm
 * Version:       1.0
 * Date:          2003-03-18
 * Description:   Converts Brainfuck source to X86 Assembly source
 * License:       GPL
 * Web page:      http://www.brainfuck.ca
 * Download:      http://www.brainfuck.ca/BF2X86Asm.java
 * Source Info:   http://www.brainfuck.ca/downloads.html
 * Latest Ver:    http://www.brainfuck.ca/downloads.html
 * Documentation: None
 * Help:          tom@brainfuck.ca
 * Developement:  tom@brainfuck.ca
 * Bugs:          tom@brainfuck.ca
 * Maintainer:    Thomas Cort <tom@brainfuck.ca>
 * Developer:     Thomas Cort <tom@brainfuck.ca>
 * Interfaces:    Command Line
 * Source Lang:   Java
 * Build Prereq:  None
 * Related Progs: BF2MIPSAsm BF2Java BF2C
 * Category:      Software Development > Programming language conversion
 */

import java.util.Stack;
import java.io.BufferedReader;
import java.io.FileReader;

/**
 *  BF2X86SAsm - Convert Brainfuck to X86 Assembly (Compiles in TASM)
 *  @author Thomas Cort (<A HREF="mailto:tom@tomcort.com">tom@tomcort.com</A>)
 *  @version 1.1 2003-03-16
 *  @since   1.0
 */
public class BF2X86Asm {

  // Text Segment Start
  String asmBegin  = ".model small\n" +
                     ".stack 100h\n" +
                     ".data\n" +
                     "array1	DB	32768 DUP(0)\n" +
                     "array2	DB	1 DUP(0)\n" +
                     "blank	DB	'$'\n" +
                     ".code\n" +
                     "main proc\n" +
                     "mov ax,@data\n" +
                     "mov ds,ax\n" +
                     "mov bx,0\n";


  String asmCode   = "";

  // Exit System Call
  String asmExit   = "mov ax,4C00h\n" +
                     "int 21h\n" +
                     "main endp\n" +
                     "end main\n";



  char[] input;
  Stack stack;
  int loopCntr, plusCntr, minCntr, incCntr, decCntr;

  /**
   *  Constructor(String)
   *  @param String - Brainfuck Code
   *  @since 1.0
   */
  public BF2X86Asm(String s) {
    input = s.toCharArray();
    stack = new Stack();
    loopCntr = 0;
    plusCntr = 0;
    minCntr = 0;
    incCntr = 0;
    decCntr = 0;
  }

  /**
   *  Converts the input BF Code to X86 Assembly
   *  @return String - X86 Code
   *  @since 1.0
   */
  public String convert() {
    for(int x = 0; x < input.length; x++) {

      // Optimize Repeating commands
      if      (input[x] == '+') plusCntr++;
      else if (x > 0 && input[x-1] =='+') asmCode += inVPtr();

      if      (input[x] == '-') minCntr++;
      else if (x > 0 && input[x-1] == '-') asmCode += deVPtr();

      if      (input[x] == '>') incCntr++;
      else if (x > 0 && input[x-1] == '>') asmCode += incPtr();

      if (input[x] == '<') decCntr++;
      else if (x > 0 && input[x-1] == '<') asmCode += decPtr();

      if      (input[x] == '[') asmCode += startLoop();
      else if (input[x] == ']') asmCode += endLoop();
      else if (input[x] == '.') asmCode += output();
      else if (input[x] == ',') asmCode += input();
    }

    return asmBegin + asmCode + asmExit;
  }


  /**
   *  Generates assembly for incrementing the pointer.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String incPtr() {
    String s = "add bx," + incCntr + "\n";
    incCntr = 0;
    return s;
  }

  /**
   *  Generates assembly for decrementing the pointer.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String decPtr() {
    String s = "sub bx," + decCntr + "\n";
    decCntr = 0;
    return s;
  }

  /**
   *  Generates assembly for incrementing the value at the pointer.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String inVPtr() {
    String s="mov al, [array1 + bx]\n" +
             "add al, "+ plusCntr + "\n"+
             "mov [array1 + bx], al\n";
    plusCntr = 0;
    return s;
  }

  /**
   *  Generates assembly for decrementing the value at the pointer.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String deVPtr() {
    String s="mov al, [array1 + bx]\n" +
             "sub al, "+ minCntr + "\n"+
             "mov [array1 + bx], al\n";
    minCntr = 0;
    return s;
  }

  /**
   *  Generates assembly for user input.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String input() {
    return "xor ah,ah\n" +
           "int 16h\n" +
           "mov [array1+bx],al\n";
  }

  /**
   *  Generates assembly for output.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String output() {
    return "mov al,[array1+bx]\n" +
           "mov [array2],al\n" +
           "mov ah,9\n" +
           "mov dx,offset array2\n" +
           "int 21h\n";
  }

  /**
   *  Generates assembly for the beginning of loops.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String startLoop() {
  	stack.push(String.valueOf(loopCntr));
  	String tmp = "loop" + loopCntr + ":\n" +
                 "mov al, [array1+bx]\n" +
                 "cmp al, 0\n" +
                 "je done" + loopCntr + "\n";
    loopCntr++;
    return tmp;
  }

  /**
   *  Generates assembly for the end of loops.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String endLoop() {
    String loopNum =(String)stack.pop();
    return "jmp    loop" + loopNum + "\n"+
           "done" + loopNum + ":\n";
  }

  public static void main(String [] args) {
    BF2X86Asm b = new BF2X86Asm("");
    BufferedReader reader;
    String line = "", input = "", filename = "";

    // Read each file and interpret.
    for(int z = 0; z < args.length; z++) {
      filename = args[z];
      input = "";

      try {
        reader = new BufferedReader( new FileReader( filename ) );
        while ( (line = reader.readLine()) != null )
          input += line;
      } catch (Exception e) {
        throw new Error("Cannot read input file");
      }

      b = new BF2X86Asm(input);
      System.out.println(b.convert());
    }
  }
}

