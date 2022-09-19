global start
extern long_mode_start

section .text
bits 32
start:
    mov esp, stack_top

    call check_multiboot
    call check_cupid
    call check_long_mode

    call setup_page_tables
    call enable_paging
    
    lgdt [gdt64.pointer] 
    jmp gdt64.code_segment:long_mode_start

    
    hlt

check_multiboot:
    cmp eax, 0x36d76289
    jne .no_multiboot
    ret

.no_multiboot:
    mov al, "M"
    jmp error

check_cupid: ; da li se ID bit flags registra moze promijeniti ? https://www.felixcloutier.com/x86/cpuid
    pushfd ;stavlja EFLAG registar na stek
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax ;da li je bit ostao promijenjen ?
    push ecx
    popfd
    cmp eax, ecx
    je .no_cpuid
    ret

.no_cpuid:
    mov al, "C"
    jmp error

check_long_mode:         ;https://wiki.osdev.org/Setting_Up_Long_Mode
    mov eax, 0x80000000    ; Set the A-register to 0x80000000.
    cpuid                  ; CPU identification.
    cmp eax, 0x80000001    ; Compare the A-register with 0x80000001.
    jb .no_long_mode         ; It is less, there is no long mode.

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .no_long_mode

    ret

.no_long_mode:
    mov al, "L"
    jmp error

setup_page_tables:
    mov eax, page_table_l3
    or eax, 0b11 ;present & writeable flags
    mov [page_table_l4], eax

    mov eax, page_table_l2
    or eax, 0b11 ;present & writeable flags
    mov [page_table_l3], eax

    mov ecx, 0 ; brojac

.loop:
    mov eax, 200000 ;dodjeljujemo po 2MiB
    mul ecx
    or eax, 0b10000011 ;7. bit je huge page bit
    mov [page_table_l2 + ecx * 8], eax
    inc ecx
    cmp ecx, 512
    jne .loop

    ret

enable_paging:
    mov eax, page_table_l4
    mov cr3, eax ; https://en.wikipedia.org/wiki/Control_register
    mov eax, cr4
    or eax, 1 << 5 ;Physical Address Extension
    mov cr4, eax

    ;long mode
    mov ecx, 0xC0000080          ; Set the C-register to 0xC0000080, which is the EFER MSR.
    rdmsr                        ; Read from the model-specific register.
    or eax, 1 << 8               ; Set the LM-bit which is the 9th bit (bit 8).
    wrmsr                        ; Write to the model-specific register.
    ;enable paging
    mov eax, cr0                 ; Set the A-register to control register 0.
    or eax, 1 << 31              ; Set the PG-bit, which is the 31st bit
    mov cr0, eax                 ; Set control register 0 to the A-register.

    ret

error: ; ispisuje odgovarajucu error poruku
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte [0xb800a], al
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
gdt64:         ;https://en.wikipedia.org/wiki/Global_Descriptor_Table
                ;https://intermezzos.github.io/book/first-edition/setting-up-a-gdt.html
    dq 0
.code_segment: equ $ - gdt64
    dq (1 << 43) | (1 << 44) | (1 << 47)  | (1 << 53)
.pointer:
    dw $ - gdt64 - 1
    dq gdt64

