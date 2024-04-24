
#include <stdio.h>
#include <stdlib.h>
#include "stm32f0xx.h"
#include "motor.h"

/* -------------------------------------------------------------------------------------------------------------
 *  Final Project Code - Water level controller and toxicity sensor 
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
char one[] = {'T','a','n','k',' ','E','m','p','t','y',',',' ','f','i','l','l','i','n','g',' ','i','n',' ','p','r','o','g','r','e','s','s','\n','\0'};
char done[] = {'F','i','l','l','i','n','g',' ','i','s',' ','c','o','m','p','l','e','t','e','!','\n','\0'};	
char errorstring2[] = {'T','O','X','I','C',' ','W','A','T','E','R','\t','M','A','N','U','A','L',' ','R','E','S','E','T',' ','R','E','Q','U','I','R','E','D','\n','\0'}; 
char cmdprompt[] = {'C','M','D','?','\0'};

char char1[] = {' ','M','o','d','e','\n','\0'};
char char2[] = {' ','S','e','t','t','i','n','g','\n','\0'};


/* -------------------------------------------------------------------------------------------------------------
 *  Miscellaneous Core Functions
 *  -------------------------------------------------------------------------------------------------------------
 */

void LED_init(void) {
    // Initialize PC8 and PC9 for LED's
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;                                          // Enable peripheral clock to GPIOC
    GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;                  // Set PC8 & PC9 to outputs
    GPIOC->OTYPER &= ~(GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0);                    // Set to push-pull output type
    GPIOC->OSPEEDR &= ~((GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0) |
                        (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0));   // Set to low speed
    GPIOC->PUPDR &= ~((GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_PUPDR_PUPDR8_1) |
                      (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0));             // Set to no pull-up/down
    GPIOC->ODR &= ~(GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0);                                   // Shut off LED's
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
		RCC->AHBENR |= (1<<17); //GPIOA enable
		RCC->AHBENR |= (1<<18);	//GPIOB enable
	
		GPIOA->MODER &= ~((1<<0) | (1<<1));
		GPIOA->OTYPER &= 0;
		GPIOA->OSPEEDR &= 0;
		GPIOA->PUPDR |= 2;
	
		GPIOB->MODER &= ~((1<<6) | (1<<7));
		GPIOB->OTYPER &= 0;
		GPIOB->OSPEEDR &= 0;
		GPIOB->PUPDR |= (2<<6);
	//GPIOB->PUPDR |= (2<<6);
		
		EXTI->IMR |= (1<<3); //PA3

		//Unmask interrupt generation on EXTI input.
		EXTI->IMR |= 1; //PA0
		
	
		//Set input to have a rising-edge trigger.
		EXTI->RTSR |= 1; //PA0
		EXTI->RTSR |= (1<<3); //PB3

	
		//Enable the SYSCFG Peripheral and enable PA0
		RCC->APB2ENR |= 1;
	
		SYSCFG->EXTICR[0] &= 0;	//EXTI0
		
		SYSCFG->EXTICR[0] |= (1<<12);	//EXTI3
		
		//Set priority of external interrupts, shut down being highest priority
		__NVIC_EnableIRQ(EXTI0_1_IRQn);
		__NVIC_EnableIRQ(EXTI2_3_IRQn);
	
		NVIC_SetPriority(SysTick_IRQn, 3);
	
		//Low water level interrupt on PA0
		NVIC_SetPriority(EXTI0_1_IRQn, 1);
		
		//Toxic water interrupt on PB3
		NVIC_SetPriority(EXTI2_3_IRQn, 2);
	
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
 * Begins main program loop
 * -------------------------------------------------------------------------------------------------------------
 */
volatile uint32_t encoder_count = 0;
volatile uint32_t PWM = 0;
volatile uint32_t PWMcap = 100;
volatile uint32_t interruptCount = 0;
volatile uint8_t levelflag = 0;
volatile uint32_t toxicflag = 0;
volatile uint32_t count= 0;

int main(int argc, char* argv[]) {

    debouncer = 0;                          
		HAL_Init();															// Initialize HAL
    LED_init();                             // Initialize LED's
    button_init();                          // Initialize button
    motor_init();                           // Initialize motor code
	
		exti_init();
		usart_init();
		
	
	
	
    while (1) {
			
			//Check for toxic flag interrupt
			if(toxicflag > 0){
				transtring(errorstring2);
				break;
			}
			else if(toxicflag == 0){
			
				if(flagSet == 1){
			
					Parse();
				
					flagSet = 0;
			
				}
				
				pwm_setDutyCycle(PWM);
				
				// If low level sensor triggers an interrupt, set the pump to fill container
				if(levelflag > 0){
					
					transtring(one); // Message pump is running
					GPIOC->BSRR |= (1<<8);
					
					//Sets water level and runs pump 
					while(count < 2000000){
						
						pwm_setDutyCycle(PWM);
				
						if(toxicflag > 0){
						transtring(errorstring2);
						PWM=0;
						break;
						}
						count++;
					}
					
					GPIOC->BSRR |= (1<<24);
					
					transtring(done);
					count = 0;
					PWM = 0;
					levelflag = 0;
				}
			
    }
		
		
	}
}

//Function to read USART commands
void Parse(void){
	
	if(counter == 0){
		color = readData;
		
		if(!(color == 'a'|| color == 'm')){
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
	
	//Used to set motor rates
	if(counter == 2){
		if(color == 'a'){
			if(mode == '0'){
		
				PWMcap = 90;
			}
			else if(mode == '1'){
				
				PWMcap = 95;
			}
			else if(mode == '2'){
			
				PWMcap = 100;
			}
			else
				transtring(errorstring);
			
		}
		//Used to turn pump on and off manually 
		else if(color == 'm'){
			if(mode == '0'){
				PWM = 0;
			}
			else if(mode == '1'){
				PWM = PWMcap;
			}
			else
				transtring(errorstring);
			
			
		}
		//Error message if invalid color is entered
		else if(color != 13 || color != 'a' || color != 'm')  {
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

//Handler to interrupt main when the water level drops below a set threshold. 
void EXTI0_1_IRQHandler(void){

	static int check = 0; // Static variable to keep track of LED state
	if(interruptCount == 0){
		levelflag = 1;
	  PWM = PWMcap;
		GPIOC->BSRR |= (1<<7); // blue LED signals pump is running
		
		interruptCount++;
		
	}
	else if(interruptCount == 1){
		PWM = 0;
		GPIOC->BSRR |= (1<<23); // turn LED signal off
		interruptCount = 0;
	}
	// Toggle between green and orange LEDs
		
		EXTI->PR |= 1;
}

//Toxic water interrupt
void EXTI2_3_IRQHandler(void){

	
		//If the pump is not running and toxic water is detected, stop system
		if(levelflag != 1){
		pwm_setDutyCycle(0);
		PWM = 0;
		GPIOC->BSRR |= (1<<6);
		toxicflag = 1;
		//Dont exit interrupt, user reset is now required.
		}
		EXTI->PR |= 1;
}


