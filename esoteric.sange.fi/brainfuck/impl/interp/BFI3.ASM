; ,]P^0Dw0Dy5{!P/5e PZX5'(n!`This is the source code, not the program code!$
;
; BFI.ASM -- BF program emulator
; TINY VERSION ----- ONLY FOR BFI.BMP!!.. (99 BYTES) 
;
;-------------------------------------------------------------------
; START -- main routine
;-------------------------------------------------------------------
CLEAR:  DEC     BX               ; clear memory 7FFF-FFFF
        MOV     BYTE PTR [BX],CH
        CMP     BH,7Fh
        JNZ     CLEAR    
        MOV     SI,0535h         ; locate BF code
DO:     INC     SI               ; go to next instruction
        MOV     AL,[SI]
        CMP     AL,"@"           ; @    END
        JNZ     O1
        INT     20h
O1:     CMP     AL,">"           ; >    BX=BX+1
        JNZ     O2
        INC     BX  
O2:     CMP     AL,"<"           ; <    BX=BX-1
        JNZ     O3
        DEC     BX
O3:     CMP     AL,"+"           ; +    [BX]=[BX]+1
        JNZ     O4
        INC     BYTE PTR [BX]
O4:     CMP     AL,"-"           ; -    [BX]=[BX]+1
        JNZ     O5
        DEC     BYTE PTR [BX]
O5:     CMP     AL,"."           ; .    OUTPUT [BX]
        JNZ     O6
        MOV     AH,02h
        MOV     DL,[BX]
        INT     21h
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
AGAIN:  CMP     BYTE PTR [SI],"[" 
        JNZ     NOTLSB
        INC     CX              ; add a bracket level
NOTLSB: CMP     BYTE PTR [SI],"]" 
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
M:

