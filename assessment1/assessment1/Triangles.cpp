#include "Triangles.h"

bool Triangles::triangleGenerated = false;
unsigned int Triangles::triEboID1, Triangles::triVBOID1 = 0, Triangles::triVaoID1 = 0, Triangles::triTextureID1 = 0, Triangles::triTextureRectVaoID = 0, Triangles::triTextureRectVboID = 0;

Triangles::Triangles()
{
	//vertix for the rect
	float triangleVertices[] = {
		0,0.5,0 ,   1,0,0, 0.5,1,//top
		0.5,-0.5,0, 0,1,0, 1,0,//bottom right
		-0.5,-0.5,0,0,0,1, 0,0,//bottom left

	};

	//order of indexes from above vertices of 2 triangles
	unsigned int triIndices[] = {
		0,2,1,
	};
	
	//triangle VAO
	glGenVertexArrays(1, &triVaoID1);

	glBindVertexArray(triVaoID1);

	//id of the triangle vertext buffer
	glGenBuffers(1, &triVBOID1);
	//make this buffer the active one
	glBindBuffer(GL_ARRAY_BUFFER, triVBOID1);
	
	//Elemental Buffer object(EBO) which holds the indexes of vertexes to help build triangles
	glGenBuffers(1, &triEboID1);
	//make it the current buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triEboID1);
	//give it the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triIndices), triIndices, GL_STATIC_DRAW);
	
	//LOAD UP TEXTURES
	//tell stbi to flip images loaded in
	stbi_set_flip_vertically_on_load(true);
	//generate texture on gfx card, get id
	triTextureID1 = loadTexture("roadWork.jpg", GL_RGB);


	//VAO - remember how to read VBO data into vertex shader
	glGenVertexArrays(1, &triTextureRectVaoID);
	//make it the active one
	glBindVertexArray(triTextureRectVaoID);

	//VBO

	glGenBuffers(1, &triTextureRectVboID);
	//make this one active
	glBindBuffer(GL_ARRAY_BUFFER, triTextureRectVboID);
	//pass our data to thee VBO currently active
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
	//Attrib pointeners
	//location = 0, xyz values
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//location = 1, RGB values
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//location = 2, ST texture coordibate values
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//bind triangle Ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triEboID1);

	//unbind VAO
	glBindVertexArray(0);
}


Triangles::~Triangles()
{
}

void Triangles::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, triTextureID1);
	glBindVertexArray(triTextureRectVaoID);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
