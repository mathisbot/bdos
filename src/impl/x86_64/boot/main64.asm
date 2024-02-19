global long_mode_start
extern kernel_main

section .text
bits 64
long_mode_start:
    ; Load null into all DS registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	call kernel_main  ; kernel/main.c

    ; Get keyboard input
    mov ah, 0  ; Read
    int 0x16  ; BIOS interrupt

    push al
    call print_char  ; kernel/print.c
    pop al

    hlt
