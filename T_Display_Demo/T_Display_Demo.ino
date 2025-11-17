/*
 * LILYGO T-Display - Advanced Demo
 *
 * Ominaisuudet:
 * - Vasen nappi: WiFi-verkkojen skannaus
 * - Oikea nappi: Akun jännitteen näyttö
 * - Oikea nappi (pitkä painallus): Deep sleep
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

// Lataa oikea näyttökonfiguraatio ja pinnit
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
    // Painikkeet
    #define BUTTON_LEFT  0
    #define BUTTON_RIGHT 35
    // ADC akun mittaukseen
    #define ADC_PIN 34
    #define ADC_EN  14  // ADC enable pin

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
    // Painikkeet
    #define BUTTON_LEFT  0
    #define BUTTON_RIGHT 14
    // ADC akun mittaukseen
    #define ADC_PIN 4
    #define ADC_EN  15

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
    // Painikkeet
    #define BUTTON_LEFT  0
    #define BUTTON_RIGHT 21
    // ADC akun mittaukseen
    #define ADC_PIN 3
    #define ADC_EN  10

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

// Kirjastot
#include <TFT_eSPI.h>
#include <WiFi.h>

// Luo näyttöolio
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);

// Nappi-tilat
unsigned long leftButtonPressTime = 0;
unsigned long rightButtonPressTime = 0;
bool leftButtonPressed = false;
bool rightButtonPressed = false;
bool leftButtonHandled = false;
bool rightButtonHandled = false;

#define LONG_PRESS_TIME 2000  // 2 sekuntia pitkälle painallukselle
#define DEBOUNCE_TIME 50      // 50ms debounce

// Funktiot
void showWelcome();
void scanWiFi();
void showVoltage();
void goToSleep();
float readBatteryVoltage();

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Käynnistetään T-Display Advanced Demo...");
    Serial.print("Laite: ");
    Serial.println(DEVICE_NAME);

    // Alusta painikkeet
    pinMode(BUTTON_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);

    // Alusta ADC enable (jos on)
    #ifdef ADC_EN
    pinMode(ADC_EN, OUTPUT);
    digitalWrite(ADC_EN, HIGH);  // Ota ADC käyttöön
    #endif

    // Alusta näyttö
    tft.init();
    tft.setRotation(1); // Vaakatasossa
    tft.fillScreen(TFT_BLACK);

    // Näytä aloitusnäyttö
    showWelcome();
}

void loop() {
    // Lue painikkeiden tila (aktiivinen LOW)
    bool leftState = digitalRead(BUTTON_LEFT) == LOW;
    bool rightState = digitalRead(BUTTON_RIGHT) == LOW;

    // ===== VASEN NAPPI =====
    if (leftState && !leftButtonPressed) {
        // Nappia juuri painettu
        leftButtonPressed = true;
        leftButtonPressTime = millis();
        leftButtonHandled = false;
    }
    else if (!leftState && leftButtonPressed) {
        // Nappi vapautettu
        if (!leftButtonHandled && (millis() - leftButtonPressTime > DEBOUNCE_TIME)) {
            // Lyhyt painallus - WiFi scan
            Serial.println("Vasen nappi: WiFi scan");
            scanWiFi();
        }
        leftButtonPressed = false;
    }

    // ===== OIKEA NAPPI =====
    if (rightState && !rightButtonPressed) {
        // Nappia juuri painettu
        rightButtonPressed = true;
        rightButtonPressTime = millis();
        rightButtonHandled = false;
    }
    else if (rightState && rightButtonPressed && !rightButtonHandled) {
        // Nappi yhä pohjassa - tarkista pitkä painallus
        if (millis() - rightButtonPressTime > LONG_PRESS_TIME) {
            Serial.println("Oikea nappi (pitkä): Deep sleep");
            rightButtonHandled = true;
            goToSleep();
        }
    }
    else if (!rightState && rightButtonPressed) {
        // Nappi vapautettu
        if (!rightButtonHandled && (millis() - rightButtonPressTime > DEBOUNCE_TIME)) {
            // Lyhyt painallus - Voltage monitor
            Serial.println("Oikea nappi: Voltage monitor");
            showVoltage();
        }
        rightButtonPressed = false;
    }

    delay(10);  // Pieni viive
}

void showWelcome() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);

    tft.setCursor(10, 10);
    tft.println("T-Display");

    tft.setCursor(10, 35);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(1);
    tft.println(DEVICE_NAME);

    tft.setCursor(10, 60);
    tft.setTextColor(TFT_CYAN);
    tft.println("Napit:");

    tft.setCursor(10, 75);
    tft.setTextColor(TFT_YELLOW);
    tft.println("VASEN:  WiFi scan");

    tft.setCursor(10, 90);
    tft.println("OIKEA:  Voltage");

    tft.setCursor(10, 105);
    tft.setTextColor(TFT_ORANGE);
    tft.println("OIKEA+: Sleep");

    Serial.println("Näyttö valmis!");
}

void scanWiFi() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println("WiFi Scan");

    tft.setTextSize(1);
    tft.setCursor(10, 35);
    tft.setTextColor(TFT_WHITE);
    tft.println("Skannataan...");

    Serial.println("WiFi scan aloitetaan...");

    // Skannaa WiFi-verkot
    int n = WiFi.scanNetworks();

    tft.fillRect(0, 35, TFT_HEIGHT, TFT_WIDTH - 35, TFT_BLACK);
    tft.setCursor(10, 35);

    if (n == 0) {
        tft.setTextColor(TFT_RED);
        tft.println("Ei verkkoja");
        Serial.println("Ei verkkoja löytynyt");
    } else {
        tft.setTextColor(TFT_GREEN);
        tft.print("Loytyi: ");
        tft.println(n);
        Serial.print("Löytyi ");
        Serial.print(n);
        Serial.println(" verkkoa");

        int y = 50;
        int maxNetworks = 8;  // Rajoita näytettävien verkkojen määrää

        for (int i = 0; i < n && i < maxNetworks; ++i) {
            if (y > TFT_WIDTH - 20) break;  // Tilan loppuessa keskeytä

            tft.setCursor(10, y);

            // Väri signaalin mukaan
            if (WiFi.RSSI(i) > -50) {
                tft.setTextColor(TFT_GREEN);
            } else if (WiFi.RSSI(i) > -70) {
                tft.setTextColor(TFT_YELLOW);
            } else {
                tft.setTextColor(TFT_ORANGE);
            }

            // Näytä SSID ja signaali
            String ssid = WiFi.SSID(i);
            if (ssid.length() > 18) {
                ssid = ssid.substring(0, 18) + "..";
            }
            tft.print(ssid);
            tft.print(" ");
            tft.print(WiFi.RSSI(i));
            tft.println("dB");

            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.println(" dB)");

            y += 12;
        }
    }

    // Näytä ohje
    tft.setCursor(10, TFT_WIDTH - 15);
    tft.setTextColor(TFT_DARKGREY);
    tft.println("Paina nappia...");
}

void showVoltage() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println("Voltage");

    float voltage = readBatteryVoltage();

    tft.setCursor(10, 45);
    tft.setTextSize(3);

    // Väri jännitteen mukaan
    if (voltage > 4.0) {
        tft.setTextColor(TFT_GREEN);
    } else if (voltage > 3.6) {
        tft.setTextColor(TFT_YELLOW);
    } else {
        tft.setTextColor(TFT_RED);
    }

    tft.print(voltage, 2);
    tft.println(" V");

    // Näytä prosenttiosuus (karkeasti)
    tft.setTextSize(2);
    int percentage = map(constrain((int)(voltage * 100), 330, 420), 330, 420, 0, 100);
    tft.setCursor(10, 80);
    tft.print("~");
    tft.print(percentage);
    tft.println(" %");

    Serial.print("Akun jännite: ");
    Serial.print(voltage);
    Serial.print(" V (");
    Serial.print(percentage);
    Serial.println(" %)");

    // Näytä palkki
    int barWidth = (TFT_HEIGHT - 40) * percentage / 100;
    tft.fillRect(10, 110, TFT_HEIGHT - 20, 20, TFT_DARKGREY);
    tft.fillRect(10, 110, barWidth, 20, (percentage > 50) ? TFT_GREEN : (percentage > 20) ? TFT_YELLOW : TFT_RED);

    // Näytä ohje
    tft.setCursor(10, TFT_WIDTH - 15);
    tft.setTextSize(1);
    tft.setTextColor(TFT_DARKGREY);
    tft.println("Paina nappia...");
}

float readBatteryVoltage() {
    // Lue ADC-arvo
    uint16_t v = analogRead(ADC_PIN);

    // Muunna jännitteeksi (ADC 12-bit, 0-4095 vastaa 0-3.3V)
    // T-Display:ssä on jännitteenjakaja (1:2), joten kerrotaan 2:lla
    float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3;

    // Lisää kalibraatio jos tarpeen (vaihtelee laitteittain)
    battery_voltage += 0.3;  // Kalibrointivakio

    return battery_voltage;
}

void goToSleep() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_ORANGE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, 50);
    tft.println("Going to");
    tft.setCursor(10, 70);
    tft.println("Sleep...");

    Serial.println("Siirrytään deep sleep -tilaan");
    Serial.println("Herää painamalla BUTTON_LEFT (GPIO 0)");

    delay(2000);

    // Sammuta näyttö
    digitalWrite(TFT_BL, LOW);

    // Aseta herätyspinni (vasen nappi)
    esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_LEFT, LOW);

    // Mene deep sleep -tilaan
    esp_deep_sleep_start();
}
