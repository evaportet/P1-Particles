#pragma once
#include "Simulator.h"
#include "Cub.h"

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
	glm::mat4 objMat;
	glm::mat3 rotMat;

	glm::vec3 angVel;

	//Euler Angles
	float roll, pitch, yaw;
};

