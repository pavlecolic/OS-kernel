#pragma once
#include <stdint.h>

uint8_t inbyte(uint16_t port);
void outbyte(uint16_t port, uint8_t data);
void remapPic();
void io_wait();
void PIC_EndMaster();
void PIC_EndSlave();