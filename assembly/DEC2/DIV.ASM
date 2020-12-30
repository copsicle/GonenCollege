
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

	mov al, 7
	mov bl, 2
	mov ah, 0
	
	div bl

	mov ax, 7
	mov dx, 0
	mov bx, 2
	
	div bx
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


