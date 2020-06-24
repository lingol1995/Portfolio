
#ifndef _MODEL_H_
#define _MODEL_H_


// INCLUDES //
#include <Windows.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
using namespace std;


// MY CLASS INCLUDES //
#include "TokenStream.h"
#include <vector>
#include "Vec3.h"
#include "SOIL.h"

class Model
{

public:
	
	bool Load(char*, char*);
	void Render();
	
private:
	
	void LoadTexture(char*);
	bool LoadModel(char*);
	
	int m_vertexCount;
	GLuint texture;

	// vectors for storing model data, for your use
	vector<float> vertex, normals, texCoords;
	
};

#endif