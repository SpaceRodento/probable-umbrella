// Setup for LILYGO T-Display-S3
// ESP32-S3 with 1.9" ST7789V 170x320 LCD

#define USER_SETUP_INFO "T-Display-S3"

// Näytön ajuri
#define ST7789_DRIVER

// Näytön resoluutio
#define TFT_WIDTH  170
#define TFT_HEIGHT 320

// ESP32-S3 pinnit T-Display-S3:lle
#define TFT_MOSI 35  // SDA
#define TFT_SCLK 36  // SCL
#define TFT_CS   37  // CS
#define TFT_DC   34  // DC
#define TFT_RST  38  // RST
#define TFT_BL   33  // Backlight

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

// SPI-nopeus
#define SPI_FREQUENCY  40000000
#define SPI_READ_FREQUENCY  16000000
