
MODEL small
STACK 100h
DATA SEGMENT
firstMemLine db 8 DUP (0AAh)
SecondMemLine db 8 DUP (0BBh)
ThirdMemLine db 8 DUP (0CCh)
DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
start:
	mov ax, DATA
	mov ds, ax

	nop

exit:
	mov ax, 4c00h
	int 21h
CODE ENDS
END start


