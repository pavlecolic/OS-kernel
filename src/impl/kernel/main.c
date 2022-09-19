#include "print.h"
#include "IDT.h"
#include "pit.h"
#include "systemTime.h"
#define true 1
#define false 0

static uint8_t *array;
static uint8_t *array2;

int i = 0;
static int num1 = 0;
static int num2 = 0;
static int sumarum = 0;
_Bool firstIntFlag = false;

void KeyboardHandler(uint8_t scanCode, uint8_t chr) {
   if(firstIntFlag == false) {
      switch (scanCode)
      {
      case 0x02: print_char(chr); array[i] = chr; array[i+1] = '\0'; i++;
        break;
      case 0x03: print_char(chr); array[i] = chr; array[i+1] = '\0'; i++;
      break;
      case 0x04: print_char(chr); array[i] = chr; array[i+1] = '\0'; i++;
      break;
      case 0x05: print_char(chr); array[i] = chr ;array[i+1] = '\0';i++;
      break;
      case 0x06: print_char(chr); array[i] = chr; array[i+1] = '\0';i++;
      break;
      case 0x07: print_char(chr); array[i] = chr; array[i+1] = '\0';i++;
      break;
      case 0x08: print_char(chr); array[i] = chr; array[i+1] = '\0'; i++;
      break;
      case 0x09: print_char(chr); array[i] = chr; array[i+1] = '\0'; i++;
      break;
      case 0x0a: print_char(chr); array[i] = chr; array[i+1] = '\0'; i++;
      break;
      case 0x0b: print_char(chr); array[i] = chr; array[i+1] = '\0'; i++;
      break;
      case 0x0c:  if(i == 0){ print_char(chr); array[i] = chr; array[i+1] = '\0'; i++; } //MINUS '-'
      break;

      case 0x9C: //ENTER
        print_char('+');
        num1 = atoi(array);
        i = 0;
        firstIntFlag = true;
        break;

      case 0x14:printTime(); print_newline();
      break;
      case 0x12: clear_screen();
      case 0x2E: setColorFlag();
      break;
      default:
        break;
      }
   }
   else {
    switch (scanCode)
      {
      case 0x02: print_char(chr); array2[i] = chr;array2[i+1] = '\0'; i++;
        break;
      case 0x03: print_char(chr); array2[i] = chr;array2[i+1] = '\0'; i++;
      break;
      case 0x04: print_char(chr); array2[i] = chr; array2[i+1] = '\0';i++;
      break;
      case 0x05: print_char(chr); array2[i] = chr;array2[i+1] = '\0'; i++;
      break;
      case 0x06: print_char(chr); array2[i] = chr;array2[i+1] = '\0'; i++;
      break;
      case 0x07: print_char(chr); array2[i] = chr;array2[i+1] = '\0'; i++;
      break;
      case 0x08: print_char(chr); array2[i] = chr;array2[i+1] = '\0';  i++;
      break;
      case 0x09: print_char(chr); array2[i] = chr;array2[i+1] = '\0';  i++;
      break;
      case 0x0a: print_char(chr); array2[i] = chr;array2[i+1] = '\0'; i++;
      break;
      case 0x0b: print_char(chr); array2[i] = chr; array2[i+1] = '\0'; i++;
      break;
      case 0x0c: if(i == 0){ print_char(chr); array2[i] = chr; array2[i+1] = '\0'; i++; }// MINUS '-'
      break;
      case 0x9C: //ENTER
        print_char('=');
        num2 = atoi(array2);

        i = 0;
        
        sumarum = num1 + num2;
        print_int(sumarum);
        print_newline();
        firstIntFlag = false;
        break;
        case 0x14: printTime(); print_newline();
        break;
        case 0x2E: setColorFlag();
        break;
      default:
        break;
   }
   }
    
}

void kernel_main(){
    print_clear();
    print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLACK);
    InitializeIDT();
    print_str("Rules:\nAddition: 1. Enter an integer 2.Press enter 3.Enter a second integer 4. Press enter. \nT - display system time since boot in h:m:s format\n C - enable/disable text color change on every system tick\n E - clear screen");
    print_newline();
  
    mainKeyboardHandler = KeyboardHandler;
}