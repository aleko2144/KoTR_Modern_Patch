#include "CollisionsFix.h"
#include "../Utils/CPatch.h"

#include "../Utils/ModUtils/Patterns.h"
#include "../Utils/ModUtils/MemoryMgr.h" 

double repulsionCoeff = 1.0;
float  collisionCoeff = 0.1;

bool CollisionsFix::injectHooks() try {
	using namespace Memory::VP;
	using namespace hook::txn;


	int* addr_repulsionCoeff = (int*)pattern("DC 0D ? ? ? ? D9 C0 D8 A4 24 ? ? ? ? D9 9C 24 ? ? ? ? ").get_first(2);
	int* addr_collisionCoeff = (int*)pattern("C7 05 ? ? ? ? ? ? ? ? 66 C7 05 ? ? ? ? ? ?").get_first(6);

	//std::cout << "repulsionCoeff=" << addr_repulsionCoeff << std::endl;
	//std::cout << "collisionCoeff=" << addr_collisionCoeff << std::endl;

	//replace default collision_coeff in truck.ini read function
	CPatch::SetFloat((int)addr_collisionCoeff, collisionCoeff);
	//replace pointer to replusion_coeff (?) in object-object collision function
	CPatch::SetPointer((int)addr_repulsionCoeff, &repulsionCoeff);

	return true;
}
catch (const hook::txn_exception&)
{
	return false;
}