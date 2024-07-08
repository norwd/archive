;
; brainfuck compiler by	INT-E
; works	as a filter, that is
;  bfc < program > program.com
;
; History:
;  99/03/27 initial version. 146 bytes
;  99/03/28 changed the	loop code. some	minor optimizations. 136 bytes
;	    made the code public, added	comments
;
; if anybody can give me hints how to reduce the size of this, please send
; me an	e-mail message to
;   int-e@gmx.de
;
; btw. this is work in progress. I don't think that this program is really
; optimized... If you want to give me a	hint, please first look	whether	there
; is a new version available.
;   (link: http://home.pages.de/~int-e/bfc/)
;
; if possible, I'd like to make the compiler Hugi Compo #6 rule conforming.
;   (link: http://www.hugi.de/compo/compoold.htm#compo6)
; (at the moment it isn't because the 10000 bytes file "[][][]..." compiles
; to a 45041 bytes file	which crashes when being run (the end of the code
; gets overwritten when	initializing the data) - I'd have to load all of cx
; (mov cx,10000) to handle this, which costs 1 byte. but compiling real	bf
; programs should be no	problem, up to a size of about 15000-20000 opcodes)
;
; here is a few	things I don't want to do:
; - inline the read/write code.	the resulting programs would become much too
;   big.
; - make the output size constant. (I only want	to save	the code which is
;   necessary to save the program, not the whole compiler, and no unecessary
;   garbage bytes after	the program)
; - use	the stack for handling the brackets in the generated program, like
;   [:cmp [di],bx
;     je ]+1
;     push offset [
;   ]:ret
;   btw	I doubt	that using the stack would actually save anything because
;   (offset [) has to be modified by subtracting (offset @start-0100h)
;

.model	tiny
.386
.code
.startup
b	equ	byte ptr
o	equ	offset

; assumes
;  AL=00 or AL=FF
;  CH=00
;  BX=0000

	mov	di,offset go	; di points to next instruction	to encode

; al is	0 (or FF), which is a no-op

@main:	sub	al,','
	test	al,0FDh
	jne	@L2

	mov	si,o @read-2	; '.' and ','
	sub	si,ax		; o @write is o	@read-2
	mov	al,0E8h		; call @read / call @write
	stosb
	jmp	@reloc

@L2:	sub	al,'+'-','	; '<'->	11h, '>'-> 13h,	'['-> 2Fh, ']'-> 31h
	rol	al,2		;	44h	   4Ch	      BCh	 C4h
	test	al,0F7h		; note that no bits get	lost when using	rol
	jne	@L3		; '+'->	00h, '-'-> 08h

	xchg	al,ah
	add	ax,05FFh	; '+'->	05FF (inc [di])	'-'-> 0DFFh (dec [di])
	stosw

@L3:	xor	al,('<'-'+')*4	; '['->	F8h, ']'-> 80h
	test	al,0F7h
	jne	@L4		; '<'->	00h, '>'-> 08h

	add	al,47h		; '>'->	4F (dec	di) '<'-> 47 (inc di)
	stosb
	stosb

@L4:	xor	al,(('['-'+')xor('<'-'+'))*4
	jne	@L1

	mov	al,0E9h		; '['
	stosb			; jmp rel16
	push	di
	stosw			; room for rel16
	push	di

@L1:	xor	al,((']'-'+')xor('['-'+'))*4
	jne	@next

	pop	ax		; ']'
	pop	si
	mov	[si],di
	sub	[si],ax		; adjust jump
	mov	ax,1D39h
	stosw			; cmp [di],bx
	mov	ax,850Fh
	stosw			; jne rel16

@reloc:	xchg	ax,si		; calculate rel16 (destination si+2)
	sub	ax,di
	stosw

@next:	call	@read		; read one character
	mov	al,[di]		; get character
	jns	@main		; if not EOF, process character

@end:	mov	cx,offset @start; cx = start of	program	to write
	mov	al,0C3h
	stosb			; store	ret
	sub	di,cx		; di = program length
	xchg	di,cx		; swap cx and di...
	inc	bx		; we want to write -> handle 1
	jmp	@rw		; write	data at	di, cx bytes and return	to dos

; assumes:
;  BX=0000
;  SP=FFFE
;  CL>0F
;  DI=SP
;  [SP]=0000
@start:	mov	ch,27h		; init code of compiled	program
;	mov	cx,10000
@l:	push	bx
	loop	@l		; clear	data (fill stack with zeros)
	jmp	go		; execute program

@write:	inc	bx		; entry	point for '.': bx=1
	mov	ax,1234h	; ignore next two bytes
	org	$-2		; 2 bytes size
@read:	mov	[di],bx		; entry	point for ',': clear data word
	mov	cl,1		; cx=1
	cmp	b [di],0Ah	; this is used by the compiler,	too, to	read
	jne	@rw		; characters
@xad:	xor	b [di],07h	; CR <=> LF
@rw:	mov	dx,di
	lea	ax,[bx+3FFFh]	; calculate function from handle
	int	21h		; read/write
	cmp	b [di],0Dh	; CR written ->	write LF, CR read -> read again
	je	@xad
	xor	bx,bx		; reset	bx to 0
	dec	ax		; set [di] to -1 if at EOF...
	or	[di],ax		; set sf if EOF	(needed	for compiler)
	ret
go:
; generated code looks like this: (note	that data is stored in
; reverse order)
; +	-> inc word [di]			(2 bytes)
; -	-> dec word [di]			(2 bytes)
; >	-> dec di		dec di		(2 bytes)
; <	-> inc di		inc di		(2 bytes)
; .	-> call	@write				(3 bytes)
; ,	-> call	@read				(3 bytes)
; [	-> jmp ]				(3 bytes)
; ]	-> cmp [di],bx		jne [+3		(6 bytes)
; end	-> ret					(1 byte)
end
