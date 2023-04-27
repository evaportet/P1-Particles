#include "AA3.h"

AA3::AA3()
{
	rows = 18;
	cols = 14;
	startX = -2.5f;
	startZ = 2.f;
	distance = 0.4f;
	tela = new Tela(rows, cols, startX, startZ, distance);
}

AA3::~AA3()
{
	delete tela;
}

void AA3::Update(float dt)
{
	tela->Update(dt);
}

void AA3::RenderUpdate()
{
	tela->RenderUpdate();
}

void AA3::RenderGui()
{
	tela->RenderGui();
}