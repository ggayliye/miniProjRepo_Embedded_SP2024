/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
HAL_Init(); // Reset of all peripherals, init the Flash and Systick
SystemClock_Config(); //Configure the system clock
/* This example uses HAL library calls to control
the GPIOC peripheral. You’ll be redoing this code
with hardware register access. */
	
	
	//LAB02************************************************
	RCC->AHBENR |= (1<<19); //Enable the 19th bit for clock
	//Enable ALL LEDs
	GPIOC->MODER |= (85<<12);
	GPIOC->OTYPER &= 0;
	GPIOC->OSPEEDR &= 0;
	GPIOC->PUPDR &= 0;
	
	//Configure user pushbutton
	RCC->AHBENR |= (1<<17); 
	GPIOA->MODER &= ~((1<<0) | (1<<1));
	GPIOA->OTYPER &= 0;
	GPIOA->OSPEEDR &= 0;
	GPIOA->PUPDR |= 2;
	
	//Unmask interrupt generation on EXTI input. line 0
	EXTI->IMR |= 1;
	//Set input 0 to have a rising-edge trigger.
	EXTI->RTSR |= 1;
	
	//Enable the SYSCFG Peripheral and enable PA0
	RCC->APB2ENR |= 1;

	SYSCFG->EXTICR[0] &= 0;
	
	//Set Green LED HIGH
	GPIOC->BSRR |= (1<<9);
	
	__NVIC_EnableIRQ(EXTI0_1_IRQn);
	
	NVIC_SetPriority(SysTick_IRQn, 2);
	
	NVIC_SetPriority(EXTI0_1_IRQn, 3);
//******************************************************	
	
	
	
	

while (1) {

	//LAB02***********************************************
	//Toggle Red LED every 500ms
	GPIOC->BSRR |= (1<<6); //Turn LED on
	HAL_Delay(500);
	GPIOC->BSRR |= (01<<22); //Turn OFF 
	HAL_Delay(500);
	//****************************************************
	
}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */

//LAB02****************************************************************

void EXTI0_1_IRQHandler(void){
	
	//LAB02 PART01***********************************
	static int check = 0; // Static variable to keep track of LED state
	
	// Toggle between green and orange LEDs
		
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9);
	
	 //Loop to break HAL delay library. (UNCOMMENT FOR PT2)
	 for(int i = 0; i <= 1500000; i++){
		 
		 __asm volatile ("nop");
	 }
	 
	 HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9);
		
		EXTI->PR |= 1;
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
