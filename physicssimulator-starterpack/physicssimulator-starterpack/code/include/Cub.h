#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <PrimitiveManager.h>
#include "EulerStep.h"

extern graphics::PrimitiveManager manager;

struct CubeState
{
	glm::vec3 pos;
	glm::quat rotation;
	glm::vec3 linMom;
	glm::vec3 angMom;
};

class Cub
{
public:
	Cub(glm::mat4 objMat, glm::vec3 linVel, glm::vec3 angVel, glm::mat3 inertia, glm::vec3 acceleration, float mass, CubeState state);
	~Cub();
	void Update(float dt);
	void RenderUpdate();
	void RenderGui();
	float GetRandomNumber();

private:
	graphics::CubePrimitive* cube;
	CubeState state;
	glm::mat4 objMat;
	glm::vec3 linVel;
	glm::vec3 angVel;
	glm::mat3 inertia;
	glm::vec3 acceleration;
	float mass;
};