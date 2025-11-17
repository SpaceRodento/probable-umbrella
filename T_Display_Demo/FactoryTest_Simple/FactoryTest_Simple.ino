/*
 * LILYGO T-Display FactoryTest (Yksinkertaistettu)
 * Perustuuu LILYGO:n viralliseen esimerkkiin
 */

#include <TFT_eSPI.h>
#include <SPI.h>
#include "WiFi.h"

// Pinnit (LILYGO virallinen)
#define TFT_BL 4
#define ADC_EN 14
#define ADC_PIN 34
#define BUTTON_1 35
#define BUTTON_2 0

// TFT_eSPI tarvitsee nämä määritykset
#define USER_SETUP_LOADED 1
#define ST7789_DRIVER
#define TFT_WIDTH  135
#define TFT_HEIGHT 240
#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 23
#define TFT_SDA_READ
#define CGRAM_OFFSET
#define SPI_FREQUENCY  40000000
#define SPI_READ_FREQUENCY  6000000

TFT_eSPI tft = TFT_eSPI(135, 240);

int vref = 1100;
bool btnClick = false;
unsigned long lastPress1 = 0;
unsigned long lastPress2 = 0;

void wifi_scan();
void showVoltage();

void setup() {
    Serial.begin(115200);
    Serial.println("LILYGO T-Display Factory Test (Simplified)");

    // ADC enable
    pinMode(ADC_EN, OUTPUT);
    digitalWrite(ADC_EN, HIGH);

    // Buttons
    pinMode(BUTTON_1, INPUT);
    pinMode(BUTTON_2, INPUT);

    // Backlight
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    Serial.println("Initializing display...");

    // Init display
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    tft.setTextColor(TFT_GREEN);
    tft.setTextDatum(MC_DATUM);

    Serial.println("Testing colors...");

    // Color test
    tft.fillScreen(TFT_RED);
    delay(1000);
    tft.fillScreen(TFT_GREEN);
    delay(1000);
    tft.fillScreen(TFT_BLUE);
    delay(1000);

    // Show menu
    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("LILYGO T-Display", tft.width() / 2, 20);
    tft.drawString("LeftButton:", tft.width() / 2, 50);
    tft.drawString("[WiFi Scan]", tft.width() / 2, 65);
    tft.drawString("RightButton:", tft.width() / 2, 85);
    tft.drawString("[Voltage Monitor]", tft.width() / 2, 100);

    Serial.println("Ready! Press buttons to test.");
}

void loop() {
    // Simple button handling
    int btn1State = digitalRead(BUTTON_1);
    int btn2State = digitalRead(BUTTON_2);

    // Button 1 (GPIO 35) - Voltage
    if (btn1State == LOW && millis() - lastPress1 > 500) {
        lastPress1 = millis();
        Serial.println("Button 1 pressed - Voltage");
        btnClick = true;
    }

    // Button 2 (GPIO 0) - WiFi Scan
    if (btn2State == LOW && millis() - lastPress2 > 500) {
        lastPress2 = millis();
        Serial.println("Button 2 pressed - WiFi Scan");
        btnClick = false;
        wifi_scan();
    }

    if (btnClick) {
        showVoltage();
    }

    delay(10);
}

void showVoltage() {
    static uint64_t timeStamp = 0;
    if (millis() - timeStamp > 1000) {
        timeStamp = millis();
        uint16_t v = analogRead(ADC_PIN);
        float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
        String voltage = "Voltage: " + String(battery_voltage) + "V";

        Serial.println(voltage);

        tft.fillScreen(TFT_BLACK);
        tft.setTextDatum(MC_DATUM);
        tft.setTextColor(TFT_GREEN);
        tft.drawString(voltage, tft.width() / 2, tft.height() / 2);
    }
}

void wifi_scan() {
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(1);

    tft.drawString("Scanning WiFi...", tft.width() / 2, tft.height() / 2);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    int16_t n = WiFi.scanNetworks();

    Serial.printf("Found %d networks\n", n);

    tft.fillScreen(TFT_BLACK);
    if (n == 0) {
        tft.drawString("No networks found", tft.width() / 2, tft.height() / 2);
    } else {
        tft.setTextDatum(TL_DATUM);
        tft.setCursor(0, 0);
        tft.setTextColor(TFT_WHITE);

        for (int i = 0; i < n && i < 10; ++i) {
            String line = String(i + 1) + ":" + WiFi.SSID(i) + "(" + String(WiFi.RSSI(i)) + ")";
            tft.println(line);
            Serial.println(line);
        }
    }
}
