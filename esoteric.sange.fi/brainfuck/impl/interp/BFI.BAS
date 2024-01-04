'BFI.BAS -- BF program emulator
DEFINT A-Z
DECLARE FUNCTION BF (IP, B)
DIM M(29999): P = 0: IP = 1: S$ = ""
LOCATE , , 0, 0, 31
OPEN "CONS:" FOR OUTPUT AS #1

'get data
S$ = ",+[-.,+]ÿ"

CLS
'main loop
NEWIP = BF(IP, 0)
END

FUNCTION BF (IP, B)
SHARED M(), P, S$
  PRINT #1, "!"
  SIP = IP: BB = B
  DO
    PRINT #1, "IP="; MID$(STR$(IP), 2); " B="; MID$(STR$(B), 2); " Y="; MID$(STR$(Y), 2); " P="; MID$(STR$(P), 2); " M(P)="; MID$(STR$(M(P)), 2)
    O$ = MID$(S$, IP, 1)
    IF O$ = CHR$(255) THEN END
    IF Y = 0 THEN
      IF O$ = ">" THEN P = (P + 1) MOD 30000: PRINT #1, ">"
      IF O$ = "<" THEN P = (P + 29999) MOD 30000: PRINT #1, "<"
      IF O$ = "+" THEN M(P) = (M(P) + 1) MOD 256: PRINT #1, "+"
      IF O$ = "-" THEN M(P) = (M(P) + 255) MOD 256: PRINT #1, "-"
      IF O$ = "." THEN PRINT #1, "." 'CHR$(M(P));
      IF O$ = "," THEN
        PRINT #1, ","
        ': LOCATE , , 1:
        M(P) = ASC(INPUT$(1))
        ': LOCATE , , 0
      END IF
      IF O$ = "[" THEN
        PRINT #1, "["
        B = B + 1
        IF M(P) = 0 THEN
          Y = 1            'value 0 on start of loop, skip thru loop
        ELSE
          NEWIP = BF(IP + 1, B)
          IP = NEWIP
        END IF
      END IF
      IF O$ = "]" THEN
        PRINT #1, "]"; M(P);
        IF M(P) = 0 THEN        'value 0, exit loop
          PRINT #1, "$"
          B = B - 1
          EXIT DO
        ELSE                    'value>0, loop again
          IP = SIP - 1: B = B + 1
        END IF
      END IF
    ELSE                        'Y=1 skip thru mode
      IF O$ = "[" THEN B = B + 1
      IF O$ = "]" THEN
        IF B = 0 THEN PRINT #1, "Bracket error!": END
        B = B - 1
        IF B = BB THEN EXIT DO
      END IF
    END IF
    IP = IP + 1
  LOOP
  BF = IP
END FUNCTION

