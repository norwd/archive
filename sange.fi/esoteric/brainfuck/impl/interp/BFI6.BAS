'BF program emulator, for conversion to NUMBERIX emu
        DEFINT A-Z: OPEN "C:\BF\PRIME.BF" FOR BINARY AS #1: SL = LOF(1)
        S$ = INPUT$(SL, 1): CLOSE #1: S$ = S$ + CHR$(255): SL = SL + 1
        CLS : OPEN "SCRN:" FOR OUTPUT AS #1
DIM M(29999), G(255), S(1999)
BF: G(GG) = IP 'main loop
D0: O$ = MID$(S$, IP + 1, 1): IF O$ = CHR$(255) THEN END ELSE IP = IP + 1
  IF O$ = ">" THEN P = P + 1: GOTO D0
  IF O$ = "<" THEN P = P - 1: GOTO D0
  IF O$ = "+" THEN M(P) = (M(P) + 1) MOD 256: GOTO D0
  IF O$ = "-" THEN M(P) = (M(P) + 255) MOD 256: GOTO D0
  IF O$ = "." THEN PRINT #1, CHR$(M(P)); : GOTO D0
  IF O$ = "," THEN M(P) = ASC(INPUT$(1)): GOTO D0
  IF O$ = "[" THEN
    B = 1: A = IP
O1: IF A = SL THEN GOTO O2
    IF MID$(S$, A + 1, 1) = "[" THEN B = B + 1
    IF MID$(S$, A + 1, 1) = "]" THEN B = B - 1
    IF B > 0 THEN A = A + 1: GOTO O1
O2: IF M(P) = 0 THEN IP = A + 1: GOTO D0
    GG = GG + 1: GOTO BF
  END IF
  IF O$ = "]" THEN IP = G(GG) - 1: GG = GG - 1 'new loop
GOTO D0

