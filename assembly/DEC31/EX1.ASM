; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
a dw 12h
b dw 0A9h
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	; Push addresses to swap
	push offset a
	push offset b
	; Call the swapping function
	call swapByRef
	
exit:
	mov ax, 4c00h
	int 21h

swapByRef PROC
	; Move stack pointer to base pointer
	mov bp, sp
	; Move the addresses into registers
	mov si, word ptr [bp + 4]
	mov di, word ptr [bp + 2]
	; Get values in addresses
	mov ax, word ptr [si]
	mov bx, word ptr [di]
	; Swap the values in the adresses
	mov word ptr [si], bx
	mov word ptr [di], ax
	; Return and wipe addresses from stack
	ret 4
swapByRef ENDP

CODE ENDS
END start