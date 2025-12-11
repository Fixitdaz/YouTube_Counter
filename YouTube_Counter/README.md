# YouTube Subscriber Counter (NerdMiner / CYD)

A real-time YouTube subscriber counter built for the **ESP32-2432S028R** (commonly known as the NerdMiner V2 or Cheap Yellow Display).

**Author:** fixitdaztv  
**Date:** 2025-12-10

![Project Screenshot](https://github.com/Fixitdaz/YouTube_Counter/blob/main/YouTube_Counter/YouTube_Counter.png)

## Hardware
* **Board:** ESP32-2432S028R (CYD)
* **Display:** 2.8" ILI9341 Touchscreen

## Software Requirements
* Arduino IDE
* **Libraries:**
    * `TFT_eSPI` by Bodmer
    * `ArduinoJson` by Benoit Blanchon

## Installation

1.  **Library Configuration (Crucial):**
    * Locate your Arduino libraries folder: `Documents/Arduino/libraries/TFT_eSPI/`.
    * Open `User_Setup.h`.
    * Replace its entire contents with the code found in `TFT_eSPI_Setup.h` from this repository.

2.  **Credentials:**
    * Open `YouTube_Counter.ino`.
    * Enter your `WiFi SSID`, `Password`, `Google API Key`, and `Channel ID` at the top of the file.

3.  **Upload:**
    * Select Board: **ESP32 Dev Module**.
    * Partition Scheme: **Huge APP (3MB No OTA/1MB SPIFFS)**.

    * Upload speed: **921600**.
