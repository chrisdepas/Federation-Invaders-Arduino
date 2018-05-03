/*
**   'Federation Invaders'
**  Attempt at a Space invaders clone
**  Chris De Pasquale
**  Jan 2018  
**
*/

#include <SPI.h>
#include <TFTFaster.h>
#include "TonePlayer.h"
#include "Time.h"
#include "GameTones.h"
#include "GameDraw.h"
#include "ExplosionController.h"
#include "Vector.h"
#include "ProjectileController.h"

#define POTENTIOMETER_PIN A3  
#define PlayerHorizontalInput() (analogRead(POTENTIOMETER_PIN) + 1) / 1024.0
    
#define NSTARS 100
uint8_t sx[NSTARS] = {};
uint8_t sy[NSTARS] = {};
uint8_t sz[NSTARS] = {};

uint8_t  g_PlayerX, g_PlayerY;

ProjectileController g_Projectiles;
ExplosionController g_Explosions;
TonePlayerAsync g_TonePlayer;

void setup() {
  randomSeed(analogRead(0));
  DisplayBegin();
  BEGIN_TFT();
  Display_FillRect(0, 0, ST7735R_WIDTH-1, ST7735R_HEIGHT-1, 0, 0, 0);

  // Init player position
  g_PlayerX = ST7735R_WIDTH / 2;
  g_PlayerY = 2;

  g_TonePlayer.Init();
  g_TonePlayer.PlayMelody(introTone, Time());
  
  g_Explosions.Init();
  // Test:
  g_Explosions.CreateExplosion(Time(), ST7735R_WIDTH - 10, ST7735R_HEIGHT - 10);
  g_Explosions.CreateExplosion(Time(), ST7735R_WIDTH / 2, ST7735R_HEIGHT / 2);
  g_Explosions.CreateExplosion(Time(), 20, 20);
}

void loop() {
  // Read input 
  float playerHorizontal = PlayerHorizontalInput();
  g_PlayerX = playerHorizontal * ST7735R_WIDTH;

  time_t time = Time();
  
  // Update sounds
  g_TonePlayer.Update(time);
  
  BEGIN_TFT();

  /* Render star background 
  Source: https://github.com/juj/ST7735R/blob/master/Test4_Starfield.h */
  DisplayBeginPixels();
  uint8_t spawnDepthVariation = 255;
  for(int i = 0; i < NSTARS; ++i) {
    if (sz[i] <= 1) {
      sx[i] = 80 - 64 + (random() & 127);
      sy[i] = random() & 127;
      sz[i] = spawnDepthVariation--;
    } 
    else {
      int old_screen_x = ((int)sx[i] - 80) * 256 / sz[i] + 80;
      int old_screen_y = ((int)sy[i] - 64) * 256 / sz[i] + 64;
      DisplayPixel(old_screen_x, old_screen_y, 0, 0, 0);
      sz[i] -= 2;
      if (sz[i] > 1) {
        int screen_x = ((int)sx[i] - 80) * 256 / sz[i] + 80;
        int screen_y = ((int)sy[i] - 64) * 256 / sz[i] + 64;

        if (screen_x >= 0 && screen_y >= 0 && screen_x < ST7735R_WIDTH && screen_y < ST7735R_HEIGHT) {
          uint8_t r, g, b;
          r = g = b = 255 - sz[i];
          b = (b < 128) ? (b*2) : 255;
          DisplayPixel(screen_x, screen_y, r, g, b);
        } 
        else {
          sz[i] = 0; // Out of screen, die.
        }
      }
    }
  }

  // Render enemy (Test)
  RenderEnemy(50, 50);
  
  // Render explosions
  g_Explosions.UpdateRender(time);
  
  // Draw player
  RenderPlayerShip(g_PlayerX, g_PlayerY);


  DisplayEndDraw();
  END_TFT();
}


