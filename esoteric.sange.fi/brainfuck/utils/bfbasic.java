//====================================================================
// BFBASIC -- Basic programming language compiler for BF
// Filename : bfbasic.java
// Language : Java 1.2+
// Version  : 1.30
// Copyright: (C) 2001 Jeffry Johnston
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation. See the file LICENSE
// for more details.
//
// Version history.  See bfbasic.txt for more information:
// 1.30    30 Oct 2003
// 1.20    23 Oct 2003
// 1.10    16 Oct 2003
// 1.00    15 Oct 2003
// 0.90    23 Sep 2003
// 0.80    20 Sep 2003
// 0.70    14 Mar 2003
// 0.60    12 Mar 2003
// 0.50    11 Mar 2003 Initial release
//====================================================================

import java.util.*;
import java.io.*;

//********************************************************************
// bfbasic
//********************************************************************
public class bfbasic {
  public static final String VERSION = "1.30";

  static boolean debug = false, insert = false, crlf = false,
                 needpre = true, needpost = false;
  static BufferedReader in; // Java 1.1
  static PrintStream out;
  static HashMap var = new HashMap(), label = new HashMap(); // Java 1.2
  static int varnext = 0, line = 0, mp = 0, linepos = 1;
  static String p = "", sourceline = "";
  static char a;
  static Stack dostack = new Stack(), forstack = new Stack(), ifstack = new Stack();
  static int annex = 1, doannex = 1, ifannex = 1, forannex = 1,gosubannex = 1;

  //------------------------------------------------------------------
  // main
  //------------------------------------------------------------------
  public static void main(String[] cmdline) {
    // display copyright text
    System.out.println("BFBASIC Basic Compiler, version " + VERSION
                       + ".  Copyright 2001 Jeffry Johnston.");
    System.out.println();

    // process command line
    String f = "", f2 = "";
    int n;
    for (n = 0; ; n++) {
      try {
        if (cmdline[n].equals("-?")) {
          usage();
          System.exit(0);
        } else if (cmdline[n].equalsIgnoreCase("-c")) {
          crlf = true;
        } else if (cmdline[n].equalsIgnoreCase("-d")) {
          debug = true;
        } else if (cmdline[n].equalsIgnoreCase("-o")) {
          f2 = cmdline[n+1];
          n++;
        } else {
          f = cmdline[n];
        }
      } catch (ArrayIndexOutOfBoundsException e) {
        break;
      }
    }
    if (f.equals("")) {
      usage();
      errout("Error: No input file given");
    }
    if ((n = f.indexOf('.')) == -1) {
      // create default output filename
      if (f2.equals("")) { f2 = f + ".bf"; }
      // add missing ".bas" extension
      f += ".bas";
    } else {
      // create default output filename
      if (f2.equals("")) { f2 = f.substring(0, n) + ".bf"; }
    }

    // display filenames
    System.out.println("Input file : " + f);
    System.out.println("Output file: " + f2);

    // open files
    try {
      in = new BufferedReader(new FileReader(f)); // Java 1.1
    } catch (FileNotFoundException e) {
      errout("Error opening '" + f + "'.  File not found");
    }
    try {
      out = new PrintStream(new FileOutputStream(f2));
    } catch (IOException e) {
      errout("Error opening '" + f2 + "' for output");
    }

    // output banner
    out.print("[ BF Code Produced by BFBASIC " + VERSION);
    if (debug == true) { out.print(" (debug comments)"); }
    out.println(" ]");

    // add reserved variables
    String l = "IGT0123456";
    for (n = 0; n < l.length(); n++) {
      addvar("_" + l.charAt(n), 1);
    }

    // output header
    first();

    // main loop
    while (true) {
      sourceline = sourceline.trim();

      // strip leading colons, if any
      while (sourceline.length() > 0 && sourceline.charAt(0) == ':') {
        sourceline = (sourceline.substring(1)).trim();
      }

      // remove line comment
      if (sourceline.length() > 0 && (sourceline.charAt(0) == '\'')) {
        sourceline = "";
      }

      // if line is empty, read another one
      if (sourceline.equals("")) {
        try {
          line++;
          sourceline = in.readLine();
        } catch (IOException e) {
          errout("Error reading '" + f + "'");
        }
        // no more source lines?  done compiling
        if (sourceline == null) {
          break;
        }
        sourceline = sourceline.trim();
      }

      // parse first token of statement
      parse();
      p = p.toUpperCase();
      //System.out.println("sl: {" + sourceline + "} p: {" + p + "} a: {" + a + "}");
      if (p.equals("")) {
        // NOP
      } else if (p.equals("BEEP")) {
        bf_beep();
      } else if (p.equals("BF")) {
        bf_bf();
      } else if (p.equals("CLS")) {
        bf_cls();
      } else if (p.equals("COLOR")) {
        bf_color();
      } else if (p.equals("DIM")) {
        bf_dim();
      } else if (p.equals("DO")) {
        bf_do();
      } else if (p.equals("ELSE")) {
        bf_else();
      } else if (p.equals("END")) {
        bf_end();
      } else if (p.equals("EXIT")) {
        bf_exit();
      } else if (p.equals("FOR")) {
        bf_for();
      } else if (p.equals("GOSUB")) {
        bf_gosub();
      } else if (p.equals("GOTO")) {
        bf_goto();
      } else if (p.equals("IF")) {
        bf_if();
      } else if (p.equals("INPUT")) {
        bf_input();
      } else if (p.equals("LET")) {
        parse();
        bf_let();
      } else if (p.equals("LOCATE")) {
        bf_locate();
      } else if (p.equals("LOOP")) {
        bf_loop();
      } else if (p.equals("NEXT")) {
        bf_next();
      } else if (p.equals("ONGOTO")) {
        bf_ongoto();
      } else if (p.equals("PRINT")) {
        bf_print();
      } else if (p.equals("RANDOMIZE")) {
        bf_randomize();
      } else if (p.equals("REM")) {
        bf_rem();
      } else if (p.equals("RETURN")) {
        bf_return();
      } else if (p.equals("STOP")) {
        bf_end();
      } else if (p.equals("SWAP")) {
        bf_swap();
      } else if (p.equals("SYSTEM")) {
        bf_end();
      } else if (p.equals("WEND")) {
        bf_loop();
      } else if (p.equals("WHILE")) {
        sourceline = "WHILE " + sourceline;
        bf_do();
      } else if (p.equals("?")) {
        bf_print();
      } else if (a == ':') {
        bf_label();
      } else {
        bf_let();
      }
    }

    // output footer
    last();
    if (debug == true) { write("\n"); }
    write("@\n");

    // display successful completion text
    System.out.println();
    System.out.println("Done, line " + line + ".");
  }

  //------------------------------------------------------------------
  // addvar -- adds a new variable name and size to internal table
  //------------------------------------------------------------------
  public static void addvar(String varname, int elements) {
    varname = varname.toUpperCase();
    for (int n = 0; n < varname.length(); n++) {
      char c = varname.charAt(n);
      if ((n == 0 && (c < '0' || c > '9')) && ((c < 'A' || c > 'Z')
          && c != '_' && c != '~')) {
        errout("Illegal variable name '" + varname + "'");
      }
    }
    if (debug == true) { write("\n(DIM " + varname + "(" + elements + "))\n"); }
    if (var.containsKey(varname)) {
      errout("Variable '" + varname + "' already dimensioned");
    }
    var.put(varname, new Integer(varnext));
    varnext += elements;
  }

  //------------------------------------------------------------------
  // arrows -- turns @ variables into BF < and >, writes code to disk
  //------------------------------------------------------------------
  public static void arrows(String o) {
    int l2, pos;
    char c;
    String varname = "";
    for (int l = 0; l < o.length(); l++) {
      // get character
      c = o.charAt(l);

      // variable
      if (c == '@') {
        // find end of variable name
        for (l2 = l + 1; l2 < o.length(); l2++) {
          if (("+-<>[].,".indexOf(o.charAt(l2))) != -1) {
            // get variable name (middle of string)
            varname = o.substring(l + 1, l2);
            break;
          } else if (l2 == o.length() - 1) {
            // get variable name (last thing in string)
            varname = o.substring(l + 1);
            l++;
          }
        }
        varname = varname.toUpperCase();
        l = l2 - 1;

        // search for variable
        pos = 0;
        if (var.containsKey(varname)) {
          pos = ((Integer) var.get(varname)).intValue();
        } else {
          // variable doesn't exist, add it
          if (varname.charAt(0) == '~') {
            addvar(varname, 23);
          } else {
            addvar(varname, 1);
          }

          // get position of newest variable
          pos = ((Integer) var.get(varname)).intValue();
        }
        if (debug == true) { write(mp + ""); }

        // output > and <
        if (mp < pos) { write(string(pos - mp, '>')); }
        if (mp > pos) { write(string(mp - pos, '<')); }
        mp = pos;
      } else {
        // output char
        write(c + "");
      }
    }
  }

  //------------------------------------------------------------------
  // bf_beep -- writes out BF code for the BEEP statement
  //------------------------------------------------------------------
  public static void bf_beep() {
    //BEEP
    //  @T0+++++++.[-]          T0=7:PRINT CHR$(T0);:T0=0
    String o = pre() + "@_0+++++++.[-]" + post();
    if (debug == true) { o = "\n(BEEP)\n" + o; }
    arrows(o);
  }

  //------------------------------------------------------------------
  // bf_bf -- writes out BF code for the BF statement
  //------------------------------------------------------------------
  public static void bf_bf() {
    sourceline = (a + sourceline).trim();
    //parse();
    //if (p.equalsIgnoreCase("END")) {
    //  // BF END
    //  needpost = true;
    //  String o = pre() + post();
    //  if (debug == true) { o = "\n(BF END)\n" + o; }
    //  arrows(o);
    //  needpre = true;
    //} else {
      //sourceline = (p + a + sourceline).trim();
      // BF (commands)
      int n;
      if ((n = sourceline.indexOf('\'')) != -1) {
        sourceline = sourceline.substring(0, n);
      }
      needpost = false;
      String o = pre() + sourceline.trim() + post();
      if (debug == true) { o = "\n(BF)\n" + o; }
      arrows(o);
      sourceline = "";
      needpre = false;
    //}
  }

  //------------------------------------------------------------------
  // bf_cls -- builds BFBASIC code for the CLS statement
  //------------------------------------------------------------------
  public static void bf_cls() {
    //CLS
    //  (...)                   builds PRINT CHR$(27) + "[2J";:
    if (debug == true) { write("\n{CLS}\n"); }
    sourceline = "PRINT \"\033[2J\";:" + sourceline;
  }

  //------------------------------------------------------------------
  // bf_color -- builds BFBASIC code for the COLOR statement
  //------------------------------------------------------------------
  public static void bf_color() {
    sourceline = (a + sourceline).trim();
    int n = findexpr("", 0);
    if (n == -1) { errout("Syntax error"); }
    String expr = (sourceline.substring(0, n)).trim();
    sourceline = "PRINT \"\033[\"; " + expr + "; \"m\";:"
                 + (sourceline.substring(n)).trim();
    if (debug == true) { write("\n{COLOR " + debugtext(expr) + "}\n"); }
  }

  //------------------------------------------------------------------
  // bf_dim -- code for the DIM statement
  //------------------------------------------------------------------
  public static void bf_dim() {
    parse();
    int n = 0;
    if (a == '(') {
      // DIM V1(#)
      String p0 = p;
      parse();
      if (a != ')') { errout("Mismatched parenthesis"); }
      try {
        n = Integer.parseInt(p);
      } catch (NumberFormatException e) {
        errout("Invalid number '" + p + "'");
      }
      if (n < 0 || n > 255) {
        errout("Array size '" + n + "' out of range (0 - 255)");
      }
      // array length=elements*2+3, elements=a+1, (a+1)*2+3=a*2+5
      addvar(p0, n * 2 + 5);
    } else {
      // DIM V1
      addvar(p, 1);
    }
  }

  //------------------------------------------------------------------
  // bf_do -- builds BFBASIC code for the DO statement
  //------------------------------------------------------------------
  public static void bf_do() {
    String p0 = "_D" + doannex;
    if (parseif() == true) {
      // no params
      // DO
      if (debug == true) { write("\n{DO}\n"); }
      dostack.push(new Integer(doannex));
    } else {
      // params
      parse();
      p = p.toUpperCase();
      if (p.equals("WHILE")) {
        // DO WHILE expr
        sourceline = (a + sourceline).trim();
        int n = findexpr("", 0);
        if (n == -1) { errout("Syntax error"); }
        String expr = (sourceline.substring(0, n)).trim();
        if (debug == true) { write("\n{DO WHILE " + debugtext(expr) + "}\n"); }
        dostack.push(new Integer(-doannex));
        sourceline = "IF NOT(" + expr + ") THEN GOTO _D" + (doannex + 1) + ":"
                     + (sourceline.substring(n)).trim();
      } else if (p.equals("UNTIL")) {
        // DO UNTIL expr
        sourceline = (a + sourceline).trim();
        int n = findexpr("", 0);
        if (n == -1) { errout("Syntax error"); }
        String expr = (sourceline.substring(0, n)).trim();
        if (debug == true) { write("\n{DO UNTIL " + debugtext(expr) + "}\n"); }
        dostack.push(new Integer(-doannex));
        sourceline = "IF " + expr + " THEN GOTO _D" + (doannex + 1) + ":"
                     + (sourceline.substring(n)).trim();
      } else {
        errout("Syntax error");
      }
    }
    p = p0;
    bf_label();
    doannex += 2;
  }

  //------------------------------------------------------------------
  // bf_else -- builds BFBASIC code for the ELSE statement
  //------------------------------------------------------------------
  public static void bf_else() {
    // ELSE
    if (debug == true) { write("\n{ELSE}\n"); }
    if (ifstack.empty()) { errout("ELSE without IF"); }
    Integer l = (Integer) ifstack.pop();
    sourceline = "GOTO _I" + ifannex + ":_I" + l + ":" + sourceline;
    ifstack.push(new Integer(ifannex++));
  }

  //------------------------------------------------------------------
  // bf_end -- writes out BF code for the END and END IF statements
  //------------------------------------------------------------------
  public static void bf_end() {
    parse();
    if (p.equalsIgnoreCase("IF")) {
      // END IF
      if (debug == true) { write("\n{END IF}\n"); }
      if (ifstack.empty()) { errout("END IF without IF"); }
      Integer l = (Integer) ifstack.pop();
      sourceline = "_I" + l + ":" + sourceline;
    } else {
      //END
      //  @IP[-]                IP=0
      //  @G-                   G=0
      needpost = true;
      sourceline = (p + a + sourceline).trim();
      String o = pre() + "@_I[-]@_G[-]" + post();
      if (debug == true) { o = "\n(END)\n" + o; }
      arrows(o);
      needpre = true;
    }
  }

  //------------------------------------------------------------------
  // bf_exit -- builds BFBASIC code for the EXIT statements
  //------------------------------------------------------------------
  public static void bf_exit() {
    parse();
    p = p.toUpperCase();
    if (p.equals("DO")) {
      if (debug == true) { write("\n{EXIT DO}\n"); }
      if (dostack.empty()) { errout("EXIT DO without DO"); }
      Integer l = (Integer) dostack.pop();
      sourceline = "GOTO _D" + (Math.abs(l.intValue()) + 1) + ":" + sourceline;
      if (l.intValue() > 0) { l = new Integer(-l.intValue()); }
      dostack.push(l);
    } else if (p.equals("FOR")) {
      if (debug == true) { write("\n{EXIT FOR}\n"); }
      if (forstack.empty()) { errout("EXIT FOR without FOR"); }
      Integer l = (Integer) forstack.pop();
      sourceline = "GOTO _F" + (Math.abs(l.intValue()) + 1) + ":" + sourceline;
      if (l.intValue() > 0) { l = new Integer(-l.intValue()); }
      forstack.push(l);
    } else {
      errout("Syntax error");
    }
  }

  //------------------------------------------------------------------
  // bf_for -- builds BFBASIC code for the FOR statement
  //------------------------------------------------------------------
  public static void bf_for() {
    // FOR expr=expr2 TO expr3
    String p0 = "_F" + forannex;
    int n = findexpr("=", 0);
    if (n == -1) { errout("Syntax error"); }
    String expr = (sourceline.substring(0, n)).trim();
    sourceline = (sourceline.substring(n + 1)).trim();
    n = findexpr("TO", 0);
    if (n == -1) { errout("Syntax error"); }
    String expr2 = (sourceline.substring(0, n)).trim();
    sourceline = (sourceline.substring(n + 2)).trim();
    n = findexpr("", 0);
    if (n == -1) { errout("Syntax error"); }
    String expr3 = (sourceline.substring(0, n)).trim();
    forstack.push(new Integer(-forannex));
    sourceline = expr + "=" + expr2 + ":" + p0
                 + ":IF " + expr + ">" + expr3 + " THEN GOTO _F" + (forannex + 1)
                 + ":" + (sourceline.substring(n)).trim();
    if (debug == true) {
      write("\n{FOR " + debugtext(expr) + "=" + debugtext(expr2)
            + " TO " + debugtext(expr3) + "}\n");
    }
    forannex += 2;
  }

  //------------------------------------------------------------------
  // bf_gosub -- builds BFBASIC code for the GOSUB statement
  //------------------------------------------------------------------
  public static void bf_gosub() {
    // GOSUB label
    p = "_G" + gosubannex++;
    labelval("","");
    String p0 = p;
    parse();
    int n = ((Integer) label.get(p0)).intValue();
    sourceline = "_GS(_GP)=" + n + ":_GP=_GP+1:GOTO " + p + ":"
                 + ":" + p0 + ":" + sourceline;
    if (debug == true) { write("\n{GOSUB " + p + "}\n"); }
  }

  //------------------------------------------------------------------
  // bf_goto -- writes out BF code for the GOTO statement
  //------------------------------------------------------------------
  public static void bf_goto() {
    //GOTO label
    //  (...)                   IP=#:G=0
    needpost = true;
    parse();
    String o = pre() + labelval("@_G", "@_I") + post();
    if (debug == true) { o = "\n(GOTO " + p +")\n" + o; }
    arrows(o);
    needpre = true;
  }

  //------------------------------------------------------------------
  // bf_if -- writes out BF code for the IF statement
  //------------------------------------------------------------------
  public static void bf_if() {
    sourceline = (a + sourceline).trim();
    int n = findexpr("THEN", 0);
    if (n == -1) { errout("IF without THEN"); }
    String expr = (sourceline.substring(0, n)).trim();
    sourceline = (sourceline.substring(n)).trim();
    parse();
    parse();
    p = p.toUpperCase();
    String o = "";
    if (p.equals("GOTO")) {
      //IF expr THEN GOTO label
      //  @TEMP0[                 IF TEMP0<>0 THEN
      //  (...)                     IP=##:G=0
      //  @TEMP0[-]]              END IF:TEMP0=0
      parse();
      if (debug == true) { o = "\n(IF " + debugtext(expr) + " THEN GOTO " + p + ")\n"; }
    } else if (p.equals("EXIT")) {
      // IF expr THEN EXIT
      parse();
      p = p.toUpperCase();
      if (p.equals("DO")) {
        // IF expr THEN EXIT DO
        if (dostack.empty()) { errout("EXIT DO without DO"); }
        Integer l = (Integer) dostack.pop();
        p = "_D" + (Math.abs(l.intValue()) + 1);
        if (l.intValue() > 0) { l = new Integer(-l.intValue()); }
        dostack.push(l);
        if (debug == true) {
          o = "\n(IF " + debugtext(expr) + " THEN {EXIT DO}(GOTO _D"
              + (Math.abs(l.intValue()) + 1) + "))\n";
        }
      } else if (p.equals("FOR")) {
        // IF expr THEN EXIT FOR
        if (forstack.empty()) { errout("EXIT FOR without FOR"); }
        Integer l = (Integer) forstack.pop();
        p = "_F" + (Math.abs(l.intValue()) + 1);
        if (l.intValue() > 0) { l = new Integer(-l.intValue()); }
        forstack.push(l);
        if (debug == true) {
          o = "\n(IF " + debugtext(expr) + " THEN {EXIT FOR}(GOTO _F"
              + (Math.abs(l.intValue()) + 1) + "))\n";
        }
      } else {
        errout("Syntax error");
      }
    } else {
      // IF expr THEN
      if (debug == true) { write("\n{IF " + debugtext(expr) + " THEN}\n"); }
      sourceline = "IF NOT(" + expr + ") THEN GOTO _I" + ifannex + ":" + sourceline;
      ifstack.push(new Integer(ifannex++));
      return;
    }
    needpost = true;
    AlgebraicExpression ae = new AlgebraicExpression(expr);
    o += pre() + ae.parse() + "@_T0[" + labelval("@_G", "@_I") + "@_T0[-]]" + post();
    arrows(o);
    needpre = true;
  }

  //------------------------------------------------------------------
  // bf_input -- writes out BF code for the INPUT statement
  //------------------------------------------------------------------
  public static void bf_input() {
    parse();
    String o = "";
    if (a == '(') {
      //INPUT V1(expr)
      //  (...)                                 TEMP0=expr
      //  @V1>>[-]<<@TEMP0[@V1>>+<<@TEMP0-]     E=B:TEMP0=0

      //  @T0+                                  T0=1
      //  [                                     DO WHILE T0<>0
      //    -                                     T0=0
      //    @T1,.                                 T1=ASC(INPUT$(1,1)):PRINT CHR$(T1);
      //    -------------                         T1=T1-13 or 10
      //    [                                     IF T1<>0 THEN
      //      @T0+                                  T0=1

      //      @T2+++++[@T1-------@T2-]              T1=T1-35 or 38:T2=0

      //      @V1[@T2+@V1-]                         T2=TEMP0:TEMP0=0
      //      @T2[                                  DO WHILE T2<>0
      //        @V1++++++++++                         T3=10:TEMP0=TEMP0+T3:T3=0
      //      @T2-]                                 T2=T2-1:LOOP:T2=0
      //      @T1[@V1+@T1-]                         TEMP0=TEMP0+T1:T1=0
      //    ]                                     END IF
      //  @T0]                                  LOOP:T0=0

      //  ++++++++++.[-]                        T0=10:PRINT CHR$(T0); or not

      //  @V1>[-]<@TEMP0[@V1>+<@TEMP0-]         F=M:TEMP0=0

      //  @V1>                                  @F
      //  >[>>[-]<<-[>>+<<-]+>>]>[-]<<<[<<]>[>[>>]>+<<<[<<]>-]>-<
      //  <
      int n = findexpr("", 1);
      if (n == -1) { errout("Syntax error"); }
      String expr = (sourceline.substring(0, n)).trim();
      if (expr.length() < 1 || expr.charAt(expr.length() - 1) != ')') {
        errout("Mismatched parenthesis");
      }
      expr = (expr.substring(0, expr.length() - 1)).trim();
      sourceline = (sourceline.substring(n)).trim();
      AlgebraicExpression ae = new AlgebraicExpression(expr);
      o = pre() + ae.parse() + "@~" + p + ">>[-]<<@_T0[@~" + p + ">>+<<@_T0-]"
          + "@_0+[-@_1,.----------" + (crlf?"---":"") + "[@_0+"
          + "@_2+++++" + (crlf?"":"+") + "[@_1------" + (crlf?"-":"") + "@_2-]"
          + "@_T0[@_2+@_T0-]@_2[@_T0++++++++++@_2-]@_1[@_T0+@_1-]]@_0]"
          + (crlf?"++++++++++.[-]":"")
          + "@~" + p + ">[-]<@_T0[@~" + p + ">+<@_T0-]@~" + p
          + ">>[>>[-]<<-[>>+<<-]+>>]>[-]<<<[<<]>[>[>>]>+<<<[<<]>-]>-<<" + post();
      if (debug == true) {
        o = "\n(INPUT " + p + "(" + debugtext(expr) + ")\n" + o;
      }
    } else {
      //INPUT V1
      //  @V1[-]@T0+                    V1=0:T0=1
      //  [                             DO WHILE T0<>0
      //    -                             T0=0
      //    @T1,.                         T1=ASC(INPUT$(1,1)):PRINT CHR$(T1);
      //    -------------                 T1=T1-13 or 10
      //    [                             IF T1<>0 THEN
      //      @T0+                          T0=1

      //      @T2+++++[@T1-------@T2-]      T1=T1-35 or 38:T2=0

      //      @V1[@T2+@V1-]                 T2=V1:V1=0
      //      @T2[                          DO WHILE T2<>0
      //        @V1++++++++++                 T3=10:V1=V1+T3:T3=0
      //      @T2-]                         T2=T2-1:LOOP:T2=0

      //      @T1[@V1+@T1-]                 V1=V1+T1:T1=0
      //    ]                             END IF
      //  @T0]                          LOOP:T0=0
      //  ++++++++++.[-]                PRINT CHR$(T0); or not
      if (debug == true) { o = "\n(INPUT " + p + ")\n"; }
      o += pre() + "@" + p + "[-]@_0+[-@_1,.----------" + (crlf?"---":"") + "[@_0+"
           + "@_2+++++" + (crlf?"":"+") + "[@_1------" + (crlf?"-":"") + "@_2-]"
           + "@" + p + "[@_2+@" + p + "-]@_2[@" + p + "++++++++++@_2-]"
           + "@_1[@" + p + "+@_1-]]@_0]" + (crlf?"++++++++++.[-]":"") + post();
    }
    arrows(o);
  }

  //------------------------------------------------------------------
  // bf_label -- writes out BF code for labels
  //------------------------------------------------------------------
  public static void bf_label() {
    //L#: label
    //  (...)                   T2=##:T1=0 (done by H)
    //  @T1+                    T1=1
    //  @T0[-]                  T0=0
    //  @G[@T1+@T0+@G-]         T1=G:T0=G:G=0
    //  @T0[@G+@T0-]            G=T0:T0=0
    //  @T[-]+                  T=1
    //  @T1[                    IF T1<>0 THEN
    //   @T-                      T=0
    //  @T1-]                   END IF:T1=0
    //  @T[                     IF T<>0 THEN
    //    @T1[-]+                 T1=1
    //    @T0[-]                  T0=0
    //    @IP[@T2-@T0+@IP-]       T2=T2-IP:T0=IP:IP=0
    //    @T0[@IP+@T0-]           IP=T0:T0=0
    //    @T2[                    IF T2<>0 THEN
    //      @T1-                    T1=0
    //    @T2[-]]                 END IF:T2=0
    //    @T1[                    IF T1<>0 THEN
    //      @G[-]+                  G=1
    //    @T1[-]]                 END IF:T1=0
    //  @T-]@T2[-]              END IF:T=0
    String o = "";
    if (debug == true) {
      o = "\n(LABEL " + p + ")\n";
      if (needpre == false) {
        needpost = true;
        o += "\t" + post();
      }
      o += "\n    (code) \t";
    } else {
      if (needpre == false) {
        needpost = true;
        o += post();
      }
    }
    o += labelval("@_1", "@_2")
         + "@_1[-]@_0[-]@_G[@_1+@_0+@_G-]@_0[@_G+@_0-]"
         + "@_T[-]+@_1[@_T-@_1-]@_T["
         + "@_1+@_0[-]@_I[@_0+@_2-@_I-]@_0[@_I+@_0-]"
         + "@_2[@_1-@_2[-]]@_1[@_G[-]+@_1[-]]"
         + "@_T-]@_2[-]";
    if (debug == true) { o += "\t"; }
    arrows(o);
    p = "";
    needpre = true;
  }

  //------------------------------------------------------------------
  // bf_let -- parses the LET statement
  //------------------------------------------------------------------
  public static void bf_let() {
    // expression
    if (a == '(') {
      bf_letarray();
    } else if (a == '=') {
      bf_letvar();
    } else {
      errout("Syntax error");
    }
  }

  //------------------------------------------------------------------
  // bf_letarray -- writes out BF code for the array = expr statement
  //------------------------------------------------------------------
  public static void bf_letarray() {
    //V1(expr)=expr2
    //  (...)                                   TEMP0=expr
    //  @V1>>[-]<<@TEMP0[@V1>>+<<@TEMP0-]       E=B:TEMP0=0
    //  (...)                                   TEMP0=expr2
    //  @V1>[-]<@TEMP0[@V1>+<@TEMP0-]           F=M:TEMP0=0
    //  @V1>                                    @F
    //  >[>>[-]<<-[>>+<<-]+>>]>[-]<<<[<<]>[>[>>]>+<<<[<<]>-]>-<
    //  <
    int n = findexpr("=", 1);
    if (n == -1) { errout("Syntax error"); }
    String expr = (sourceline.substring(0, n)).trim();
    if (expr.length() < 1 || expr.charAt(expr.length() - 1) != ')') {
      errout("Mismatched parenthesis");
    }
    expr = (expr.substring(0, expr.length() - 1)).trim();
    sourceline = (sourceline.substring(n)).trim();
    String p0 = p;
    parse();
    AlgebraicExpression ae = new AlgebraicExpression(expr);
    String o = pre() + ae.parse() + "@~" + p0 + ">>[-]<<@_T0[@~" + p0 + ">>+<<@_T0-]";
    n = findexpr("", 0);
    if (n == -1) { errout("Syntax error"); }
    String expr2 = (sourceline.substring(0, n)).trim();
    sourceline = (sourceline.substring(n)).trim();
    ae = new AlgebraicExpression(expr2);
    o += ae.parse() + "@~" + p0 + ">[-]<@_T0[@~" + p0 + ">+<@_T0-]@~" + p0
         + ">>[>>[-]<<-[>>+<<-]+>>]>[-]<<<[<<]>[>[>>]>+<<<[<<]>-]>-<<" + post();
    if (debug == true) {
      o = "\n(" + p0 + "(" + debugtext(expr) + ")=" + debugtext(expr2) + ")\n" + o;
    }
    arrows(o);
  }

  //------------------------------------------------------------------
  // bf_letvar -- writes out BF code for the var = expr statement
  //------------------------------------------------------------------
  public static void bf_letvar() {
    //V1=expr
    //  (...)                   TEMP0=expr
    //  @V1[-]                  V1=0
    //  @TEMP0[@V1+@TEMP0-]     V1=TEMP0:TEMP0=0
    int n = findexpr("", 0);
    if (n == -1) { errout("Syntax error"); }
    String expr = (sourceline.substring(0, n)).trim();
    sourceline = (sourceline.substring(n)).trim();
    AlgebraicExpression ae = new AlgebraicExpression(expr);
    String o = pre() + ae.parse() + "@" + p + "[-]@_T0[@" + p + "+@_T0-]" + post();
    if (debug == true) { o = "\n(" + p + "=" + debugtext(expr) + ")\n" + o; }
    arrows(o);
  }

  //------------------------------------------------------------------
  // bf_locate -- builds BFBASIC code for the LOCATE statement
  //------------------------------------------------------------------
  public static void bf_locate() {
    sourceline = (a + sourceline).trim();
    int n = findexpr(",", 0);
    if (n == -1) { errout("Syntax error"); }
    String expr = (sourceline.substring(0, n)).trim();
    sourceline = (sourceline.substring(n)).trim();
    parse();
    n = findexpr("", 0);
    if (n == -1) { errout("Syntax error"); }
    String expr2 = (sourceline.substring(0, n)).trim();
    sourceline = "PRINT \"\033[\"; " + expr + "; \";\"; "
                 + expr2 + "; \"H\";:" + (sourceline.substring(n)).trim();
    if (debug == true) {
      write("\n{LOCATE " + debugtext(expr + "," + expr2) + "}\n");
    }
  }

  //------------------------------------------------------------------
  // bf_loop -- builds BFBASIC code for the LOOP statement
  //------------------------------------------------------------------
  public static void bf_loop() {
    if (dostack.empty()) { errout("LOOP without DO"); }
    Integer l;
    if (parseif() == true) {
      // no params
      // LOOP
      if (debug == true) { write("\n{LOOP}\n"); }
      l = (Integer) dostack.pop();
      String temp = "GOTO _D" + Math.abs(l.intValue()) + ":";
      if (l.intValue() < 0) { temp += "_D" + (-l.intValue() + 1) + ":"; }
      sourceline = temp + sourceline;
    } else {
      // params
      parse();
      p = p.toUpperCase();
      if (p.equals("WHILE")) {
        // LOOP WHILE expr
        sourceline = (a + sourceline).trim();
        int n = findexpr("", 0);
        if (n == -1) { errout("Syntax error"); }
        String expr = (sourceline.substring(0, n)).trim();
        sourceline = (sourceline.substring(n)).trim();
        if (debug == true) { write("\n{LOOP WHILE " + debugtext(expr) + "}\n"); }
        l = (Integer) dostack.pop();
        String temp = "IF " + expr + " THEN GOTO _D" + Math.abs(l.intValue()) + ":";
        if (l.intValue() < 0) { temp += "_D" + (-l.intValue() + 1) + ":"; }
        sourceline = temp + sourceline;
      } else if (p.equals("UNTIL")) {
        // LOOP UNTIL expr
        sourceline = (a + sourceline).trim();
        int n = findexpr("", 0);
        if (n == -1) { errout("Syntax error"); }
        String expr = (sourceline.substring(0, n)).trim();
        sourceline = (sourceline.substring(n)).trim();
        if (debug == true) { write("\n{LOOP UNTIL " + debugtext(expr) + "}\n"); }
        l = (Integer) dostack.pop();
        String temp = "IF NOT(" + expr + ") THEN GOTO _D" + Math.abs(l.intValue()) + ":";
        if (l.intValue() < 0) { temp += "_D" + (-l.intValue() + 1) + ":"; }
        sourceline = temp + sourceline;
      } else {
        errout("Syntax error");
      }
    }
  }

  //------------------------------------------------------------------
  // bf_next -- builds BFBASIC code for the NEXT statement
  //------------------------------------------------------------------
  public static void bf_next() {
    // NEXT expr
    int n = findexpr("", 0);
    if (n == -1) { errout("Syntax error"); }
    String expr = (sourceline.substring(0, n)).trim();
    Integer l = (Integer) forstack.pop();
    String temp = expr + "=" + expr + "+1:GOTO _F" + Math.abs(l.intValue()) + ":";
    if (l.intValue() < 0) { temp += "_F" + (-l.intValue() + 1) + ":"; }
    sourceline = temp + (sourceline.substring(n)).trim();
    if (debug == true) { write("\n{NEXT " + debugtext(expr) + "}\n"); }
  }

  //------------------------------------------------------------------
  // bf_ongoto -- writes out BF code for the ONGOTO statement
  //------------------------------------------------------------------
  public static void bf_ongoto() {
    //ONGOTO expr
    //  @I[-]@G[-]              I=0:G=0
    //  @TEMP0[@IP+@TEMP0-]     IP=TEMP0:TEMP0=0
    needpost = true;
    sourceline = (a + sourceline).trim();
    int n = findexpr("", 0);
    if (n == -1) { errout("Syntax error"); }
    String expr = (sourceline.substring(0, n)).trim();
    sourceline = (sourceline.substring(n)).trim();
    AlgebraicExpression ae = new AlgebraicExpression(expr);
    String o = pre() + ae.parse() + "@_I[-]@_G[-]@_T0[@_I+@_T0-]" + post();
    if (debug == true) { o = "\n(ONGOTO " + debugtext(expr) + ")\n" + o; }
    arrows(o);
    needpre = true;
  }

  //------------------------------------------------------------------
  // bf_print -- writes out BF code for the PRINT statement
  //------------------------------------------------------------------
  public static void bf_print() {
    if (parseif() == true) {
      // no params
      //PRINT
      //  (...)                 PRINT
      String o = pre() + newline() + post();
      if (debug == true) { o = "\n(PRINT)\n" + o; }
      arrows(o);
    } else {
      // params
      boolean sameline;
      // parse print expression list
      String o = "";
      while (parseif() == false) {
        sameline = false;
        //System.out.println("p["+p+"] a["+a+"] sl["+sourceline+"]");

        if (sourceline.length() > 0 && sourceline.charAt(0) == '\"') {
          // string
          parse();
          p = p.substring(1);
          int n;
          if ((n = p.indexOf('\"')) == -1) { errout("Mismatched quotation mark"); }
          if (a == ';') {
            sameline = true;
            a = ' ';
          }
          p = p.substring(0, n);
          if (p.length() == 0) {
            // empty string
            //PRINT
            //  (...)             PRINT
            if (sameline == false) {
              if (debug == true) { o += "\n(PRINT \"\")\n"; }
              o += newline();
            }
          } else {
            // string literal
            //PRINT "text"
            //  @T0               (...)
            //  (...)             PRINT "text"
            if (debug == true) {
              o += "\n(PRINT \"" + debugtext(p) + "\"";
              if (sameline == true) { o += ";"; }
              o += ")\n";
            }
            o += "@_0" + bf_text(p);
            if (sameline == false) { o += newline(); }
          }
        } else if (sourceline.length() >= 1 && sourceline.charAt(0) == ';') {
          // PRINT ;
          sourceline = sourceline.substring(1);
        } else if ((sourceline.length() >= 4)
                   && (sourceline.substring(0, 4)).equalsIgnoreCase("CHR$")) {
          // PRINT CHR$(expr)
          //   (...)              TEMP0=expr
          //   @TEMP0.            PRINT CHR$(TEMP0);
          parse();
          if (a != '(') { errout("Syntax error"); }
          int n = findexpr("", 1);
          if (n == -1) { errout("Syntax error"); }
          String expr = (sourceline.substring(0, n)).trim();
          if (expr.length() < 1 || expr.charAt(expr.length() - 1) != ')') {
            errout("Mismatched parenthesis");
          }
          expr = (expr.substring(0, expr.length() - 1)).trim();
          sourceline = (sourceline.substring(n)).trim();
          if (sourceline.length() > 0 && sourceline.charAt(0) == ';') {
            sameline = true;
            sourceline = sourceline.substring(1);
          }
          AlgebraicExpression ae = new AlgebraicExpression(expr);
          if (debug == true) {
            o += "\n(PRINT CHR$(" + debugtext(expr) + ")";
            if (sameline == true) { o += ";"; }
            o += ")\n";
          }
          o += ae.parse() + "@_T0.";
          if (sameline == false) { o += newline(); }
        } else if ((sourceline.length() >= 6)
                   && (sourceline.substring(0, 6)).equalsIgnoreCase("SPACE$")) {
          // PRINT SPACE$(expr)
          //   (@T0[-])           (T0=0)
          //   (@T1[-])           (T1=0)
          //   (...)              TEMP0=expr
          //   @T1++++[           T1=4:DO WHILE T1<>0
          //     @T0++++++++        T0=T0+8
          //   @T1-]              T1=T1-1:LOOP
          //   @TEMP0[            DO WHILE TEMP0<>0
          //     @T0.               PRINT " ";
          //   @TEMP0-]           TEMP0=TEMP0-1:LOOP
          //   @T0[-]             T0=0
          parse();
          if (a != '(') { errout("Syntax error"); }
          int n = findexpr("", 1);
          if (n == -1) { errout("Syntax error"); }
          String expr = (sourceline.substring(0, n)).trim();
          if (expr.length() < 1 || expr.charAt(expr.length() - 1) != ')') {
            errout("Mismatched parenthesis");
          }
          expr = (expr.substring(0, expr.length() - 1)).trim();
          sourceline = (sourceline.substring(n)).trim();
          if (sourceline.length() > 0 && sourceline.charAt(0) == ';') {
            sameline = true;
            sourceline = sourceline.substring(1);
          }
          AlgebraicExpression ae = new AlgebraicExpression(expr);
          if (debug == true) {
            o += "\n(PRINT SPACE$(" + debugtext(expr) + ")";
            if (sameline == true) { o += ";"; }
            o += ")\n";
          }
          o += ae.parse() + "@_1++++[@_0++++++++@_1-]@_T0[@_0.@_T0-]@_0[-]";
          if (sameline == false) { o += newline(); }
        } else if ((sourceline.length() >= 7)
                   && (sourceline.substring(0, 7)).equalsIgnoreCase("STRING$")) {
          // PRINT STRING$(expr1, expr2)
          //   (...)               TEMP0=expr
          ///  @TEMP0[@ST+@TEMP0-] ST=TEMP0
          //   @ST[                DO WHILE ST<>0
          //     @TEMP0.             PRINT CHR$(TEMP0);
          //   @ST-]               ST=ST-1:LOOP
          parse();
          if (a != '(') { errout("Syntax error"); }
          int n = findexpr(",", 0);
          if (n == -1) {
            errout("Syntax error");
          }
          String expr = (sourceline.substring(0, n)).trim();
          sourceline = (sourceline.substring(n + 1)).trim();
          n = findexpr("", 1);
          if (n == -1) { errout("Syntax error"); }
          String expr2 = (sourceline.substring(0, n)).trim();
          if (expr2.length() < 1 || expr2.charAt(expr2.length() - 1) != ')') {
            errout("Mismatched parenthesis");
          }
          expr2 = (expr2.substring(0, expr2.length() - 1)).trim();
          sourceline = (sourceline.substring(n)).trim();
          if (sourceline.length() > 0 && sourceline.charAt(0) == ';') {
            sameline = true;
            sourceline = sourceline.substring(1);
          }
          if (debug == true) {
            o += "\n(PRINT STRING$(" + debugtext(expr + "," + expr2) + ")";
            if (sameline == true) { o += ";"; }
            o += ")\n";
          }
          AlgebraicExpression ae = new AlgebraicExpression(expr);
          o += ae.parse() + "@_T0[@_ST+@_T0-]";
          ae = new AlgebraicExpression(expr2);
          o += ae.parse() + "@_ST[@_T0.@_ST-]";
          if (sameline == false) { o += newline(); }
        } else {
          // PRINT expr
          //   (...)              TEMP0=expr
          //   (...)              PRINT TEMP0;
          sourceline = (a + sourceline).trim();
          int n = findexpr("", 0);
          if (n == -1) { errout("Syntax error"); }
          String expr = (sourceline.substring(0, n)).trim();
          sourceline = (sourceline.substring(n)).trim();
          if (sourceline.length() > 0 && sourceline.charAt(0) == ';') {
            sameline = true;
            sourceline = sourceline.substring(1);
          }
          AlgebraicExpression ae = new AlgebraicExpression(expr);
          if (debug == true) {
            o += "\n(PRINT " + debugtext(expr);
            if (sameline == true) { o += ";"; }
            o += ")\n";
          }
          o += ae.parse() + itoa();
          if (sameline == false) { o += newline(); }
        }
        sourceline = sourceline.trim();
      }
      if (!o.equals("")) {
        o = pre() + o;
        if (debug == true) {
          o = "\n{PRINT}\n" + o;
        }
        o += post();
        arrows(o);
      }
    }
  }

  //------------------------------------------------------------------
  // bf_randomize -- writes out BF code for the RANDOMIZE statement
  //------------------------------------------------------------------
  public static void bf_randomize() {
    parse();
    if (p.equalsIgnoreCase("KEY")) {
      //RANDOMIZE KEY
      //  @T0(...)                      PRINT "Random seed?"
      //  +                             T0=1
      //  [                             DO WHILE T0<>0
      //    @T0-                          T0=0
      //    @T1,-------------             T1=INKEY:T1=T1-13 or 10
      //    [                             DO WHILE T1<>0
      //      @T0+                          T0=1
      //      @T1[@RH+@T1-]                 RH=RH+T1:T1=0
      //      @RH[@RL+@T1+@RH-]             RL=RL+RH:T1=RH:RH=0
      //      @T1[@RH+@T1-]                 RH=T1:T1=0
      //    ]                             LOOP
      //  @T0]                          LOOP
      String o = pre() + "@_0" + bf_text("Random seed?")
                 +"+[@_0-@_1,----------" + (crlf?"---":"") + "[@_0+@_1[@_RH+@_1-]"
                 +"@_RH[@_RL+@_1+@_RH-]@_1[@_RH+@_1-]]@_0]" + post();
      if (debug == true) { o = "\n(RANDOMIZE KEY)\n" + o; }
      arrows(o);
    } else {
      errout("Syntax error");
    }
  }

  //------------------------------------------------------------------
  // bf_rem -- handles the REM statement
  //------------------------------------------------------------------
  public static void bf_rem() {
    // REM comment
    sourceline = "";
  }

  //------------------------------------------------------------------
  // bf_return -- builds BFBASIC code for the RETURN statement
  //------------------------------------------------------------------
  public static void bf_return() {
    // RETURN
    sourceline = "_GP=_GP-1:ONGOTO _GS(_GP):" + sourceline;
    if (debug == true) { write("\n{RETURN}\n"); }
  }

  //------------------------------------------------------------------
  // bf_swap -- writes out BF code for the SWAP statement
  //------------------------------------------------------------------
  public static void bf_swap() {
    //SWAP V1,V2
    //  (@T0[-])                (T0=0)
    //  @V1[@T0+@V1-]           T0=V1:V1=0
    //  @V2[@V1+@V2-]           V1=V2:V2=0
    //  @T0[@V2+@T0-]           V2=T0:T0=0
    parse();
    String p0 = p;
    if (a != ',') { errout("Syntax error"); }
    parse();
    String o = pre() + "@" + p0 + "[@_0+@" + p0 + "-]@" + p
               + "[@" + p0 + "+@" + p + "-]@_0[@" + p + "+@_0-]" + post();
    if (debug == true) { o = "\n(SWAP " + p0 + ", " + p + ")\n" + o; }
    arrows(o);
  }

  //------------------------------------------------------------------
  // bf_text -- convert ascii string to BF program
  // Programmed by Jeffry Johnston, July 25, 2001
  //------------------------------------------------------------------
  public static String bf_text(String ascii) {
    char[] firstch = new char[7];      // first character used in each range
    int[] f = new int[7];
    int[] value = new int[7];          // current value of each cell
    int[] low = { 15, 27, 43, 65, 78, 94, 110 };
    int[] high = { 26, 42, 64, 77, 93, 109, 126 };
    int ranges = 0;                    // number of text ranges used
    String code = "";                  // for bf code

    // determine which characters start in each range
    boolean[] used = new boolean[7]; // if each range is used
    for(int n = 0; n < ascii.length(); n++) {
      char b = ascii.charAt(n);
      if (b < 15 || b > 126) { errout("Invalid ascii character: " + (int) b); }
      for (int c = 0; c <= 6; c++) {
        // figure out if range already init'd and if char is in range
        if (used[c] == false && b >= low[c] && b <= high[c]) {
          used[c] = true;      // mark range as used
          firstch[ranges] = b; // save 1st char used in this range
          ranges++;            // count number of used ranges
        }
      }
    }
    ranges--;

    // find the best multiplicands
    int best = 1000, mult = 0, sample, g;
    for (int n = 1; n <= 50; n++) {
      g = n;
      sample = 0;
      for(int b = 0; b <= ranges; b++) {
        f[b] = Math.round((float) firstch[b] / (float) n);
        g += f[b];
        sample += Math.abs(firstch[b] - n * f[b]);
      }
      sample += g;
      if (sample < best) {
        best = sample;
        mult = n;
        for (int b = 0; b <= 6; b++) {
          value[b] = f[b];
        }
      }
    }

    // build the multiplication string
    // ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>
    code += string(mult, '+') + "[";
    for (int c = 0; c <= ranges; c++) {
      code += ">" + string(value[c], '+');
      value[c] *= mult;
    }

    // position mp to get started
    int mp = 0, mpnew;
    code += string(ranges + 1, '<') + "-]>";

    // output the rest
    for(int n = 0; n < ascii.length(); n++) {
      char b = ascii.charAt(n);
      mpnew = 0;

      // determine the best variable to use (find closest value)
      best = 255; // worst possible match, will certainly beat this
      for (int c = 0; c <= ranges + 1; c++) {
        sample = Math.abs(value[c] - b);
        if (sample < best || (sample <= best && c == mp)) {
          mpnew = c;
          best = sample;
        }
      }

      // move to new memory cell as decided above
      if (mpnew < mp) { code += string(mp - mpnew, '<'); }
      if (mpnew > mp) { code += string(mpnew - mp, '>'); }
      mp = mpnew;

      // adjust cell value as decided above
      if (b < value[mp]) { code += string(value[mp] - b, '-'); }
      if (b > value[mp]) { code += string(b - value[mp], '+'); }
      value[mp] = b;
      code += ".";
    }

    // zero used cells and position mp back to where it started from
    code += string(ranges - mp, '>');
    for (int c = 0; c <= ranges; c++) {
      code += "[-]<";
    }
    return code;
  }

  //------------------------------------------------------------------
  // debugtext -- removes BF commands from debug text
  // On entry:
  //   String text      text
  // Returns:
  //   String           fixed text
  //------------------------------------------------------------------
  public static String debugtext(String text) {
    String debug = "";
    for (int d = 0; d < text.length(); d++) {
      switch (text.charAt(d)) {
      case '+':
        debug += "(plus)"; break;
      case '-':
        debug += "(minus)"; break;
      case ',':
        debug += "(comma)"; break;
      case '.':
        debug += "(dot)"; break;
      case '<':
        debug += "(lt)"; break;
      case '>':
        debug += "(gt)"; break;
      case '[':
        debug += "(lsb)"; break;
      case ']':
        debug += "(rsb)"; break;
      case '@':
        debug += "(at)"; break;
      case 27:
        debug += "(esc)"; break;
      default:
        debug += text.substring(d, d + 1); break;
      }
    }
    return debug;
  }

  //------------------------------------------------------------------
  // errout -- prints error message then terminates program execution
  //------------------------------------------------------------------
  public static void errout(String e) {
    System.out.println();
    System.out.print(e);
    if (line > 0) { System.out.print(", line " + line); }
    System.out.println(".");
    System.exit(1);
  }

  //------------------------------------------------------------------
  // findexpr -- find expression in sourceline
  // Returns:
  //   int              last character position of expression + 1
  //------------------------------------------------------------------
  public static int findexpr(String endexpr, int startdepth) {
    endexpr = endexpr.toUpperCase();
    boolean q = false;
    // : ' ; [end]
    // ""
    //
    int ee = -1, depth = startdepth;
    for (int n = 0; n < sourceline.length(); n++) {
      char c = sourceline.charAt(n);
      if (c == '\"') {
        q = !q;
      }
      if (q == false) {
        if (c == '(') {
          depth++;
        } else if (c == ')') {
          depth--;
          if (depth < 0) { errout ("Mismatched parenthesis"); }
        }
        if (depth == 0) {
          if (endexpr.equals("")) {
            if (c == ':' || c == '\''|| c == ';') {
              ee = n;
              break;
            }
          } else if (n == (sourceline.toUpperCase()).indexOf(endexpr, n)) {
            ee = n;
            break;
          }
        }
      }
    }
    if (ee == -1 && endexpr.equals("")) { ee = sourceline.length(); }
    return ee;
  }

  //------------------------------------------------------------------
  // first -- output header code for BFBASIC program
  //------------------------------------------------------------------
  public static void first() {
    //(top of program)
    //  (@G[-]@IP[-])           (G=0:IP=0)
    //  @G+                     G=1
    //  @IP+                    IP=1
    //  [                       DO WHILE IP<>0
    String o = "@_G+@_I+[";
    if (debug == true) { o = "\n(FIRST)\n    (code) " + o; }
    arrows(o);
    needpre = true;
  }

  //------------------------------------------------------------------
  // h -- Converts a number to BF format
  // On entry:
  //  p                 number
  //  temp              temporary variable name to use.  Will be zeroed.
  //  dest              temporary variable name to use.  Will contain number.
  // Returns:
  //  o                 BF code
  //------------------------------------------------------------------
  public static String h(String temp, String dest) {
    int n = 0;
    try {
      n = Integer.parseInt(p);
    } catch (NumberFormatException e) {
      errout("Invalid number or label '" + p + "'");
    }
    if (n < 0 || n > 255) {
      errout("Number '" + n + "' out of range (0 - 255)");
    }
    int hi = (n & 0xF0) >> 4;
    int lo = n & 0x0F;
    String o = "";
    if (hi == 0) {
      o += temp + "[-]";
      o += dest + "[-]" + string(lo, '+');
    } else {
      o += dest + "[-]" + string(lo, '+');
      o += temp + "[-]" + string(hi, '+');
      o += "[" + dest + "++++++++++++++++" + temp + "-]";
    }
    return o;
  }

  //------------------------------------------------------------------
  // isnum -- decides whether current token is a number or not
  // Parameters:
  //   none
  // Returns:
  //   boolean          true=number, false=text
  //------------------------------------------------------------------
  public static boolean isnum() {
    boolean ans = false;
    if ((p.length() >= 2 && (p.substring(0, 2)).equalsIgnoreCase("&H")) ||
        (p.length() > 0 && p.charAt(0) >= '0' && p.charAt(0) <= '9')) {
      ans = true;
    }
    return ans;
  }

  //------------------------------------------------------------------
  // itoa -- convert number at TEMP0 to ascii and display it
  // Returns:
  //  String            BF code
  //------------------------------------------------------------------
  public static String itoa() {
    //  (@T0[-])@T1[-]@T2[-]@T3[-]@T4[-]        HUN=0:TEN=0:ONE=0
    //  @TEMP0[                                 DO WHILE N<>0
    //    @T3+                                    ONE=ONE+1
    //    [@T4+@T0+@T3-]                          IF ONE=10 THEN
    //    @T0[@T3+@T0-]+

    //    @T4----------[
    //      @T0-
    //    @T4[-]]
    //    @T0[
    //      @T2+@T3[-]                              TEN=TEN+1:ONE=0
    //    @T0-]                                   END IF

    //    @T2[@T4+@T0+@T2-]                       IF TEN=10 THEN
    //    @T0[@T2+@T0-]+

    //    @T4----------[
    //      @T0-
    //    @T4[-]]
    //    @T0[
    //      @T1+@T2[-]                              HUN=HUN+1:TEN=0
    //    @T0-]                                   END IF

    //  @TEMP0-]                                N=N-1:LOOP
    //  @T1[                                    IF HUN<>0 THEN
    //    @T0++++++++[@T1++++++@T2++++++@T0-]     HUN=HUN+48:TEN=TEN+48

    //    @T1.@T2.[-]                             PRINT CHR$(HUN);CHR$(TEN);:TEN=0
    //  @T1[-]]                                 HUN=0:END IF
    //  @T2[                                    IF TEN<>0 THEN
    //    @T0++++++++[@T2++++++@T0-]              TEN=TEN+48

    //    @T2.                                    PRINT CHR$(TEN);
    //  [-]]                                    TEN=0:END IF
    //  @T0++++++++[@T3++++++@T0-]              ONE=ONE+48
    //  @T3.                                    PRINT CHR$(ONE);
    String o = "@_1[-]@_2[-]@_3[-]@_4[-]@_T0[@_3+[@_4+@_0+@_3-]@_0[@_3+@_0-]+"
               + "@_4----------[@_0-@_4[-]]@_0[@_2+@_3[-]@_0-]"
               + "@_2[@_4+@_0+@_2-]@_0[@_2+@_0-]+"
               + "@_4----------[@_0-@_4[-]]@_0[@_1+@_2[-]@_0-]"
               + "@_T0-]@_1[@_0++++++++[@_1++++++@_2++++++@_0-]"
               + "@_1.@_2.[-]@_1[-]]@_2[@_0++++++++[@_2++++++@_0-]"
               + "@_2.[-]]@_0++++++++[@_3++++++@_0-]@_3.[-]";
    return o;
  }

  //------------------------------------------------------------------
  // labelval -- Creates line number code for a line label
  // On entry:
  //  p                 line label
  //  temp              temporary variable name to use.  Will be zeroed.
  //  dest              temporary variable name to use.  Will contain number.
  // Returns:
  //  o                 BF code
  //------------------------------------------------------------------
  public static String labelval(String temp, String dest) {
    // validate label
    p = (p.toUpperCase()).trim();
    for (int n = 0; n < p.length(); n++) {
      char c = p.charAt(n);
      if (c != '_' && (c < 'A' || c > 'Z') && (c < '0' || c > '9')) {
        errout("Label \'" + p + "\' contains the invalid character \'" + c + "\'");
      }
      if (c >= '0' && c <= '9' && n == 0) {
        errout("Label cannot begin with a number");
      }
    }

    // find label and associated number
    int n = 0;
    if (label.containsKey(p)) {
      // entry already exists, look up line number
      n = ((Integer) label.get(p)).intValue();
    } else {
      // doesn't exist, create new entry
      label.put(p, new Integer(annex));
      n = annex++;
      if (annex > 256) { errout("Out of line numbers"); }
    }

    // create BF string to represent number
    int hi = (n & 0xF0) >> 4;
    int lo = n & 0x0F;
    String o = "";
    if (hi == 0) {
      o += temp + "[-]";
      o += dest + "[-]" + string(lo, '+');
    } else {
      o += dest + "[-]" + string(lo, '+');
      o += temp + "[-]" + string(hi, '+');
      o += "[" + dest + "++++++++++++++++" + temp + "-]";
    }
    return o;
  }

  //------------------------------------------------------------------
  // last -- trailing code for BFBASIC program
  //------------------------------------------------------------------
  public static void last() {
    //(bottom of program)
    //    @IP[-]@G[-]             END (IP=0:G=0)
    //  @IP]                    LOOP
    needpost = true;
    String o = pre() + "@_I[-]@_G[-]" + post();
    if (debug == true) { o = "\n(END)\n" + o; }
    if (debug == true) { o += "\n(LAST)\n    (code) "; }
    o += "@_I]";
    arrows(o);
  }

  //------------------------------------------------------------------
  // newline -- returns BF code to print a newline
  //------------------------------------------------------------------
  public static String newline() {
    //PRINT (cr) (lf)
    //  @T0+++++++++++++.     T0=13:PRINT CHR$(T0);
    //  ---.                  T0=10:PRINT CHR$(T0);
    //  [-]                   T0=0

    //PRINT (lf)
    //  @T0++++++++++.          T0=10:PRINT CHR$(T0);
    //  [-]                     T0=0
    return "@_0++++++++++" + (crlf?"+++":"") + "." + (crlf?"---.":"") + "[-]";
  }

  //------------------------------------------------------------------
  // parse -- parses the next token (program statement/element)
  // Parameters:
  //   none
  // Changes:
  //   p                statement
  //   a                character that caused the parse to stop:
  //                    ":" end of statement ("" and "'" are given as ":")
  //                    "(" open parenthesis
  //                    "+" addition operator
  //                    (etc)
  //   sourceline       remaining line
  // Returns:
  //   void
  //------------------------------------------------------------------
  public static void parse() {
    sourceline = sourceline.trim();
    boolean q = false;
    int n;
    p = "";
    for (n = 0; n < sourceline.length(); n++) {
      a = sourceline.charAt(n);
      if (a == '\"') {
        q = !q;
      } else if (": \'()=+-<>*/,.[];".indexOf(a) != -1) {
        if (q == false) { break; }
      }
    }
    p = (sourceline.substring(0, n)).trim();
    if (n == sourceline.length() || a == '\'') {
      // comment or end of line
      sourceline = "";
      a = ':';
    } else if (n < sourceline.length()) {
      sourceline = (sourceline.substring(n)).trim();
    }
    // if V1 = ..., we want p="V1":a="=", not p="V1";a=" "
    if (sourceline.length() > 0 && "=()<+-*/,;".indexOf(sourceline.charAt(0)) != -1) {
      a = sourceline.charAt(0);
      sourceline = (sourceline.substring(1)).trim();
    }
  }

  //------------------------------------------------------------------
  // parseif -- are we are at the end of the current statement?
  // On entry:
  //   sourceline       remaining line
  // Returns:
  //   boolean          true = yes, false = no
  //------------------------------------------------------------------
  public static boolean parseif() {
    boolean ans = true;
    if (sourceline.length() > 0 && sourceline.charAt(0) != '\''
        && sourceline.charAt(0) != ':') {
      ans = false;
    }
    return ans;
  }

  //------------------------------------------------------------------
  // pre -- code put before each command, except labels & DIM's
  // Returns:
  //  String            BF code
  //------------------------------------------------------------------
  public static String pre() {
    //  @T[-]                   T=0
    //  @T0[-]                  T0=0
    //  @G[@T+@T0+@G-]          T=G:T0=G:G=0
    //  @T0[@G+@T0-]            G=T0:T0=0
    //  @T[                     IF T<>0 THEN
    String o = "";
    if (needpre == true) {
      o = "@_0[-]@_T[-]@_G[@_T+@_0+@_G-]@_0[@_G+@_0-]@_T[";
      if (debug == true) { o = "    (pre)  \t" + o + "\t\n    (code) \t"; }
      needpre = false;
    } else if (debug == true) {
      o = "    (code) \t";
    }
    return o;
  }

  //------------------------------------------------------------------
  // post -- code put after each command, except labels & DIM's
  // Returns:
  //  String            BF code
  //------------------------------------------------------------------
  public static String post() {
    //  @T[-]]                  END IF
    String o = "";
    if (needpost == true) {
      if (debug == true) { o = "\t\n    (post) "; }
      o += "@_T[-]]";
      needpost = false;
    } else if (debug == true) {
      o = "\t\n";
    }
    return o;
  }

  //------------------------------------------------------------------
  // string -- generate a string of identical characters
  //------------------------------------------------------------------
  public static String string(int len, char ch) {
    char[] c = new char[len];
    Arrays.fill(c, ch);
    return new String(c);
  }

  //------------------------------------------------------------------
  // usage -- prints usage information
  //------------------------------------------------------------------
  public static void usage() {
    System.out.println("Usage: bfbasic [-c] [-d] [-o outfile] file[.bas] [-?]");
    System.out.println("Where: file         Input filename");
    System.out.println("       -c           Treat newlines as CRLF, default: LF");
    System.out.println("       -d           Debug output");
    System.out.println("       -o outfile   Specify output filename, default: file.bf");
    System.out.println("       -?           Display usage information");
  }

  //------------------------------------------------------------------
  // write
  //------------------------------------------------------------------
  public static void write(String text) {
    if (debug == true) {
      for (int n = 0; n < text.length(); n++) {
        if (text.charAt(n) == '\t') {
          insert = !insert;
          continue;
        }
        if (text.charAt(n) == '\n') {
          if (insert == false && linepos != 1) {
            out.println();
            linepos = 1;
          } else if (insert == true && linepos != 12) {
            out.println();
            out.print("           ");
            linepos = 12;
          }
          continue;
        }
        if (linepos > 65) {
          out.println();
          linepos = 1;
          if (insert == true) {
            out.print("           ");
            linepos = 12;
          }
        }
        out.print(text.charAt(n));
        linepos++;
      }
    } else {
      out.print(text);
    }
  }

}

//********************************************************************
// AlgebraicExpression
//********************************************************************
class AlgebraicExpression {
  static String ae;
  static String token;
  int tokentype;
  static int tempvar = 0;
  static final int TOKEN_NULL = 0;
  static final int TOKEN_LEVEL0 = 1; // and or
  static final int TOKEN_LEVEL1 = 2; // = <> < <= > >=
  static final int TOKEN_LEVEL2 = 3; // + -
  static final int TOKEN_LEVEL3 = 4; // * /
  static final int TOKEN_LEVEL4 = 5; // -
  static final int TOKEN_NUMBER = 10;
  static final int TOKEN_VARIABLE = 11;
  static final int TOKEN_STRING = 12;
  static final int TOKEN_FUNCTION = 13;
  static final int TOKEN_LPAREN = 14;
  static final int TOKEN_RPAREN = 15;

  //------------------------------------------------------------------
  // (constructor)
  //------------------------------------------------------------------
  AlgebraicExpression(String ae) {
    this.ae = ae;
  }

  //------------------------------------------------------------------
  // getToken
  //------------------------------------------------------------------
  String getToken() {
    token = "";
    tokentype = TOKEN_NULL;
    ae = ae.trim() + "   ";
    char p = ae.charAt(0);
    int i;
    if (ae.equals("   ")) { // empty
      ae = "";
    } else if ((ae.substring(0, 2)).equalsIgnoreCase("&h")) { // hex number
      tokentype = TOKEN_NUMBER;
      token = "0x";
      for (i = 2; i < ae.length(); i++) {
        p = ae.charAt(i);
        if ((p >= '0' && p <= '9') || (p >= 'a' && p <= 'f') || (p >= 'A' && p <= 'F')) {
          token += p + "";
        } else break;
      }
      try {
        token = (Integer.decode(token)).toString();
      } catch (NumberFormatException e) { }
      ae = ae.substring(i);
    } else if (p >= '0' && p <= '9') { // decimal number
      tokentype = TOKEN_NUMBER;
      token = p + "";
      for (i = 1; i < ae.length(); i++) {
        p = ae.charAt(i);
        if (p >= '0' && p <= '9') {
          token += p + "";
        } else break;
      }
      ae = ae.substring(i);
    } else if (p == '\"') { // string literal
      tokentype = TOKEN_STRING;
      i = ae.indexOf('\"');
      if (i == -1) {
        bfbasic.errout("Unclosed string literal");
      } else {
        token = ae.substring(1, i);
      }
      ae = ae.substring(i + 1);
    } else if (p == '(') { // left parenthesis
      tokentype = TOKEN_LPAREN;
      ae = ae.substring(1);
    } else if (p == ')') { // right parenthesis
      tokentype = TOKEN_RPAREN;
      ae = ae.substring(1);
    } else if (p == '\'') { // comment
      ae = "";
    } else if ((ae.substring(0, 3)).equalsIgnoreCase("and")) { // operator level 0: logic
      token = " " + ae.substring(0, 3).toUpperCase() + " ";
      tokentype = TOKEN_LEVEL0;
      ae = ae.substring(3);
    } else if ((ae.substring(0, 2)).equalsIgnoreCase("or")) { // operator level 0: logic
      token = " " + ae.substring(0, 2).toUpperCase() + " ";
      tokentype = TOKEN_LEVEL0;
      ae = ae.substring(2);
    } else if ("<=>".indexOf(p) != -1) { // operator level 1: compare
      tokentype = TOKEN_LEVEL1;
      if ((p == '<' || p == '>') && ae.charAt(1) == '=') { // combine operators
        token = p + "=";
        ae = ae.substring(2);
      } else if (p == '<' && ae.charAt(1) == '>') {
        token = p + ">";
        ae = ae.substring(2);
      } else {
        token = p + "";
        ae = ae.substring(1);
      }
    } else if ("+-".indexOf(p) != -1) { // operator level 2: add, subtract
      tokentype = TOKEN_LEVEL2;
      token = p + "";
      ae = ae.substring(1);
    } else if ("*/".indexOf(p) != -1) { // operator level 3: multiply, divide
      tokentype = TOKEN_LEVEL3;
      token = p + "";
      ae = ae.substring(1);
    /*
    } else if (p == '!') { // operator level 4: negate
      tokentype = TOKEN_LEVEL4;
      token = p + "";
      ae = ae.substring(1);
    */
    } else if ((p >= 'a' && p <= 'z') || (p >= 'A' && p <= 'Z') || (p == '_')) { // variable
      tokentype = TOKEN_VARIABLE;
      token = p + "";
      for (i = 1; i < ae.length(); i++) {
        p = ae.charAt(i);
        if (p == '(') { // function or array
          tokentype = TOKEN_FUNCTION;
          i++;
          break;
        } else if ((p >= 'a' && p <= 'z') || (p >= 'A' && p <= 'Z') || (p >= '0' && p <= '9')) {
          token += p + "";
        } else break;
      }
      token = token.toUpperCase();
      ae = ae.substring(i);
    } else { // unknown
      bfbasic.errout("Invalid token \'" + p + "\'");
    }
    return token;
  }

  //------------------------------------------------------------------
  // parse
  //------------------------------------------------------------------
  String parse() {
    String parsed = "";
    String operator;
    Stack tokens = new Stack();
    Stack tokentypes = new Stack();
    Stack operands = new Stack();
    Stack functions = new Stack();
    int operand1 = 0, operand2 = 0;
    tempvar = 0;
    getToken();
    try {
      while (tokentype != TOKEN_NULL) {
        if (tokentype == TOKEN_LPAREN) {
          tokens.push(token);
          tokentypes.push(new Integer(tokentype));
          functions.push(token);
        } else if (tokentype == TOKEN_FUNCTION) {
          tokens.push(token);
          tokentypes.push(new Integer(TOKEN_LPAREN));
          functions.push(token);
        } else if (tokentype == TOKEN_RPAREN) {
          while (((Integer) tokentypes.peek()).intValue() != TOKEN_LPAREN) {
            operator = (String) tokens.pop();
            operand2 = ((Integer) operands.pop()).intValue();
            operand1 = ((Integer) operands.peek()).intValue();
            /*
            if (((Integer) tokentypes.pop()).intValue() == TOKEN_LEVEL4) {
              operand1 = -1;
            } else {
              operand1 = ((Integer) operands.peek()).intValue();
            }
            */
            parsed += getCode("_T" + operand1, operator, "_T" + operand2);
            tempvar = operand2;
            tokentypes.pop();
          }
          if (!((String) functions.peek()).equals("")) {
            String funct = ((String) functions.peek()).toUpperCase();
            if (funct.equals("NOT")) {
              //V1=NOT(V1)
              //  @T0 ([-]) -           T0=255
              //  @V1[@T0-@V1-]         T0=T0-V1:V1=0
              //  @T0[@V1+@T0-]         V1=T0:T0=0
              if (bfbasic.debug == true) {
                parsed += "\n(_T" + (tempvar - 1) + "=NOT(_T" + (tempvar - 1) + "))\n";
              }
              parsed += "@_0-@_T" + (tempvar - 1) + "[@_0-@_T" + (tempvar - 1)
                        + "-]@_0[@_T" + (tempvar - 1) + "+@_0-]";
            } else {
              //V1=V2(V1)
              //  (@T0[-])
              //  @V2>>[-]<<
              //  @V1[@V2>>+<<@V1-]
              //  @V2>
              //  >[>>[-]<<-[>>+<<-]+>>]>[<<<[<<]>+>[>>]>-]<<<[<<]>
              //  [<@V1+@T0+@V2>-]<
              //  @T0[@V2>+<@T0-]
              //  @V2   ??? (>) ???
              //  >[>>]>[-]<<<[<<]>[>[>>]>+<<<[<<]>-]>-<
              //  <
              if (bfbasic.debug == true) {
                parsed += "\n(_T" + (tempvar - 1) + "=" + funct + "(_T"
                       + (tempvar - 1) + "))\n";
              }
              parsed += "@~" + funct + ">>[-]<<@_T" + (tempvar - 1) + "[@~" + funct
                        + ">>+<<@_T" + (tempvar - 1) + "-]@~" + funct
                        + ">>[>>[-]<<-[>>+<<-]+>>]>[<<<[<<]>+>[>>]>-]<<<[<<]>"
                        + "[<@_T" + (tempvar - 1) + "+@_0+@~" + funct + ">-]<"
                        + "@_0[@~" + funct + ">+<@_0-]@~" + funct
                        + ">>[>>]>[-]<<<[<<]>[>[>>]>+<<<[<<]>-]>-<<";
            }
          }
          functions.pop();
          tokens.pop();
          tokentypes.pop();
        } else if (tokentype == TOKEN_NUMBER) {
          //V1=#
          //  (...)               V1=#:T0=0
          String p = bfbasic.p;
          bfbasic.p = token;
          if (bfbasic.debug == true) {
            parsed += "\n(_T" + tempvar + "=" + token + ")\n";
          }
          parsed += bfbasic.h("@_0","@_T" + tempvar);
          bfbasic.p = p;
          operands.push(new Integer(tempvar));
          tempvar++;
        } else if (tokentype == TOKEN_VARIABLE) {
          if (bfbasic.debug == true) {
            parsed += "\n(_T" + tempvar + "=" + token + ")\n";
          }
          if (token.equalsIgnoreCase("INKEY")) {
            //V1=INKEY
            //  @V1,                V1=ASC(INPUT$(1,1))
            parsed += "@_T" + tempvar + ",";
          } else if (token.equalsIgnoreCase("RND")) {
            //V1=RND
            //Uses linear congruential generator, V = (A * V + B) % M
            //Where: A = 31821, B = 13849, M = 65536, V = 0 (initial seed)
            //A and B values from:
            //  Texas Instruments TMS320 DSP DESIGNER'S NOTEBOOK Number 43
            //  Random Number Generation on a TMS320C5x
            //  Written by Eric Wilbur
            //Random numbers will repeat after 65536 calls to this function

            //  @RH[@T0+@RH-]                   T0=RH:RH=0
            //  @RL[@T1+@RL-]                   T1=RL:RL=0
            //  @T3+++++++[@T2+++++++++++@T3-]  T2=77:T3=0

            //  @T2[                            DO WHILE T2<>0
            //    @T0[@RH+@T3+@T0-]               RH=RH+T0:T3=T0:T0=0
            //    @T3[@T0+@T3-]                   T0=T3:T3=0
            //    @T1[@RH+@T3+@T4+@T1-]           RH=RH+T1:T3=T1:T4=T1:T1=0

            //    @T4[@T1+@T4-]                   T1=T4:T4=0
            //    @T3[                            DO WHILE T3<>0
            //      @RL+[@T4+@T5+@RL-]              RL=RL+1:T4=RL:T5=RL:RL=0
            //      @T5[@RL+@T5-]+                  RL=T5:T5=1

            //      @T4[                            IF T4<>0 THEN
            //        @T5-                            T5=0
            //      @T4[-]]                         END IF:T4=0
            //      @T5[                            IF T5<>0 THEN
            //        @RH+                            RH=RH+1
            //      @T5-]                           END IF:T5=0
            //    @T3-]                           T3=T3-1:LOOP:T3=0
            //  @T2-]                           T2=T2-1:LOOP:T2=0

            //  ++++++[@T3++++++++@T2-]@T3-     T3=47:T2=0
            //  [                               DO WHILE T3<>0
            //    @T1[@RH+@T2+@T1-]               RH=RH+T1:T2=T1:T1=0
            //    @T2[@T1+@T2-]                   T1=T2:T2=0

            //  @T3-]                           T3=T3-1:LOOP:T3=0
            //  @T0[-]@T1[-]+++++[@T0+++++@T1-] T0=25:T1=0 (R=R+13849)
            //  @T0[                            DO WHILE T0<>0
            //    @RL+[@T1+@T2+@RL-]              RL=RL+1:T1=RL:T2=RL:RL=0

            //    @T2[@RL+@T2-]+                  RL=T2:T2=1
            //    @T1[                            IF T1<>0 THEN
            //      @T2-                            T2=0
            //    @T1[-]]                         END IF:T1=0
            //    @T2[                            IF T2<>0 THEN
            //      @RH+                            RH=RH+1
            //    @T2-]                           END IF:T2=0
            //  @T0-]                           T0=T0-1:LOOP:T0=0

            //  ++++++[@RH+++++++++@T0-]        RH=RH+54:T0=0

            //  @RH[@V1+@T0+@RH-]               V1=RH:T0=RH:RH=0
            //  @T0[@RH+@T0-]                   RH=T0:T0=0
            parsed += "@_RH[@_0+@_RH-]@_RL[@_1+@_RL-]@_3+++++++[@_2+++++++++++@_3-]"
                      + "@_2[@_0[@_RH+@_3+@_0-]@_3[@_0+@_3-]@_1[@_RH+@_3+@_4+@_1-]"
                      + "@_4[@_1+@_4-]@_3[@_RL+[@_4+@_5+@_RL-]@_5[@_RL+@_5-]+"
                      + "@_4[@_5-@_4[-]]@_5[@_RH+@_5-]@_3-]@_2-]"
                      + "++++++[@_3++++++++@_2-]@_3-[@_1[@_RH+@_2+@_1-]@_2[@_1+@_2-]"
                      + "@_3-]@_0[-]@_1[-]+++++[@_0+++++@_1-]@_0[@_RL+[@_1+@_2+@_RL-]"
                      + "@_2[@_RL+@_2-]+@_1[@_2-@_1[-]]@_2[@_RH+@_2-]@_0-]"
                      + "++++++[@_RH+++++++++@_0-]"
                      + "@_RH[@_T" + tempvar + "+@_0+@_RH-]@_0[@_RH+@_0-]";
          } else {
            //V1=V2
            //  (@T0[-])            (T0=0)
            //  @V1[-]              V1=0
            //  @V2[@V1+@T0+@V2-]   V1=V2:T0=V2:V2=0
            //  @T0[@V2+@T0-]       V2=T0:T0=0
            parsed += "@_T" + tempvar + "[-]@" + token + "[@_T" + tempvar
                      + "+@_0+@" + token + "-]@_0[@" + token + "+@_0-]";
          }
          operands.push(new Integer(tempvar));
          tempvar++;
        } else {
          while (!tokens.empty()) {
            if (((Integer) tokentypes.peek()).intValue() == TOKEN_LPAREN) {
              break;
            }
            if (tokentype > ((Integer) tokentypes.peek()).intValue()) {
              break;
            }
            operator = (String) tokens.pop();
            operand2 = ((Integer) operands.pop()).intValue();
            operand1 = ((Integer) operands.peek()).intValue();
            /*
            if (((Integer) tokentypes.pop()).intValue() == TOKEN_LEVEL4) {
              operand1 = -1;
            } else {
              operand1 = ((Integer) operands.peek()).intValue();
            }
            */
            tempvar = operand2;
            parsed += getCode("_T" + operand1, operator, "_T" + operand2);
            tokentypes.pop();
          }
          tokens.push(token);
          if (tokentype == TOKEN_FUNCTION) { tokentype = TOKEN_LPAREN; }
          tokentypes.push(new Integer(tokentype));
        }
        getToken();
      }
      while (!tokens.empty()) {
        operator = (String) tokens.pop();
        operand2 = ((Integer) operands.pop()).intValue();
        operand1 = ((Integer) operands.peek()).intValue();
        /*
        if (((Integer) tokentypes.pop()).intValue() == TOKEN_LEVEL4) {
          operand1 = -1;
        } else {
          operand1 = ((Integer) operands.peek()).intValue();
        }
        */
        tempvar = operand2;
        parsed += getCode("_T" + operand1, operator, "_T" + operand2);
        tokentypes.pop();
      }
    } catch (EmptyStackException e) {
      bfbasic.errout("Mismatched or empty parenthesis");
    }
    return parsed;
  }

  //------------------------------------------------------------------
  // getCode
  //------------------------------------------------------------------
  String getCode(String operand1, String operator, String operand2) {
    String code = "";
    if (bfbasic.debug == true) {
      if (operand1.equals("_T-1")) {
        code += "\n(_T" + operand2 + "=-_T" + operand2 + ")\n";
      } else {
        code += "\n(" + operand1 + "=" + operand1 + bfbasic.debugtext(operator)
                + operand2 + ")\n";
      }
    }
    operator = operator.trim();
    if (operator.equals("!")) {
      //V1=-V1
      //  @T0[-]                T0=0
      //  @V1[@T0-@V1-]         T0=T0-V1:V1=0
      //  @T0[@V1+@T0-]         V1=T0:T0=0
      code += "@_0[-]@_T" + operand2 + "[@_0-@_T" + operand2 + "-]"
              + "@_0[@_T" + operand2 + "+@_0-]";
    } else if (operator.equals("+")) {
      //V1=V1+V2
      //  (@T0[-])              (T0=0)
      //  @V2[@V1+@T0+@V2-]     V1=V1+V2:T0=V2:V2=0
      //  @T0[@V2+@T0-]         V2=T0:T0=0
      code += "@" + operand2 + "[@" + operand1 + "+@_0+@" + operand2 + "-]"
              + "@_0[@" + operand2 + "+@_0-]";
    } else if (operator.equals("-")) {
      //V1=V1-V2
      //  (@T0[-])              (T0=0)
      //  @V2[@V1-@T0+@V2-]     V1=V1-V2:T0=V2:V2=0
      //  @T0[@V2+@T0-]         V2=T0:T0=0
      code += "@" + operand2 + "[@" + operand1 + "-@_0+@" + operand2 + "-]"
              + "@_0[@" + operand2 + "+@_0-]";
    } else if (operator.equals("*")) {
      //V1=V1*V2
      //  (@T0[-])              (T0=0)
      //  (@T1[-])              (T1=0)
      //  (@T2[-])              (T2=0)
      //  @V1[@T1+@V1-]         T1=V1:V1=0
      //  @T1[                  DO WHILE T1<>0

      //    @V2[@V1+@T0+@V2-]     V1=V1+V2:T0=V2:V2=0

      //    @T0[@V2+@T0-]         V2=T0:T0=0
      //  @T1-]                 T1=T1-1:LOOP
      code += "@" + operand1 + "[@_1+@" + operand1 + "-]@_1["
              + "@" + operand2 + "[@" + operand1 + "+@_0+@" + operand2 + "-]"
              + "@_0[@" + operand2 + "+@_0-]@_1-]";
    } else if (operator.equals("/")) {
      //V1=V1/V2
      //  (@T0[-])              (T0=0)
      //  (@T1[-])              (T1=0)
      //  (@T2[-])              (T2=0)
      //  (@T3[-])              (T3=0)
      //  @V1[@T3+@V1-]         T3=V1:V1=0
      //  @T3[                  DO WHILE T3<>0

      //    @V2[@T2+@T0+@V2-]     T2=V2:T0=V2:V2=0
      //    @T0[@V2+@T0-]         V2=T0:T0=0

      //    @T2[                  DO WHILE T2<>0
      //      @T3-[@T1+@T0+@T3-]    T3=T3-1:T1=T3:T0=T3
      //      @T0[@T3+@T0-]+        T3=0:T0=1
      //      @T1[                  DO WHILE T1<>0
      //        @T0-                  T0=0
      //      @T1[-]]               END IF:T1=0

      //      @T0[                  DO WHILE T0<>0
      //        @T2-[                 T2=T2-1:IF T2<>0 THEN
      //          @V1-                  V1=V1-1
      //        @T2[-]]+              END IF:T2=1
      //      @T0[-]]               END IF:T0=0
      //    @T2-]                 T2=T2-1:LOOP
      //    @V1+                  V1=V1+1
      //  @T3]                  LOOP:(T3=0)
      code += "@" + operand1 + "[@_3+@" + operand1 + "-]@_3["
              + "@" + operand2 + "[@_2+@_0+@" + operand2 + "-]@_0[@" + operand2 + "+@_0-]"
              + "@_2[@_3-[@_1+@_0+@_3-]@_0[@_3+@_0-]+@_1[@_0-@_1[-]]"
              + "@_0[@_2-[@" + operand1 + "-@_2[-]]+@_0[-]]@_2-]@" + operand1 + "+@_3]";
    } else if (operator.equals("=")) {
      //V1=V1=V2
      //  (@T0[-])              (T0=0)
      //  (@T1[-])              (T1=0)
      //  @V1[@T1+@V1-]-        T1=V1:V1=255
      //  @V2[@T1-@T0+@V2-]     T1=T1-V2:T0=V2:V2=0
      //  @T0[@V2+@T0-]         V2=T0:T0=0
      //  @T1[                  IF T1<>0 THEN
      //    @V1+                  V1=0
      //  @T1[-]]               END IF:T1=0
      code += "@" + operand1 + "[@_1+@" + operand1 + "-]-@" + operand2 + "[@_1-@_0+@"
              + operand2 + "-]@_0[@" + operand2 + "+@_0-]@_1[@" + operand1 + "+@_1[-]]";
    } else if (operator.equals("<>")) {
      //V1=V1<>V2
      //  (@T0[-])              (T0=0)
      //  (@T1[-])              (T1=0)
      //  @V1[@T1+@V1-]         T1=V1:V1=0
      //  @V2[@T1-@T0+@V2-]     T1=T1-V2:T0=V2:V2=0
      //  @T0[@V2+@T0-]         V2=T0:T0=0
      //  @T1[                  IF T1<>0 THEN
      //    @V1-                  V1=255
      //  @T1[-]]               END IF:T1=0
      code += "@" + operand1 + "[@_1+@" + operand1 + "-]@" + operand2 + "[@_1-@_0+@"
              + operand2 + "-]@_0[@" + operand2 + "+@_0-]@_1[@" + operand1 + "-@_1[-]]";
    } else if (operator.equals("<")) {
      //V1=V1<V2
      //  (@T0[-])              (T0=0)
      //  (@T1[-])              (T1=0)
      //  (@T2[-])              (T2=0)
      //  (@T3[-])              (T3=0)
      //  (@T4[-])              (T4=0)
      //  @V1[@T4+@V1-]         T4=V1:V1=0

      //  @V2[@T1+@T2+@T0+@V2-] T1=V2:T2=V2:T0=V2:V2=0

      //  @T0[@V2+@T0-]         V2=T0:T0=0
      //  @T2[                  DO WHILE T2<>0
      //    @T4[@T3+@T0+@T4-]     T3=T4:T0=T4:T4=0
      //    @T0[@T4+@T0-]+        T4=T0:T0=1

      //    @T3[                  IF T3<>0 THEN
      //      @T1-                  T1=T1-1
      //      @T4-                  T4=T4-1
      //      @T0-                  T0=0
      //    @T3[-]]               END IF:T3=0
      //    @T0[                  IF T0<>0 THEN
      //      @T2[-]+               T2=1
      //    @T0-]                 END IF:T0=0
      //  @T2-]                 T2=T2-1:LOOP

      //  @T1[                  IF T1<>0 THEN
      //    @V1-                  V1=255
      //  @T1[-]]               END IF:T1=0
      //  @T4[-]                T4=0
      code += "@" + operand1 + "[@_4+@" + operand1 + "-]"
              + "@" + operand2 + "[@_1+@_2+@_0+@" + operand2 + "-]"
              + "@_0[@" + operand2 + "+@_0-]@_2[@_4[@_3+@_0+@_4-]@_0[@_4+@_0-]+"
              + "@_3[@_1-@_4-@_0-@_3[-]]@_0[@_2[-]+@_0-]@_2-]"
              + "@_1[@" + operand1 + "-@_1[-]]@_4[-]";
    } else if (operator.equals("<=")) {
      //V1=V1<=V2
      //  (@T0[-])              (T0=0)
      //  (@T1[-])              (T1=0)
      //  (@T2[-])              (T2=0)
      //  (@T3[-])              (T3=0)
      //  (@T4[-])              (T4=0)
      //  @V1[@T4+@V1-]-        T4=V1:V1=255

      //  @V2[@T1+@T2+@T0+@V2-] T1=V2:T2=V2:T0=V2:V2=0

      //  @T0[@V2+@T0-]         V2=T0:T0=0
      //  @T2[                  DO WHILE T2<>0
      //    @T4[@T3+@T0+@T4-]     T3=T4:T0=T4:T4=0
      //    @T0[@T4+@T0-]+        T4=T0:T0=1

      //    @T3[                  IF T3<>0 THEN
      //      @T1-                  T1=T1-1
      //      @T4-                  T4=T4-1
      //      @T0-                  T0=0
      //    @T3[-]]               END IF:T3=0
      //    @T0[                  IF T0<>0 THEN
      //      @T2[-]+               T2=1
      //    @T0-]                 END IF:T0=0
      //  @T2-]                 T2=T2-1:LOOP

      //  @T4[                  IF T4<>0 THEN
      //    @V1-                  V1=255
      //  @T4[-]]               END IF:T4=0
      //  @T1[-]                T1=0
      code += "@" + operand1 + "[@_4+@" + operand1 + "-]-"
              + "@" + operand2 + "[@_1+@_2+@_0+@" + operand2 + "-]"
              + "@_0[@" + operand2 + "+@_0-]@_2[@_4[@_3+@_0+@_4-]@_0[@_4+@_0-]+"
              + "@_3[@_1-@_4-@_0-@_3[-]]@_0[@_2[-]+@_0-]@_2-]"
              + "@_4[@" + operand1 + "+@_4[-]]@_1[-]";
    } else if (operator.equals(">")) {
      //V1=V1>V2
      //  (@T0[-])              (T0=0)
      //  (@T1[-])              (T1=0)
      //  (@T2[-])              (T2=0)
      //  (@T3[-])              (T3=0)
      //  (@T4[-])              (T4=0)
      //  @V1[@T4+@V1-]         T4=V1:V1=0

      //  @V2[@T1+@T2+@T0+@V2-] T1=V2:T2=V2:T0=V2:V2=0

      //  @T0[@V2+@T0-]         V2=T0:T0=0
      //  @T2[                  DO WHILE T2<>0
      //    @T4[@T3+@T0+@T4-]     T3=T4:T0=T4:T4=0
      //    @T0[@T4+@T0-]+        T4=T0:T0=1

      //    @T3[                  IF T3<>0 THEN
      //      @T1-                  T1=T1-1
      //      @T4-                  T4=T4-1
      //      @T0-                  T0=0
      //    @T3[-]]               END IF:T3=0
      //    @T0[                  IF T0<>0 THEN
      //      @T2[-]+               T2=1
      //    @T0-]                 END IF:T0=0
      //  @T2-]                 T2=T2-1:LOOP

      //  @T4[                  IF T4<>0 THEN
      //    @V1-                  V1=255
      //  @T4[-]]               END IF:T4=0
      //  @T1[-]                T1=0
      code += "@" + operand1 + "[@_4+@" + operand1 + "-]"
              + "@" + operand2 + "[@_1+@_2+@_0+@" + operand2 + "-]"
              + "@_0[@" + operand2 + "+@_0-]@_2[@_4[@_3+@_0+@_4-]@_0[@_4+@_0-]+"
              + "@_3[@_1-@_4-@_0-@_3[-]]@_0[@_2[-]+@_0-]@_2-]"
              + "@_4[@" + operand1 + "-@_4[-]]@_1[-]";
    } else if (operator.equals(">=")) {
      //V1=V1>=V2
      //  (@T0[-])              (T0=0)
      //  (@T1[-])              (T1=0)
      //  (@T2[-])              (T2=0)
      //  (@T3[-])              (T3=0)
      //  (@T4[-])              (T4=0)
      //  @V1[@T4+@V1-]-        T4=V1:V1=255

      //  @V2[@T1+@T2+@T0+@V2-] T1=V2:T2=V2:T0=V2:V2=0

      //  @T0[@V2+@T0-]         V2=T0:T0=0
      //  @T2[                  DO WHILE T2<>0
      //    @T4[@T3+@T0+@T4-]     T3=T4:T0=T4:T4=0
      //    @T0[@T4+@T0-]+        T4=T0:T0=1

      //    @T3[                  IF T3<>0 THEN
      //      @T1-                  T1=T1-1
      //      @T4-                  T4=T4-1
      //      @T0-                  T0=0
      //    @T3[-]]               END IF:T3=0
      //    @T0[                  IF T0<>0 THEN
      //      @T2[-]+               T2=1
      //    @T0-]                 END IF:T0=0
      //  @T2-]                 T2=T2-1:LOOP

      //  @T1[                  IF T1<>0 THEN
      //    @V1+                  V1=0
      //  @T1[-]]               END IF:T1=0
      //  @T4[-]                T4=0
      code += "@" + operand1 + "[@_4+@" + operand1 + "-]-"
              + "@" + operand2 + "[@_1+@_2+@_0+@" + operand2 + "-]"
              + "@_0[@" + operand2 + "+@_0-]@_2[@_4[@_3+@_0+@_4-]@_0[@_4+@_0-]+"
              + "@_3[@_1-@_4-@_0-@_3[-]]@_0[@_2[-]+@_0-]@_2-]"
              + "@_1[@" + operand1 + "+@_1[-]]@_4[-]";
    } else if (operator.equals("OR")) {
      //V1=V1 OR V2
      //  (@T0[-])              (T0=0)
      //  @V1[@T0+@V1-]         T0=V1:V1=0
      //  @T0[                  IF T0<>0 THEN
      //    @V1-                  V1=255
      //  @T0[-]]               END IF:T0=0

      //  @V2[@T0+@T1+@V2-]     T0=V2:T1=V2:V2=0

      //  @T1[@V2+@T1-]         V2=T1:T1=0
      //  @T0[                  IF T0<>0 THEN
      //    @V1[-]-               V1=255
      //  @T0[-]]               END IF:T0=0

      code += "@" + operand1 + "[@_0+@" + operand1 + "-]@_0[@" + operand1 + "-@_0[-]]"
              + "@" + operand2 + "[@_0+@_1+@" + operand2 + "-]"
              + "@_1[@" + operand2 + "+@_1-]@_0[@" + operand1 + "[-]-@_0[-]]";
    } else if (operator.equals("AND")) {
      //V1=V1 AND V2
      //  (@T0[-])              (T0=0)
      //  @V1[@T0+@V1-]         T0=V1:V1=0
      //  @T0[                  IF T0<>0 THEN
      //    @T0[-]                T0=0

      //    @V2[@T0+@T1+@V2-]     T0=V2:T1=V2:V2=0

      //    @T1[@V2+@T1-]         V2=T1:T1=0
      //    @T0[                  IF T0<>0 THEN
      //      @V1-                  V1=255
      //    @T0[-]]               END IF:T0=0
      //  ]                     END IF
      code += "@" + operand1 + "[@_0+@" + operand1 + "-]@_0[@_0[-]"
              + "@" + operand2 + "[@_0+@_1+@" + operand2 + "-]"
              + "@_1[@" + operand2 + "+@_1-]@_0[@" + operand1 + "-@_0[-]]]";
    } else {
      bfbasic.errout("Unknown operator \'" + operator + "\'");
    }
    return code;
  }

}
