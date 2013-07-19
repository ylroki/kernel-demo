;----------------------
; Function memcpy
; Just as void* memcpy(void* dst, void*, src, int size);
global memcpy
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

;----------------------
; Function memset
; Just as void* memset(void* dst, BYTE src, int size);
global memset
memset:
    push ebp
    mov ebp, esp
    push esi
    push edi
    push ecx

    mov edi, [ebp + 8]; destination
    mov edx, [ebp + 12]; source
    mov ecx, [ebp + 16]; size
.begin:
    cmp ecx, 0
    jz .end

    mov byte[edi], dl
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
global disp_char_per_line
global disp_pos_per_line
global disp_line_limit

disp_pos dd 0
disp_char_per_line dd 80
disp_pos_per_line dd 160
disp_line_limit dd 25

disp_str:
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi

    mov edi, [disp_pos]
	cmp edi, 4000
	jb .notfull
	mov edi, 3996
	mov ah, 64 
	mov al, 64 
    mov [gs:edi], ax
	jmp .end

.notfull:
    mov esi, [ebp + 8]; address of string
    ;mov edi, [disp_pos]
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

