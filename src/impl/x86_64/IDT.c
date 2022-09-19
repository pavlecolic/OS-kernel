
#include "IDT.h"
#include "print.h"
#include "kbScanCodeTranslation.h"
#include "pit.h"
#include "interrupts.h"

struct IDT64{
   uint16_t offset_low;
   uint16_t selector;
   uint8_t ist;
   uint8_t types_attr;
   uint16_t offset_mid;
   uint32_t offset_high;
   uint32_t zero;
};
extern struct IDT64 _idt[256];
extern uint64_t isr1;
extern uint64_t isr0;
extern void load_idt();


void InitializeIDT() {
       
      _idt[0].zero = 0;
      _idt[0].offset_low = (uint16_t)(((uint64_t) & isr0 & 0x000000000000ffff));
      _idt[0].offset_mid = (uint16_t)(((uint64_t) & isr0 & 0x00000000ffff0000) >> 16);
      _idt[0].offset_high = (uint32_t)(((uint64_t) & isr0 & 0x0000ffff00000000) >> 32);
      _idt[0].ist = 0;
      _idt[0].selector = 0x08;
      _idt[0].types_attr = 0x8e;
   
      _idt[1].zero = 0;
      _idt[1].offset_low = (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
      _idt[1].offset_mid = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
      _idt[1].offset_high = (uint32_t)(((uint64_t)&isr1 & 0x0000ffff00000000) >> 32);
      _idt[1].ist = 0;
      _idt[1].selector = 0x08;
      _idt[1].types_attr = 0x8e;

   remapPic();
   
   outbyte(0x21, 0xfc);
   outbyte(0xa1, 0xff);
   load_idt();
}

void (*mainKeyboardHandler)(uint8_t scanCode, uint8_t chr);

 void isr1_handler() {
   uint8_t scanCode = inbyte(0x60);
   uint8_t chr = 0;
   

   if((scanCode >= 0x02 && scanCode <= 0x0b) || scanCode == 0x14 || scanCode == 0x9C || scanCode == 0x0c || scanCode == 0x14 || scanCode == 0x2E || scanCode == 0x12)
   {
      chr = ASCIITable[scanCode];
   }
   
   if(mainKeyboardHandler != 0) {
      mainKeyboardHandler(scanCode, chr);
   }
    PIC_EndSlave();
}

 void isr0_handler() {
   tick();
   PIC_EndMaster();
 }