
#include "CHABO.h"
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

Chabo::Chabo(Shader& shader) : shader(shader) {
	goldTexture = Texture("Textures/R.jpg");
	hairTexture = Texture("Textures/hair.png");
	redTexture = Texture("Textures/red.jpg");
	eyeTexture = Texture("Textures/eye.jpg");

	meshList = std::vector<Mesh*>();
	vertices = std::vector<float>();
	indices = std::vector<unsigned int>();
}


void Chabo::createSphere(float radius, int sectorCount, int stackCount) {
	float x, y, z, xy;                // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                       // vertex texCoord

	float sectorStep = float(2 * M_PI / sectorCount);
	float stackStep = float(M_PI / stackCount);
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = float(M_PI / 2 - i * stackStep);// starting from pi/2 to -pi/2
		xy = 1.02f * radius * cosf(stackAngle); // r * cos(u)
		z = radius * sinf(stackAngle);          // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep; // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);  // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);  // r * cos(u) * sin(v)
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			vertices.push_back(nx);
			vertices.push_back(ny);
			vertices.push_back(nz);

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			vertices.push_back(s);
			vertices.push_back(t);
		}
	}

	// generate CCW index list of sphere triangles
	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
}


void Chabo::createCircle(float radius, int segmentCount) {
	float x, y;    // vertex position

	// Add the center vertex
	vertices.push_back(0.0f);  // x
	vertices.push_back(0.0f);  // y

	float sectorStep = float(2 * M_PI / segmentCount);
	for (int i = 0; i <= segmentCount; ++i) {
		float sectorAngle = i * sectorStep; // starting from 0 to 2pi

		// vertex position (x, y)
		x = radius * cosf(sectorAngle);  // r * cos(v)
		y = radius * sinf(sectorAngle);  // r * sin(v)
		vertices.push_back(x);
		vertices.push_back(y);
	}

	// Generate triangle fan indices
	for (int i = 0; i < segmentCount; ++i) {
		indices.push_back(1); // Center vertex
		indices.push_back(i + 1);
		indices.push_back(i - 1);
	}
}

void Chabo::CreateObjects()
{
	unsigned int indices0[] = {
		0, 2, 1,
		0, 3, 2,
	};


	GLfloat vertices0[] = {
		//	x       y      z		u	  v   nx,  ny,  nz
		   5.0f, 5.0f,  5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		   5.0f, -5.0f,  5.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		  -5.0f, -5.0f,  5.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		  -5.0f, 5.0f,  5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned int indices1[] = {
		0, 2, 1,
		0, 3, 2,
	};


	GLfloat vertices1[] = {
		//	x       y      z		u	  v   nx,  ny,  nz
		   3.0f, 7.0f,  3.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		   3.0f, 5.0f,  3.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		  -3.0f, 5.0f,  3.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		  -3.0f, 7.0f,  3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned int indices2[] = {
		0, 2, 1,
		0, 3, 2,
	};


	GLfloat vertices2[] = {
		//	x       y      z		u	  v   nx,  ny,  nz
		   3.0f, 7.0f,  -3.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		   3.0f, 7.0f,  3.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		  -3.0f, 7.0f,  3.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		  -3.0f, 7.0f,  -3.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	};

	unsigned int indices3[] = {
		0, 2, 1,
		0, 3, 2,
		0, 1, 4,
		3, 5, 2,
		4, 1, 2,
		4, 2, 5,
	};


	GLfloat vertices3[] = {
		//	x       y      z		u	  v   nx,  ny,  nz
		   0.7f, 1.0f,  5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		   1.0f, -3.0f, 6.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		  -1.0f, -3.0f, 6.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		  -0.7f, 1.0f,  5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		   1.0f, -3.0f, 5.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		  -1.0f, -3.0f, 5.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	};

	unsigned int indices4[] = {
		0, 2, 1,
		0, 3, 2,
	};


	GLfloat vertices4[] = {
		//	x       y      z		u	  v   nx,  ny,  nz
			 5.0f, 5.0f,  5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 5.0f, 3.0f,  5.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-5.0f, 3.0f,  5.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-5.0f, 5.0f,  5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned int indices5[] = {
		0, 2, 1,
		0, 3, 2,
		0, 4, 5,
	};


	GLfloat vertices5[] = {
		//	x       y      z		u	  v   nx,  ny,  nz
			 5.0f, 5.0f,  5.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			 5.0f, 5.0f,  -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			 5.0f, 3.0f,  -5.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 5.0f, 3.0f,  5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 5.0f, -1.5f,  5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 5.0f, 5.0f,  2.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	};

	unsigned int indices6[] = {
		0, 2, 1,
		0, 3, 2,
	};


	GLfloat vertices6[] = {
		//	x       y      z		u	  v   nx,  ny,  nz
			 5.0f, 5.0f,  5.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
			 5.0f, -2.0f,  5.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
			-5.0f, -2.0f,  5.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			-5.0f, 5.0f,  5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
	};

	unsigned int indices7[] = {
		0, 2, 1,
		0, 3, 2,
		3, 4, 2,
		3, 5, 4,
		5, 7, 4,
		5, 6, 7,
	};


	GLfloat vertices7[] = {
		//	x       y      z		u	  v   nx,  ny,  nz
			 1.0f, -3.5f,  5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 1.0f, -3.8f,  5.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -4.0f,  5.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -3.8f,  5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -4.0f,  5.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -3.8f,  5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -3.5f,  5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -3.8f,  5.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned int indices8[] = {
		0, 5, 1,
		1, 5, 2,
		2, 5, 3,
		3, 5, 4,
	};


	GLfloat vertices8[] = {
		//	x       y      z		u	  v   nx,  ny,  nz
			 5.0f, 1.5f,  -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 6.0f, 1.5f,  -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 6.0f, 0.0f,  -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 7.0f, 0.0f,  -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 7.0f, -2.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 5.0f, -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	Mesh* obj0 = new Mesh();
	obj0->CreateMesh(vertices0, indices0, 32, 6);
	meshList.push_back(obj0);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices1, indices1, 32, 6);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices2, indices2, 32, 6);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(vertices3, indices3, 48, 18);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vertices4, indices4, 32, 6);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(vertices5, indices5, 48, 9);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(vertices6, indices6, 32, 6);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(vertices7, indices7, 64, 18);
	meshList.push_back(obj7);

	Mesh* obj8 = new Mesh();
	obj8->CreateMesh(vertices8, indices8, 48, 12);
	meshList.push_back(obj8);
}


void Chabo::renderChabo(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model1)
{	

	CreateObjects();

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	

	//Create a sphere
	createSphere(1.0f, 30, 30);
	// Create a mesh object for the sphere
	Mesh* sphereMesh = new Mesh();
	sphereMesh->CreateMesh(vertices.data(), indices.data(), vertices.size(), indices.size());

	// Clear the vertices and indices vectors for the next sphere
	vertices.clear();
	indices.clear();

	createSphere(0.5f, 30, 30);
	Mesh* sphereMesh1 = new Mesh();
	sphereMesh1->CreateMesh(vertices.data(), indices.data(), vertices.size(), indices.size());

	vertices.clear();
	indices.clear();

	// Create circle
	createCircle(1.0f, 360);
	Mesh* circleMesh2 = new Mesh();
	circleMesh2->CreateMesh(vertices.data(), indices.data(), vertices.size(), indices.size());

	vertices.clear();
	indices.clear();

	createCircle(0.5f, 360);
	Mesh* circleMesh1 = new Mesh();
	circleMesh1->CreateMesh(vertices.data(), indices.data(), vertices.size(), indices.size());

	vertices.clear();
	indices.clear();


	shader.UseShader();
	uniformModel = shader.GetModelLocation();
	uniformProjection = shader.GetProjectionLocation();
	uniformView = shader.GetViewLocation();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

	//head
	glm::mat4 model = model1;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture.UseTexture();
	meshList[0]->RenderMesh();


	model = model1;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture.UseTexture();
	meshList[0]->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture.UseTexture();
	meshList[0]->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture.UseTexture();
	meshList[0]->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture.UseTexture();
	meshList[0]->RenderMesh();

	//nose
	model = model1;
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture.UseTexture();
	meshList[3]->RenderMesh();

	//hair
	model = model1;
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[0]->RenderMesh();

	model = model1;
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[1]->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[1]->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[1]->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[1]->RenderMesh();

	model = model1;
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[2]->RenderMesh();

	model = model1;
	model = glm::translate(model, glm::vec3(0, 0, 0.1));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[4]->RenderMesh();

	model = model1;
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[5]->RenderMesh();

	model = model1;
	model = glm::translate(model, glm::vec3(-10.1, 0, 0));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[5]->RenderMesh();

	model = model1;
	model = glm::translate(model, glm::vec3(0, 0, -10.1));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[6]->RenderMesh();

	// Hair sphere
	glm::mat4 modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(0, 6, 4)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(2, 6, 4));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-2, 6, 4)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(4, 6, 4));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-4, 6, 4));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(0, 6, -4)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(2, 6, -4)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-2, 6, -4)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(4, 6, -4)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-4, 6, -4)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(4, 6, 2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(4, 6, 0)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(4, 6, -2));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-4, 6, -2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-4, 6, 0));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-4, 6, 2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(0, 8, 2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(2, 8, 2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-2, 8, 2));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(0, 8, 0)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(0, 8, -2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-2, 8, 0)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-2, 8, -2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(2, 8, 0)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(2, 8, -2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(1, 9, 1)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-1, 9, 1)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-1, 9, -1));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(1, 9, -1)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(0, 10, 0));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(0, 4.5, 5)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(2, 4.5, 5)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(4, 4.5, 5)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-2, 4.5, 5)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-4, 4.5, 5)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-5, 4, 4)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-5, 4, 2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-5, 4, 0)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-5, 4, -2));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(-5, 4, -4));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(5, 4, 4)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(5, 4, 2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(5, 4, 0)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(5, 4, -2)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(5, 4, -4)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	hairTexture.UseTexture();
	sphereMesh->RenderMesh();

	modelSphere = model1;
	modelSphere = glm::translate(modelSphere, glm::vec3(0, 2, 5)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelSphere));
	redTexture.UseTexture();
	sphereMesh1->RenderMesh();

	//mouth
	glm::mat4 modelCircle = model1;
	modelCircle = glm::rotate(modelCircle, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	modelCircle = glm::rotate(modelCircle, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelCircle = glm::translate(modelCircle, glm::vec3(-6.3, 0, 0.8)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCircle));
	eyeTexture.UseTexture();
	circleMesh1->RenderMesh();

	//eye
	model = model1;
	model = glm::translate(model, glm::vec3(3, 4, 0.1));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[7]->RenderMesh();


	model = model1;
	model = glm::translate(model, glm::vec3(-3, 4, 0.1));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	hairTexture.UseTexture();
	meshList[7]->RenderMesh();

	//ear

	model = model1;
	model = glm::translate(model, glm::vec3(0, 0, 2));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture.UseTexture();
	meshList[8]->RenderMesh();

	glm::mat4 modelCircle1 = model1;
	modelCircle1 = glm::rotate(modelCircle1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	modelCircle1 = glm::rotate(modelCircle1, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelCircle1 = glm::translate(modelCircle1, glm::vec3(-2.3, 6, -1)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCircle1));
	goldTexture.UseTexture();
	circleMesh2->RenderMesh();

	model = model1;
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	goldTexture.UseTexture();
	meshList[8]->RenderMesh();

	modelCircle1 = model1;
	modelCircle1 = glm::rotate(modelCircle1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	modelCircle1 = glm::rotate(modelCircle1, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelCircle1 = glm::translate(modelCircle1, glm::vec3(-2.3, -6, -1)); 
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCircle1));
	goldTexture.UseTexture();
	circleMesh2->RenderMesh();
}


Chabo::~Chabo() {
	for (auto mesh : meshList) {
		delete mesh;
	}
}
