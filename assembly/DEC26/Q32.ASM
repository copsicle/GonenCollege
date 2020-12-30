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
	sub di, 2
	mov dx, word ptr coefficient[di]
	add result, dx
	jc big
	test di, di
	jz endc
	mov bx, di
l2:
	test bx, bx
	jz l1
	mov ax, X
	sub bx, 2
	mul word ptr coefficient[bx]
	jc big
	mov word ptr coefficient[bx], ax
	jmp l2

big:
	mov dx, offset toobig
	mov ah, 9h
	int 21h
	jmp exit

endc:
	mov ax, result
	mov bx, 5
	mov cx, 10
populate:
	dec bx
	xor dx, dx
	div cx
	add dl, '0'
	mov byte ptr dec_digit_arr[bx], dl
	test ax, ax
	jnz populate

	xor bx, bx
	mov ah, 2h
prnt:
	mov dl, byte ptr dec_digit_arr[bx]
	test dl, dl
	jz dontprnt
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