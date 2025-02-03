section .data
choice:    db 'Enter choice 1.Addition 2.Subtraction 3.Multiplication 4.Division 5.Exit',10
choicelen: equ $-choice

msg:    db 'Result of addition is: '
len:    equ $-msg

msg1:   db 'Result of subtraction is: '
len1:   equ $-msg1

msg2:   db 'Result of multiplication is: '
len2:   equ $-msg2

msg3:   db 'Result of division is: '
len3:   equ $-msg3

arr:    dq 222222222222222h,11111h,1111h,1111h,1111h
temp:   dq 0

section .bss
count:    resb 1
result:   resb 17
result1:  resb 17
result2:  resb 17
result3:  resb 17

%macro disp 2
    mov rax,1
    mov rdi,1
    mov rsi,%1
    mov rdx,%2
    syscall
%endmacro

section .text
global _start

_start:
main_loop:
    disp choice, choicelen
    mov rax, 0
    mov rdi, 0
    mov rsi, temp
    mov rdx, 8
    syscall

    mov rcx, [temp]

    cmp cl, 31h
    je ch1
    cmp cl, 32h
    je ch2
    cmp cl, 33h
    je ch3
    cmp cl, 34h
    je ch4
    cmp cl, 35h
    je exit
    jmp main_loop

ch1:
    call addition
    jmp main_loop

ch2:
    call subtraction
    jmp main_loop

ch3:
    call multiplication
    jmp main_loop

ch4:
    call division
    jmp main_loop

addition:
    disp msg, len
    mov byte [count], 5
    mov rax, 0
    mov rsi, arr

loop1:
    add rax, [rsi]
    add rsi, 8
    dec byte [count]
    jnz loop1

    mov rbx, rax
    mov rsi, result
    mov byte [count], 10h
    mov cl, 04

    call display
    disp result, 17
    ret

subtraction:
    disp msg1, len1
    mov byte [count], 4
    mov rsi, arr
    mov rax, [rsi]
    add rsi, 8

loop2:
    sub rax, [rsi]
    add rsi, 8
    dec byte [count]
    jnz loop2

    mov rbx, rax
    mov rsi, result1
    mov byte [count], 10h
    mov cl, 04

    call display
    disp result1, 17
    ret

multiplication:
    disp msg2, len2
    mov byte [count], 4
    mov rsi, arr
    mov rax, [rsi]
    add rsi, 8

loop3:
    mov rcx, [rsi]
    mul rcx
    add rsi, 8
    dec byte [count]
    jnz loop3

    mov rbx, rax
    mov rsi, result2
    mov byte [count], 10h
    mov cl, 04

    call display
    disp result2, 17
    ret

division:
    disp msg3, len3
    mov byte [count], 4
    mov rsi, arr
    mov rax, [rsi]
    add rsi, 8

loop4:
    mov rcx, [rsi]
    div rcx
    add rsi, 8
    dec byte [count]
    jnz loop4

    mov rbx, rax
    mov rsi, result3
    mov byte [count], 10h
    mov cl, 04

    call display
    disp result3, 17
    ret

display:
l1:
    rol rbx, cl
    mov dl, bl
    and dl, 0fh
    cmp dl, 09h
    jbe l2
    add dl, 07h
l2:
    add dl, 30h
    mov [rsi], dl
    inc rsi
    dec byte [count]
    jnz l1

    mov byte [rsi], 0ah
    ret

exit:
    mov rax, 60
    xor rdi, rdi
    syscall
