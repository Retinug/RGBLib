#ifndef INC_RGB_FX_H_
#define INC_RGB_FX_H_

#include "stm32f1xx_hal.h"

#include "RGBLib.h"

#define SEGMENT_SIZEMAX 5

#define FX_MODE_OFF 0
#define FX_MODE_STATIC 1

typedef struct TYPE_FX_SEGMENT
{
  uint16_t start;
  uint16_t end;
  uint8_t mode; //mode effect
  uint8_t options;
  uint8_t counterTarget;
  uint8_t counterCurrent;
  uint8_t colorHue;
} FX_Segment;

typedef struct TYPE_FX_SEGMENT_MANAGER
{
  FX_Segment segments[SEGMENT_SIZEMAX];
} FX_Segment_Manager;


void FX_Update(void);

void FX_SetSegment(uint8_t num, uint16_t start, uint16_t end, uint8_t mode, uint8_t counterTarget, uint8_t hue);
void FX_SegmentStep(FX_Segment *segment);
void FX_SegmentUpdate(FX_Segment *segment);

void FX_Off(FX_Segment *segment);
void FX_Static(FX_Segment *segment);
#endif
