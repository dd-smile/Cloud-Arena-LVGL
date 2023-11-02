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
// DO控制
void SetSerialDo(uint8_t addr, uint8_t SetSerialIndex, uint8_t status)
{
    unsigned char packet[8];

    packet[0] = addr;
    packet[1] = 0x05;
    packet[2] = 0x00;
    packet[3] = SetSerialIndex;
    if(status == 1)
        packet[4] = 0xFF;
    else
        packet[4] = 0;
    packet[5] = 0x00;
    packet[6] = calculate_crc16(packet, sizeof(packet) - 2) & 0xFF;
    packet[7] = calculate_crc16(packet, sizeof(packet) - 2) >> 8;

    serial_send(packet, sizeof(packet));


    usleep(100 * 1000);

 
}

// 关闭DO
void SetAllDoClose(uint8_t addr)
{
    unsigned char packet[10];

    packet[0] = addr;
    packet[1] = 0x0F;
    packet[2] = 0x00;
    packet[3] = 0x00;
    packet[4] = 0x00;
    packet[5] = 0x06;
    packet[6] = 0x01;
    packet[7] = 0x00;    
    packet[8] = calculate_crc16(packet, sizeof(packet) - 2) & 0xFF;
    packet[9] = calculate_crc16(packet, sizeof(packet) - 2) >> 8;

    serial_send(packet, sizeof(packet));
    
    if(addr == 0xFE || addr == 0x03)
    {
        for (size_t i = 0; i < 2; i++)
        {   
            usleep(100 * 1000); // 休眠100ms
            SetSerialDo(3, i, 0);      
        }
    }
    
}

static uint32_t modbus_build_request(int8_t *buffer, uint8_t slave_addr, uint8_t func_code, uint16_t reg_addr, int16_t reg_val)
{
    buffer[0] = slave_addr;      // Slave address
    buffer[1] = func_code;       // Function code
    buffer[2] = reg_addr >> 8;   // High byte of register address
    buffer[3] = reg_addr & 0xFF; // Low byte of register address
    buffer[4] = reg_val >> 8;    // High byte of register value
    buffer[5] = reg_val & 0xFF;  // Low byte of register value

    uint16_t crc = calculate_crc16(buffer, 6); // Calculate CRC-16 checksum
    buffer[6] = crc & 0xFF;                 // Low byte of CRC checksum
    buffer[7] = crc >> 8;                   // High byte of CRC checksum

    return 8; // Return length of request packet
}

void send_modbus(uint8_t slave_addr, uint8_t func_code, uint16_t reg_addr, int16_t reg_val)
{
    int8_t tx_buffer[8];
    uint32_t tx_len = modbus_build_request(tx_buffer, slave_addr, func_code, reg_addr, reg_val); 
    serial_send(tx_buffer, sizeof(tx_buffer));
    usleep(50 * 1000);
} 