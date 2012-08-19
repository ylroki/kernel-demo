[section .text]
global _start

_start:
	mov ah, 0fh
	mov al, 'K'
	mov [gs:238], ax
	jmp $
