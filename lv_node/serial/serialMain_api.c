/**
 * Here is a demo DEMO
 * The use of several API interfaces is demonstrated here
 * So the data sending and receiving is to initialize and call the API.
 */

#include "color_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "ui_app.h"

serial_handler_t *serial_handler;
void serial_init(serial_handler_t **ydt_handler)
{
    if (serial_hander_init(ydt_handler, 1, 9600, 8, 0, 1) != SERIAL_SUCCESS) // 使用通道一485口
    {
        printf("serial_init error!\r\n");
    }
}

void serial_uinit(serial_handler_t *serial_handler)
{
    serial_hander_uninit(serial_handler);
}
void serial_send(const unsigned char *data, int length)
{
    serial_status_t status = SERIAL_SUCCESS;
    memcpy((unsigned char *)serial_handler->serial_frame_buff, data, length);
    serial_handler->serial_frame_length = length;
    serial_handler->frame_send(serial_handler); // 发送数据
    
    
}

void *serial_recv()
{
    static uint8_t prevValue = 0; // 上一次的值
    serial_status_t status = SERIAL_SUCCESS;
    serial_handler->frame_recv(serial_handler);

    for(int i = 0; i < 10; i++)
    {
        printf( " %02X", serial_handler->serial_frame_buff[i]);
    }
    printf("\n");

    // 收到第一个继电器信息
    if (serial_handler->serial_frame_buff[0] == 0x01 && serial_handler->serial_frame_buff[1] == 0x02)
    {
        uint8_t currentValue = serial_handler->serial_frame_buff[3];

        if (currentValue != prevValue )
        {
            
            switch (currentValue)
            {
            case 0x01: // 看台展开电机限位信号
                printf("DI1输入\r\n");
                if (Swich_status == 0) // 一键开按钮
                {
                    if (ReadSerialDiNum == 1)
                    {
                        SetAllDoClose(0xFE); // 广播地址全关
                        usleep(100 * 1000);
                        SetSerialDo(1, 2, 1); // 打开D03
                        
                        ReadSerialDiNum = 3;
                        stand_flag = false;
                    }
                    
                }
                else // 只开看台按钮
                {
                    SetSerialDo(1, 0, 0); // 关闭DO1
                    stand_flag = false;
                }
                break;

            case 0x02: // 看台收拢电机限位信号
                printf("DI2输入\r\n");
                if (ReadSerialDiNum == 2)
                {
                    SetSerialDo(1, 1, 0); // 关闭DO2
                    stand_flag = true;
                }
                break;

            case 0x04: // 座椅展开电机限位信号
                printf("DI3输入\r\n");           
                if (ReadSerialDiNum == 3)
                {
                    SetSerialDo(1, 2, 0); // 关闭D03
                    chair_flag = false;
                }
                break;

            case 0x08: // 座椅收起电机限位信号
                printf("DI4输入\r\n");
                if (Swich_status == 2)
                {
                    if (ReadSerialDiNum == 4)
                    {
                        SetAllDoClose(0xFE); // 广播地址全关
                        usleep(100 * 1000);
                        SetSerialDo(1, 1, 1); // 打开D02
                        ReadSerialDiNum = 2;
                        chair_flag = true;
                    }
                }
                else
                {
                    SetSerialDo(1, 3, 0); // 关闭DO4
                    chair_flag = true;

                }
                break;

            case 0x10: // 球架1打开电机限位信号
                
                printf("DI5输入\r\n");
                if (ReadSerialDiNum == 5)
                {
                    SetSerialDo(1, 4, 0); // 关闭DO5
                    basketball_flag[0] = false;
                   
                }
                break;
            case 0x20: // 球架1收起电机限位信号

                printf("DI6输入\r\n");
                if (ReadSerialDiNum == 6)
                {
                    SetSerialDo(1, 5, 0); // 关闭DO6
                    basketball_flag[0] = true;
                   
                }
                break;
            }
            prevValue = currentValue; // 更新上一次的值
        }
    }
    // 收到第二个继电器信息
    else if (serial_handler->serial_frame_buff[0] == 0x02 && serial_handler->serial_frame_buff[1] == 0x02)
    {
        uint8_t currentValue = serial_handler->serial_frame_buff[3];

        if (currentValue != prevValue )
        {
            switch (currentValue)
            {
            case 0x01: // 球架2打开电机限位信号
                
                printf("DI1输入\r\n");
                if (ReadSerialDiNum == 7)
                {
                    SetSerialDo(2, 0, 0); // 关闭DO1
                    basketball_flag[1] = false;
                   
                }
                break;
            case 0x02: // 球架2收起电机限位信号

                printf("DI2输入\r\n");
                if (ReadSerialDiNum == 8)
                {
                    SetSerialDo(2, 1, 0); // 关闭DO2
                    basketball_flag[1] = true;
                   
                }
                break;
            case 0x04: // 球架3打开电机限位信号
                
                printf("DI3输入\r\n");
                if (ReadSerialDiNum == 9)
                {
                    SetSerialDo(2, 2, 0); // 关闭DO3
                    basketball_flag[2] = false;
                   
                }
                break;
            case 0x08: // 球架3收起电机限位信号

                printf("DI4输入\r\n");
                if (ReadSerialDiNum == 10)
                {
                    SetSerialDo(2, 3, 0); // 关闭DO4
                    basketball_flag[2] = true;
                   
                }
                break;
            case 0x10: // 球架4打开电机限位信号
                
                printf("DI5输入\r\n");
                if (ReadSerialDiNum == 11)
                {
                    SetSerialDo(2, 4, 0); // 关闭DO5
                    basketball_flag[3] = false;
                   
                }
                break;
            case 0x20: // 球架4收起电机限位信号

                printf("DI6输入\r\n");
                if (ReadSerialDiNum == 12)
                {
                    SetSerialDo(2, 5, 0); // 关闭DO6
                    basketball_flag[3] = true;
                   
                }
                break;

            }
            prevValue = currentValue; // 更新上一次的值
        }
    }
    else if (serial_handler->serial_frame_buff[0] == 0x03 && serial_handler->serial_frame_buff[1] == 0x02)
    {
        uint8_t currentValue = serial_handler->serial_frame_buff[3];

        if (currentValue != prevValue )
        {
            switch (currentValue)
            {
            case 0x01: // 分隔幕打开电机限位信号
                
                printf("DI1输入\r\n");
                if (ReadSerialDiNum == 13)
                {
                    SetSerialDo(3, 0, 0); // 关闭DO1
                    patition_flag = false;
                }
                break;
            case 0x02: // 分隔幕收起电机限位信号

                printf("DI2输入\r\n");
                if (ReadSerialDiNum == 14)
                {
                    SetSerialDo(3, 1, 0); // 关闭DO2
                    patition_flag = true;
                   
                }
                break;
            }
            prevValue = currentValue; // 更新上一次的值
        }


    }
}

void ReadSerialDi(void *args)
{
 
    unsigned char send_data[] =  {0x01, 0x02, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00}; // 检测第一个继电器DI
    unsigned char send_data2[] = {0x02, 0x02, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00}; // 第二个
    unsigned char send_data3[] = {0x03, 0x02, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00}; // 第三个
    size_t send_data_length = sizeof(send_data) / sizeof(send_data[0]);

    send_data[6] = calculate_crc16(send_data, sizeof(send_data) - 2) & 0xFF;   // 计算校验码
    send_data[7] = calculate_crc16(send_data, sizeof(send_data) - 2) >> 8;

    send_data2[6] = calculate_crc16(send_data2, sizeof(send_data2) - 2) & 0xFF; // 计算校验码
    send_data2[7] = calculate_crc16(send_data2, sizeof(send_data2) - 2) >> 8;

    send_data3[6] = calculate_crc16(send_data3, sizeof(send_data3) - 2) & 0xFF; // 计算校验码
    send_data3[7] = calculate_crc16(send_data3, sizeof(send_data3) - 2) >> 8;

    serial_init(&serial_handler);
    while (1)
    {
        printf("ReadSerialDiNum %d\n", ReadSerialDiNum);
        // 选择需要检测的继电器
        if(ReadSerialDiNum <= 6)
        {
            serial_send(send_data, send_data_length); // 发送数据
            serial_recv();
            usleep(100 * 1000);
        }
            
        else if(ReadSerialDiNum > 6 && ReadSerialDiNum <= 12)
        {
            serial_send(send_data2, send_data_length);
            serial_recv();
            usleep(100 * 1000);
        }
        
        else if(ReadSerialDiNum > 12 && ReadSerialDiNum <= 16)
        {
            serial_send(send_data3, send_data_length);
            serial_recv();
            usleep(100 * 1000);
        }        
        
    }
    serial_uinit(serial_handler);
}
