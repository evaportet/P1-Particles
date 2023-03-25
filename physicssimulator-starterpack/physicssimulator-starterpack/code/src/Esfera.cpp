#include <Esfera.h>

extern graphics::PrimitiveManager manager;

Esfera::Esfera(float r, glm::vec3 p) : radius(r), position(p) 
{
	spherePrim = manager.NewSphere(p, r);
};

Esfera::~Esfera()
{
	manager.DestroyPrimitive(spherePrim);
}

void Esfera::Update(float dt)
{

}

void Esfera::Render()
{

}

void Esfera::RenderGUI()
{

}