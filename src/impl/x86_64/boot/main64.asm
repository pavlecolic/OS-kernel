global long_mode_start
extern kernel_main
extern load_idt
section .text
bits 64
long_mode_start: ; 0 u sve data segment registre
    mov ax, 0
    mov ss, ax
    mov ds ,ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call load_idt
    
    ; enable SSE
    mov rax, cr0
    and ax, 0xFFFB		;clear coprocessor emulation CR0.EM
    or ax, 0x2			;set coprocessor monitoring  CR0.MP
    mov cr0, rax
    mov rax, cr4
    or ax, 3 << 9		;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
    mov cr4, rax

    ; enable interrupts
    sti 
    ; enter kernel loop


    call kernel_main

.hang:
    hlt
    jmp .hang