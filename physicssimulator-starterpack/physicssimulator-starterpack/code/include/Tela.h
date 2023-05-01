#pragma once
#include <PrimitiveManager.h>
#include <EulerStep.h>
#include <VerletStep.h>
#include <Molla.h>
#include <vector>
#include "imgui/imgui.h"

extern graphics::PrimitiveManager manager;

class Tela
{
public:
	Tela(int rows, int cols, float startX, float startZ, float dist, float elast, float damp);
	~Tela();
	void Update(float dt);
	void RenderUpdate();
	void RenderGui();

	void UpdateMesh();
	void AddForces();
private:
	graphics::MeshPrimitive* mesh;
	int rows, cols;
	float startX, startZ, distance;
	glm::vec3 gravity = glm::vec3(0.f, -9.81f, 0.f);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> velocities;
	std::vector<glm::vec3> accelerations;

	std::vector<int> posX;
	std::vector<int> posY;

	std::vector<Molla> structural;
	std::vector<Molla> shear;
	std::vector<Molla> bending;


	const float MAX_DIST = 5.0f;
	const float MIN_DIST = 0.0f;
};

