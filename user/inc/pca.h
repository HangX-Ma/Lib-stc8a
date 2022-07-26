/**
 * @file pca.h
 * @author MContour (m-contour@qq.com)
 * @brief PCA function definitions
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

#ifndef __PCA__H__
#define __PCA__H__
//* ------------      head files      ------------
#include "core_stc8x.h"

#if (LIB_MCU_MODULE == STC8Ax)
    #include "config_stc8ax.h"
#elif (LIB_MCU_MODULE == STC8Hx)
    #include "config_stc8hx.h"
#endif

//* ------------ developer definitions ------------
#define PCA_TIMER_FUNCTION (0)


//* ------------   GLOBAL variables   ------------

//* ------------     functions     ------------

/**
 * @brief PCA 16 bits timer initialization
 * 
 * @param ModuleGroup PCA module selection
 * @param CMODVal CMOD value
 * @param CCAPMxVal CCAPMx value, 'x' is the PCA module number
 * @param CCAPxVal CCAPx value, 'x' is the PCA module number
 */
void PCA_Timer_Init(uint8_t ModuleGroup, uint8_t CMODVal, uint8_t CCAPMxVal, uint16_t CCAPxVal);

/**
 * @brief PCA PWM initialization
 * 
 * @param ModuleGroup PCA module selection
 * @param CMODVal CMOD value
 * @param CCAPMxVal CCAPMx value, 'x' is the PCA module number
 * @param CCAPxVal CCAPx value, 'x' is the PCA module number
 */
void PCA_PWM_Init(uint8_t ModuleGroup, uint8_t CMODVal, uint8_t CCAPMxVal, uint16_t CCAPxVal, uint8_t PCA_PWMxVal);

#endif  //!__PCA__H__