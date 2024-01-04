'BFASM.BAS -- Converts a BF program into an ASM source
'Combines +- and <> statements for a shorter program
'Standard I/O
DEFLNG A-Z
F$ = COMMAND$
IF F$ = "" THEN INPUT "Enter filename of BF source [.BF]: ", F$
F = INSTR(F$, "."): IF F = 0 THEN F$ = F$ + ".BF"
F = INSTR(F$, "."): FO$ = MID$(F$, 1, F) + "ASM"
PRINT "Writing "; FO$; "."
OPEN F$ FOR BINARY AS #1
OPEN FO$ FOR OUTPUT AS #2
PRINT #2, "CLEAR:"
PRINT #2, "DEC     BX"
PRINT #2, "MOV     [BX],CH"
PRINT #2, "CMP     BH,7Fh"
PRINT #2, "JNZ     CLEAR"
A = LOF(1): S = 0: T = 0: V = 0
K = 1: DIM K(2000)
DO
AGAIN:
  IF A = 0 THEN GOTO SKIP
  A$ = INPUT$(1, 1)
  A = A - 1
  IF INSTR("<>+-[].,", A$) = 0 THEN GOTO AGAIN
SKIP:
  IF T = 1 AND ((A$ <> "<" AND A$ <> ">") OR (A = 0)) THEN
    IF V = 1 THEN PRINT #2, "INC     BX"
    IF V = 2 THEN PRINT #2, "INC     BX": PRINT #2, "INC     BX"
    IF V = -1 THEN PRINT #2, "DEC     BX"
    IF V = -2 THEN PRINT #2, "DEC     BX": PRINT #2, "DEC     BX"
    IF V > 2 THEN PRINT #2, "ADD     BX,"; MID$(STR$(V), 2)
    IF V < -2 THEN PRINT #2, "SUB     BX,"; MID$(STR$(V), 2)
    T = 0
  END IF
  IF T = 2 AND ((A$ <> "+" AND A$ <> "-") OR (A = 0)) THEN
    V = V MOD 256: V = (V + 256) MOD 256
    IF V = 1 THEN PRINT #2, "INC     BYTE PTR [BX]"
    IF V = 255 THEN PRINT #2, "DEC     BYTE PTR [BX]"
    IF V > 1 AND V < 255 THEN PRINT #2, "ADD     BYTE PTR [BX]," + MID$(STR$(V), 2)
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
    PRINT #2, "MOV     AH,2"
    PRINT #2, "MOV     DL,[BX]"
    PRINT #2, "INT     21h"
  CASE ","
    PRINT #2, "MOV     AH,8"
    PRINT #2, "INT     21h"
    PRINT #2, "MOV     [BX],AL"
  CASE "["
    PRINT #2, "W" + MID$(STR$(K), 2) + ":"
    PRINT #2, "CMP     BYTE PTR [BX],0"
    PRINT #2, "JNZ     W" + MID$(STR$(K + 1), 2)
    PRINT #2, "JMP     W" + MID$(STR$(K + 2), 2)
    PRINT #2, "W" + MID$(STR$(K + 1), 2) + ":"
    K = K + 3: K(S) = K - 1: S = S + 1
  CASE "]"
    S = S - 1
    IF S < 0 THEN PRINT "Error: ] without matching [": END
    PRINT #2, "JMP     W" + MID$(STR$(K(S) - 2), 2)
    PRINT #2, "W" + MID$(STR$(K(S)), 2) + ":"
  END SELECT
LOOP
PRINT #2, "RET"
IF S > 0 THEN PRINT "Error: [ without matching ]": END
IF S < 0 THEN PRINT "Error: ] without matching [": END
CLOSE #1, #2
PRINT "Done."
END

