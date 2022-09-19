ENTRY(start)

SECTIONS 
{
	. = 1M;

	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot_header)
		*(.text)
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	.idt BLOCK(0x1000) :ALIGN(0x1000)
	{
		_idt = .;
		. = . + 0x1000;
	}

	.eh_frame BLOCK(4K) : ALIGN(4K)
	{
		*(.eh_frame)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
