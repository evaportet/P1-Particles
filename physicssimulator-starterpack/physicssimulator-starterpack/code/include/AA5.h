#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <vector>
#include <Malla.h>

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
	//Malla* malla;
	std::vector<Malla*> olas;
	int rows, cols;
	float startX, startY, startZ, a, wavelenght, freq, phi, amplitude, distance;
};