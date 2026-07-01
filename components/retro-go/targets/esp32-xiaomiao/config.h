// Target definition
#define RG_TARGET_NAME             "ESP32-XIAOMIAO"

// Storage
#define RG_STORAGE_ROOT             "/sd"
#define RG_STORAGE_SDSPI_HOST       SPI2_HOST
#define RG_STORAGE_SDSPI_SPEED      SDMMC_FREQ_DEFAULT

// Audio - Piezo buzzer on GPIO14 (PWM/LEDC)
#define RG_AUDIO_USE_BUZZER_PIN     14
#define RG_AUDIO_USE_INT_DAC        0
#define RG_AUDIO_USE_EXT_DAC        0

// Video - ST7735 128x160 on SPI2 (shared with SD card)
#define RG_SCREEN_DRIVER            0
#define RG_SCREEN_HOST              SPI2_HOST
#define RG_SCREEN_SPEED             SPI_MASTER_FREQ_40M
#define RG_SCREEN_BACKLIGHT         0
#define RG_SCREEN_WIDTH             160
#define RG_SCREEN_HEIGHT            128
#define RG_SCREEN_ROTATE            3
#define RG_SCREEN_VISIBLE_AREA      {0, 0, 0, 0}
#define RG_SCREEN_SAFE_AREA         {0, 0, 0, 0}
#define RG_SCREEN_INIT()                                                                  \
    rg_usleep(145 * 1000);           /* Complete SWRESET wait (ili9341 only waits 5ms) */\
    ILI9341_CMD(0xB1, 0x01, 0x2C, 0x2D); /* FRMCTR1: Frame Rate Control */              \
    ILI9341_CMD(0xB2, 0x01, 0x2C, 0x2D); /* FRMCTR2: Full Colors Frame Rate */          \
    ILI9341_CMD(0xB3, 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D); /* FRMCTR3: Partial */     \
    rg_usleep(10);                                                                        \
    ILI9341_CMD(0xB4, 0x07);             /* INVCTR: Display Inversion Control */         \
    ILI9341_CMD(0xC0, 0xA2, 0x02, 0x84); /* PWCTR1: Power Control 1 */                  \
    ILI9341_CMD(0xC1, 0xC5);             /* PWCTR2: Power Control 2 */                  \
    ILI9341_CMD(0xC2, 0x0A, 0x00);       /* PWCTR3: Power Control 3 */                  \
    ILI9341_CMD(0xC3, 0x8A, 0x2A);       /* PWCTR4: Power Control 4 */                  \
    ILI9341_CMD(0xC4, 0x8A, 0xEE);       /* PWCTR5: Power Control 5 */                  \
    ILI9341_CMD(0xC5, 0x0E);             /* VMCTR1: VCOM Control 1 */                   \
    ILI9341_CMD(0x3A, 0x05);         /* COLMOD: 16-bit RGB565 */                         \
    rg_usleep(50);                                                                        \
    ILI9341_CMD(0x20);                   /* INVOFF: Invert off*/                  \
    ILI9341_CMD(0x36, 0x60);             /* MADCTL: MX|MV|RGB (90° CCW) */               \
    ILI9341_CMD(0xE0, 0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29,                        \
                0x2D, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10); /* GMCTRP1 */   \
    ILI9341_CMD(0xE1, 0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29,                        \
                0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10); /* GMCTRN1 */   \
    ILI9341_CMD(0x13);                   /* NORON: Normal Display On */                  \
    rg_usleep(10);

// Input - 6 GPIO buttons (active low, with pullup where possible)
// NOTE: GPIO34,35 are input-only (no pullup); external pull-up resistors required
#define RG_GAMEPAD_GPIO_MAP {\
    {RG_KEY_UP,    .num = GPIO_NUM_2,  .pullup = 1, .level = 0},\
    {RG_KEY_DOWN,  .num = GPIO_NUM_13, .pullup = 1, .level = 0},\
    {RG_KEY_LEFT,  .num = GPIO_NUM_27, .pullup = 1, .level = 0},\
    {RG_KEY_RIGHT, .num = GPIO_NUM_35, .pullup = 0, .level = 0},\
    {RG_KEY_A,     .num = GPIO_NUM_34, .pullup = 0, .level = 0},\
    {RG_KEY_B,     .num = GPIO_NUM_12, .pullup = 1, .level = 0},\
    {RG_KEY_START, .num = GPIO_NUM_33, .pullup = 1, .level = 0},\
    {RG_KEY_SELECT,.num = GPIO_NUM_32, .pullup = 1, .level = 0},\
}
#define RG_GAMEPAD_VIRT_MAP {\
    {RG_KEY_MENU,   .src = RG_KEY_A | RG_KEY_START},\
    {RG_KEY_OPTION, .src = RG_KEY_A | RG_KEY_SELECT},\
}

// Battery - not present
// #define RG_BATTERY_DRIVER           1

// Status LED - not present
// #define RG_GPIO_LED                 GPIO_NUM_XX

// I2C BUS
#define RG_GPIO_I2C_SDA             GPIO_NUM_21
#define RG_GPIO_I2C_SCL             GPIO_NUM_15

// SPI Display (ST7735)
#define RG_GPIO_LCD_MISO            GPIO_NUM_NC
#define RG_GPIO_LCD_MOSI            GPIO_NUM_23
#define RG_GPIO_LCD_CLK             GPIO_NUM_18
#define RG_GPIO_LCD_CS              GPIO_NUM_5
#define RG_GPIO_LCD_DC              GPIO_NUM_4
// RES is shared with SD MISO (GPIO19); use power-on reset instead
// #define RG_GPIO_LCD_RST             GPIO_NUM_19
#define RG_GPIO_LCD_RST             GPIO_NUM_NC

// SPI SD Card (shared bus with TFT)
#define RG_GPIO_SDSPI_MISO          GPIO_NUM_19
#define RG_GPIO_SDSPI_MOSI          GPIO_NUM_23
#define RG_GPIO_SDSPI_CLK           GPIO_NUM_18
#define RG_GPIO_SDSPI_CS            GPIO_NUM_22

// Sensors (ADC1) - ADC only, input-only pins
// Light sensor:  GPIO36 (ADC1_CH0)
// Thermistor:    GPIO39 (ADC1_CH3)

// Expansion (PH2.0 3P): GPIO33, 32, 26, 25

// Defaults
#define RG_LANG_DEFAULT                 RG_LANG_ZH
#define RG_FONT_DEFAULT                 RG_FONT_FUSION_12

// Updater
#define RG_UPDATER_ENABLE               1
#define RG_UPDATER_APPLICATION          RG_APP_FACTORY
#define RG_UPDATER_DOWNLOAD_LOCATION    RG_STORAGE_ROOT "/firmware"
