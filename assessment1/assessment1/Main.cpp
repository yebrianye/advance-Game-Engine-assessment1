#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Shader.h"
#include "Poly.h"
#include "Rect.h"
#include "Triangles.h"

#define STB_IMAGE_IMPLEMENTATION
#include "TextureLoader.h"




using namespace std;

int currentShapeToDraw = 1;

//windows resize callback function
void windowResizeCallBack(GLFWwindow* window, int width, int height);

//process user inputs
void processInputs(GLFWwindow* window);

//vertex shader program source code
//main goal of vertex shader is to pass data into gl_Position which is a vec4
const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 apos; \n"//location = 0, is the variable slot. "in" means data passed in
"\n"
"void main()\n"
"{\n"
"gl_Position = vec4(apos.x,apos.y,apos.z,1.0);\n"
"}\n\0";

//FRAGMENT SHADER
//main goal is to pass a vec4 to the next shader representing a final colour for a pixel
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"//out variables are passed to the next shader 
"\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f,0.5f,0.3f,1.0f);\n"
"}\n\0";

bool checkShaderCompileError(int shaderID) {
	int success;//failed or not
	char infoLog[512];//store error info
	//check compile status
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	//report if it failed
	if (!success) {
		//get error and display it 
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		cout << "Shader compile error!!! " << infoLog << endl;
		system("pause");

		return false;
	}

	return true;
}

bool checkShaderLnkingErrors(int shaderProgramID) {
	int success;
	char infoLog[512];
	//check if successfull
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		cout << "Shader Linking Error: " << infoLog << endl;
		system("pause");
		return false;
	}

	return true;
}

void main() {
	//setup windows to use for opengl renderering 
	glfwInit();
	//tell glfw which verision of opengl to use, 3.3 core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//the first 3 in 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//the .3 in 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //core profile

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Assessment 1", NULL, NULL);
	//did it fail?
	if (window == NULL) {
		cout << "window error " << endl;
		glfwTerminate();
		system("pause");
		return; //exit program early
	}

	//make this window the main window
	glfwMakeContextCurrent(window);

	//use glad to bind functions from gpu drivers to our opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		//it failed
		cout << "GLAD Failed1" << endl;
		glfwTerminate();
		system("pause");
		return;
	}

	//tell opengl which part of out window it can render to 
	glViewport(0, 0, 1280, 720);//(x,y,w,h)

	//todo: window resize callback
	//set it so when the screen changes size, or function is called for this window
	glfwSetFramebufferSizeCallback(window, windowResizeCallBack);

	//SHADERS
	//generate shader id
	int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);//returns id of shader generated on GPU

	//giving newly generated shader on GPU shader sourcecode
	
	glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
	//compile code on the gpu
	glCompileShader(vertexShaderID);

	//check for errors
	checkShaderCompileError(vertexShaderID);

	//fragment shader
	int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderID);
	//check for error
	checkShaderCompileError(fragmentShaderID);


	//SHADER PROGRAM 
	//joins your shaders and existing ones to make a full pipeline
	int shaderProgramID = glCreateProgram();
	//attach our shaders to the program
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	//link our shaders
	glLinkProgram(shaderProgramID);
	//check for shader linking errors
	checkShaderLnkingErrors(shaderProgramID);
	//once linked together, no longer need vertex and fragment shader as individual parts
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	Shader rectShaderProgram1("textureVertexShader1.txt", "textureFragmentShader2.txt");
	Shader rectShaderProgram2("polygonVertexShader.txt", "polygonFragmentShader.txt");
	Shader polygonShaderProgram3("polygonVertexShader.txt", "polygonFragmentShader.txt");
	Shader triangleShaderProgram1("textureVertexShader1.txt", "textureFragmentShader2.txt");


	
	//build polygon
	Poly poly;
	poly.shader = &polygonShaderProgram3;

	Rect rect;
	rect.shader = &rectShaderProgram2;

	Triangles triangle;
	triangle.shader = &triangleShaderProgram1;

	//Game loop
	while (!glfwWindowShouldClose(window)) {
		//user inputs
		processInputs(window);

		//RENDERING
			//set clear colour
		glClearColor(0, 0, 0, 0);//rgba, value 0-1 example 0.67
		//clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		if (currentShapeToDraw == 1) {
			
			rectShaderProgram1.use();
            rect.draw();
		}

		if (currentShapeToDraw == 2) {
			triangleShaderProgram1.use();
			triangle.draw();

		}

		if (currentShapeToDraw == 3) {
			rectShaderProgram1.use();
			poly.draw();
			
		}

		
		//process any polled events
		glfwPollEvents();

		//opengl uses double buffering, use this to swap the buffers over
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	system("pause");
}

void windowResizeCallBack(GLFWwindow* window, int width, int height)
{
	//resize opengl viewport
	glViewport(0, 0, width, height);
}

void processInputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		currentShapeToDraw = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		currentShapeToDraw = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		currentShapeToDraw = 3;
	}
}

