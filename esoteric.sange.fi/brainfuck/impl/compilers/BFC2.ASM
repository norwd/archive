; BF Compiler -- Jeffry Johnston, March 2001
; Produces i8088, MS-DOS compatible code.  Assemble using A86.
; 123 bytes 
        MOV     AH,9
        MOV     DX,OFFSET START
        INT     21h                     ; output file header
READ:   MOV     AH,8                    ; CHARACTER INPUT WITHOUT ECHO
READ2:  INT     21h
        MOV     DI,OFFSET FIND          ; search table for char
CHECK:  DEC     DI
        CMP     [DI],AL                 ; found?
        JZ      FOUND
        CMP     [DI],CH                 ; didn't find, end of table?
        JNZ     CHECK                   ; if not, keep looking
        JMP     READ2                   ; not an instruction, go to next char
FOUND:  MOV     DX,DI                   ; found a BF instruction!
        INC     DX                      ; position for output
        PUSH    AX
        MOV     AH,9
        INT     21h                     ; output precompiled instructions
        POP     AX
        CMP     AL,"@"                  ; "@" marks EOF
        JNZ     READ                    ; keep reading file till end
        RET                             ; end

; Data and precompiled instructions start here
START:  XOR     CX,CX                   ; clear memory 7FFFh-FFFFh
CLEAR:  DEC     BX                      ;      10:33 C9 4B 88 2F 80 FF 7F 75
        MOV     [BX],CH                 ;         F6
        CMP     BH,7Fh                
        JNZ     START     
        DB      "$"
        DB      0,">"                   ; >     1:43
        INC     BX                      ; M=M+1
        DB      "$"
        DB      "<"                     ; <     1:4B
        DEC     BX                      ; M=M-1
        DB      "$"
        DB      "+"                     ; +     2:FE 07
        INC     BYTE PTR [BX]           ; [M]=[M]+1        
        DB      "$"
        DB      "-"                     ; -     2:FE 0F
        DEC     BYTE PTR [BX]           ; [M]=[M]-1
        DB      "$"
        DB      "."                     ; .     6:B4 02 8A 17 CD 21
        MOV     AH,2                    ; OUTPUT [M]
        MOV     DL,[BX]
        INT     21h
        DB      "$"
        DB      ","                     ; ,     6:B4 08 CD 21 88 07
        MOV     AH,8                    ; INPUT [M]
        INT     21h
        MOV     [BX],AL
        DB      "$"
        DB      "]"                     ; ]     2:C3 90
        RET                             ; return to matching "["
        NOP
        DB      "$"
        DB      "@"                     ; @     1:C3   
        RET                             ; end program
        DB      "$"
        DB      "["                     ; [    33:E8 00 00 5E 4E 4E 4E 56 38 
FIND:   DB      0E8h,00h,00h            ;         2F 75 15 80 3C E8 75 01 41
        POP     SI                      ;         80 3C 90 75 01 49 E3 03 46
        DEC     SI                      ;         EB EF 58 46 FF E6   
        DEC     SI                      ; get IP and move back to FIND:
        DEC     SI
        PUSH    SI                      ; store IP, for future jump to "["
        CMP     [BX],CH                 ; if [M]<>0, then don't jump past "]"
        JNZ     PAST                    ; if [M]=0, find "]" so we can jump 
AGAIN:  CMP     BYTE PTR [SI],0E8h      ; if "[" (CALL) then go deeper
        JNZ     NOTLSB
        INC     CX                      
NOTLSB: CMP     BYTE PTR [SI],90h       ; if "]" (NOP) then shallow one level
        JNZ     NOTRSB
        DEC     CX
NOTRSB: JCXZ    DONE                    ; end of []?    
        INC     SI
        JMP     AGAIN                   ; if not, keep going
DONE:   POP     AX                      ; done, lose the return to "["
        INC     SI
        JMP     SI                      ; jump past "]"
PAST:   DB      "$"                     

