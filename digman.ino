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
int score = 0;
bool gameOver = false;

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

// Game timer
unsigned long startTime;
unsigned long currentTime;
unsigned long timeElapsed;
unsigned long gameDuration = 0.5 * 60000; // Game duration in milliseconds
void setup() {
  // Initialize block Y positions
  for (int i = 0; i < numLevels; i++) {
    blockYLevels[i] = tileSize * (startingLvl + i) + blockY;

    // Set random values for blocks at each level
    for (int j = 0; j < numBlocks; j++) {
      blocks[i][j] = getRandomValue();
    }
  }

  arduboy.begin();
  arduboy.setFrameRate(60);

   startTime = millis(); // Record the start time when the game begins
}

void loop() {
  arduboy.pollButtons(); // Read button inputs
  
  if (!arduboy.nextFrame()) {
    return;
  }

  if (!gameOver) {
    if (arduboy.pressed(LEFT_BUTTON)) {
      moveDigman(-tileSize);
    } else if (arduboy.pressed(RIGHT_BUTTON)) {
      moveDigman(tileSize);
    }
    
    if (arduboy.pressed(DOWN_BUTTON)) {
      moveBlocksUp();
    }

    if (timeElapsed >= gameDuration) {
      gameOver = true;
      // Optionally, you can add further actions here when the game ends
    }

    drawGame();
  } else {
    // Game over, display final score fullscreen
    displayFinalScore();
    // Optionally, you can add a reset or exit condition here

    if (arduboy.pressed(A_BUTTON)) {
      resetGame();
    }
  }
}

void displayScore() {
  int scoreDigits = 1; // Assume the score has at least one digit

  if (score >= 10) {
    scoreDigits = 2;
  }
  if (score >= 100) {
    scoreDigits = 3;
  }
  if (score >= 1000) {
    scoreDigits = 4;
  }
  if (score >= 1000) {
    scoreDigits = 5;
  }
  // Add more conditions for larger scores if needed

  int scoreX = screenWidth - 2 - (scoreDigits * 6); // Adjust the multiplication factor based on font size

  //Adjust the -6 in the fillRect function to increase or decrease the padding between the score and the score label.
  arduboy.fillRect(scoreX - 2, 0, scoreDigits * 6, 8, BLACK); // Black background for the score
  arduboy.setCursor(scoreX, 2); // Adjust position for the score text
  arduboy.print(score);
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

int getRandomValue() {
  int randomValue = random(1, 101); // Generate a random number between 1 and 100

  if (randomValue <= 2) {
    return 5;
  } else if (randomValue <= 75) {
    return 0; // Around 75% chance for a gem
  } else if (randomValue <= 90) {
    return 1; // Around 5% chance for a gem
  } else if (randomValue <= 99) {
    return 10; // Around 15% chance for a 10-point gem
  } else {
    return 100; // Around 5% chance for a 100-point gem (rarer)
  }
}

void moveBlocksUp() {
    unsigned long currentTime = millis();

    if (currentTime - lastDownMoveTime >= downMoveDelay) {
      for (int i = 0; i < numLevels; i++) {
        blockYLevels[i] -= tileSize; // Move blocks up by one tileSize

        // If a block goes beyond the top of the screen, move it back to the bottom
        if (blockYLevels[i] < 0) {
          blockYLevels[i] = screenHeight - tileSize;
            // Set random values for blocks at each level
            for (int j = 0; j < numBlocks; j++) {
              blocks[i][j] = getRandomValue();
            }
          }
      }

      lastDownMoveTime = currentTime;
    }
}

void drawGame() {
    arduboy.clear();

    // Draw blocks based on their positions
    for (int i = 0; i < numLevels; i++) {
      for (int j = 0; j < numBlocks; j++) {
        int newY = blockYLevels[i];
        int newX = blockX + j * tileSize;
        
        if(newX == digmanX && newY == digmanY){
          // Add score
          if(blocks[i][j] == 5) {
            gameDuration += 5000; //more 5 seconds
          } else if(blocks[i][j] > 0) {
            score += blocks[i][j];
          }

          // Destroy block
          blocks[i][j] = -1;
        }

        if (blocks[i][j] == -1) {
          arduboy.drawRect(newX, newY, tileSize, tileSize, BLACK); // Draw black rectangle for an empty block
        }
        else if(blocks[i][j] == 5) {
          arduboy.drawBitmap(newX, newY, epd_bitmap_time, 12, 12, WHITE);
        }
        else if(blocks[i][j] == 1) {
          arduboy.drawBitmap(newX, newY, epd_bitmap_gem2, 12, 12, WHITE);
        }
        else if(blocks[i][j] == 10) {
          arduboy.drawBitmap(newX, newY, epd_bitmap_gem1, 12, 12, WHITE);
        }
        else if(blocks[i][j] == 100) {
          arduboy.drawBitmap(newX, newY, epd_bitmap_gem4, 12, 12, WHITE);
        }
        else {
          arduboy.drawBitmap(newX, newY, epd_bitmap_block2, 12, 12, WHITE);
        }

      }
    }

    arduboy.drawBitmap(digmanX, digmanY, epd_bitmap_digman, 12, 12, WHITE);

    currentTime = millis();
    timeElapsed = currentTime - startTime;

    displayScore();
    displayTimer();

    arduboy.display();
}

void displayTimer() {
  int timeDigits = 2; // Display timer in seconds (2 digits)
  int secondsLeft = (gameDuration - timeElapsed) / 1000; // Convert milliseconds to seconds
  
  int timerX = 2; // Adjust this value for positioning the timer

  arduboy.fillRect(timerX, 0, timeDigits * 6, 8, BLACK); // Black background for the timer
  arduboy.setCursor(timerX, 2); // Adjust position for the timer text
  arduboy.print(secondsLeft);
}

void displayFinalScore() {
  arduboy.clear();
  arduboy.setCursor(10, 10); // Adjust position for the final score text
  arduboy.print("Game Over!");
  arduboy.setCursor(10, 20); // Adjust position for the final score text
  arduboy.print("Final Score:");
  arduboy.setCursor(50, 30); // Adjust position for the final score value
  arduboy.print(score);
  arduboy.setCursor(10, 50); // Adjust position for the instructions text
  arduboy.print("Press A to restart");
  arduboy.display();
}

void resetGame() {
  // Reset all game variables to their initial values
  gameOver = false;
  score = 0;
  startTime = millis();
  gameDuration = 0.5 * 60000;
  // Add any additional reset logic here if needed

  // Re-initialize block Y positions and values
  for (int i = 0; i < numLevels; i++) {
    blockYLevels[i] = tileSize * (startingLvl + i) + blockY;
    for (int j = 0; j < numBlocks; j++) {
      blocks[i][j] = getRandomValue();
    }
  }
}

bool isAtXBoundary(int x) {
  if (x <= 0 || x >= screenWidth - tileSize) {
    return false;
  }

  return true;
}
