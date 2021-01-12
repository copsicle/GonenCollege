; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
sum dw 0
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	mov ah, 7h
	int 21h
	sub al, '0'

	cbw
	push ax
	push offset sum
	call sumNum

exit:
	mov ax, 4c00h
	int 21h

sumNum PROC
	push bp
	mov bp, sp
	
	mov ax, 1
	mov bx, [bp + 2]
	mov cx, [bp + 4]
loopa:
	add [bx], ax
	add ax, 2
	loop loopa
	pop bp
	ret 4
sumNum ENDP

CODE ENDS
END start