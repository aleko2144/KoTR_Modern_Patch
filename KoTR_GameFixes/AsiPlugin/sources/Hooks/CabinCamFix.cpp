#include "CabinCamFix.h"
#include "..\Utils\CPatch.h"

void CabinCamFix::injectHooks(){
	//makes the extra cabin height lowering code unexecutable
	CPatch::SetInt(0x531F9E, 6600784);
}