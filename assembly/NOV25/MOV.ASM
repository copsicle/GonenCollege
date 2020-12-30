
MODEL small
STACK 100h
DATA SEGMENT
DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax
	
	mov byte ptr [ds:30h], 069h
	mov byte ptr [ds:40h], 042h

	mov al, [ds:30h]
	mov ah, [ds:40h]
	mov [ds:40h], al
	mov [ds:30h], ah

	mov byte ptr [ds:4h], 036h

	mov al, [ds:4h]
	mov [ds:12h], al
	mov [ds:13h], al

	mov byte ptr [ds:10h], 0AAh

	mov cl, [ds:10h]
	mov dl, cl
	mov ch, dl
	mov dh, ch

exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


