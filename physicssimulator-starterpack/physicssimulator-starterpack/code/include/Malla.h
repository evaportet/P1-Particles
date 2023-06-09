#pragma once
#include <PrimitiveManager.h>
#include <EulerStep.h>
#include <vector>
#include "imgui/imgui.h"

extern graphics::PrimitiveManager manager;

class Malla
{
public:
	Malla(int rows, int cols, float startX, float startY, float startZ, float a, float wavelenght, float freq, float phi, float amplitude, float dist);
	~Malla();
	void Update(float dt);
	void RenderUpdate();
	void RenderGui();
private:
	graphics::MeshPrimitive* mesh;
	int rows, cols;
	float startX, startY, startZ, a, wavelenght, freq, phi, amplitude, distance;
	float k;

	glm::vec3 direction;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> velocities;
	std::vector<glm::vec3> accelerations;


	const float MAX_DIST = 5.0f;
	const float MIN_DIST = 0.0f;
};
