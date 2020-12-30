
MODEL small
STACK 100h
DATA SEGMENT

digit db 5
num dw -1
tenw dw 10
mone db 0

DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	mov ax, num
next:
	xor dx, dx
	div tenw
	cmp dl, digit
	jne go
	add mone, 1
go:
	cmp ax, 0
	jne next

exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


