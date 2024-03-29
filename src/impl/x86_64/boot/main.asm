global start
extern long_mode_start

section .text
bits 32  ; Starts as 32-bit
start:
	mov esp, stack_top

	; System checks
	call check_multiboot
	call check_cpuid
	call check_long_mode

	; Setup page tables and enable long mode
	call setup_page_tables
	call enable_paging

	; Switch to 64-bit mode
	lgdt [gdt64.pointer]
	jmp gdt64.code_segment:long_mode_start

	hlt

check_multiboot:
	; Check if multiboot is present
	cmp eax, 0x36d76289
	jne .no_multiboot
	ret
.no_multiboot:
	mov al, "M"  ; "M" for "No multiboot"
	jmp error

check_cpuid:
	; Check if CPUID is supported
	pushfd
	pop eax
	mov ecx, eax
	xor eax, 1 << 21
	push eax
	popfd
	pushfd
	pop eax
	push ecx
	popfd
	cmp eax, ecx
	je .no_cpuid
	ret
.no_cpuid:
	mov al, "C"  ; "C" for "No CPUID"
	jmp error

check_long_mode:
	; Check if long mode is supported
	mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jb .no_long_mode

	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jz .no_long_mode
	
	ret
.no_long_mode:
	mov al, "L"  ; "L" for "No long mode"
	jmp error

setup_page_tables:
	mov eax, page_table_l3
	or eax, 0b11
	mov [page_table_l4], eax
	
	mov eax, page_table_l2
	or eax, 0b11
	mov [page_table_l3], eax

	mov ecx, 0  ; Counter
.loop:

	mov eax, 0x200000  ; 2 MebiB = 2097152 B
	mul ecx
	or eax, 0b10000011  ; Present, writable, huge page
	mov [page_table_l2 + ecx * 8], eax

	inc ecx
	cmp ecx, 512 ; Checks if the table is mapped
	jne .loop

	ret

enable_paging:
	; Give page location to the CPU
	mov eax, page_table_l4
	mov cr3, eax

	; Enable Physical Address Extension
	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	; Enable long mode
	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	; Enable paging
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax

	ret

error:
	; Prints "ERR: X" 
	mov dword [0xb8000], 0x4f524f45
	mov dword [0xb8004], 0x4f3a4f52
	mov dword [0xb8008], 0x4f204f20
	mov byte  [0xb800a], al
	hlt

section .bss
align 4096
page_table_l4:
	resb 4096
page_table_l3:
	resb 4096
page_table_l2:
	resb 4096
stack_bottom:
	resb 4096 * 4
stack_top:

section .rodata
gdt64:
	dq 0  ; Zero entry
.code_segment: equ $ - gdt64
	dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)  ; Code segment
.pointer:
	dw $ - gdt64 - 1
	dq gdt64
