
; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT

arr1 db 17 dup (?)
arr2 dw 07999h, 08000h, 08001h, 08002h

DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	mov cx, 011h

l1:
	mov bx, 011h
	sub bx, cx
	mov ax, bx
	inc ax
	
	mov arr1[bx], al
	
	loop l1
	
	mov cx, 4

l2:
	mov ax, 4
	sub ax, cx
	mov bx, 2
	mul bx
	mov bx, ax
	
	mov ax, arr2[bx]
	neg ax
	mov arr2[bx], ax
	
	loop l2
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


