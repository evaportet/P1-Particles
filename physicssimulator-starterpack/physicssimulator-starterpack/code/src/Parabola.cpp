#include <Parabola.h>
#include <PrimitiveManager.h>


ParabolaSim::ParabolaSim() 
{
	emiter1 = new Cascada(glm::vec3(-1.f, 6.f, 0.f), glm::vec3(1.f, 6.f, 0.f), glm::vec3(0.f, 0.f, 1.f), 5.f);
	emiter2 = new Font(glm::vec3(-1.f, 6.f, 0.f), glm::vec3(-1.f, 12.f, 0.f), glm::vec3(1.f, 6.f, 0.f), glm::vec3(0.f, 0.f, 1.f), 5.f);
	
	esfera = new Esfera(3, glm::vec3(0.5f, 0.f, -4.f));
	pastilla = new Pastilla(glm::vec3(3.f, 0.f, 3.f), glm::vec3(3.f, 2.f, 3.f), 3);
	/*totalTime = 0;

	for (int i = 0; i < nParts; i++)
	{
		positions[i] = glm::vec3(rand() % 5);
		velocities[i] = glm::vec3(rand() % 5);
		accelerations[i] = glm::vec3(0.0f, -0.981f, 0.0f);
	}

	particlesPrim = manager.NewParticles(nParts);
	particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = nParts;*/
}

ParabolaSim::~ParabolaSim() 
{
	delete emiter1;
	delete emiter2;
	delete esfera;
	delete pastilla;
	//manager.DestroyPrimitive(particlesPrim);
}

void ParabolaSim::Update(float dt) 
{
	//totalTime += dt;
	//EulerSolver(dt);
	emiter1->Update(dt);
	emiter2->Update(dt);
	//particlesPrim->Update(0, 1, &(currentPos.x));
	//nParticles = emissionRate + particleLife;
}
void ParabolaSim::RenderUpdate() 
{
	/*particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = 100;*/
	//particlesPrim->Update(0, nParts, &(positions[0].x));
	emiter1->Render();
	emiter2->Render();
	esfera->Render();
	pastilla->Render();
}
void ParabolaSim::RenderGui() 
{
	emiter1->RenderGUI();
	emiter2->RenderGUI();
	esfera->RenderGUI();
	pastilla->RenderGUI();
}

//void ParabolaSim::EulerSolver(float dt)
//{
//	for (int i = 0; i < nParts; i++)
//	{
//		positions[i] = positions[i] + dt * velocities[i];
//		velocities[i] = velocities[i] + dt * accelerations[i];
//	}
//}