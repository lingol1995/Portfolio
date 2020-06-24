#include "Markers.h"
#include <graphics/mesh_instance.h>
#include <maths\quaternion.h>

Markers::Markers()
{
}

void Markers::Init()
{
	marker_id = 0;				//Marker ID 1
	marker_id2 = 1;				//Marker ID 2
	marker_id3 = 2;				//Marker ID 3
	marker_id4 = 3;				//Marker ID 4
	renderOne = false;			//For rendering, don't render object one
	renderTwo = false;			//Don't render object two
	renderThree = false;		//Don't render object three
	renderFour = false;			//Don't render object four
	reloadTimer = 0;			//Timer for how long marker four can be covered
	markerFourMissing = false;	//Marker four has been missing for longer than 10 frames
}

bool Markers::marker1Found()
{
	if (sampleIsMarkerFound(marker_id))		//If marker 1 is found
	{
		sampleGetTransform(					//Get the marker's transform
			marker_id,
			&marker1_transform);

		renderOne = true;					//Object one can be drawn
		return true;						//Marker one found
	}
}

bool Markers::marker3Found()						
{
	if (sampleIsMarkerFound(marker_id3))	//If marker 3 is found
	{
		sampleGetTransform(					//Get the marker's transform			
			marker_id3,
			&marker3_transform);

		renderThree = true;					//Object three can be drawn
		return true;						//Marker three found
	}
}

bool Markers::marker2Found()
{
	if (sampleIsMarkerFound(marker_id2))				//If second card found
	{
		sampleGetTransform(								//Marker is being tracked, get it’s transform
			marker_id2,
			&marker_transform2);
		return true;
	}
	else return false;
}

bool Markers::marker4Found()
{
	if (sampleIsMarkerFound(marker_id4))				//If marker 4 is found
	{										
		sampleGetTransform(								// Marker is being tracked, get it’s transform
			marker_id4,
			&marker_transform4);
	}
}

void Markers::markerOneReaction(gef::MeshInstance& object, Controller& controller_)			//Card found, so render object corresponding to it
{
	if(marker1Found())																		//Marker 1 found
	{ 
		transform1_.SetIdentity();
		transform1_rotation_.RotationX(1.57f);												//Rotate Book
		transform_scaling_.Scale(gef::Vector4(0.01f, 0.01f, 0.01f));						//Scale Book
		transform_translation_.SetIdentity();
		transform_translation_.SetTranslation(gef::Vector4(0.0f, 0.0f, -0.1f));				//Translate book
		transform1_ = transform_scaling_ * transform1_rotation_ * transform_translation_;	//New Transform
		object.set_transform(transform1_ * marker1_transform);								//Transform to marker position
		
	}
}

void Markers::markerTwoReaction(gef::Platform& platform_, Enemy& enemy)			//Enemy movement
{
	if (marker2Found())															//If second marker found
	{
		enemy.movement(platform_, marker3_transform.GetTranslation(), marker_transform2.GetTranslation(), marker1_transform.GetTranslation());		//Move enemy between two marker points, and above third point
	}
}

void Markers::markerTwoDraw(gef::MeshInstance& object2)
{
	if (marker2Found())
	{
		transform2_.SetIdentity();
		localtransform2_scaling_.Scale(gef::Vector4(0.1f, 0.1f, 0.1f));					//Transform for Pencil scaled
		localtransform2_translation_.SetIdentity();
		localtransform2_translation_.SetTranslation(gef::Vector4(0.0f, 0.0f, 0.1f));	//Translate Pencil
		transform2_ = localtransform2_scaling_ * localtransform2_translation_;
		object2.set_transform(transform2_* marker_transform2);							//Transform pencil above marker local position
		renderTwo = true;																//Pencil can be rendered
	}
}

void Markers::markerThreeReaction(gef::MeshInstance& object3)				//Marker 3 found reaction				
{
	if(marker3Found())														//If marker three found
	{
		transform3_.SetIdentity();	
		transform3_.Scale(gef::Vector4(0.1f, 0.1f, 0.1f));					//Transform for Pencil scaled
		object3.set_transform(transform3_* marker3_transform );				//Transform Pencil above marker local position
	}
}

void Markers::markerFourReaction(Player& player, gef::MeshInstance& object4)				//Marker 4 found reaction
{
	if (marker4Found())																		//If marker 4 found
	{	
		renderFour = true;																	//Can render box
		transform4_.SetIdentity();
		localtransform4_scaling_.Scale(gef::Vector4(0.001f, 0.001f, 0.001f));				//Transform for Box scaled
		localtransform4_translation_.SetIdentity();
		localtransform4_translation_.SetTranslation(gef::Vector4(0.0f, 0.1f, 0.0f));		//Translation for Box model
		transform4_ =  localtransform4_scaling_ * localtransform4_translation_;				//Local transform			
		object4.set_transform(transform4_* marker_transform4);								//Object positioning
	}

	else														//If card not found
	{
		renderFour = false;
		if (player.reload == true)								//If player runs out of bullets
		{
			player.bulletReload();								//Reload bullets
		}
		
	}
}