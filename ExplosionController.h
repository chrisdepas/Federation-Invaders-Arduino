#ifndef __EXPLOSION_CONTROLLER_H__
#define __EXPLOSION_CONTROLLER_H__

#include "Vector.h"

#define MAX_EXPLOSION_EFFECT 3
#define MAX_EXPLOSION_TIME 300

struct Explosion {
  boolean bActive;
  time_t createTime;
  int lastRadius;
  Vector2i origin;
  
  void Clear(boolean bDraw) { 
    if (lastRadius > 0 && bDraw) {
      Display_FilledCircle(origin.x, origin.y, lastRadius + 1, 0, 0, 0); 
    }
    bActive = createTime = lastRadius = origin.x = origin.y = 0; 
  }
  
  /* Initialise as new explosion */
  void Init(time_t curTime, int x, int y) {
    createTime = curTime;
    bActive = true;
    lastRadius = 0;
    origin.x = x;
    origin.y = y;
  }
  
  /* Draw, return false if expired */
  boolean Draw(time_t curTime) {
    if (lastRadius > 0) {
      // Clear last circle
      Display_FilledCircle(origin.x, origin.y, lastRadius + 1, 0, 0, 0); 
    }
    
    // Check for expiry
    time_t delta = curTime - createTime;
    if (delta > MAX_EXPLOSION_TIME) { 
      return true; 
    }
    
    // Render expanding circle
    float pctDelta = delta / (float)MAX_EXPLOSION_TIME;
    int g = (int)(pctDelta * 200);
    int rad = (int)(pctDelta * 8);
    if (rad > 0) {
      Display_Circle(origin.x, origin.y, rad, 255, g, 0); 
      Display_Circle(origin.x, origin.y, rad + 1, 255, g + 50, 0); 
      lastRadius = rad;
    }
    return false;
  }
};

class ExplosionController {
  Explosion explosions[MAX_EXPLOSION_EFFECT];
  boolean bExploding;
  
public:

  void Init() {
    bExploding = false;
    for (int i = 0; i < MAX_EXPLOSION_EFFECT; i++) {
      explosions[i].Clear(false);
    }
  }

  void UpdateRender(time_t curTime) {
    if (!bExploding) {
      return;
    }
    
    bExploding = false;
    for (int i = 0; i < MAX_EXPLOSION_EFFECT; i++) {
      if (!explosions[i].bActive) {
        continue;
      }
      bExploding = true; 
      if (explosions[i].Draw(curTime)) {
        explosions[i].Clear(true);
      }
    }
  }
  boolean hasSlots() {
    for (int i = 0; i < MAX_EXPLOSION_EFFECT; i++) {
      if (!explosions[i].bActive) {
        return true;
      }
    }
    return false;
  }
  
  void CreateExplosion(time_t time, int x, int y) {
    bExploding = true;
    for (int i = 0; i < MAX_EXPLOSION_EFFECT; i++) {
      if (!explosions[i].bActive) {
        explosions[i].Init(time, x, y);
        return;
      }
    }
  }
  
};




#endif
