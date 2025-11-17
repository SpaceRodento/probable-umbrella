// Setup for LILYGO T-Display
// ESP32 with 1.14" ST7789V 135x240 LCD

#define USER_SETUP_INFO "T-Display"

// Näytön ajuri
#define ST7789_DRIVER

// Näytön resoluutio
#define TFT_WIDTH  135
#define TFT_HEIGHT 240

// ESP32 pinnit T-Display:lle
#define TFT_MOSI 19  // SDA
#define TFT_SCLK 18  // SCL
#define TFT_CS   5   // CS
#define TFT_DC   16  // DC
#define TFT_RST  23  // RST
#define TFT_BL   4   // Backlight

// ST7789 IPS specific settings
#define TFT_RGB_ORDER TFT_BGR  // IPS näytöt käyttävät BGR!
#define TFT_INVERSION_OFF      // IPS ei tarvitse inversiota
#define CGRAM_OFFSET           // IPS muisti-offset
#define COLSTART 52            // IPS X-offset
#define ROWSTART 40            // IPS Y-offset

// Värit (RGB565)
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

// Fontit
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SMOOTH_FONT

// SPI-nopeus (alennettu stabiilisuuden vuoksi)
#define SPI_FREQUENCY  10000000
#define SPI_READ_FREQUENCY  10000000
