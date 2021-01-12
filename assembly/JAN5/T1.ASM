; Author: Gonen Cohen
MODEL small
STACK 100h

DATA SEGMENT
entr db 13
num dw 0
str1 db 'The number has a negetive value $'
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

start:
    mov ax, DATA
    mov ds, ax

    push offset num
    call get
    pop ax
    test ax, 8000h ;5
    jz exit
    mov ah, 9
    lea dx, str1
    int 21h

exit:
    mov ax, 4c00h
    int 21h

get proc
    push bp
    mov bp,sp
    
    mov bx, [bp+4];
    mov si, 10
    mov ah,1
    int 21h
    cmp al, entr
    je get_ret
    sub al, '0' ;1
    cbw
    push ax
ag:
    mov ax, [bx]
    mul si
    mov [bx], ax
    pop ax ;2
    add [bx], ax
    mov ah,1
    int 21h
    cmp al, entr ;3
    je get_ret
    sub al, '0'
    cbw
    push ax
    jmp ag
get_ret:
    mov cx, [bx]
    mov [bp+4], cx
    pop bp
    ret ;4
get endp

CODE ENDS
END start