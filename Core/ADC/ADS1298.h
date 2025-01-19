#ifndef _ADS1298_H_
#define _ADS1298_H_

/******************** Private Macro ********************/
/*** ADS1298 Pin State ***/
#define HIGH 1
#define LOW 0

/*** ADS1298 Opcocde Table ***/
#define CMD_WAKEUP 0x02
#define CMD_STANDBY 0x04
#define CMD_RESET 0x06
#define CMD_START 0x08
#define CMD_STOP 0x0A

#define CMD_RDATAC 0x10
#define CMD_SDATAC 0x11
#define CMD_RDATA 0x12

#define CMD_WREG_RegAddr 0x40
#define CMD_WREG_RegNum 0x19
#define CMD_RREG_RegAddr 0x20
#define CMD_RREG_RegNum 0x19





/*** ADS1298 Register Table ***/
#define ID 0xD2	// 0b110 10 010

#define CONFIG1 0x85	// 0b1 0 0 00 101
//#define CONFIG2 0x00	// 0b00 0 0 0 0 00
#define CONFIG2 0x10
#define CONFIG3 0xFC	// 0b1 1 1 1 1 1 0 0
#define LOFF 0x03	// 0b000 0 00 11

//#define CH1SET 0x00	// 0b0 000 0 000
//#define CH2SET 0x00	// 0b0 000 0 000
//#define CH3SET 0x00	// 0b0 000 0 000
//#define CH4SET 0x00	// 0b0 000 0 000
//#define CH5SET 0x00	// 0b0 000 0 000
//#define CH6SET 0x00	// 0b0 000 0 000
//#define CH7SET 0x00	// 0b0 000 0 000
//#define CH8SET 0x00	// 0b0 000 0 000
#define CH1SET 0x05
#define CH2SET 0x05
#define CH3SET 0x05
#define CH4SET 0x05
#define CH5SET 0x05
#define CH6SET 0x05
#define CH7SET 0x05
#define CH8SET 0x05
#define RLD_SENSP 0x00	// 0b0 0 0 0 0 0 0 0
#define RLD_SENSN 0x00	// 0b0 0 0 0 0 0 0 0
#define LOFF_SENSP 0xFF	// 0b1 1 1 1 1 1 1 1
#define LOFF_SENSN 0x02	// 0b0 0 0 0 0 0 0 1
#define LOFF_FLIP 0x00	// 0b0 0 0 0 0 0 0 0

#define LOFF_STATP 0x00	// 0b0 0 0 0 0 0 0 0
#define LOFF_STATN 0x00	// 0b0 0 0 0 0 0 0 0

#define GPIO 0x00	// 0b0000 0000
#define PACE 0x00	// 0b0 0 0 00 00 0
#define RESP 0xF0	// 0b1 1 1 100 00
#define CONFIG4 0x22	// 0b001 0 0 0 1 0
#define WCT1 0x0A	// 0b0 0 0 0 1 010
#define WCT2 0xE3	// 0b1 1 100 011





/******************** Private Function ********************/
void ADS_Init(void);
void ADS_Data_Receive(void);



/*** ADS1298 Opcode Command ***/
/* System Command */
void ADS_Send_WakeUp(void);
void ADS_Send_Standby(void);
void ADS_Send_Reset(void);
void ADS_Send_Start(void);
void ADS_Send_Stop(void);

/* Data Read Command */
void ADS_Send_Data_Rd_Cont(void);
void ADS_Send_Data_Stop_Cont(void);
void ADS_Send_Data_Rd_Single(void);

/* Register Read Command */
void ADS_Send_Reg_Rd(void);
void ADS_Send_Reg_Wr(void);



/*** ADS1298 Pin Settings ***/
void ADS_ClkSel(int);
void ADS_ExtClk(void);
void ADS_Reset(void);
void ADS_PowerDown(void);
void ADS_Start(int);
void ADS_ChipSelect(int);



#endif