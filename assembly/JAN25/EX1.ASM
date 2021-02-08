; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
n dw ?
arr dw 100 DUP (?)
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	; Get input number
	push offset n
	call inputNum
	; Call series function
	mov bx, offset arr
	mov di, 3
	push n
	call series
	; New line - CRLF
	mov ah, 2h
	mov dl, 13
    int 21h
    mov dl, 10
    int 21h

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
	mov ah, 1h
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

series PROC
	push bp
	mov bp, sp
	mov ax, [bp + 4]
	; Check if at the end of the series
	cmp ax, 1
	je end_series
	; Test if number is even or odd
	test ax, 1
	jnz odd
	; Divide by 2 and recurse
	shr ax, 1
	jmp recurse
	; Multiply by di (3), increase by 1 and recurse
odd:
	mul di
	inc ax
recurse:
	push ax
	call series
end_series:
	; Write to array and print
	mov ax, [bp + 4]
	mov [bx], ax
	call print
	; Got to next array address to write
	add bx, 2
	pop bp
	ret 2
series ENDP

print PROC
	mov si, 10
    xor cx, cx
l2:
    ; Push digits of the decimal number onto the stack
    inc cx
    xor dx, dx
    div si
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
	; Space
	mov dl, 32
	int 21h
	ret
print ENDP

CODE ENDS
END start