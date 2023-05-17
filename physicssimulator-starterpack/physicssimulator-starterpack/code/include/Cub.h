#pragma once
#include <PrimitiveManager.h>
#include "imgui/imgui.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
extern graphics::PrimitiveManager manager;

struct CubeState
{
	glm::vec3 pos;
	glm::quat rotation;
	glm::vec3 linMom;
	glm::vec3 angMom;
};

class Cub
{
public:
	Cub(glm::mat4 objMat, glm::vec3 linVel, glm::vec3 angVel, glm::mat3 inertia, glm::vec3 acceleration, float mass, CubeState state);
	~Cub();
	void Update(float dt);
	void RenderUpdate();
	void RenderGui();
private:
	graphics::CubePrimitive* cube;
	CubeState state;

	glm::mat4 objMat;

	glm::vec3 linVel;
	glm::vec3 angVel;

	glm::mat3 inertia;

	glm::vec3 acceleration;

	float mass;
};