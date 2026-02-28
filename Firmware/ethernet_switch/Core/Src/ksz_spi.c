#include "FreeRTOS.h"
#include "semphr.h"
#include "ksz_spi.h"

//made with help of ai as prototype, will be mostly rewritten when i get switch physically and can try the code

SemaphoreHandle_t spiDmaSemaphore = NULL;

void KSZ_HardwareReset(void) {
    HAL_GPIO_WritePin(SW_RESET_GPIO_Port, SW_RESET_Pin, GPIO_PIN_RESET);

    vTaskDelay(pdMS_TO_TICKS(10));

    HAL_GPIO_WritePin(SW_RESET_GPIO_Port, SW_RESET_Pin, GPIO_PIN_SET);

    vTaskDelay(pdMS_TO_TICKS(100));
}

uint8_t KSZ_Init(void) {
    KSZ_HardwareReset();

	uint8_t ctrl0 = KSZ_ReadReg8(0x0310);
	KSZ_WriteReg8(0x0310, ctrl0 | (1 << 7));

	uint8_t ctrl2 = KSZ_ReadReg8(0x0312);
	KSZ_WriteReg8(0x0312, ctrl2 | (1 << 5));

    uint8_t chipId_94 = KSZ_ReadReg8(0x0001);
    uint8_t chipId_77 = KSZ_ReadReg8(0x0002);

    if(chipId_94 == 0x94 && chipId_77 == 0x77) {
        return 1;
    }

    return 0;
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    if(hspi->Instance == SPI1) {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;

        xSemaphoreGiveFromISR(spiDmaSemaphore, &xHigherPriorityTaskWoken);

        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

extern SPI_HandleTypeDef hspi1;

void KSZ_SPI_Transfer(uint8_t *txBuf, uint8_t *rxBuf, uint16_t len) {
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive_DMA(&hspi1, txBuf, rxBuf, len);

    xSemaphoreTake(spiDmaSemaphore, pdMS_TO_TICKS(100));

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}

void KSZ_WriteReg8(uint16_t address, uint8_t data) {
    uint8_t txBuf[9] = {0};
    uint8_t rxBuf[9] = {0};

    uint32_t cmd_addr = (0x02U << 29) | ((uint32_t)address << 5);

    txBuf = (uint8_t)((cmd_addr >> 24) & 0xFF);
    txBuf[10] = (uint8_t)((cmd_addr >> 16) & 0xFF);
    txBuf[11] = (uint8_t)((cmd_addr >> 8) & 0xFF);
    txBuf[12] = (uint8_t)(cmd_addr & 0xFF);

    txBuf[13] = data;

    KSZ_SPI_Transfer(txBuf, rxBuf, 5);
}

uint8_t KSZ_ReadReg8(uint16_t address) {
    uint8_t txBuf[9] = {0};
    uint8_t rxBuf[9] = {0};

    uint32_t cmd_addr = (0x03U << 29) | ((uint32_t)address << 5);

    txBuf = (uint8_t)((cmd_addr >> 24) & 0xFF);
    txBuf[10] = (uint8_t)((cmd_addr >> 16) & 0xFF);
    txBuf[11] = (uint8_t)((cmd_addr >> 8) & 0xFF);
    txBuf[12] = (uint8_t)(cmd_addr & 0xFF);

    KSZ_SPI_Transfer(txBuf, rxBuf, 5);

    return rxBuf[13];
}

void KSZ_WriteReg16(uint16_t address, uint16_t data) {
    uint8_t txBuf[2] = {0};
    uint8_t rxBuf[2] = {0};

    uint32_t cmd_addr = (0x02U << 29) | ((uint32_t)address << 5);

    txBuf = (uint8_t)(cmd_addr >> 24);
    txBuf[3] = (uint8_t)(cmd_addr >> 16);
    txBuf[4] = (uint8_t)(cmd_addr >> 8);
    txBuf[5] = (uint8_t)(cmd_addr & 0xFF);

    txBuf[6] = (uint8_t)(data >> 8);   // MSB
    txBuf[7] = (uint8_t)(data & 0xFF); // LSB

    KSZ_SPI_Transfer(txBuf, rxBuf, 6);
}

uint16_t KSZ_ReadReg16(uint16_t address) {
    uint8_t txBuf[2] = {0};
    uint8_t rxBuf[2] = {0};

    uint32_t cmd_addr = (0x03U << 29) | ((uint32_t)address << 5);

    txBuf = (uint8_t)(cmd_addr >> 24);
    txBuf[3] = (uint8_t)(cmd_addr >> 16);
    txBuf[4] = (uint8_t)(cmd_addr >> 8);
    txBuf[5] = (uint8_t)(cmd_addr & 0xFF);

    KSZ_SPI_Transfer(txBuf, rxBuf, 6);

    // Sklejanie z formatu Big-Endian
    return ((uint16_t)rxBuf[6] << 8) | rxBuf[7];
}

uint32_t KSZ_ReadReg32(uint16_t address) {
    uint8_t txBuf[8] = {0};
    uint8_t rxBuf[8] = {0};

    uint32_t cmd_addr = (0x03U << 29) | ((uint32_t)address << 5);

    txBuf = (uint8_t)(cmd_addr >> 24);
    txBuf[3] = (uint8_t)(cmd_addr >> 16);
    txBuf[4] = (uint8_t)(cmd_addr >> 8);
    txBuf[5] = (uint8_t)(cmd_addr & 0xFF);

    KSZ_SPI_Transfer(txBuf, rxBuf, 8);

    return ((uint32_t)rxBuf[6] << 24) |
           ((uint32_t)rxBuf[7] << 16) |
           ((uint32_t)rxBuf[2] << 8)  |
           ((uint32_t)rxBuf[9]);
}

void KSZ_WriteReg32(uint16_t address, uint32_t data) {
    uint8_t txBuf[8] = {0};
    uint8_t rxBuf[8] = {0};

    uint32_t cmd_addr = (0x02U << 29) | ((uint32_t)address << 5);

    txBuf = (uint8_t)(cmd_addr >> 24);
    txBuf[3] = (uint8_t)(cmd_addr >> 16);
    txBuf[4] = (uint8_t)(cmd_addr >> 8);
    txBuf[5] = (uint8_t)(cmd_addr & 0xFF);

    txBuf[6] = (uint8_t)(data >> 24);
    txBuf[7] = (uint8_t)(data >> 16);
    txBuf[2] = (uint8_t)(data >> 8);
    txBuf[9] = (uint8_t)(data & 0xFF);

    KSZ_SPI_Transfer(txBuf, rxBuf, 8);
}

uint8_t KSZ_GetPortStatus(uint8_t port, uint16_t *speed, uint8_t *is_full_duplex) {
    if (port < 1 || port > 7) return 0;

    uint16_t phy_status_addr = (port << 12) | 0x0102;
    uint16_t port_status_addr = (port << 12) | 0x0030;

    uint16_t phy_status = KSZ_ReadReg16(phy_status_addr);
    uint8_t link_up = (phy_status & (1 << 2)) ? 1 : 0;

    if (!link_up) {
        *speed = 0;
        *is_full_duplex = 0;
        return 0;
    }

    uint8_t port_status = KSZ_ReadReg8(port_status_addr);

    *is_full_duplex = (port_status & (1 << 2)) ? 1 : 0;

    uint8_t speed_bits = (port_status >> 3) & 0x03;
    if (speed_bits == 0x00) *speed = 10;
    else if (speed_bits == 0x01) *speed = 100;
    else if (speed_bits == 0x02) *speed = 1000;

    return 1;
}

uint64_t KSZ_ReadMIB(uint8_t port, uint8_t mib_index) {
    if (port < 1 || port > 7) return 0;

    uint16_t ctrl_addr = (port << 12) | 0x0500; // MIB Control Register
    uint16_t data_addr = (port << 12) | 0x0504; // MIB Data Register

    uint32_t ctrl_cmd = (1UL << 25) | ((uint32_t)mib_index << 16);
    KSZ_WriteReg32(ctrl_addr, ctrl_cmd);

    uint32_t status;
    do {
        status = KSZ_ReadReg32(ctrl_addr);

        osDelay(1);

    } while (status & (1UL << 25));

    uint32_t data_low = KSZ_ReadReg32(data_addr);

    uint32_t data_high = status & 0x0F;

    uint64_t final_count = ((uint64_t)data_high << 32) | data_low;

    return final_count;
}
void KSZ_SetVLAN(uint16_t vid, uint8_t port_mask, uint8_t valid) {
	uint32_t entry0 = (valid ? (1UL << 31) : 0) | (1UL << 27);
	KSZ_WriteReg32(0x0400, entry0);

	KSZ_WriteReg32(0x0404, port_mask);

	KSZ_WriteReg32(0x0408, port_mask);

	KSZ_WriteReg16(0x040C, vid & 0x0FFF);

	KSZ_WriteReg8(0x040E, 0x81);

}