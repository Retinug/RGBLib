#include "RGB_FX.h"

FX_Segment_Manager SegmentManager;

void FX_Update(void)
{
  for (int i = 0; i <= SEGMENT_SIZEMAX - 1; i++)
  {
    FX_SegmentStep(&SegmentManager.segments[i]);
  }
  RGB_Send();
}

void FX_SetSegment(uint8_t num, uint16_t start, uint16_t end, uint8_t mode, uint8_t counterTarget, uint8_t hue)
{
  //FX_Segment Segment;
  //Segment = &SegmentManager->segments[num];
  SegmentManager.segments[num].start = start;
  SegmentManager.segments[num].end = end;
  SegmentManager.segments[num].mode = mode;
  SegmentManager.segments[num].counterTarget = counterTarget;
  SegmentManager.segments[num].colorHue = hue;
  //SegmentManager->segments[num] = Segment;
  //Segment->FX_Effect = FX_Effect;
}

void FX_SegmentStep(FX_Segment *segment)
{
  if(segment->counterTarget == 0)
  {
    return;
  }
  segment->counterCurrent++;
  if(segment->counterCurrent >= segment->counterTarget)
  {
    segment->counterCurrent = 0;
    FX_SegmentUpdate(segment);
  }
}

void FX_SegmentUpdate(FX_Segment *segment)
{
  switch (segment->mode) {
    case FX_MODE_OFF:
      FX_Off(segment);
      break;
    case FX_MODE_STATIC:
      FX_Static(segment);
      break;
    default:
      break;
  }
}

void FX_Off(FX_Segment *segment)
{
  for (uint16_t i = segment->start; i < segment->end; i++)
  {
    RGB_FillPixelRGB(i, 0, 0, 0);
  }
}

void FX_Static(FX_Segment *segment)
{
  uint8_t r, g, b;
  RGB_HSVtoRGB(segment->colorHue, 255, 255, &r, &g, &b);
  for (uint16_t i = segment->start; i <= segment->end; i++)
  {
    RGB_FillPixelRGB(i, r, g, b);
  }
}
  }
}
