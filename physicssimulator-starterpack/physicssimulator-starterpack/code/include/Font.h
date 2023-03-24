#pragma once
#include "Emiter.h"
#include<glm/gtx/rotate_vector.hpp>
#include "imgui/imgui.h"

class Font : public Emiter
{
public:
	Font(glm::vec3 pA, glm::vec3 dir, float dirMagnitude);
	~Font();

	void Update(float dt) override;

	void RenderGUI();

private:
	glm::vec3 pointA;
	glm::vec3 spawnVel;
	float velMagnitude;
	float angle;

	std::vector<float> lifeTimes;
};