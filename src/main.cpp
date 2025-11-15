#include <Arduino.h>

// Lataa TFT-näytön konfiguraatio ennen TFT_eSPI.h:ta
#include "User_Setup_Select.h"
#include <TFT_eSPI.h>

// Luo näyttöolio
TFT_eSPI tft = TFT_eSPI();

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Käynnistetään näyttö...");

    // Alusta näyttö
    tft.init();
    tft.setRotation(1); // Vaakatasossa

    // Tyhjennä näyttö (musta tausta)
    tft.fillScreen(TFT_BLACK);

    // Aseta tekstin väri ja koko
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);

    // Näytä teksti näytön keskellä
    tft.setCursor(10, 10);
    tft.println("Hei!");

    tft.setCursor(10, 40);
    tft.setTextColor(TFT_GREEN);
    tft.println("ESP32 toimii!");

    tft.setCursor(10, 70);
    tft.setTextColor(TFT_CYAN);
    tft.setTextSize(1);

#ifdef TDISPLAY
    tft.println("Laite: T-Display");
    tft.println("Naytto: 1.14\" ST7789V");
    tft.println("Siru: ESP32");
#elif defined(TDISPLAY_S3)
    tft.println("Laite: T-Display-S3");
    tft.println("Naytto: 1.9\" ST7789");
    tft.println("Siru: ESP32-S3");
#elif defined(TPICOC3)
    tft.println("Laite: T-PicoC3");
    tft.println("Naytto: 1.14\" ST7735");
    tft.println("Siru: ESP32-C3");
#else
    tft.println("Laite: ESP32");
#endif

    Serial.println("Näyttö valmis!");
}

void loop() {
    // Vilkuta LED jos sellainen on
    static unsigned long lastBlink = 0;
    static bool ledState = false;

    if (millis() - lastBlink > 1000) {
        lastBlink = millis();
        ledState = !ledState;

        // Näytä laskuri ruudulla
        static int counter = 0;
        tft.fillRect(10, 110, 200, 20, TFT_BLACK);
        tft.setCursor(10, 110);
        tft.setTextColor(TFT_YELLOW);
        tft.setTextSize(2);
        tft.print("Laskuri: ");
        tft.print(counter++);

        Serial.print("Laskuri: ");
        Serial.println(counter);
    }
}
