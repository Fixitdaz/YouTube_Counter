/*
 * File:    graphics.h
 * Author:  fixitdaztv
 * Date:    2025-12-11
 * Purpose: Contains helper functions to draw vector graphics (Logos)
 * This saves memory by drawing shapes instead of loading images.
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <pgmspace.h>
#include <TFT_eSPI.h> // Include graphics library

// Function: drawYouTubeLogo
// Inputs: tft object, x position, y position
void drawYouTubeLogo(TFT_eSPI &tft, int x, int y) {
  
  // 1. Draw the Red Box
  // fillRoundRect(x, y, width, height, radius, color)
  tft.fillRoundRect(x, y, 60, 42, 10, 0xE800); // 0xE800 is YouTube Red hex
  
  // 2. Draw the White Play Triangle
  // fillTriangle(x1, y1, x2, y2, x3, y3, color)
  // Coordinates are relative to the x,y input
  tft.fillTriangle(x + 24, y + 12,   // Top Point
                   x + 24, y + 30,   // Bottom Point
                   x + 40, y + 21,   // Middle Point (Tip)
                   TFT_WHITE);       // Color
}

#endif