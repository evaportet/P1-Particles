#pragma once
#include <glm/glm.hpp>

struct VerletStep
{
	glm::vec3 endPos;
	glm::vec3 endVel;
	glm::vec3 currentPos;
	glm::vec3 currentVel;
	glm::vec3 prevPos;
	glm::vec3 prevVel;

	static VerletStep DoStep(glm::vec3 pos, glm::vec3 vel, glm::vec3 a, float dt)
	{
		VerletStep s;

		s.currentPos = pos;
		s.currentVel = vel;

		s.prevPos = pos - dt * vel;
		s.prevVel = vel - dt * a;

		s.endPos = s.currentPos + (s.currentPos - s.prevPos) + a * (dt * dt);
		s.endVel = (s.endPos - s.currentPos)/dt;

		return s;
	}
};