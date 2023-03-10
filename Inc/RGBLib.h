#ifndef INC_RGBLIB_H_
#define INC_RGBLIB_H_

#include "stm32f1xx_hal.h"

#include "math.h"

#define RGB_NUM 60

//72 MHz 1 us code
//T0H - 330 us | T0L - 670 us
//T1H - 670 us | T1L - 330 us
#define RGB_HIGH 49
#define RGB_LOW 25

typedef enum TYPE_RGB_STATUS
{
  RGB_READY = 0,
  RGB_TRANSMIT = 1,
  RGB_WAIT = 2,
} TYPE_RGB_STATUS;

void RGB_Init(TIM_HandleTypeDef *timData, uint32_t channel, TIM_HandleTypeDef *timRate);

void RGB_FinishedCallback(void);

void RGB_WaitStatus(TYPE_RGB_STATUS status);

TYPE_RGB_STATUS RGB_GetStatus(void);
void RGB_SetStatus(TYPE_RGB_STATUS status);

void RGB_FillPixelRGB(uint16_t num, uint8_t red, uint8_t green, uint8_t blue);
void RGB_FillPixelHSV(uint16_t num, uint8_t hue, uint8_t sat, uint8_t val);
void RGB_Send(void);

void RGB_HSVtoRGB(uint8_t hue, uint8_t sat, uint8_t val, uint8_t *red, uint8_t *green, uint8_t *blue);

#endif
