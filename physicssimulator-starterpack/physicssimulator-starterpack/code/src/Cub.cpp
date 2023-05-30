//Cub.cpp
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

	objMat = glm::translate(glm::mat4(1.0f), state.pos); // Update the object matrix based on the new position

	// Apply the updated object matrix to the cube primitive
	cube->Update(objMat);
}

void Cub::RenderUpdate()
{
	// No changes needed in this method
}

void Cub::RenderGui()
{
	// No changes needed in this method
}