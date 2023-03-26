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

void Pastilla::ToggleVisibility(bool val)
{
	capsulePrim->SetVisible(val);
}

bool Pastilla::PointInsideCapsule(glm::vec3 p, Pastilla* c)
{
	glm::vec3 puntProper, vectorPastilla, vectorDistancia, aux;
	puntProper = p;
	vectorPastilla = c->position2 - c->position1;
	//Q' = A `clamp (((P'-A)*(B-A))/(B-A)^2, 0.1) * (B-A)
	//CLAMP manual perque el glm::clamp i std::clamp no va
	aux = ((puntProper - c->position1) * vectorPastilla)  / (vectorPastilla * vectorPastilla);
	if (aux.x > 0.1f) aux.x = 0.1f; if (aux.x < -0.1f) aux.x = -0.1f;
	if (aux.y > 0.1f) aux.y = 0.1f; if (aux.y < -0.1f) aux.y = -0.1f;
	if (aux.z > 0.1f) aux.z = 0.1f; if (aux.z < -0.1f) aux.z = -0.1f;

	vectorDistancia = c->position1 + aux * vectorPastilla;
	float distancia = sqrt(vectorDistancia.x * vectorDistancia.x + vectorDistancia.y * vectorDistancia.y + vectorDistancia.z * vectorDistancia.z);
	return distancia <= radius;
}

glm::vec3 Pastilla::GetPosition1()
{
	return position1;
}

glm::vec3 Pastilla::GetPosition2()
{
	return position2;
}

float Pastilla::GetRadius()
{
	return radius;
}