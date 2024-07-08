DEFLNG A-Z
OPEN "PRIME.BF" FOR BINARY AS #1
OPEN "PRIME2.BF" FOR OUTPUT AS #2
Z = LOF(1)
DO WHILE A <= Z
  A = A + 1
  A$ = INPUT$(1, 1)
  IF INSTR("><+-.,[]", A$) = 0 THEN A$ = ""
  PRINT #2, A$;
LOOP

