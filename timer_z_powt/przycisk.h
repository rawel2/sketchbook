
// Code under MIT License

#ifndef _PRZYCISK_H_
#define _PRZYCISK_H_
#include <stdint.h>

class Przycisk {
    public:
        Przycisk(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
        Przycisk(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char znak);

        void Paint();
        int16_t IsPressed();

    private:
        uint8_t _x1, _x2, _y1, _y2;
        char _znak;
};

#endif
