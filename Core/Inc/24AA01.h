/*
 * 24AA01.h
 *
 *  Created on: Sep 17, 2024
 *      Author: msucharski
 */

#ifndef INC_24AA01_H_
#define INC_24AA01_H_

#include "stm32l4xx.h"
#include <stdint.h>

HAL_StatusTypeDef WriteDataToEEPROM(I2C_HandleTypeDef *hi2c, uint16_t MemAddress, uint8_t *buffer, const uint8_t size);
HAL_StatusTypeDef ReadDataFromEEPROM(I2C_HandleTypeDef *hi2c, uint16_t MemAddress, uint8_t *buffer, const uint8_t size);

#endif /* INC_24AA01_H_ */
