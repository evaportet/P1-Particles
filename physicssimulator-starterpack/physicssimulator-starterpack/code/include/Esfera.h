#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <vector>
#include <PrimitiveManager.h>
#include "imgui/imgui.h"

class Esfera
{
protected:
	graphics::SpherePrimitive* spherePrim;
	float radius;
	glm::vec3 position;

public:
	Esfera(float r, glm::vec3 p);
	~Esfera();

	void Render();
	void RenderGUI();
	void ToggleVisibility(bool val);
	bool PointInsideSphere(glm::vec3 p, Esfera* e);
	glm::vec3 GetPosition();
	float GetRadius();
};