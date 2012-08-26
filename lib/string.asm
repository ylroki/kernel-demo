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

;--------------------------
; Function void disp_str(char*);
;--------------------------
global disp_str
global disp_pos

disp_pos dd 0

disp_str:
	push ebp
	mov ebp, esp
	push ebx
	push esi
	push edi

	mov esi, [ebp + 8]; address of string
	mov edi, [disp_pos]
	mov ah, 0fh

.begin:
		lodsb
		test al, al
		jz .end
		cmp al, 0ah
		jnz .display
		push eax
		mov eax, edi
		mov bl, 160
		div bl
		and eax, 0ffh
		inc eax
		mov bl, 160
		mul bl
		mov edi, eax
		pop eax
		jmp .begin

.display:
	mov [gs:edi], ax
	add edi, 2
	jmp .begin

.end:
	mov [disp_pos], edi

	pop edi
	pop esi
	pop ebx
	pop ebp
	ret


