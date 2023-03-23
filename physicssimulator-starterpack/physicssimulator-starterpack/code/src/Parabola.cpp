#include <Parabola.h>
#include <PrimitiveManager.h>

extern graphics::PrimitiveManager manager;

ParabolaSim::ParabolaSim() 
{
	totalTime = 0;

	position		=	{ 2.0f,	  0.0f,	2.0f };
	velocity		=	{ 6.0f,	 15.0f,	6.0f };
	acceleration	=	{ 0.0f,	-9.81f, 0.0f };

	float velocityModule = sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);

	xyAngle = acos(velocity.x / velocityModule);
	xzAngle = acos(velocity.z / velocityModule);;
	yzAngle = acos(velocity.z / velocityModule);;

	for (int i = 0; i < nParts; i++)
	{
		positions[i] = { rand() % (int)position.x, position.y, rand() % (int)position.z };
		velocities[i] = { rand() % (int)velocity.x, velocity.y, rand() % (int)velocity.z };
		accelerations[i] = { acceleration.x, acceleration.y, acceleration.z };
	}

	particlesPrim = manager.NewParticles(nParts);
	particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = nParts;
}

ParabolaSim::~ParabolaSim() 
{
	manager.DestroyPrimitive(particlesPrim);
}

void ParabolaSim::Update(float dt) 
{
	totalTime += dt;
	EulerSolver(dt);
	//particlesPrim->Update(0, 1, &(currentPos.x));
	nParticles = emissionRate + particleLife;
}
void ParabolaSim::RenderUpdate() 
{
	/*particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = 100;*/
	particlesPrim->Update(0, nParts, &(positions[0].x));
}
void ParabolaSim::RenderGui() 
{
	
	ImGui::SliderFloat("Emission Rate (particles/s)",
						&emissionRate,
						MIN_EMISSION_RATE,
						MAX_EMISSION_RATE);

	ImGui::SliderFloat("Particle Life (s)",
						&particleLife,
						MIN_LIFE,
						MAX_LIFE);
	
}

void ParabolaSim::EulerSolver(float dt)
{
	for (int i = 0; i < nParts; i++)
	{
		positions[i] = positions[i] + dt * velocities[i];
		velocities[i] = velocities[i] + dt * accelerations[i];
	}
}