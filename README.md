# STM32L4xx with ADS1298 to microSD

## Description
This example is based on STM32L4 series microcontroller. We capture ECG signal by ADS1298, and save it into microSD card
- STM32L4 communicate with ADS1298 & microSD via SPI protocol
- #DRDY pin of ADS1298 will trigger STM32L4's pin interrupt to notify FW that data is ready
- sampling rate of ADS1298 in the example is 1kHz
- middleware: FATFS


## ADS1298, OP Code
```c
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
```

## ADS1298, Register

```c
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
```


## Result
Retrieve data from microSD card, plot data with Matlab, use 10Hz High-Pass Filter
<img width="1071" alt="image" src="https://github.com/user-attachments/assets/701623ce-b7e9-4751-9cf5-1b25b5b277b5" />
