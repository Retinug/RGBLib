#include "RGBLib.h"

TIM_HandleTypeDef *timerData, *timerRate;
uint32_t channelData;

volatile uint8_t RGB_BUFFER[RGB_NUM * 3] = {0, };
volatile uint8_t PWM_BUFFER[RGB_NUM * 24] = {0, };

volatile TYPE_RGB_STATUS RGB_STATUS;

void RGB_Init(TIM_HandleTypeDef *timData, uint32_t channel, TIM_HandleTypeDef *timRate)
{
  timerData = timData;
  channelData = channel;
  timerRate = timRate;
}

void RGB_FinishedCallback(void)
{
  HAL_TIM_PWM_Stop_DMA(timerData, channelData);
  RGB_STATUS = RGB_WAIT;
}

void RGB_WaitStatus(TYPE_RGB_STATUS status)
{
  while (RGB_GetStatus() != status);
}

TYPE_RGB_STATUS RGB_GetStatus(void)
{
  return RGB_STATUS;
}

void RGB_SetStatus(TYPE_RGB_STATUS status)
{
  RGB_STATUS = status;
}

void RGB_FillPixelRGB(uint16_t num, uint8_t red, uint8_t green, uint8_t blue)
{
  RGB_BUFFER[3 * num] = green;
  RGB_BUFFER[3 * num + 1] = red;
  RGB_BUFFER[3 * num + 2] = blue;
}

void RGB_FillPixelHSV(uint16_t num, uint8_t hue, uint8_t sat, uint8_t val)
{
  uint8_t r, g, b;
  RGB_HSVtoRGB(hue, sat, val, &r, &g, &b);
  RGB_FillPixelRGB(num, r, g, b);
}

void RGB_Send(void)
{
  uint32_t indx = 0;
  for (int currPix = 0; currPix < RGB_NUM; currPix++)
  {
    uint32_t data = (RGB_BUFFER[3 * currPix] << 16) | (RGB_BUFFER[3 * currPix + 1] << 8) | RGB_BUFFER[3 * currPix + 2];
    for (int i = 23; i >= 0; i--)
    {
      if (data & (1 << i))
        PWM_BUFFER[indx] = RGB_HIGH;
      else
        PWM_BUFFER[indx] = RGB_LOW;
      indx++;
    }
  }
  HAL_TIM_PWM_Start_DMA(timerData, channelData, (uint32_t*) PWM_BUFFER, RGB_NUM * 24);
  RGB_STATUS = RGB_TRANSMIT;
}

void RGB_HSVtoRGB(uint8_t hue, uint8_t sat, uint8_t val, uint8_t *red, uint8_t *green, uint8_t *blue)
{
  float h = (float) hue / 255;
  float s = (float) sat / 255;
  float v = (float) val / 255;

  int i = (int) floorf(h * 6);
  float f = h * 6 - (float) i;
  uint8_t p = (uint8_t) (v * (1.0 - s) * 255.0);
  uint8_t q = (uint8_t) (v * (1.0 - f * s) * 255.0);
  uint8_t t = (uint8_t) (v * (1.0 - (1.0 - f) * s) * 255.0);

  switch (i % 6)
  {
    case 0:
      *red = val, *green = t, *blue = p;
      break;
    case 1:
      *red = q, *green = val, *blue = p;
      break;
    case 2:
      *red = p, *green = val, *blue = t;
      break;
    case 3:
      *red = p, *green = q, *blue = val;
      break;
    case 4:
      *red = t, *green = p, *blue = val;
      break;
    default:
      *red = val, *green = p, *blue = q;
      break;
  }
}
