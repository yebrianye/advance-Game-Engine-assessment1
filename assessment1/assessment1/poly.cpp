#include "Poly.h"

bool Poly::polyGenerated = false;
unsigned int Poly::polygonEboID1, Poly::polygonVBOID1, Poly::polygonVaoID1, Poly::textureID1, Poly::textureRectVaoID, Poly::textureRectVboID;


Poly::Poly()
{
	//vertix for the polygon
	float polygonVertices[] = {

		0.0,0.6,0,  1,0,1, 0.5,1,//top
		0.5,0.2,0,  0,1,0,0.8,0.7,//mid right
		0.8,-0.5,0, 1,0,1, 1,0,//bottom right
		0.0,-0.5,0, 0,1,0, 0.5,0,//bottom mid
		-0.8,-0.5,0,1,0,1,0,0,//bottom left
		-0.5,0.2,0, 0,1,0, 0.2,0.7//mid left
	};



	//order of indexes from above vertices of 4 triangles
	unsigned int polygonIndices[] = {
		1,2,3,//second triangle
		0,1,3,//first triangle
		0,3,5,//thrid triangle
		3,4,5//second triangle
	};

	//polygon VAO
	glGenVertexArrays(1, &polygonVaoID1);

	glBindVertexArray(polygonVaoID1);

	//id of the polygon vertext buffer
	glGenBuffers(1, &polygonVBOID1);
	//make this buffer the active one
	glBindBuffer(GL_ARRAY_BUFFER, polygonVBOID1);
	//put data into it
	glBufferData(GL_ARRAY_BUFFER, sizeof(polygonVertices), polygonVertices, GL_STATIC_DRAW);


	//Elemental Buffer object(EBO) which holds the indexes of vertexes to help build triangles
	glGenBuffers(1, &polygonEboID1);
	//make it the current buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, polygonEboID1);
	//give it the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(polygonIndices), polygonIndices, GL_STATIC_DRAW);

	
	/*
	//feed polygon Buffer Data into vertex shader. 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//enable location 0
	glEnableVertexAttribArray(0);

	///*
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//enable location 1
	glEnableVertexAttribArray(1);
//*/
//LOAD UP TEXTURES
//tell stbi to flip images loaded in
stbi_set_flip_vertically_on_load(true);
	//generate texture on gfx card, get id
	textureID1 = loadTexture("smile.jpg", GL_RGB);


	//VAO - remember how to read VBO data into vertex shader
	glGenVertexArrays(1, &textureRectVaoID);
	//make it the active one
	glBindVertexArray(textureRectVaoID);

	//VBO

	glGenBuffers(1, &textureRectVboID);
	//make this one active
	glBindBuffer(GL_ARRAY_BUFFER, textureRectVboID);
	//pass our data to thee VBO currently active
	glBufferData(GL_ARRAY_BUFFER, sizeof(polygonVertices), polygonVertices, GL_STATIC_DRAW);
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

	//bind rect Ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, polygonEboID1);

	//unbind VAO
	glBindVertexArray(0);


	//unbind VAO
	//glBindVertexArray(0);
}


Poly::~Poly()
{
}

void Poly::draw()
{
	//shader->use();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID1);
	glBindVertexArray(textureRectVaoID);
	
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);


}

