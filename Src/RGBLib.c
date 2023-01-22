#include "RGBLib.h"

TIM_HandleTypeDef *timerData, *timerRate;
uint32_t channelData;

volatile uint8_t RGB_BUFFER[RGB_NUM * 3] = {0, };
volatile uint8_t PWM_BUFFER[RGB_NUM * 24] = {0, };

void RGB_Init(TIM_HandleTypeDef *timData, uint32_t channel, TIM_HandleTypeDef *timRate)
{
  timerData = timData;
  channelData = channel;
  timerRate = timRate;
}
void RGB_FillPixelRGB(uint16_t num, uint8_t red, uint8_t green, uint8_t blue)
{
  RGB_BUFFER[3 * num] = green;
  RGB_BUFFER[3 * num + 1] = red;
  RGB_BUFFER[3 * num + 2] = blue;
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
}
