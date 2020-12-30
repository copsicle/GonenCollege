; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
X dw 4
coefficient dw 8, 6, 3, 11, 26
n dw 5
result dw 0
dec_digit_arr db 5 dup (0)
toobig db 'The polinom is to big to continue calculate, more than 16bit$'
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	mov di, n
	shl di, 1

l1:
	mov bx, n
	shl bx, 1
	sub bx, di
	mov ax, word ptr coefficient[bx]

	shr di, 1
	dec di
	cmp di, 0
	jz endc
	
	mov cx, di
	mov bx, X
	shl di, 1
l2:
	mul bx
	cmp dx, 0
	jne big
	loop l2

	add result, ax
	jnc l1

big:
	mov dx, offset toobig
	mov ah, 9h
	int 21h
	jmp exit

endc:
	add result, ax
	
	mov ax, result
	mov bx, 5
	mov cx, 10
populate:
	dec bx
	xor dx, dx
	div cx
	add dl, '0'
	mov byte ptr dec_digit_arr[bx], dl
	cmp ax, 0
	jnz populate

	xor bx, bx
	mov ah, 2h
prnt:
	mov dl, byte ptr dec_digit_arr[bx]
	cmp dl, 0
	je dontprnt
	int 21h
dontprnt:
	inc bx
	cmp bx, 5
	jb prnt

exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start