#include "Tela.h"

Tela::Tela(int rows, int cols, float startX, float startZ, float dist, float elast, float damp)
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

	// Molles
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int currentPosInMatrix = (i * rows) + j;

			//Structural
			if (j < cols - 1) 
				structural.emplace_back(elast, damp, positions[currentPosInMatrix], positions[currentPosInMatrix + 1]);
			if (i < rows - 1) 
				structural.emplace_back(elast, damp, positions[currentPosInMatrix], positions[currentPosInMatrix + cols]);

			//Shear
			if (j < cols - 1 && i < rows - 1) 
				structural.emplace_back(elast, damp, positions[currentPosInMatrix], positions[currentPosInMatrix + cols + 1]);
			if (j < cols - 1 && i > 0) 
				structural.emplace_back(elast, damp, positions[currentPosInMatrix], positions[currentPosInMatrix - cols + 1]);

			//Bending
			if (j < cols - 2) 
				structural.emplace_back(elast, damp, positions[currentPosInMatrix], positions[currentPosInMatrix + 2]);
			if (i < rows - 2) 
				structural.emplace_back(elast, damp, positions[currentPosInMatrix], positions[currentPosInMatrix + (cols * 2)]);
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
		VerletStep step = VerletStep::DoStep(
			positions[i],
			velocities[i],
			accelerations[i],
			dt
		);

		positions[i] = step.endPos;
		velocities[i] = step.endVel;
		//accelerations[i] = accelerations[i];
	}

	UpdateMesh();
}

void Tela::RenderUpdate()
{
	mesh->Update(&positions[0].x);
}

void Tela::RenderGui()
{
	ImGui::SliderFloat("SeparaciÅEPunts", &distance, MIN_DIST, MAX_DIST);
}

void Tela::UpdateMesh()
{
	AddForces();
}

void Tela::AddForces()
{

}