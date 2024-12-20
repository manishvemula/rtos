/*
**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/**
2. Create a task vLedTask() which will toggle the given LED
with given rate. LED number and rate will be given as argument.
In main() create four real-time tasks to operate four LEDs.**/

#include <stdlib.h>
#include<string.h>
#include <stdint.h>
#include <stdio.h>
#include"FreeRTOS.h"
#include"FreeRTOSConfig.h"
#include"task.h"
#include"led.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
/**
int rate;
int led;
**/
typedef struct mine{
	portTickType rate;
	int led;
}mine_t;




void vLedTask1(void *pvParam)
{
	//led =*((int *)pvParam);
	mine_t *p=(mine_t*)pvParam;

	while(1)
	{
		// work
		led_toggle(p->led);
		vTaskDelay(p->rate / portTICK_RATE_MS);
	}
	vTaskDelete(NULL);
}


int main()
{

	led_init(LED_RED);
	led_init(LED_GREEN);
	led_init(LED_BLUE);
	led_init(LED_ORANGE);

	static mine_t *t1,*t2,*t3,*t4;

	t1->led=15;
	t1->rate=2000;
	t2->led=1;
	t2->rate=2000;
	t3->led=14;
	t3->rate=2000;
	t4->led=12;
	t4->rate=2000;

	xTaskCreate(vLedTask1, "task1-APeriodic", configMINIMAL_STACK_SIZE, (void *)t1, 1, NULL);

	xTaskCreate(vLedTask1, "2-APeriodic", configMINIMAL_STACK_SIZE,(void *)t2, 2, NULL);

	xTaskCreate(vLedTask1, "3-APeriodic", configMINIMAL_STACK_SIZE,(void *)t3, 2, NULL);

	xTaskCreate(vLedTask1, "4-APeriodic", configMINIMAL_STACK_SIZE, (void *)t4, 3, NULL);

	vTaskStartScheduler();
	while(1);
	return 0;
}








