'BFI2.BAS -- BF program emulator
'faster than BFI3/4
DEFINT A-Z
DECLARE SUB BF (E)
'$DYNAMIC
DIM M(29999)
P = 0: IP = 0
LOCATE , , 1', 0, 31

'get program data
F$ = COMMAND$
IF F$ = "" THEN INPUT "Enter filename of BF source [.BF]: ", F$
F = INSTR(F$, "."): IF F = 0 THEN F$ = F$ + ".BF"
'S$ = ",+[-.,+]ÿ"
OPEN F$ FOR BINARY AS #1: S$ = INPUT$(LOF(1), 1) + CHR$(255): CLOSE #1
'S$ = ""
'DO
'  T$ = INPUT$(1)
'  S$ = S$ + T$
'  IF T$ = CHR$(255) THEN EXIT DO
'LOOP
SL = LEN(S$)
'CLS
OPEN "CONS:" FOR OUTPUT AS #1
'main loop
CALL BF(SL)
END

REM $STATIC
SUB BF (E)
SHARED M(), P, S$, IP
  SIP = IP
  DO
    IP = IP + 1
    'PRINT #1, "IP="; MID$(STR$(IP), 2); " SIP="; MID$(STR$(SIP), 2); " E="; MID$(STR$(E), 2); " P="; MID$(STR$(P), 2); " M(P)="; MID$(STR$(M(P)), 2)': SLEEP
    O$ = MID$(S$, IP, 1)
    IF O$ = CHR$(255) THEN EXIT SUB
    IF O$ = ">" THEN P = (P + 1) MOD 30000
    IF O$ = "<" THEN P = (P + 29999) MOD 30000
    IF O$ = "+" THEN M(P) = (M(P) + 1) MOD 256
    IF O$ = "-" THEN M(P) = (M(P) + 255) MOD 256
    IF O$ = "." THEN PRINT #1, CHR$(M(P));
    IF O$ = "," THEN M(P) = ASC(INPUT$(1))
    IF O$ = "[" THEN 'new loop
      'find matching "]"
      B = 1
      FOR A = IP + 1 TO E
        IF MID$(S$, A, 1) = "[" THEN B = B + 1
        IF MID$(S$, A, 1) = "]" THEN B = B - 1
        IF B = 0 THEN EXIT FOR
      NEXT A
      IF A = E + 1 THEN PRINT #1, "Error in []": END
      IF M(P) = 0 THEN
        IP = A
      ELSE
        CALL BF(A)
      END IF
    END IF
    IF O$ = "]" THEN
      IP = SIP - 1
      EXIT DO
    END IF
  LOOP
END SUB

