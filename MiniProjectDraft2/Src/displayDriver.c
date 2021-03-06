#include <displayDriver.h>
#include "stm32f0xx_hal.h"
#include "spi.h"
#include "string.h"
#include "tim.h"

void displayOn(void){

	uint8_t data[2] = {0xFE, 0x41};

	HAL_SPI_Transmit (&hspi1, data, sizeof(uint8_t)*2, 1);

	// delay 5ms
	delay_ms(5);

}

void displayOff(void){

	uint8_t data[2] = {0xFE, 0x42};

	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	// delay 5ms
	delay_ms(5);

}

void transmitDisplay(char * string){

	for(int x = 0; x < strlen(string); x++){
		HAL_SPI_Transmit (&hspi1, (uint8_t *) &string[x], 1, 1);

		// delay 2ms
		delay_ms(5);
	}
}

void displayClear(void){

	uint8_t data[2] = {0xFE, 0x51};

	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	// delay 5ms
	delay_ms(5);
}

void turnOnBlinkingCursor(void){

	uint8_t data[2] = {0xFE, 0x4B};

	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	// delay 5ms
	delay_ms(5);

}

void cursorLeft(void){

	uint8_t data[2] = {0xFE, 0x49};

	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	// delay 5ms
	delay_ms(5);

}

void displayBrightness(int brightness){
	uint8_t data[3] = {0xFE, 0x53, (uint8_t) brightness};

	HAL_SPI_Transmit (&hspi1, data, 3, 1);

	// delay 5ms
	delay_ms(5);

}

void cursorPosition(int position){

	uint8_t data[3] = {0xFE, 0x45, (uint8_t) position};

	HAL_SPI_Transmit (&hspi1, data, 3, 1);

	// delay 5ms
	delay_ms(5);


}

void cursorHome(void){

	uint8_t data[2] = {0xFE, 0x46};

	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	// delay 5ms
	delay_ms(5);

}

void backspace(void){

	uint8_t data[2] = {0xFE, 0x4E};
	HAL_SPI_Transmit (&hspi1, data, 2, 1);

	// delay 5ms
	delay_ms(5);
}

