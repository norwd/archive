'BFASM.BAS -- Converts a BF program into an ASM source
'Combines some statements for a shorter program
'Standard I/O
DEFLNG A-Z
F$ = COMMAND$
IF F$ = "" THEN INPUT "Enter filename of BF source [.BF]: ", F$
F = INSTR(F$, "."): IF F = 0 THEN F$ = F$ + ".BF"
F = INSTR(F$, "."): FO$ = MID$(F$, 1, F) + "ASM"
INPUT "Optimize for size? [Y/n]: ", Z$: Z$ = UCASE$(Z$)
PRINT "Writing "; FO$; "."
OPEN F$ FOR BINARY AS #1
OPEN FO$ FOR OUTPUT AS #2
PRINT #2, "MOV     BX,30000"
PRINT #2, "CLEAR:"
PRINT #2, "DEC     BX"
PRINT #2, "MOV     BYTE PTR [M+BX],0"
PRINT #2, "JNZ     CLEAR"
A = LOF(1): S = 0: T = 0: V = 0
K = 1: DIM K(2000)
DO
  IF A = 0 THEN GOTO SKIP
  A$ = INPUT$(1, 1)
  A = A - 1
SKIP:
  IF T = 1 AND ((A$ <> "<" AND A$ <> ">") OR (A = 0)) THEN
    V = V MOD 30000: V = (V + 30000) MOD 30000
    PRINT #2, "ADD     BX," + MID$(STR$(V), 2)
    IF Z$ = "N" THEN
      PRINT #2, "CMP     BX,29999"
      PRINT #2, "DW      1142"
      PRINT #2, "SUB     BX,30000"
    ELSE
      PRINT #2, "CALL    GTLT"
    END IF
    T = 0
  END IF
  IF T = 2 AND ((A$ <> "+" AND A$ <> "-") OR (A = 0)) THEN
    V = V MOD 256: V = (V + 256) MOD 256
    'PRINT #2, "MOV     AL," +
    PRINT #2, "ADD     BYTE PTR [M+BX]," + MID$(STR$(V), 2)
    T = 0
  END IF
  IF T = 3 AND INSTR("<>+-.,[]" + CHR$(13) + CHR$(10), A$) > 0 THEN
    PRINT #2, ";" + V$
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
    'IF Z$ = "N" THEN
      PRINT #2, "MOV     AH,2"
      PRINT #2, "MOV     DL,[M+BX]"
      PRINT #2, "INT     21h"
    'ELSE
    '  PRINT #2, "CALL    PRINT"
    'END IF
  CASE ","
    'IF Z$ = "N" THEN
      PRINT #2, "MOV     AH,8"
      PRINT #2, "INT     21h"
      PRINT #2, "MOV     [M+BX],AL"
    'ELSE
    '  PRINT #2, "CALL    INPUT"
    'END IF
  CASE "["
    PRINT #2, "W" + MID$(STR$(K), 2) + ":"
    PRINT #2, "CMP     BYTE PTR [M+BX],0"
    PRINT #2, "JNZ     W" + MID$(STR$(K + 1), 2)
    PRINT #2, "JMP     W" + MID$(STR$(K + 2), 2)
    PRINT #2, "W" + MID$(STR$(K + 1), 2) + ":"
    K = K + 3: K(S) = K - 1: S = S + 1
  CASE "]"
    S = S - 1
    IF S < 0 THEN PRINT "Error: ] without matching [": END
    PRINT #2, "JMP     W" + MID$(STR$(K(S) - 2), 2)
    PRINT #2, "W" + MID$(STR$(K(S)), 2) + ":"
  CASE ELSE
    IF T = 0 AND INSTR(" " + CHR$(13) + CHR$(10), A$) = 0 THEN T = 3: V$ = ""
    V$ = V$ + A$
  END SELECT
LOOP
PRINT #2, "INT     20h"
IF Z$ <> "N" THEN
  PRINT #2, "GTLT            PROC    NEAR"
  PRINT #2, "        CMP     BX,29999"
  PRINT #2, "        DW      1142"
  PRINT #2, "        SUB     BX,30000"
  PRINT #2, "        RET"
  PRINT #2, "GTLT            ENDP"
END IF
PRINT #2, "M:"
IF S > 0 THEN PRINT "Error: [ without matching ]": END
IF S < 0 THEN PRINT "Error: ] without matching [": END
CLOSE #1, #2
PRINT "Done."
END

'Example of output file & each instruction
'XOR     BX,BX

'ADD     BX,#####                '><
'CMP     BX,29999
'DW      1142
'SUB     BX,30000

'ADD     BYTE PTR [M+BX],###     '+-

'MOV     AH,2                    '.
'MOV     DL,[M+BX]
'INT     21h

'MOV     AH,8                    ',
'INT     21h
'MOV     [M+BX],AL

'W1:                             '[
'CMP     BYTE PTR [M+BX],0
'JNZ     W2
'JMP     W3
'W2:

'JMP     W1                      ']
'W3:

'INT     20h
'M:


