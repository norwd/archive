comment	î-ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
	     entry for HUGI size coding	competition #6		³
  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
  ³
  ³  ±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±	    ÛŞÛÛŞÛİÛÛÛ
  ³  ±±	       Brainfuck interpreter	     ±±	    ÛŞİÛ ÛşÛß
  ³  ±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±	    ÛŞİÛİÛ ÛÜÛ
  ³
  ÃÄ the data is stored	in reverse order  (this	can not	be de-
  ³  tected by any valid brainfuck program)
  ÃÄ a brainfuck source	file must not be empty	(but you would
  ³  not call an empty file a program source code, would you?)
  ³  fixing this costs two bytes at the	moment (FIXFS)
  ³
î-Ù
.model tiny
.486
.code
.startup
	FIXFS =	0
	REDIR =	0		; define this to save one byte,	but the
	DEBUG =	0		; resulting program not	handle console
	b	EQU byte ptr	; input	correctly
IF	DEBUG
; assumes
	mov	bh,0
	mov	cx,00FFh	; actually only	cx!=0 is needed
	mov	di,-2
ENDIF
	mov	dh,0Fh		; load program at 0F?? (replaces a mov ah,0Fh)
	push	dx		; push si (restored at @close:)
	mov	ax,1A5Ch	; set DTA adress, first	byte of	mov dx,005Ch
	int	21h
	cbw			; second byte of mov dx,005Ch
	xchg	dx,ax		; third	byte of	mov dx,005Ch; mov ah,0Fh
	int	21h		; OPEN FCB
IF	FIXFS
	mov	ah,27h		; RANDOM BLOCK READ FROM FCB FILE
ELSE
	mov	ah,14h		; SEQUENTIAL READ FROM FCB FILE
ENDIF
	sub	[6Bh+di+2],ah	; set block size to EC80h / D980h
	int	21h		; read file and	fill buffer
IF	FIXFS
	jcxz	@ret		; end program if zero blocks read
ENDIF
@c7:	dec	ax		; '<'(-1), '='(0), '>'(+1)
IF	FIXFS
	add	al,al
ELSE
	add	ax,ax
ENDIF
	sub	di,ax		; update di, init di to	D7FAh (D87Ah)

;> fall	through: cx is non-zero, si is pushed on the stack, al is a no-op

@close:	jcxz	aga		; ']' if cx==0 restore state (pop cx)
	pop	si		; else restore pointer

;> fall	through: al contains a no-op (-2('<'), 0('=',']'), 2('>'), 4(startup))

bloop:	cbw			; handle brackets
	sub	al,'['
	jne	@c1
@open:	push	cx		; '[': save pointer
	mov	cx,[di]		; get new state
@c1:	sub	al,']'-'['
	je	@close
cloop:	jcxz	cxz		; handle commands: if cx==0 skip...
	push	si		; save si (first half of mov cx,si)
	sub	al,'<'-']'	; second half (pop cx) at aga:
	cmp	al,3
	jb	@c7
	sub	al,'+'-'<'
	mov	bl,1		; bx=1
	mov	cx,bx		; cx=1 for '.' and ','
	cmp	al,3
	je	@write
	dec	ax		; does not change cf which is tested at	@c5
IF	REDIR
	jnc	aga
ENDIF
	jne	@c5
@read:	dec	bx		; bx=0
	mov	[di],ax		; clear	upper byte of [di]
@write:	cmp	b [di],0Ah
	jne	@rw		; if we	output a 0Ah, output a 0Dh first
@xchgad:xor	b [di],07h	; 0Ah <--> 0Dh
@rw:	lea	ax,[bx+3FFFh]	; calculate ah=3Fh/40h from bx
	mov	dx,di
	int	21h		; read/write one byte
	cmp	b [di],0Dh	; 0Dh read or written? -> write	0Ah or read
	je	@xchgad		; again
IF	REDIR
	xor	al,1
@c5:	sub	[di],ax		; '+' (-1), '-'	(+1), ',' or '.' (+1 or	0)
ELSE
	dec	ax		; ax=FFFF (EOF)	or ax=0000
	or	[di],ax		; [di]=FFFF (EOF) or no-op, clears cf
@c5:	jnc	aga		; tests	the carry from the cmp al,3 above
	sub	[di],ax		; '+' (-1) or '-' (+1)
ENDIF
aga:	pop	cx		; second half of mov cx,si or restore state
cxz:	lodsw
	dec	si		; get one byte
	jns	bloop		; until	si=8000	(byte at 7FFF read)
@ret:	ret			; finish

; a few	notes on the brackets handling (I hope they are	understandable ;-) :
;
; - after each character executed as command (cloop does not jump to aga,
;   cx!=0), cx will be set to si (pointer to next command)
; - '['	pushes a 0 (in which case cx stays zero) or the	offset of the '[' (with
;   one	exception which	will be	discussed later). the new state	will be	0 if
;   [di] is 0, otherwise the '[' will be executed (noop) and cx	will be	set to
;   si afterwards
; - ']'	restores si to point to	the '['	if the loop was	executed, otherwise
;   it restores	the state in cx	(0 or a	pointer	to a '[')
; - if a '[' follows directly after a ']', and the state inside	the first loop
;   was	0, the pointer saved points to the start of the	first loop (or the
;   one	before etc.), which is no problem because the state inside this	loop
;   is again 0,	that means the saved value will	never be used as a pointer but
;   only as state.
; - needs nesting level	+ 1 stack entries (limit: ~5100	or ~4980)
; - no checking	whether	brackets are balanced; they better are.
end
; '+' ',' '-' '.' '<' '>' '[' ']'
; 43  44  45  46  60  62  91  93
; 2B  2C  2D  2E  3C  3E  5B  5D
