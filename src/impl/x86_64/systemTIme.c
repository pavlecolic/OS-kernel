#include "systemTime.h"
#include "print.h"
int hs = 0;
int min = 0;
int sec = 0;


void updateSeconds(double timeSinceBoot) {
    sec = (int)timeSinceBoot % 60;
    if(sec == 59){
        updateMinutes();
    }
}

void updateMinutes() {
    min++;
    if(min == 60) {
        updateHours();
        min = 0;
    }
}

void updateHours() {
    hs++;
    if(hs == 24) {
        hs = 0;
    }
}

void printTime() {
       print_int(hs);
       print_char(':');
       print_int(min/18);
       print_char(':');
       print_int(sec);
}