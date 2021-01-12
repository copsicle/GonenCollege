; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
tbl db "zxcvbnmasdfghjklqwertyuiop"
txt db "sfctvzuxyf"
txtlen db $ - txt
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	mov ah, 2h
	mov bx, offset tbl
	mov cl, txtlen
	xor di, di
l1:
	mov al, txt[di]
	sub al, 'a'
	xlat
	mov dl, al
	int 21h
	inc di
	loop l1

	mov dl, 13
	int 21h
	mov dl, 10
	int 21h

exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start