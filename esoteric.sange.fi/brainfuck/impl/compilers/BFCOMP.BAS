'BFCOMP.BAS -- BF program compressor

'get program data
F$ = COMMAND$
IF F$ = "" THEN INPUT "Enter filename of BF source [.BF]: ", F$
F = INSTR(F$, "."): IF F = 0 THEN F$ = F$ + ".BF": F = INSTR(F$, ".")
F2$ = MID$(F$, 1, F) + "BFC"
OPEN F$ FOR BINARY AS #1
OPEN F2$ FOR OUTPUT AS #2
SP$ = ""
FOR A = 1 TO LOF(1)
  S$ = INPUT$(1, 1)
  IF INSTR(1, "<>+-[].,", S$) = 0 THEN GOTO A
  IF INSTR("<>< +-+", SP$ + S$) > 0 AND SP$ <> "" THEN GOTO A
  PRINT #2, SP$;
  SP$ = S$
A:
NEXT A
PRINT #2, SP$;
CLOSE #1, #2
END

