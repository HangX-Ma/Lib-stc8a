/**
 * @file i2c.c
 * @author MContour (m-contour@qq.com)
 * @brief Software I2C
 * @version 0.1
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2022
 * 
 *****************************************************************************
 * Copyright (c) 2022 MContour m-contour@qq.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************
 */

#include "i2c.h"
#include "stc8x_delay.h"


void I2C_Start(void) {
    /* prepare for start signal */
    SCL = SETBIT;
    SDA = SETBIT;
     /* wait for stability */
    delay_nus(5);

    SDA = CLRBIT;
    delay_nus(5);

    /* Pull down SCL to clamp bus, avoiding mistaken signal to be sent */
    SCL = CLRBIT;
}


void I2C_Stop(void) {
    /* prepare for start signal */
    SCL = CLRBIT;
    SDA = CLRBIT;
    /* wait for stability */
    delay_nus(2);

    /* Start Signal */
    SCL = SETBIT;
    delay_nus(2);
    SDA = SETBIT;
    delay_nus(5);
    
    /* Pull down SCL to clamp bus, avoiding mistaken signal to be sent */
    SCL = CLRBIT;
}

void I2C_Ack(void) {
    /* prepare for start signal */
    SCL = CLRBIT;
    SDA = CLRBIT;
    /* wait for stability */
    delay_nus(2);

    SCL = SETBIT;
    delay_nus(5);

    /* Pull down SCL to clamp bus, avoiding mistaken signal to be sent */
    SCL = CLRBIT;
}

void I2C_NAck(void) {
    /* prepare for start signal */
    SCL = CLRBIT;
    SDA = SETBIT;
    /* wait for stability */
    delay_nus(2);

    SCL = SETBIT;
    delay_nus(5);

    /* Pull down SCL to clamp bus, avoiding mistaken signal to be sent */
    SCL = CLRBIT;
}

bit I2C_Wait_Ack(void) {
    uint8_t count = 0;

    SDA = SETBIT;
    delay_nus(5);

    SCL = SETBIT; // Release BUS when SCL and SDA simultaneously high.
    delay_nus(5);

    while (SDA) {
        count++;
        if (count > 255) {
            I2C_Stop();

            return 1;
        } // No acknowledge
    }

    SCL = CLRBIT;

    return 0;
}

void I2C_Send_Byte(uint8_t dat) {
    uint8_t i;

    SCL = CLRBIT;
    for (i = 0; i < 8; i++) {
        SDA = (dat & 0x80) >> 7; // Read the highest bit
        dat = dat << 1;
        SCL = SETBIT; // wait SDA read
        delay_nus(2);
        /* Pull down SCL to clamp bus, avoiding mistaken signal to be sent */
        SCL = CLRBIT;
        delay_nus(2);
    }
}

uint8_t  I2C_Read_Byte(uint8_t ack) {
    uint8_t i, value;

    for (i = 0; i < 8; i++) {
        value <<= 1;    // data moved left for next bit reading
        SCL = SETBIT;   // Ensure SDA value not changed
        delay_nus(2);

        if (SDA) {
            value++;
        }
        /* Pull down SCL to clamp bus, avoiding mistaken signal to be sent */
        SCL = CLRBIT;
        delay_nus(2);
    }

    if (!ack) {
        I2C_NAck();
    } 
    else {
        I2C_Ack();
    }

    return value;
}