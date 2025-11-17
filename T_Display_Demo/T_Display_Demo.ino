/*
 * LILYGO T-Display Demo
 *
 * Tämä esimerkki toimii Arduino IDE:ssä kaikille T-Display -laitteille.
 *
 * TÄRKEÄÄ: Valitse laitteesi alla olevasta vaihtoehdosta
 * poistamalla kommenttimerkinnät (//) oikean laitteen riviltä!
 */

// ====== VALITSE LAITTEESI TÄSTÄ ======
// Poista // sen laitteen edestä joka sinulla on!

#define TDISPLAY          // T-Display (alkuperäinen ESP32, 1.14" näyttö)
// #define TDISPLAY_S3    // T-Display-S3 (ESP32-S3, 1.9" näyttö)
// #define TPICOC3        // T-PicoC3 (ESP32-C3, 1.14" näyttö)

// =======================================

// Määritä että käytetään omaa konfiguraatiota
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
    #define DISPLAY_NAME "1.14\" ST7789V"
    #define CHIP_NAME "ESP32"

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
    #define DISPLAY_NAME "1.9\" ST7789"
    #define CHIP_NAME "ESP32-S3"

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
    #define DISPLAY_NAME "1.14\" ST7735"
    #define CHIP_NAME "ESP32-C3"

#else
    #error "Valitse laite koodin alussa! Poista // haluamasi laitteen edestä."
#endif

// Yleiset asetukset
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT
#define SPI_FREQUENCY  40000000
#define SPI_READ_FREQUENCY  16000000

// Värit
#define TFT_BLACK   0x0000
#define TFT_NAVY    0x000F
#define TFT_DARKGREEN 0x03E0
#define TFT_DARKCYAN 0x03EF
#define TFT_MAROON  0x7800
#define TFT_PURPLE  0x780F
#define TFT_OLIVE   0x7BE0
#define TFT_LIGHTGREY 0xC618
#define TFT_DARKGREY 0x7BEF
#define TFT_BLUE    0x001F
#define TFT_GREEN   0x07E0
#define TFT_CYAN    0x07FF
#define TFT_RED     0xF800
#define TFT_MAGENTA 0xF81F
#define TFT_YELLOW  0xFFE0
#define TFT_WHITE   0xFFFF
#define TFT_ORANGE  0xFD20
#define TFT_GREENYELLOW 0xAFE5
#define TFT_PINK    0xF81F

// Nyt vasta ladataan TFT_eSPI kirjasto
#include <TFT_eSPI.h>

// Luo näyttöolio
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Käynnistetään näyttö...");
    Serial.print("Laite: ");
    Serial.println(DEVICE_NAME);

    // Alusta näyttö
    tft.init();
    tft.setRotation(1); // Vaakatasossa

    // Tyhjennä näyttö (musta tausta)
    tft.fillScreen(TFT_BLACK);

    // Aseta tekstin väri ja koko
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);

    // Näytä teksti
    tft.setCursor(10, 10);
    tft.println("Hei!");

    tft.setCursor(10, 40);
    tft.setTextColor(TFT_GREEN);
    tft.println("ESP32 toimii!");

    // Näytä laitteen tiedot
    tft.setCursor(10, 70);
    tft.setTextColor(TFT_CYAN);
    tft.setTextSize(1);

    tft.print("Laite: ");
    tft.println(DEVICE_NAME);
    tft.print("Naytto: ");
    tft.println(DISPLAY_NAME);
    tft.print("Siru: ");
    tft.println(CHIP_NAME);

    Serial.println("Näyttö valmis!");
}

void loop() {
    static unsigned long lastUpdate = 0;

    if (millis() - lastUpdate > 1000) {
        lastUpdate = millis();

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
