; Author: Gonen Cohen
MODEL small
STACK 64h

DATA SEGMENT

DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	mov ax, 1234h
	push ax
	pop ax
	push 5678h

	pop bx

	push ax
	push bx
	pop ax
	pop bx

	xor cx, cx
	mov bx, 10
populate:
	xor dx, dx
	inc cx
	div bx
	add dl, '0'
	push dx
	test ax, ax
	jnz populate

	mov ah, 2h
prnt:
	pop dx
	int 21h
	loop prnt

exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start