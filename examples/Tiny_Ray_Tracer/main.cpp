#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM!"
#endif

#include <Arduino.h>
#include "epd_driver.h"
#include "pins.h"

#include "Game.h"

Game game;

void setup()
{
    Serial.begin(115200);

    delay(1000);

    epd_init();
    epd_poweron();
    epd_clear();
    epd_poweroff();

    Rect_t screenRect = epd_full_screen();
    game.initialize(screenRect.width, screenRect.height);
}

void loop()
{
    game.update();
}
