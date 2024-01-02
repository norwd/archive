;; echo.asm: Copyright (C) 2020 Brian Raiter <breadbox@muppetlabs.com>
;; Licensed under the terms of the GNU General Public License, either
;; version 2 or (at your option) any later version.
;;
;; To build:
;;	nasm -f bin -o echo echo.asm && chmod +x echo

BITS 32

		org	0x00010000

		db	0x7F, "ELF"
		dd	1
		dd	0
		dd	$$
		dw	2
		dw	3
		dd	_start
		dd	_start
		dd	4
_start:		inc	ebx			; set ebx to stdout
		inc	edx			; set edx to length 1
		pop	ecx			; discard argc
		pop	ecx			; discard argv[0] (into ecx)
		pop	edi			; save argv[1] in edi
		or	edi, edi		; is argv[1] NULL?
		jz	finish			; yes, skip ahead to finish
		cmp	eax, 0x00010020		; otherwise, enter the loop
mainloop:	mov	ecx, edi		; point ecx at char to output
		jecxz	done			; if pointer is NULL, exit loop
		inc	edi			; point edi at next char
		cmp	[ecx], al		; is there a char to output?
		jnz	out			; yes, continue normally
		mov	[ecx], byte 32		; no, inject a space char
		pop	edi			; and retrieve the next arg
		or	edi, edi		; is there a next arg?
		jnz	out			; yes, continue normally
finish:		mov	[ecx], byte 10		; no, inject a NL instead
out:		mov	al, 4			; 4 == write system call
		int	0x80			; output one byte to stdout
		dec	eax			; did write return 1?
		jz	mainloop		; if so, continue looping
done:		xchg	eax, ebx		; use al for the exit code
		int	0x80			; 1 == exit system call

;; This is how the file looks when it is read as an ELF header,
;; beginning at offset 0:
;;
;; e_ident:	db	0x7F, "ELF"			; required
;;		db	1				; 1 = ELFCLASS32
;;		db	0				; (garbage)
;;		db	0				; (garbage)
;;		db	0				; (garbage)
;;		db	0x00, 0x00, 0x00, 0x00		; (unused)
;;		db	0x00, 0x00, 0x01, 0x00
;; e_type:	dw	2				; 2 = ET_EXE
;; e_machine:	dw	3				; 3 = EM_386
;; e_version:	dd	0x00010020			; (garbage)
;; e_entry:	dd	0x00010020			; program starts here
;; e_phoff:	dd	4				; phdrs located here
;; e_shoff:	dd	0x59594243			; (garbage)
;; e_flags:	dd	0x74FF095F			; (unused)
;; e_ehsize:	dw	0x3D16				; (garbage)
;; e_phentsize:	dw	0x20				; phdr entry size
;; e_phnum:	dw	1				; one phdr in the table
;; e_shentsize:	dw	0xF989				; (garbage)
;; e_shnum:	dw	0x17E3				; (garbage)
;; e_shstrndx:	dw	0x3847				; (garbage)
;;
;; This is how the file looks when it is read as a program header
;; table, beginning at offset 4:
;;
;; p_type:	dd	1				; 1 = PT_LOAD
;; p_offset:	dd	0				; read from top of file
;; p_vaddr:	dd	0x00010000			; load at this address
;; p_paddr:	dd	0x00030002			; (unused)
;; p_filesz:	dd	0x00010020			; too big, but ok
;; p_memsz:	dd	0x00010020			; equal to file size
;; p_flags:	dd	4				; 4 = PF_R
;; p_align:	dd	0x59594243			; (garbage)
;;
;; Some of the fields marked as containing garbage are not used when
;; loading and executing programs. Other fields containing garbage are
;; simply accepted because Linux currently doesn't examine then.
