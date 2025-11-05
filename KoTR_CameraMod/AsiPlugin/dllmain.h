#ifndef _DLL_H_
#define _DLL_H_
#define BUILDING_DLL 1

#include "input.h"

#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

#endif
