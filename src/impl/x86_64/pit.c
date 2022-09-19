#include "pit.h"
#include "interrupts.h"
#include "print.h"
#include "systemTime.h"
#define false 0
#define true 1

double timeSinceBoot = 0;
uint16_t Divisor = 65535;
int colorCounter = 0;
_Bool colorFlag = false;

void sleepd(double seconds) {
    double startTime = timeSinceBoot;
    while(timeSinceBoot < startTime + seconds) {
       asm("hlt");
    }
}

void setColorFlag() {
    if(colorFlag == false) {
        colorFlag = true;
    }
    else {
        colorFlag = false;
    }
}
void sleep(uint64_t milliseconds) {
    sleepd((double)milliseconds / 1000);
}

void setDivisor(uint16_t divisor) {
    if(divisor < 100) divisor = 100;
    Divisor = divisor;
    outbyte(0x40, (uint8_t)(divisor & 0x00ff));
    io_wait();
    outbyte(0x40, (uint8_t)(divisor & 0xff00) >> 8);
}
uint16_t getDivisor() {
    return Divisor;
}
uint64_t getFrequency() {
    return 1193182 / Divisor;
}
void setfrequency (uint64_t frequency) {
    setDivisor(1193182 / frequency);
}
double getTimeSinceBoot() {
    return timeSinceBoot;
}
void tick() {
    timeSinceBoot += 1 / (double)getFrequency();
    updateSeconds(timeSinceBoot);
    if(colorFlag == true) {   
        print_set_color(PRINT_COLOR_BLUE + colorCounter , PRINT_COLOR_BLACK);
        colorCounter++;
    if(colorCounter >= 14) {
        colorCounter = 0;
        }
    }
}