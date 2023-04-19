#include "AA3.h"

AA3::AA3()
{
	rows = 18;
	cols = 14;
	startX = -4.0f;
	startY = 10.0f;
	distance = 0.4f;
	tela = new Tela(rows, cols, startX, startY, distance);
}

AA3::~AA3()
{
	delete tela;
}

void AA3::RenderUpdate()
{
	tela->RenderUpdate();
}

void AA3::RenderGui()
{
	tela->RenderGui();
}