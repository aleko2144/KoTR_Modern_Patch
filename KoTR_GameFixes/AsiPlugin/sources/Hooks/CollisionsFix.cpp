#include "CollisionsFix.h"
#include "..\Utils\CPatch.h"

double repulsionCoeff = 1.0;
float  collisionCoeff = 0.1;

void CollisionsFix::injectHooks(){
	//replace default collision_coeff in truck.ini read function
	CPatch::SetFloat(0x4DFAE2, collisionCoeff);
	//replace pointer to replusion_coeff (?) in object-object collision function
	CPatch::SetPointer(0x57FF08, &repulsionCoeff);
}