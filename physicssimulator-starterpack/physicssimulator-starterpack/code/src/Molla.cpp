#include "Molla.h"

Molla::Molla(float e, float d, glm::vec3 p1, glm::vec3 p2)
{
	elasticitat = e;
	damping = d;
	punt1 = p1;
	punt2 = p2;
	llargada = p1 - p2;
}

Molla::~Molla()
{

}

glm::vec3 Molla::CalcularForces(glm::vec3 v1, glm::vec3 v2)
{
	glm::vec3 forçaResultant;
	//F = -(Ke * (||P1 - P2|| - L12) + Kd * (V1 - V2) * (P1 - P2/||P1 - P2||)) * (P1 - P2/||P1 - P2||)
	forçaResultant = -(elasticitat * (punt1 - punt2 - llargada) + damping * (v1 - v2) * (punt1 - punt2 / punt1 - punt2)) * (punt1 - punt2 / punt1 - punt2);

	return forçaResultant;
}