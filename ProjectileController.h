#ifndef __PROJECTILECONTROLLER_H__
#define __PROJECTILECONTROLLER_H__

#include "Vector.h"
#include "Time.h"

#define MAX_PROJECTILES 3

struct Projectile {
  Vector2i origin;
  boolean isPlayerProjectile;
  
  void Draw(time_t curTime) {
    
  }
};

class ProjectileController {
  
  void EnemyShootProjectile() {
  }
  void PlayerShootProjectile() {
  }
  
  void Init(time_t time);
  void Update(int playerX, int playerY);
};


#endif
