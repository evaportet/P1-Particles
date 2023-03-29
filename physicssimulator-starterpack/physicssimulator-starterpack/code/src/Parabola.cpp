#include <Parabola.h>


ParabolaSim::ParabolaSim() 
{
	emiter1 = new Cascada(glm::vec3(-1.f, 6.f, 0.f), glm::vec3(1.f, 6.f, 0.f), glm::vec3(0.f, 0.f, 1.f), 5.f);
	cascadeActive = true;
	emiter2 = new Font(glm::vec3(-1.f, 6.f, 0.f), glm::vec3(-1.f, 12.f, 0.f), glm::vec3(1.f, 6.f, 0.f), glm::vec3(0.f, 0.f, 1.f), 5.f);
	fountainActive = false;
	esfera = new Esfera(3, glm::vec3(0.5f, 0.f, -4.f));
	sphereActive = false;
	pastilla = new Pastilla(glm::vec3(3.f, 0.f, 3.f), glm::vec3(3.f, 2.f, 3.f), 3);
	sphereActive = false;
}

ParabolaSim::~ParabolaSim() 
{
	delete emiter1;
	delete emiter2;
	delete esfera;
	delete pastilla;
}

ParabolaSim::CollisionBounceResult PlaneCollisionMirror(EulerStep s, Plano* p)
{
	ParabolaSim::CollisionBounceResult res;
	//p = P' -2 * (n * P' + d) * n
	res.resPos = s.endPos - 2.f * (p->GetNormal() * s.endPos + p->GetD()) * p->GetNormal();
		//v = v' -2 * (n * v') * n
	res.resVel = s.endVel - 2.f * ((p->GetNormal() * s.endVel)) * p->GetNormal();

	return res;
}

void ParabolaSim::Update(float dt) 
{
	if (cascadeActive) {
		for (int i = 0; i < emiter1->GetNumParticles(); i++)
		{
			EulerStep step = EulerStep::DoStep(
				emiter1->GetParticlePosition(i),
				emiter1->GetParticleVelocity(i),
				emiter1->GetParticleAcceleration(i),
				dt
			);
			emiter1->UpdateParticle(i, step.endPos, step.endVel, emiter1->GetParticleAcceleration(i), dt);
			for (int j = 0; j < 6; j++)
			{
				if (Plano::colisionPointPlane(&paredes[j], emiter1->GetParticlePosition(i)))
				{
					CollisionBounceResult res = PlaneCollisionMirror(step, &paredes[j]);
					emiter1->UpdateParticle(i, res.resPos, res.resVel, emiter1->GetParticleAcceleration(i), 0);
				}
			}
		}
		emiter1->Update(dt);
	}

	if (fountainActive) {
		for (int i = 0; i < emiter2->GetNumParticles(); i++)
		{
			EulerStep step = EulerStep::DoStep(
				emiter2->GetParticlePosition(i),
				emiter2->GetParticleVelocity(i),
				emiter2->GetParticleAcceleration(i),
				dt
			);
			emiter2->UpdateParticle(i, step.endPos, step.endVel, emiter2->GetParticleAcceleration(i), dt);
			for (int j = 0; j < 6; j++)
			{
				if (Plano::colisionPointPlane(&paredes[j], emiter2->GetParticlePosition(i)))
				{
					CollisionBounceResult res = PlaneCollisionMirror(step, &paredes[j]);
					emiter2->UpdateParticle(i, res.resPos, res.resVel, emiter2->GetParticleAcceleration(i), 0);
				}
			}
		}
		emiter2->Update(dt);		
	}
}
void ParabolaSim::RenderUpdate() 
{	
	emiter1->ToggleVisibility(cascadeActive);
	emiter2->ToggleVisibility(fountainActive);
	esfera->ToggleVisibility(sphereActive);
	pastilla->ToggleVisibility(capsuleActive);

	if (cascadeActive) emiter1->Render();
	if (fountainActive) emiter2->Render();
	if (sphereActive) esfera->Render();
	if (capsuleActive) pastilla->Render();
}
void ParabolaSim::RenderGui() 
{
	ImGui::Checkbox("Cascada", &cascadeActive);
	if (cascadeActive) {
		ImGui::Text("CASCADA:");
		emiter1->RenderGUI();
	}
	ImGui::Checkbox("Font", &fountainActive);
	if (fountainActive) {
		ImGui::Spacing();
		ImGui::Text("FUENTE:");
		ImGui::Spacing();
		emiter2->RenderGUI();
	}
	ImGui::Checkbox("Esfera", &sphereActive);
	if (sphereActive) {
		ImGui::Spacing();
		ImGui::Text("ESFERA:");
		ImGui::Spacing();
		esfera->RenderGUI();
	}
	ImGui::Checkbox("Pastilla", &capsuleActive);
	if (capsuleActive) {
		ImGui::Spacing();
		ImGui::Text("PASTILLA:");
		ImGui::Spacing();
		pastilla->RenderGUI();
	}
}
