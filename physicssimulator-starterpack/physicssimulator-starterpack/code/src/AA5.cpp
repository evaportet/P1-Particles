#include "AA5.h"

AA5::AA5()
{
	rows = 18;
	cols = 14;
	startX = -2.5f;
	startZ = 2.f;
	distance = 0.4f;
	maya = new Maya(rows, cols, startX, startZ, distance);
}

AA5::~AA5()
{
	delete maya;
}

void AA5::Update(float dt)
{
	maya->Update(dt);
}

void AA5::RenderUpdate()
{
	maya->RenderUpdate();
}

void AA5::RenderGui()
{
	maya->RenderGui();
}