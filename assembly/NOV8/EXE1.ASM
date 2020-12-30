
MODEL small
STACK 100h
DATA SEGMENT
var1 db 5
DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	
	mov al, var1
	mov ax, 10
	mov bx, 1010b
	mov cx, 0Ah
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


