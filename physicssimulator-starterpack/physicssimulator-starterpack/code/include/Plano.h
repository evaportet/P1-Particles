#pragma once
#include "glm/glm.hpp"

class Plano
{
public:
	Plano(glm::vec3 p, glm::vec3 n, float d);
	~Plano();

	static bool colisionPointPlane(Plano* plano, glm::vec3 p);
	glm::vec3 GetPoint();
	glm::vec3 GetNormal();
	float GetD();


private:
	glm::vec3 point;
	glm::vec3 normal;
	float d;
};

