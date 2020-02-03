// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License

#ifndef _PRZYCISK_H_
#define _PRZYCISK_H_
#include <stdint.h>

class Przycisk {
    public:
        Przycisk(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
        Przycisk(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char znak);

        uint16_t pressure(void);
        int readTouchY();
        int readTouchX();
        TSPoint_kbv getPoint();
        int16_t pressureThreshhold;

    private:
        uint8_t _yp, _ym, _xm, _xp;
        uint16_t _rxplate;
};

#endif
