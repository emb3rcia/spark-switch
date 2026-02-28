//
// Created by ember on 2/26/26.
//

#include "config.h"
#include "main.h" // dla bibliotek HAL
#include <string.h>

//made with help of ai as prototype, will be mostly rewritten when i get switch physically and can try the code

#define CONFIG_FLASH_ADDRESS ((uint32_t)0x080E0000)

DeviceConfig_t CurrentConfig;

void Config_Init(void) {
    DeviceConfig_t *flash_cfg = (DeviceConfig_t *)CONFIG_FLASH_ADDRESS;

    if (flash_cfg->magic_word == CONFIG_MAGIC_WORD) {
        memcpy(&CurrentConfig, flash_cfg, sizeof(DeviceConfig_t));
    } else {
        CurrentConfig.magic_word = CONFIG_MAGIC_WORD;
        strcpy(CurrentConfig.mqtt_broker_ip, "192.168.0.10");
        memset(CurrentConfig.vlan_table, 0, sizeof(CurrentConfig.vlan_table));

    }
}

void Config_SaveToFlash(void) {
    __disable_irq();

    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef EraseInitStruct;
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector = FLASH_SECTOR_11; // Należy dobrać odpowiedni sektor
    EraseInitStruct.NbSectors = 1;

    uint32_t SectorError = 0;
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) == HAL_OK) {
        uint32_t *ram_ptr = (uint32_t *)&CurrentConfig;
        uint32_t flash_ptr = CONFIG_FLASH_ADDRESS;
        uint32_t words_to_write = sizeof(DeviceConfig_t) / 4;

        if (sizeof(DeviceConfig_t) % 4 != 0) words_to_write++;

        for (uint32_t i = 0; i < words_to_write; i++) {
            HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flash_ptr, ram_ptr[i]);
            flash_ptr += 4;
        }
    }

    HAL_FLASH_Lock();

    __enable_irq();
}

