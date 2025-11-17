#include <Arduino.h>
#include <WiFi.h>

// Lataa TFT-näytön konfiguraatio ennen TFT_eSPI.h:ta
#include "User_Setup_Select.h"
#include <TFT_eSPI.h>

// Määritä painikkeet, backlight ja ADC-pinnit eri laitteille
#ifdef TDISPLAY
    #define BUTTON_LEFT  0
    #define BUTTON_RIGHT 35
    #define ADC_PIN 34
    #define ADC_EN  14
    #define BACKLIGHT_PIN 4
#elif defined(TDISPLAY_S3)
    #define BUTTON_LEFT  0
    #define BUTTON_RIGHT 14
    #define ADC_PIN 4
    #define ADC_EN  15
    #define BACKLIGHT_PIN 33
#elif defined(TPICOC3)
    #define BUTTON_LEFT  0
    #define BUTTON_RIGHT 21
    #define ADC_PIN 3
    #define ADC_EN  10
    #define BACKLIGHT_PIN 2
#endif

// Luo näyttöolio
TFT_eSPI tft = TFT_eSPI();

// Nappi-tilat
unsigned long leftButtonPressTime = 0;
unsigned long rightButtonPressTime = 0;
bool leftButtonPressed = false;
bool rightButtonPressed = false;
bool leftButtonHandled = false;
bool rightButtonHandled = false;

#define LONG_PRESS_TIME 2000  // 2 sekuntia pitkälle painallukselle
#define DEBOUNCE_TIME 50      // 50ms debounce

// Funktioprotot
void showWelcome();
void scanWiFi();
void showVoltage();
void goToSleep();
float readBatteryVoltage();

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Käynnistetään T-Display Advanced Demo...");

    // Alusta painikkeet
    pinMode(BUTTON_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);

    // Alusta ADC enable (jos on)
    #ifdef ADC_EN
    pinMode(ADC_EN, OUTPUT);
    digitalWrite(ADC_EN, HIGH);  // Ota ADC käyttöön
    #endif

    // Alusta näytön backlight (TÄRKEÄ!)
    pinMode(BACKLIGHT_PIN, OUTPUT);
    digitalWrite(BACKLIGHT_PIN, HIGH);  // Kytke backlight päälle

    Serial.println("Alustetaan näyttö...");

    // Alusta näyttö
    tft.init();
    tft.setRotation(1); // Vaakatasossa

    Serial.println("Täytetään näyttö mustalla...");
    tft.fillScreen(TFT_BLACK);

    delay(100);  // Pieni viive varmistukseksi

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

#ifdef TDISPLAY
    tft.println("T-Display (ESP32)");
#elif defined(TDISPLAY_S3)
    tft.println("T-Display-S3");
#elif defined(TPICOC3)
    tft.println("T-PicoC3");
#endif

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

    tft.fillRect(0, 35, 240, 100, TFT_BLACK);
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
            if (y > 120) break;  // Tilan loppuessa keskeytä

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
    tft.setCursor(10, 120);
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
    int barWidth = 200 * percentage / 100;
    tft.fillRect(10, 110, 220, 20, TFT_DARKGREY);
    tft.fillRect(10, 110, barWidth, 20, (percentage > 50) ? TFT_GREEN : (percentage > 20) ? TFT_YELLOW : TFT_RED);

    // Näytä ohje
    tft.setCursor(10, 120);
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
    digitalWrite(BACKLIGHT_PIN, LOW);

    // Aseta herätyspinni (vasen nappi)
    esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_LEFT, LOW);

    // Mene deep sleep -tilaan
    esp_deep_sleep_start();
}
