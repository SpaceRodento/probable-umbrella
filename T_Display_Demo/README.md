# T-Display Demo - Arduino IDE

Advanced demo LILYGO T-Display -laitteille Arduino IDE:ssä.

## ✨ Ominaisuudet

- **Vasen nappi**: WiFi-verkkojen skannaus
- **Oikea nappi**: Akun jännitteen näyttö
- **Oikea nappi (pitkä painallus 2s)**: Deep sleep -tila

## Asennus

### 1. Asenna Arduino IDE

Lataa ja asenna Arduino IDE: https://www.arduino.cc/en/software

### 2. Asenna ESP32 board tuki

1. Avaa Arduino IDE
2. Mene: **File → Preferences**
3. Lisää "Additional Board Manager URLs" -kenttään:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Mene: **Tools → Board → Boards Manager**
5. Etsi "esp32" ja asenna **esp32 by Espressif Systems**

### 3. Asenna TFT_eSPI kirjasto

1. Mene: **Sketch → Include Library → Manage Libraries**
2. Etsi "TFT_eSPI"
3. Asenna **TFT_eSPI by Bodmer**

### 4. Valitse oikea board

#### T-Display (alkuperäinen ESP32):
- **Tools → Board → ESP32 Arduino → ESP32 Dev Module**

#### T-Display-S3:
- **Tools → Board → ESP32 Arduino → ESP32S3 Dev Module**

#### T-PicoC3:
- **Tools → Board → ESP32 Arduino → ESP32C3 Dev Module**

### 5. Valitse laitteesi koodissa

1. Avaa `T_Display_Demo.ino` Arduino IDE:ssä
2. Etsi koodin alusta kohta "VALITSE LAITTEESI"
3. Poista `//` sen laitteen edestä joka sinulla on:

```cpp
// ====== VALITSE LAITTEESI TÄSTÄ ======
#define TDISPLAY          // ← Tämä on valittu (ei //)
// #define TDISPLAY_S3    // ← Tämä ei ole valittu (on //)
// #define TPICOC3        // ← Tämä ei ole valittu (on //)
```

### 6. Lataa koodiin

1. Kytke laite USB-kaapelilla
2. Valitse oikea portti: **Tools → Port**
3. Paina **Upload** (nuoli-nappi)

## Mitä ohjelma tekee?

### Aloitusnäyttö
- Näyttää laitteen nimen
- Näyttää ohjeet nappien käytöstä

### Vasen nappi - WiFi Scan
- Skannaa lähellä olevat WiFi-verkot
- Näyttää verkon nimen (SSID) ja signaalin vahvuuden
- Värikoodaus signaalin mukaan:
  - Vihreä: Vahva signaali (> -50 dB)
  - Keltainen: Kohtalainen signaali (-50 to -70 dB)
  - Oranssi: Heikko signaali (< -70 dB)

### Oikea nappi - Voltage Monitor
- Näyttää akun jännitteen voltteina
- Näyttää arvion akun lataustasosta prosentteina
- Värikoodaus jännitteen mukaan:
  - Vihreä: Täysi lataus (> 4.0V)
  - Keltainen: Kohtalainen (3.6V - 4.0V)
  - Punainen: Matala (< 3.6V)
- Graafinen palkki lataustason näyttämiseen

### Oikea nappi (pitkä painallus) - Deep Sleep
- Pidä oikeaa nappia pohjassa 2 sekuntia
- Laite menee deep sleep -tilaan virran säästämiseksi
- Herää painamalla vasenta nappia
- Näyttö sammuu sleep-tilassa

## Vianmääritys

### "A fatal error occurred: Failed to connect"

1. Pidä **BOOT**-nappia pohjassa laitteessa
2. Paina **Upload** Arduino IDE:ssä
3. Odota kunnes näet "Connecting..."
4. Voit nyt päästää **BOOT**-napista

### Näyttö pysyy mustana

1. Tarkista että valitsit oikean laitteen koodin alussa
2. Tarkista että valitsit oikean boardin Tools-valikosta
3. Avaa Serial Monitor: **Tools → Serial Monitor** (115200 baud)
4. Paina laitteen **RESET**-nappia

### Napit eivät toimi

1. Tarkista että painat oikeaa nappia
2. Katso Serial Monitor -viestejä napinpainalluksista
3. Jos deep sleep aktivoituu vahingossa, paina vasenta nappia herättääksesi laitteen

### WiFi scan ei näytä verkkoja

1. Varmista että olet WiFi-verkkojen läheisyydessä
2. WiFi scan voi kestää muutaman sekunnin
3. Katso Serial Monitor -viestejä lisätiedoista

### Jännitemittaus näyttää väärin

1. Jännitemittaus on karkea arvio
2. Kalibrointivakio (0.3V) voi vaatia säätöä eri laitteilla
3. Muokkaa koodissa `battery_voltage += 0.3;` kohtaa tarvittaessa

### Käännösvirhe

Jos saat virheen `#error "Valitse laite koodin alussa!"`:
- Poista `//` jonkin laitteen edestä koodin alussa

## Serial Monitor

Avaa Serial Monitor nähdäksesi debug-viestit:
1. **Tools → Serial Monitor**
2. Aseta baud rate: **115200**
3. Paina laitteen RESET-nappia

## Lisätietoja

Tuetut laitteet:
- **T-Display**: Alkuperäinen ESP32, 1.14" ST7789V näyttö
  - Vasen nappi: GPIO 0
  - Oikea nappi: GPIO 35
  - ADC: GPIO 34
- **T-Display-S3**: ESP32-S3, 1.9" ST7789V näyttö
  - Vasen nappi: GPIO 0
  - Oikea nappi: GPIO 14
  - ADC: GPIO 4
- **T-PicoC3**: ESP32-C3, 1.14" ST7735S näyttö
  - Vasen nappi: GPIO 0
  - Oikea nappi: GPIO 21
  - ADC: GPIO 3

## Teknisiä yksityiskohtia

- **Debounce**: 50ms napinpainalluksille
- **Long press**: 2000ms (2 sekuntia)
- **WiFi**: Station mode, passive scan
- **ADC**: 12-bit resoluutio, 2:1 jännitteenjakaja
- **Deep sleep**: EXT0 wake-up vasemmalla napilla
