#include "main.h"
#include "ADS1298.h"

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim2;

uint8_t ADS_READY;

uint8_t ADS_REGVal_Read[26] = {0};
uint8_t ADS_CMD[2] = {0, 0};

uint8_t ADS_RegVal[26] = {
	ID, CONFIG1, CONFIG2, CONFIG3, LOFF, CH1SET, CH2SET, CH3SET, CH4SET, CH5SET, CH6SET, CH7SET, CH8SET,
	RLD_SENSP, RLD_SENSN, LOFF_SENSP, LOFF_SENSN, LOFF_FLIP, LOFF_STATP, LOFF_STATN,
	GPIO, PACE, RESP, CONFIG4, WCT1, WCT2
};




/********************* ADS1298 Issue Opcode Command *********************/
void ADS_Send_WakeUp(void) {
	ADS_CMD[0] = CMD_WAKEUP;
	HAL_SPI_Transmit(&hspi1, ADS_CMD, 1, 100);
}

void ADS_Send_Standby(void) {
	ADS_CMD[0] = CMD_STANDBY;
	HAL_SPI_Transmit(&hspi1, ADS_CMD, 1, 100);
}

void ADS_Send_Reset(void) {
	ADS_CMD[0] = CMD_RESET;
	HAL_SPI_Transmit(&hspi1, ADS_CMD, 1, 100);
}

void ADS_Send_Start(void) {
	ADS_CMD[0] = CMD_START;
	HAL_SPI_Transmit(&hspi1, ADS_CMD, 1, 100);
}

void ADS_Send_Stop(void) {
	ADS_CMD[0] = CMD_STOP;
	HAL_SPI_Transmit(&hspi1, ADS_CMD, 1, 100);
}

void ADS_Send_Data_Rd_Cont(void) {
	ADS_CMD[0] = CMD_RDATAC;
	HAL_SPI_Transmit(&hspi1, ADS_CMD, 1, 100);
}

void ADS_Send_Data_Stop_Cont(void) {
	ADS_CMD[0] = CMD_SDATAC;
	HAL_SPI_Transmit(&hspi1, ADS_CMD, 1, 100);
}

void ADS_Send_Data_Rd_Single(void) {
	ADS_CMD[0] = CMD_RDATA;
	HAL_SPI_Transmit(&hspi1, ADS_CMD, 1, 100);
}

void ADS_Send_Reg_Rd(void) {
	ADS_CMD[0] = CMD_RREG_RegAddr;
	ADS_CMD[1] = CMD_RREG_RegNum;
	HAL_SPI_Transmit(&hspi1, ADS_CMD, 2, 100);
	HAL_SPI_Receive(&hspi1, (uint8_t*)(ADS_REGVal_Read), 26, 100);
	HAL_UART_Transmit(&huart1, (uint8_t*)(ADS_REGVal_Read), 26, 100);
}

void ADS_Send_Reg_Wr(void) {
	ADS_CMD[0] = CMD_WREG_RegAddr;
	ADS_CMD[1] = CMD_WREG_RegNum;
	HAL_SPI_Transmit(&hspi1, ADS_CMD, 2, 100);
	HAL_SPI_Transmit(&hspi1, ADS_RegVal, 26, 100);
}
/************************************************************************/





/********************* ADS1298 Pin Configuration *********************/
void ADS_ClkSel(int PinState) {
	if (PinState == LOW) HAL_GPIO_WritePin(ADS_CLKSEL_GPIO_Port, ADS_CLKSEL_Pin, GPIO_PIN_RESET);
	else HAL_GPIO_WritePin(ADS_CLKSEL_GPIO_Port, ADS_CLKSEL_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
}


void ADS_ExtClk(void) {
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_Delay(100);
}

void ADS_Reset(void) {
	HAL_GPIO_WritePin(ADS_RESET_GPIO_Port, ADS_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(ADS_RESET_GPIO_Port, ADS_RESET_Pin, GPIO_PIN_SET);
}

void ADS_PowerDown(void) {
	HAL_GPIO_WritePin(ADS_PWDN_GPIO_Port, ADS_PWDN_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(ADS_PWDN_GPIO_Port, ADS_PWDN_Pin, GPIO_PIN_SET);
}

void ADS_Start(int PinState) {
	if (PinState == HIGH) HAL_GPIO_WritePin(ADS_START_GPIO_Port, ADS_START_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(ADS_START_GPIO_Port, ADS_START_Pin, GPIO_PIN_RESET);
}

void ADS_ChipSelect(int PinState) {
	if (PinState == LOW) HAL_GPIO_WritePin(ADS_CS_GPIO_Port, ADS_CS_Pin, GPIO_PIN_RESET);
	else HAL_GPIO_WritePin(ADS_CS_GPIO_Port, ADS_CS_Pin, GPIO_PIN_SET);
}
/*********************************************************************/





/******************** ADS1298 Initialization ********************/
void ADS_Init(void) {
	ADS_ExtClk();
	ADS_ClkSel(LOW);
	ADS_Reset();
	ADS_PowerDown();
	
	HAL_Delay(1000);	// Wait until VCAP1 ge 1.1V
	
	ADS_Reset();	// Issue reset pulse
	
	ADS_ChipSelect(LOW);
	
	ADS_Send_Data_Stop_Cont();
	ADS_Send_Reg_Wr();
}
/****************************************************************/





/******************** ADS1298 Recordings ********************/
void ADS_Data_Receive(void) {
	ADS_Start(HIGH);
	ADS_Send_Data_Rd_Cont();
	HAL_Delay(3000);
	ADS_READY = 1;
}
/************************************************************/