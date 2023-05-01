#pragma once
#include <PrimitiveManager.h>
class Molla
{
public:
	Molla(float e, float d, glm::vec3 p1, glm::vec3 p2);
	~Molla();
	glm::vec3 CalcularForces(glm::vec3 v1, glm::vec3 v2);
private:
	float elasticitat, damping;
	glm::vec3 llargada, punt1, punt2;
};