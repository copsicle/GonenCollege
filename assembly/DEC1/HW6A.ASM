
; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT

arr1 db 10, 8, 4, 5
arr2 db 080h, 0A2h, 094h, 0C8h

sum dw ?
isum dw ?

DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	
	mov bx, 0
	mov cx, 4

muloop:

	mov al, arr1[bx]
	mov dl, arr2[bx]
	mul dl
	add sum, ax

	mov al, arr1[bx]
	mov dl, arr2[bx]
	imul dl
	add isum, ax

	inc bx

	loop muloop
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


