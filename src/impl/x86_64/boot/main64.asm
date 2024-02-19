global long_mode_start
extern kernel_main
extern print_key
extern move_cursor

section .text
bits 64

; Entry point for the kernel
long_mode_start:
    ; Load null into all DS registers
    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	call kernel_main  ; kernel/main.c

; Infinite loop to keep the kernel running
kernel_loop:
    call check_keyboard_status
    test eax, eax
    jz kernel_loop

    in al, 0x60

    movzx rdi, al
    call print_key

    jmp kernel_loop

    hlt


; Handling keyboard input
; EAX = 0 if no data available, 1 if data available
check_keyboard_status:
    in al, 0x64
    test al, 0x01
    jnz .key_found
    xor eax, eax
    ret
.key_found:
    mov eax, 1
    ret
