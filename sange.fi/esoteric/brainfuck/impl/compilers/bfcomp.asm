;Assembles with MASM or TASM (I don't know about NASM)
.model tiny
.code
org 100h
start:
;8=char input no echo
;11=get input status
;2=char output
;Reads from the standard input and writes to the standard output.
;You have to redirect the input and output to the desired source
;and object files.
;Works on MS-DOS 7.0 and earlier.  The DOS calls it uses may
;not be implemented in later versions.
;Doesn't check for unbalanced brackets or anything like that.
;Uses only 8086 instructions.
mov di,offset headend
case9:
nextchar:
mov ah,11
int 21h
or al,al
jz inputdone
mov ah,8
int 21h


cmp al,'+'
jne case2
mov ax,0
org $-2
inc byte ptr [bx]
stosw
jmp nextchar
case2:
cmp al,'-'
jne case3
mov ax,0
org $-2
dec byte ptr [bx]
stosw
jmp nextchar
case3:
cmp al,'<'
jne case4
mov al,0
org $-1
dec bx
stosb
jmp nextchar
case4:
cmp al,'>'
jne case5
mov al,0
org $-1
inc bx
stosb
jmp nextchar
case5:
cmp al,'['
jne case6
mov al,0E9h
;org $-1
;jmp near nextchar
;org $-2
stosb
push di
xor ax,ax
stosw
jmp nextchar
case6:
cmp al,']'
jne case7

pop bx
mov ax,di
sub ax,bx
dec ax
dec ax
mov [bx],ax
mov ax,0
org $-2
cmp byte ptr [bx],0
org $-1
stosw
mov ax,0
org $-1 ;not a mistake
jz $
org $-1
stosw
;mov ax,3
mov ax,0E903h
;org $-1 ;not a mistake
;jmp near nextchar
;org $-2
stosw
mov ax,bx
sub ax,di
stosw

jmp nextchar
case7:
cmp al,'.'
jne case8
mov ax,0
org $-2
call dx
stosw
jmp nextchar
case8:
cmp al,','
jne case9
mov ax,0
org $-2
call cx
stosw
jmp nextchar


inputdone:
mov si,offset exitloc
movsw
movsw
movsb
mov cx,di
mov si,offset dataloc
sub cx,si

mov ax,start-dataloc
add ax,di
mov word ptr [movdi+1],ax

outputloop:
lodsb
mov dl,al
mov ah,2
int 21h
loop outputloop

exitloc:
mov ax,4C00h
int 21h
dataloc: ;THIS DETERMINES THE WAY THAT THE COMPILED BF PROGRAM DOES I/O
  jmp l1
c1:
  mov al,byte ptr [start-80h];[80h]
  or al,al
  jnz c1a
  mov ah,10
  push dx
  mov dx,7Fh
  int 21h
  pop dx
  mov byte ptr [cm1-(2+start-dataloc)],81h
  inc byte ptr [start-80h];[80h]
  jmp short c1
c1a:
  ;mov al,[start-7Fh];[81h]
  db 0A0h,81h,0
cm1:
  cmp al,26
  jne c1b
  mov al,-1
c1b:
  cmp al,13
  jne c1c
  mov al,10
c1c:
  inc byte ptr [cm1-(2+start-dataloc)]
  dec byte ptr [start-80h];[80h]
  mov [bx],al
  ret
c1z:
  mov ah,11
  int 21h
  or al,al
  jnz c1za
  dec ax
  jmp short c1zb
c1za:
  mov ah,1
  int 21h
c1zb:
  cmp al,13
  je c1z
  mov [bx],al
  ret
c2:
  ;mov ax,200h
  ;xlat
  mov ah,2
  push dx
  mov dl,[bx]
  cmp dl,10
  jne c2a
  mov dl,13
  int 21h  
  mov dl,10
c2a:
  int 21h  
  pop dx
c2ret:
  ret
l1:
  push cs
  pop ds
  push cs
  pop es
  mov bx,7Fh
  mov byte ptr [bx],80h
  mov al,20h
movdi:
  mov di,0
  ;mov di,offset l2+(start-dataloc)
  ;mov cx,-1
  ;repne scasb
  mov bx,di
  mov cx,sp
  sub cx,di
  xor ax,ax
  rep stosb
  mov cx,offset c1+(start-dataloc)
  ;cmp byte ptr [80h],0
  db 80h,3Eh,80h,0,0  
  jz l1a
  mov cx,offset c1z+(start-dataloc)
l1a:
  mov dx,offset c2+(start-dataloc)
  and sp,-4
  mov bp,sp
l2:
headend:
end start
