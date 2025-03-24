section .data
	srcblock db 12h, 45h, 87h, 24h, 97h
	count equ 05
	
	msg db "ALP for nin overlapped block transfer using string instructions: ", 10
	msg_len equ $-msg
	
	msgsrc db 10, "The source block contains the elements: ", 10
	msgsrc_len equ $-msgsrc
	
	msgdest db 10, "The destination block contains the elements: ", 10
	msgdest_len equ $-msgdest
	
	bef db 10, "Before block transfer: ", 10
	bef_len equ $-bef
	
	aft db 10, "After block transfer: ", 10
	aft_len equ $-aft
	
	nwline db " ", 10
	
section .bss
	destblock resb 5
	result resb 4
	
%macro write 2
	mov rax,1
	mov rdi,1
	mov rsi,%1
	mov rdx,%2
	syscall 
%endmacro

section .text
	global _start
	
_start:
	write msg, msg_len
	write bef, bef_len
	
	write msgsrc, msgsrc_len
	mov rsi, srcblock
	call dispblock
	
	write msgdest, msgdest_len
	mov rsi, destblock
	call dispblock
	
	mov rsi, srcblock
	mov rdi, destblock
	mov rcx, count
	cld 
	rep movsb
	
	write aft, aft_len
	
	write msgsrc, msgsrc_len
	mov rsi, srcblock
	call dispblock
	
	write msgdest, msgdest_len
	mov rsi, destblock
	call dispblock
	write nwline, 2
	mov rax, 60
	mov rdi, 0
	syscall
	
dispblock: 
	mov rbp, count

next:
	mov al, [rsi]
	push rsi
	call disp
	pop rsi
	inc rsi
	dec rbp
	jnz next
	ret
	
disp:
	mov bl, al
	mov rdi, result
	mov cx, 02
	
up1:
	rol bl, 4
	mov al, bl
	and al, 0fh
	cmp al, 09h
	jg add_37
	add al, 30h
	jmp skip1
	
add_37:
	add al, 37h

skip1:
	mov[rdi], al
	inc rdi
	dec cx
	jnz up1
	
	write result, 4
	write nwline, 1
	ret