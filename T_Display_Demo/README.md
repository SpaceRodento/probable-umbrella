# T-Display Demo - Arduino IDE

Yksinkertainen esimerkki LILYGO T-Display -laitteille Arduino IDE:ssä.

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

- Näyttää "Hei!" ja "ESP32 toimii!" tekstit
- Näyttää laitteen tiedot
- Päivittää laskurin joka sekunti

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
- **T-Display-S3**: ESP32-S3, 1.9" ST7789V näyttö
- **T-PicoC3**: ESP32-C3, 1.14" ST7735S näyttö
