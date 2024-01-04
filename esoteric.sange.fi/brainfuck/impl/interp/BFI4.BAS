'BFI.BAS -- BF program emulator
'slower than BFI2, gearing towards ASM emu
DEFINT A-Z
DIM M(29999): P = 0: IP = 0
DIM G(1000): G = 0
LOCATE , , 1', 0, 31

'get program data
F$ = COMMAND$
F$ = "C:\BF\FACTOR.BF"
IF F$ = "" THEN INPUT "Enter filename of BF source [.BF]: ", F$
F = INSTR(F$, "."): IF F = 0 THEN F$ = F$ + ".BF"
'S$ = ",+[-.,+]ÿ"
OPEN F$ FOR BINARY AS #1: S$ = INPUT$(LOF(1), 1) + CHR$(255): CLOSE #1
SL = LEN(S$)
OPEN "CONS:" FOR OUTPUT AS #1
GOSUB BF
END

'main loop
BF:
  G(G) = IP
D:
    IP = IP + 1
    'PRINT #1, "IP="; MID$(STR$(IP), 2); " SIP="; MID$(STR$(SIP), 2); " E="; MID$(STR$(E), 2); " P="; MID$(STR$(P), 2); " M(P)="; MID$(STR$(M(P)), 2)': SLEEP
    O$ = MID$(S$, IP, 1)
    IF O$ = CHR$(255) THEN END
    IF O$ = ">" THEN P = (P + 1) MOD 30000
    IF O$ = "<" THEN P = (P + 29999) MOD 30000
    IF O$ = "+" THEN M(P) = (M(P) + 1) MOD 256
    IF O$ = "-" THEN M(P) = (M(P) + 255) MOD 256
    IF O$ = "." THEN PRINT #1, CHR$(M(P));
    IF O$ = "," THEN M(P) = ASC(INPUT$(1))
    IF O$ = "[" THEN 'new loop
      'find matching "]"
      B = 1
      FOR A = IP TO SL
        IF MID$(S$, A + 1, 1) = "[" THEN B = B + 1
        IF MID$(S$, A + 1, 1) = "]" THEN B = B - 1
        IF B = 0 THEN EXIT FOR
      NEXT A
      IF M(P) = 0 THEN
        IP = A + 1
      ELSE
        G = G + 1
        GOSUB BF
        G = G - 1
        GOTO D
      END IF
    END IF
    IF O$ = "]" THEN
      IP = G(G) - 1
      'find matching "["
      'B = 1
      'FOR A = IP - 1 TO 1 STEP -1
      '  IF MID$(S$, A, 1) = "[" THEN B = B - 1
      '  IF MID$(S$, A, 1) = "]" THEN B = B + 1
      '  IF B = 0 THEN EXIT FOR
      'NEXT A
      'IP = A - 1
      GOTO DE
    END IF
  GOTO D
DE:
RETURN

