#pragma once
#include <Simulator.h>

class AA3 : public Simulator
{
public:
	AA3();
	~AA3();
	//Inherited via Simualtor
	void Update(float dt) override;
	void RenderUpdate() override;
	void RenderGui() override;
};

