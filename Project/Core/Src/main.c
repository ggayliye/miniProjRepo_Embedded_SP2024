
#include <stdio.h>
#include <stdlib.h>
#include "stm32f0xx.h"
#include "motor.h"

/* -------------------------------------------------------------------------------------------------------------
 *  Global Variable Declarations
 *  -------------------------------------------------------------------------------------------------------------
 */
volatile uint32_t debouncer;

void tranchar(char key);

void transtring(char key[]);

void Parse();

volatile int readData;
volatile int flagSet;
volatile int counter = 0;
volatile char color;
volatile int mode;

char errorstring[] = {'E','R','R','O','R',':','\t','I','N','V','A','L','I','D','\t','K','E','Y','\n','\0'}; 
char cmdprompt[] = {'C','M','D','?','\0'};
char testpoint[] = {'a','a','a','\n','\0'};

char char1[] = {'C','H','A','R','1','\n','\0'};
char char2[] = {'C','H','A','R','2','\n','\0'};


/* -------------------------------------------------------------------------------------------------------------
 *  Miscellaneous Core Functions
 *  -------------------------------------------------------------------------------------------------------------
 */

void LED_init(void) {
    // Initialize PC8 and PC9 for LED's
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;                                          // Enable peripheral clock to GPIOC
    GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;                  // Set PC8 & PC9 to outputs
    GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9);                    // Set to push-pull output type
    GPIOC->OSPEEDR &= ~((GPIO_OSPEEDR_OSPEEDR8_0 | GPIO_OSPEEDR_OSPEEDR8_1) |
                        (GPIO_OSPEEDR_OSPEEDR9_0 | GPIO_OSPEEDR_OSPEEDR9_1));   // Set to low speed
    GPIOC->PUPDR &= ~((GPIO_PUPDR_PUPDR8_0 | GPIO_PUPDR_PUPDR8_1) |
                      (GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR9_1));             // Set to no pull-up/down
    GPIOC->ODR &= ~(GPIO_ODR_8 | GPIO_ODR_9);                                   // Shut off LED's
}

void  button_init(void) {
    // Initialize PA0 for button input
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;                                          // Enable peripheral clock to GPIOA
    GPIOA->MODER &= ~(GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1);               // Set PA0 to input
    GPIOC->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0_0 | GPIO_OSPEEDR_OSPEEDR0_1);     // Set to low speed
    GPIOC->PUPDR |= GPIO_PUPDR_PUPDR0_1;                                        // Set to pull-down
}

//Initialize low level sensor cutoff trigger
void exti_init(void)	{
	
	//Configure user pushbutton for low water level sensor interrupt
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
	
		__NVIC_EnableIRQ(EXTI0_1_IRQn);
	
		NVIC_SetPriority(SysTick_IRQn, 2);
	
		NVIC_SetPriority(EXTI0_1_IRQn, 1);
	
}

void usart_init(void)		{
	GPIOC->MODER |= (10 << 8);
	
	//Enable afrl for pc4 and pc5 
	// 00010001 shifted left 16 (AF1) (AF1)
	GPIOC->AFR[0] |= (17 << 16); 
	
	//Enable the clock to the USART register. 
	//Writes a 1 to enable USART3 Clock
	RCC->APB1ENR |= (1 << 18);
	
	//Set the baud rate BRR value
	USART3->BRR = 69; //69(HAL_RCC_GetHCLKFreq()/115200)
	
	//Enable transmit and recieve as well as enable the USART
	USART3->CR1 |= 13;
	
	//Enable RXNE Interrupt
	USART3->CR1 |= (1<<5);
	
	//Interrupt enable 
	__NVIC_EnableIRQ(USART3_4_IRQn);
	NVIC_SetPriority(USART3_4_IRQn, 0);
	
}

/* Called by SysTick Interrupt
 * Performs button debouncing, changes wave type on button rising edge
 * Updates frequency output from ADC value
 */
void HAL_SYSTICK_Callback(void) {
    // Remember that this function is called by the SysTick interrupt
    // You can't call any functions in here that use delay

    debouncer = (debouncer << 1);
    if(GPIOA->IDR & (1 << 0)) {
        debouncer |= 0x1;
    }

    if(debouncer == 0x7FFFFFFF) {
    switch(target_rpm) {
        case 80:
            target_rpm = 50;
            break;
        case 50:
            target_rpm = 81;
            break;
        case 0:
            target_rpm = 80;
            break;
        default:
            target_rpm = 0;
            break;
        }
    }
}

/* -------------------------------------------------------------------------------------------------------------
 * Main Program Code
 *
 * Starts initialization of peripherals
 * Blinks green LED (PC9) in loop as heartbeat
 * -------------------------------------------------------------------------------------------------------------
 */
volatile uint32_t encoder_count = 0;
volatile uint32_t PWM = 100;
volatile uint32_t interruptCount = 0;

int main(int argc, char* argv[]) {

    debouncer = 0;                          // Initialize global variables
		HAL_Init();															// Initialize HAL
    LED_init();                             // Initialize LED's
    button_init();                          // Initialize button
    motor_init();                           // Initialize motor code
	
		exti_init();
		usart_init();
		
	
	
    while (1) {
        GPIOC->ODR ^= GPIO_ODR_9;           // Toggle green LED (heartbeat)
        encoder_count = TIM2->CNT;
			
				if(flagSet == 1){
			
					Parse();
				
					flagSet = 0;
			
				}
				
				// PROJECT When board is reset, start filling for 4.5 seconds at 90% duty cycle
				pwm_setDutyCycle(PWM);
			
        //HAL_Delay(128);                      // Delay 1/8 second
    }
}

//************************************************************************

void Parse(void){
	
	if(counter == 0){
		color = readData;
		
		if(!(color == 'a'|| color == 'm' || color == 'g' || color == 'o')){
			transtring(errorstring);
			counter = 0;
		}
		else{
			transtring(char1);
			counter++;
		}
	}
	else if(counter == 1){
		mode = readData;
		transtring(char2);
		counter++;
		
	}
	
	//transtring(testpoint);
	if(counter == 2){
		if(color == 'a'){
			if(mode == '0'){
				//Turn off LED
				//GPIOC->BSRR |= (1<<22);
				PWM = 0;
			}
			else if(mode == '1'){
				//Turn on LED
				//GPIOC->BSRR |= (1<<6);
				PWM = 100;
			}
			else if(mode == '2'){
				//Toggle LED
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
			}
			else
				transtring(errorstring);
			
		}
		else if(color == 'o'){
			if(mode == '0'){
				//Turn off LED
				GPIOC->BSRR |= (1<<24);
			}
			else if(mode == '1'){
				//Turn on LED
				GPIOC->BSRR |= (1<<8);
			}
			else if(mode == '2'){
				//Toggle LED
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
			}
			else
				transtring(errorstring);
			
			
		}
		else if(color == 'g'){
			if(mode == '0'){
				//Turn off LED
				GPIOC->BSRR |= (1<<25);
			}
			else if(mode == '1'){
				//Turn on LED
				GPIOC->BSRR |= (1<<9);
			}
			else if(mode == '2'){
				//Toggle LED
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
			}
			else
				transtring(errorstring);
				
			
		}
		else if(color == 'b'){
			if(mode == '0'){
				//Turn off LED
				GPIOC->BSRR |= (1<<23);
			}
			else if(mode == '1'){
				//Turn on LED
				GPIOC->BSRR |= (1<<7);
			}
			else if(mode == '2'){
				//Toggle LED
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
			}
			else
				transtring(errorstring);
		}
		//Error message if invalid color is entered
		else if(color != 13 || color != 'r' || color != 'g' || color != 'b' || color != 'o')  {
			transtring(errorstring);
		}
		counter = 0;
	}
		
	
}
	
//USART3 Interrupt handler
void USART3_4_IRQHandler(void){
	
	if (USART3->ISR & USART_ISR_RXNE){
	//transtring(testpoint);
		flagSet = 1;
		
		readData = USART3->RDR;
		//transtring(testpoint);
	}
	
}
// Function used to transmit a character
// Takes a single character parameter and saves that into the TDR register.
void tranchar(char key)
{
	//While the transmit data register is not empty...
	// USART3->ISR != (USART3->ISR &= USART_ISR_TXE_Msk) 
	while(!(USART3->ISR & USART_ISR_TXE))
	{
		
	}
	
	USART3->TDR = key;
}

//Function used to transmit a string of chars
//Takes an array of chars and transmits each char seperately. 
void transtring(char key[])
{
	
		char current = key[0];
		
		for(int i = 0; current != 0; i++)
		{
			current = key[i];
			tranchar(current);
		}
}

//************************************************************************************

//Handler to interrupt main when the water level drops below a set threshold. 
void EXTI0_1_IRQHandler(void){
	
	//LAB02 PART01***********************************
	static int check = 0; // Static variable to keep track of LED state
	if(interruptCount == 0){
	 PWM = 0;
		interruptCount++;
	}
	else if(interruptCount == 1){
		PWM = 100;
		interruptCount = 0;
	}
	// Toggle between green and orange LEDs
		
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9);
	
	//PROJECT
	//Maybe kick off the water pump and wait until user reset 
	
	
	 //Loop to break HAL delay library. (UNCOMMENT FOR PT2)
	 for(int i = 0; i <= 1500000; i++){
		 
		 __asm volatile ("nop");
	 }
	 
	
	 HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9);
		
		EXTI->PR |= 1;
}


// ----------------------------------------------------------------------------
