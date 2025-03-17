section .data
    sblock db 10h, 20h, 30h, 50h, 50h, 60h, 70h
    dblock times 7 db 0h
    
    smsg db 10, "Source Block: "
    smsg_len equ $-smsg
    
    dmsg db 10, "Destination Block: "
    dmsg_len equ $-dmsg
    
    space db " "
    nline db 10
    
    before db 10, "#Before Transfer: "
    blen equ $-before
    
    after db 10, "#After Transfer: "
    alen equ $-after 
    
    topic db 10, "# Assignment-8: Non-Overlapped Block Transfer #", 10
    tlen equ $-topic
    
section .bss
    char_ans resb 2
    
print_macro:
%macro print 2
    mov rax, 1
    mov rdi, 1
    mov rsi, %1
    mov rdx, %2
    syscall
%endmacro

%macro exit 0
    mov rax, 60
    mov rdi, 0
    syscall
%endmacro

section .text
    global _start
    
_start:
    print topic, tlen
    
    print before, blen
    
    print smsg, smsg_len
    mov rsi, sblock
    call block_display
    
    print dmsg, dmsg_len
    mov rsi, dblock
    call block_display
    
    call block_transfer
    
    print nline, 1
    print after, alen
    
    print smsg, smsg_len
    mov rsi, sblock
    call block_display
    
    print dmsg, dmsg_len
    mov rsi, dblock
    call block_display
    
    print nline, 1
    exit
    
block_transfer: 
    mov rsi, sblock     
    mov rdi, dblock    
    mov rcx, 7          

back:
    mov al, [rsi]     
    cmp al, [rdi]      
    je skip_transfer    

    mov [rdi], al  

skip_transfer:
    inc rsi            
    inc rdi         
    dec rcx          
    jnz back            
    ret
    
block_display: 
    mov rbp, 7
    
next_num:
    mov al, [rsi]
    push rsi
    
    call display
    print space, 1
    
    pop rsi
    inc rsi
    dec rbp
    jnz next_num
    ret

display:
    mov rbx, 16
    mov rcx, 2
    mov rsi, char_ans+1
    
next_digit:
    mov rdx, 0
    xor rdx, rdx
    div rbx
    
    cmp dl, 09h
    jbe add30
    add dl, 07h
    
add30:
    add dl, 30h
    mov [rsi], dl
    dec rsi
    dec rcx
    jnz next_digit
    
    print char_ans, 2
    ret
