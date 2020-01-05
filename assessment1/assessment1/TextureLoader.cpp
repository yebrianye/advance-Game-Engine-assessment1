#include "TextureLoader.h"


unsigned int loadTexture(const char * fileName, int RGBType)
{
	//LOAD UP TEXTURES
	//generate texture on gfx card, get id
	unsigned int textureID1 = 0;
	glGenTextures(1, &textureID1);
	//make this texture the one we're working on
	glBindTexture(GL_TEXTURE_2D, textureID1);
	//wrapping options!
	//params:       type			wrap axis			wrap type
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);//s = horizontal axis on image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);//T = vertical axis
	//filtering options!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//on shrink, use bulonear filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//on stretch, use nearest neighbour filter

	int width, height, numberOfChannels;//these variables will be filled in as we load our image
	unsigned char* image1Data = stbi_load(fileName, &width, &height, &numberOfChannels, 0);
	//if loaded
	if (image1Data) {
		cout << "picture loaded fine!" << endl;
		//let pass image data to the texture in the gfx card
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, RGBType, GL_UNSIGNED_BYTE, image1Data);
		 
		//generate mipmaps :D
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Picture load failed!" << endl;

	}
	//cleanup
	stbi_image_free(image1Data);


	return textureID1;
}
