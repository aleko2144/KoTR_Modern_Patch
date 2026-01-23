#ifndef WAY_H
#define WAY_H

typedef struct 
{
  int flags;
  int field_4;
  double roadWidth;
  char *moduleName;
  char *roomName;
  double field_18;
  int field_20;
  int field_24;
  int field_28;
  int field_2C;
} LocalRoadParameters;

typedef struct 
{
  int roadI;
  void *nodeId;
  double field_8;
  int roadSegmentVectorId;
  int roadSegmentId;
  int field_18;
  int field_1C;
} PositionId;

#endif
