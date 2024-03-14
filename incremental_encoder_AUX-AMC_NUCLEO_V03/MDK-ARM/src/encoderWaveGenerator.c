/*
 * Copyright (C) 2024 iCub Facility - Istituto Italiano di Tecnologia
 * Author: 
 * email:  
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/
/*
 * Copyright (C) 2024 iCub Facility - Istituto Italiano di Tecnologia
 * Author: 
 * email:  
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/


#include <stdint.h>
#include "stdbool.h"
#include "gpio.h"
#include "tim.h"

#define TIM_TIME htim16

static uint32_t t = 0;                          // Current temp set 0
static uint32_t T_wave = 5;                     // Define wave period
static bool state1 = true;                      // Flag state for square wave 1
static bool state2 = true;                      // Flag state for square wave 2
static bool sequence = true;                    // Check flag
static uint32_t offset_wave = 5;                // Define wave offset
static uint32_t T_index = 10; 

bool index_state = false;                       // Flag for index call

uint32_t counter = 0;
uint32_t time = 0;
uint32_t t1 = 0;


//void init(uint32_t waveLen)
//{
//    T_wave = waveLen;
//}

uint32_t micros_asolari(void)
{
	return ((__HAL_TIM_GET_COUNTER(&TIM_TIME) + (time << 16) ) );
}

void Index_timing(void)
{
  uint32_t dt1 = micros_asolari() - t1;
	
	if(dt1 >= T_index)
	{
		HAL_GPIO_WritePin(ENCZ_GPIO_Port,ENCZ_Pin,false);
		index_state = false;
	}
}

void Wave_generator(void)
{
    
    uint32_t dt = micros_asolari()- t;

    if((dt>= T_wave) && (sequence==true))
    {
        state1 = !state1;
        HAL_GPIO_WritePin(ENCA_GPIO_Port,ENCA_Pin,state1);
        sequence = false;
    }
    
    if (dt >= (T_wave + offset_wave))
    {
        state2 = !state2;
        HAL_GPIO_WritePin(ENCB_GPIO_Port,ENCB_Pin,state2);
        t = micros_asolari();
        sequence = true;
        counter++;
    }
}


void Index_generator(void)
{
	if (index_state == true)
	{
        HAL_GPIO_WritePin(ENCZ_GPIO_Port,ENCZ_Pin,true);
        Index_timing();
	}
}

// here the Callback function ----------------------------------------------------------------------------------------------------

// press button SW1 to configure the "normal situation" with Vel = 20°/s --> 11.5 KHz
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == BUTTON_HALL_Pin) 
  {
    T_wave = 44/2;
    offset_wave = 44/2;
    T_index = 44;
  }
// press button SW2 to configure the "normal situation" with Vel = 40°/s --> 23 KHz  
    if(GPIO_Pin == BUTTON_START_Pin) 
  {
    T_wave = 22/2;
    offset_wave = 22/2;
    T_index = 22;
  }
// press button SW3 to configure the "normal situation" with Vel = 90°/s --> 52 KHz
    if(GPIO_Pin == BUTTON_SPEED_Pin) 
  {
    T_wave = 10/2;
    offset_wave = 10/2;
    T_index = 10;
  }

// press button SW5 to create a index fault
    if(GPIO_Pin == BUTTON_MODE_Pin) 
  {
    T_index = T_index/3;
  }
}

//// press button SW1 to configure the "normal situation" with Vel = 20°/s --> 11.5 KHz
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//  if(GPIO_Pin == BUTTON_HALL_Pin) 
//  {
//    T_wave = 44/2;
//    offset_wave = 44/2;
//    T_index = 44;
//  }
//// press button SW2 to configure the "normal situation" with Vel = 40°/s --> 23 KHz  
//    if(GPIO_Pin == BUTTON_START_Pin) 
//  {
//    T_wave = 22/2;
//    offset_wave = 22/2;
//    T_index = 22;
//  }
//// press button SW3 to configure the "normal situation" with Vel = 90°/s --> 52 KHz
//    if(GPIO_Pin == BUTTON_SPEED_Pin) 
//  {
//    T_wave = 10/2;
//    offset_wave = 10/2;
//    T_index = 10;
//  }
//}
