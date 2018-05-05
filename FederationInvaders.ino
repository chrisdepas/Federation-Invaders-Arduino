/*
**   'Federation Invaders'
**  Attempt at a Space invaders clone
**  Chris De Pasquale
**  Jan 2018
**  Last edit 05/05/18
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

#define BUTTON_PIN 6
#define POTENTIOMETER_PIN A3
#define PlayerButtonInput() digitalRead(BUTTON_PIN) == HIGH
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

  DisplayClear(0, 0, 0);

  DisplayEndDraw();
  END_TFT();


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


  // Setup pushbutton
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  // Read input
  float playerHorizontal = PlayerHorizontalInput();
  g_PlayerX = playerHorizontal * ST7735R_WIDTH;

  boolean overdrive = PlayerButtonInput();
  static boolean lastOverdrive = PlayerButtonInput();

  time_t time = Time();

  // Update sounds
  g_TonePlayer.Update(time);

  BEGIN_TFT();

  /* Render star background
  Source: https://github.com/juj/ST7735R/blob/master/Test4_Starfield.h */
  DisplayBeginPixels();
  uint8_t spawnDepthVariation = 255;
  if (lastOverdrive && !overdrive) {
    DisplayClear(0, 0, 0);
  }
  for(int i = 0; i < NSTARS; ++i) {
    if (sz[i] <= 1) {
      sx[i] = 80 - 64 + (random() & 127);
      sy[i] = random() & 127;
      sz[i] = spawnDepthVariation--;
    }
    else {
      int old_screen_x = ((int)sx[i] - 80) * 256 / sz[i] + 80;
      int old_screen_y = ((int)sy[i] - 64) * 256 / sz[i] + 64;

      if (!overdrive) {
        DisplayPixel(old_screen_x, old_screen_y, 0, 0, 0);

        if (i % 13 == 0) {
          DisplayPixel(old_screen_x+1, old_screen_y  , 0, 0, 0);
          DisplayPixel(old_screen_x,   old_screen_y+1, 0, 0, 0);
          DisplayPixel(old_screen_x+1, old_screen_y+1, 0, 0, 0);
        }
      }

      sz[i] -= 2;
      if (sz[i] > 1) {
        int screen_x = ((int)sx[i] - 80) * 256 / sz[i] + 80;
        int screen_y = ((int)sy[i] - 64) * 256 / sz[i] + 64;

        if (screen_x >= 0 && screen_y >= 0 && screen_x < ST7735R_WIDTH && screen_y < ST7735R_HEIGHT) {
          uint8_t r, g, b;
          r = g = b = 255 - sz[i];
          if (i % 6 == 0) {
            // Purple, 1/6
            r = (r < 128) ? (r*2) : 255;
            b = (b < 128) ? (b*2) : 255;

          } else if (i % 7 == 0) {
            // Red, 1/7
            r = (r < 85) ? (r*3) : 255;

          } else if (i % 11 == 0) {
            // Yellow, 1/11
            r = (r < 185) ? (r+70) : 255;
            g = (g < 185) ? (g+70) : 255;

          } else if (i % 13 == 0) {
            // White, 1/13
            r = (r < 128) ? (r*2) : 255;
            g = (g < 128) ? (g*2) : 255;
            b = (b < 128) ? (b*2) : 255;
            DisplayPixel(screen_x,   screen_y,   r, g, b);
            DisplayPixel(screen_x+1, screen_y,   r, g, b);
            DisplayPixel(screen_x,   screen_y+1, r, g, b);
            DisplayPixel(screen_x+1, screen_y+1, r, g, b);
            continue;

          } else {
            // Blue (Default)
            b = (b < 128) ? (b*2) : 255;

          }
          DisplayPixel(screen_x, screen_y, r, g, b);
        }
        else {
          sz[i] = 0; // Out of screen, die.
        }
      }
    }
  }
  lastOverdrive = overdrive;

  // Render enemy (Test)
  RenderEnemy(50, 50);

  // Render explosions
  g_Explosions.UpdateRender(time);

  // Draw player
  RenderPlayerShip(g_PlayerX, g_PlayerY);
  if (PlayerButtonInput()) {
    static int offset_3 = 0, last_offset3 = 0;
    static int offset_2 = 0, last_offset2 = 0;
    static int offset_1 = 0, last_offset1 = 0;
    static int offset_size = 0, last_offsetsize = 0;

    offset_size = (int)((sin(time/30) * 1.5) - 0.5);
    offset_3 = (int)(sin(time/70) * 2);// [-Radius, Radius]
    offset_2 = (int)(sin(time/100) * 2);//sin(time/100) * 2;
    offset_1 = (int)(sin(time/300) * 2);//sin(time/120) * 2;//((time/100) % (PLAYER_PROJECTILE_TRAIL_RADIUS_3*2 + 1)) - PLAYER_PROJECTILE_TRAIL_RADIUS_3;


    if (offset_3 != last_offset3 || offset_2 != last_offset2 || offset_1 != last_offset1 || offset_size != last_offsetsize) {
      ClearProjectilePlayer(60, 80, last_offsetsize, last_offset1, last_offset2, last_offset3);
    }
    last_offset3 = offset_3;
    last_offset2 = offset_2;
    last_offset1 = offset_1;
    last_offsetsize = offset_size;

    RenderProjectilePlayer(60, 80, offset_size, offset_1, offset_2, offset_3);
  }


  DisplayEndDraw();
  END_TFT();
}


