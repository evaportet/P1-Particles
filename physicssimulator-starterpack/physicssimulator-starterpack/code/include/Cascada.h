#pragma once
#include "Emiter.h"
#include<glm/gtx/rotate_vector.hpp>
#include "imgui/imgui.h"

class Cascada : public Emiter
{
public:
	Cascada(glm::vec3 pA, glm::vec3 pB, glm::vec3 dir, float dirMagnitude);
	~Cascada();

	void Update(float dt) override;
	void UpdateParticle(int index, glm::vec3 pos, glm::vec3 vel, glm::vec3 a, float dt) override;

	void RenderGUI();

private:
	glm::vec3 pointA;
	glm::vec3 pointB;
	glm::vec3 spawnVel;
	float velMagnitude;
	float angle;

	std::vector<float> lifeTimes;
};
