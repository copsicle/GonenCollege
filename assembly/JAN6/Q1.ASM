; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
num dw 0
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	push offset num
	call inputNum
	push offset num
	call printNum

exit:
	mov ax, 4c00h
	int 21h

inputNum PROC
	push bp
	mov bp, sp
	mov bx, [bp + 4]
	mov di, 10
	xor dx, dx
l1:
	mov ah,1
    int 21h
	cmp al, 13
	je next
	cbw
	mov cx, ax
	mov ax, [bx]
	mul di
	sub cx, '0'
	add ax, cx
	mov [bx], ax
	jmp l1
next:
	pop bp
	ret	2
inputNum ENDP

printNum PROC
	push bp
	mov bp, sp
	mov ah, 2h
	mov bx, [bp + 4]
	mov cl, 12
	mov di, 0F000h
l2:
	mov dx, [bx]
	and dx, di
	shr dx, cl

	cmp dl, 9
	jbe isnum
	
	add dl, 'A' - 10
	int 21h
	jmp after
isnum:
	add dl, '0'
	int 21h 
after:
	sub cl, 4
	shr di, 4
	jnc l2

	mov dl, 'h'
	int 21h
	pop bp
	ret 2
printNum ENDP

CODE ENDS
END start