/**
 * @file main_PCA_Timer.c
 * @author MContour (m-contour@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-10
 * 
 * @copyright Apache 2.0 LICENSE
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

#include "main.h"
#include "STDIO.H"
#include "STDLIB.H"
#include "STRING.H"
#include "INTRINS.H"



sbit     PCA_PWM1_G0_IO = P1^6; // PCA Group 0, PCA Module 1 PWM output pin: P1.6
uint16_t pulse_cnt;             //PWM pulse number
uint16_t PCA1_PWM_Period;       // PCA module 1 PWM period

// step = T*(SYSclk/12)
// 0.005 * (24000000/12) = 0x2710
uint8_t  PCAInterruptCount;


void sentPulseNum(uint16_t pulseNum) {
    pulse_cnt = pulseNum << 1;  // overflow times = pulseNum * 2
    CCON_CR   = SETBIT;         // Start PCA counting
}

int main (void) {
    GPIO_DeInit();

    //* 16 bits PCA Timer
    // PCA_Timer_Init(0/*Select Module 0*/, 0x80, 0x49 /*Set PCA module 0 as a 16-bit timer*/, 0x2710 /*CCAP0 value*/);
    // PCAInterruptCount = 100;
    // EA = SETBIT;

    // CCON_CR = SETBIT; // Start PCA Timer

    //* PCA PWM
    PCA_PWM_Init(1/*Select Module 1*/, 0x08, 0x42/*ECOM1,PWM1*/, 0x2020, 0xC0);
    CCON_CR = SETBIT;

    while (1) {
        ;
    }

    return 0;
}

void PCA_ISR_Handler(void) interrupt(PCA_VECTOR) { // 5ms interrupt
    if (CCON_CCF0) {
        union {
            uint16_t num;
            struct {
                uint8_t High, Low;
            } Result;
        } Calculator;
        
        Calculator.num = (uint16_t)(CCAP0H << 8) + CCAP0L + 0x2710;
        CCAP0L     = Calculator.Result.Low;         // Takes the lower 8 bits of the calculated result
        CCAP0H     = Calculator.Result.High;   // Takes the higher 8 bits of the calculated result
        CCON_CCF0  = CLRBIT;                        // Clear interrupt flag
        PCAInterruptCount--;                        // Update interrupt times
        if (PCAInterruptCount == 0) {
            PCAInterruptCount = 100;      // Recover interrupt initial value
            P50 = !P50;
        } // Multiply 0.005s with 100 equal to 0.5s (half period, 1Hz frequency)
    }

    if (CCON_CCF1) {
        CCON_CCF1 = CLRBIT; // Clear interrupt flag
    }

}