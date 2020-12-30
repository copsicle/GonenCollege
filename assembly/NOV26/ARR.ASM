
MODEL small
STACK 100h
DATA SEGMENT
arr1 db 10 dup (5)
arr2 dw 10 dup (5)
arr3 db 20 dup (4,5,6)
DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	mov bx, offset arr1
	mov dl, [bx]

	mov bx, 0000Ah
	mov dx, arr2[bx]

	mov dl, arr3[3]
	
exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


