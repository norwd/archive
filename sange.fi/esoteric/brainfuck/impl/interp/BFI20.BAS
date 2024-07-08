OPEN "BFI2.COM" FOR BINARY AS #1
A$ = INPUT$(LOF(1), 1)
CLOSE #1
DIM Z(255)
FOR A = 1 TO LEN(A$)
  B = ASC(MID$(A$, A, 1))
  Z(B) = Z(B) + 1
NEXT A
SCREEN 9: CLS
FOR A = 0 TO 255
  PRINT " "; HEX$(Z(A));
  IF (A + 1) / 16 = (A + 1) \ 16 THEN
    PRINT
  ELSEIF (A + 1) / 8 = (A + 1) \ 8 THEN
    PRINT " |";
  END IF
  C = Z(A): IF C = 0 THEN C = 15
  LINE (A * 2 + 50, 300)-(A * 2 + 50, 300 - Z(A) * 2), C
NEXT A
END

