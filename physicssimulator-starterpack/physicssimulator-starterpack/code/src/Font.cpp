#include "Font.h"

Font::Font(glm::vec3 p, glm::vec3 t, glm::vec3 r, glm::vec3 dir, float dirMagnitude)
	: point(p), target(t), rotPoint(r), spawnVel(dir), velMagnitude(dirMagnitude), Emiter(200, 1.5f)
{
	nParts = 0;
	angle = 90.f;
}

void Font::Update(float dt)
{
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
			glm::vec3 directionVect = target - point;
			glm::vec3 randomPos = point + directionVect * (float(rand() % 100)) / 100.f;
			float randomangle = (float)(rand()) / angle;
			glm::vec3 vel = glm::rotate(spawnVel, glm::radians(randomangle), directionVect);
			positions.push_back(point);
			velocities.push_back(vel * velMagnitude);
			accelerations.push_back(gravity);
			lifeTimes.push_back(particleLife);

			nParts++;
			RegeneratePrim(nParts);
		}
	}
}

void Font::UpdateParticle(int index, glm::vec3 pos, glm::vec3 vel, glm::vec3 a, float dt)
{
	positions[index] = pos;
	velocities[index] = vel;
	accelerations[index] = a;
	lifeTimes[index] -= dt;
}

void Font::RenderGUI()
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
	ImGui::SliderFloat("Point A x", &point[0], -5.f, 5.f);
	ImGui::SliderFloat("Point A y", &point[1], 0.f, 10.f);
	ImGui::SliderFloat("Point A z", &point[2], -5.f, 5.f);
	ImGui::Spacing();
	ImGui::SliderFloat3("Vel direction", &spawnVel[0], -1.f, 1.f, "%.1f");
	ImGui::SliderFloat("Vel magnitude", &velMagnitude, -8.f, 8.f);
	ImGui::SliderFloat("Angle", &angle, -90.f, 90.f);
}