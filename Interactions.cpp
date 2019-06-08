#include "Interactions.h"



Interactions::Interactions()
{
}


Interactions::~Interactions()
{
}

int Interactions::Collision(glm::vec3 A, glm::vec3 B, float radius)
{
	if (sqrt(((A.x - B.x)*(A.x - B.x)) +
		((A.y - B.y)*(A.y - B.y)) +
		((A.z - B.z)*(A.z - B.z))) < radius)
	{
		return 1;
	}
	return 0;
}

int Interactions::AABBCollision(glm::vec3 A, glm::vec3 B, glm::vec3 scale)
{
	if (A.x > B.x && A.x < B.x * 20.0f &&
		A.y > B.y && A.y < B.y * 5.0f &&
		A.z > B.z && A.z < B.z * 1.0f)
	{
		return 1;
	}
	return 0;
}

