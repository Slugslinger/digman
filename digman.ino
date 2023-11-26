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

int blockYLevel1 = screenHeight - tileSize * 3;
int blockYLevel2 = screenHeight - tileSize * 2;
int blockYLevel3 = screenHeight - tileSize * 1;

int totalBlockWidth = tileSize * numBlocks;
int blockX = (screenWidth - totalBlockWidth) / 2;

int digmanX = 50;
int digmanY = blockYLevel1 - tileSize;

bool isPressed = false;
bool canMove = true;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
}

void loop() {
  arduboy.pollButtons(); // Read button inputs
  
  if (!arduboy.nextFrame()) {
    return;
  }

  
    if (arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(RIGHT_BUTTON)) {
      isPressed = true;
    }
    if (arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON)) {
      isPressed = false;
    }
  
    if(isPressed && canMove) {
      if (arduboy.pressed(LEFT_BUTTON)) {
        int newX = digmanX - tileSize;

        if (isAtXBoundary(newX)) {
          digmanX = newX;
        }
      }
      
      else if (arduboy.pressed(RIGHT_BUTTON)) {
        int newX = digmanX + tileSize;
        if (isAtXBoundary(newX)) {
          digmanX = newX;
        }
      }
      canMove = false;
    }
    else if(!canMove && !isPressed) {
      canMove = true;
    }
    // Similar logic for UP and DOWN movements...
  
  drawGame();
}

void drawGame() {
    arduboy.clear();

    for (int i = 0; i < numBlocks; i++) {
        arduboy.drawBitmap(blockX + i * tileSize, blockYLevel1, epd_bitmap_block2, 12, 12, WHITE);
        arduboy.drawBitmap(blockX + i * tileSize, blockYLevel2, epd_bitmap_block2, 12, 12, WHITE);
        arduboy.drawBitmap(blockX + i * tileSize, blockYLevel3, epd_bitmap_block2, 12, 12, WHITE);
    }

    arduboy.drawBitmap(digmanX, digmanY, epd_bitmap_digman, 12, 12, WHITE);

    arduboy.display();
}

bool isAtXBoundary(int x) {
    return (x >= 0 && x <= screenWidth - tileSize);
}
