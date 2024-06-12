#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "CHABO.h"
//#include "CHABObody.h"

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

Texture T1, T2, T3, T4, T5,
Texture0, Texture1, Texture2, Texture3, Texture4, Texture5, Texture6, Texture7, Texture8,
goldTexture, hairTexture, redTexture, eyeTexture;

DirectionalLight dLight(1.0f, 1.0f, 1.0f, 0.5f, 0.8f, 1.0f);

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";


void CreateObjects()
{
	//background
	unsigned int indices[] = {
		2, 1, 0,
		2, 3, 1
	};
	GLfloat vertices[] = {
		//	x       y      z	u	  v    nx,  ny,  nz
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, //0
			0.0f, 0.0f, 2.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //1
			0.0f, -2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //2
			0.0f, -2.0f, 2.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //3

	};

	//mặt bàn to
	unsigned int indices0[] = {
		3, 1, 0,
		3, 2, 1,
		6, 4, 7,
		6, 5, 4,
		2, 4, 1,
		2, 5, 4,
		7, 1, 0,
		7, 4, 1,
		3, 7, 0,
		3, 6, 7,
		6, 5, 2,
		6, 2, 3
	};
	GLfloat vertices0[] = {
		//	x       y      z	u	  v    nx,  ny,  nz
			0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, //0
			0.0f, 0.0f, 2.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, //1
			1.2f, 0.0f, 2.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, //2
			1.2f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f,  //3
			0.0f, -0.1f, 2.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, //4
			1.2f, -0.1f, 2.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, //5
			1.2f, -0.1f, 0.0f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, //6
			0.0f, -0.1f, 0.0f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f //7
	};

	//chân bàn to
	unsigned int indices1[] = {
		3, 1, 0,
		3, 2, 1,
		6, 4, 7,
		6, 5, 4,
		2, 4, 1,
		2, 5, 4,
		7, 1, 0,
		7, 4, 1,
		3, 7, 0,
		3, 6, 7,
		6, 5, 2,
		6, 2, 3
	};
	GLfloat vertices1[] = {
		//	x       y      z	u	  v    nx,  ny,  nz
			0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, //0
			0.0f, 0.0f, 0.3f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, //1
			0.3f, 0.0f, 0.3f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, //2
			0.2f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f,  //3
			0.0f, -3.2f, 0.3f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, //4
			0.3f, -3.2f, 0.3f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, //5
			0.3f, -3.2f, 0.0f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, //6
			0.0f, -3.2f, 0.0f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f //7
	};

	//////////////////////////////////////////
	//đế
	unsigned int indices2[] = {
		0,5,6,
		5,1,6,
		5,3,1,
		3,7,1,
		3,4,7,
		4,2,7,

		0,5,8,
		5,13,8,

		5,3,13,
		3,11,13,

		3,4,11,
		4,12,11,

		4,2,12,
		2,10,12,

		2,7,10,
		7,15,10,

		7,1,15,
		1,9,15,

		1,6,9,
		6,14,9,

		6,0,14,
		0,8,14,
	};
	GLfloat vertices2[] = {
		//x     y      z	  u	    v
		 -1.0f, 0.0f, 1.5f,    0.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a
		0.0f, -1.0f, 1.5f,    1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a1
		1.0f, 0.0f, 1.5f,   0.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a2
		0.0f, 1.0f, 1.5f,     1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a3
		float(1 / sqrt(2)),  float(1 / sqrt(2)), 1.5f,    1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a4
		-float(1 / sqrt(2)),  float(1 / sqrt(2)), 1.5f,   0.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a5
		-float(1 / sqrt(2)),  -float(1 / sqrt(2)), 1.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a6
		float(1 / sqrt(2)),  -float(1 / sqrt(2)), 1.5f,   0.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a7

		 -1.0f, 0.0f, 1.8f,    0.0f, 0.0f,  0.0f, 0.0f, 1.0f,//c//8
		0.0f, -1.0f, 1.8f,     1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//c1//9
		1.0f, 0.0f, 1.8f,    0.0f, 1.0f,  0.0f, 0.0f, 1.0f,//c2//10
		0.0f, 1.0f, 1.8f,     1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//c3//11
		float(1 / sqrt(2)),  float(1 / sqrt(2)), 1.8f,     1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//c4//12
		-float(1 / sqrt(2)),  float(1 / sqrt(2)), 1.8f,    0.0f, 1.0f,  0.0f, 0.0f, 1.0f,//c5//13
		-float(1 / sqrt(2)),  -float(1 / sqrt(2)), 1.8f,   1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//c6//14
		float(1 / sqrt(2)),  -float(1 / sqrt(2)), 1.8f,    0.0f, 0.0f,  0.0f, 0.0f, 1.0f,//c7//15

	};

	//lop ngoai
	unsigned int indices3[] = {
	0,1,2,1,3,2,

	4,5,6,5,7,6,

	8,9,10,9,11,10,

	12,13,14,13,15,14,

	16,17,18,17,19,18,

	20,21,22,21,23,22,

	24,25,26,25,27,26,

	28,29,30,29,31,30,

	32,33,34,33,35,34,

	};
	GLfloat vertices3[] = {
		//x y z u v nx ny nz
		-1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a
		-float(1 / sqrt(2)),  float(1 / sqrt(2)), 0.0f,   1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a5
		-1.0f, 0.0f, 1.5f,    0.0f, 0.0f, 0.0f, 0.0f, -1.0f,//b//8
		-float(1 / sqrt(2)),  float(1 / sqrt(2)), 1.5f,   0.0f, 1.0f,  0.0f, 0.0f, -1.0f,//b5//13

		-float(1 / sqrt(2)),  float(1 / sqrt(2)), 0.0f,   1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a5
		0.0f, 1.0f, 0.0f,     1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a3
		-float(1 / sqrt(2)),  float(1 / sqrt(2)), 1.5f,   0.0f, 0.0f,  0.0f, 0.0f, -1.0f,//b5//13
		0.0f, 1.0f, 1.5f,    0.0f, 1.0f, 0.0f, 0.0f, -1.0f,//b3//11

		0.0f, 1.0f, 0.0f,     1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a3
		float(1 / sqrt(2)),  float(1 / sqrt(2)), 0.0f,    1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a4
		0.0f, 1.0f, 1.5f,    0.0f, 0.0f, 0.0f, 0.0f, -1.0f,//b3//11
		float(1 / sqrt(2)),  float(1 / sqrt(2)), 1.5f,    0.0f, 1.0f,  0.0f, 0.0f, -1.0f,//b4//12

		float(1 / sqrt(2)),  float(1 / sqrt(2)), 0.0f,    1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a4
		1.0f, 0.0f, 0.0f,     1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a2
		float(1 / sqrt(2)),  float(1 / sqrt(2)), 1.5f,    0.0f, 0.0f,  0.0f, 0.0f, -1.0f,//b4//12
		1.0f, 0.0f, 1.5f,    0.0f, 1.0f, 0.0f, 0.0f, -1.0f,//b2//10

		1.0f, 0.0f, 0.0f,     1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a2
		float(1 / sqrt(2)),  -float(1 / sqrt(2)), 0.0f,   1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a7
		1.0f, 0.0f, 1.5f,    0.0f, 0.0f, 0.0f, 0.0f, -1.0f,//b2//10
		float(1 / sqrt(2)),  -float(1 / sqrt(2)), 1.5f,   0.0f, 1.0f,  0.0f, 0.0f, -1.0f,//b7//15


		float(1 / sqrt(2)),  -float(1 / sqrt(2)), 0.0f,   1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a7
		0.0f, -1.0f, 0.0f,    1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a1
		float(1 / sqrt(2)),  -float(1 / sqrt(2)), 1.5f,   0.0f, 0.0f,  0.0f, 0.0f, -1.0f,//b7//15
		0.0f, -1.0f, 1.5f,    0.0f, 1.0f, 0.0f, 0.0f, -1.0f,//b1//9

		0.0f, -1.0f, 0.0f,    1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a1
		-float(1 / sqrt(2)),  -float(1 / sqrt(2)), 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a6
		0.0f, -1.0f, 1.5f,    0.0f, 0.0f, 0.0f, 0.0f, -1.0f,//b1//9
		-float(1 / sqrt(2)),  -float(1 / sqrt(2)), 1.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,//b6//14

		-float(1 / sqrt(2)),  -float(1 / sqrt(2)), 0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a6
		-1.0f, 0.0f, 0.0f,    1.0f, 1.0f,  0.0f, 0.0f, 1.0f,//a
		-float(1 / sqrt(2)),  -float(1 / sqrt(2)), 1.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,//b6//14
		-1.0f, 0.0f, 1.5f,    0.0f, 1.0f, 0.0f, 0.0f, -1.0f,//b//8

	};

	//lop trong
	unsigned int indices4[] = {
		0,5,8,
		5,13,8,

		5,3,13,
		3,11,13,

		3,4,11,
		4,12,11,

		4,2,12,
		2,10,12,

		2,7,10,
		7,15,10,

		7,1,15,
		1,9,15,

		1,6,9,
		6,14,9,

		6,0,14,
		0,8,14,
	};
	GLfloat vertices4[] = {
		//x y z u v nx ny nz
		-1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a
		0.0f, -1.0f, 0.0f,    1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a1
		1.0f, 0.0f, 0.0f,     1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a2
		0.0f, 1.0f, 0.0f,     1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a3
		float(1 / sqrt(2)),  float(1 / sqrt(2)), 0.0f,    0.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a4
		-float(1 / sqrt(2)),  float(1 / sqrt(2)), 0.0f,   0.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a5
		-float(1 / sqrt(2)),  -float(1 / sqrt(2)), 0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a6
		float(1 / sqrt(2)),  -float(1 / sqrt(2)), 0.0f,   0.0f, 0.0f,  0.0f, 0.0f, 1.0f,//a7

		-1.0f, 0.0f, 1.5f,    1.0f, 1.0f, 0.0f, 0.0f, -1.0f,//b//8
		0.0f, -1.0f, 1.5f,    0.0f, 1.0f, 0.0f, 0.0f, -1.0f,//b1//9
		1.0f, 0.0f, 1.5f,    0.0f, 1.0f, 0.0f, 0.0f, -1.0f,//b2//10
		0.0f, 1.0f, 1.5f,    1.0f, 1.0f, 0.0f, 0.0f, -1.0f,//b3//11
		float(1 / sqrt(2)),  float(1 / sqrt(2)), 1.5f,    0.0f, 1.0f,  0.0f, 0.0f, -1.0f,//b4//12
		-float(1 / sqrt(2)),  float(1 / sqrt(2)), 1.5f,   0.0f, 1.0f,  0.0f, 0.0f, -1.0f,//b5//13
		-float(1 / sqrt(2)),  -float(1 / sqrt(2)), 1.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,//b6//14
		float(1 / sqrt(2)),  -float(1 / sqrt(2)), 1.5f,   1.0f, 1.0f,  0.0f, 0.0f, -1.0f,//b7//15

	};

	//nen nhang
	unsigned int indices5[]{
		0,1,2,
		0,2,3,

		4,5,6,
		4,6,7,

		8,9,10,
		8,10,11,

		12,13,14,
		12,14,15
	};
	GLfloat vertices5[]{
		//x y z u v nx ny nz
		0.0f, -0.03f, 1.0f,  0.0f,0.0f, 1.0f, -1.0f, 0.0f,
		0.03f, 0.0f, 1.0f,  1.0f,0.0f, 1.0f, -1.0f, 0.0f,
		0.03f, 0.0f, -2.0f,  1.0f,1.0f, 1.0f, -1.0f, 0.0f,
		0.0f, -0.03f, -2.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f,


		0.03f, 0.0f, 1.0f, 0.0f,0.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 0.03f, 1.0f, 1.0f,0.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 0.03f, -2.0f, 1.0f,1.0f, 1.0f, 1.0f, 0.0f,
		0.03f, 0.0f, -2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		0.0f, 0.03f, 1.0f, 0.0f,0.0f, -1.0f, 1.0f, 0.0f,
		-0.03f, 0.0f, 1.0f, 1.0f,0.0f, -1.0f, 1.0f, 0.0f,
		-0.03f, 0.0f,-2.0f, 1.0f,1.0f, -1.0f, 1.0f, 0.0f,
		0.0f, 0.03f, -2.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f,

		-0.03f, 0.0f, 1.0f, 0.0f,0.0f, -1.0f, -1.0f, 0.0f,
		0.0f, -0.03f, 1.0f, 1.0f,0.0f, -1.0f, -1.0f, 0.0f,
		0.0f, -0.03f, -2.0f, 1.0f,1.0f, -1.0f, -1.0f, 0.0f,
		-0.03f, 0.0f, -2.0f, 0.0f,1.0f, -1.0f, -1.0f, 0.0f,


	};

	//Dai
	unsigned int indices6[]{
		0,1,2,
		0,2,3,

		4,5,6,
		4,6,7,

		8,9,10,
		8,10,11,

		12,13,14,
		12,14,15,

		16,17,18,
		16,18,19,

		20,21,22,
		20,22,23,
	};
	GLfloat vertices6[]{
		1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a
		-1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//b
		-1.0f, 0.0f, 0.0f, 1.0f, 0.4f, 0.0f, 0.0f, 1.0f,//a2
		1.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.0f, 0.0f, 1.0f,//a1

		1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a
		-1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//b
		-1.0f, 0.5f, 1.0f, 1.0f, 0.4f, 0.0f, 0.0f, -1.0f,//b
		1.0f, 0.5f, 1.0f,0.0f, 0.4f, 0.0f, 0.0f, -1.0f,//a

		-1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,//b
		-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a2
		-1.0f, 0.0f, 1.0f, 1.0f, 0.4f, 0.0f, 0.0f, -1.0f,//a2
		-1.0f, 0.5f, 1.0f,0.0f, 0.4f, 0.0f, 0.0f, -1.0f,//b



		-1.0f, 0.0f, 0.0f, 1.0f, 0.4f, 0.0f, 0.0f, 1.0f,//a2
		1.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.0f, 0.0f, 1.0f,//a1
		1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,//a1
		-1.0f, 0.0f, 1.0f,1.0f, 1.0f, 0.0f, 0.0f, -1.0f,//a2




		1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a1
		1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a
		1.0f, 0.5f, 1.0f, 1.0f, 0.4f, 0.0f, 0.0f, -1.0f,//a
		1.0f, 0.0f, 1.0f,0.0f, 0.4f, 0.0f, 0.0f, -1.0f,//a1

		1.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,//a
		-1.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,//b
		-1.0f, 0.0f, 1.0f, 1.0f, 0.4f, 0.0f, 0.0f, -1.0f,//a2
		1.0f, 0.0f, 1.0f, 0.0f, 0.4f, 0.0f, 0.0f, -1.0f,//a1
	};

	//den
	unsigned int indices7[]{
		0,1,2,3,4,5,6,7,8
	};
	GLfloat vertices7[]{
		0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a
		0.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a3
		0.0f, 0.0f, -1.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,//b

		0.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a3
		-0.1f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a3//a1
		0.0f, 0.0f, -1.0f,  0.5f, 1.0f, 0.0f, 0.0f,1.0f,//b

		-0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a//a1
		0.2f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//a3//a
		0.0f, 0.0f, -1.0f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,//b//b
	};

	/////////////////////////////////////////

	//////////////////////////////////////////////////////
	Mesh* obj0 = new Mesh();
	obj0->CreateMesh(vertices0, indices0, 64, 36);
	meshList.push_back(obj0);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices1, indices1, 64, 36);
	meshList.push_back(obj1);

	Mesh* obj = new Mesh();
	obj->CreateMesh(vertices, indices, 32, 6);
	meshList.push_back(obj);
	/////////////////////////////////////////////
		//đế
	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices2, indices2, 128, 66);
	meshList.push_back(obj2);

	//lop ngoai
	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(vertices3, indices3, 256, 48);
	meshList.push_back(obj3);

	//lop trong
	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vertices4, indices4, 128, 48);
	meshList.push_back(obj4);

	//nen nhang
	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(vertices5, indices5, 128, 24);
	meshList.push_back(obj5);

	//dai
	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(vertices6, indices6, 192, 36);
	meshList.push_back(obj6);

	//den
	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(vertices7, indices7, 72, 9);
	meshList.push_back(obj7);

	///////////////////////////////////////////////////

}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.2f);

	Chabo chabo(shaderList[0]);
	chabo.goldTexture.LoadTexture();
	chabo.hairTexture.LoadTexture();
	chabo.redTexture.LoadTexture();
	chabo.eyeTexture.LoadTexture();
	//ChaboBodi chaboBodi(shaderList[0]);
	//chaboBodi.goldTexture2.LoadTexture(); 
	Texture0 = Texture("Textures/hi.jpg");
	Texture0.LoadTexture();
	Texture1 = Texture("Textures/wo.jpg");
	Texture1.LoadTexture();
	Texture2 = Texture("Textures/3.jpg");
	Texture2.LoadTexture();
	Texture3 = Texture("Textures/pot1.jpg");
	Texture3.LoadTexture();
	Texture4 = Texture("Textures/4.jpg");
	Texture4.LoadTexture();
	Texture5 = Texture("Textures/5.jpg");
	Texture5.LoadTexture();
	Texture6 = Texture("Textures/gold.jpg");
	Texture6.LoadTexture();
	Texture7 = Texture("Textures/lightt.jpg");
	Texture7.LoadTexture();
	T1 = Texture("Textures/bgbt.jpg");
	T1.LoadTexture();
	T2 = Texture("Textures/1111.jpg");
	T2.LoadTexture();
	T3 = Texture("Textures/wall1.jpg");
	T3.LoadTexture();
	T4 = Texture("Textures/wall.jpg");
	T4.LoadTexture();
	T5 = Texture("Textures/bgbt3.jpg");
	T5.LoadTexture();
	
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0,
		uniformAmbientColour = 0, uniformDiffuseIntensity = 0, uniformSpecularIntensity = 0, uniformLightDirection = 0;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		// Get + Handle User Input
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
		uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
		uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformLightDirection = shaderList[0].GetLightDirectionLocation();

		dLight.UseDirLight(uniformAmbientIntensity, uniformAmbientColour,
			uniformDiffuseIntensity, uniformSpecularIntensity, uniformLightDirection);

		/////////////////////////////////////////mặt bàn
		//mặt ở dưới
		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(4.5f, 5.8f, 4.5f));
		model = glm::translate(model, glm::vec3(-0.8f, 0.45f, -0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		T2.UseTexture();
		meshList[0]->RenderMesh();
		//mặt ở trên
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.0f, 3.0f, -4.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T2.UseTexture();
		meshList[0]->RenderMesh();

		/////////////////////////////////////////chân bàn
		// chân 1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, 2.2f, -2.3f));
		model = glm::scale(model, glm::vec3(3.5f, 2.2f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T2.UseTexture();
		meshList[1]->RenderMesh();
		// chân 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, 2.2f, 6.5f));
		model = glm::scale(model, glm::vec3(3.5f, 2.2f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T2.UseTexture();
		meshList[1]->RenderMesh();
		//chân 3
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.7f, 2.2f, 6.5f));
		model = glm::scale(model, glm::vec3(3.5f, 2.2f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T2.UseTexture();
		meshList[1]->RenderMesh();
		//chân 4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.7f, 2.2f, -2.3f));
		model = glm::scale(model, glm::vec3(3.5f, 2.2f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T2.UseTexture();
		meshList[1]->RenderMesh();

		/////////////////////////////////////////background
		//hoa sen
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, 14.3f, -3.5f));
		model = glm::scale(model, glm::vec3(5.0f, 8.2f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T1.UseTexture();
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, -2.0f, -3.5f));
		model = glm::scale(model, glm::vec3(5.0f, 1.3f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T5.UseTexture();
		meshList[2]->RenderMesh();

		//behind lotus
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(4.0f, 17.3f, -8.0f));
		model = glm::scale(model, glm::vec3(0.5f, 11.0f, 8.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T3.UseTexture();
		meshList[2]->RenderMesh();

		//Left
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(4.0f, 17.3f, -8.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 11.0f, 8.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T3.UseTexture();
		meshList[2]->RenderMesh();

		//right
		/*model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(4.0f, 13.3f, 13.2f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 9.0f, 8.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T3.UseTexture();
		meshList[2]->RenderMesh();*/

		//down
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-17.2f, -4.7f, -8.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 10.6f, 8.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T4.UseTexture();
		meshList[2]->RenderMesh();

		/////////////////////////////////////////////Câu đối


		//////////////////////////////////////////đế bat huong
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.3f, 2.8f, -4.6f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture1.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.0f, 0.2f, -4.8f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture1.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.0f, 5.2f, -4.8f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture1.UseTexture();
		meshList[3]->RenderMesh();

		/////////////////////////////////////////////////// lớp ngoài
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.3f, 2.8f, -4.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture0.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.3f, 2.8f, -4.75f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture0.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.0f, 0.2f, -4.8f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture0.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.0f, 5.2f, -4.8f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture0.UseTexture();
		meshList[4]->RenderMesh();

		////////////////////////////////////////lớp trong
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.3f, 2.8f, -4.8f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture3.UseTexture();
		meshList[5]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.0f, 0.2f, -4.8f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture3.UseTexture();
		meshList[5]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.0f, 5.2f, -4.8f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture3.UseTexture();
		meshList[5]->RenderMesh();

		////////////////////////////////////////////////nén nhang
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.3f, -2.8f, 4.8f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture2.UseTexture();
		meshList[6]->RenderMesh();


		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.0f, -0.2f, 4.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture2.UseTexture();
		meshList[6]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.0f, -5.2f, 4.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture2.UseTexture();
		meshList[6]->RenderMesh();

		//đài
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-8.0f, 6.0f, 3.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture4.UseTexture();
		meshList[7]->RenderMesh();


		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.6f));
		model = glm::translate(model, glm::vec3(5.7f, -25.5f, -4.5f));
		model = glm::rotate(model, glm::radians(60.0f), glm::vec3(-0.5f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture5.UseTexture();
		meshList[6]->RenderMesh();


		////////////////////////////////////////////////đènnnnn
		///////////////////// nến bên trái
		// đế để nến
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.2f, 2.2f, 0.6f));
		model = glm::translate(model, glm::vec3(1.0f, 2.8f, -8.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		T2.UseTexture();
		meshList[0]->RenderMesh();

		//đế nến dưới
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -4.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		model = glm::translate(model, glm::vec3(14.1f, -9.5f, -3.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture6.UseTexture();
		meshList[3]->RenderMesh();

		//đế nến trên
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -3.85f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(18.8f, -12.6f, -10.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture6.UseTexture();
		meshList[3]->RenderMesh();

		//chân nến nhỏ
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -5.2f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 1.0f));
		model = glm::translate(model, glm::vec3(56.5f, -37.52f, -3.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture6.UseTexture();
		meshList[3]->RenderMesh();

		//thân nến
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -4.75f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.7f));
		model = glm::translate(model, glm::vec3(28.3f, -18.8f, -4.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture7.UseTexture();
		meshList[4]->RenderMesh();

		//nến sáng
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -4.7f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.4f));
		model = glm::translate(model, glm::vec3(9.35f, -6.28f, -7.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture6.UseTexture();
		meshList[8]->RenderMesh();

		///////////////////// nến bên phải
		// đế để nến
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.2f, 2.2f, 0.6f));
		model = glm::translate(model, glm::vec3(1.0f, 2.8f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		T2.UseTexture();
		meshList[0]->RenderMesh();

		//đế nến dưới
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -4.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		model = glm::translate(model, glm::vec3(14.1f, 25.5f, -3.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture6.UseTexture();
		meshList[3]->RenderMesh();

		//đế nến trên
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -3.85f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(18.8f, 34.0f, -10.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture6.UseTexture();
		meshList[3]->RenderMesh();

		//chân nến nhỏ
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -5.2f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 1.0f));
		model = glm::translate(model, glm::vec3(56.5f, 102.0f, -3.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture6.UseTexture();
		meshList[3]->RenderMesh();

		//thân nến
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -4.75f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.7f));
		model = glm::translate(model, glm::vec3(28.3f, 51.0f, -4.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture7.UseTexture();
		meshList[4]->RenderMesh();

		//nến sáng
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-4.0f, -0.5f, -4.7f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.4f));
		model = glm::translate(model, glm::vec3(9.35f, 16.9f, -7.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		Texture6.UseTexture();
		meshList[8]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(4.0f, 40.0f, 14.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		chabo.renderChabo(projection, camera.calculateViewMatrix(), model);

		/*model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(1.0f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(4.0f, 40.0f, 14.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		chaboBodi.renderChaboBodi(projection, camera.calculateViewMatrix(), model);
		*/



		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;

};