/**
  ******************************************************************************
  * @file           : ws2812b.c
  * @brief          : 
  ******************************************************************************
  * @attention
  * eslatma!! bu kutubxona faqat OS dan tashqarida ishlatishga mo`ljalangan 
  * agar siz OS bilan ishlatmoqchi bo`lsangiz unga o`zgartirishlar kiritishingiz kerak
  ******************************************************************************
  */
#include "ws2812b.h"
#include <stdlib.h>
#include <string.h>

RAM_FUNC void __ws2812b_update(ws2812b *hws);
uint8_t __ws2812b_shift_byte(uint8_t byte);

ws2812b_state ws2812b_init(ws2812b *hws)
{
    hws->buf = (uint8_t *)malloc(hws->length * sizeof(uint8_t) * 3);
    memset(hws->buf, 0, hws->length * sizeof(uint8_t) * 3);
    return WS2812B_OK;
}
ws2812b_state ws2812b_set(ws2812b *hws, uint16_t index, uint32_t color)
{
    if (index >= hws->length)
        return WS2812B_ERROR;
    hws->buf[index*3]   = __ws2812b_shift_byte((uint8_t)color);
    hws->buf[index*3+1] = __ws2812b_shift_byte((uint8_t)(color >> 8));
    hws->buf[index*3+2] = __ws2812b_shift_byte((uint8_t)(color >> 16));
    return WS2812B_OK;
}
uint32_t ws2812b_get(ws2812b *hws, uint16_t index)
{
    /* Hali yozilmadi */
    return 0;
}
ws2812b_state ws2812b_update(ws2812b *hws)
{
    __disable_irq();
    __ws2812b_update(hws);
    __enable_irq();
    return WS2812B_OK;
}
ws2812b_state ws2812b_delete_init(ws2812b *hws)
{
    free(hws->buf);
    return WS2812B_OK;
}
/* The ws2812b update runs from RAM */
RAM_FUNC void __ws2812b_update(ws2812b *hws)
{
    uint32_t len = hws->length * sizeof(uint8_t) * 3 * 8 + 1;
    for (uint32_t i = 0; i < len; i++)
    {
        // set pin to high
        SET_PIN_HIGH(hws->gpio, hws->pin);
        if (hws->buf[(uint32_t)(i/8)]&(uint8_t)(1 << (i%8)))
        {
            // wait 0.8us
            asm("nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n"
                "nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n"
                "nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n");
            // set pin to low
            SET_PIN_LOW(hws->gpio, hws->pin);
            // wait 0.45us
            asm("nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n"
                "nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n");
        }
        else
        {
            // wait 0.4us
            asm("nop\n""nop\n""nop\n""nop\n""nop\n""nop\n"
                "nop\n""nop\n""nop\n""nop\n""nop\n""nop\n");
            // set pin to low
            SET_PIN_LOW(hws->gpio, hws->pin);
            // wait 0.85us
            asm("nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n"
                "nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n"
                "nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n"
                "nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n"
                "nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n""nop\n");
        }
    }
}
uint8_t __ws2812b_shift_byte(uint8_t byte)
{
    uint8_t shift = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (byte & (uint8_t)(1 << i))
            shift |= 1;
        shift <<= 1;
    }
    return shift;
}
/*** END FILE ***/