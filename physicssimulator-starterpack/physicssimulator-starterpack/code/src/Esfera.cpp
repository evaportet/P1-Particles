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

void Esfera::Render()
{
	spherePrim->Update(position, radius);
}

void Esfera::RenderGUI()
{
	ImGui::SliderFloat("Sphere Radius",
		&radius,
		0,
		30);

	ImGui::Spacing();
	ImGui::SliderFloat("Sphere Position X", &position[0], -5.f, 5.f);
	ImGui::SliderFloat("Sphere Position Y", &position[1], 0.f, 10.f);
	ImGui::SliderFloat("Sphere Position Z", &position[2], -5.f, 5.f);
}