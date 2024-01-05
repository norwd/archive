;=====================================================================
; HELLO -- Hello World Example
; Filename : hello.asm
; Language : ASM
; Version  : 0.20
; Copyright: (C) 2004 Jeffry Johnston
;
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation. See the file LICENSE for more details.
;
; Version history:
; 0.20    04 Aug 2004 Fixed puts to output a linefeed after text
; 0.10    24 Jun 2004 Initial release
;=====================================================================

;=====================================================================
; data
;=====================================================================
stk     2               ; set up the stack with 2 elements max
org     0
txt     "Hello World!"
db_     0               ; NUL

;=====================================================================
; main
;=====================================================================
        psh     1       ; return address
        psh     0       ; address of text string
        jmp     100     ; call puts
lbl 1
        end             ; end program

;=====================================================================
; puts
;=====================================================================
lbl 100
        pop     r1      ; get address
lbl 102
        rcl     r2,r1   ; get character at address
        jz_     r2,101  ; it is zero (NUL)?  if so, done
        out     r2      ; no, output it
        inc     r1      ; go to the next character
        jmp     102     ; repeat
lbl 101
        out     10      ; output newline
ret