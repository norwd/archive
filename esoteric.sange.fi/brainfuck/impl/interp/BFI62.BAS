'BF program emulator, for conversion to NUMBERIX/casio emu
        DEFINT A-Z: OPEN "C:\BF\PRIME.BF" FOR BINARY AS #1: SL = LOF(1)
DIM M(2000), G(200), S(5000)
        S$ = INPUT$(SL, 1): CLOSE #1: S$ = S$ + CHR$(255): SL = SL + 1
        CLS : OPEN "SCRN:" FOR OUTPUT AS #1
        R = 0
        FOR S = 1 TO SL
          I = INSTR("><+-.,[]" + CHR$(255), MID$(S$, S, 1))
          IF I > 0 THEN S(R) = I - 1: R = R + 1': PRINT S(R - 1);
        NEXT S

BF: G(GG) = IP 'main loop
D0:
  O = S(IP): IF O = 8 THEN END ELSE IP = IP + 1
  IF O = 0 THEN P = P + 1: GOTO D0
  IF O = 1 THEN P = P - 1: GOTO D0
  IF O = 2 THEN M(P) = (M(P) + 1) MOD 256: GOTO D0
  IF O = 3 THEN M(P) = (M(P) + 255) MOD 256: GOTO D0
  IF O = 4 THEN PRINT #1, CHR$(M(P)); : GOTO D0
  IF O = 5 THEN M(P) = ASC(INPUT$(1)): GOTO D0
  IF O = 6 THEN
    B = 1: A = IP
O1: IF A = SL THEN GOTO O2
    IF S(A) = 6 THEN B = B + 1
    IF S(A) = 7 THEN B = B - 1
    IF B > 0 THEN A = A + 1: GOTO O1
O2: IF M(P) = 0 THEN IP = A + 1: GOTO D0
    GG = GG + 1: GOTO BF
  END IF
  IF O = 7 THEN IP = G(GG) - 1: GG = GG - 1 'new loop
GOTO D0

