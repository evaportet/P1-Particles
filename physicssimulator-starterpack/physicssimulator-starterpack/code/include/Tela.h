#pragma once
#include <PrimitiveManager.h>
#include "imgui/imgui.h"

extern graphics::PrimitiveManager manager;

class Tela
{
public:
	Tela(int rows, int cols, float startX, float startY, float dist);
	~Tela();
	void Update(float dt);
	void RenderUpdate();
	void RenderGui();
private:
	graphics::MeshPrimitive* mesh;
	int rows, cols;
	float startX, startY, distance;

	const float MAX_DIST = 5.0f;
	const float MIN_DIST = 0.0f;
};

