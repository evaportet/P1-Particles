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
	capsuleActive = false;
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

ParabolaSim::CollisionBounceResult SphereCollision(EulerStep s, Esfera* e)
{
	ParabolaSim::CollisionBounceResult resultat;

	//Crear variables auxiliars per facilitar treballar amb els nombres
	glm::vec3 pos, vel, cen;
	float rad;
	pos = s.endPos;
	vel = s.endVel;
	cen = e->GetPosition();
	rad = e->GetRadius();

	float alphaX2, alphaY2, alphaZ2, alphaX1, alphaY1, alphaZ1, naturalX, naturalY, naturalZ, finalAlpha2, finalAlpha1, finalNatural;
	//Fer a^2 + 2ab + b^2 amb cada eix de (x-cenx)^2 on x = px + alpha * vx
	alphaX2 = vel.x * vel.x;
	alphaX1 = vel.x * (pos.x - cen.x) * 2;
	naturalX = (pos.x - cen.x) * (pos.x - cen.x);

	alphaY2 = vel.y * vel.y;
	alphaY1 = vel.y * (pos.y - cen.y) * 2;
	naturalY = (pos.y - cen.y) * (pos.y - cen.y);

	alphaZ2 = vel.z * vel.z;
	alphaZ1 = vel.z * (pos.z - cen.z) * 2;
	naturalZ = (pos.z - cen.z) * (pos.z - cen.z);

	//Agrupar tots els resultats per tpus i dividir-los per r^2 per igualar l'operació a 0
	finalAlpha2 = (alphaX2 + alphaY2 + alphaZ2) / (rad * rad);
	finalAlpha1 = (alphaX1 + alphaY1 + alphaZ1) / (rad * rad);
	finalNatural = (naturalX + naturalY + naturalZ) / (rad * rad);

	//Calcular alpha amb una equació de segon grau
	float a, b, c, x1, x2, alphaFinal;
	a = finalAlpha2;
	b = finalAlpha1;
	c = finalNatural;
	x1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	x2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

	//Agafar la alpha més petita
	alphaFinal = x1 < x2 ? x1 : x2;

	//Resoldre P = P' + alpha * V
	glm::vec3 puntRebot;
	puntRebot.x = pos.x + alphaFinal * vel.x;
	puntRebot.y = pos.y + alphaFinal * vel.y;
	puntRebot.z = pos.z + alphaFinal * vel.z;

	//Treure el vector normal del pla i normalitzar-lo
	glm::vec3 vec, nVec;
	vec = puntRebot - cen;
	nVec = vec / (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));

	//Definir components del pla
	float pA, pB, pC, pD;
	pA = puntRebot.x * nVec.x;
	pB = puntRebot.y * nVec.y;
	pC = puntRebot.z * nVec.z;
	pD = pA + pB + pC;

	//Trobar punt i velocitat despres de rebotar
	//P = P' - 2 * (u * P' + d)u
	resultat.resPos = pos - 2.f * (nVec.x * pos.x + nVec.y * pos.y + nVec.z * pos.z + pD) * nVec;
	//V = V' - 2 * (u * V')u
	resultat.resVel = vel - 2.f * (nVec.x * vel.x + nVec.y * vel.y + nVec.z * vel.z) * nVec;;

	return resultat;
}

ParabolaSim::CollisionBounceResult CapsuleCollision(EulerStep s, Pastilla* c)
{
	ParabolaSim::CollisionBounceResult result;

	//No és així, pero era per posar alguna cosa
	result.resPos -= (result.resPos + result.resPos);
	result.resVel -= (result.resVel + result.resVel);

	return result;
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
				else if (esfera->PointInsideSphere(emiter1->GetParticlePosition(i), esfera))
				{
					CollisionBounceResult res = SphereCollision(step, esfera);
					emiter1->UpdateParticle(i, res.resPos, res.resVel, emiter1->GetParticleAcceleration(i), 0);
				}
				else if (pastilla->PointInsideCapsule(emiter1->GetParticlePosition(i), pastilla))
				{
					CollisionBounceResult res = CapsuleCollision(step, pastilla);
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
				else if (esfera->PointInsideSphere(emiter2->GetParticlePosition(i), esfera))
				{
					CollisionBounceResult res = SphereCollision(step, esfera);
					emiter2->UpdateParticle(i, res.resPos, res.resVel, emiter2->GetParticleAcceleration(i), 0);
				}
				/*else if (pastilla->PointInsideCapsule(emiter2->GetParticlePosition(i), pastilla))
				{
					CollisionBounceResult res = CapsuleCollision(step, pastilla);
					emiter2->UpdateParticle(i, res.resPos, res.resVel, emiter2->GetParticleAcceleration(i), 0);
				}*/
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
