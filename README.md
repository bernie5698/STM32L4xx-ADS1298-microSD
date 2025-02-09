# STM32L4xx with ADS1298 to microSD

## Description
This example is based on STM32L4 series microcontroller. We capture ECG signal by ADS1298, and save it into microSD card
- STM32L4 communicate with ADS1298 & microSD via SPI protocol
- #DRDY pin of ADS1298 will trigger STM32L4's pin interrupt to notify FW that data is ready
- sampling rate of ADS1298 in the example is 1kHz
- middleware: FATFS

## Result
Retrieve data from microSD card, plot data with Matlab, use 10Hz High-Pass Filter
<img width="1071" alt="image" src="https://github.com/user-attachments/assets/701623ce-b7e9-4751-9cf5-1b25b5b277b5" />
