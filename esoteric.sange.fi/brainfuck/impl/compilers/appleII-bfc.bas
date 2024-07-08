0 REM by Simon Biber

10 GOSUB 10000: REM initialisation

500 GET A$: PRINT A$;
510 IF A$=CHR$(3) THEN GOTO 3000: REM finish
520 IF A$="-" THEN R=0:GOSUB 1000: REM (*p)--
530 IF A$="+" THEN R=1:GOSUB 1000: REM (*p)++
540 IF A$="<" THEN R=2:GOSUB 1000: REM p--
550 IF A$=">" THEN R=3:GOSUB 1000: REM p++
560 IF A$="[" THEN GOSUB 1500:R=4:GOSUB 1000: REM while (*p) {
570 IF A$="]" THEN R=5:GOSUB 1000:GOSUB 2000:REM }
580 IF A$="." THEN R=6:GOSUB 1000: REM putchar (*p)
590 IF A$="," THEN R=7:GOSUB 1000: REM *p = getchar(p)
600 GOTO 500

1000 REM write the command in C(R,...)
1010 FOR I=1 to C(R,0)
1020  X=C(R,I)
1030  IF X=-1 THEN X=DL: REM low byte of data address
1040  IF X=-2 THEN X=DH: REM high byte of data address
1050  POKE PC, X
1060  PC=PC+1
1070 NEXT I
1080 RETURN

1500 REM push PC
1510 SN=SN+1: S(SN)=PC
1520 RETURN

2000 OP=s(sn): sn=sn-1: REM pop loop start address
2010 REM put the current address into the jump forward
2020 MS=INT(PC/256): LS=(PC/256-MS)*256
2030 POKE OP+6, LS: POKE OP+7, MS
2040 REM put the start address into the jump back
2050 MS=INT((OP+8)/256): LS=((OP+8)/256-MS)*256
2060 POKE PC-2, LS: POKE PC-1, MS
2070 RETURN

3000 REM finish up
3010 R=8:GOSUB 1000: REM write RTS command
3020 IF F$<>"" THEN PRINT D$;"CLOSE"
3030 PL=PC-PS: REM program length
3040 PRINT
3050 PRINT "Program finished. If you want to save"
3060 INPUT "Enter filename: ";FS$
3070 IF FS$="" THEN 3110
3080 PRINT D$;"BSAVE ";FS$;", A";PS;", L";PL
3090 PRINT "Program saved. If you want to load, type"
3100 PRINT "BLOAD ";FS$
3110 PRINT "To run the program, type CALL ";PS
3120 INPUT "Run now (y/n)? ";YN$
3130 IF YN$="y" OR YN$="Y" THEN CALL PS
3140 END

4000 DIM C(9,10): REM array to hold code
4010 FOR I=0 to 9
4020 READ C(I,0)
4030 FOR J=1 TO C(I,0)
4040 READ C(I,J)
4050 NEXT J
4060 NEXT I
4070 RETURN

5000 REM error handling routine
5010 IF PEEK(222)=5 THEN PRINT:PRINT "End of file reached.":GOTO 3000
5020 PRINT "Sorry, an error occurred, number ";PEEK(222)
5030 END

10000 DIM S(100): REM loop address stack
10010 D$=CHR$(4): REM dos command character
10020 GOSUB 4000: REM read code into array
10030 PRINT "Simon's better BF to Apple II machine code compiler"
10040 PRINT
10050 INPUT "Program address (recommend 8192): ";PS
10060 IF PS<>INT(PS) OR PS<0 OR PS>65535 THEN 10050
10070 INPUT "Data address (recommend 16384): ";DS
10080 IF DS<>INT(DS) OR DS<0 OR DS>65280 THEN 10070
10090 PC=PS: REM program counter
10100 DH=INT(DS/256): REM high byte of data start
10110 DL=(DS/256-DH)*256: REM low byte of data start
10120 R=9:GOSUB 1000: REM Write initialisation routine
10200 PRINT "Name of file to compile, else hit Return"
10210 INPUT "for keyboard: ";F$
10220 IF F$="" THEN RETURN
10230 ?D$;"OPEN ";F$
10240 ?D$;"READ ";F$
10250 ONERR GOTO 5000: REM for the "end of file" error
10260 RETURN

20000 REM (*p)--      DEC DS,X
20010 DATA 3, 222, -1, -2
20100 REM (*p)++       INC DS,X
20110 DATA 3, 254, -1, -2
20200 REM p--          DEX
20210 DATA 1, 202
20300 REM p++          INX
20310 DATA 1, 232
20400 REM while(*p){   LDA DS,X; BNE {+3}; JMP ????
20410 DATA 8, 189, -1, -2, 208, 3, 76, 0, 0
20500 REM }            LDA DS,X; BEQ {+3}; JMP ????
20510 DATA 8, 189, -1, -2, 240, 3, 76, 0, 0
20600 REM putchar(*p)  LDA #80; ORA DS,X; JSR FDED
20610 DATA 8, 169, 128, 29, -1, -2, 32, 237, 253
20700 REM *p=getchar() JSR FD0C; AND #7F; STA DS,X
20710 DATA 8, 32, 12, 253, 41, 127, 157, -1, -2
20800 REM }            RTS
20810 DATA 1, 96
20900 REM for(i=0;i<256;i++)p[i]=0;
20905 REM LDA #00; LDX #00; STA DS,X; DEX; BNE {-6}
20910 DATA 10, 169, 0, 162, 0, 157, -1, -2, 202, 208, 250
