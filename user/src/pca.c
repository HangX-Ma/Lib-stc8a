/**
 * @file pca.c
 * @author MContour (m-contour@qq.com)
 * @brief PCA function realization
 * @version 0.1
 * @date 2022-05-15
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

#include "pca.h"


void PCA_Timer_Init(uint8_t ModuleGroup, uint8_t CMODVal, uint8_t CCAPMxVal, uint16_t CCAPxVal) {
    CCON = 0x00;    // Stop PCA counter and clear counter overflow interrupt flag and PCA module interrupt flag
    CMOD = CMODVal;
    CL   = 0x00;
    CH   = 0x00;
    if      (ModuleGroup == 0) {CCAPM0 = CCAPMxVal; CCAP0L = CCAPxVal;  CCAP0H = CCAPxVal >> 8;}
    else if (ModuleGroup == 1) {CCAPM1 = CCAPMxVal; CCAP1L = CCAPxVal;  CCAP1H = CCAPxVal >> 8;}
    else if (ModuleGroup == 2) {CCAPM2 = CCAPMxVal; CCAP2L = CCAPxVal;  CCAP2H = CCAPxVal >> 8;}
    else if (ModuleGroup == 3) {CCAPM3 = CCAPMxVal; CCAP3L = CCAPxVal;  CCAP3H = CCAPxVal >> 8;}

    CCON_CR = CLRBIT; // Stop PCA timer
}

void PCA_PWM_Init(uint8_t ModuleGroup, uint8_t CMODVal, uint8_t CCAPMxVal, uint16_t CCAPxVal, uint8_t PCA_PWMxVal) {
    P_SW1   = (P_SW1 & ~P_SW1_CCP_S) | 0x00; // switch I/O group. 0x00: P1.2 P1.7 P1.6 P1.5 P1.4
    CCON    = 0x00; // Clear all interrupt flag
    if      (ModuleGroup == 0) {CCAPM0 = CCAPMxVal; PCA_PWM0 = PCA_PWMxVal; CCAP0L = CCAPxVal;  CCAP0H = CCAPxVal >> 8;}
    else if (ModuleGroup == 1) {CCAPM1 = CCAPMxVal; PCA_PWM1 = PCA_PWMxVal; CCAP1L = CCAPxVal;  CCAP1H = CCAPxVal >> 8;}
    else if (ModuleGroup == 2) {CCAPM2 = CCAPMxVal; PCA_PWM2 = PCA_PWMxVal; CCAP2L = CCAPxVal;  CCAP2H = CCAPxVal >> 8;}
    else if (ModuleGroup == 3) {CCAPM3 = CCAPMxVal; PCA_PWM3 = PCA_PWMxVal; CCAP3L = CCAPxVal;  CCAP3H = CCAPxVal >> 8;}
    /* level 1 priority */
    IPH    &= ~IPH_PPCAH;
    PPCA    = SETBIT;

    CMOD    = CMODVal;
    CL      = 0x00;
    CH      = 0x00;
    CCON_CR = CLRBIT; // Stop PCA timer
}