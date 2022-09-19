#pragma once
#include <stdint.h>
#include <stddef.h>


void InitializeIDT();
void isr_handler();
void (*mainKeyboardHandler)(uint8_t scanCode, uint8_t chr);
