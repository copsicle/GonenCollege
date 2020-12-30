; Author: Gonen Cohen
MODEL small
STACK 100h
DATA SEGMENT

empty dd 8 dup (0)

dat db 01h, 02h, 03h, 04h, 05h, 06h

DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	mov ah, 0
	mov bx, 20h
	mov cx, 7
l1:
	mov al, [bx]
	mov [bx], ah
	mov ah, al
	inc bx
	loop l1

exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


