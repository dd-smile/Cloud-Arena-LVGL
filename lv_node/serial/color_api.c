/*
 * @Description:
 * @Author: mai
 * @LastEditors: mai
 * @Date: 2023-05-26 17:16:06
 * @LastEditTime: 2023-07-07 16:08:33
 * @FilePath: /lingxiantiyu_compile/lv_node/serial/color_api.c
 */

#include "ui_app.h"


uint16_t calculate_crc16(uint8_t *data, size_t length)
{
    uint16_t crc = 0xFFFF;

    for (size_t i = 0; i < length; i++)
    {
        crc ^= data[i];
        for (int j = 0; j < 8; j++)
        {
            if (crc & 0x0001)
            {
                crc = (crc >> 1) ^ 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return crc;
}
void SetSerialDo(uint8_t SetSerialIndex, uint8_t status)
{
   
    unsigned char packet[10];

    packet[0] = 0xFE;
    packet[1] = 0x0F;
    packet[2] = 0x00;
    packet[3] = SetSerialIndex;
    packet[4] = 0x00;
    packet[5] = 0x01;
    packet[6] = 0x01;
    packet[7] = status;
    packet[8] = calculate_crc16(packet, sizeof(packet) - 2) & 0xFF;
    packet[9] = calculate_crc16(packet, sizeof(packet) - 2) >> 8;

    serial_send(packet, sizeof(packet));

    // 休眠300ms
    usleep(100 * 1000);

 
}
