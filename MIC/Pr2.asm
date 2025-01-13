section .data
    msg1 db 10,13,"Enter 10 64 bit numbers: $"
    len1 equ $-msg1

    msg2 db 10,13,"Entered 10 64 bit numbers: $"
    len2 equ $-msg2

section .bss
    array resb 200
    counter resb 1

section .text
    global _start

_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg1
    mov rdx, len1
    syscall

    mov byte [counter], 10
    mov rbx, 0

accept_input:
    mov rax, 0
    mov rdi, 0
    lea rsi, [array + rbx]
    mov rdx, 17
    syscall

    add rbx, 17
    dec byte [counter]
    jnz accept_input

    mov rax, 1
    mov rdi, 1
    mov rsi, msg2
    mov rdx, len2
    syscall

    mov byte [counter], 10
    mov rbx, 0

display_numbers:
    mov rax, 1
    mov rdi, 1
    lea rsi, [array + rbx]
    mov rdx, 17
    syscall

    add rbx, 17
    dec byte [counter]
    jnz display_numbers

    mov rax, 60
    mov rdi, 0
    syscall

