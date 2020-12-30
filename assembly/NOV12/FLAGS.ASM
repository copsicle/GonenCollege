
MODEL small
STACK 100h
DATA SEGMENT
var1 dw 0AAh
var2 dw 0FFFFh
var3 dw 01h
var4 dw 08000h
DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	mov ax, var1
	sub ax, var1

	mov ax, var2
	mov bx, var3
	add ax, bx

	mov ax, var4
	add ax, var4

exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


