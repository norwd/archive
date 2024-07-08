OPEN "BFI2.COM" FOR BINARY AS #1
A$ = INPUT$(LOF(1), 1) + " "
CLOSE #1
OPEN "BFI24.BIN" FOR OUTPUT AS #1
C = 0
FOR A = 1 TO LEN(A$) / 3
  B1 = ASC(MID$(A$, A, 1)): R1 = (B1 AND 192) / 4: B1 = B1 AND 63
  B2 = ASC(MID$(A$, A + 1, 1)): R2 = (B2 AND 192) / 16: B2 = B2 AND 63
  B3 = ASC(MID$(A$, A + 2, 1)): R3 = (B3 AND 192) / 64: B3 = B3 AND 63
  R = R1 + R2 + R3
  PRINT #1, CHR$(R + 48); CHR$(B1 + 48); CHR$(B2 + 48); CHR$(B3 + 48);
  C = C + 1: IF C > 16 THEN C = 0: PRINT #1, ""
NEXT A
CLOSE #1
END

