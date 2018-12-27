
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

#define LEDBlauOn(); GPIO_ResetBits (GPIOC, GPIO_Pin_0);
#define LEDBlauOff(); GPIO_SetBits (GPIOC, GPIO_Pin_0);
#define LEDBlauToggle(); GPIO_ToggleBits (GPIOC, GPIO_Pin_0);

#define LEDRotOn(); GPIO_ResetBits (GPIOC, GPIO_Pin_1);
#define LEDRotOff(); GPIO_SetBits (GPIOC, GPIO_Pin_1);
#define LEDRotToggle(); GPIO_ToggleBits (GPIOC, GPIO_Pin_1);

#define LEDGelbOn(); GPIO_ResetBits (GPIOC, GPIO_Pin_2);
#define LEDGelbOff(); GPIO_SetBits (GPIOC, GPIO_Pin_2);
#define LEDGelbToggle(); GPIO_ToggleBits (GPIOC, GPIO_Pin_2);

#define LEDGruenOn(); GPIO_ResetBits (GPIOC, GPIO_Pin_3);
#define LEDGruenOff(); GPIO_SetBits (GPIOC, GPIO_Pin_3);
#define LEDGruenToggle(); GPIO_ToggleBits (GPIOC, GPIO_Pin_3);

#define LED_green_on(); GPIO_SetBits (GPIOA, GPIO_Pin_5);
#define LED_green_off(); GPIO_ResetBits (GPIOA, GPIO_Pin_5);
#define LED_green_toggle(); GPIO_ToggleBits (GPIOA, GPIO_Pin_5);


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
