; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
arr db 8 DUP (?)
arrsize EQU $-arr
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	; Input into array
	mov bx, offset arr
	mov cx, arrsize
	call input
	; Sort the array
	push offset arr
	push arrsize
	call bubble
	; Print the sorted array
	mov bx, offset arr
	mov cx, arrsize
	call output

exit:
	mov ax, 4c00h
	int 21h

input PROC
	mov ah, 1h
l1:
	; Input x (cx) digits and put in address y (bx)
	int 21h
	sub al, '0'
	mov [bx], al
	inc bx
	loop l1
	; New line - CRLF
	mov ah, 2h
	mov dl, 13
    int 21h
    mov dl, 10
    int 21h
	ret
input ENDP

bubble PROC
	push bp
	mov bp, sp
	; Decrement length by 1 as were checking item i and i+1
	dec word ptr [bp + 4]
	mov bx, [bp + 6]
	mov cx, [bp + 4]
l2:
	; Get the two digits by address
	mov al, [bx]
	mov ah, [bx + 1]
	; Check if the left one is bigger
	cmp al, ah
	jna eol
	; Swap
	mov [bx], ah
	mov [bx + 1], al
eol:
	; Increase address and loop to bubble biggest digit
	inc bx
	loop l2
	; Check if were done sorting
	cmp word ptr [bp + 4], 1
	je end_bubble
	; Recurse
	push [bp + 6]
	push [bp + 4]
	call bubble
end_bubble:
	pop bp
	ret 4
bubble ENDP

output PROC
	mov ah, 2h
l3:
	; Print array with x (cx) items on address y (dx)
	mov dl, [bx]
	add dl, '0'
	int 21h
	; Space
	mov dl, 32
	int 21h
	; Go to next item in the array and loop
	inc bx
	loop l3
	; New line - CRLF
	mov dl, 13
    int 21h
    mov dl, 10
    int 21h
	ret
output ENDP

CODE ENDS
END start