#include "Tela.h"

Tela::Tela(int rows, int cols, float startX, float startZ, float dist)
{
	this->rows = rows;
	this->cols = cols;
	this->startX = startX;
	this->startZ = startZ;
	this->distance = dist;
	mesh = manager.NewMesh(this->rows, this->cols);

	for (int i = 0; i < rows; i++)
	{
		float z = startZ - distance * i;
		for (int j = 0; j < cols; j++)
		{
			float x = startX + distance * j;
			positions.emplace_back(x, 9.f, z);
			velocities.emplace_back(0.f, 0.f, 0.f);
			accelerations.emplace_back(gravity);
		}
	}
}

Tela::~Tela()
{
	manager.DestroyPrimitive(mesh);
}

void Tela::Update(float dt)
{
	for (int i = 0; i < positions.size(); i++)
	{
		EulerStep step = EulerStep::DoStep(
			positions[i],
			velocities[i],
			accelerations[i],
			dt
		);

		positions[i] = step.endPos;
		velocities[i] = step.endVel;
		//accelerations[i] = accelerations[i];
	}
}

void Tela::RenderUpdate()
{
	mesh->Update(&positions[0].x);
}

void Tela::RenderGui()
{
	ImGui::SliderFloat("Separació Punts", &distance, MIN_DIST, MAX_DIST);
}