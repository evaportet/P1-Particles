#include "Cub.h"

Cub::Cub(glm::mat4 objMat, glm::mat3 rotMat, glm::vec3 angVel)
{
	this->objMat = objMat;
	this->rotMat = rotMat;
	this->angVel = angVel;
	cube = manager.NewCube(this->objMat);
}

Cub::~Cub()
{
	manager.DestroyPrimitive(cube);
}

void Cub::Update(float dt)
{
	glm::mat3 angVelMat = glm::mat3(glm::vec3(0, -angVel.z, angVel.y), glm::vec3(angVel.z,  0, -angVel.x), glm::vec3(-angVel.y, angVel.z, 0));
	rotMat = rotMat + dt * (angVelMat * rotMat);
	std::cout << glm::to_string(rotMat) << std::endl;
}

void Cub::RenderUpdate()
{
	cube->Update(rotMat);
}

void Cub::RenderGui()
{
}
