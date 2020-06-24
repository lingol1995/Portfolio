#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "GameObject.h"

namespace gef
{
	class Aabb;
}

class Collisions : public GameObject
{
public:
	Collisions();
	bool Collision(gef::Aabb aabb1, gef::Aabb aabb2);		//Handle collisions between two bounding boxes

};

#endif 
