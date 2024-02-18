section .multiboot_header
header_start:
	; MultiBoot2 header
	dd 0xe85250d6
	; Architecture (0x0 for i386)
	dd 0
	; Header length
	dd header_end - header_start
	; Checksum
	dd 0x100000000 - (0xe85250d6 + 0 + header_end - header_start)

	; End tag
	dw 0
	dw 0
	dd 8
header_end:
