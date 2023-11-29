#include <Arduboy2.h>
#include <EEPROM.h>
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
int highScore = 0;
int score = 0;
bool isNewHighScore = false;
bool gameOver = false;

int totalBlockWidth = tileSize * numBlocks;
int blockX = (screenWidth - totalBlockWidth) / 2;
int totalBlockHeight = tileSize * (numLevels - 1);
int blockY = screenHeight - totalBlockHeight;

int digmanX = blockX;
// Digman needs to be one level on top so we add one more tileSize
int digmanY = tileSize * startingLvl - tileSize + blockY;

enum GameState {
  START_MENU,
  GAME_PLAY,
  GAME_OVER
};

GameState gameState = START_MENU;

unsigned long lastMoveTime = 0; // Timestamp to track last movement
const unsigned long moveDelay = 250; // Delay between movements (in milliseconds)
unsigned long lastDownMoveTime = 0; // Timestamp to track last downward movement
const unsigned long downMoveDelay = 250; // Delay between downward movements (in milliseconds)

unsigned long boostMove = 150;
const unsigned long boostTimer = 5000;
unsigned long startBoostTime;

// Game timer
unsigned long startTime;
unsigned long currentTime;
unsigned long timeElapsed;
unsigned long gameDuration = 0.5 * 60000; // Game duration in milliseconds

// Function prototypes
void setup();
void loop();
void displayScore();
void moveDigman(int deltaX);
int getRandomValue();
void moveBlocksUp();
void drawGame();
void displayTimer();
void displayFinalScore();
void updateHighScore(int newScore);
void displayHighScore(int yPos = 10);
void resetGame();
void displayStartMenu();
bool isAtXBoundary(int x);

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

  // Load the high score from EEPROM
  EEPROM.get(0, highScore);

  startTime = millis(); // Record the start time when the game begins
}

void loop() {
  arduboy.pollButtons(); // Read button inputs
  
  if (!arduboy.nextFrame()) {
    return;
  }

  switch (gameState) {
    case START_MENU:
      if (arduboy.pressed(A_BUTTON)) {
        gameState = GAME_PLAY;
        resetGame(); // Reset the game when starting
      }
      displayStartMenu();
      break;

     case GAME_PLAY:
      // Game logic
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
        gameState = GAME_OVER;
      }
      break;
    
      case GAME_OVER:
        // Game over state
        updateHighScore(score);
        displayFinalScore();
        // Optionally, you can add a reset or exit condition here

        if (arduboy.pressed(A_BUTTON)) {
          resetGame();
        }
      break;
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
          } else if(blocks[i][j] == 6) {
            startBoostTime = millis();
          } else if(blocks[i][j] == -2) {
            gameState = GAME_OVER;
          } else if(blocks[i][j] > 0) {
            score += blocks[i][j];
          }

          // Destroy block
          blocks[i][j] = -1;
        }

        if (blocks[i][j] == -1) {
          arduboy.drawRect(newX, newY, tileSize, tileSize, BLACK); // Draw black rectangle for an empty block
        }
        else if(blocks[i][j] == -2) {
          arduboy.drawBitmap(newX, newY, epd_bitmap_spider, 12, 12, WHITE);
        }
        else if(blocks[i][j] == 5) {
          arduboy.drawBitmap(newX, newY, epd_bitmap_time, 12, 12, WHITE);
        }
        else if(blocks[i][j] == 6) {
          arduboy.drawBitmap(newX, newY, epd_bitmap_speed1, 12, 12, WHITE);
        }
        else if(blocks[i][j] == 1) {
          // arduboy.drawBitmap(newX, newY, epd_bitmap_gem2, 12, 12, WHITE);
          arduboy.drawBitmap(newX, newY, epd_bitmap_coin1_v3, 12, 12, WHITE);
        }
        else if(blocks[i][j] == 10) {
          // arduboy.drawBitmap(newX, newY, epd_bitmap_gem1, 12, 12, WHITE);~
          arduboy.drawBitmap(newX, newY, epd_bitmap_coin10_v3, 12, 12, WHITE);
        }
        else if(blocks[i][j] == 100) {
          // arduboy.drawBitmap(newX, newY, epd_bitmap_gem4, 12, 12, WHITE);
          arduboy.drawBitmap(newX, newY, epd_bitmap_coin100, 12, 12, WHITE);
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
  // In case we need to wait to move again
    bool canMove;

    if(isSpeedBoost()) {
      canMove = currentTime - lastMoveTime >= boostMove;
    }
    else {
      canMove = currentTime - lastMoveTime >= moveDelay;
    }

  if (canMove) {
    int newX = digmanX + deltaX;

    if (isAtXBoundary(newX)) {
      digmanX = newX;
    }

    lastMoveTime = currentTime;
  }
}

int getRandomValue() {
  int randomValue = random(1, 101); // Generate a random number between 1 and 100

  if (randomValue <= 1) {
    //spider
    return -2;
  } else if (randomValue <= 2) {
    //power up
    int newRandomValue = random(1, 50); 
    if(newRandomValue <= 25) {
      //extra time
      return 5;
    } else {
      //speed boost
      return 6;
    }
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
    // In case we need to wait to move again
    bool canMove;

    if(isSpeedBoost()) {
      canMove = currentTime - lastDownMoveTime >= boostMove;
    }
    else {
      canMove = currentTime - lastDownMoveTime >= downMoveDelay;
    }

    if (canMove) {
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

void displayStartMenu() {
  arduboy.clear();

  // Display the start menu elements
  arduboy.drawBitmap(0, 0, epd_bitmap_title, 128, 64, WHITE);

  // Display "Press A to start" message at the bottom
  arduboy.setCursor(16, 35);
  arduboy.print("Press A to start");

  displayHighScore(50);

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
  arduboy.setCursor(35, 0); // Adjust position for the final score text
  arduboy.print("Game Over!");
  arduboy.setCursor(10, 20); // Adjust position for the final score text
  // arduboy.print("Final Score:");
  if(isNewHighScore){
      arduboy.print("New High Score: ");
      
      isNewHighScore = false;
    }
    else {
      arduboy.print("Final Score:");
    }
  arduboy.setCursor(50, 30); // Adjust position for the final score value
  arduboy.print(score);
  arduboy.setCursor(10, 50); // Adjust position for the instructions text
  arduboy.print("Press A to restart");

  // displayHighScore();
  arduboy.display();
}

void resetGame() {
  // Re-initialize block Y positions and values
  for (int i = 0; i < numLevels; i++) {
    blockYLevels[i] = tileSize * (startingLvl + i) + blockY;
    for (int j = 0; j < numBlocks; j++) {
      blocks[i][j] = getRandomValue();
    }
  }

  // Reset all game variables to their initial values
  gameOver = false;
  score = 0;
  startTime = millis();
  gameDuration = 0.5 * 60000;
  // Add any additional reset logic here if needed

  gameState = GAME_PLAY;
}

bool isSpeedBoost() {
    long temp = millis();

    return temp < startBoostTime + boostTimer;
}

bool isAtXBoundary(int x) {
  if (x <= 0 || x >= screenWidth - tileSize) {
    return false;
  }

  return true;
}

void updateHighScore(int newScore) {
    if (newScore > highScore) {
        highScore = newScore;
        isNewHighScore = true;
        // Store the new high score to EEPROM
        EEPROM.put(0, highScore);
    }
}

void displayHighScore(int yPos = 10) {
      arduboy.setCursor(15, yPos); // Adjust position for the high score text
      arduboy.print("High Score: ");
    arduboy.print(highScore);
}