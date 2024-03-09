#include <LilyGo_AMOLED.h>
#include <TFT_eSPI.h>

#include "Game.h"

LilyGo_Class amoled;

TFT_eSPI tft = TFT_eSPI();

Game game;

void setup()
{
    Serial.begin(115200);

    if (!amoled.begin()) {
        while (1) {
            Serial.println("There is a problem with the device!"); delay(1000);
        }
    }

    game.initialize(&amoled, tft, amoled.height(), amoled.width());
}

void loop()
{
    game.update();
}
