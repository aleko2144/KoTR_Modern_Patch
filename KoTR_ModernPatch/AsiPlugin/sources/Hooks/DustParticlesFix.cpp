#include "DustParticlesFix.h"
#include "..\Utils\CPatch.h"

void DustParticlesFix::injectHooks() {
	//This patch makes the direction of movement of dust particles equal to the vehicle's movement vector (before calling the emitter).

	unsigned char mod_bytes1[] = { 0x8B, 0x8E, 0x60, 0x54, 0x00, 0x00, 0xD9, 0x41, 0x44, 0xD9,
								   0x5C, 0x24, 0x3C, 0xD9, 0x41, 0x40, 0xD9, 0xE0, 0xD9, 0x5C,
								   0x24, 0x40, 0xD9, 0x41, 0x48, 0xD9, 0x5C, 0x24, 0x44 };

	unsigned char mod_bytes2[] = { 0x8B, 0x4C, 0x24, 0x18 };

	//asm patch
	CPatch::Nop(0x551CE8, 128);
	CPatch::SetBytes(0x551CEA, &mod_bytes1, sizeof(mod_bytes1));
	CPatch::SetBytes(0x551D64, &mod_bytes2, sizeof(mod_bytes2));
	
	//dust particles lifetime (default 3.0)
	CPatch::SetFloat(0x64C1C0, 0.35);
}