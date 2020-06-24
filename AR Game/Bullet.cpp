#include "Bullet.h"
#include "GameObject.h"
#include <graphics\mesh_instance.h>
#include <graphics\mesh.h>

namespace gef
{
	class MeshInstance;
	class Mesh;
	class Aabb;
}

Bullet::Bullet()
{
}

void Bullet::Init(gef::Platform& platform_, int& maxbullet_number)								//Initialising bullets, take in maximum bullets
{
	for (int no = 1; no < maxbullet_number; no++)												//For each bullet (max number)
	{
		bullets[no].bullet_mesh = bullets[no].bullets_obj.CreateMesh(platform_, 0.02f);			//Bullet meshes created
		bullets[no].bullets_obj.set_mesh(bullets[no].bullet_mesh);								//Bullet Game Objects given meshes
		bullets[no].launched = false;															//No bullets shot yet
		bullets[no].timeLaunch = 1;																//Time is set to 1
	}
}

void Bullet::InitBullets(gef::Matrix44 spawnPos, int& bullet_number)							//Initialse bullet at spawn point position, takes in current bullet
{
	bullets[bullet_number].bullets_obj.CreateTransform(spawnPos.GetTranslation().x(), spawnPos.GetTranslation().y(), spawnPos.GetTranslation().z());	//Create transform at spawn position (Player)
	bullets[bullet_number].bullet_aabb = bullets[bullet_number].bullets_obj.mesh()->aabb().Transform(bullets[bullet_number].bullets_obj.transform());	//Transform Bounding boxes to new bullet position (player)
}

void Bullet::bulletReset(gef::Matrix44 spawnPos, int& bullet_number)							//Reset current bullet to player positition (spawnPos)
{
	bullets[bullet_number].launched = false;													//Bullet no longer shot
	bullets[bullet_number].timeLaunch = 0;														//Time reset
	bullets[bullet_number].bullets_obj.CreateTransform(spawnPos.GetTranslation().x(), spawnPos.GetTranslation().y(), spawnPos.GetTranslation().z());	//Reset to player position
	bullets[bullet_number].bullet_aabb = bullets[bullet_number].bullets_obj.mesh()->aabb().Transform(bullets[bullet_number].bullets_obj.transform());	//Reset to bullet new position
	bullets[bullet_number].bullets_obj.velocity.set_value(0.0f, 0.0f, 0.0f);					//No longer moving
}

void Bullet::ShootOne(gef::Matrix44 spawnPos, int& bullet_number)
{
	if (bullets[bullet_number].launched == true)												//If current bullet is shot
	{
		bullets[bullet_number].timeLaunch += 1 * Time.deltaTime;								//The time from launch
		bullets[bullet_number].bullets_obj.velocity.set_value(0.0f, 0.0f, -0.1f);				//Shoot current bullet down z axis
		bullets[bullet_number].bullets_obj.Move(bullets[bullet_number].bullets_obj.velocity);	//Move current bullet
		bullets[bullet_number].bullet_aabb = bullets[bullet_number].bullets_obj.mesh()->aabb().Transform(bullets[bullet_number].bullets_obj.transform());

		if (bullets[bullet_number].timeLaunch >= 5.0)											
		{
			bulletReset(spawnPos, bullet_number);												//Reset current bullet at spawn point
		}
	}
}


void Bullet::Shoot(gef::Matrix44 spawnPos, int& bullet_number)									//Shoot current bullet at spawn position
{
	bullet_number++;																			//Increase bullet number
	InitBullets(spawnPos, bullet_number);														//Initialise bullet at spawn position
	bullets[bullet_number].launched = true;														//Another bullet launched
}