; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
arr db 81h, 0A9h, 0C3h, 97h, 0F1h
len dw $-arr
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	; Push array address and length
	push offset arr
	push len
	; Call counting function
	call count
	; Print the array character by character
	mov ah, 2h
	mov bx, offset arr
	mov cx, len
prnt:
	mov dl, byte ptr [bx]
	add dl, '0'
	int 21h
	; Space between each number
	mov dl, ' '
	int 21h
	inc bx
	loop prnt

exit:
	mov ax, 4c00h
	int 21h

count PROC
	; Move stack pointer to base pointer
	mov bp, sp
	; Move array address and length into registers
	mov di, word ptr [bp + 4]
	mov cx, word ptr [bp + 2]

iarray:
	; Outer loop that iterates on the array
	push cx
	xor bl, bl
	mov al, byte ptr [di]
	mov cx, 8
shiftnum:
	; Shift array member 8 bits and add carry to counter
	shr al, 1
	adc bl, 0
	loop shiftnum
	; Move counter into array and go to the next array member
	mov byte ptr [di], bl
	inc di
	pop cx
	loop iarray
	; After passing through all members return and wipe stack
	ret 4
count ENDP

CODE ENDS
END start