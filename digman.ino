#include <Arduboy2.h>
#include "bitmaps.h"

Arduboy2 arduboy;

#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

const int tileSize = 12;
const int screenWidth = 128;
const int screenHeight = 64;
const int numBlocks = 10;
// Number of levels
const int numLevels = 6;
const int startingLvl = 3;

int currentLvl = 0;

int totalBlockWidth = tileSize * numBlocks;
int blockX = (screenWidth - totalBlockWidth) / 2;

int digmanX = 50;
int digmanY = screenHeight - tileSize * 4;

unsigned long lastMoveTime = 0; // Timestamp to track last movement
const unsigned long moveDelay = 150; // Delay between movements (in milliseconds)
unsigned long lastDownMoveTime = 0; // Timestamp to track last downward movement
const unsigned long downMoveDelay = 150; // Delay between downward movements (in milliseconds)

int blockYLevels[numBlocks][numLevels];

void setup() {
  // Initialize block positions
    for (int i = 0; i < numBlocks; i++) {
        for (int j = 0; j < numLevels; j++) {
            blockYLevels[i][j] = screenHeight - tileSize * (startingLvl + startingLvl - j);
        }
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
        for (int j = 0; j < numLevels - 1; j++) {
            blockYLevels[i][j] = blockYLevels[i][j + 1];
        }
    }
}

void moveBlocksUp() {
    unsigned long currentTime = millis();

    if (currentTime - lastDownMoveTime >= downMoveDelay) {
        if (currentLvl < numLevels) {
            currentLvl++;
        } else {
            currentLvl = 0;

            // Shift blocks up
            shiftBlocksUp();

            // Move the block at level 6 to the bottom
            for (int i = 0; i < numBlocks; i++) {
                if (currentLvl - 1 == 6) {
                    blockYLevels[i][numLevels - 1] = screenHeight - tileSize * (startingLvl - numLevels);
                }
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
            arduboy.drawBitmap(blockX + i * tileSize, blockYLevels[i][j], epd_bitmap_block2, 12, 12, WHITE);
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
