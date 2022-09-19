#pragma once
#include <stdint.h>

extern double timeSinceBoot;


void sleepd(double seconds);
void sleep(uint64_t milliseconds);

void setDivisor(uint16_t divisor);
uint64_t getFrequency();
uint16_t getDivisor();
void setFrequency(uint64_t frequency);
void tick();
void setColorFlag();
double getTimeSinceBoot();