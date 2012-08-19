;--------------------
; Function DisplayAL
; Display digit in al
DisplayAL:
	push ecx
	push edx
	push edi
	
	mov	edi, [dwDispPos]

	mov ah, 0fh
	mov dl, al
	shr al, 4
	mov ecx, 2
.begin:
	and al, 0fh
	cmp al, 9
	ja .1
	add al, '0'
	jmp .2
.1:
	sub al, 0Ah
	add al, 'A'
.2:
	mov [gs:edi], ax
	add edi, 2
	
	mov al, dl
	loop .begin

	mov [dwDispPos], edi
	pop edi
	pop edx
	pop ecx
	ret

;--------------------------
; Function DisplayInt
; Display a 4-byte Integer
; parameter in stack
DisplayInt:
	mov	eax, [esp + 4]
	shr	eax, 24
	call	DisplayAL

	mov	eax, [esp + 4]
	shr	eax, 16
	call	DisplayAL

	mov	eax, [esp + 4]
	shr	eax, 8
	call	DisplayAL

	mov	eax, [esp + 4]
	call	DisplayAL

	mov	ah, 07h			
	mov	al, 'h'
	push	edi
	mov	edi, [dwDispPos]
	mov	[gs:edi], ax
	add	edi, 4
	mov	[dwDispPos], edi
	pop	edi

	ret
;--------------------------
; Function DisplayStringPM
DisplayStringPM:
	push ebp
	mov ebp, esp
	push ebx
	push esi
	push edi

	mov esi, [ebp + 8]; address of string
	mov edi, [dwDispPos]
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
	mov [dwDispPos], edi

	pop edi
	pop esi
	pop ebx
	pop ebp
	ret



;---------------------------
; Function DisplayReturn
DisplayReturn:
	push szReturn
	call DisplayStringPM
	add esp, 4
	ret

;----------------------
; Function Memcpy
; Just as void* memcpy(void* dst, void*, src, int size);
Memcpy:
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
