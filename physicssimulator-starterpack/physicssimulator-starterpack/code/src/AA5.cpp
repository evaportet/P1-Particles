#include "AA5.h"

AA5::AA5()
{
	rows = 18;
	cols = 14;
	startX = -2.5f;
	startY = 1.f;
	startZ = 2.f;

	
	a = 0.3f;
	wavelenght = 2.f;
	freq = 3.5f;
	phi = 3.9f;

	amplitude = 3.f;
	distance = 0.4f;

	olas.push_back(new Malla(rows, cols, startX, startY, startZ, a, wavelenght, freq, phi, amplitude, distance));
	olas.push_back(new Malla(rows, cols, startX, 1.5f, startZ, 0.5f, 3.f, 4.f, 4.2f, amplitude, distance));
	olas.push_back(new Malla(rows, cols, startX, 2.f, startZ, 0.1f, 1.f, 3.f, 3.5f, amplitude, distance));
}

AA5::~AA5()
{
	for (int i = 0; i < olas.size(); i++)
	{
		delete olas[i];
	}
}

void AA5::Update(float dt)
{
	for (int i = 0; i < olas.size(); i++)
	{ 
		olas[i]->Update(dt);
	}
}

void AA5::RenderUpdate()
{
	for (int i = 0; i < olas.size(); i++)
	{
		olas[i]->RenderUpdate();
	}
}

void AA5::RenderGui()
{
	for (int i = 0; i < olas.size(); i++)
	{
		olas[i]->RenderGui();
	}
}