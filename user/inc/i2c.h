/**
 * @file i2c.h
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

/* I2C communication protocol */
// Data Validity: Only when SCL is LOW, can SCA change its value, otherwise keeping stable.
// Start Signal: When SCL is HIGH, SDA change from HIGH to LOW.
// Stop Signal: When SCL is HIGH, SDA change from LOW to HIGH.
// Acknowledge Signal: When SCL HIGH (keeping_time>4us) but SDA LOW, acknowledge signal is sent.
// Not-Acknowledge Signal: When SCL HIGH(keeping_time>4us) and SDA HIGH, non-acknowledge signal is sent.



#ifndef __I2C__H__
#define __I2C__H__

//* ------------      head files      ------------
#include "core_stc8x.h"

#if (LIB_MCU_MODULE == STC8Ax)
    #include "config_stc8ax.h"
#elif (LIB_MCU_MODULE == STC8Hx)
    #include "config_stc8hx.h"
#endif

//* ------------ developer definitions ------------ 
sbit SCL = P3^1;
sbit SDA = P3^2;
//* ------------   GLOBAL variables   ------------

//* ------------     functions     ------------


void I2C_Start(void);

void I2C_Stop(void);

void I2C_Ack(void);

void I2C_NAck(void);

bit I2C_Wait_Ack(void);

void I2C_Send_Byte(uint8_t dat);

uint8_t I2C_Read_Byte(uint8_t ack);

#endif  //!__I2C__H__

