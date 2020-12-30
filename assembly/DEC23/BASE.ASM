; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
nl db 13, 10, '$'
prompt db '>>> $'
wel db 'Welcome $'
exc db '!!!$'
namelim db 20
fname db 21 dup (?)
other db 'bla la la$'
pend db 'See you soon...$'
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	xor ax, ax
	
	mov dx, offset prompt
	mov ah, 9h
	int 21h

	mov dx, offset namelim
	mov ah, 0Ah
	int 21h
	
	mov dx, offset nl
	mov ah, 9h
	int 21h

	xor bx, bx
	mov bl, fname
	add bx, offset fname
	inc bx
	mov byte ptr [bx], '$'

	mov dx , offset wel
	mov ah, 9h
	int 21h
	mov dx, offset (fname + 1)
	int 21h
	
	mov dl, ' '
	mov ah, 2h
	int 21h

	mov dx, offset exc
	mov ah, 9h
	int 21h
	mov dx, offset nl
	int 21h
	mov dx, offset prompt
	int 21h

l1:
	mov ah, 7h
	int 21h
	cmp al, 0
	jz special
	cmp al, 27
	je exit
	cmp al, 58
	jb number
	cmp al, 91
	jb letter
	cmp al, 123
	jb sletter
el:
	mov dx, offset other
	mov ah, 9h
	int 21h
	jmp l1

special:
	int 21h
	cmp al, 83
	je inf
	cmp al, 75
	je arrow
	cmp al, 77
	je arrow
	jmp el

inf:
	mov dl, 0
	mov ah, 2h
	int 21h
	mov dl, 236
	int 21h
	jmp l1

arrow:
	mov bl, al
	sub bl, 74
	mov dl, 0
	mov ah, 2h
	int 21h
	mov dl, bl
	int 21h
	jmp l1

number:
	cmp al, 48
	jb el
	mov dl, al
	mov ah, 2h
	int 21h
	jmp l1

sletter:
	cmp al, 97
	jb el
letter:
	cmp al, 65
	jb el
	mov dl, '*'
	mov ah, 2h
	int 21h
	jmp l1

exit:
	mov dx, offset nl
	mov ah, 9h
	int 21h
	mov dx, offset pend
	int 21h
	mov ax, 4c00h
	int 21h

CODE ENDS
END start