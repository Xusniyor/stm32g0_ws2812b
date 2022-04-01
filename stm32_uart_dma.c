/**
  ******************************************************************************
  * @file           : stm32_uart_dma.c
  * @brief          : 
  ******************************************************************************
  * @attention
  * eslatma!! bu kutubxona faqat OS dan tashqarida ishlatishga mo`ljalangan 
  * agar siz OS bilan ishlatmoqchi bo`lsangiz unga o`zgartirishlar kiritishingiz kerak
  ******************************************************************************
  */
#include "stm32_uart_dma.h"
#include <stdlib.h>

uint16_t __find, __last_find;

stm32_uart_dma_state stm32_uart_dma_init(stm32_uart_dma *hobj, void(*rxcallback))
{
    hobj->rxcallback = rxcallback;
    hobj->rxbuf = (uint8_t *)malloc(hobj->rxbuf_max_size * sizeof(uint8_t));
    HAL_GPIO_WritePin(hobj->de_gpio, hobj->de_pin, GPIO_PIN_RESET);
    HAL_UART_Receive_DMA(hobj->uart, hobj->rxbuf, hobj->rxbuf_max_size);
    return STM32_UART_DMA_OK;
}
stm32_uart_dma_state stm32_uart_dma_loop(stm32_uart_dma *hobj)
{
    __find = __HAL_DMA_GET_COUNTER(hobj->uart->hdmarx);
    if (__find != hobj->rxbuf_max_size)
    {
        __last_find = __find;
        HAL_Delay(10);
        __find = __HAL_DMA_GET_COUNTER(hobj->uart->hdmarx);
        if (__last_find != __find)
            return STM32_UART_DMA_OK;
        HAL_UART_Abort(hobj->uart);
        hobj->rxcallback(hobj->rxbuf, hobj->rxbuf_max_size - __find);
        HAL_UART_Receive_DMA(hobj->uart, hobj->rxbuf, hobj->rxbuf_max_size);
    }
    return STM32_UART_DMA_OK;
}
stm32_uart_dma_state stm32_uart_dma_write(stm32_uart_dma *hobj, uint8_t *data, uint16_t len)
{
    HAL_GPIO_WritePin(hobj->de_gpio, hobj->de_pin, GPIO_PIN_SET);
    HAL_UART_Transmit(hobj->uart, data, len, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(hobj->de_gpio, hobj->de_pin, GPIO_PIN_RESET);
    return STM32_UART_DMA_OK;
}
stm32_uart_dma_state stm32_uart_dma_delete_init(stm32_uart_dma *hobj)
{
    free(hobj->rxbuf);
    return STM32_UART_DMA_OK;
}
/*** END FILE ***/