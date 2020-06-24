#include "GameObject.h"
#include <system/platform.h>
#include <graphics/mesh.h>
#include <graphics/primitive.h>
#include <maths\quaternion.h>

GameObject::GameObject()
{
	velocity.set_x(0);			//Initialise velocity of object
	velocity.set_y(0);
	velocity.set_z(0);
}


int GameObject::Reset()			//Resetting GameObject		
{
	velocity.set_x(0);			//Velocity reset
	velocity.set_y(0);
	health = 100.0f;			//Health reset
	Power = 0;					//Power reset

	return 0;
}

int GameObject::Move(gef::Vector4 curr_Velocity)		//Move object using its velocity
{	//Add velocity to current position
	newPosVec = gef::Vector4(transform().GetTranslation().x() + curr_Velocity.x(), transform().GetTranslation().y()+curr_Velocity.y(), transform().GetTranslation().z() +curr_Velocity.z());		
	newPos.SetIdentity();								//New transform						
	newPos.NormaliseRotation();							//Normalise					
	newPos.SetTranslation(newPosVec);					//Translate transform to vector
	set_transform(newPos);								//Set this new transform as object's transform

	return 0;
}

void GameObject::CreateTransform(float positionx, float positiony, float positionz)		//Shortcut to creating a transform for objects
{
	transform_matrix.SetIdentity();														//Set identity
	transform_matrix.SetTranslation(gef::Vector4(positionx, positiony, positionz));		//Translate to positions dictated by parameters
	mesh()->aabb().Transform(transform_matrix);											//Move bounding box to new transform
	set_transform(transform_matrix);													//Set this as new transform
}

//More detailed version of the function above
//Dictate rotation, scaling etc. using this
void GameObject::CreateTransformFull(float positionx, float positiony, float positionz, float scaleX, float scaleY, float scaleZ, float rotateX, float rotateY, float rotateZ)
{
	transform_matrix.SetIdentity();
	transform_matrix.Scale(gef::Vector4(scaleX, scaleY, scaleZ));					//Scale
	transform_matrix.Rotation(gef::Quaternion(rotateX, rotateY, rotateZ, 1));		//Rotation
	transform_matrix.SetTranslation(gef::Vector4(positionx, positiony, positionz));	//Translate

	mesh()->aabb().Transform(transform_matrix);										//Move Bounding Box to this transform
	set_transform(transform_matrix);												//Set transform
}

//Creates a Cube mesh with bounding box
//Takes half-size as a paramater for easier editing
gef::Mesh* GameObject::CreateMesh(gef::Platform& platform, float half_size)
{
	gef::Mesh* mesh = platform.CreateMesh();
	// initialise the vertex data to create
	
	const gef::Mesh::Vertex vertices[] = {
		{ half_size, -half_size, -half_size,  0.577f, -0.577f, -0.577f, 0.0f, 0.0f },
		{ half_size,  half_size, -half_size,  0.577f,  0.577f, -0.577f, 0.0f, 0.0f },
		{ -half_size,  half_size, -half_size, -0.577f,  0.577f, -0.577f, 0.0f, 0.0f },
		{ -half_size, -half_size, -half_size, -0.577f, -0.577f, -0.577f, 0.0f, 0.0f },
		{ half_size, -half_size,  half_size,  0.577f, -0.577f,  0.577f, 0.0f, 0.0f },
		{ half_size,  half_size,  half_size,  0.577f,  0.577f,  0.577f, 0.0f, 0.0f },
		{ -half_size,  half_size,  half_size, -0.577f,  0.577f,  0.577f, 0.0f, 0.0f },
		{ -half_size, -half_size,  half_size, -0.577f, -0.577f,  0.577f, 0.0f, 0.0f }

	};

	mesh->InitVertexBuffer(platform, static_cast<const void*>(vertices), sizeof(vertices) / sizeof(gef::Mesh::Vertex), sizeof(gef::Mesh::Vertex));

	// we will create a single triangle list primitive to draw the triangles that make up the cube
	mesh->AllocatePrimitives(1);
	gef::Primitive* primitive = mesh->GetPrimitive(0);

	const UInt32 indices[] = {
		// Back
		0, 1, 2,
		2, 3, 0,
		// Front
		6, 5, 4,
		4, 7, 6,
		// Left
		2, 7, 3,
		2, 6, 7,
		// Right
		0, 4, 1,
		5, 1, 4,
		// Top
		6, 2, 1,
		5, 6, 1,
		// Bottom
		0, 3, 7,
		0, 7, 4
	};

	primitive->InitIndexBuffer(platform, static_cast<const void*>(indices), sizeof(indices) / sizeof(UInt32), sizeof(UInt32));
	primitive->set_type(gef::TRIANGLE_LIST);

	// set size of bounds, we need this for collision detection routines
	gef::Aabb aabb3(gef::Vector4(-half_size, -half_size, -half_size), gef::Vector4(half_size, half_size, half_size));
	gef::Sphere sphere3(aabb3);

	mesh->set_aabb(aabb3);
	mesh->set_bounding_sphere(sphere3);

	return mesh;
}

//Creates a plane
//Takes half-size for custom easier editing
//Used for camera feed and HUD
gef::Mesh* GameObject::CreatePlane(gef::Platform& platform_, float half_size)
{
	gef::Mesh* mesh = platform_.CreateMesh();

	// initialise the vertex data to create
	//const float half_size = 0.0295f;
	const gef::Mesh::Vertex vertices[] = {
		{ half_size, -half_size, -half_size,  0.577f, -0.577f, -0.577f, 0.0f, 0.0f },
		{ half_size,  half_size, -half_size,  0.577f,  0.577f, -0.577f, 0.0f, 0.0f },
		{ -half_size,  half_size, -half_size, -0.577f,  0.577f, -0.577f, 0.0f, 0.0f },
		{ -half_size, -half_size, -half_size, -0.577f, -0.577f, -0.577f, 0.0f, 0.0f },
	};

	mesh->InitVertexBuffer(platform_, static_cast<const void*>(vertices), sizeof(vertices) / sizeof(gef::Mesh::Vertex), sizeof(gef::Mesh::Vertex));

	// we will create a single triangle list primitive to draw the triangles that make up the cube
	mesh->AllocatePrimitives(1);
	gef::Primitive* primitive = mesh->GetPrimitive(0);

	const UInt32 indices[] = {
		// Back
		0, 1, 2,
		2, 3, 0,
		// Front
		6, 5, 4,
		4, 7, 6,

	};

	primitive->InitIndexBuffer(platform_, static_cast<const void*>(indices), sizeof(indices) / sizeof(UInt32), sizeof(UInt32));
	primitive->set_type(gef::TRIANGLE_LIST);

	// set size of bounds, we need this for collision detection routines
	gef::Aabb aabb3(gef::Vector4(-half_size, -half_size, -half_size), gef::Vector4(half_size, half_size, half_size));
	gef::Sphere sphere3(aabb3);

	mesh->set_aabb(aabb3);
	mesh->set_bounding_sphere(sphere3);

	return mesh;
}