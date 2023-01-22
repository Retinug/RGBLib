#include "RGB_FX.h"

FX_Segment_Manager SegmentManager;

void FX_Update(void)
{
  for (int i = 0; i < SegmentManager.segmentsSize; i++)
  {
    FX_SegmentUpdate(SegmentManager.segments[i]);
  }
}

void FX_SetSegment(uint8_t num, uint16_t start, uint16_t end, uint8_t counterTarget)
{
  FX_Segment *Segment;
  Segment = SegmentManager.segments[num];
  Segment->start = start;
  Segment->end = end;
  Segment->counterTarget = counterTarget;
}

void FX_SegmentUpdate(FX_Segment *segment)
{
  segment->counterCurrent++;
  if(segment->counterCurrent >= segment->counterTarget)
  {
    segment->counterCurrent = 0;
    //update effect
  }
}
