#include "AA4.h"

AA4::AA4()
{
	objMat = glm::mat4(1.0f);

	linVel = { 0, 0, 0 };
	angVel = { 0, 0, 0 };
	inertia = glm::mat3(0);

	mass = 1;

	cub = new Cub(objMat);
}

AA4::~AA4()
{
	delete cub;
}

void AA4::Update(float dt)
{
	cub->Update(dt);
}

void AA4::RenderUpdate()
{
	cub->RenderUpdate();
}

void AA4::RenderGui()
{
}
