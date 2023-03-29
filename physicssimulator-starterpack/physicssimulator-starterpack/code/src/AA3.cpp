#include "AA3.h"

AA3::AA3()
{
	mesh = manager.NewMesh(18, 14);
}

AA3::~AA3()
{
	manager.DestroyPrimitive(mesh);
}

void AA3::Update(float dt)
{

}

void AA3::RenderUpdate()
{
	std::vector<glm::vec3> positions;
	float dist = 0.4f;
	float startY = 9.f;
	float startX = -4.f;
	for (int i = 0; i < 18; i++)
	{
		float y = startY - dist * i;
		for (int j = 0; j < 14; j++)
		{
			float x = startX + dist * j;
			positions.push_back(glm::vec3(x, y, 0.f));
		}
	}
	mesh->Update(&positions[0].x);
}

void AA3::RenderGui()
{

}