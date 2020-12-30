
MODEL small
STACK 100h
DATA SEGMENT
; --------------------------
; Your variables here
; --------------------------
DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	mov ax, 0FBh
	mov bx, 0Ch

	div bl

	mov ax, 0141Bh
	mov bx, 12Ch

	div bx

	mov bx, 0

	div bx
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


