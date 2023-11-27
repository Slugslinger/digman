#include <Arduboy2.h>
#include "bitmaps.h"

Arduboy2 arduboy;

#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

const int tileSize = 12;
const int screenWidth = 128;
const int screenHeight = 64;
// Number of blocks
const int numBlocks = 10;
// Number of levels
const int numLevels = 6;
const int startingLvl = 2;

// 0 means it's a block
// 1, 10, 100 its the gems type and points we earn
// -1 means the block was destroyed 
int blocks[numLevels][numBlocks];
int blockYLevels[numLevels];

int currentLvl = 0;

int totalBlockWidth = tileSize * numBlocks;
int blockX = (screenWidth - totalBlockWidth) / 2;
int totalBlockHeight = tileSize * (numLevels - 1);
int blockY = screenHeight - totalBlockHeight;

int digmanX = blockX;
// Digman needs to be one level on top so we add one more tileSize
int digmanY = tileSize * startingLvl - tileSize + blockY;

unsigned long lastMoveTime = 0; // Timestamp to track last movement
const unsigned long moveDelay = 150; // Delay between movements (in milliseconds)
unsigned long lastDownMoveTime = 0; // Timestamp to track last downward movement
const unsigned long downMoveDelay = 150; // Delay between downward movements (in milliseconds)

void setup() {
  // Initialize block Y positions
  for (int i = 0; i < numLevels; i++) {
    blockYLevels[i] = tileSize * (startingLvl + i) + blockY;
  }

  arduboy.begin();
  arduboy.setFrameRate(60);
}

void loop() {
  arduboy.pollButtons(); // Read button inputs
  
  if (!arduboy.nextFrame()) {
    return;
  }

  if (arduboy.pressed(LEFT_BUTTON)) {
    moveDigman(-tileSize);
  } else if (arduboy.pressed(RIGHT_BUTTON)) {
    moveDigman(tileSize);
  }
  
  if (arduboy.pressed(DOWN_BUTTON)) {
    moveBlocksUp();
  }

  drawGame();
}

void moveDigman(int deltaX) {
  unsigned long currentTime = millis();

  if (currentTime - lastMoveTime >= moveDelay) {
    int newX = digmanX + deltaX;

    if (isAtXBoundary(newX)) {
      digmanX = newX;
    }

    lastMoveTime = currentTime;
  }
}

void shiftBlocksUp() {
    // Shift the blocks up by one level
    for (int i = 0; i < numBlocks; i++) {
      blockYLevels[i] = blockYLevels[i + 1];
    }
}

void moveBlocksUp() {
    unsigned long currentTime = millis();

    if (currentTime - lastDownMoveTime >= downMoveDelay) { 
      currentLvl++;

      for (int i = 0; i < numLevels; i++) {
        int newYPos =  tileSize * (startingLvl + i - currentLvl) + blockY;

        if(newYPos < - tileSize) {
          blockYLevels[i] = newYPos + screenHeight + tileSize - blockY;
        }
        else {
          blockYLevels[i] = newYPos;
        }
      }

      lastDownMoveTime = currentTime;
    }
}

void drawGame() {
    arduboy.clear();

    // Draw blocks based on their positions
    for (int i = 0; i < numBlocks; i++) {
      for (int j = 0; j < numLevels; j++) {
        arduboy.drawBitmap(blockX + i * tileSize, blockYLevels[j], epd_bitmap_block2, 12, 12, WHITE);
      }
    }

    arduboy.drawBitmap(digmanX, digmanY, epd_bitmap_digman, 12, 12, WHITE);

    arduboy.display();
}

bool isAtXBoundary(int x) {
  if (x <= 0 || x >= screenWidth - tileSize) {
    return false;
  }

  return true;
}
