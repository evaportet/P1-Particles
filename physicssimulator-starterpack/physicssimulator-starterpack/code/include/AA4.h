#pragma once
#include "Simulator.h"
#include "Cub.h"

struct CubeState
{
	glm::vec3 pos;
	glm::quat rotation;
	glm::vec3 linMom;
	glm::vec3 angMom;
};

class AA4 : public Simulator
{
public:
	AA4();
	~AA4();
	void Update(float dt);
	void RenderUpdate();
	void RenderGui();
private:
	Cub* cub;
	CubeState state;

	glm::mat4 objMat;

	glm::vec3 linVel;
	glm::vec3 angVel;

	glm::mat3 inertia;

	float mass;
};

