#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <vector>
#include <Maya.h>

class AA5 : public Simulator
{
public:
	AA5();
	~AA5();
	//Inherited via Simualtor
	void Update(float dt) override;
	void RenderUpdate() override;
	void RenderGui() override;
private:
	Maya* maya;
	int rows, cols;
	float startX, startZ, distance;
};