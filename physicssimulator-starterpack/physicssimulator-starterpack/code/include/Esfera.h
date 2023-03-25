#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <vector>
#include <PrimitiveManager.h>

class Esfera
{
protected:
	graphics::SpherePrimitive* spherePrim;
	float radius;
	glm::vec3 position;

public:
	Esfera(float r, glm::vec3 p);
	~Esfera();

	void Update(float dt);
	void Render();
	void RenderGUI();
};