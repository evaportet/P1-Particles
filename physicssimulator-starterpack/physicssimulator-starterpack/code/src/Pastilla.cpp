#include <Pastilla.h>

extern graphics::PrimitiveManager manager;

Pastilla::Pastilla(glm::vec3 p1, glm::vec3 p2, float r) : position1(p1), position2(p2), radius(r)
{
	capsulePrim = manager.NewCapsule(p1, p2,r);
};

Pastilla::~Pastilla()
{
	manager.DestroyPrimitive(capsulePrim);
}

void Pastilla::Render()
{
	capsulePrim->Update(position1, position2, radius);
}

void Pastilla::RenderGUI()
{
	ImGui::SliderFloat("Capsule Radius",
		&radius,
		0,
		30);

	ImGui::Spacing();
	ImGui::SliderFloat("Capsule Side 1 Position X", &position1[0], -5.f, 5.f);
	ImGui::SliderFloat("Capsule Side 1 Position Y", &position1[1], 0.f, 10.f);
	ImGui::SliderFloat("Capsule Side 1 Position Z", &position1[2], -5.f, 5.f);
	ImGui::SliderFloat("Capsule Side 2 Position X", &position2[0], -5.f, 5.f);
	ImGui::SliderFloat("Capsule Side 2Position Y", &position2[1], 0.f, 10.f);
	ImGui::SliderFloat("Capsule Side 2Position Z", &position2[2], -5.f, 5.f);
}