#include "AA4.h"

AA4::AA4()
{
	objMat = glm::mat4(1.0f);

	//Definir Angles d'Euler
	roll = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;

	//Definir Velocitat Angular
	angVel = glm::vec3(0.0f, 1.0f, 0.0f) * 3.0f;

	//Matriu de Rotació
	glm::mat3 Rx = glm::mat3(glm::vec3(1, 0, 0), glm::vec3(0, glm::cos(roll), -glm::sin(roll)), glm::vec3(0, glm::sin(roll), glm::cos(roll)));
	glm::mat3 Ry = glm::mat3(glm::vec3(glm::cos(pitch), 0, glm::sin(pitch)), glm::vec3(0, 1, 0), glm::vec3(-glm::sin(pitch), 0, glm::cos(pitch)));
	glm::mat3 Rz = glm::mat3(glm::vec3(glm::cos(yaw), -glm::sin(yaw), 0), glm::vec3(glm::sin(yaw), glm::cos(yaw), 0), glm::vec3(0, 0, 1));

	rotMat = Rz * Ry * Rx;

	cub = new Cub(objMat, rotMat, angVel);
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
