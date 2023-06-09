#include "Malla.h"

Malla::Malla(int rows, int cols, float startX, float startY, float startZ, float a, float wavelenght, float freq, float phi, float amplitude, float dist)
{
	this->rows = rows;
	this->cols = cols;
	this->startX = startX;
	this->startZ = startZ;
	this->startY = startY;
	this->amplitude = amplitude;
	this->distance = dist;
	this->a = a;
	this->wavelenght = wavelenght;
	this->freq = freq;
	this->phi = phi;
	mesh = manager.NewMesh(this->rows, this->cols);

	for (int i = 0; i < rows; i++)
	{
		float z = startZ - distance * i;
		for (int j = 0; j < cols; j++)
		{
			float x = startX + distance * j;
			positions.emplace_back(x, startY, z);
			velocities.emplace_back(0.f, 0.f, 0.f);
			accelerations.emplace_back(0.f, 0.f, 0.f);
		}
	}
	
	//Gerstner waves
	k = 2 * glm::pi<float>() / wavelenght; 
	direction = glm::vec3(0.05f, 0.f, 0.f);
}

Malla::~Malla()
{
	manager.DestroyPrimitive(mesh);
}

void Malla::Update(float dt)
{
	/*for (int i = 0; i < positions.size(); i++)
	{*/
		//Gerstner waves	
		//positions[i].x = startX - amplitude * glm::sin(k * startX - (freq * dt) + phi);
		//positions[i].y = amplitude * glm::cos(k * startX - (freq * dt) + phi);
		//positions[i].z = startZ - amplitude * glm::sin(k * startZ - (freq * dt) + phi);

		//glm::vec3 position = direction * amplitude * glm::sin(glm::dot(direction, glm::vec3(startX, startY, startZ)) - (freq * dt) + phi);
		//position.y = amplitude * glm::cos(glm::dot(direction, glm::vec3(startX, startY, startZ)) - (freq * dt) + phi);

		glm::vec3 position = direction * amplitude * glm::sin(glm::dot(direction, positions[0]) - (freq * dt) + phi);
		position.y = amplitude * glm::cos(glm::dot(direction, positions[0]) - (freq * dt) + phi);

		positions[0] = position;
	//}
}

void Malla::RenderUpdate()
{
	mesh->Update(&positions[0].x);
}

void Malla::RenderGui()
{
	//ImGui::SliderFloat("Separacio Punts", &distance, MIN_DIST, MAX_DIST);
}