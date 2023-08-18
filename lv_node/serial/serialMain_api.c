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
    if (serial_handler->serial_frame_buff[0] == 0xfe && serial_handler->serial_frame_buff[1] == 0x02)
    {
        uint8_t currentValue = serial_handler->serial_frame_buff[3];

        if (currentValue != prevValue)
        {

            switch (currentValue)
            {
            case 0x01:

                if (Swich_status == 0)
                {
                    if (ReadSerialDiNum == 1)
                    {

                        for (size_t i = 0; i < 4; i++)
                        {
                            SetSerialDo(i, 0);
                        }
                        SetSerialDo(2, 1); // 打开D03
                        ReadSerialDiNum = 3;
                    }

                    printf("DI1输入\r\n");
                }
                else
                {
                    SetSerialDo(0, 0); // 打开D03
                }

                break;

            case 0x02:

                if (Swich_status == 1)
                {
                    if (ReadSerialDiNum == 2)
                    {
                        for (size_t i = 0; i < 4; i++)
                        {
                            SetSerialDo(i, 0);
                        }
                        printf("DI2输入\r\n");
                    }
                }
                else
                {
                    SetSerialDo(1, 0); // 打开D03
                }

                break;

            case 0x04:
                if (Swich_status == 0)
                {
                    if (ReadSerialDiNum == 3)
                    {
                        for (size_t i = 0; i < 4; i++)
                        {
                            SetSerialDo(i, 0);
                        }
                        printf("DI3输入\r\n");
                    }
                }
                else
                {
                    SetSerialDo(2, 0); // 打开D03
                }

                break;

            case 0x08:

                printf("DI4输入\r\n");
                if (Swich_status == 1)
                {
                    for (size_t i = 0; i < 4; i++)
                    {
                        SetSerialDo(i, 0);
                    }
                    SetSerialDo(1, 1); // 打开D02
                    ReadSerialDiNum = 2;
                }
                else
                {
                    SetSerialDo(3, 0); // 打开D03
                }
                break;
            }

            prevValue = currentValue; // 更新上一次的值
        }
    }
}

void ReadSerialDi(void *args)
{

    unsigned char send_data[] = {0xFE, 0x02, 0x00, 0x00, 0x00, 0x04, 0x6D, 0xC6};
    size_t send_data_length = sizeof(send_data) / sizeof(send_data[0]);

    while (1)
    {
        serial_init(&serial_handler);
        serial_send(send_data, send_data_length); // 发送数据

        serial_recv();

        usleep(200 * 1000);
        serial_uinit(serial_handler);
    }
}
