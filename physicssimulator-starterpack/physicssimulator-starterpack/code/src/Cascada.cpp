#include "Cascada.h"

Cascada::Cascada(glm::vec3 pA, glm::vec3 pB, glm::vec3 dir, float dirMagnitude) 
	: pointA(pA), pointB(pB), spawnVel(dir), velMagnitude(dirMagnitude), Emiter(200, 1.5f)
{
	nParts = 0;
	angle = 0.f;
}

void Cascada::Update(float dt)
{
	for (int i = 0; i < nParts; i++)
	{
		//EULER
		positions[i] = positions[i] + dt * velocities[i];
		velocities[i] = velocities[i] + dt * accelerations[i];
		lifeTimes[i] -= dt;
	}

	//update lifetimes
	for (int i = 0; i < nParts; i++)
	{
		if (lifeTimes[i] <= 0.f)
		{
			positions.erase(positions.begin() + i);
			velocities.erase(velocities.begin() + i);
			accelerations.erase(accelerations.begin() + i);
			lifeTimes.erase(lifeTimes.begin() + i);
			i = 0;
			nParts--;
			RegeneratePrim(nParts);
		}
	}
	
	//spawn particles
	if (nParts < currentMaxPart)
	{
		int particlesToSpawn = int((float)emissionRate * dt);
		for (int i = 0; i < particlesToSpawn; i++)
		{
			//create particle
			glm::vec3 segmentVect = pointB - pointA;
			glm::vec3 randomPos = pointA + segmentVect * (float(rand() % 100)) / 100.f;
			glm::vec3 vel = glm::rotate(spawnVel, glm::radians(angle), segmentVect);
			glm::vec3 splashedVel = vel * velMagnitude;
			positions.push_back(randomPos);
			velocities.push_back(splashedVel);
			accelerations.push_back(gravity);
			lifeTimes.push_back(particleLife);

			nParts++;
			RegeneratePrim(nParts);
		}
	}
}

void Cascada::RenderGUI()
{
	ImGui::SliderInt("Emission Rate (particles/s)",
		&emissionRate,
		MIN_EMISSION_RATE,
		MAX_EMISSION_RATE);

	ImGui::SliderFloat("Particle Life (s)",
		&particleLife,
		MIN_LIFE,
		MAX_LIFE);
	
	ImGui::SliderInt("Max particles",
		&currentMaxPart,
		100,
		10000);
	
	ImGui::Spacing();
	ImGui::SliderFloat("Point A x", &pointA[0], -5.f, 5.f);
	ImGui::SliderFloat("Point A y", &pointA[1], 0.f, 10.f);
	ImGui::SliderFloat("Point A z", &pointA[2], -5.f, 5.f);
	ImGui::Spacing();
	ImGui::SliderFloat("Point B x", &pointB[0], -5.f, 5.f);
	ImGui::SliderFloat("Point B y", &pointB[1], 0.f, 10.f);
	ImGui::SliderFloat("Point B z", &pointB[2], -5.f, 5.f);
	ImGui::Spacing();
	ImGui::SliderFloat3("Vel direction", &spawnVel[0], -1.f, 1.f, "%.1f");
	ImGui::SliderFloat("Vel magnitude", &velMagnitude, -8.f, 8.f);
	ImGui::SliderFloat("Angle", &angle, -90.f, 90.f);
}