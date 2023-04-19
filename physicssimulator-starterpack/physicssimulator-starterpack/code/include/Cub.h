#pragma once
#include <PrimitiveManager.h>
#include "imgui/imgui.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
extern graphics::PrimitiveManager manager;

class Cub
{
public:
	Cub(glm::mat4 objMat, glm::mat3 rotMat, glm::vec3 angVel);
	~Cub();
	void Update(float dt);
	void RenderUpdate();
	void RenderGui();
private:
	graphics::CubePrimitive* cube;
	glm::mat4 objMat;
	glm::mat3 rotMat;
	glm::vec3 angVel;
};