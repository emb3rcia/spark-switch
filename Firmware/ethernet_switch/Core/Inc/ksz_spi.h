#ifndef KSZSPI_H
#define KSZSPI_H

#include "main.h"

//made with help of ai as prototype, will be mostly rewritten when i get switch physically and can try the code

void KSZ_SPI_Init(void);

void KSZ_WriteReg8(uint16_t address, uint8_t data);
uint8_t KSZ_ReadReg8(uint16_t address);

void KSZ_WriteReg16(uint16_t address, uint16_t data);
uint16_t KSZ_ReadReg16(uint16_t address);

void KSZ_WriteReg32(uint16_t address, uint32_t data);
uint32_t KSZ_ReadReg32(uint16_t address);

void KSZ_SetVLAN(uint16_t vid, uint8_t port_mask, uint8_t valid);

#endif /* KSZSPI_H */