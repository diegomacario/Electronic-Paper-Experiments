#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM!"
#endif

#include <Arduino.h>
#include "epd_driver.h"
#include "pins.h"

uint8_t *framebuffer = NULL;

#include "Game.h"

Game game;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    framebuffer = (uint8_t *)heap_caps_malloc(EPD_WIDTH * EPD_HEIGHT / 2, MALLOC_CAP_SPIRAM);
    if (!framebuffer) {
        Serial.println("Memory allocation failed!");
        while (1);
    }
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

    epd_init();

    epd_poweron();
    epd_clear();
    epd_poweroff();

    Rect_t screenRect = epd_full_screen();
    game.initialize(screenRect.width, screenRect.height);
}

void loop()
{
    epd_poweron();

    for (int32_t i = 0; i < 240; ++i) {
        for (int32_t j = 0; j < 135; ++j) {
            uint8_t value = random(255);
            epd_draw_pixel(i, j, value, framebuffer);
        }
    }
    
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    delay(5000);

    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    epd_clear();
    epd_poweroff();

    game.update();
}
