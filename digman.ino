#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <EEPROM.h>
#include "bitmaps.h"
#include "sounds.h"

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

const int tileSize = 12;
const int screenWidth = 128;
const int screenHeight = 64;
// Number of blocks
const int numBlocks = 10;
// Number of levels
const int numLevels = 5;
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
bool isFalling = false;
bool isThemePlaying = false;

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
void drawBlock(int x, int y, int blockType);
void handleDigmanCollision(int row, int col);
void playSound(const uint16_t *sound);
void playThemeSong();
void stopThemeSong();
void playGameOverSound();

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(60);

    // Load the high score from EEPROM
    EEPROM.get(0, highScore);

    //Debug
    Serial.begin(9600); // Initialize serial communication at 9600 baud rate

    // Set the initial block map
    for (int i = 0; i < numLevels; i++) {
        blockYLevels[i] = tileSize * (startingLvl + i) + blockY;

        // Set random values for blocks in the rest of the columns at each level
        for (int j = 1; j < numBlocks; j++) {
            blocks[i][j] = getRandomValue();
        }
    }

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
        // playThemeSong();
        
        if (!isFalling) {
            int levelBelowDigman = -1;
            for (int i = 0; i < numLevels; i++) {
                if (digmanY + tileSize == blockYLevels[i]) {
                    levelBelowDigman = i;
                    break;
                }
            }

            if (levelBelowDigman != -1) {
                int col = (digmanX - blockX) / tileSize; // Get the column of the digman

                // Access the block below the 'digman' in the 'blocks' array
                int blockBelowDigman = blocks[levelBelowDigman][col];
                // Serial.println("Block below digman: " + String(blockBelowDigman));

                if(blockBelowDigman != 0) {
                  moveBlocksUp();
                }
            }
        }

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
        // stopThemeSong();
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

    for (int i = 0; i < numLevels; i++) {
        for (int j = 0; j < numBlocks; j++) {
            int newY = blockYLevels[i];
            int newX = blockX + j * tileSize;

            if (newX == digmanX && newY == digmanY) {
                handleDigmanCollision(i, j); // Handle collision with digman
            }
                drawBlock(newX, newY, blocks[i][j]); // Draw the block if it's within the screen bounds
        }
    }

    arduboy.drawBitmap(digmanX, digmanY, epd_bitmap_digman, 12, 12, WHITE);

    currentTime = millis();
    timeElapsed = currentTime - startTime;

    displayScore();
    displayTimer();

    arduboy.display();

        // Print the current map state to Serial
    // printMapState();
}

void drawBlock(int x, int y, int blockType) {
    switch (blockType) {
        case -2:
            arduboy.drawBitmap(x, y, epd_bitmap_spider, 12, 12, WHITE);
            break;
        case -1:
            arduboy.drawRect(x, y, tileSize, tileSize, BLACK);
            break;
        case 5:
            arduboy.drawBitmap(x, y, epd_bitmap_time, 12, 12, WHITE);
            break;
        case 6:
            arduboy.drawBitmap(x, y, epd_bitmap_speed1, 12, 12, WHITE);
            break;
        case 1:
            arduboy.drawBitmap(x, y, epd_bitmap_coin1_v3, 12, 12, WHITE);
            break;
        case 10:
            arduboy.drawBitmap(x, y, epd_bitmap_coin10_v3, 12, 12, WHITE);
            break;
        case 100:
            arduboy.drawBitmap(x, y, epd_bitmap_coin100, 12, 12, WHITE);
            break;
        default:
            arduboy.drawBitmap(x, y, epd_bitmap_block2, 12, 12, WHITE);
            break;
    }
}

void handleDigmanCollision(int row, int col) {
    int blockType = blocks[row][col];

    // Handle different block types and their effects on 'digman'
    switch (blockType) {
        case 5: // If the block is a time power-up
            playSound(powerUp1);
            gameDuration += 5000; // Add 5 seconds to the game duration
            break;
        case 6: // If the block is a speed boost power-up
            playSound(powerUp2);
            startBoostTime = millis(); // Start the speed boost timer
            break;
        case -2: // If the block is a spider
            playGameOverSound();
            gameState = GAME_OVER; // Game over due to collision with a spider
            break;
        case 0: // If the block is a regular block without any effect
            // No specific effect on 'digman'
            break;
        case 1: // If the block is a type with some effect (example)
            playSound(coinValue1);
            score += 1; // Increase the score by 1
            break;
        case 10: // Handle other block types with specific effects (example)
            playSound(coinValue10);
            score += 10; // Increase the score by 10
            break;
        case 100: // Another block type with a different effect (example)
            playSound(coinValue100);
            score += 100; // Increase the score by 100
            break;
        default:
            // Handle any other block type not covered above
            break;
    }

    blocks[row][col] = -1;
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
    isFalling = false;
  }
}

void moveBlocksUp() {
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

      lastMoveTime = currentTime;
      isFalling = false;
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
  // arduboy.print("Final Score:");
  if(isNewHighScore){
      arduboy.setCursor(10, 20); // Adjust position for the final score text
      arduboy.print("New High Score: ");
      
      isNewHighScore = false;
    }
    else {
      arduboy.setCursor(25, 20); // Adjust position for the final score text
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

void playSound(const uint16_t *soundToPlay) {
  sound.tone(soundToPlay);
  delay(200); // Adjust this delay to control the sound duration
  sound.noTone(); // Stop the sound after the delay
}

void playGameOverSound() {
  sound.tone(gameOverSound);
  delay(500); // Adjust this delay to control the sound duration
  sound.noTone(); // Stop the sound after the delay
}

void playThemeSong() {
  if(!isThemePlaying) {
    isThemePlaying = true;
    sound.tone(themeSong);
  }
}

void stopThemeSong() {
  if(isThemePlaying){
    isThemePlaying = false;
    sound.noTone(); // Stop the sound after the delay
  }
}

int getRandomValue() {
    int randomValue = random(1, 101); // Generate a random number between 1 and 100

    // Prioritize generating specific block types
    if (randomValue <= 1) {
        return -2; // spider
    } else if (randomValue <= 2) {
        int newRandomValue = random(1, 50);

        if (newRandomValue <= 25) {
            return 5; // extra time
        } else {
            return 6; // speed boost
        }
    } else if (randomValue <= 75) {
        return 0; // Regular block
    } else if (randomValue <= 90) {
        return 1; // Coin (low value)
    } else if (randomValue <= 98) {
        return 10; // Coin (medium value)
    } else if (randomValue <= 99) {
        return 100; // Coin (high value)
    } else {
        return -1; // default empty block
    }
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

void printMapState() {
    Serial.println("Current Map State:");
    for (int i = 0; i < numLevels; i++) {
        Serial.print("blockYLevels[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(blockYLevels[i]);
        
        for (int j = 0; j < numBlocks; j++) {
            int newY = blockYLevels[i];
            int newX = blockX + j * tileSize;
            
            Serial.print("X: ");
            Serial.print(newX);
            Serial.print(", Y: ");
            Serial.print(newY);
            Serial.print(", Block: ");
            Serial.print(blocks[i][j]);
            Serial.print(" ");
        }
        Serial.println();
    }
    Serial.println();
}