'BFI.BAS -- BF program emulator
'slower than BFI2, gearing towards ASM emu
DEFINT A-Z
DIM M(29999): P = 0
DIM G(1000)

'get program data
F$ = COMMAND$
F$ = "C:\BF\SORT.BF"
IF F$ = "" THEN INPUT "Enter filename of BF source [.BF]: ", F$
F = INSTR(F$, "."): IF F = 0 THEN F$ = F$ + ".BF"
OPEN F$ FOR BINARY AS #1
SL = LOF(1)
S$ = INPUT$(SL, 1)
CLOSE #1
S$ = S$ + CHR$(255): SL = SL + 1
IP = 0
GG = 0
CLS
OPEN "CONS:" FOR OUTPUT AS #1
GOSUB BF
END

'main loop
BF:
  G(GG) = IP
D0:
    O$ = MID$(S$, IP + 1, 1)
    IP = IP + 1
    'PRINT #1, "IP="; MID$(STR$(IP), 2); " SIP="; MID$(STR$(SIP), 2); " E="; MID$(STR$(E), 2); " P="; MID$(STR$(P), 2); " M(P)="; MID$(STR$(M(P)), 2); " O$="; O$: SLEEP
    IF O$ <> CHR$(255) THEN GOTO O1
      END
O1: IF O$ <> ">" THEN GOTO O2
      IF P = 29999 THEN P = -1
      P = P + 1
      GOTO D0
O2: IF O$ <> "<" THEN GOTO O3
      IF P = 0 THEN P = 30000
      P = P - 1
      GOTO D0
O3: IF O$ <> "+" THEN GOTO O4
      M(P) = (M(P) + 1) MOD 256
      GOTO D0
O4: IF O$ <> "-" THEN GOTO O5
      M(P) = (M(P) + 255) MOD 256
      GOTO D0
O5: IF O$ <> "." THEN GOTO O6
      PRINT #1, CHR$(M(P));
      GOTO D0
O6: IF O$ <> "," THEN GOTO O7
      M(P) = ASC(INPUT$(1))
      GOTO D0
O7: IF O$ <> "[" THEN GOTO O8 'new loop
      B = 1
      A = IP
O71:  IF A = SL THEN GOTO O72
      IF MID$(S$, A + 1, 1) <> "[" THEN GOTO O711
      B = B + 1
O711: IF MID$(S$, A + 1, 1) <> "]" THEN GOTO O712
      B = B - 1
O712: IF B = 0 THEN GOTO O72
      A = A + 1
      GOTO O71
O72:  IF M(P) <> 0 THEN GOTO O73
      IP = A
      IP = IP + 1
      GOTO D0
O73:  GG = GG + 1
      GOSUB BF
      GG = GG - 1
      GOTO D0
O8: IF O$ <> "]" THEN GOTO O9
      IP = G(GG)
      IP = IP - 1
      GOTO DONE
O9:
  GOTO D0
DONE:
RETURN

