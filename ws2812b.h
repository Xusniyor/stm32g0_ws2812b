/**
  ******************************************************************************
  * @file    ws2812.h
  * @brief   This file contains all the function prototypes for
  *          the ws2812.c file
  ******************************************************************************
  * @attention
  * eslatma!! bu kutubxona faqat OS dan tashqarida ishlatishga mo`ljalangan 
  * agar siz OS bilan ishlatmoqchi bo`lsangiz unga o`zgartirishlar kiritishingiz kerak
  ******************************************************************************
  */
#ifndef __WS2812B_H_
#define __WS2812B_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Core/Inc/main.h"
#include <stdint.h>

/**
 * @brief please add this to the *.id file
 * << *(.code_in_ram) >>
 * HOW TO ADD
 * https://dev.to/rajeevbharol/executing-code-from-ram-on-stm32-arm-microcontrollers-2k2l
 */
#define RAM_FUNC __attribute__ ((long_call, section (".code_in_ram")))

#define SET_PIN_HIGH(__PORT__, __PIN__) __PORT__->BSRR = (uint32_t)__PIN__
#define SET_PIN_LOW(__PORT__, __PIN__)  __PORT__->BRR  = (uint32_t)__PIN__

typedef enum
{
    WS2812B_OK,
    WS2812B_ERROR
}ws2812b_state;

typedef struct 
{
    GPIO_TypeDef *gpio;
    uint16_t pin;
    uint16_t length;
    uint8_t *buf;
}ws2812b;

ws2812b_state ws2812b_init(ws2812b *hws);
ws2812b_state ws2812b_delete_init(ws2812b *hws);
ws2812b_state ws2812b_update(ws2812b *hws);
ws2812b_state ws2812b_set(ws2812b *hws, uint16_t index, uint32_t color);
uint32_t      ws2812b_get(ws2812b *hws, uint16_t index);



#ifdef __cplusplus
}
#endif

#endif /* __WS2812B_H_ */

/*** END FILE ***/