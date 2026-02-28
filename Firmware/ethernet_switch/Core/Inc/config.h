//
// Created by ember on 2/26/26.
//

//made with help of ai as prototype, will be mostly rewritten when i get switch physically and can try the code

#ifndef ETHERNET_SWITCH_CONFIG_H
#define ETHERNET_SWITCH_CONFIG_H

#include <stdint.h>

#define CONFIG_MAGIC_WORD 0xDEADBEEF
typedef struct {
    uint16_t vid;          // Numer VLAN (1-4095)
    uint8_t port_mask;     // Maska portów (np. 0x07 dla portów 1,2,3)
    uint8_t is_active;     // Flaga: 1 = istnieje, 0 = usunięty
} VlanEntry_t;

typedef struct {
    uint32_t magic_word;
    char mqtt_broker_ip[16];
	uint8_t port_enabled[8];
	VlanEntry_t vlans[15];
	uint8_t reserved[16];

} DeviceConfig_t;

extern DeviceConfig_t CurrentConfig;

void Config_Init(void);
void Config_SaveToFlash(void);

#endif //ETHERNET_SWITCH_CONFIG_H