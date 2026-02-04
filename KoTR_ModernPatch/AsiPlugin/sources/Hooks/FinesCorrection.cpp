#include "FinesCorrection.h"
#include "..\Utils\CPatch.h"

void FinesCorrection::injectHooks(){
	//makes the fine for crossing a center line given a bit more frequently
	//(fine ID replacement inside fine giving event, 2 to 5)
	CPatch::SetInt(0x54FB63, 5);
}