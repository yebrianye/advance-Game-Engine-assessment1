#pragma once
#include "Shader.h"
#include <GLFW\glfw3.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "TextureLoader.h"

class Rect
{
public:
	Shader* shader;
	static bool rectGenerated;
	static unsigned int rectEboID1, rectVBOID1, rectVaoID1, textureID1, textureRectVaoID, textureRectVboID;

	Rect();
	~Rect();

	void draw();
};

