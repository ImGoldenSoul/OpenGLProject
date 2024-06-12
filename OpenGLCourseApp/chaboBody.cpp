
#include "CHABObody.h"
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

ChaboBodi::ChaboBodi(Shader& shader) : shader(shader) {
	goldTexture2 = Texture("Textures/R1.jpg");
	
	meshList = std::vector<Mesh*>();
	
}

void ChaboBodi::CreateObjects()
{
	unsigned int indices0[] = {
			0, 2, 1, 1, 2, 3, // top face
			4, 5, 6, 4, 6, 7,
			8, 9, 10, 8, 10, 11,
			12, 14, 13, 12, 15, 14, //thuận
			16, 18, 17,19, 18, 16,// thuận
			20, 21, 22, 20, 22, 23 //thuận

	};
	GLfloat vertices0[] = {
		//    x       y      z        u      v   nx,  ny,  nz
			 -1.0f,  -1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //a
			 -1.0f,  1.0f,  1.0f,   1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //b
			 1.0f,  -1.0f,  1.0f,    0.0f, 0.0f, 0.0f, 1.0f, 0.0f, //c
			 1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //d

			1.0f,  -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, -1.0f, 0.0f, //c
			1.0f,  -1.0f,  -1.0f,   0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //e
			1.0f,  1.0f, -1.0f,     1.0f, 0.0f, 0.0f, -1.0f, 0.0f,//f
			1.0f,  1.0f, 1.0f,      1.0f, 1.0f, 0.0f, -1.0f, 0.0f,//d


			1.0f,  1.0f, 1.0f,      0.0f, 1.0f, 0.0f, -1.0f, 0.0f,//d
			1.0f,  1.0f, -1.0f,      0.0f, 0.0f, 0.0f, -1.0f, 0.0f,//f
			-1.0f, 1.0f, -1.0f,     1.0f, 0.0f, 0.0f, -1.0f, 0.0f,//g
			-1.0f,  1.0f,  1.0f,   1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //b

			1.0f,  -1.0f,  -1.0f,   0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //e
			1.0f,  1.0f, -1.0f,     1.0f, 0.0f, 0.0f, -1.0f, 0.0f,//f
			-1.0f, 1.0f, -1.0f,     1.0f, 1.0f, 0.0f, -1.0f, 0.0f,//g
			-1.0f, -1.0f, -1.0f,     0.0f, 1.0f, 0.0f, -1.0f, 0.0f,//h

			-1.0f,  -1.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //a
			-1.0f,  1.0f,  1.0f,   1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //b
			-1.0f, 1.0f, -1.0f,     1.0f, 0.0f, 0.0f, -1.0f, 0.0f,//g
			-1.0f, -1.0f, -1.0f,     0.0f, 0.0f, 0.0f, -1.0f, 0.0f,//h


			-1.0f,  -1.0f,  1.0f,   1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //a
			-1.0f, -1.0f, -1.0f,     0.0f, 1.0f, 0.0f, -1.0f, 0.0f,//h
			1.0f,  -1.0f,  -1.0f,   0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //e
			1.0f,  -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, -1.0f, 0.0f, //c



	};

	unsigned int indices1[] = {
			0, 2, 1, 1, 2, 3, // top face
			4, 5, 6, 4, 6, 7,
			8, 9, 10, 8, 10, 11,
			12, 14, 13, 12, 15, 14, //thuận
			16, 18, 17, 19, 18, 16,// thuận
			20, 21, 22, 20, 22, 23 //thuận

	};
	GLfloat vertices1[] = {
		//    x       y      z        u      v   nx,  ny,  nz
		-0.3f,  -0.3f,  0.6f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //a
		-0.3f,  0.3f,  0.6f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //b
		0.3f,  -0.3f,  0.6f,    0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //c
		0.3f,  0.3f,  0.6f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //d

		0.3f,  -0.3f,  0.6f,    0.0f, 1.0f, 0.0f, -1.0f, 0.0f, //c
		0.3f,  -0.3f,  -0.6f,   0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //e
		0.3f,  0.3f, -0.6f,     1.0f, 0.0f, 0.0f, -1.0f, 0.0f,//f
		0.3f,  0.3f, 0.6f,      1.0f, 1.0f, 0.0f, -1.0f, 0.0f,//d


		0.3f,  0.3f, 0.6,      0.0f, 1.0f, 0.0f, -1.0f, 0.0f,//d
		0.3f,  0.3f, -0.6f,     0.0f, 0.0f, 0.0f, -1.0f, 0.0f,//f
		-0.3f, 0.3f, -0.6f,     1.0f, 0.0f, 0.0f, -1.0f, 0.0f,//g
		-0.3f,  0.3f,  0.6f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //b




		0.3f,  -0.3f,  -0.6f,   0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //e
		0.3f,  0.3f, -0.6f,     1.0f, 0.0f, 0.0f, -1.0f, 0.0f,//f
		-0.3f, 0.3f, -0.6f,       1.0f, 1.0f, 0.0f, -1.0f, 0.0f,//g
		-0.3f, -0.3f, -0.6f,     0.0f, 1.0f, 0.0f, -1.0f, 0.0f,//h

		-0.3f,  -0.3f,  0.6f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //a
		-0.3f,  0.3f,  0.6f,   1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //b
		-0.3f, 0.3f, -0.6f,     1.0f, 0.0f, 0.0f, -1.0f, 0.0f,//g
		-0.3f, -0.3f, -0.6f,     0.0f, 0.0f, 0.0f, -1.0f, 0.0f,//h


		-0.3f,  -0.3f,  0.6f,   1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //a
		-0.3f, -0.3f, -0.6f,     0.0f, 1.0f, 0.0f, -1.0f, 0.0f,//h
		0.3f,  -0.3f,  -0.6f,   0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //e
		0.3f,  -0.3f,  0.6f,    1.0f, 0.0f, 0.0f, -1.0f, 0.0f, //c

	};

	Mesh* obj0 = new Mesh();
	obj0->CreateMesh(vertices0, indices0, 192, 36);
	meshList.push_back(obj0);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices1, indices1, 192, 36);
	meshList.push_back(obj1);
}


void ChaboBodi::renderChaboBodi(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model1)
{

	CreateObjects();

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

	shader.UseShader();
	uniformModel = shader.GetModelLocation();
	uniformProjection = shader.GetProjectionLocation();
	uniformView = shader.GetViewLocation();


	glm::mat4 model=model1;
	//glm::mat4 view(1.0f);
	//model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture2.UseTexture();
	meshList[0]->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-1.0f, -0.6f, 0.4f));
	// model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
   //  model = glm::scale(model, glm::vec3(0.9f, 0.9f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture2.UseTexture();
	meshList[1]->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 0.0f));
	//  model = glm::scale(model, glm::vec3(0.9f, 0.9f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture2.UseTexture();
	meshList[1]->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 0.0f));
	//  model = glm::scale(model, glm::vec3(0.9f, 0.9f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture2.UseTexture();
	meshList[1]->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, -1.0f));
	//  model = glm::scale(model, glm::vec3(0.9f, 0.9f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture2.UseTexture();
	meshList[1]->RenderMesh();
}


ChaboBodi::~ChaboBodi() {
	for (auto mesh : meshList) {
		delete mesh;
	}
}
