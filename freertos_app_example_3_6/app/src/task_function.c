/*
 * Copyright (c) 2023 Juan Manuel Cruz <jcruz@fi.uba.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @file   : task_function.c
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"
#include "cmsis_os.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application includes. */
#include "app.h"
#include "led_button.h"

/********************** macros and definitions *******************************/
#define G_TASK_FUNCTION_CNT_INI	0u

#define BUTTON_TICK_CNT_MAX		500
#define LED_TICK_CNT_MAX		500

#define LED_ON			GPIO_PIN_SET
#define LED_OFF			GPIO_PIN_RESET
#define BUTTON_PRESSED	GPIO_PIN_RESET
#define BUTTON_HOVER	GPIO_PIN_SET

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_task_function 	= "Task FUNCTION - Demo Code";

const char *p_task_blinking_on	= "Blinking turn On ";
const char *p_task_blinking_off	= "Blinking turn Off";

const char *p_task_ldx_t_on		= "LDX turn On ";
const char *p_task_ldx_t_off	= "LDX turn Off";

ldx_btnx_config_t ldx_btnx_config[]	= {{LD2_GPIO_Port, 		LD2_Pin, 			\
										LED_OFF,			NOT_BLINKING,	0,	\
										B1_GPIO_Port, 		B1_Pin,				\
										BUTTON_HOVER,		NOT_PRESSED,	0},
							  	   	   {LD2_GPIO_Port, 		LD2_Pin, 			\
							  	   		LED_OFF,			NOT_BLINKING,	0,	\
										B1_GPIO_Port, 		B1_Pin, 			\
										BUTTON_HOVER,		NOT_PRESSED,	0},
									   {LD2_GPIO_Port, 		LD2_Pin, 			\
										LED_OFF,			NOT_BLINKING, 	0,	\
										B1_GPIO_Port,		B1_Pin,				\
										BUTTON_HOVER,		NOT_PRESSED, 	0}};

/********************** external data declaration *****************************/
uint32_t g_task_function_cnt;

/********************** external functions definition ************************/
/* Task A, B and C thread */
void task_function(void *parameters)
{
	#if (TEST_X == 0)
	g_task_function_cnt = G_TASK_FUNCTION_CNT_INI;

	/*  Declare & Initialize Task Function variables for argument, led, button and task */
	ldx_btnx_config_t* p_ldx_btnx_config = (ldx_btnx_config_t *) parameters;

	p_ldx_btnx_config->led_tick_cnt = xTaskGetTickCount();
	p_ldx_btnx_config->button_tick_cnt = xTaskGetTickCount();

	char *p_task_name = (char *) pcTaskGetName(NULL);

	/* Print out: Application Update */
	LOGGER_LOG("  %s is running - %s\r\n", p_task_name, p_task_function);

	#endif

	#if (TEST_X == 1)

	/* Here another code option */

	#endif

	#if (TEST_X == 2)

	/* Here Chatbot Artificial Intelligence generated code */

	#endif

	/* As per most tasks, this task is implemented in an infinite loop. */
	for (;;)
	{

		#if (TEST_X == 0)

		/* Update Task A Counter */
		g_task_function_cnt++;

		/* Check HW Button State */
		p_ldx_btnx_config->button_state = HAL_GPIO_ReadPin(p_ldx_btnx_config->btnx_gpio_port, p_ldx_btnx_config->btnx_pin);
		if (BUTTON_PRESSED == p_ldx_btnx_config->button_state)
		{
			/* Delay for a period using Tick Count */
			if ((xTaskGetTickCount() - p_ldx_btnx_config->button_tick_cnt) >= BUTTON_TICK_CNT_MAX)
			{
				/* Check, Update and Print Led Flag */
				if (NOT_BLINKING == (p_ldx_btnx_config->led_flag))
				{
					p_ldx_btnx_config->led_flag = BLINKING;

					/* Print out: Task execution */
					LOGGER_LOG("  %s - %s\r\n", p_task_name, p_task_blinking_on);
				}
				else
				{
					p_ldx_btnx_config->led_flag = NOT_BLINKING;

					/* Print out: Task execution */
					LOGGER_LOG("  %s - %s\r\n", p_task_name, p_task_blinking_off);
				}
				/* Update and Button Tick Counter */
				p_ldx_btnx_config->button_tick_cnt = xTaskGetTickCount();
			}
		}

		/* Check Led Flag */
		if (BLINKING == (p_ldx_btnx_config->led_flag))
		{
			/* Delay for a period using Tick Count. */
			if ((xTaskGetTickCount() - (p_ldx_btnx_config->led_tick_cnt)) >= LED_TICK_CNT_MAX)
			{
				/* Check, Update and Print Led State */
				if (GPIO_PIN_RESET == (p_ldx_btnx_config->led_state))
				{
					p_ldx_btnx_config->led_state = GPIO_PIN_SET;

					/* Print out: Task execution */
					//LOGGER_LOG("  %s - %s\r\n", p_task_name, p_task_ldx_t_on);
				}
				else
				{
					p_ldx_btnx_config->led_state = GPIO_PIN_RESET;

					/* Print out: Task execution */
					//LOGGER_LOG("  %s - %s\r\n", p_task_name, p_task_ldx_t_off);
				}
				/* Update HW Led State */
		    	HAL_GPIO_WritePin( p_ldx_btnx_config->ldx_gpio_port, p_ldx_btnx_config->ldx_pin, p_ldx_btnx_config->led_state );

				/* Update and Led Tick Counter */
		    	p_ldx_btnx_config->led_tick_cnt = xTaskGetTickCount();
			}
		}

		#endif

		#if (TEST_X == 1)

		/* Here another code option */

		#endif

		#if (TEST_X == 2)

		/* Here Chatbot Artificial Intelligence generated code */

		#endif
	}
}

/********************** end of file ******************************************/
