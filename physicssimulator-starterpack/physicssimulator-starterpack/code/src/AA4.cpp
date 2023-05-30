//AA4.cpp
#include "AA4.h"

AA4::AA4()
{
	objMat = glm::mat4(1.0f);
	linVel = { 0, 5.0f, 0 };
	angVel = { 1.0f, 0, 0 };
	inertia = glm::mat3(0);
	acceleration = { 0, -9.81f, 0 };
	mass = 1;
	state.pos = { 0, 0, 0 };
	state.rotation = glm::quat(); // Initialize with identity rotation
	state.linMom = { 0, 0, 0 };
	state.angMom = { 0, 0, 0 };
	cub = new Cub(objMat, linVel, angVel, inertia, acceleration, mass, state);
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
	cub->RenderGui();
}