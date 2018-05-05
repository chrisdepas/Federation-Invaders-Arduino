#ifndef __GAMEDRAW_H__
#define __GAMEDRAW_H__

#include <TFTFaster.h>
#include <SPI.h>
#include "Vector.h"

#define ENEMY_R 100
#define ENEMY_G 255
#define ENEMY_B 100


/*  Player Ship
          ,-> Gun (Rectangle)
       ||/
       ||    ,-> Saucer section (Circle)
    ,`    `, /
   .        . 
   `,  __  ,` .---> Body Main (Rectangle)
 _    |  |--`_
 | |__|__|__| |
 | |________| |
 |_| \      |_| -> Engine (Rectangle x2)
      `-> Body back (Rectangle)
 */

// Saucer section
#define PLAYER_SAUCER_RADIUS 6
#define PLAYER_SAUCER_R 0xdd
#define PLAYER_SAUCER_G 0xd7
#define PLAYER_SAUCER_B 0xd7
// Engines
#define PLAYER_ENGINE_WIDTH 2
#define PLAYER_ENGINE_HEIGHT 10
#define PLAYER_ENGINE_R 0x77
#define PLAYER_ENGINE_G 0x70
#define PLAYER_ENGINE_B 0x70
// Body main
#define PLAYER_BODY_MAIN_WIDTH 2
#define PLAYER_BODY_MAIN_HEIGHT 8
#define PLAYER_BODY_MAIN_R 0xb2
#define PLAYER_BODY_MAIN_G 0xad
#define PLAYER_BODY_MAIN_B 0xad
// Body back
#define PLAYER_BODY_BACK_WIDTH 8
#define PLAYER_BODY_BACK_HEIGHT 4
#define PLAYER_BODY_BACK_R 0xa0
#define PLAYER_BODY_BACK_G 0x9f
#define PLAYER_BODY_BACK_B 0x9f
// Gun
#define PLAYER_GUN_WIDTH 2
#define PLAYER_GUN_HEIGHT 4
#define PLAYER_GUN_R 0x96
#define PLAYER_GUN_G 0x96
#define PLAYER_GUN_B 0x96

// Extra height occurs when engines stick out behind back of body
#define EXTRA_HEIGHT ((PLAYER_BODY_BACK_HEIGHT/2)- (PLAYER_ENGINE_HEIGHT/2) > 0 ? (PLAYER_ENGINE_HEIGHT/2) - (PLAYER_BODY_BACK_HEIGHT/2) : 0)

// Max width (At engine) and max height (top of gun)
#define PLAYER_WIDTH PLAYER_BODY_BACK_WIDTH + PLAYER_ENGINE_WIDTH + 1
#define PLAYER_HEIGHT PLAYER_BODY_BACK_HEIGHT + PLAYER_BODY_MAIN_HEIGHT + PLAYER_SAUCER_RADIUS + PLAYER_SAUCER_RADIUS + PLAYER_GUN_HEIGHT + EXTRA_HEIGHT

void RenderPlayerShip(int x, int y) {
  static int lastX = -1;
  static int lastY = -1;
  
  /* Clear player */
  if (lastX != x || lastY != y) {
    DisplayBeginRect(lastX, lastY, lastX + PLAYER_BODY_BACK_WIDTH, lastY + PLAYER_BODY_BACK_HEIGHT);
  
    DisplayFillRect(lastX, 
                     lastY, 
                     lastX + PLAYER_BODY_BACK_WIDTH, 
                     lastY + PLAYER_BODY_BACK_HEIGHT, 
                     0, 0, 0);
  
    // Engine Left
    DisplayFillRect(lastX - PLAYER_ENGINE_WIDTH-1, 
                     lastY - (PLAYER_ENGINE_HEIGHT/2) + (PLAYER_BODY_BACK_HEIGHT/2), 
                     lastX - 1, 
                     lastY + (PLAYER_ENGINE_HEIGHT/2) + (PLAYER_BODY_BACK_HEIGHT/2), 
                     0, 0, 0);
  
    // Engine Right 
    DisplayFillRect(lastX + PLAYER_BODY_BACK_WIDTH + 1, 
                     lastY - (PLAYER_ENGINE_HEIGHT/2) + (PLAYER_BODY_BACK_HEIGHT/2), 
                     lastX + PLAYER_BODY_BACK_WIDTH + PLAYER_ENGINE_WIDTH + 1, 
                     lastY + (PLAYER_ENGINE_HEIGHT/2) + (PLAYER_BODY_BACK_HEIGHT/2), 
                     0, 0, 0);
  
    // Player body main centre
    DisplayFillRect(lastX + (PLAYER_BODY_BACK_WIDTH/2) - PLAYER_BODY_MAIN_WIDTH, 
                     lastY + PLAYER_BODY_BACK_HEIGHT, 
                     lastX + (PLAYER_BODY_BACK_WIDTH/2) + PLAYER_BODY_MAIN_WIDTH, 
                     lastY + PLAYER_BODY_BACK_HEIGHT + PLAYER_BODY_MAIN_HEIGHT, 
                     0, 0, 0);
    // Saucer
    DisplayFilledCircle(lastX + (PLAYER_BODY_BACK_WIDTH/2), 
                         lastY + PLAYER_BODY_BACK_HEIGHT + PLAYER_BODY_MAIN_HEIGHT + PLAYER_SAUCER_RADIUS, 
                         PLAYER_SAUCER_RADIUS,
                         0, 0, 0);
                         
                         
    // Gun Type 1
    DisplayFillRect(lastX + (PLAYER_BODY_BACK_WIDTH/2) - (PLAYER_GUN_WIDTH/2), 
                     lastY + PLAYER_BODY_BACK_HEIGHT + PLAYER_BODY_MAIN_HEIGHT + PLAYER_SAUCER_RADIUS + PLAYER_SAUCER_RADIUS,
                     lastX + (PLAYER_BODY_BACK_WIDTH/2) + (PLAYER_GUN_WIDTH/2) , 
                     lastY + PLAYER_BODY_BACK_HEIGHT + PLAYER_BODY_MAIN_HEIGHT + PLAYER_SAUCER_RADIUS + PLAYER_SAUCER_RADIUS + PLAYER_GUN_HEIGHT, 
                     0, 0, 0);
    lastX = x;
    lastY = y;
  }
  DisplayBeginRect(x, y, x + PLAYER_BODY_BACK_WIDTH, y + PLAYER_BODY_BACK_HEIGHT);
  
  // Back
  DisplayFillRect(x, 
                   y, 
                   x + PLAYER_BODY_BACK_WIDTH, 
                   y + PLAYER_BODY_BACK_HEIGHT, 
                   PLAYER_BODY_BACK_R, PLAYER_BODY_BACK_G, PLAYER_BODY_BACK_B);

  // Engine Left
  DisplayFillRect(x - PLAYER_ENGINE_WIDTH-1, 
                   y - (PLAYER_ENGINE_HEIGHT/2) + (PLAYER_BODY_BACK_HEIGHT/2), 
                   x - 1, 
                   y + (PLAYER_ENGINE_HEIGHT/2) + (PLAYER_BODY_BACK_HEIGHT/2), 
                   PLAYER_ENGINE_R, PLAYER_ENGINE_G, PLAYER_ENGINE_B);

  // Engine Right 
  DisplayFillRect(x + PLAYER_BODY_BACK_WIDTH + 1, 
                   y - (PLAYER_ENGINE_HEIGHT/2) + (PLAYER_BODY_BACK_HEIGHT/2), 
                   x + PLAYER_BODY_BACK_WIDTH + PLAYER_ENGINE_WIDTH + 1, 
                   y + (PLAYER_ENGINE_HEIGHT/2) + (PLAYER_BODY_BACK_HEIGHT/2), 
                   PLAYER_ENGINE_R, PLAYER_ENGINE_G, PLAYER_ENGINE_B);

  // Body main 
  DisplayFillRect(x + (PLAYER_BODY_BACK_WIDTH/2) - PLAYER_BODY_MAIN_WIDTH, 
                   y + PLAYER_BODY_BACK_HEIGHT, 
                   x + (PLAYER_BODY_BACK_WIDTH/2) + PLAYER_BODY_MAIN_WIDTH, 
                   y + PLAYER_BODY_BACK_HEIGHT + PLAYER_BODY_MAIN_HEIGHT, 
                   PLAYER_BODY_BACK_R, PLAYER_BODY_BACK_G, PLAYER_BODY_BACK_B);
                   
  // Saucer section
  DisplayFilledCircle(x + (PLAYER_BODY_BACK_WIDTH/2), 
                       y + PLAYER_BODY_BACK_HEIGHT + PLAYER_BODY_MAIN_HEIGHT + PLAYER_SAUCER_RADIUS, 
                       PLAYER_SAUCER_RADIUS,
                       PLAYER_SAUCER_R, PLAYER_SAUCER_G, PLAYER_SAUCER_B);
                       
                       
  // Gun
  DisplayFillRect(x + (PLAYER_BODY_BACK_WIDTH/2) - (PLAYER_GUN_WIDTH/2), 
                   y + PLAYER_BODY_BACK_HEIGHT + PLAYER_BODY_MAIN_HEIGHT + PLAYER_SAUCER_RADIUS + PLAYER_SAUCER_RADIUS,
                   x + (PLAYER_BODY_BACK_WIDTH/2) + (PLAYER_GUN_WIDTH/2) , 
                   y + PLAYER_BODY_BACK_HEIGHT + PLAYER_BODY_MAIN_HEIGHT + PLAYER_SAUCER_RADIUS + PLAYER_SAUCER_RADIUS + PLAYER_GUN_HEIGHT, 
                   PLAYER_GUN_R, PLAYER_GUN_G, PLAYER_GUN_B); 
}


#define ENEMY_WIDTH 6
#define ENEMY_HEIGHT 6

void RenderEnemy(int x, int y) {
  // TODO: Convert to bitmap

  DisplayPixel(x  , y  , ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+2, y  , ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+3, y  , ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+5, y  , ENEMY_R, ENEMY_G, ENEMY_B);

  DisplayPixel(x+4, y+1, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+1, y+1, ENEMY_R, ENEMY_G, ENEMY_B);

  DisplayPixel(x+4, y+2, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+3, y+2, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+2, y+2, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+1, y+2, ENEMY_R, ENEMY_G, ENEMY_B);

  DisplayPixel(x+5, y+3, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+3, y+3, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+2, y+3, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x  , y+3, ENEMY_R, ENEMY_G, ENEMY_B);

  DisplayPixel(x+4, y+4, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+3, y+4, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+2, y+4, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+1, y+4, ENEMY_R, ENEMY_G, ENEMY_B);

  DisplayPixel(x+3, y+5, ENEMY_R, ENEMY_G, ENEMY_B);
  DisplayPixel(x+2, y+5, ENEMY_R, ENEMY_G, ENEMY_B);
}

#define PLAYER_PROJECTILE_HEAD_RADIUS 1
#define PLAYER_PROJECTILE_BODY_LENGTH 6
#define PLAYER_PROJECTILE_BODY_WIDTH PLAYER_PROJECTILE_HEAD_RADIUS + PLAYER_PROJECTILE_HEAD_RADIUS
#define PLAYER_PROJECTILE_TAIL_SIZE 2
#define PLAYER_PROJECTILE_WIDTH PLAYER_PROJECTILE_HEAD_RADIUS + PLAYER_PROJECTILE_HEAD_RADIUS + PLAYER_PROJECTILE_TAIL_SIZE + PLAYER_PROJECTILE_TAIL_SIZE + 3
#define PLAYER_PROJECTILE_HEIGHT PLAYER_PROJECTILE_BODY_LENGTH
#define PLAYER_PROJECTILE_R 100
#define PLAYER_PROJECTILE_G 130
#define PLAYER_PROJECTILE_B 50

#define PLAYER_PROJECTILE_TRAIL_R 255
#define PLAYER_PROJECTILE_TRAIL_G_1 20
#define PLAYER_PROJECTILE_TRAIL_G_2 110
#define PLAYER_PROJECTILE_TRAIL_G_3 210
#define PLAYER_PROJECTILE_TRAIL_B 0
#define PLAYER_PROJECTILE_TRAIL_RADIUS_1 2
#define PLAYER_PROJECTILE_TRAIL_RADIUS_2 1
#define PLAYER_PROJECTILE_TRAIL_RADIUS_3 0

// Size is height of triangle rendered
#define ENEMY_PROJECTILE_SIZE PLAYER_PROJECTILE_TAIL_SIZE
#define ENEMY_PROJECTILE_WIDTH ENEMY_PROJECTILE_SIZE + ENEMY_PROJECTILE_SIZE
#define ENEMY_PROJECTILE_HEIGHT ENEMY_PROJECTILE_SIZE + ENEMY_PROJECTILE_SIZE
#define ENEMY_PROJECTILE_R 191
#define ENEMY_PROJECTILE_G 255
#define ENEMY_PROJECTILE_B 255

void ClearProjectilePlayer(int x, int y, int offset_size, int offset_1, int offset_2, int offset_3) {
  
  // Render flame
  Vector2i drawPos(x + PLAYER_PROJECTILE_BODY_WIDTH/2, y - PLAYER_PROJECTILE_TRAIL_RADIUS_2);
  if (PLAYER_PROJECTILE_TRAIL_RADIUS_1 - offset_size > 0) {
    DisplayBeginRect(drawPos.x - PLAYER_PROJECTILE_TRAIL_RADIUS_1, 
                     drawPos.y - PLAYER_PROJECTILE_TRAIL_RADIUS_1, 
                     drawPos.x + PLAYER_PROJECTILE_TRAIL_RADIUS_1, 
                     drawPos.y + PLAYER_PROJECTILE_TRAIL_RADIUS_1);
    DisplayFilledCircle(drawPos.x, drawPos.y, 
                         PLAYER_PROJECTILE_TRAIL_RADIUS_1 - offset_size, 
                         0, 0, 0);
  }

  if (PLAYER_PROJECTILE_TRAIL_RADIUS_2 - offset_size > 0) {   
    drawPos.y -= (PLAYER_PROJECTILE_TRAIL_RADIUS_1);
    drawPos.x += offset_2;
    DisplayFilledCircle(drawPos.x, drawPos.y, 
                         PLAYER_PROJECTILE_TRAIL_RADIUS_2 - offset_size,
                         0, 0, 0);
    if (PLAYER_PROJECTILE_TRAIL_RADIUS_3 - offset_size > 0) {
      drawPos.y -= (PLAYER_PROJECTILE_TRAIL_RADIUS_2);
      drawPos.x += offset_3;
      DisplayFilledCircle(drawPos.x, drawPos.y, 
                           PLAYER_PROJECTILE_TRAIL_RADIUS_3 - offset_size, 
                           0, 0, 0);
    }
  }
  
  DisplayFillRect(x, 
                   y, 
                   x + PLAYER_PROJECTILE_HEAD_RADIUS + PLAYER_PROJECTILE_HEAD_RADIUS, 
                   y + PLAYER_PROJECTILE_BODY_LENGTH, 
                   0, 0, 0);
               
  DisplayFilledCircle(x + PLAYER_PROJECTILE_HEAD_RADIUS,
                       y + PLAYER_PROJECTILE_BODY_LENGTH,
                       PLAYER_PROJECTILE_HEAD_RADIUS,
                       0, 0, 0);
 
 for (int i = PLAYER_PROJECTILE_TAIL_SIZE; i > 0; i--) {
   for (int j = 0; j <= i; j++) { 
     DisplayPixel(x+PLAYER_PROJECTILE_HEAD_RADIUS-1-j, y + (PLAYER_PROJECTILE_TAIL_SIZE - i), 0, 0, 0);
     DisplayPixel(x+PLAYER_PROJECTILE_HEAD_RADIUS+1+j, y + (PLAYER_PROJECTILE_TAIL_SIZE - i), 0, 0, 0);
   }
 }   
}
 
void RenderProjectilePlayer(int x, int y, int offset_size, int offset_1, int offset_2, int offset_3) {
  
  // Render flame
  Vector2i drawPos(x + PLAYER_PROJECTILE_BODY_WIDTH/2, y - PLAYER_PROJECTILE_TRAIL_RADIUS_2);
  if (PLAYER_PROJECTILE_TRAIL_RADIUS_1 - offset_size > 0) {
    DisplayBeginRect(drawPos.x - PLAYER_PROJECTILE_TRAIL_RADIUS_1, 
                     drawPos.y - PLAYER_PROJECTILE_TRAIL_RADIUS_1, 
                     drawPos.x + PLAYER_PROJECTILE_TRAIL_RADIUS_1, 
                     drawPos.y + PLAYER_PROJECTILE_TRAIL_RADIUS_1);
    DisplayFilledCircle(drawPos.x, drawPos.y, 
                         PLAYER_PROJECTILE_TRAIL_RADIUS_1 - offset_size, 
                         PLAYER_PROJECTILE_TRAIL_R, PLAYER_PROJECTILE_TRAIL_G_1, PLAYER_PROJECTILE_TRAIL_B);
  }

  if (PLAYER_PROJECTILE_TRAIL_RADIUS_2 - offset_size > 0) {   
    drawPos.y -= (PLAYER_PROJECTILE_TRAIL_RADIUS_1);
    drawPos.x += offset_2;
    DisplayFilledCircle(drawPos.x, drawPos.y, 
                         PLAYER_PROJECTILE_TRAIL_RADIUS_2 - offset_size,
                         PLAYER_PROJECTILE_TRAIL_R, PLAYER_PROJECTILE_TRAIL_G_2, PLAYER_PROJECTILE_TRAIL_B);
    if (PLAYER_PROJECTILE_TRAIL_RADIUS_3 - offset_size > 0) {
      drawPos.y -= (PLAYER_PROJECTILE_TRAIL_RADIUS_2);
      drawPos.x += offset_3;
      DisplayFilledCircle(drawPos.x, drawPos.y, 
                           PLAYER_PROJECTILE_TRAIL_RADIUS_3 - offset_size, 
                           PLAYER_PROJECTILE_TRAIL_R, PLAYER_PROJECTILE_TRAIL_G_3, PLAYER_PROJECTILE_TRAIL_B);
    }
  }
  
  DisplayFillRect(x, 
                   y, 
                   x + PLAYER_PROJECTILE_HEAD_RADIUS + PLAYER_PROJECTILE_HEAD_RADIUS, 
                   y + PLAYER_PROJECTILE_BODY_LENGTH, 
                   PLAYER_PROJECTILE_R, PLAYER_PROJECTILE_G, PLAYER_PROJECTILE_B);
               
  DisplayFilledCircle(x + PLAYER_PROJECTILE_HEAD_RADIUS,
                       y + PLAYER_PROJECTILE_BODY_LENGTH,
                       PLAYER_PROJECTILE_HEAD_RADIUS,
                       PLAYER_PROJECTILE_R, PLAYER_PROJECTILE_G, PLAYER_PROJECTILE_B);
 
 for (int i = PLAYER_PROJECTILE_TAIL_SIZE; i > 0; i--) {
   for (int j = 0; j <= i; j++) { 
     DisplayPixel(x+PLAYER_PROJECTILE_HEAD_RADIUS-1-j, y + (PLAYER_PROJECTILE_TAIL_SIZE - i), PLAYER_PROJECTILE_R, PLAYER_PROJECTILE_G, PLAYER_PROJECTILE_B);
     DisplayPixel(x+PLAYER_PROJECTILE_HEAD_RADIUS+1+j, y + (PLAYER_PROJECTILE_TAIL_SIZE - i), PLAYER_PROJECTILE_R, PLAYER_PROJECTILE_G, PLAYER_PROJECTILE_B);
   }
 }   
                       
}

void ClearProjectileEnemy(int x, int y) {
  for (int i = ENEMY_PROJECTILE_SIZE; i > 0; i--) {
   for (int j = 0; j <= i; j++) { 
     DisplayPixel(x-1-j, y + (ENEMY_PROJECTILE_SIZE - j), 0, 0, 0);
     DisplayPixel(x+1+j, y + (ENEMY_PROJECTILE_SIZE - j), 0, 0, 0);
   }
 }
}
void RenderProjectileEnemy(int x, int y) {
  for (int i = ENEMY_PROJECTILE_SIZE; i > 0; i--) {
   for (int j = 0; j <= i; j++) { 
     DisplayPixel(x-1-j, y - j, ENEMY_PROJECTILE_R, ENEMY_PROJECTILE_G, ENEMY_PROJECTILE_B);
     DisplayPixel(x+1+j, y - j, ENEMY_PROJECTILE_R, ENEMY_PROJECTILE_G, ENEMY_PROJECTILE_B);
   }
 }
}




#endif
