
MODEL small
STACK 100h
DATA SEGMENT

Employer1 db 11000001b
Employer2 db 00001100b

task db 01001101b

DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	mov bl, 0
	mov al, Employer1
	mov ah, Employer2
	or al, ah
	mov ah, task
	xor al, ah
	and ah, al
	cmp ah, 0
	jz l1
	jmp l2
l1:
	mov bl, 1
l2:

exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


