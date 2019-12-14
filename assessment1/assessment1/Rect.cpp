#include "Rect.h"
bool Rect::rectGenerated = false;
unsigned int Rect::rectEboID1=0, Rect::rectVBOID1=0, Rect::rectVaoID1=0,Rect::textureID1=0,Rect::textureRectVboID=0,Rect::textureRectVaoID=0;


Rect::Rect()
{
	//vertix for the rect
	float rectVertices[] = {
		0.5,0.5,0,  0,1,0, 1,1,//top right
		0.5,-0.5,0, 1,0,0, 1,0,//bottom right
		-0.5,-0.5,0,0,0,1, 0,0,//bottom left
		-0.5,0.5,0, 1,1,0, 0,1//top left
	};



	//order of indexes from above vertices of 2 triangles
	unsigned int rectIndices[] = {
		0,1,3,//first triangle
		1,2,3,//second triangle
	};
	/**/
	//rect VAO
	glGenVertexArrays(1, &rectVaoID1);

	glBindVertexArray(rectVaoID1);

	//id of the rect vertext buffer
	glGenBuffers(1, &rectVBOID1);
	//make this buffer the active one
	glBindBuffer(GL_ARRAY_BUFFER, rectVBOID1);
	//put data into it
	//glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);


	//Elemental Buffer object(EBO) which holds the indexes of vertexes to help build triangles
	glGenBuffers(1, &rectEboID1);
	//make it the current buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectEboID1);
	//give it the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndices), rectIndices, GL_STATIC_DRAW);

	//LOAD UP TEXTURES
	//tell stbi to flip images loaded in
	stbi_set_flip_vertically_on_load(true);
	//generate texture on gfx card, get id
	textureID1 = loadTexture("monsterHunter.jpg", GL_RGB);


	//VAO - remember how to read VBO data into vertex shader
	glGenVertexArrays(1, &textureRectVaoID);
	//make it the active one
	glBindVertexArray(textureRectVaoID);

	//VBO
	
	glGenBuffers(1, &textureRectVboID);
	//make this one active
	glBindBuffer(GL_ARRAY_BUFFER, textureRectVboID);
	//pass our data to thee VBO currently active
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectEboID1);

	//unbind VAO
	glBindVertexArray(0);
}


Rect::~Rect()
{
}

void Rect::draw() {
	/*	shader->use();


	//work with registered texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//assign our crate texture to that slot
	glBindTexture(GL_TEXTURE_2D, textureID1);
	//make our texture rect shape current again
	glBindVertexArray(textureRectVaoID);

	int texture1UniformLocationID = glGetUniformLocation(&shader.ID, "texture1");
	glUniform1i(texture1UniformLocationID, 0);//ie - set teture1 variable on frag shader to value 0

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	*/
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID1);
	glBindVertexArray(textureRectVaoID);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


}
