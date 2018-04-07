#include <displayDriver.h>
#include "stm32f0xx_hal.h"
#include "spi.h"
#include "string.h"

void displayOn(void){

	uint8_t data[2] = {0xFE, 0x41};

	HAL_SPI_Transmit (&hspi1, data, sizeof(uint8_t)*2, 1);

	delay(10); // delay 2ms

}

void displayOff(void){

	uint8_t data[2] = {0xFE, 0x42};

	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	delay(10); // delay 2ms

}

void transmitDisplay(char * string){

	HAL_SPI_Transmit (&hspi1, (uint8_t *) string, strlen(string), 1);

	delay(10); // delay 2ms

}

void displayClear(void){

	uint8_t data[2] = {0xFE, 0x51};

	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	delay(10); // delay 2ms

}

void turnOnBlinkingCursor(void){

	uint8_t data[2] = {0xFE, 0x4B};

	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	delay(10); // delay 2ms

}

void cursorLeft(void){

	uint8_t data[2] = {0xFE, 0x49};

	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	delay(10); // delay 2ms

}

void displayBrightness(int brightness){
	uint8_t data[3] = {0xFE, 0x53, (uint8_t) brightness};

	HAL_SPI_Transmit (&hspi1, data, 3, 1);

	delay(10); // delay 2ms

}

// 0 - 79 possible position. Each row has 15 coloumns
void cursorPosition(int position){

	uint8_t data[3] = {0xFE, 0x45, (uint8_t) position};

	HAL_SPI_Transmit (&hspi1, data, 3, 1);

	delay(10); // delay 2ms


}

void cursorHome(void){

	uint8_t data[2] = {0xFE, 0x46};

	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	delay(10); // delay 2ms

}

void timeoutLED(int value){
	if (value == 1){
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	}
	else{
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	}
}

void backspace(void){
	uint8_t data[2] = {0xFE, 0x4E};
	HAL_SPI_Transmit (&hspi1, data, 2, 1);
	delay(10);
}

