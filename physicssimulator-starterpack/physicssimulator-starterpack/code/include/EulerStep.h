//EulerStep.h
#pragma once
#include <glm/glm.hpp>

struct EulerStep
{
	glm::vec3 endPos;
	glm::vec3 endVel;
	glm::vec3 prevPos;
	glm::vec3 prevVel;

	static EulerStep DoStep(glm::vec3 pos, glm::vec3 vel, glm::vec3 a, float dt)
	{
		EulerStep s;
		s.endPos = pos + dt * vel;
		s.endVel = vel + dt * a;

		s.prevPos = pos;
		s.prevVel = vel;
		return s;
	}
};