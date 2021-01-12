; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
a dw 0F2h
b dw 3
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	push a
	push b
	call mlt
	
exit:
	mov ax, 4c00h
	int 21h

mlt PROC
	mov bp, sp
	add ax, [bp + 4]
	dec word ptr [bp + 2]
	cmp word ptr [bp + 2], 0
	je mlt_ret
	push [bp + 4]
	push [bp + 2]
	call mlt
mlt_ret:
	ret 4	
mlt ENDP

CODE ENDS
END start