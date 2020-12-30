
MODEL small
STACK 100h
DATA SEGMENT
num1 dw 76ABh
num2 dw 8013h
DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	mov ax, num1
	add num2, ax
	mov bl, 68h
	add bl, 7Ah
	mov cx, 7FFFh
	add cx, 0Ah
	mov dl, 64h
	add dl, 64h
	sub dl, 0C8h
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start