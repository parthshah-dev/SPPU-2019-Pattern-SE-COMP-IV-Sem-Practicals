section .data
	msg1: db 'Enter a string: '
	size1: equ $-msg1
	newline: db 0x0A
	
section .bss
	string: resb 50
	temp: resb 1
	len: resb 1
	
section .text
	global _start
	
_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, size1
	int 80h
	
	mov ebx, string
	mov byte[len], 0
	
	;convert to ASCII
	mov ebp, 48
	mov[len], ebp
	
reading:
	push ebx
	mov eax, 3
	mov ebx, 0
	mov ecx, temp
	mov edx, 1
	int 80h
	
	pop ebx
	mov al, byte[temp]
	mov byte[ebx], al
	
	inc byte[len]
	inc ebx
	
	cmp byte[temp], 10
	jne reading
	
	dec ebx
	dec byte[ebx]
	dec byte[len]
	
	mov eax, 4
	mov ebx, 1
	mov ecx, len
	mov edx, 1
	int 80h
	
	mov eax, 4
	mov ebx, 1
	mov ecx, newline
	mov edx, 1
	int 80h
	
exit: 
	mov eax, 1
	mov ebx, 0
	int 80h 
	
