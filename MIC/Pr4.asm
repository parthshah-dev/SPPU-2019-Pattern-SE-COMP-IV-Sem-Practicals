section .data
    msg db "The largest number is: ", 0
    len equ $ - msg
    numbers dd 0x1A2B3C4D, 0x22E1F2C3, 0x11A4A5B6, 0x3ABCDEE3, 0x444D556E

section .bss
    count resb 1
    result resb 15

section .text
    global _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, len
    int 0x80

    mov byte [count], 5
    xor eax, eax
    mov esi, numbers

find_largest:
    cmp eax, [esi]
    jnc skip_update
    mov eax, [esi]

skip_update:
    add esi, 4
    dec byte [count]
    jnz find_largest

    mov ebx, eax
    mov esi, result

    mov byte [count], 8
    mov cl, 4

convert_to_hex:
    rol ebx, cl
    mov dl, bl
    and dl, 0x0F
    cmp dl, 0x09
    jbe convert_to_ascii
    add dl, 0x07

convert_to_ascii:
    add dl, 0x30
    mov [esi], dl
    inc esi
    dec byte [count]
    jnz convert_to_hex

    mov byte [esi], 0x0A

    mov edx, 9
    mov ecx, result
    mov ebx, 1
    mov eax, 4
    int 0x80

    mov eax, 1
    xor ebx, ebx
    int 0x80

