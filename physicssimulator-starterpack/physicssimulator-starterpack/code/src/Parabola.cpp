#include <Parabola.h>
#include <PrimitiveManager.h>


ParabolaSim::ParabolaSim() 
{
	emiter = new Cascada(glm::vec3(-1.f, 6.f, 0.f), glm::vec3(1.f, 6.f, 0.f), glm::vec3(0.f, 0.f, 1.f), 5.f);
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
	delete emiter;
	//manager.DestroyPrimitive(particlesPrim);
}

void ParabolaSim::Update(float dt) 
{
	//totalTime += dt;
	//EulerSolver(dt);
	emiter->Update(dt);
	//particlesPrim->Update(0, 1, &(currentPos.x));
	//nParticles = emissionRate + particleLife;
}
void ParabolaSim::RenderUpdate() 
{
	/*particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = 100;*/
	//particlesPrim->Update(0, nParts, &(positions[0].x));
	emiter->Render();
}
void ParabolaSim::RenderGui() 
{
	emiter->RenderGUI();
	
}

//void ParabolaSim::EulerSolver(float dt)
//{
//	for (int i = 0; i < nParts; i++)
//	{
//		positions[i] = positions[i] + dt * velocities[i];
//		velocities[i] = velocities[i] + dt * accelerations[i];
//	}
//}