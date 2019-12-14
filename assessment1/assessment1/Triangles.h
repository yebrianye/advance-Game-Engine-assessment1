#pragma once
#include "Shader.h"
#include <GLFW\glfw3.h>

#include "TextureLoader.h"
class Triangles
{
public:
	Shader* shader;
	static bool triangleGenerated;
	static unsigned int triEboID1, triVBOID1, triVaoID1, triTextureID1, triTextureRectVaoID, triTextureRectVboID;

	Triangles();
	~Triangles();

	void draw();
};

