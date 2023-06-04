#pragma once
#include "Simulator.h"
#include "Cub.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

class AA4 : public Simulator
{
public:
	AA4();
	~AA4();
	void Update(float dt);
	void RenderUpdate();
	void RenderGui();

	void InitCube();
	float GetRandomNumber();

private:
	Cub* cub;
	CubeState state;
	glm::mat4 objMat;
	glm::vec3 linVel;
	glm::vec3 angVel;
	glm::mat3 inertia;
	glm::vec3 acceleration;
	float mass;

	float currentTime;
	float maxTime;
};