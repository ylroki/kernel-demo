;-----------------------------
; void out_byte(uint16_t port, uint8_t value);
;-----------------------------
global out_byte
out_byte:
    mov edx, [esp+4]
    mov al, [esp+8]
    out dx, al
    nop
    nop
    ret

;-------------------------------
; uint8_t in_byte(uint16_t port);
;-------------------------------
global in_byte
in_byte:
    mov edx, [esp+4]
    xor eax, eax
    in al, dx
    nop
    nop
    ret

global enable_interrupt
enable_interrupt:
	cli
	ret

global disable_interrupt
disable_interrupt:
	sti
	ret
