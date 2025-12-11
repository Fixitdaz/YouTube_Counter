/*
 * Project: YouTube Subscriber Counter (VEEB Style)
 * Author:  fixitdaztv
 * Date:    2025-12-11
 * Board:   ESP32-2432S028R (NerdMiner V2 / CYD)
 * Purpose: Connects to YouTube API, fetches subs, formats to "19.7K", displays on TFT.
 */

// ----------------LIBRARIES----------------
#include <WiFi.h>             // Allows the ESP32 to connect to WiFi networks
#include <WiFiClientSecure.h> // Required for HTTPS (Secure) connections to Google
#include <HTTPClient.h>       // Simplified web browser for the ESP32
#include <ArduinoJson.h>      // Decodes the text data sent back by YouTube
#include <TFT_eSPI.h>         // High-speed graphics library for the screen
#include "graphics.h"         // Our custom file that draws the YouTube Logo

// ----------------USER SETTINGS----------------
// EDIT THIS SECTION ONLY
const char* ssid = "YOUR_WIFI_SSID";         // Your WiFi Name (Case Sensitive!)
const char* password = "YOUR_WIFI_PASSWORD"; // Your WiFi Password
const char* apiKey = "YOUR_GOOGLE_API_KEY";  // Key from Google Cloud Console
const char* channelId = "YOUR_CHANNEL_ID";   // Channel ID (Starts with "UC")
// ---------------------------------------------

// Initialize the display object
TFT_eSPI tft = TFT_eSPI();

// ----------------THEME COLORS----------------
#define BG_COLOR TFT_BLACK   // Main background color
#define TEXT_COLOR TFT_WHITE // Main text color
#define SUB_COLOR 0x9CD3     // Light gray color for the word "subscribers"

// ----------------TIMERS----------------
unsigned long lastTime = 0;       // Tracks the last time we updated
unsigned long timerDelay = 60000; // Time between updates (60,000ms = 60 seconds)

// Store the old count so we only refresh screen if number changes
String oldFormattedCount = "";

// ----------------SETUP (Runs Once)----------------
void setup() {
  Serial.begin(115200); // Start serial communication for debugging

  // 1. Initialize Screen Hardware
  tft.init();
  tft.setRotation(1);       // Landscape orientation (USB port to the right)
  tft.fillScreen(BG_COLOR); // Wipe screen black
  
  // 2. Turn on Backlight 
  // Pin 21 is the standard backlight pin for CYD boards
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);

  // 3. Draw Loading Screen
  tft.setTextColor(TEXT_COLOR, BG_COLOR);
  tft.setTextDatum(MC_DATUM); // Align text to Middle Center
  tft.drawString("Fixitdaz TV", 160, 120, 4); // Draw Branding
  tft.drawString("Booting...", 160, 150, 2);  // Draw Status

  // 4. Connect to WiFi
  WiFi.begin(ssid, password);
  
  // Loop until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);         // Wait half a second
    Serial.print(".");  // Print a dot to the computer logs
  }

  // 5. Run the first update immediately
  updateScreen();
}

// ----------------LOOP (Runs Forever)----------------
void loop() {
  // Check if 60 seconds have passed since last update
  if ((millis() - lastTime) > timerDelay) {
    updateScreen();
  }
}

// ----------------HELPER: FORMAT NUMBERS----------------
// Converts raw numbers like "19700" into "19.7K"
String formatMetric(String rawCount) {
  long value = rawCount.toInt(); // Convert text "19700" to number 19700
  
  if (value >= 1000000) {
    // If over 1 Million (e.g. 1,500,000 -> 1.5M)
    float val = value / 1000000.0;
    if (val == (int)val) return String((int)val) + "M"; // No decimal if whole number
    return String(val, 1) + "M"; // One decimal place
  } else if (value >= 1000) {
    // If over 1 Thousand (e.g. 19,700 -> 19.7K)
    float val = value / 1000.0;
    if (val == (int)val) return String((int)val) + "K"; // No decimal if whole number
    return String(val, 1) + "K"; // One decimal place
  } else {
    // If under 1000, just show the number (e.g. 500)
    return String(value);
  }
}

// ----------------HELPER: FETCH DATA----------------
void updateScreen() {
  // Only try to update if WiFi is alive
  if (WiFi.status() == WL_CONNECTED) {
    
    // Create a secure client (HTTPS)
    WiFiClientSecure client;
    client.setInsecure(); // Skip checking the security certificate (simplifies code)
    HTTPClient https;
    
    // Construct the Google API URL
    String url = "https://www.googleapis.com/youtube/v3/channels?part=statistics&id=" + String(channelId) + "&key=" + String(apiKey);

    // Start the connection
    if (https.begin(client, url)) {
      int httpCode = https.GET(); // Send the request
      
      // If server responds with data (Code > 0)
      if (httpCode > 0) {
        String payload = https.getString(); // Get the raw text data
        
        // Parse the JSON data
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (!error) {
          // Extract the specific "subscriberCount" field
          String rawCount = doc["items"][0]["statistics"]["subscriberCount"].as<String>();
          
          // Convert it to K/M format
          String formattedCount = formatMetric(rawCount); 

          // Check if number changed since last time
          if (formattedCount != oldFormattedCount) {
            drawMainInterface(formattedCount); // Redraw screen
            oldFormattedCount = formattedCount; // Save new number
          }
        }
      }
      https.end(); // Close connection
    }
  }
  // Reset timer
  lastTime = millis();
}

// ----------------HELPER: DRAW UI----------------
void drawMainInterface(String count) {
  tft.fillScreen(BG_COLOR); // Clear screen
  
  // 1. Top Branding
  tft.setTextColor(TEXT_COLOR, BG_COLOR);
  tft.setTextDatum(TC_DATUM); // Top Center alignment
  tft.setTextSize(1);         // Normal size
  tft.drawString("Fixitdaz TV", 160, 25, 4); // Draw Header in Font 4

  // 2. Middle Logo Area
  int logoY = 85; // Vertical position of the logo row
  drawYouTubeLogo(tft, 70, logoY); // Call function from graphics.h
  
  tft.setTextDatum(TL_DATUM); // Top Left alignment for text next to logo
  tft.drawString("YouTube", 140, logoY + 4, 4); // Draw "YouTube"
  
  tft.setTextColor(SUB_COLOR, BG_COLOR); // Switch to Gray
  tft.drawString("subscribers", 140, logoY + 28, 2); // Draw "subscribers"

  // 3. Bottom Big Number
  tft.setTextColor(TEXT_COLOR, BG_COLOR); // Switch back to White
  tft.setTextDatum(MC_DATUM); // Middle Center alignment
  
  // Scale text up to make it huge
  tft.setTextSize(2); // Double size
  tft.drawString(count, 160, 200, 4); // Draw the count using Font 4
  
  // Reset text size for safety
  tft.setTextSize(1);
}