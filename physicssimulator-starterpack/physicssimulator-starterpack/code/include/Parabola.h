#pragma once
#include<Emiter.h>
#include<Cascada.h>
#include<Font.h>
#include "imgui/imgui.h"

class ParabolaSim : public Simulator {
public:
	ParabolaSim();
	~ParabolaSim();

	void Update(float dt) override;
	void RenderUpdate() override;
	void RenderGui() override;
	//void EulerSolver(float dt);

private:
	Emiter* emiter1;
	Emiter* emiter2;
};