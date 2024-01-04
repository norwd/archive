'BF.BAS -- Converts a BF program into a Basic program
'Combines some statements for a shorter program
'Standard I/O
DEFLNG A-Z
F$ = COMMAND$
IF F$ = "" THEN INPUT "Enter filename of BF source [.BF]: ", F$
F = INSTR(F$, "."): IF F = 0 THEN F$ = F$ + ".BF"
F = INSTR(F$, "."): FO$ = MID$(F$, 1, F) + "BAS"
PRINT "Writing "; FO$; "."
OPEN F$ FOR BINARY AS #1
OPEN FO$ FOR OUTPUT AS #2
PRINT #2, "DEFINT A-Z"
PRINT #2, "DIM M(29999): P = 0"
PRINT #2, "LOCATE , , 0, 0, 31"
A = LOF(1): S = 0: T = 0: V = 0
DO
  IF A = 0 THEN GOTO SKIP
  A$ = INPUT$(1, 1)
  A = A - 1
SKIP:
  IF T = 1 AND ((A$ <> "<" AND A$ <> ">") OR (A = 0)) THEN
    V = V MOD 30000: V = (V + 30000) MOD 30000
    PRINT #2, SPACE$(S) + "P = (P +"; STR$(V); ") MOD 30000"
    T = 0
  END IF
  IF T = 2 AND ((A$ <> "+" AND A$ <> "-") OR (A = 0)) THEN
    V = V MOD 256: V = (V + 256) MOD 256
    PRINT #2, SPACE$(S) + "M(P) = (M(P) +" + STR$(V); ") MOD 256"
    T = 0
  END IF
  IF T = 3 AND INSTR("<>+-.,[]" + CHR$(13) + CHR$(10), A$) > 0 THEN
    PRINT #2, SPACE$(S) + "'" + V$
    T = 0
  END IF
  IF A = 0 THEN EXIT DO
  SELECT CASE A$
  CASE ">"
    IF T = 0 THEN T = 1: V = 0
    V = V + 1
  CASE "<"
    IF T = 0 THEN T = 1: V = 0
    V = V - 1
  CASE "+"
    IF T = 0 THEN T = 2: V = 0
    V = V + 1
  CASE "-"
    IF T = 0 THEN T = 2: V = 0
    V = V - 1
  CASE "."
    PRINT #2, SPACE$(S) + "PRINT CHR$(M(P));"
  CASE ","
    'PRINT #2, SPACE$(S) + "LOCATE , , 1: DO: A$ = INKEY$: LOOP WHILE A$ = " + CHR$(34) + CHR$(34) + ": M(P) = ASC(A$): LOCATE , , 0"
    PRINT #2, SPACE$(S) + "LOCATE , , 1: M(P) = ASC(INPUT$(1)): LOCATE , , 0"
  CASE "["
    PRINT #2, SPACE$(S) + "WHILE M(P)"
    S = S + 2
  CASE "]"
    S = S - 2: IF S < 0 THEN PRINT "Error: ] without matching [": END
    PRINT #2, SPACE$(S) + "WEND"
  CASE ELSE
    IF T = 0 AND INSTR(" " + CHR$(13) + CHR$(10), A$) = 0 THEN T = 3: V$ = ""
    V$ = V$ + A$
  END SELECT
LOOP
PRINT #2, "CLOSE #1"
PRINT #2, "END"
IF S > 0 THEN PRINT "Error: [ without matching ]": END
IF S < 0 THEN PRINT "Error: ] without matching [": END
CLOSE #1, #2
PRINT "Done."
END

'Example of output file & each instruction
'TEST:
'DEFINT A-Z
'DIM M(29999): P = 0
'LOCATE , , 0, 0, 31
'P = (P + 1) MOD 30000                                   '>
'P = (P + 29999) MOD 30000                               '<
'M(P) = (M(P) + 1) MOD 256                               '+
'M(P) = (M(P) + 255) MOD 256                             '-
'PRINT CHR$(M(P));                                       '.
'LOCATE , , 1: M(P) = ASC(INPUT$(1)): LOCATE , , 0       ',
'WHILE M(P)                                              '[
'WEND                                                    ']
'CLOSE #1
'END

