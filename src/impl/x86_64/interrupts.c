
#include "interrupts.h"
#define PIC1		0x20		
#define PIC2		0xA0		
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_EOI 0x20
#define ICW1_ICW4	0x01		
#define ICW1_SINGLE	0x02		
#define ICW1_INTERVAL4	0x04		
#define ICW1_LEVEL	0x08	
#define ICW1_INIT	0x10		
 
#define ICW4_8086	0x01		
#define ICW4_AUTO	0x02		
#define ICW4_BUF_SLAVE	0x08		
#define ICW4_BUF_MASTER	0x0C		
#define ICW4_SFNM	0x10		

uint8_t inbyte(uint16_t port) {

    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (ret) : "d" (port));
    return ret;
}

void outbyte(uint16_t port, uint8_t data) {
    __asm__ __volatile__ ("outb %1, %0" : : "d" (port), "a" (data) );
}
void io_wait(){
    __asm__ __volatile__ ("outb %%al, $0x80" : : "a"(0));
}
void remapPic(){

    unsigned char a1, a2;
 
	a1 = inbyte(PIC1_DATA);                        
	a2 = inbyte(PIC2_DATA);
 
	outbyte(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  
	io_wait();
	outbyte(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outbyte(PIC1_DATA, 0);                 
	io_wait();
	outbyte(PIC2_DATA, 8);                
	io_wait();
	outbyte(PIC1_DATA, 4);                       
	io_wait();
	outbyte(PIC2_DATA, 2);                       
	io_wait();
 
	outbyte(PIC1_DATA, ICW4_8086);
	io_wait();
	outbyte(PIC2_DATA, ICW4_8086);
	io_wait();
 
	outbyte(PIC1_DATA, a1);   
	outbyte(PIC2_DATA, a2);
    
}
void PIC_EndMaster(){
    outbyte(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSlave(){
    outbyte(PIC2_COMMAND, PIC_EOI);
    outbyte(PIC1_COMMAND, PIC_EOI);
}