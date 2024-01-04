/*
 *  BF2MIPSAsm.java
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
 * Program Name:  BF2MIPSAsm
 * Version:       1.0
 * Date:          2003-03-18
 * Description:   Converts Brainfuck source to MIPS Assembly source
 * License:       GPL
 * Web page:      http://www.brainfuck.ca
 * Download:      http://www.brainfuck.ca/BF2MIPSAsm.java
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
 * Related Progs: BF2X86Asm BF2Java BF2C
 * Category:      Software Development > Programming language conversion
 */

import java.util.Stack;
import java.io.BufferedReader;
import java.io.FileReader;

/**
 *  BF2MIPSAsm - Convert Brainfuck to Optimized MIPS Assembly (Executable in SPIM)
 *  @author Thomas Cort (<A HREF="mailto:tom@tomcort.com">tom@tomcort.com</A>)
 *  @version 1.1 2003-03-16
 *  @since   1.0
 */
public class BF2MIPSAsm {

  // Text Segment Start
  String asmBegin  = ".text\n" +
                     ".globl __start\n" +
                     "__start:\n";

  String asmCode   = "";

  // Exit System Call
  String asmExit   = "li $v0,10\n" +
                     "syscall\n";

  // Data Segment Start
  String asmData   = ".data\n" +
                     "output: .space 16\n" +
                     "array1: .space 32768\n" +
                     "index1: .byte 0\n";

  char[] input;
  Stack stack;
  int loopCntr, plusCntr, minCntr, incCntr, decCntr;

  /**
   *  Constructor(String)
   *  @param String - Brainfuck Code
   *  @since 1.0
   */
  public BF2MIPSAsm(String s) {
    input = s.toCharArray();
    stack = new Stack();
    loopCntr = 0;
    plusCntr = 0;
    minCntr = 0;
    incCntr = 0;
    decCntr = 0;
  }

  /**
   *  Converts the input BF Code to MIPS Assembly
   *  @return String - MIPS Code
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

    return asmBegin + asmCode + asmExit + asmData;
  }


  /**
   *  Generates assembly for incrementing the pointer.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String incPtr() {
    String asmIncPtr = "lb $t1,index1\n" +
                       "add $t1,"+incCntr+"\n" +
                       "sb $t1,index1\n";
    incCntr = 0;
    return asmIncPtr;
  }

  /**
   *  Generates assembly for decrementing the pointer.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String decPtr() {
    String asmDecPtr = "lb $t1,index1\n" +
                       "sub $t1,"+decCntr+"\n" +
                       "sb $t1,index1\n";
    decCntr = 0;
    return asmDecPtr;
  }

  /**
   *  Generates assembly for incrementing the value at the pointer.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String inVPtr() {
    String asmInVPtr = "la $s0,array1\n"+
                       "lw $s1,index1\n" +
                       "add $s0,$s0, $s1\n"+
                       "lb $t1,($s0)\n" +
                       "add $t1,"+plusCntr+"\n" +
                       "sb $t1,($s0)\n";
    plusCntr = 0;
    return asmInVPtr;
  }

  /**
   *  Generates assembly for decrementing the value at the pointer.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String deVPtr() {
    String asmDeVPtr = "la $s0,array1\n"+
                       "lw $s1,index1\n" +
                       "add $s0,$s0,$s1\n"+
                       "lb $t1,($s0)\n"+
                       "sub $t1,"+minCntr+"\n" +
                       "sb $t1,($s0)\n";
    minCntr = 0;
    return asmDeVPtr;
  }

  /**
   *  Generates assembly for user input.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String input() {
    return "li $v0,5\n" +
           "syscall\n" +
           "la $s0,array1\n"+
           "lw $s1,index1\n" +
           "add $s0,$s0,$s1\n" +
           "sb $v0,($s0)\n";
  }

  /**
   *  Generates assembly for output.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String output() {
    return "la $s0,array1\n" +
	   "lw $s1,index1\n" +
	   "add $s0,$s0,$s1\n" +
           "lb $t1,($s0)\n" +
           "la $a0,output\n" +
           "sb $t1,($a0)\n" +
           "la $a0,output\n" +
           "li $v0,4\n" +
           "syscall\n";
  }

  /**
   *  Generates assembly for the beginning of loops.
   *  @return String - assembly code
   *  @since 1.0
   */
  public String startLoop() {
  	stack.push(String.valueOf(loopCntr));
  	String tmp = "loop" + loopCntr + ":\n" +
                 "la $s0,array1\n" +
                 "lw $s1,index1\n" +
                 "add $s0,$s0,$s1\n" +
                 "lb $t1,($s0)\n" +
                 "beq $t1,$0,done" + loopCntr + "\n";
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
    return "j    loop" + loopNum + "\n"+
           "done" + loopNum + ":\n";
  }

  public static void main(String [] args) {
    BF2MIPSAsm b = new BF2MIPSAsm("");
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

      b = new BF2MIPSAsm(input);
      System.out.println(b.convert());
    }
  }
}

