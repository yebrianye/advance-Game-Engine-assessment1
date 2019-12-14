#pragma once
#include "Shader.h"
#include <GLFW\glfw3.h>
#include "TextureLoader.h"

class Poly
{
public:

	Shader* shader;
	static bool polyGenerated;
	static unsigned int polygonEboID1, polygonVBOID1, polygonVaoID1, textureID1, textureRectVaoID, textureRectVboID;

	Poly();
	virtual ~Poly();

	void draw();
};

