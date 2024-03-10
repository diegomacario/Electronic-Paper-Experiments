#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM!"
#endif

#include <Arduino.h>
#include "epd_driver.h"
#include "pins.h"

#include "Game.h"

//Game game;

uint8_t *framebuffer = NULL;

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

    //Rect_t screenRect = epd_full_screen();
    //game.initialize(screenRect.width, screenRect.height);
}

void drawFrame(uint8_t *framebuffer)
  {
    epd_clear_area_cycles(epd_full_screen(), 2, 80);
    delay(100);
    
    epd_draw_image(epd_full_screen(), framebuffer, WHITE_ON_WHITE);
    epd_draw_image(epd_full_screen(), framebuffer, WHITE_ON_WHITE);
    epd_draw_image(epd_full_screen(), framebuffer, WHITE_ON_BLACK);
    
    epd_draw_image(epd_full_screen(), framebuffer, BLACK_ON_WHITE);

    epd_clear();
  }

int iter = 0;

void loop()
{
    epd_poweron();

    if (iter == 0) {
        for (int32_t i = 0; i < 480; ++i) {
            for (int32_t j = 0; j < 270; ++j) {
                uint8_t value = random(255);
                epd_draw_pixel(i, j, value, framebuffer);
            }
        }
    } else if (iter == 1) {
        for (int32_t i = 480; i < 960; ++i) {
            for (int32_t j = 0; j < 270; ++j) {
                uint8_t value = random(255);
                epd_draw_pixel(i, j, value, framebuffer);
            }
        }
    } else if (iter == 2) {
        for (int32_t i = 0; i < 480; ++i) {
            for (int32_t j = 270; j < 540; ++j) {
                uint8_t value = random(255);
                epd_draw_pixel(i, j, value, framebuffer);
            }
        }
    } else if (iter == 3) {
        for (int32_t i = 480; i < 960; ++i) {
            for (int32_t j = 270; j < 540; ++j) {
                uint8_t value = random(255);
                epd_draw_pixel(i, j, value, framebuffer);
            }
        }
    }
    
    iter++;
    iter %= 5;

    if (iter > 3) {
        epd_draw_grayscale_image(epd_full_screen(), framebuffer);
        delay(5000);
    }

    //memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    epd_clear();

    //drawFrame(framebuffer);

    epd_poweroff();

    //game.update();
}
