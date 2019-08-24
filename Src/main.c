/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body for flash updation of VIM
  * @author			: Shantam Bajpai
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct{
	int age;
	char FirstName[15];
	char MiddleName[15];
	char LastName[15];
}Update_FlashInitTypeDef;

struct Node
{
	char data;
	struct Node* next;
};
struct Node* front = NULL;
struct Node* tail = NULL;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
Update_FlashInitTypeDef __uninited_region_start__  __attribute__((section(".upflash"))) ;
const Update_FlashInitTypeDef *lConfigureFlash = &__uninited_region_start__;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

int _write(int fd, char *str, int len)
{return (HAL_UART_Transmit(&huart2,(uint8_t*)str,len,HAL_MAX_DELAY)==HAL_OK) ? (len): (0);}

void Flash_Write(uint32_t Flash_address , uint8_t Flash_Data);
void Flash_Write_Int(uint32_t Flash_address_int, uint32_t Flash_Data_int);
//uint32_t Flash_Read(uint32_t Flash_address);
void Flash_Read(uint32_t Flash_address);
void EnqueueData(char x);
void Dequeue();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t Flash_address __attribute__((unused));
char rxData;
/**important as the compiler thinks that its value wont change through the project life cycle hence use volatile
to tell compiler that its value will change during the program lifecycle**/
volatile uint8_t newline;
char buffer[40];
volatile uint8_t length = 0;
int count = 0;
int StringLengthFirst = 0;
int StringLengthLast = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  char myAge[3];
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, (uint8_t*)&rxData, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
   if(newline)
   	    {

   	    while(length)
   	    {
   	  	  Dequeue();
   	    }
   	    newline--; //Reset Newline
   	    /**DECLARATION OF TOKEN**/
   	    char* token = strtok(buffer , ":");
   	    /**END F DECLARATION OF TOKEN**/

   	    /**STRING CHECK TO SEE IF WRITE DATA or READ DATA**/

   	    if(strcmp(token,"WRITE DATA")==0)
   	    {
   	  	/**FLASH SECTOR ERASE FUNCTIONALITY**/
   	  	HAL_FLASH_Unlock();
   	    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGSERR );
   	    FLASH_Erase_Sector(FLASH_SECTOR_4,VOLTAGE_RANGE_3);
   	    HAL_FLASH_Lock();
   	    /**FLASH ERASE SECTOR COMPLETE**/
   	  	  for(int i=0;i<3;i++)
   	  	  {
   	  		  token = strtok(NULL , ",");
   	  		  if(i==0)
   	  		  {
   	  			  printf("%s,%d\r\n",token,i);
   	  			  for(int i=0;i<strlen(token);i++)
   	  				  {
   	  				  	  StringLengthFirst = strlen(token);
   	  				  	  Flash_Write((__IO uint32_t)&lConfigureFlash->FirstName[i],token[i]);
   	  				  }
   	  		  }
   	  		  else if(i==1)
   	  		  {
   	  			  printf("%s,%d\r\n",token,i);
   	  			  for(int j=0;j<strlen(token);j++)
   	  				  {
   	  				  	  StringLengthLast = strlen(token);
   	  				  	  Flash_Write((__IO uint32_t)&lConfigureFlash->LastName[j],token[j]);
   	  				  }
   	  		  }
   	  		  else if(i==2)
   	  		  {
   	  			  printf("%s,%d\r\n",token,i);
   	  			  for(int j=0;j<strlen(token);j++)
   	  				  myAge[j] = token[j];
   	  			  Flash_Write_Int((__IO uint32_t)&lConfigureFlash->age,atoi(myAge));  //ASCII to Integer
   	  		  }
   	  	 }

   	  }
   	    else if(strcmp(token , "READ DATA")==0)
   	    {
   	  	  printf("%d\r\n",lConfigureFlash->age);
  	  	  for(int i=0;i<StringLengthFirst;i++)
   	  		  printf("%c",lConfigureFlash->FirstName[i]);
  	  	  printf("\n");
   	  	  for(int i=0;i<StringLengthLast;i++)
   	  		  printf("%c",lConfigureFlash->LastName[i]);
   	  	  printf("\n");
   	    }
	   else
   	    {
   	    	printf("Format in which you entered the data is not valid");
   	    }
   	  }
   	  for(int i=0;i<sizeof(buffer);i++)
   		  buffer[i] = 0;  //Setting buffer to0 for continuous updation of data
   	   count = 0; //Reset Counter
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE BEGIN WHILE */
    /* USER CODE END WHILE */
}

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/**DEVELOPMENT OF QUEUE FOR RECIEVING DATA**/

void EnqueueData(char x)
{
	struct Node* temp = (struct Node*)malloc((sizeof(struct Node)));
	temp->data = x;
	temp->next = NULL;
	if(front == NULL && tail == NULL)
	{
		front = tail = temp;
	}
	tail->next = temp;
	tail = temp;
	length++;
}

/**END OF ENQUEUE FUNCTION**/

/**DEVELOPMENT OF DEQUEUE FUNCTION**/

void Dequeue()
{
	struct Node* temp = front;
	if(front == NULL)
		{
		return;
		}
	else if(front == tail)
	{
		front = tail = NULL;
	}
	else
	{
		front = front->next;
	}
	buffer[count] = temp->data;
	free(temp);
	count++;
	length--;
	if(count > 40)
	{
		printf("Out of Bounds Data!!!");
	}
}

void Flash_Write(uint32_t Flash_address , uint8_t Flash_Data) //FOR CHAR DATATYPE
{
	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGSERR );
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE , Flash_address , Flash_Data);
	HAL_FLASH_Lock();
}

void Flash_Write_Int(uint32_t Flash_address_int, uint32_t Flash_Data_int) //FOR INT DATATYPE
{
	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGSERR );
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Flash_address_int,Flash_Data_int);
	HAL_FLASH_Lock();
}
void Flash_Read(uint32_t Flash_address)
{
	uint32_t Flash_Data;
	Flash_Data = *(uint32_t*)Flash_address;
	printf("%lu",Flash_Data);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	EnqueueData(rxData);
	if(rxData == '\n')
		newline++;
	HAL_UART_Receive_IT(huart , (uint8_t*)&rxData , 1);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
