section .multiboot_header
;gnu.org sajt
header_start:
    ; magic number
    dd 0xe85250d6 ; multiboot2
    ;arhitektura
    dd 0 ; protected mode
    ;header length
    dd header_end - header_start
    ;checksum
    dd 0x100000000 - (0xe85250d6 + (header_end - header_start))
    ;kraj
    dw 0 ;tip
    dw 0 ;flags
    dd 8 ;size

header_end:
