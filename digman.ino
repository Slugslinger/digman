
#include <Arduboy2.h>
#include "bitmaps.h"

// make an instance of arduboy used for many functions
Arduboy2 arduboy;

// make an ArdBitmap instance that will use the given the screen buffer and dimensions
#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

const int tileSize = 12;
const int screenWidth = 128;
const int screenHeight = 64;
const int numBlocks = 10;  // Number of blocks you want to draw

// Define variables for element positions and other game logic
// Adjust as needed based on your game design

void setup() {
  // initiate arduboy instance
  arduboy.begin();
  arduboy.setFrameRate(60);
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }

  // Game logic goes here

  drawGame(); // Call function to draw game elements
}
  
// Define Y positions for each level of block2
int blockYLevel1 = screenHeight - tileSize * 3;
int blockYLevel2 = screenHeight - tileSize * 2;
int blockYLevel3 = screenHeight - tileSize * 1;

// Calculate the total width of the blocks
int totalBlockWidth = tileSize * numBlocks;
// Calculate the starting X position to center the blocks
int blockX = (screenWidth - totalBlockWidth) / 2;

// Digman Position
int digmanX = 50;
int digmanY = blockYLevel1 - tileSize; 

void drawGame() {
    arduboy.clear();

    // Draw block2 for level 1
    for (int i = 0; i < numBlocks; i++) {
        arduboy.drawBitmap(blockX + i * tileSize, blockYLevel1, epd_bitmap_block2, 12, 12, WHITE);
    }

    // Draw block2 for level 2
    for (int i = 0; i < numBlocks; i++) {
        arduboy.drawBitmap(blockX + i * tileSize, blockYLevel2, epd_bitmap_block2, 12, 12, WHITE);
    }

    // Draw block2 for level 3
    for (int i = 0; i < numBlocks; i++) {
        arduboy.drawBitmap(blockX + i * tileSize, blockYLevel3, epd_bitmap_block2, 12, 12, WHITE);
    }

    // Draw 'digman' character on top of the blocks
    // int digmanX = 50; // Adjust this value for 'digman' X position
    // int digmanY = blockYLevel1 - tileSize; // Position 'digman' above the blocks
    arduboy.drawBitmap(digmanX, digmanY, epd_bitmap_digman, 12, 12, WHITE);

    arduboy.display();
}