section .data
	nwline db 10
	array dw 8505h,90ffh,87h,88h,8a9h,0adh,02h
	arrcnt equ 7

	pcnt db 0
	ncnt db 0

	msg db "Count of +ve and -ve Numbers in an array",0xa,0
	msg_len equ $-msg

	pmsg db "Count of +ve Numbers:",0xa,0
	pmsg_len equ $-pmsg

	nmsg db "Count of -ve Numbers:",0xa,0
	nmsg_len equ $-nmsg

section .bss
	dispbuff resb 2

%macro print 2
	mov eax,4
	mov ebx,1
	mov ecx,%1
	mov edx,%2
	int 80h
%endmacro

section .text
	global _start

_start:
	print msg,msg_len
	mov esi,array
	mov ecx,arrcnt
	xor eax,eax
	xor ebx,ebx

up1:
	bt word[esi],15
	jnc pnxt
	inc byte[ncnt]
	jmp pskip

pnxt:
	inc byte[pcnt]

pskip:
	add esi, 2
	loop up1

	print pmsg,pmsg_len
	mov bl,[pcnt]
	call disp8num

	print nwline,1
	print nmsg,nmsg_len
	mov bl,[ncnt]
	call disp8num
	print nwline,1

exit:
	mov eax,1
	mov ebx,0
	int 80h

disp8num:
	mov ecx,2
	lea edi,[dispbuff]
	mov al,bl
	shr al,4
	and al,0fh
	add al,'0'
	mov [edi],al
	inc edi
	mov al,bl
	and al,0fh
	add al,'0'
	mov [edi],al
	mov [edi],al

	print dispbuff,2
	ret
