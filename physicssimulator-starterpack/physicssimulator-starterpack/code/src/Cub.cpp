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

}

void Cub::RenderUpdate()
{
	cube->Update(objMat);
}

void Cub::RenderGui()
{
}
