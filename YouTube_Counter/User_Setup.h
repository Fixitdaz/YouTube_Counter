/*
 * File:    User_Setup.h
 * Author:  fixitdaztv
 * Date:    2025-12-11
 * Purpose: Configuration map for the ESP32-2432S028R (NerdMiner/CYD)
 * Note:    Replace the contents of Documents/Arduino/libraries/TFT_eSPI/User_Setup.h
 */

#define USER_SETUP_INFO "User_Setup"

// ----------------DRIVER----------------
#define ILI9341_2_DRIVER    // Use the ILI9341 Driver (Standard for this screen)

// ----------------RESOLUTION----------------
#define TFT_WIDTH  240      // Screen Width in pixels
#define TFT_HEIGHT 320      // Screen Height in pixels

// ----------------PIN MAPPING (CYD Board)----------------
#define TFT_MISO 12         // Master In Slave Out
#define TFT_MOSI 13         // Master Out Slave In (Data to screen)
#define TFT_SCLK 14         // Serial Clock
#define TFT_CS   15         // Chip Select
#define TFT_DC    2         // Data/Command (Crucial Pin)
#define TFT_RST  -1         // Reset (Connected to Global Reset)
#define TFT_BL   21         // Backlight Control Pin

#define TFT_BACKLIGHT_ON HIGH // Signal to turn backlight ON

// ----------------FONTS----------------
// Load fonts into memory
#define LOAD_GLCD   
#define LOAD_FONT2  
#define LOAD_FONT4  
#define LOAD_FONT6  
#define LOAD_FONT7  
#define LOAD_FONT8  

// ----------------SPEED SETTINGS----------------
#define SPI_FREQUENCY  55000000 // High speed SPI (55MHz) for smooth updates
#define SPI_READ_FREQUENCY 20000000
#define SPI_TOUCH_FREQUENCY 2500000