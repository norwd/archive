; BrainFuck compiler.  Copyright 1997 Ben Olmstead.  This program is
; governed by the GNU public license.  See the file COPYING for details.
;
; This compiler generates an MS-DOS .COM file from a BrainFuck source.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Note: This program is ****ing tiny.  It has *no* extras at all--if you
; want a more intelligent compiler, use bfc.c instead.  This one has
; nothing more than the basics.
;
; I have been unable to reduce it to less than 331 bytes--this is mainly
; because I am unwilling to do a number of optimizations that may not
; prove safe.  (This is fairly bullet-proof code--not completely (it may
; choke and die if the disk fills up while it is writing out the
; executable, and there are no checks about the executable being
; greater than 64K)--but, overall, pretty good.)  Also, I am unwilling
; to use 486-or-greater-specific instructions, simply because that would
; make a lot of functionality go bye-bye.  (I could, for example,
; replace the first two instructions with 'movzx bx,[0x0080]' and save a
; byte, but then it would choke & die on less than a 486.)  As it is, it
; will only run on a 286 or greater.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
bits 16
org 0x100
section .text

	xor	bx,bx
	mov	bl,[0x0080]
	mov	byte [bx+0x0081],0x00
	mov	dx,0x0082
	mov	ah,0x3d
	int	0x21
	jc	noin
	mov	[inh],ax

	mov	dx,aout
	mov	ah,0x3c
	call	fseek.n
	jc	noout
	mov	[outh],ax

	mov	cx,0x0006
	mov	dx,header
	call	fwrite

	mov	cx,0x0064
for:	push	cx
	mov	cl,0x01
	mov	dx,zero
	call	fwrite
	pop	cx
	loop	for

	call	comp

	mov	cx,0x0001
	mov	dx,noin
	call	fwrite

	mov	bx,[outh]
	mov	ah,0x3e
	int	0x21

noout:	mov	bx,[inh]
	mov	ah,0x3e
	int	0x21

noin:	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
aout	db	"a.c"
n	db	"om"
zero	db	0x00
header	db	0xbe,0x06,0x01	; mov	si,0x106
	db	0xeb,0x65	; jmp	0x16a
	db	0x0d		; db	0x0d
randat	db	0x4e		; dec	si
landat	db	0x46		; inc	si
pludat	db	0xfe,0x04	; inc	byte [si]
mindat	db	0xfe,0x0c	; dec	byte [si]
dotdat	db	0xb4,0x40	; mov	ah,0x40
	db	0xbb,0x01,0x00	; mov	bx,0x0001
	db	0x89,0xd9	; mov	cx,bx
	db	0x89,0xf2	; mov	dx,si
	db	0xcd,0x21	; int	0x21
	db	0x80,0x3c,0x0a	; cmp	byte [si],0x0a
	db	0x75,0x0c	; jnz	$+12
	db	0xb4,0x40	; mov	ah,0x40
	db	0xbb,0x01,0x00	; mov	bx,0x0001
	db	0x89,0xd9	; mov	cx,bx
	db	0xba,0x05,0x01	; mov	dx,0x0105
	db	0xcd,0x21	; int	0x21
taidat	db	0xb4,0x3f	; mov	ah,0x3f
	db	0x3f,0x31	; xor	bx,bx
	db	0xb9,0x01,0x00	; mov	cx,0x0001
	db	0x89,0xf2	; mov	dx,si
	db	0xcd,0x21	; int	0x21
	db	0x80,0x3c,0x0d	; cmp	byte [si],0x0d
	db	0x74,0xf0	; jz	dotdat
opbdat1	db	0x80,0x3c,0x00	; cmp	byte [si],0x00
	db	0x75,0x03	; jnz	$+3
opbdat2	db	0xe9		; jmp	????
instr	db	"<>+-.,"
inlen	db	0x01,0x01,0x02,0x02,0x1c,0x10,0x00
inadr	db	0x65,0x66,0x67,0x69,0x6b,0x87
;	db	(randat) - 0x0100, (landat) - 0x0100, (pludat) - 0x0100
;	db	(mindat) - 0x0100, (dotdat) - 0x0100, (taidat) - 0x0100
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
comp:	mov	ah,0x3f
	db	0xbb
inh	dw	0x0000
	mov	cx,0x0001
	mov	dx,aout
	int	0x21
	mov	bl,[aout]
	or	al,ch
	jz	noin

.nx:	cmp	bl,']'
	jz	noin

openb:	cmp	bl,'['
	jnz	oinsns
	db	0x68
loc	dw	0x0000

	mov	cx,0x0008
	mov	dl,opbdat1 - 0x0100
	call	fwrite

	call	comp

	mov	cx,0x0001
	mov	dl,opbdat2 - 0x0100
	call	fwrite

	pop	ax
	push	ax
	sub	ax,[loc]
	sub	ax,0x0002
	mov	[n],ax

	mov	cx,0x0002
	mov	dx,n
	call	fwrite

	pop	dx
	push	dx
	add	dx,0x0006
	call	fseek

	pop	ax
	neg	ax
	add	ax,[loc]
	sub	ax,0x0008
	mov	[n],ax
	mov	cx,0x0002
	mov	dx,n
	call	fwrite
	sub	word [loc],0x0002

	mov	dx,[loc]
	call	fseek

	jmp	comp

oinsns:	mov	si,instr
	mov	cx,0x0007
oiloop:	lodsb
	cmp	al,bl
	jz	fini
	loop	oiloop

fini:	mov	dh,0x01
	mov	cl,[si+0x0005]
	mov	dl,[si+0x000c]
	call	fwrite
	jmp	comp

fwrite:	mov	ah,0x40
	db	0xbb
outh	dw	0x0000
	int	0x21
	add	[loc],ax
	ret

fseek:	mov	ax,0x4200
	mov	bx,[outh]
.n:	xor	cx,cx
	int	0x21
	ret

end
