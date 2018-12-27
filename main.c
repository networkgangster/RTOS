/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "stdio.h"
#include <stdlib.h>





// Task priorities: Higher numbers are higher priority.
#define mainTestTask_Priority ( tskIDLE_PRIORITY + 1 )
//TaskHandle_t xHandle = NULL;
//BaseType_t xReturned;

//void Delay(__IO uint32_t nCount);
//void init(void);
static void Start( void *pvParameters );
static void Ausgabe( void *pvParameters );
static void Startsequenz( void *pvParameters );
static void Random( void *pvParameters );
static void Output( void *pvParameters );
static void ToggleBlau( void *pvParameters );
static void ToggleRot( void *pvParameters );
static void ToggleGelb( void *pvParameters );
static void ToggleGruen( void *pvParameters );
static void USARTRx( void *pvParameters );
static void Vergleich( void *pvParameters );
static void Gruen( void *pvParameters );
static void Random2( void *pvParameters );
static void Rot( void *pvParameters );
static void Reset( void *pvParameters );

void vTaskDelay( portTickType xTicksToDelay );

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;
int z=0, s=0;
int zug=1;
int zeit=1000;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);
void Init (void);

/* Private functions ---------------------------------------------------------*/

QueueHandle_t startq, randomq, rxq;
SemaphoreHandle_t semstart, semlauflicht, semrandom, semoutput, semblau, semrot, semgelb, semgruen, semrx;

int main(void)
{
	Init();
	
	semstart = xSemaphoreCreateBinary();
	semlauflicht = xSemaphoreCreateBinary();
	semrandom = xSemaphoreCreateBinary();
	semoutput = xSemaphoreCreateBinary();
	semblau = xSemaphoreCreateBinary();
	semrot = xSemaphoreCreateBinary();
	semgelb = xSemaphoreCreateBinary();
	semgruen = xSemaphoreCreateBinary();
	semrx = xSemaphoreCreateBinary();
	
	xSemaphoreGive(semstart);
	
	startq = xQueueCreate( 1000, sizeof(char) );
	randomq = xQueueCreate( 1000, sizeof(char) );
	rxq = xQueueCreate( 1000, sizeof(char) );	
	
	xTaskCreate( Start , "Start", configMINIMAL_STACK_SIZE, NULL, 1, NULL );  // LOW
	xTaskCreate( Ausgabe , "Ausgabe", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( Startsequenz , "Startsequenz", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( Random , "Random", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( Output , "Output", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( ToggleBlau , "Togglesequenz", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( ToggleRot , "Togglesequenz", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( ToggleGelb , "Togglesequenz", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( ToggleGruen , "Togglesequenz", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( USARTRx , "USARTRx", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( Vergleich , "Vergleich", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( Gruen , "Gruen", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( Random2 , "Random2", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( Rot , "Rot", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( Reset , "Reset", configMINIMAL_STACK_SIZE, NULL, 1, NULL );


	
    vTaskStartScheduler(); // This should never return.
		// Will only get here if there was insufficient memory to create
    // the idle task.
    for( ;; );
}
//_________________________________________________________
void Start( void * pvParameters )
{	
	// Start Text Raus schicken über queue
	// Und bei restart  muss wieder auf 0
	char sendString[16];
	char myChar;
	sprintf(sendString, "Bitte tippen sie 's' ein");
			for (int j=0; sendString[j] != '\0'; j++) {
				xQueueSend( startq, &sendString[j], (portTickType) 10 );	
				}
			
for( ;; ){

	if (xSemaphoreTake( semstart, ( TickType_t ) 4200 ) == pdTRUE )
			{
				//LEDBlauToggle();
				
				// wenn etwas recieved wurde mach weiter wenn nicht warte hier 
				for(;!(USART_GetFlagStatus(USART2, USART_FLAG_RXNE));)
				{
				}
				
					myChar=USART_ReceiveData(USART2);
			
		//Wenn s eingegeben wurde dann gebe semaphore
			if(myChar == 's'){
		xSemaphoreGive( semlauflicht );	
			}
			
				
	}
}
	
}

void Ausgabe( void * pvParameters )
{
for( ;; ){
	
	char sendChar;
	for(;;)
	{
		if (xQueueReceive( startq, &sendChar, (portTickType) 10 )) {
			USART_SendData(USART2, sendChar);
			}
		vTaskDelay(1);
	}
	}		
}

void Startsequenz( void * pvParameters )
{
for( ;; ){
	if (xSemaphoreTake( semlauflicht, ( TickType_t ) 4200 ) == pdTRUE )
		{
        LEDBlauOn();
				vTaskDelay(100);
				LEDBlauOff();
				vTaskDelay(100);
				LEDRotOn();
				vTaskDelay(100);
				LEDRotOff();
				vTaskDelay(100);
				LEDGelbOn();
				vTaskDelay(100);
				LEDGelbOff();
				vTaskDelay(100);
				LEDGruenOn();
				vTaskDelay(100);
				LEDGruenOff();
				vTaskDelay(100);
				
				LEDBlauOn();
				vTaskDelay(100);
				LEDBlauOff();
				vTaskDelay(100);
				LEDRotOn();
				vTaskDelay(100);
				LEDRotOff();
				vTaskDelay(100);
				LEDGelbOn();
				vTaskDelay(100);
				LEDGelbOff();
				vTaskDelay(100);
				LEDGruenOn();
				vTaskDelay(100);
				LEDGruenOff();
				vTaskDelay(100);
				
				xSemaphoreGive(semrandom);
			}

	}		
}

void Random( void * pvParameters )
{
	int num;

	for( ;; ){
	if (xSemaphoreTake( semrandom, ( TickType_t ) 4200 ) == pdTRUE )
		{			
					num = (rand() % 4 ) + 1 + 48; // von 1 bis 4 , 48 wegen asci
		xQueueSend( randomq, &num, (portTickType) 10 );
			
		xSemaphoreGive(semoutput);
		}
	}	
}

void Output( void * pvParameters )
{
		char sendChar;
	
		for( ;; ){
			
		if (xSemaphoreTake( semoutput, ( TickType_t ) 4200 ) == pdTRUE )
		{
			for(int i = 0;i<zug;i++){
				
			if (xQueueReceive( randomq, &sendChar, (portTickType) 10 )) {
					if (sendChar=='1')
					{
						xSemaphoreGive(semblau);
					}
					else if (sendChar=='2')
					{					
						xSemaphoreGive(semrot);
					}
					else if (sendChar=='3')
					{
						xSemaphoreGive(semgelb);
					}
					else if (sendChar=='4')
					{
					xSemaphoreGive(semgruen);
					}
			}
			
			
		}
			
			xSemaphoreGive(semrx);
		
	}	
}
}

void ToggleBlau( void * pvParameters )
{
		for( ;; ){
	
	if (xSemaphoreTake( semblau, ( TickType_t ) 4200 ) == pdTRUE )
		{
			LEDBlauOn();
			vTaskDelay(zeit);
			LEDBlauOff();
			xSemaphoreGive(semoutput);
		}
	}
}
void ToggleRot( void * pvParameters )
{
		for( ;; ){
		if (xSemaphoreTake( semrot, ( TickType_t ) 4200 ) == pdTRUE )
		{
			LEDRotOn();
			vTaskDelay(zeit);
			LEDRotOff();
			xSemaphoreGive(semoutput);
		}
	}
}

void ToggleGelb( void * pvParameters )
{
		for( ;; ){
		if (xSemaphoreTake( semgelb, ( TickType_t ) 4200 ) == pdTRUE )
		{
			LEDGelbOn();
			vTaskDelay(zeit);
			LEDGelbOff();
			xSemaphoreGive(semoutput);
		}
	}
}

void ToggleGruen( void * pvParameters )
{
		for( ;; ){
		if (xSemaphoreTake( semgruen, ( TickType_t ) 4200 ) == pdTRUE )
		{
			LEDGruenOn();
			vTaskDelay(zeit);
			LEDGruenOff();
			xSemaphoreGive(semoutput);
		}
	}	
}

void USARTRx( void * pvParameters )
{
		for( ;; ){
	//weiter
	
	}	
}

void Vergleich( void * pvParameters )
{
		for( ;; ){
	
	}	
}

void Gruen( void * pvParameters )
{
		for( ;; ){
	
	}	
}

void Random2( void * pvParameters )
{
		for( ;; ){
	
	}	
}

void Rot( void * pvParameters )
{
		for( ;; ){
	
	}	
}

void Reset( void * pvParameters )
{
		for( ;; ){
	
	}	
}
//_________________________________________________________

//_________________________________________________________

//_________________________________________________________

//_________________________________________________________

/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

void Init (void)
{
	GPIO_InitTypeDef GPIO_IS;
	USART_InitTypeDef USART_IS;

  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
	NVIC_SetPriority (SysTick_IRQn, 0);
  
  /* Add your application code here */
  /* Insert 50 ms delay */
  Delay(50);
	

  /* Enable the GPIOC peripheral */ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  
  /* Configure MCO1 pin(PA5) in output */
	GPIO_IS.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_IS.GPIO_OType = GPIO_OType_OD;
	GPIO_IS.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_15;
	GPIO_IS.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_IS.GPIO_Speed = GPIO_Speed_2MHz;
	
  GPIO_Init(GPIOC, &GPIO_IS);
  
  /* Output HSE clock on MCO1 pin(PA8) ****************************************/ 
  /* Enable the GPIOA peripheral */ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  /* Configure MCO1 pin(PA5) in output */
	GPIO_IS.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_IS.GPIO_OType = GPIO_OType_PP;
	GPIO_IS.GPIO_Pin = GPIO_Pin_5;
	GPIO_IS.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_IS.GPIO_Speed = GPIO_Speed_2MHz;
	
  GPIO_Init(GPIOA, &GPIO_IS);
	
	
/// ------ Pin fuer USART AF konfigurieren ---------------	
	/* Enable the GPIOA peripheral */ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  /* Configure MCO1 pin(PA2 & PA3) in alternate function */
	GPIO_IS.GPIO_Mode = GPIO_Mode_AF;
	GPIO_IS.GPIO_OType = GPIO_OType_PP;
	GPIO_IS.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_IS.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_IS.GPIO_Speed = GPIO_Speed_2MHz;
	
  GPIO_Init(GPIOA, &GPIO_IS);
	
	GPIO_PinAFConfig (GPIOA, GPIO_PinSource2, GPIO_AF_USART2);  // Tx AF7 fuer USART2 waehlen
	GPIO_PinAFConfig (GPIOA, GPIO_PinSource3, GPIO_AF_USART2);  // Rx AF7 fuer USART2 waehlen

/// ------ Pin fuer USART AF konfigurieren ---------------	

/// ------ USART konfigurieren ---------------
/* Enable the USART2 peripheral */ 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  // 2x APB1 , USART2
	
		USART_IS.USART_BaudRate = 9600;
		USART_IS.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_IS.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
		USART_IS.USART_Parity = USART_Parity_No;
		USART_IS.USART_StopBits = USART_StopBits_1;
		USART_IS.USART_WordLength = USART_WordLength_8b;
		
		USART_Init (USART2, &USART_IS);
		
		// jede Peripheral muss eingeschaltet werden !!!!!
		USART_Cmd (USART2, ENABLE);

/// ------ USART konfigurieren ---------------	

LEDBlauOff();
LEDGelbOff();
LEDGruenOff();
LEDRotOff();

}

///**
//  * @brief  Inserts a delay time.
//  * @param  nTime: specifies the delay time length, in milliseconds.
//  * @retval None
//  */
//void Delay(__IO uint32_t nTime)
//{ 
//  uwTimingDelay = nTime;

//  while(uwTimingDelay != 0);
//}

///**
//  * @brief  Decrements the TimingDelay variable.
//  * @param  None
//  * @retval None
//  */
//void TimingDelay_Decrement(void)
//{
//  if (uwTimingDelay != 0x00)
//  { 
//    uwTimingDelay--;
//  }
//}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
