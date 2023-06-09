#include "Plano.h"

Plano::Plano(glm::vec3 p, glm::vec3 n, float d)
{
	point = p;
	normal = n;
	this->d = d;
}

Plano::~Plano()
{
}

glm::vec3 Plano::GetPoint() 
{
	return point;
}

glm::vec3 Plano::GetNormal()
{
	return normal;
}

float Plano::GetD()
{
	return d;
}


bool Plano::colisionPointPlane(Plano* plano, glm::vec3 p)
{
	//normalize para resultados más precisos
	glm::vec3 planeNormal = glm::normalize(plano->GetNormal());
	
	float distance;
	distance = planeNormal.x * p.x + planeNormal.y * p.y + planeNormal.z * p.z + plano->GetD();

	return distance <= 0;
}