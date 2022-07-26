/**
 * @file main_ADC_BMM.c
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

/**
 * @brief Rewrite 'putchar' function, remapped to UARTx output
 * 
 * @param c input character
 * @return char 
 */
char putchar (char c) {
    UARTx_Send(c);

    return c;
}

int main (void) {
    
    GPIO_DeInit();
    UART1_Init();

    ADC_Init(ADCCFG_ADC_RESFMT, ADCCFG_SPEED_512tk);
    ADC_BMM_config();

    EA = 1;

    while (1) {
        if (ADC_BMM_FLAG) {
            ADC_BMM_FLAG = CLRBIT;
            printf("ADC channel 15: %d\r\n", ADC_BMM_Buffer[15][ADC_Data_size-2]);
            P_SW2 |= P_SW2_EAXFR;
            BMM_ADC_CR = BMM_ADC_CR_ENADC | BMM_ADC_CR_TRIG;
            P_SW2 &= ~P_SW2_EAXFR;
        }
        delay_nms(50);
    }

    return 0;
}