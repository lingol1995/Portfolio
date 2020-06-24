#include "Player.h"
#include <graphics/mesh.h>
#include <graphics/renderer_3d.h>

Player::Player()
{
}

//Initialise player
void Player::Init(gef::Platform& platform_)
{
	reload = false;														//Bullets haven't run out
	health = 100.0f;													//Health is full
	max_bullets = 20;													//Maximum number of bullets
	CreateTransform(-0.1f, 0.0f, -0.4f);								//Initial Transform creation for player
	bulletNo = 0;														//Number of Bullets
	bulletsLeft = 19;													//Bullets that are left
	bullet.Init(platform_, max_bullets);								//Initialise bullets
	bar_size = 100.0f;													//Size of health bars
	barPosition = gef::Vector4(600.0f, 510.0f, -0.9f);					//Positions of health bar
	bar2Position = gef::Vector4(710.0f, 510.0f, -0.9f);					//Position of power bar
	healthBarBack.HealthBar(20.0f, bar_size, barPosition, 0xff000000);	//Set up backing of health bar
	powerBarBack.HealthBar(20.0f, bar_size, bar2Position, 0xff000000);	//Set up backing of power bar
}

//Updating health and power bar since they increase/decrease
void Player::updateHealth()
{
	healthBar.HealthBar(20.0f, health, barPosition, 0xff00ff00);		//Setting up health bar, bar has health as its width
	powerBar.HealthBar(20.0f, Power, bar2Position, 0xff0000ff);			//Setting up power bar, bar has Power as its width
}

//Reload bullets
void Player::bulletReload()
{
	bulletNo = 0;				//On bullet number 1
	bulletsLeft = 19;			//19 bullets left
	reload = false;				//No longer need to reload
}

void Player::Shoot(Controller& controller_)
{
	if (reload == false)							//If player has bullets
	{
		if (controller_.Shoot() == true)			//Tell if triangle button pressed
		{
			bullet.Shoot(transform(), bulletNo);	//Shoot bullet
			if (bulletNo >= 19)						//If bullets are finished
			{
				reload = true;						//Need to reload
			}
			bulletsLeft = 19 - bulletNo;			//Subtract to get the remaining bullets
		}
	}
}


