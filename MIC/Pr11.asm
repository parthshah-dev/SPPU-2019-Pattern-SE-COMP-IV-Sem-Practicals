section .data
    newline db 0xa
    prompt db "Enter number: ", 0
    prompt_len equ $-prompt

section .bss
    input resb 2
    num resb 1
    result resb 4

section .text
    global _start

_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, prompt
    mov rdx, prompt_len
    syscall

    mov rax, 0
    mov rdi, 0
    mov rsi, input
    mov rdx, 2
    syscall

    mov al, [input]
    sub al, '0'
    mov [num], al

    mov ax, 1
    mov bh, 0
    mov bl, [num]
    call fact

    mov esi, result
    mov cl, 4

up:
    rol ax, 4
    mov dx, ax
    and ax, 0fh
    cmp al, 09
    jbe skip
    add al, 07

skip:
    add al, 30h
    mov [esi], al
    inc esi
    mov ax, dx
    dec cl
    jnz up

    mov rax, 1
    mov rdi, 1
    mov rsi, result
    mov rdx, 4
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    mov rax, 60
    mov rdi, 0
    syscall

fact:
    cmp bx, 1
    jne next
    ret

next:
    mul bx
    dec bx
    call fact
    ret
