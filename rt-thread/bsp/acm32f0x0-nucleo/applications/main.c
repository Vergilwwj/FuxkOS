/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-23     AisinoChip   the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include <drivers/pin.h>

#define LED_PIN_NUM    1     /* PA1 */

int main(void)
{
    rt_pin_mode(LED_PIN_NUM, PIN_MODE_OUTPUT);

    while(1)
    {
        rt_pin_write(LED_PIN_NUM, PIN_LOW);
        rt_thread_delay(RT_TICK_PER_SECOND/2);
        rt_pin_write(LED_PIN_NUM, PIN_HIGH);
        rt_thread_delay(RT_TICK_PER_SECOND/2);
    }
}

