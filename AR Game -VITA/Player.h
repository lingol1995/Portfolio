#ifndef _PLAYER_H
#define _PLAYER_H

#include <maths\aabb.h>
#include <graphics/renderer_3d.h>

#include "GameObject.h"
#include "Controller.h"
#include "samples\ar_app\build\vs2015\Sprites.h"
#include "Bullet.h"

namespace gef
{
	class Renderer3D;
	class Mesh;
	class RenderTarget;
	class Aabb;
}

class Player : public GameObject
{
public:
	Player();

	void Init(gef::Platform& platform_);		//Initialises Player
	void Shoot(Controller& controller_);		//Shoot when button pressed
	void updateHealth();						//Update health and power bars
	void bulletReload();						//Reload bullets

	int bulletNo;								//Current bullet number
	int bulletsLeft;							//Bullets remained
	int max_bullets;							//Maximum bullets
	float bar_size;								//size of health and power bar backings

	gef::Vector4 barPosition;					//Position of sprite bar
	gef::Vector4 bar2Position;					//Position of sprite bar 2

	Sprites healthBar;							//Health bar sprite
	Sprites healthBarBack;						//Health bar backing sprite
	Sprites powerBar;							//Power bar sprite
	Sprites powerBarBack;						//Power bar backing sprite

	Bullet bullet;								//Bullet object
	
	bool reload;								//Do you need to reload?

};
#endif