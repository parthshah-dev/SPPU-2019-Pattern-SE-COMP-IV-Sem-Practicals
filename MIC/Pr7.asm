section .data
    rmodemsg db 10, 'Sorry! Processor is in real mode'
    rmsg_len equ $-rmodemsg
    pmodemsg db 10, 'Processor is in protected mode'
    pmsg_len: equ $-pmodemsg
    prmsg db 10, 'Processor register contents: '
    tmsg_len equ $-prmsg
    gdtmsg db 10, 'GDTR contents are: '
    gmsg_len: equ $-gdtmsg
    ldtmsg db 10, 'LDTR contents are: '
    lmsg_len: equ $-ldtmsg
    idtmsg db 10, 'IDTR contents are: '
    imsg_len: equ $-idtmsg
    mswmsg db 10, 'Machine status word: '
    mmsg_len: equ $-mswmsg
    colmsg db ':'
    nwline db 10

section .bss
    cr0_data resb 4
    gdtr resb 6
    ldtr resb 2
    idtr resb 6
    msw resw 1
    tr resw 1
    dnum_buff resb 4

%macro disp 2
    mov eax, 04
    mov ebx, 01
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

section .text
    global _start

_start:
    smsw eax
    BT eax, 0
    jc prmode
    disp rmodemsg, rmsg_len
    jmp nxt1

prmode:
    disp pmodemsg, pmsg_len

nxt1:
    sgdt [gdtr]
    sldt [ldtr]
    sidt [idtr]
    str [tr]

    disp gdtmsg, gmsg_len
    mov bx, [gdtr+4]
    call disp_num
    mov bx, [gdtr+2]
    call disp_num
    disp colmsg, 1
    mov bx, [gdtr]
    call disp_num

    disp ldtmsg, lmsg_len
    mov bx, [ldtr]
    call disp_num

    disp idtmsg, imsg_len
    mov bx, [idtr+4]
    call disp_num
    mov bx, [idtr+2]
    call disp_num
    disp colmsg, 1
    mov bx, [idtr]
    call disp_num

    disp prmsg, tmsg_len
    mov bx, [tr]
    call disp_num

    disp mswmsg, mmsg_len
    mov bx, [msw]
    call disp_num
    mov bx, [cr0_data]
    call disp_num

exit:
    disp nwline, 1
    mov eax, 01
    mov ebx, 00
    int 80h

disp_num:
    mov esi, dnum_buff
    mov ecx, 04

up1:
    rol bx, 04
    mov dl, bl
    AND dl, 0fh
    ADD dl, 30h
    cmp dl, 39h
    jbe skip1
    ADD dl, 07h

skip1:
    mov [esi], dl
    inc esi
    loop up1
    disp dnum_buff, 4
    ret
