#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <vector>
#include <PrimitiveManager.h>
#include "imgui/imgui.h"

class Pastilla
{
protected:
	graphics::CapsulePrimitive* capsulePrim;
	float radius;
	glm::vec3 position1;
	glm::vec3 position2;
public:
	Pastilla(glm::vec3 p1, glm::vec3 p2, float r);
	~Pastilla();

	void Render();
	void RenderGUI();
	void ToggleVisibility(bool val);
	bool PointInsideCapsule(glm::vec3 p, Pastilla* c);
	glm::vec3 GetPosition1();
	glm::vec3 GetPosition2();
	float GetRadius();
};