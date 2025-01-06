;Program to print "Hello, World!"

section .data
	message db 'Hello, World!', 10
	msg_len equ $ - message
	
section .text
	global _start
_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, message
	mov edx, msg_len
	int 80h
	
	mov eax, 1
	xor ebx, ebx
	int 80h
	
