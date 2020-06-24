#include "Collisions.h"

#include <graphics/mesh.h>

Collisions::Collisions()
{
}

bool Collisions::Collision(gef::Aabb aabb1, gef::Aabb aabb2)				//Collisions between two game object bounding boxes
{
		if (aabb1.max_vtx().x() >= aabb2.min_vtx().x()						//Testing if all the maximums of both bounding boxes are bigger than the others minumums
			&& aabb1.min_vtx().x() <= aabb2.max_vtx().x()
			&& aabb1.max_vtx().y() >= aabb2.min_vtx().y()
			&& aabb1.min_vtx().y() <= aabb2.max_vtx().y()
			&& aabb1.max_vtx().z() >= aabb2.min_vtx().z()
			&& aabb1.min_vtx().z() <= aabb2.max_vtx().z())
			return true;													//If they all are, return true	
		
		else return false;													//If not, no collision made
}



