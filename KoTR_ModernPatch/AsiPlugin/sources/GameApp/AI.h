#ifndef AI_H
#define AI_H

#include "way.h"
#include "..\Utils\CVector.h"

PositionId *__cdecl getPlayerPositionId(PositionId *posID, void *playerID);
CVector    *__cdecl getCoordinates(CVector *vec, PositionId pos);
int         __cdecl getRoadParameters(PositionId pos, LocalRoadParameters * rp);
bool        __cdecl sub_4CFD50(void *playerID);

#endif
