/*
 * Copyright (C) 2024 iCub Facility - Istituto Italiano di Tecnologia
 * Author: Andrea Solari
 * email:  andrea.solari@iit.it
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


#include "encoderWaveGenerator.h"

#define TIM_TIME htim16

static uint32_t t = 0;                                                  // Current temp set 0
static uint32_t T_wave = 0;                                             // Define wave period end set default
static bool state1 = true;                                              // Flag state for square wave 1
static bool state2 = true;                                              // Flag state for square wave 2
static bool sequence = true;                                            // Check flag
static uint32_t offset_wave = 50;                                       // Define wave offset end set default
static uint32_t T_index = 100;                                          // Define index end set default
                                                                        
bool index_state = false;                                               // Flag for index call
                                                                        
uint32_t counter = 0;                                                   // Global start value for counter
uint32_t time = 0;                                                      // Global start value for time
uint32_t t1 = 0;                                                        // Global start value for t1


void init(uint32_t waveLen, uint32_t offset_wave, uint32_t T_index)     // First value without button press
{
    T_wave = waveLen;
}


// - create a micros counter ---------------------------------------------------------------------------------------------------
uint32_t micros_asolari(void)
{
	return ((__HAL_TIM_GET_COUNTER(&TIM_TIME) + (time << 16) ) );       // I create a micro time base
}

// - build a index time dimension ----------------------------------------------------------------------------------------------

void Index_timing(void)
{
  uint32_t dt1 = micros_asolari() - t1;
	
	if(dt1 >= T_index)
	{
		HAL_GPIO_WritePin(ENCZ_GPIO_Port,ENCZ_Pin,false);               // Here write the state for GPIO
		index_state = false;                                            // Update the index condition
	}
}

// - build A e B channel time dimension ----------------------------------------------------------------------------------------

void Wave_generator(void)
{
    
    uint32_t dt = micros_asolari()- t;

    if((dt>= T_wave) && (sequence==true))
    {
        state1 = !state1;
        HAL_GPIO_WritePin(ENCA_GPIO_Port,ENCA_Pin,state1);              // Here write the state for GPIO
        sequence = false;
    }
    
    if (dt >= (T_wave + offset_wave))
    {
        state2 = !state2;
        HAL_GPIO_WritePin(ENCB_GPIO_Port,ENCB_Pin,state2);              // Here write the state for GPIO
        t = micros_asolari();
        sequence = true;
        counter++;                                                      // Update a index counter
    }
}

// - Here detect index condition and create a output ------------------------------------------------------------------------------

void Index_generator(void)
{
	if (index_state == true)
	{
        HAL_GPIO_WritePin(ENCZ_GPIO_Port,ENCZ_Pin,true);
        Index_timing();
	}
}

// here the Callback function ----------------------------------------------------------------------------------------------------


/*
 * ENCODER CPR --> 1300
 * => 360°/1300 = 0.2769° OF RESOLUTION
 * THE GEARBOX BETEWEEN HIGH/LOW SPEED IS 160
 * MAX SPEED MOTOR IS 6000 RPM --> 105 KHz
*/

// press button SW1 to configure the "normal situation" with Vel = 20°/s --> 11.5 KHz
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == BUTTON_HALL_Pin) 
  {
    T_wave = 44/2;
    offset_wave = 44/2;
    T_index = 44;
  
    // Update LED USER status
      
      HAL_GPIO_WritePin(LED_M1_GPIO_Port,LED_M1_Pin,true);
      HAL_GPIO_WritePin(LED_M2_GPIO_Port,LED_M2_Pin,false);     
      HAL_GPIO_WritePin(LED_M3_GPIO_Port,LED_M3_Pin,true);
      
  }
// press button SW2 to configure the "normal situation" with Vel = 40°/s --> 23 KHz  
   if(GPIO_Pin == BUTTON_START_Pin) 
  {
    T_wave = 22/2;
    offset_wave = 22/2;
    T_index = 22;

    // Update LED USER status
      
      HAL_GPIO_WritePin(LED_M1_GPIO_Port,LED_M1_Pin,true);
      HAL_GPIO_WritePin(LED_M2_GPIO_Port,LED_M2_Pin,true);     
      HAL_GPIO_WritePin(LED_M3_GPIO_Port,LED_M3_Pin,false);
      
      
  }
// press button SW5 to configure the "normal situation" with Vel = 90°/s --> 52 KHz
    if(GPIO_Pin == BUTTON_MODE_Pin) 
  {
    T_wave = 10/2;
    offset_wave = 10/2;
    T_index = 10;
  
    // Update LED USER status
      
      HAL_GPIO_WritePin(LED_M1_GPIO_Port,LED_M1_Pin,false);
      HAL_GPIO_WritePin(LED_M2_GPIO_Port,LED_M2_Pin,true);     
      HAL_GPIO_WritePin(LED_M3_GPIO_Port,LED_M3_Pin,true);      
      
      
  }

// press button SW3 to create a index fault
    if(GPIO_Pin == BUTTON_SPEED_Pin) 
  {
    T_index = T_index/2;
      
    // Update LED USER status
      
    HAL_GPIO_TogglePin(LED_S2_GPIO_Port,LED_S2_Pin);
  }
}



//here i use the interrupt callback when timer roll over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	//check the callback and toggle the GPIO pin
	if (htim == &TIM_TIME)
	{
		time++;
    }
}