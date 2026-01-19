#include "CollisionsFix.h"
#include "utils\CPatch.h"

void CollisionsFix::injectHooks(){
	//replace default collision_coeff in truck.ini read function
	CPatch::SetFloat(0x4DFAE2, 0.75);

	//replace pointer of dbl 0.2 to 3.141 inside slide collision process function
	CPatch::SetInt(0x57FF08, 6600744);
}