/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"ST7735\ST7735.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BOTAO9 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)
#define BOTAO10 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)
#define BOTAO11 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)
#define BOTAO12 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)

#define LED3_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1)
#define LED4_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,1)
#define LED5_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1)
#define LED6_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1)

#define LED3_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0)
#define LED4_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0)
#define LED5_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0)
#define LED6_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
uint16_t cor=BLUE;
short camp[8][8];
short bomba = 10;
short casastotais = 36;
short casasvitoria = 0;
short casasabertas = 0;
short posxjogador=0;
short posyjogador=0;
short raio= 1;
short posx=0;
short posxtitulo=13;
short posxtela=30;
short posytitulo=0;
short posytela=30;
short posytela2=15;
short posytela3=45;
short posytela4=60;
short posy=0;
short bandeira;
int i, j = 0;
short cursorX = 1, cursorY = 1;
char buffer [10];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
// short está sendo utilizado por causa do espaço ocupado que é menor do que int
short Menu( uint16_t cor, short bomba);
short Jogo(uint16_t cor);
short DificuldadeLed(uint16_t cor);
short Derrota_Vitoria(short casasabertas, uint16_t cor);
short MudarCor(uint16_t cor);
void cursorEsquerda(void);
void cursorDireita(void);
int sprintf(char *str, const char *format, ...);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7735_Init();
 // unsigned int C = sizeof(camp[0]); //C=Coluna
 // unsigned int L = sizeof(camp)/C; //L=Linha
 // srand(SysTick->VAL);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 // short cor=0;
	   Menu(cor,bomba);
	   ST7735_FillScreen(BLACK);
	   while (1){

	   }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_DC_Pin|ST7735_RES_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin PB3 PB4
                           PB5 PB6 */
  GPIO_InitStruct.Pin = ST7735_DC_Pin|ST7735_RES_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
short Menu( uint16_t cor,short bomba){
	ST7735_FillScreen(cor);
	int escolha=0;
	ST7735_WriteString(posxtitulo, posytitulo,"Campo Minado",Font_11x18, BLACK, cor );
	ST7735_WriteString(posxtela, posytela,"P9-Jogar!",Font_7x10, BLACK, cor );
	ST7735_WriteString(posxtela, posytela3,"P10-Dificuldade:",Font_7x10, BLACK, cor );
	ST7735_WriteString(posxtela, posytela4,"P11-Cores:",Font_7x10, BLACK, cor );


	while(escolha==0){
    	if (BOTAO9 == 0 && BOTAO10 == 1 && BOTAO11 == 1 && BOTAO12 == 1) {
    	escolha=1;
    	}
    	else if (BOTAO9 == 1 && BOTAO10 == 0 && BOTAO11 == 1 && BOTAO12 == 1) {
    	    	    escolha=2;
    	    	  }

	else if (BOTAO9 == 1 && BOTAO10 == 1 && BOTAO11 == 0 && BOTAO12 == 1) {
	    	    	    escolha=3;
	    	    	  }
		}

	switch (escolha) {
			case 1:
		    Jogo(cor);
			break;

			case 2:
			DificuldadeLed(cor);
			break;

			case 3:
			MudarCor(cor);
			Menu(cor,bomba);
			break;
		}


	}

short Jogo(uint16_t cor){
	distribuirBombas(bomba);
	int verificarbotao=0;
	ST7735_FillScreen(cor);
	ST7735_WriteString(posxtitulo, posytitulo, "Jogabilidade",Font_11x18, BLACK, cor );
	ST7735_WriteString(7, posytela, "P10- colocar Bandeiras",Font_7x10, BLACK, cor );
	ST7735_WriteString(23, posytela3 + 10, "Pr. qualquer botao",Font_7x10, BLACK, cor );
	while (BOTAO9!=0 && BOTAO10!=0 && BOTAO11!=0 && BOTAO12!=0) {
	}
	ST7735_FillScreen(cor);
	ST7735_FillRectangleFast(0, 0, 80, 80, WHITE);
	ST7735_WriteString(90, posytela2, "Bandeiras",Font_7x10, BLACK, cor );
	atualizarBandeiras();
	for (i = 0; i <= 8; i++) {
		ST7735_DrawLine((i*10), 0, (i*10), 80, BLACK);
		ST7735_DrawLine(0, (i*10), 80, (i*10), BLACK);
	}
	ST7735_WriteString(2, 2, "X" , Font_7x10 , BLACK , WHITE);
	//Tabuleiro: -1:Bomba; 0:Vazio n explorado; 1:Explorado; 2:Bandeira
	while (verificarbotao==0){
		if (BOTAO9==0) {
			ST7735_WriteString(2 + (cursorX - 1) * 10, 2 + (cursorY - 1) * 10, " " , Font_7x10 , BLACK , WHITE);
			consertaTabuleiro ();
			cursorEsquerda();
			ST7735_WriteString(2 + (cursorX - 1) * 10, 2 + (cursorY - 1) * 10, "X" , Font_7x10 , BLACK , WHITE);
			consertaTabuleiro ();
		}
		else if (BOTAO11==0) {
			ST7735_WriteString(2 + (cursorX - 1) * 10, 2 + (cursorY - 1) * 10, " " , Font_7x10 , BLACK , WHITE);
			consertaTabuleiro ();
			cursorDireita();
			ST7735_WriteString(2 + (cursorX - 1) * 10, 2 + (cursorY - 1) * 10, "X" , Font_7x10 , BLACK , WHITE);
			consertaTabuleiro ();
		}
		else if (BOTAO12==0) {
			if (bomba > 0)
			Bandeira();
		}

	}

}
short MudarCor(uint16_t cor)
{
	ST7735_FillScreen(cor);
		short escolhacor=0;
		ST7735_WriteString(posxtitulo, posytitulo, "Tabela de cores",Font_7x10, BLACK, cor );
		ST7735_WriteString(posxtela, posytela2, "P9-Verde",Font_7x10, BLACK, cor );
		ST7735_WriteString(posxtela, posytela, "PA10-Magenta",Font_7x10, BLACK, cor );
		ST7735_WriteString(posytela, posytela3, "P11-Azul",Font_7x10, BLACK, cor );
		ST7735_WriteString(posxtela, posytela4, "P12-Voltar",Font_7x10, BLACK, cor );

		while(escolhacor==0){


			if (BOTAO9 == 0 && BOTAO10 == 1 && BOTAO11 == 1 && BOTAO12 == 1) {
				cor=GREEN;
				ST7735_FillScreenFast(cor);
				ST7735_WriteString(posxtitulo, posytitulo, "Tabela de cores",Font_7x10, BLACK, cor );
				ST7735_WriteString(posxtela, posytela2, "P9-Verde",Font_7x10, BLACK, cor );
				ST7735_WriteString(posxtela, posytela, "PA10-Magenta",Font_7x10, BLACK, cor );
				ST7735_WriteString(posxtela, posytela3, "P11-Azul",Font_7x10, BLACK, cor );
				ST7735_WriteString(posxtela, posytela4, "P12-Voltar",Font_7x10, BLACK, cor );

			    	}
			    	else if (BOTAO9 == 1 && BOTAO10 == 0 && BOTAO11 == 1 && BOTAO12 == 1) {
			    	    cor=MAGENTA;
			    	    ST7735_FillScreenFast(cor);
			    	    ST7735_WriteString(posxtitulo, posytitulo, "Tabela de cores",Font_7x10, BLACK, cor );
						ST7735_WriteString(posxtela, posytela2, "P9-Verde",Font_7x10, BLACK, cor );
		  				ST7735_WriteString(posxtela, posytela, "PA10-Magenta",Font_7x10, BLACK, cor );
 	    				ST7735_WriteString(posxtela, posytela3, "P11-Azul",Font_7x10, BLACK, cor );
	    				ST7735_WriteString(posxtela, posytela4, "P12-Voltar",Font_7x10, BLACK, cor );
			    	    	  }

				else if (BOTAO9 == 1 && BOTAO10 == 1 && BOTAO11 == 0 && BOTAO12 == 1) {
					cor=BLUE;
					ST7735_FillScreenFast(cor);
					ST7735_WriteString(posxtitulo,posytitulo, "Tabela de cores",Font_7x10, BLACK, cor );
					ST7735_WriteString(posxtela, posytela2, "P9-Verde",Font_7x10, BLACK, cor );
			  		ST7735_WriteString(posxtela, posxtela, "PA10-Magenta",Font_7x10, BLACK, cor );
					ST7735_WriteString(posxtela, posytela3, "P11-Azul",Font_7x10, BLACK, cor );
					ST7735_WriteString(posxtela, posytela4, "P12-Voltar",Font_7x10, BLACK, cor );
				    	    	  }
				else if(BOTAO9 == 1 && BOTAO10 == 1 && BOTAO11 == 1 && BOTAO12 == 0){
					Menu(cor,bomba);
				}
		}

}
short DificuldadeLed(uint16_t cor){
	int escolhadificuldade=0;

	ST7735_FillScreenFast(cor);
	ST7735_WriteString(posxtitulo, posytitulo, "Escolha o nivel",Font_7x10, BLACK, cor );
	ST7735_WriteString(posxtela, posytela2, "P9-Facil",Font_7x10, BLACK, cor );
	ST7735_WriteString(posxtela, posytela, "PA10-Medio",Font_7x10, BLACK, cor );
	ST7735_WriteString(posxtela, posytela3, "P11-Dificil",Font_7x10, BLACK, cor );
	ST7735_WriteString(posxtela, posytela4, "P12-Voltar",Font_7x10, BLACK, cor );

	while(escolhadificuldade==0){
	if(BOTAO9==0){
	LED6_LIGA;
	bomba=7;
}
	else if(BOTAO10==0){
		LED6_LIGA;
		LED5_LIGA;
	}
	else if(BOTAO11==0){
	LED6_LIGA;
	LED5_LIGA;
	LED4_LIGA;
	bomba=15;
	}
	else if(BOTAO12==0){
		LED6_DESLIGA;
		LED5_DESLIGA;
		LED4_DESLIGA;
		escolhadificuldade=1;
		Menu(cor,bomba);

	}

}
}
short Derrota_Vitoria(short casasabertas, uint16_t cor ){
		casasvitoria=casastotais-bomba;
		if(casasabertas==casasvitoria){
			ST7735_FillScreenFast(GREEN);
			ST7735_WriteString(posxtitulo, posytitulo, "Parabens!", Font_11x18, BLACK, cor);
			ST7735_WriteString(posxtela, posytela, "Deseja Continuar?", Font_7x10, BLACK, cor);
			ST7735_WriteString(posxtela, posytela3, "P9->Sim", Font_7x10, BLACK, cor);
			ST7735_WriteString(posxtela, posytela4, "P12->Nao", Font_7x10, BLACK, cor);
			if(BOTAO9==0){
							Jogo(cor);
						}
						else if(BOTAO12==0){
							return 0;
						}

		}
		else {
			ST7735_FillScreenFast(RED);
			ST7735_WriteString(posxtitulo, posytitulo, "Você Perdeu", Font_11x18, BLACK, cor);
			ST7735_WriteString(posxtela, posytela2, "Deseja Continuar?", Font_7x10, BLACK, cor);
			ST7735_WriteString(posxtela, posytela3, "P9->Sim", Font_7x10, BLACK, cor);
			ST7735_WriteString(posxtela, posytela4, "P12->Nao", Font_7x10, BLACK, cor);
			if(BOTAO9==0){
				Jogo(cor);
			}
			else if(BOTAO12==0){
				return 0;
			}



		}
	}

void Bandeira(void){
	camp[cursorX - 1][cursorY - 1] = 2;
	bomba--;

	ST7735_WriteString(2 + (cursorX - 1) * 10, 2 + (cursorY - 1) * 10, "B" , Font_7x10 , BLACK , WHITE);
	consertaTabuleiro ();

	cursorEsquerda();
	ST7735_WriteString(2 + (cursorX - 1) * 10, 2 + (cursorY - 1) * 10, "X" , Font_7x10 , BLACK , WHITE);
	consertaTabuleiro ();

	atualizarBandeiras();
	HAL_Delay(700);
}

void atualizarBandeiras() {
	sprintf(buffer, "%d ", bomba);
	ST7735_WriteString(110, 40, buffer,Font_11x18, BLACK, cor );
}
void cursorDireita () {
	for(;;) {
		cursorX++;
		if (cursorX == 9 && cursorY == 8) {
			cursorX = 1;
			cursorY = 1;
		} else if (cursorX == 9) {
			cursorX = 1;
			cursorY++;
		}

		if (camp[cursorX - 1][cursorY - 1] != 1 && camp[cursorX - 1][cursorY - 1] != 2) {
			return;
		}
	}
}
void cursorEsquerda () {
	for(;;) {
		cursorX--;
		if (cursorX == 0 && cursorY == 1) {
			cursorX = 8;
			cursorY = 8;
		} else if (cursorX == 0) {
			cursorX = 8;
			cursorY--;
		}

		if (camp[cursorX - 1][cursorY - 1] != 1 && camp[cursorX - 1][cursorY - 1] != 2) {
					return;
		}
	}
}
void consertaTabuleiro () {
			ST7735_DrawLine((cursorX*10), 0, (cursorX*10), 80, BLACK);
			ST7735_DrawLine(0, (cursorY*10), 80, (cursorY*10), BLACK);
}

void distribuirBombas(int nBombas) {
	for(;;) {
		for(i = 0; i < 8; i++) {
			for(j = 0; j < 8; j++) {
				short valor = (rand() % 2) - 1;
				nBombas+= valor;
				camp[i][j] = valor;
				if (nBombas == 0)
					return;
			}
		}
	}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
