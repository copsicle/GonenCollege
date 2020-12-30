; Author: Gonen Cohen
MODEL small
STACK 100h
DATA SEGMENT

var1 db 060h
var2 db 090h

sum dw 0

DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	mov al, var1
	cbw
	mov cl, var2
l1:
	add sum, ax
	loop l1
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


