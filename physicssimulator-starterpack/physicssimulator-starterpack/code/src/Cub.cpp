#include "Cub.h"

Cub::Cub(glm::mat4 objMat)
{
	this->objMat = objMat;
	rotMat = glm::mat3(0);
	angVel = {0, 0, 0};
	cube = manager.NewCube(this->objMat);
}

Cub::~Cub()
{
	manager.DestroyPrimitive(cube);
}

void Cub::Update(float dt)
{
	/*glm::mat3 angVelMat = glm::mat3(glm::vec3(0, -angVel.z, angVel.y), glm::vec3(angVel.z,  0, -angVel.x), glm::vec3(-angVel.y, angVel.z, 0));
	rotMat = rotMat + dt * (angVelMat * rotMat);*/
}

void Cub::RenderUpdate()
{
	cube->Update(objMat);
}

void Cub::RenderGui()
{
}
