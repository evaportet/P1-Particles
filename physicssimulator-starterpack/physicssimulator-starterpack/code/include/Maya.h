#pragma once
#include <PrimitiveManager.h>
#include <EulerStep.h>
#include <vector>
#include "imgui/imgui.h"

extern graphics::PrimitiveManager manager;

class Maya
{
public:
	Maya(int rows, int cols, float startX, float startZ, float dist);
	~Maya();
	void Update(float dt);
	void RenderUpdate();
	void RenderGui();
private:
	graphics::MeshPrimitive* mesh;
	int rows, cols;
	float startX, startZ, distance;
	glm::vec3 gravity = glm::vec3(0.f, -9.81f, 0.f);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> velocities;
	std::vector<glm::vec3> accelerations;


	const float MAX_DIST = 5.0f;
	const float MIN_DIST = 0.0f;
};