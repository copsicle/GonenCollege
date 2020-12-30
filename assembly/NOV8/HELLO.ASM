
MODEL small
STACK 100h
DATA SEGMENT
message db 13,10,'Hello, World !',13,10,'$'
DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	mov ah, 9
	mov dx, offset message
	int 21h
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


