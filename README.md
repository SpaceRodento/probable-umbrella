# ESP32 Display Setup

Perusprojekti LILYGO T-Display -laitteille. Näyttää tekstiä LCD-ruudulla.

## Tuetut laitteet

### T-Display-S3
- **Siru**: ESP32-S3
- **Näyttö**: 1.9" ST7789V (170x320)
- **Ympäristö**: `t-display-s3`

### T-PicoC3
- **Siru**: ESP32-C3
- **Näyttö**: 1.14" ST7735S (135x240)
- **Ympäristö**: `t-picoc3`

## Käyttöönotto

### 1. Asenna PlatformIO

Jos et ole vielä asentanut PlatformIO:ta:
```bash
# VSCode extension tai
pip install platformio
```

### 2. Valitse laitteesi

Tarkista laitteesi malli (S3 vai C3) ja käytä vastaavaa komentoa.

### 3. Käännä projekti

**T-Display-S3:lle:**
```bash
pio run -e t-display-s3
```

**T-PicoC3:lle:**
```bash
pio run -e t-picoc3
```

### 4. Lataa laitteelle

**T-Display-S3:lle:**
```bash
pio run -e t-display-s3 --target upload
```

**T-PicoC3:lle:**
```bash
pio run -e t-picoc3 --target upload
```

### 5. Avaa Serial Monitor

```bash
pio device monitor
```

## Mitä ohjelma tekee?

Ohjelma:
1. Alustaa LCD-näytön
2. Näyttää tervehdystekstin
3. Näyttää laitteen tiedot
4. Päivittää laskurin joka sekunti

## Näytön pinnit

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

1. **Tarkista laitevalinta**: Varmista, että käytät oikeaa ympäristöä (`t-display-s3` tai `t-picoc3`)
2. **Tarkista USB-liitäntä**: Laite pitää olla kytketty tietokoneeseen
3. **Serial Monitor**: Tarkista Serial Monitorista, näkyykö käynnistysviestit
4. **Pinnikytkennät**: Pinnit on määritetty automaattisesti, mutta tarkista että ne vastaavat laitettasi

### Käännösvirheet

Jos saat virheen kirjastoista:
```bash
pio pkg install
```

### En tiedä kumpi laite minulla on

Tarkista:
- **Näytön koko**: Mittaa vinoittain (1.14" vs 1.9")
- **Laitekoko**: T-Display-S3 on suurempi ja ohuempi, T-PicoC3 on pienempi ja leveämpi
- **Sirun merkintä**: Tarkista laitteen pohjasta "ESP32-S3" tai "ESP32-C3"
- **Kokeile molempia**: Lataa ensin `t-display-s3`, jos ei toimi, kokeile `t-picoc3`

## Oma koodi

Muokkaa `src/main.cpp` -tiedostoa omia tarpeita varten.

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

## Lisätietoja

- [TFT_eSPI dokumentaatio](https://github.com/Bodmer/TFT_eSPI)
- [PlatformIO dokumentaatio](https://docs.platformio.org/)
- [LILYGO T-Display GitHub](https://github.com/Xinyuan-LilyGO)

## Lisenssi

MIT License
