'BFI.BAS -- BF program emulator
'slower than BFI2, gearing towards ASM emu
DEFINT A-Z
DECLARE SUB BF ()
COMMON SHARED M(), IP, P, S$, SL, O$, A, B
DIM M(29999): P = 0: IP = 0


LOCATE , , 1', 0, 31
OPEN "CONS:" FOR OUTPUT AS #1

'get program data
'S$ = ",+[-.,+]ÿ"
OPEN "FACTOR.BF" FOR BINARY AS #2: S$ = INPUT$(LOF(2), 2) + CHR$(255): CLOSE #2
'S$ = ""
'DO
'  T$ = INPUT$(1)
'  S$ = S$ + T$
'  IF T$ = CHR$(255) THEN EXIT DO
'LOOP
SL = LEN(S$)
CLS
'main loop
CALL BF
END

SUB BF
  SIP = IP
  DO
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
      FOR A = IP + 1 TO SL
        IF MID$(S$, A, 1) = "[" THEN B = B + 1
        IF MID$(S$, A, 1) = "]" THEN B = B - 1
        IF B = 0 THEN EXIT FOR
      NEXT A
      IF M(P) = 0 THEN
        IP = A
      ELSE
        CALL BF: O$ = ""
      END IF
    END IF
    IF O$ = "]" THEN
      'IP = SIP - 1
      'find matching "["
      B = 1
      FOR A = IP - 1 TO 1 STEP -1
        IF MID$(S$, A, 1) = "[" THEN B = B - 1
        IF MID$(S$, A, 1) = "]" THEN B = B + 1
        IF B = 0 THEN EXIT FOR
      NEXT A
      IP = A - 1
      EXIT DO
    END IF
  LOOP
END SUB

