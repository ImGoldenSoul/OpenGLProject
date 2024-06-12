#pragma once
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

#define M_PI 3.14159265358979323846


class Chabo
{
private:
	std::vector<Mesh*> meshList;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Shader& shader;

public:
	Chabo(Shader& shader);
	~Chabo();
	Texture goldTexture;
	Texture hairTexture;
	Texture redTexture;
	Texture eyeTexture;
	void createSphere(float radius, int sectorCount, int stackCount);
	void createCircle(float radius, int segmentCount);
	void CreateObjects();
	void renderChabo(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model1);
};