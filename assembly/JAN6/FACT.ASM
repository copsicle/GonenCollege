; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
n dw 5
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	inc ax
	push n
	call factorial
	
exit:
	mov ax, 4c00h
	int 21h

factorial PROC
	mov bp, sp
	mul word ptr [bp + 2]
	dec word ptr [bp + 2]
	cmp word ptr [bp + 2], 1
	je end_fact
	push [bp + 2]
	call factorial
end_fact:
	ret 2
factorial ENDP

CODE ENDS
END start