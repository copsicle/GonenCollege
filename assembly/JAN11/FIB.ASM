; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
n dw 0
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	; Input the number (word) into memory
	push offset n
	call inputNum
	; zero ax, push n onto the stack and call fib
	xor ax, ax
	push n
	call fib
	; Print the result
	call printNum

exit:
	mov ax, 4c00h
	int 21h

inputNum PROC
	push bp
	mov bp, sp
	; Get address where to put the result from stack
	mov bx, word ptr [bp + 4]
	mov di, 10
	xor dx, dx
l1:
	; Get a character
	mov ah,1
    int 21h
	; Check if its enter
	cmp al, 13
	je next
	; Extend al into ah
	cbw
	mov cx, ax
	; Multiply final number by 10 and add the charcter
	mov ax, word ptr [bx]
	mul di
	; Exit if overflow
	jc next
	sub cx, '0'
	add ax, cx
	; Put result back into memory for next iteration
	mov word ptr [bx], ax
	jmp l1
next:
	pop bp
	ret	2
inputNum ENDP

fib PROC
	; Push bp and bx of previous recursions
	mov bp, sp
	push bx
	; Get n from stack and end recursion if its below 2
	mov bx, word ptr [bp + 2]
	cmp word ptr [bp + 2], 2
	jb inc_fib
	; Call recursion twice for (fib - 1) and (fib - 2)
	dec bx
	push bx
	call fib
	dec bx
	push bx
	call fib
	jmp end_fib
inc_fib:
	; Increment ax when recursion ends on 0 or 1
	inc ax
end_fib:
	; Pop bp and bx for the previous recursion/exit
	pop bx
	ret 2
fib ENDP

printNum PROC
	mov bx, 10
	xor cx, cx
l2:
	; Push digits of the decimal number onto the stack
	inc cx
	xor dx, dx
	div bx
	add dx, '0'
	push dx
	; Push until all digits are in the stack
	test ax, ax
	jnz l2
	mov ah, 2h
prnt:
	; Print the digits in the stack
	pop dx
	int 21h
	loop prnt
	; New line - CRLF
	mov dl, 13
	int 21h
	mov dl, 10
	int 21h
	ret
printNum ENDP

CODE ENDS
END start