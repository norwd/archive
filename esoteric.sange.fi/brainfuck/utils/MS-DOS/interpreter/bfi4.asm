; ,]P^0Dw0Dy5{!P/5e PZX5'(n!`This is the source code, not the program code!$
;=====================================================================
; BFI4.ASM -- BF program emulator
; Copyright (c) 2001 Jeffry Johnston
; Assemble with NASM 0.98.35 or equivalent
;
; Usage: BFI4 filename -or- BFI4 (then type the program and press Enter)
;
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation. See the file LICENSE for more details.
;
; From Brian Raiter's BF page, on Muppetlabs:
; (http://www.muppetlabs.com/~breadbox/bf)
;
; "A [Brainf***] program has an implicit byte pointer, called "the pointer",
; which is free to move around within an array of 30000 bytes, initially all
; set to zero.  The pointer itself is initialized to point to the beginning
; of this array.
;
; The [Brainf***] programming language consists of eight commands, each of
; which is represented as a single character.
; >     Increment the pointer.
; <     Decrement the pointer.
; +     Increment the byte at the pointer.
; -     Decrement the byte at the pointer.
; .     Output the byte at the pointer.
; ,     Input a byte and store it in the byte at the pointer.
; [     Jump [past] the matching ] if the byte at the pointer is zero.
; ]     Jump to the matching [." 
;=====================================================================
CPU     8086
BITS    16
ORG     0100h

;-------------------------------------------------------------------
; START -- main routine
;-------------------------------------------------------------------
        MOV     AH,3Dh          ; OPEN
        MOV     BL,81h          ; change from ASCII to ASCIZ
        ADD     BL,[0080h]      ;  . by putting 00h at end of filename 
        MOV     BYTE [BX],00h   ;  .  
        MOV     DX,0082h        ; where to look for filename
        INT     21h
        JNC     OPENOK          ; opened ok?
        XOR     AX,AX           ; open failed, use STDIN
OPENOK: XCHG    BX,AX           ; put file handle in BX
        MOV     AH,3Fh          ; READ
        MOV     CX,0FFFFh       ; # of bytes to read
        MOV     DX,M            ; put data at M
        INT     21h
        INC     CX
        MOV     SI,M-1          ; locate BF code
        ADD     AX,SI
        XCHG    DI,AX           ; DI=LOF(1)
        MOV     AH,3Eh          ; CLOSE
        INT     21h
        MOV     BX,SP      
CLEAR:  DEC     BX              ; clear memory 7FFF-FFFF
        MOV     [BX],CH
        CMP     BH,7Fh
        JNZ     CLEAR    
DO:     INC     SI              ; go to next instruction
        CMP     SI,DI
        JLE     O1
        RET
O1:     MOV     AL,[SI]
        CMP     AL,">"          ; >    BX=BX+1
        JNZ     O2
        INC     BX  
        CMP     BX,7FFFh
        JB      CRASH           ; oops! went outside memory range
O2:     CMP     AL,"<"          ; <    BX=BX-1
        JNZ     O3
        DEC     BX
        CMP     BX,7FFFh
        JB      CRASH           ; oops! went outside memory range
O3:     CMP     AL,"+"          ; +    [BX]=[BX]+1
        JNZ     O4
        INC     BYTE [BX]
O4:     CMP     AL,"-"          ; -    [BX]=[BX]+1
        JNZ     O5
        DEC     BYTE [BX]
O5:     CMP     AL,"."          ; .    OUTPUT [BX]
        JNZ     O6
        MOV     AH,02h
        MOV     DL,[BX]
        INT     21h
        MOV     AL,00h
O6:     CMP     AL,"]"          ; ]     JUMP BACK TO MATCHING "["
        JNZ     O7   
        POP     SI              ; get "[" location
        DEC     SI              ; go back 1
O7:     CMP     AL,"["          ; [     IF [M]=0 JUMP PAST MATCHING "]"
        JNZ     O8
        PUSH    SI              ; save SI for "]"
        CMP     [BX],CH         ; [M]=0?
        JNZ     DO              
        POP     SI              ; forget "[" location (skipping "]")
        XOR     CX,CX           ; CX=bracket level
AGAIN:  CMP     BYTE [SI],"[" 
        JNZ     NOTLSB
        INC     CX              ; add a bracket level
NOTLSB: CMP     BYTE [SI],"]" 
        JNZ     NOTRSB
        DEC     CX              ; take off a bracket level
        JCXZ    DO              ; if bracket level is 0 then we are done
NOTRSB: INC     SI              ; check out next instruction
        JMP     AGAIN
O8:     CMP     AL,","          ; ,    INPUT [BX]
        JNZ     DO
        MOV     AH,08h
        INT     21h
        MOV     [BX],AL
        JMP     DO
CR      DB      "Illegal code!$"
CRASH:  MOV     AH,09h
        MOV     DX,CR
        INT     21h
        RET
        DB      "Copyright (c) 2001 Jeffry Johnston"
M:      ;DB      ",+[-.,+]"
