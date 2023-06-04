#include "Cub.h"

Cub::Cub(glm::mat4 objMat, glm::vec3 linVel, glm::vec3 angVel, glm::mat3 inertia, glm::vec3 acceleration, float mass, CubeState state)
{
	this->objMat = objMat;
	this->linVel = linVel;
	this->angVel = angVel;
	this->inertia = inertia;
	this->acceleration = acceleration;
	this->mass = mass;
	this->state = state;
	cube = manager.NewCube(this->objMat);
}

Cub::~Cub()
{
	manager.DestroyPrimitive(cube);
}

void Cub::Update(float dt)
{
	EulerStep step = EulerStep::DoStep(state.pos, linVel, acceleration, dt);

	state.pos = step.endPos;
	linVel = step.endVel;
	glm::vec3 linMom = linVel * mass;
	glm::vec3 angMom = angVel * inertia;

	state.rotation += 0.5f * dt * glm::quat(0.0f, angVel) * state.rotation;
	state.rotation = glm::normalize(state.rotation);

	objMat = glm::translate(glm::mat4(1.0f), state.pos) * (glm::mat4)state.rotation;

	cube->Update(objMat);
}

void Cub::RenderUpdate()
{
	
}

void Cub::RenderGui()
{
	
}

glm::vec3 Cub::GetPosition()
{
	return state.pos;
}