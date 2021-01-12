; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
NUM DW 54321
RESULT DW ?
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	push NUM
	call SUM
	pop RESULT ;1
	mov ax, 4c00h
	int 21h

SUM PROC
	push bp
	mov bp, sp
	mov ax, word ptr [bp + 4]
	mov word ptr [bp + 4], 0
	mov bx, 10
	xor dx, dx
AG:
	or ax, ax
	jz exit ;2
	div bx ;3
	add word ptr [bp + 4], dx ;6
	or ax, ax
	jz exit ;2
	neg ax ;4
	cwd
	idiv bx ;5
	add word ptr[bp + 4], dx ;6
	neg ax
	cwd
	jmp AG
exit:
	pop bp
	ret
SUM ENDP

CODE ENDS
END start