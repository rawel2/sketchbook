#include "Arduino.h"

#include "przycisk.h"



Przycisk::Przycisk(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
    _x1 = x1;
    _y1 = y1;
    _x2 = x2;
    _y2 = y2;
}

Przycisk::Przycisk(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char znak){
    _x1 = x1;
    _y1 = y1;
    _x2 = x2;
    _y2 = y2;
    _znak = znak;
}


void Przycisk::Paint(){

}

int16_t Przycisk::IsPressed(){

}