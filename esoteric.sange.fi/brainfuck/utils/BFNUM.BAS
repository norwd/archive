A$ = "ESOteric OS"
DEFINT A-Z
DIM A(3), O(3), F(3), L(3): O = 0
CLS
FOR A = 1 TO LEN(A$)
  B = ASC(MID$(A$, A, 1))
  IF B < 32 AND A(0) = 0 THEN A(0) = B: O(O) = 1: O = O + 1
  IF B > 31 AND B < 64 AND A(1) = 0 THEN A(1) = B: O(O) = 2: O = O + 1
  IF B > 63 AND B < 96 AND A(2) = 0 THEN A(2) = B: O(O) = 3: O = O + 1
  IF B > 95 AND B < 127 AND A(3) = 0 THEN A(3) = B: O(O) = 4: O = O + 1
NEXT A
PRINT A(0); A(1); A(2); A(3)
O(0) = 1: O(1) = 2: O(2) = 3: O(3) = 4
PRINT O(0); O(1); O(2); O(3)
L = 1000: M = 0
FOR A = 1 TO 20
  E = 0: G = 0
  PRINT A; ":";
  FOR B = 0 TO 3
    C = A(B)
    F(B) = CINT(C / A): G = G + F(B)
    PRINT A * F(B); "("; F(B); ")";
    E = E + ABS(C - A * F(B))
  NEXT B
  PRINT "="; E; "+"; G / 4; "="; E + G / 4
  E = E + G / 4
  IF E < L THEN L = E: M = A: L(0) = F(0): L(1) = F(1): L(2) = F(2): L(3) = F(3)
NEXT A
PRINT M; ":"; L(0); L(1); L(2); L(3)
BB = SGN(L(0)) + SGN(L(1)) + SGN(L(2)) + SGN(L(3))
'++++++++++[>+++++++>++++++++++>+++>+<<<<-]>
PRINT STRING$(M, "+"); "[";
FOR A = 0 TO 3
  IF O(A) > 0 THEN PRINT ">"; STRING$(L(O(A) - 1), "+");
NEXT A
PRINT STRING$(BB, "<"); "-]>";
FOR A = 0 TO 3: L(A) = L(A) * M: NEXT A
'++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
B = 0
FOR A = 1 TO LEN(A$)
  C = ASC(MID$(A$, A, 1))
  SELECT CASE C
  CASE 0 TO 31
    IF B > 0 THEN PRINT STRING$(B, "<"); : B = 0
    IF C > L(0) THEN
      PRINT STRING$(C - L(0), "+");
    ELSE
      PRINT STRING$(L(0) - C, "-");
    END IF
    L(0) = C
  CASE 32 TO 63
    IF B > 1 THEN PRINT STRING$(B - 1, "<"); : B = 1
    IF B = 0 THEN PRINT ">"; : B = 1
    IF C > L(1) THEN
      PRINT STRING$(C - L(1), "+");
    ELSE
      PRINT STRING$(L(1) - C, "-");
    END IF
    L(1) = C
  CASE 64 TO 95
    IF B < 2 THEN PRINT STRING$(2 - B, ">"); : B = 2
    IF B = 3 THEN PRINT "<"; : B = 2
    IF C > L(2) THEN
      PRINT STRING$(C - L(2), "+");
    ELSE
      PRINT STRING$(L(2) - C, "-");
    END IF
    L(2) = C
  CASE 96 TO 126
    IF B < 3 THEN PRINT STRING$(3 - B, ">"); : B = 3
    IF C > L(3) THEN
      PRINT STRING$(C - L(3), "+");
    ELSE
      PRINT STRING$(L(3) - C, "-");
    END IF
    L(3) = C
  END SELECT
  PRINT ".";
NEXT A

