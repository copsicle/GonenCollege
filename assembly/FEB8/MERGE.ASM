; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
	node struc
		info db ?
		next dw ?
	node ends

	start1 node <'a', $+2>, <'b', $+2>, <'g', $+2>, <'l',0>
	start2 node <'c', $+2>, <'d',$+2>, <'f',$+2>, <'l',$+2>, <'z', 0>

	list_1 dw start1
	list_2 dw start2

	head dw ?
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	push DATA
	pop ds
	; Call the merging function with the two lists
	push list_1
	push list_2
	call merge
	; Call the printing function with the head of the new list
	push head
	call printList

exit:
	mov ax, 4c00h
	int 21h

merge PROC
	push bp
	mov bp, sp
	; Move list addresses into pointer registers
	mov si, [bp + 4]
	mov di, [bp + 6]
	; Move first values in lists into ax
	mov ah, [si]
	mov al, [di]
	; Check which one is lower and start with it
	cmp ah, al
	ja inithigh
	; Put address of lowest value node into head
	; And initialize bx as last node added to list
	mov head, si
	mov bx, si
	mov si, [bx + 1]	
	jmp afterinit
inithigh:
	mov head, di
	mov bx, di
	mov di, [bx + 1]
afterinit:
	; Check which node to merge next by info
	mov ah, [si]
	mov al, [di]
	cmp ah, al
	ja afterhigh
	; Merge node and advance pointer to list
	mov [bx + 1], si
	mov bx, si
	mov si, [bx + 1]
	; Check if were at the end of the list
	cmp si, 0
	je lowerend
	jmp afterinit
afterhigh:
	mov [bx + 1], di
	mov bx, di
	mov di, [bx + 1]
	cmp di, 0
	je higherend
	jmp afterinit
lowerend:
	; Merge the end of the other potentially not empty list
	mov [bx + 1], di
	jmp done
higherend:
	mov [bx + 1], si
done:
	pop bp
	ret	4
merge ENDP

printList PROC
	push bp
	mov bp, sp
	; Set to print individual characters and get head of list
	mov ah, 2h
	mov bx, [bp + 4]
iterate:
	; Print the character in the node and advance the pointer
	mov dl, [bx]
	int 21h
	mov bx, [bx + 1]
	; End the printing loop if our pointer is null
	test bx, bx
	jz endprint
	; Print arrow pointing to next node
	mov dl, '-'
	int 21h
	mov dl, '>'
	int 21h
	jmp iterate
endprint:
	; New line - CRLF
	mov dl, 13
	int 21h
	mov dl, 10
	int 21h
	pop bp
	ret 2	
printList ENDP

CODE ENDS
END start