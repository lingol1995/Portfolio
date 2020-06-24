#include "Enemy.h"
#include <system/platform.h>

//Initialising enemy
Enemy::Enemy()
{
	direction = left_;			//Enemy starts moving left
	Power = 0;					//Power initialised
	health = 100.0f;			//Health is full
	powerLevel = 1.0f;			//Power multiplied by this when level changes
	backingbarSize = 100.0f;	//Health and power bars sizes
	shoot = false;				//Can't shoot
}

//Move enemy between point 1 and 2 (markers), and position above point 3 (marker)
void Enemy::movement(gef::Platform& platform, gef::Vector4 point1, gef::Vector4 point2, gef::Vector4 point3)
{
	enemy_transform.SetTranslation(gef::Vector4(transform().GetTranslation().x(), point3.y() + 0.1f, point3.z()));	//Enemy shows above book
	HealthandPowerBar();																							//Sets up health and power bars and also move them along too
	//////////////////////ENEMY MOVEMENT//////////////////////////////

	if (point1.x() <= point2.x())										//If point 1 is to the left of point 2
	{
		switch (direction)												//Enemy moves left and right between markers
		{
		case left_:														//Moving Left
			velocity.set_value(-0.002f, 0.0f, 0.0f);
			if (transform().GetTranslation().x() <= point1.x())			//If enemy has reached point1
			{
				Power += 10 * powerLevel;								//Enemy powers up at each turn
				direction = right_;										//Change Direction
			}
			break;

		case right_:													//Moving right
			velocity.set_value(0.002f, 0.0f, 0.0f);						
			if (transform().GetTranslation().x() >= point2.x())			//If enemy reaches point2
			{
				Power += 10 * powerLevel;								//Power up
				direction = left_;										//Change Direction
			}
			break;
		}
	}

	else																//If cards have been switched
		switch (direction)												//Enemy moves left and right between markers
		{
		case left_:														//Moving Left
			velocity.set_value(-0.002f, 0.0f, 0.0f);
			if (transform().GetTranslation().x() <= point2.x())			//When reaches point 2
			{
				Power += 10 * powerLevel;								//Enemy powers up at each turn
				direction = right_;										//Change Direction
			}
			break;

		case right_:													//Moving right
			velocity.set_value(0.002f, 0.0f, 0.0f);						
			if (transform().GetTranslation().x() >= point1.x())			//When it reaches point 1
			{
				Power += 10 * powerLevel;								//Power Up
				direction = left_;										//Change Direction
			}
			break;
		}

	set_transform(enemy_transform);										//Give this transform to the enemy
	Move(velocity);														//Move enemy
}

void Enemy::HealthandPowerBar()
{
	gef::Vector4 enemyPos = gef::Vector4(600 * enemy_transform.GetTranslation().x() + 500, enemy_transform.GetTranslation().y() + 20, -0.9f);		//Make power bar move above and with enemy
	gef::Vector4 enemyPosAbove = gef::Vector4(600 * enemy_transform.GetTranslation().x() + 500, enemy_transform.GetTranslation().y() + 40, -0.9f);	//Make health bar move above and with enemy

	if (Power < 100)																//Stop when around 100
	{
		powerBar.HealthBar(20.0f, Power, enemyPos, 0xffff0000);						//Position health bar and change height, colour etc.
		powerBarBack.HealthBar(20.0f, backingbarSize, enemyPos, 0xff000000);		//Black behind health bar
	}

	if (health > 0)																	//Stop when health is below 0
	{
		healthBar.HealthBar(20.0f, health, enemyPosAbove, 0xff00ff00);				//Position health bar above other bar
		healthBarBack.HealthBar(20.0f, backingbarSize, enemyPosAbove, 0xff000000);	//Position back of health bar above power bar
	}

	if (Power >= 100)																//When power is at maximum
	{
		shoot = true;																//Enemy can shoot
	}
}

