#include "Tela.h"

Tela::Tela(int rows, int cols, float startX, float startY, float dist)
{
	this->rows = rows;
	this->cols = cols;
	this->startX = startX;
	this->startY = startY;
	this->distance = dist;
	mesh = manager.NewMesh(this->rows, this->cols);
}

Tela::~Tela()
{
	manager.DestroyPrimitive(mesh);
}

void Tela::Update(float dt)
{

}

void Tela::RenderUpdate()
{
	std::vector<glm::vec3> positions;
	for (int i = 0; i < rows; i++)
	{
		float y = startY - distance * i;
		for (int j = 0; j < cols; j++)
		{
			float x = startX + distance * j;
			positions.push_back(glm::vec3(x, y, 0.f));
		}
	}
	mesh->Update(&positions[0].x);
}

void Tela::RenderGui()
{
	ImGui::SliderFloat("Separació Punts", &distance, MIN_DIST, MAX_DIST);
}