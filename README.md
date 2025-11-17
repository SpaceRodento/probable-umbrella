# ESP32 Display Setup

Perusprojekti LILYGO T-Display -laitteille. Näyttää tekstiä LCD-ruudulla.

## 🚀 Pika-aloitus

### Arduino IDE käyttäjät
📁 **Avaa: [`T_Display_Demo/T_Display_Demo.ino`](T_Display_Demo/)**
📖 [Arduino IDE ohjeet](T_Display_Demo/README.md)

### PlatformIO käyttäjät
📖 Jatka lukemalla alla olevat ohjeet

---

## Tuetut laitteet

### T-Display (alkuperäinen) ⭐
- **Siru**: ESP32 (alkuperäinen)
- **Näyttö**: 1.14" ST7789V (135x240)
- **USB-sarja**: CH9102F
- **Ympäristö**: `t-display`

### T-Display-S3
- **Siru**: ESP32-S3
- **Näyttö**: 1.9" ST7789V (170x320)
- **Ympäristö**: `t-display-s3`

### T-PicoC3
- **Siru**: ESP32-C3
- **Näyttö**: 1.14" ST7735S (135x240)
- **Ympäristö**: `t-picoc3`

## Käyttöönotto (PlatformIO)

**Käytätkö Arduino IDE:tä?** → [Klikkaa tästä](T_Display_Demo/README.md)

### 1. Asenna PlatformIO

Jos et ole vielä asentanut PlatformIO:ta:
```bash
# VSCode extension tai
pip install platformio
```

### 2. Valitse laitteesi

Tarkista laitteesi malli ja käytä vastaavaa komentoa.

### 3. Käännä ja lataa laitteelle

**T-Display (alkuperäinen ESP32):**
```bash
pio run -e t-display --target upload
```

**T-Display-S3:**
```bash
pio run -e t-display-s3 --target upload
```

**T-PicoC3:**
```bash
pio run -e t-picoc3 --target upload
```

### 4. Avaa Serial Monitor (valinnainen)

```bash
pio device monitor
```

Tai yhdistä lataus ja monitorointi:
```bash
pio run -e t-display --target upload --target monitor
```

## Mitä ohjelma tekee?

Ohjelma:
1. Alustaa LCD-näytön
2. Näyttää tervehdystekstin
3. Näyttää laitteen tiedot
4. Päivittää laskurin joka sekunti

## Näytön pinnit

### T-Display (alkuperäinen)
- MOSI (SDA): GPIO 19
- SCLK (SCL): GPIO 18
- CS: GPIO 5
- DC: GPIO 16
- RST: GPIO 23
- BL (Backlight): GPIO 4

### T-Display-S3
- MOSI (SDA): GPIO 35
- SCLK (SCL): GPIO 36
- CS: GPIO 37
- DC: GPIO 34
- RST: GPIO 38
- BL (Backlight): GPIO 33

### T-PicoC3
- MOSI (SDA): GPIO 7
- SCLK (SCL): GPIO 6
- CS: GPIO 10
- DC: GPIO 8
- RST: GPIO 9
- BL (Backlight): GPIO 2

## Vianmääritys

### Näyttö ei näytä mitään

1. **Tarkista laitevalinta**: Varmista, että käytät oikeaa ympäristöä (`t-display`, `t-display-s3` tai `t-picoc3`)
2. **Tarkista USB-liitäntä**: Laite pitää olla kytketty tietokoneeseen
3. **Serial Monitor**: Tarkista Serial Monitorista, näkyykö käynnistysviestit
4. **Pinnikytkennät**: Pinnit on määritetty automaattisesti, mutta tarkista että ne vastaavat laitettasi

### Käännösvirheet

Jos saat virheen kirjastoista:
```bash
pio pkg install
```

### En tiedä kumpi laite minulla on

Tunnistusohje:
- **1.14" näyttö**:
  - Alkuperäinen T-Display (ESP32) - yleisin malli, CH9102F USB-sarja
  - T-PicoC3 (ESP32-C3) - Raspberry Pi Pico -muotoinen
- **1.9" näyttö**: T-Display-S3 (ESP32-S3) - suurempi ja ohuempi

**Jos epävarma**, kokeile järjestyksessä:
1. `pio run -e t-display --target upload` (yleisin)
2. Jos ei toimi: `pio run -e t-display-s3 --target upload`
3. Jos ei toimi: `pio run -e t-picoc3 --target upload`

## Oma koodi

**PlatformIO**: Muokkaa `src/main.cpp` -tiedostoa omia tarpeita varten.
**Arduino IDE**: Muokkaa `T_Display_Demo/T_Display_Demo.ino` -tiedostoa.

### Esimerkkejä

**Muuta tekstiä:**
```cpp
tft.setCursor(10, 10);
tft.setTextColor(TFT_GREEN);
tft.setTextSize(3);
tft.println("Oma tekstini!");
```

**Piirrä suorakulmio:**
```cpp
tft.fillRect(x, y, leveys, korkeus, TFT_BLUE);
```

**Piirrä ympyrä:**
```cpp
tft.fillCircle(x, y, sade, TFT_RED);
```

## Projektin rakenne

```
├── T_Display_Demo/           # Arduino IDE projekti
│   ├── T_Display_Demo.ino   # Pääohjelma (avaa tämä Arduino IDE:ssä)
│   └── README.md            # Arduino IDE ohjeet
│
├── src/                      # PlatformIO projekti
│   └── main.cpp             # Pääohjelma (PlatformIO)
│
├── include/                  # Näyttökonfiguraatiot
│   ├── TDisplay_Setup.h
│   ├── TDisplay_S3_Setup.h
│   └── TPicoC3_Setup.h
│
└── platformio.ini           # PlatformIO konfiguraatio
```

## Lisätietoja

- [TFT_eSPI dokumentaatio](https://github.com/Bodmer/TFT_eSPI)
- [PlatformIO dokumentaatio](https://docs.platformio.org/)
- [Arduino IDE dokumentaatio](https://www.arduino.cc/)
- [LILYGO T-Display GitHub](https://github.com/Xinyuan-LilyGO)

## Lisenssi

MIT License
