/*
 * 24AA01.c
 *
 *  Created on: Sep 17, 2024
 *      Author: msucharski
 */

#include "24AA01.h"

#define EEPROM_WRITE_ADDR 0xA0
#define EEPROM_READ_ADDR  0xA1
#define EEPROM_MEMORY_MAX_SIZE 128
#define EEPROM_DEFAULT_TIMEOUT 1000

HAL_StatusTypeDef WriteDataToEEPROM(I2C_HandleTypeDef *hi2c, uint16_t MemAddress, uint8_t *buffer, uint8_t size)
{
	if(size > EEPROM_MEMORY_MAX_SIZE) {
		return HAL_ERROR;
	}

	HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(hi2c, EEPROM_WRITE_ADDR, 0x0, HAL_MAX_DELAY);
	if(status != HAL_OK)
		return status;

	int tick = HAL_GetTick();

	for(;;)
	{
		if(HAL_I2C_Mem_Write(hi2c, EEPROM_WRITE_ADDR, MemAddress, sizeof(uint8_t), buffer, 1, HAL_MAX_DELAY) == HAL_OK)
		{
			size -= 1;
			buffer += 1;
			MemAddress += 1;
			HAL_Delay(6);
		}

		if(size <= 0) {
			break;
		}

		if(HAL_GetTick() - tick > EEPROM_DEFAULT_TIMEOUT) {
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}

HAL_StatusTypeDef ReadDataFromEEPROM(I2C_HandleTypeDef *hi2c, uint16_t MemAddress, uint8_t *buffer, const uint8_t size)
{
	HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(hi2c, EEPROM_READ_ADDR, 0x0, HAL_MAX_DELAY);
	if(status != HAL_OK)
		return status;

	return HAL_I2C_Mem_Read(hi2c, EEPROM_READ_ADDR, MemAddress, sizeof(uint8_t), buffer, size, HAL_MAX_DELAY);
}
