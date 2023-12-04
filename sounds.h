#ifndef SOUNDS_H
#define SOUNDS_H

#include <Arduino.h>
#include <ArduboyTones.h>

// Coins
const uint16_t coinValue1[] PROGMEM = {NOTE_E7, 50, TONES_END};
const uint16_t coinValue10[] PROGMEM = {NOTE_F7, 100, NOTE_A6, 100, TONES_END};
const uint16_t coinValue100[] PROGMEM = {NOTE_G7, 150, NOTE_B6, 150, NOTE_D6, 150, TONES_END};
// Sound for Power-up 1
const uint16_t powerUp1[] PROGMEM = {NOTE_C7, 100, NOTE_E7, 100, NOTE_G7, 100, TONES_END};
// Sound for Power-up 2
const uint16_t powerUp2[] PROGMEM = {NOTE_A5, 150, NOTE_B5, 150, NOTE_D6, 150, TONES_END};
// Damage hit
const uint16_t damageSound[] PROGMEM = {NOTE_C4, 50, NOTE_G3, 50, NOTE_E3, 50, TONES_END};
// Theme song
const uint16_t themeSong[] PROGMEM = {
  NOTE_C4, 200, NOTE_G4, 200, NOTE_A4, 400,
  NOTE_C4, 200, NOTE_G4, 200, NOTE_A4, 400,
  NOTE_F4, 200, NOTE_E4, 200, NOTE_D4, 400,
  NOTE_F4, 200, NOTE_E4, 200, NOTE_D4, 400,
  TONES_END
};
// Game Over
const uint16_t gameOverSound[] PROGMEM = {
  NOTE_A1, 500, NOTE_G1, 500, NOTE_E1, 1000,
  TONES_END
};

#endif