; Author: Gonen Cohen
MODEL small
STACK 100h
DATA SEGMENT
DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	mov ax, 0100h
	mov bx, 05h
l1:
	mov [bx], ah
	mov dl, ah
	add dl, al
	mov al, ah
	mov ah, dl
	inc bx
	cmp ah, 50
	jl l1
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


