'BF interpreter outline

'Variable list
'-------------
'PROGRAM        BF Program
'MEMORY         Memory
'IP             Instruction Pointer
'IPVALUE        Value at Instruction Pointer, [IP]
'MP             Memory Pointer
'MPVALUE        Value at Memory Pointer, [MP]
'A              (Temp) Keystroke
'LEVEL          (Temp) Depth of square brackets
'QUIT           Exit flag

DEFINT A-Z
PROGRAM$ = ",+[-.,+]@"
OPEN "C:\BF\FACTOR.BF" FOR BINARY AS #1
PROGRAM$ = INPUT$(LOF(1), 1)
CLOSE #1
DIM MEMORY(1 TO 30000)
IP = 0: MP = 1: QUIT = 0
DO
  IP = IP + 1: IPVALUE = ASC(MID$(PROGRAM$, IP, 1))
  MPVALUE = MEMORY(MP)
  SELECT CASE IPVALUE
  CASE 64 '@
    QUIT = -1
  CASE 60 '<
    MP = MP - 1
  CASE 62 '>
    MP = MP + 1
  CASE 43 '+
    MEMORY(MP) = (MPVALUE + 1) MOD 256
  CASE 45 '-
    MEMORY(MP) = (MPVALUE + 255) MOD 256
  CASE 46 '.
    PRINT CHR$(MPVALUE);
  CASE 44 ',
A:  A$ = MID$(UCASE$(INKEY$), 1, 1): IF A$ = "" THEN GOTO A
    MEMORY(MP) = ASC(A$)
  CASE 93 ']
    DIRECTION = -1: GOSUB MATCH
    IP = IP - 1
  CASE 91 '[
    IF MPVALUE = 0 THEN DIRECTION = 1: GOSUB MATCH
  END SELECT
LOOP UNTIL QUIT
END

MATCH:
  LEVEL = 1
  DO
    IP = IP + DIRECTION: IPVALUE = ASC(MID$(PROGRAM$, IP, 1))
    IF IPVALUE = 91 THEN LEVEL = LEVEL + DIRECTION
    IF IPVALUE = 93 THEN LEVEL = LEVEL - DIRECTION
  LOOP UNTIL LEVEL <= 0
RETURN

