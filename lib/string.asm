global memcpy
;----------------------
; Function memcpy
; Just as void* memcpy(void* dst, void*, src, int size);
memcpy:
	push ebp
	mov ebp, esp
	push esi
	push edi
	push ecx

	mov edi, [ebp + 8]; destination
	mov esi, [ebp + 12]; source
	mov ecx, [ebp + 16]; size
.begin:
	cmp ecx, 0
	jz .end
	mov al, [ds:esi]
	inc esi
	mov byte[es:edi], al
	inc edi

	dec ecx
	jmp .begin

.end:
	mov eax, [ebp + 8]

	pop ecx
	pop edi
	pop esi
	pop ebp
	ret
