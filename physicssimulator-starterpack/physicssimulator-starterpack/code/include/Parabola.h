#pragma once
#include<Emiter.h>
#include<Cascada.h>
#include "Plano.h"
#include "EulerStep.h"
#include<Font.h>
#include "imgui/imgui.h"

class ParabolaSim : public Simulator {
public:
	
	struct CollisionBounceResult
	{
		glm::vec3 resPos;
		glm::vec3 resVel;
	};
	//CollisionBounceResult PlaneCollisionMirror(EulerStep s, Plano* p);

	ParabolaSim();
	~ParabolaSim();

	void Update(float dt) override;
	void RenderUpdate() override;
	void RenderGui() override;	

private:
	bool cascadeActive;
	bool fountainActive;

	Emiter* emiter1;
	Emiter* emiter2;
	Plano paredes[6] = {
		Plano(glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), 0.f),				//Terra
		Plano(glm::vec3(0.f, 10.f, 0.f), glm::vec3(0.f, -1.f, 0.f), 10.f),	//Sostre
		Plano(glm::vec3(5.f, 5.f, 0.f), glm::vec3(-1.f, 0.f, 0.f), 5.f),	//Dreta
		Plano(glm::vec3(-5.f, 5.f, 0.f), glm::vec3(1.f, 0.f, 0.f), 5.f),	//Esquerra
		Plano(glm::vec3(0.f, 5.f, -5.f), glm::vec3(0.f, 0.f, -1.f), 5.f),	//Fondo
		Plano(glm::vec3(0.f, 5.f, 5.f), glm::vec3(0.f, 0.f, 1.f), 5.f)		//Proxim
	};
};