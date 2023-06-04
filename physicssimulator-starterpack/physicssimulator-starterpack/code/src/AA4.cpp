#include "AA4.h"

AA4::AA4()
{
	maxTime = 15;
	currentTime = 0;
	hasCollided = false;
	InitCube();
}

AA4::~AA4()
{
	delete cub;
}

void AA4::Update(float dt)
{
	currentTime += 0.1f;
	cub->Update(dt);

	for (int j = 0; j < 6; j++)
	{
		if (Plano::colisionPointPlane(&paredes[j], cub->GetPosition()) && !hasCollided)
		{
			printf("COLLIDED");
			hasCollided = true;
		}
	}

	if (currentTime >= maxTime)
	{
		delete cub;
		InitCube();
		currentTime = 0;
		hasCollided = false;
	}
}

void AA4::RenderUpdate()
{
	cub->RenderUpdate();
}

void AA4::RenderGui()
{
	cub->RenderGui();
}

void AA4::InitCube()
{
	objMat = glm::mat4(1.0f);
	linVel = { GetRandomNumber(), GetRandomNumber(), GetRandomNumber() };
	angVel = { GetRandomNumber(), GetRandomNumber(), GetRandomNumber() };
	inertia = glm::mat3(0);
	acceleration = { 0, -9.81f, 0 };
	mass = 1;
	state.pos = { 0, 5, 0 };
	state.rotation = glm::quat();
	state.linMom = { 0, 0, 0 };
	state.angMom = { 0, 0, 0 };
	cub = new Cub(objMat, linVel, angVel, inertia, acceleration, mass, state);
}

float AA4::GetRandomNumber()
{
	srand(time(NULL));
	return rand() % 5;
}