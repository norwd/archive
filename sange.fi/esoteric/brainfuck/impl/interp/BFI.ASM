; ,]P^0Dw0Dy5{!P/5e PZX5'(n!`This is the source code, not the program code!$
;
; BFI.ASM -- BF program emulator
;
;-------------------------------------------------------------------
; START -- main routine
;-------------------------------------------------------------------
;M       DB      30000 DUP(?)    ; Memory (30000 bytes)               M
;G       DW      1000 DUP(?)     ; GOSUB memory (2000 bytes)          M+30000
;SL      DW      ?               ; Length of input file (2 bytes)     M+32000
;S       DB      ?               ; File space (rest of memory in seg) M+32002
;S       DB      ",+[-.,+]",0FFh
;DI=GG (GOSUB pointer), SI=IP (IP), BX=P (Pointer), AL=O/B
        XOR     SI,SI                   ; IP = 0
        XOR     DI,DI                   ; GG = 0
        MOV     AX,3D00h                ; OPEN
        MOV     BX,0081h                ;\
        ADD     BL,[0080h]              ; > change from ASCII to ASCIZ
        MOV     BYTE PTR [BX],00h       ;/  by putting 00h at end of filename
        MOV     DX,0082h                ; where to look for filename
        INT     21h
        MOV     BX,AX                   ; put file handle in BX
        MOV     AH,3Fh                  ; READ
        MOV     CX,0FFFFh               ; # of bytes to read
        LEA     DX,M+32002              ; put data in S$
        INT     21h
        MOV     M+32000,AX              ; SL=LOF(1)
        MOV     AH,3Eh                  ; CLOSE
        INT     21h
        MOV     BX,M+32000                ;\ S$=S$+CHR$(255)
        MOV     BYTE PTR [M+32002+BX],255 ;/
        MOV     BX,30000                ;\
CLEAR:                                  ; \
        DEC     BX                      ;  > clear memory
        MOV     BYTE PTR [M+BX],0       ; /
        JNZ     CLEAR                   ;/
        CALL    BF                      ; GOSUB BF
        INT     20h                     ; END

;-------------------------------------------------------------------
; BF -- Main program loop
;-------------------------------------------------------------------
BF              PROC    NEAR
        MOV     [M+30000+DI],SI  ; G(GG) = IP
DO:
        MOV     AL,[M+32002+SI]  ; O$ = MID$(S$, IP + 1, 1)
        INC     SI               ; IP = IP + 1
        ;IF O$ = CHR$(255) THEN END
        CMP     AL,255           ; CHR$(255)
        JNZ     O1
        INT     20h    
        ;IF O$ = ">" THEN P = (P + 1) MOD 30000
O1:     CMP     AL,">"           ; >
        JNZ     O2
        CMP     BX,29999
        JNZ     POK1
        MOV     BX,0FFFFh
POK1:
        INC     BX 
        JMP     DO
        ;IF O$ = "<" THEN P = (P + 29999) MOD 30000
O2:     CMP     AL,"<"           ; <
        JNZ     O3
        CMP     BX,0
        JNZ     POK2
        MOV     BX,30000
POK2:
        DEC     BX
        JMP     DO
        ;IF O$ = "+" THEN M(P) = (M(P) + 1) MOD 256
O3:     CMP     AL,"+"           ; +
        JNZ     O4
        INC     BYTE PTR [M+BX]
        JMP     DO
        ;IF O$ = "-" THEN M(P) = (M(P) + 255) MOD 256
O4:     CMP     AL,"-"           ; -
        JNZ     O5
        DEC     BYTE PTR [M+BX]
        JMP     DO 
        ;IF O$ = "." THEN PRINT #1, CHR$(M(P));
O5:     CMP     AL,"."           ; .
        JNZ     O6
        MOV     AH,02h
        MOV     DL,[M+BX]
        INT     21h
        JMP     DO
        ;IF O$ = "," THEN M(P) = ASC(INPUT$(1))
O6:     CMP     AL,","           ; ,
        JNZ     O7
        MOV     AH,08h
        INT     21h
        MOV     [M+BX],AL
        JMP     DO
        ;IF O$ = "[" THEN 'new loop
        ;  find matching "]"
        ;  B = 1
        ;  FOR A = IP TO SL (STEP 1)
        ;    IF MID$(S$, A+1, 1) = "[" THEN B = B + 1
        ;    IF MID$(S$, A+1, 1) = "]" THEN B = B - 1
        ;    IF B = 0 THEN EXIT FOR
        ;  NEXT A
        ;  IF [M+P] = 0 THEN
        ;    IP=A+1
        ;  ELSE
        ;    GG=GG+1
        ;    CALL BF
        ;    GG=GG-1
        ;    JMP DO
        ;  END IF
        ;END IF
O7:     CMP     AL,"["          ; [
        JNZ     O8
        XCHG    BX,CX           ; BX=A, CX=P
        MOV     AL,1            ; B = 1
        MOV     BX,SI           ; FOR A = IP
O71:    CMP     BX,M+32000      ; TO (SL-1)
        JZ      O72    
        CMP     [M+32002+BX],"["; IF MID$(S$, A+1, 1) = "["
        JNZ     O711
        INC     AL              ; THEN B = B + 1
O711:   CMP     [M+32002+BX],"]"; IF MID$(S$, A+1, 1) = "]"
        JNZ     O712
        DEC     AL              ; THEN B = B - 1
O712:   CMP     AL,0            ; IF B = 0
        JZ      O72             ; THEN EXIT FOR
        INC     BX              ; STEP 1
        JMP     O71             ; NEXT A
O72:    XCHG    BX,CX           ; BX=P, CX=A
        CMP     [M+BX],0        ; IF [M+BX] = 0
        JNZ     O73
        MOV     SI,CX           ; THEN IP=A
        INC     SI              ; +1
        JMP     DO
O73:    INC     DI              ; ELSE DI=DI+1
        CALL    BF              ; GOSUB BF
        DEC     DI              ; DI=DI-1
        JMP     DO
        ;IF O$ = "]" THEN IP = G(GG) - 1:GOTO DONE
O8:     CMP     AL,"]"          ; ]
        JNZ     O9   
        MOV     SI,[M+30000+DI]
        DEC     SI
        JMP     DONE
O9:     JMP     DO
DONE:
        RET
BF              ENDP
M:

