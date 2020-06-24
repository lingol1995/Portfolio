// Application.h
#ifndef _LAB1_H
#define _LAB1_H

// Includes
#include "baseapplication.h"

#include "CubeMesh.h"
#include "PointMesh.h"
#include "SphereMesh.h"
#include "ColourShader.h"
#include "RenderTexture.h"
#include "OrthoMesh.h"
#include "TextureShader.h"
#include "LightShader.h";
#include "Light.h";
#include "PlaneMesh.h";
#include "ManipulationShader.h";
#include "Timer.h"
#include "ShadowShader.h";
#include "DepthShader.h";
#include "Model.h";
#include "GeometryShader.h";
#include "TranslationShader.h";
#include "TessellationShader.h";
#include "TessellationMesh.h";
#include "Input.h";
#include "HorizontalBlurShader.h";
#include "VerticalBlurShader.h";
#include "WallGeometryShader.h";
#include "Walls.h"
#include "SpecularShader.h";


#include<vector>

	const int SHADOWMAP_WIDTH = 1024;
	const int SHADOWMAP_HEIGHT = 1024;

	using std::vector;
class Lab1 : public BaseApplication
{
public:

	Lab1(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input*);
	~Lab1();


	bool Frame();

	void RenderToTexture();
	//BLURRING////////////////
	void BlurWholeScene();
	void DownSample();
	void Horizontal();
	void Vertical();
	void UpSample();
	void FinalBlur();
	////////////////////
	bool RenderScene();
	float time;
	float height;
	float frequency;
	float tess;

private:
	bool Render();

private:
	//SCENE OBJECTS
	SphereMesh* m_Moon;
	SphereMesh* m_Sweet;
	SphereMesh* m_Sweet2;
	SphereMesh* m_Sweet3;
	SphereMesh* m_LavaLamp;
	SphereMesh* m_Lava;
	SphereMesh* m_try;
	SphereMesh* m_Spillage;
	Model* m_Teapot;
	Model* m_Cup;
	Model* m_Book;
	PointMesh* m_backWall;
	Walls* m_Wall;
	PlaneMesh* m_Plane;
	
	//SHADERS
	LightShader* m_LightShader;
	SpecularShader* m_specShader;
	GeometryShader* m_geometry;
	WallGeometryShader* m_wallShader;
	ManipulationShader* m_Manipulation;
	TranslationShader* m_translation;
	TessellationMesh* m_TessMesh;
	TessellationShader* m_TessShader;
	HorizontalBlurShader* m_Horizontal;
	VerticalBlurShader* m_Vertical;
	ColourShader* m_ColourShader;
	TextureShader* m_TextureShader;
	ShadowShader* m_Shadow;
	DepthShader* m_Depth;

	//ORTHO MESHES
	OrthoMesh* m_OrthoMesh;
	OrthoMesh* m_fullOrtho;
	OrthoMesh* m_smallOrtho;
	OrthoMesh* m_finalOrtho;
	
	//RENDER TEXTURES
	RenderTexture* m_RenderTexture;
	RenderTexture* m_blurWhole;
	RenderTexture* m_DownSample;
	RenderTexture* m_horBlur;
	RenderTexture* m_verBlur;
	RenderTexture* m_UpSample;
	RenderTexture* m_screen;
	RenderTexture* m_final;

	//LIGHTS
	Light* m_Light;
	Light* m_Light2;
	Light* m_Light3;
	Light* m_Light4;
	Light* m_Light6;
	////////////////////
	Timer* m_Time;
	int downSampleWidth, downSampleHeight;
	int screenW, screenH;
	float textureTranslation;
};

#endif