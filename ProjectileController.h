#ifndef __PROJECTILECONTROLLER_H__
#define __PROJECTILECONTROLLER_H__

#include "Vector.h"
#include "Time.h"
#include "GameDraw.h"

#define MAX_PLAYER_PROJECTILES 3
#define MAX_ENEMY_PROJECTILES MAX_PLAYER_PROJECTILES

// Pixels/second
#define PROJECTILE_VELOCITY_DEFAULT 50

struct BaseProjectile {
  Vector2i origin;
  int velocity;
  boolean isActive;
  
  void Init(int x, int y, int verticalVelocity) {
    origin.x = x;
    origin.y = y;
    velocity = verticalVelocity;
    isActive = true;
  }
  
  void Clear() { isActive = false; }
  
  int getWidth();
  int getHeight();
  
  
};

struct EnemyProjectile : public BaseProjectile {
  
  int getWidth() { return ENEMY_PROJECTILE_WIDTH; }
  int getHeight() { return ENEMY_PROJECTILE_HEIGHT; }
  
  // Returns TRUE when projectile should be destroyed
  boolean DrawUpdate(int x, int y) {
    ClearProjectileEnemy(origin.x, origin.y);
    origin.x = x;
    origin.y = y;
    RenderProjectileEnemy(origin.x, origin.y);
  }
};

struct Projectile : public BaseProjectile {  
  int trailOffset[4]; // size offset, and offset for trail 1 2, 3 
  
  void Init(int x, int y, int verticalVelocity) {
    origin.x = x;
    origin.y = y;
    velocity = verticalVelocity;
    isActive = true;
    trailOffset[0] = trailOffset[1] = trailOffset[2] = trailOffset[3] = 0;
  }
  
  int getWidth() { return PLAYER_PROJECTILE_WIDTH; }
  int getHeight() { return PLAYER_PROJECTILE_HEIGHT; }
  
  // Returns TRUE when projectile should be destroyed
  boolean DrawUpdate(float fDeltaSeconds, int curOffsetSize, int curOffset1, int curOffset2, int curOffset3) {

    if (curOffsetSize != trailOffset[0] || curOffset1 != trailOffset[1] || curOffset2 != trailOffset[2] || curOffset3 != trailOffset[3]) {
      ClearProjectilePlayer(origin.x, origin.y, trailOffset[0], trailOffset[1], trailOffset[2], trailOffset[3]);
      trailOffset[0] = curOffsetSize;
      trailOffset[1] = curOffset1;
      trailOffset[2] = curOffset2;
      trailOffset[3] = curOffset3;
    }
    
    origin.y += fDeltaSeconds * velocity;
    RenderProjectilePlayer(origin.x, origin.y, trailOffset[0], trailOffset[1], trailOffset[2], trailOffset[3]);
  }
};

class ProjectileController {
  Projectile enemyProjectiles[MAX_ENEMY_PROJECTILES];
  Projectile playerProjectiles[MAX_PLAYER_PROJECTILES];
  time_t lastUpdateTime;
  
public:

  void EnemyShootProjectile(int x, int y) {
  }
  
  void PlayerShootProjectile(int x, int y) {
  }
  
  void Init(time_t time) {
    lastUpdateTime = time;
  }
  void Update(int playerX, int playerY, time_t time) {
    time_t timeDelta = time - lastUpdateTime;
  }
  
  boolean playerCanShoot() { return false; }
};


#endif
