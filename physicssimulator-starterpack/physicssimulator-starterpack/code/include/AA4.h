#pragma once
#include "Simulator.h"
#include "Cub.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Plano.h"

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

	Plano paredes[6] = {
		Plano(glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), 0.f),				//Terra
		Plano(glm::vec3(0.f, 10.f, 0.f), glm::vec3(0.f, -1.f, 0.f), 10.f),	//Sostre
		Plano(glm::vec3(5.f, 5.f, 0.f), glm::vec3(-1.f, 0.f, 0.f), 5.f),	//Dreta
		Plano(glm::vec3(-5.f, 5.f, 0.f), glm::vec3(1.f, 0.f, 0.f), 5.f),	//Esquerra
		Plano(glm::vec3(0.f, 5.f, -5.f), glm::vec3(0.f, 0.f, -1.f), 5.f),	//Fondo
		Plano(glm::vec3(0.f, 5.f, 5.f), glm::vec3(0.f, 0.f, 1.f), 5.f)		//Proxim
	};

	bool hasCollided;
};