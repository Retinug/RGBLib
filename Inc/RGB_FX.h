#ifndef INC_RGB_FX_H_
#define INC_RGB_FX_H_

#include "stm32f1xx_hal.h"

#include "RGBLib.h"
typedef struct TYPE_FX_SEGMENT
{
  uint16_t start;
  uint16_t end;
  uint8_t counterTarget;
  uint8_t counterCurrent;
} FX_Segment;

typedef struct TYPE_FX_SEGMENT_MANAGER
{
  FX_Segment *segments[SEGMENT_SIZEMAX];
  uint8_t segmentsSize;
} FX_Segment_Manager;
void FX_ManagerUpdate(void);

void FX_SetSegment(uint8_t num, uint16_t start, uint16_t end, uint8_t counter_target);
void FX_SegmentUpdate(FX_Segment *segment);

#endif
