#pragma once
#include "Emiter.h"
#include<glm/gtx/rotate_vector.hpp>
#include "imgui/imgui.h"

class Font : public Emiter
{
public:
	Font(glm::vec3 p, glm::vec3 t, glm::vec3 r, glm::vec3 dir, float dirMagnitude);
	~Font();

	void Update(float dt) override;

	void RenderGUI();

private:
	glm::vec3 point;
	glm::vec3 target;
	glm::vec3 rotPoint;
	glm::vec3 spawnVel;
	float velMagnitude;
	float angle;

	std::vector<float> lifeTimes;
};