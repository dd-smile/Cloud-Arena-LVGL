


#ifndef _COLOR_API_H_
#define _COLOR_API_H_

#include "ui_app.h"


uint16_t calculate_crc16(uint8_t *data, size_t length);
void SetSerialDo(uint8_t addr, uint8_t SetSerialIndex, uint8_t status);
void SetAllDoClose(uint8_t addr);

#endif