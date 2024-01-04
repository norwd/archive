'BF interpreter outline

'Variable list
'-------------
'PROGRAM        BF Program
'MEMORY         Memory
'STAK           Square bracket stack
'IP             Instruction Pointer
'IPVALUE        Value at Instruction Pointer, [IP]
'MP             Memory Pointer
'MPVALUE        Value at Memory Pointer, [MP]
'SP             Stack Pointer
'A              (Temp) Keystroke
'LVL            (Temp) Depth of square brackets
'QUIT           Exit flag

DEFINT A-Z
PROGRAM$ = ",+[-.,+]@"
OPEN "C:\BF\PRIME.BF" FOR BINARY AS #1
PROGRAM$ = INPUT$(LOF(1), 1)
CLOSE #1
DIM MEMORY(1 TO 30000)
DIM STAK(1 TO 100)
IP = 0: MP = 1: SP = 1: QUIT = 0
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
D:
    A$ = MID$(UCASE$(INKEY$), 1, 1): IF A$ = "" THEN GOTO D
    MEMORY(MP) = ASC(A$)
  CASE 93 ']
    SP = SP - 1: IP = STAK(SP)
  CASE 91 '[
    IF MPVALUE = 0 THEN
      LVL = 1
      DO
        IP = IP + 1: IPVALUE = ASC(MID$(PROGRAM$, IP, 1))
        IF IPVALUE = 91 THEN LVL = LVL + 1
        IF IPVALUE = 93 THEN LVL = LVL - 1
      LOOP UNTIL LVL <= 0
    ELSE
      STAK(SP) = IP - 1: SP = SP + 1
    END IF
  END SELECT
LOOP UNTIL QUIT
END

