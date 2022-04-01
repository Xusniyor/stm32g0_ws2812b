/**
  ******************************************************************************
  * @file    stm32_uart_dma.h
  * @brief   This file contains all the function prototypes for
  *          the stm32_uart_dma.c file
  ******************************************************************************
  * @attention
  * eslatma!! bu kutubxona faqat OS dan tashqarida ishlatishga mo`ljalangan 
  * agar siz OS bilan ishlatmoqchi bo`lsangiz unga o`zgartirishlar kiritishingiz kerak
  ******************************************************************************
  */
#ifndef __STM32_UART_DMA_H_
#define __STM32_UART_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Core/Inc/main.h"
#include <stdint.h>

typedef enum
{
    STM32_UART_DMA_OK,
    STM32_UART_DMA_ERROR
}stm32_uart_dma_state;

typedef struct 
{
    uint8_t *rxbuf;
    uint16_t rxbuf_max_size;
    UART_HandleTypeDef *uart;
    GPIO_TypeDef *de_gpio;
    uint16_t de_pin;
    void(*rxcallback)(uint8_t *, uint16_t);
}stm32_uart_dma;

stm32_uart_dma_state stm32_uart_dma_init(stm32_uart_dma *hobj, void(*rxcallback));
stm32_uart_dma_state stm32_uart_dma_loop(stm32_uart_dma *hobj);
stm32_uart_dma_state stm32_uart_dma_write(stm32_uart_dma *hobj, uint8_t *data, uint16_t len);
stm32_uart_dma_state stm32_uart_dma_delete_init(stm32_uart_dma *hobj);

#ifdef __cplusplus
}
#endif

#endif /* __STM32_UART_DMA_H_ */
/*** END FILE ***/