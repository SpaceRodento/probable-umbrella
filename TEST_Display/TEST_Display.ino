/*
 * LILYGO T-Display - TESTI
 *
 * Tämä koodi piirtää VÄRILLISET PALKIT näytölle.
 * Jos näet värilliset palkit, tiedämme että näyttö toimii!
 *
 * TÄRKEÄÄ: Valitse laitteesi!
 */

// ====== VALITSE LAITTEESI TÄSTÄ ======
#define TDISPLAY          // T-Display (alkuperäinen ESP32, 1.14" näyttö)
// #define TDISPLAY_S3    // T-Display-S3 (ESP32-S3, 1.9" näyttö)
// #define TPICOC3        // T-PicoC3 (ESP32-C3, 1.14" näyttö)
// =======================================

#define USER_SETUP_LOADED 1

// Lataa oikea näyttökonfiguraatio
#ifdef TDISPLAY
    #define ST7789_DRIVER
    #define TFT_WIDTH  135
    #define TFT_HEIGHT 240
    #define TFT_MOSI 19
    #define TFT_SCLK 18
    #define TFT_CS   5
    #define TFT_DC   16
    #define TFT_RST  23
    #define TFT_BL   4
    #define TFT_RGB_ORDER TFT_RGB
    #define DEVICE_NAME "T-Display"
#elif defined(TDISPLAY_S3)
    #define ST7789_DRIVER
    #define TFT_WIDTH  170
    #define TFT_HEIGHT 320
    #define TFT_MOSI 35
    #define TFT_SCLK 36
    #define TFT_CS   37
    #define TFT_DC   34
    #define TFT_RST  38
    #define TFT_BL   33
    #define DEVICE_NAME "T-Display-S3"
#elif defined(TPICOC3)
    #define ST7735_DRIVER
    #define TFT_WIDTH  135
    #define TFT_HEIGHT 240
    #define TFT_MOSI 7
    #define TFT_SCLK 6
    #define TFT_CS   10
    #define TFT_DC   8
    #define TFT_RST  9
    #define TFT_BL   2
    #define ST7735_GREENTAB160x80
    #define CGRAM_OFFSET
    #define DEVICE_NAME "T-PicoC3"
#else
    #error "Valitse laite!"
#endif

// Yleiset asetukset
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define SPI_FREQUENCY  40000000

// Värit
#define TFT_BLACK   0x0000
#define TFT_BLUE    0x001F
#define TFT_RED     0xF800
#define TFT_GREEN   0x07E0
#define TFT_CYAN    0x07FF
#define TFT_MAGENTA 0xF81F
#define TFT_YELLOW  0xFFE0
#define TFT_WHITE   0xFFFF

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);

void setup() {
    Serial.begin(115200);
    delay(500);

    Serial.println("========================================");
    Serial.println("LILYGO T-DISPLAY TESTI");
    Serial.println("========================================");
    Serial.print("Laite: ");
    Serial.println(DEVICE_NAME);
    Serial.println("");

    // TÄRKEÄ: Kytke backlight päälle!
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    Serial.println("1. Backlight kytketty päälle");

    // Alusta näyttö
    tft.init();
    Serial.println("2. Näyttö alustettu");

    tft.setRotation(1);
    Serial.println("3. Rotaatio asetettu");

    // Täytä näyttö mustalla
    tft.fillScreen(TFT_BLACK);
    Serial.println("4. Näyttö täytetty mustalla");

    delay(500);

    // Piirrä värilliset palkit
    Serial.println("");
    Serial.println("Piirretään VÄRILLISET PALKIT...");
    Serial.println("Jos näet värilliset palkit näytöllä, testi ONNISTUI!");
    Serial.println("");

    int barHeight = TFT_WIDTH / 7;  // 7 väriä

    tft.fillRect(0, 0 * barHeight, TFT_HEIGHT, barHeight, TFT_RED);
    Serial.println("- Punainen palkki");

    tft.fillRect(0, 1 * barHeight, TFT_HEIGHT, barHeight, TFT_GREEN);
    Serial.println("- Vihreä palkki");

    tft.fillRect(0, 2 * barHeight, TFT_HEIGHT, barHeight, TFT_BLUE);
    Serial.println("- Sininen palkki");

    tft.fillRect(0, 3 * barHeight, TFT_HEIGHT, barHeight, TFT_YELLOW);
    Serial.println("- Keltainen palkki");

    tft.fillRect(0, 4 * barHeight, TFT_HEIGHT, barHeight, TFT_CYAN);
    Serial.println("- Syaani palkki");

    tft.fillRect(0, 5 * barHeight, TFT_HEIGHT, barHeight, TFT_MAGENTA);
    Serial.println("- Magenta palkki");

    tft.fillRect(0, 6 * barHeight, TFT_HEIGHT, barHeight, TFT_WHITE);
    Serial.println("- Valkoinen palkki");

    // Lisää teksti
    delay(500);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, TFT_WIDTH - 25);
    tft.print("TESTI OK!");

    Serial.println("");
    Serial.println("========================================");
    Serial.println("VALMIS!");
    Serial.println("========================================");
    Serial.println("Näetkö VÄRILLISET PALKIT näytöllä?");
    Serial.println("- KYLLÄ = Näyttö toimii oikein!");
    Serial.println("- EI = Väärä laite valittu tai vika pinnimäärityksessä");
    Serial.println("");
}

void loop() {
    // Ei tehdä mitään - palkit pysyvät näytöllä
    delay(1000);
}
