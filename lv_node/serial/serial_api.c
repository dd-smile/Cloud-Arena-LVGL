#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include "serial_api.h"
#include "serial_mutex.h"

static const char *uart_path[2] = {"/dev/ttyS1","/dev/ttyS2"};   // 串口路径ttys1是232口，ttyS2是485口
static int uart_fd[2];

static uint32_t GET_TICK_COUNT()
{
    struct timespec ts = {0};

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (uint32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

static int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio, oldtio;
    if (tcgetattr(fd, &oldtio) != 0)
    {
        perror("SetupSerial 1");
        return -1;
    }
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch (nBits)
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch (nEvent)
    {
    case 'O':
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        break;
    }

    switch (nSpeed)
    {
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 38400:
        cfsetispeed(&newtio, B38400);
        cfsetospeed(&newtio, B38400);
        break;
    case 57600:
        cfsetispeed(&newtio, B57600);
        cfsetospeed(&newtio, B57600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    case 460800:
        cfsetispeed(&newtio, B460800);
        cfsetospeed(&newtio, B460800);
        break;
    default:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }
    if (nStop == 1)
        newtio.c_cflag &= ~CSTOPB;
    else if (nStop == 2)
        newtio.c_cflag |= CSTOPB;
    newtio.c_cc[VTIME] = 100; ///* 设置超时10 seconds*/
    newtio.c_cc[VMIN] = 0;
    tcflush(fd, TCIFLUSH);
    if ((tcsetattr(fd, TCSANOW, &newtio)) != 0)
    {
        perror("com set error");
        return -1;
    }

    //	printf("set done!\n\r");
    return 0;
}

serial_status_t serial_open(serial_handler_t *handler, uint8_t port, uint32_t baud_rate, uint8_t data_width, serial_parity_t parity, uint8_t nstop)
{
    port = port % 2;
    uart_fd[port] = open(uart_path[port], O_RDWR | O_NONBLOCK);
    if (uart_fd[port] < 0)
    {
        return SERIAL_INIT_ERROR;
    }
    char p = 'N';
    switch (parity)
    {
    case SERIAL_PAR_NONE:
        p = 'N';
        break;
    case SERIAL_PAR_ODD:
        p = 'O';
        break;
    case SERIAL_PAR_EVEN:
        p = 'E';
        break;
    default:
        break;
    }
    set_opt(uart_fd[port], baud_rate, data_width, p, nstop);

    handler->private = &uart_fd[port];
    return SERIAL_SUCCESS;
}

serial_status_t serial_close(serial_handler_t *handler)
{
    close(*(int *)handler->private);
    return SERIAL_SUCCESS;
}

serial_status_t serial_frame_send(serial_handler_t *handler)
{
    int fd = *(int *)handler->private;
    tcflush(fd, TCIOFLUSH);
#if 0
    printf("serial send:");
    for (uint8_t i = 0; i < handler->serial_frame_length; i++)
    {
        printf("%c", handler->serial_frame_buff[i]);
    }
    printf("\r\n");
#endif
    if (write(*(int *)(handler->private), handler->serial_frame_buff, handler->serial_frame_length) < 0)
    {
        return SERIAL_FRAME_SEND_ERR;
    }
    return SERIAL_SUCCESS;
}

serial_status_t serial_frame_recv(serial_handler_t *handler)
{
    int fd = *(int *)handler->private;
    serial_status_t ret = SERIAL_SUCCESS;
    int timer = GET_TICK_COUNT();
    uint8_t buffer[1024 * 3] = {0};
    int r = 0;
    int lenght = 0;
    while (1)
    {
        r = read(fd, &buffer[lenght], 30);

        if (r > 0)
        {
            lenght = lenght + r;
            timer = GET_TICK_COUNT();
        }

        if (GET_TICK_COUNT() - timer > handler->respond_timeout)
        {
            break;
        }
        usleep(100);
    }

    if (lenght > 0)
    {
        handler->serial_frame_length = lenght;
        memcpy(handler->serial_frame_buff, buffer, lenght);
        ret = SERIAL_SUCCESS;
#if 0
        printf("recv len = %d,recv=", lenght);
        for (int i = 0; i < lenght; i++)
        {
           printf("%02x", buffer[i]);
        }
        printf("\r\n");
#endif
    }
    else
    {
        ret = SERIAL_SLAVE_NO_RESPOND;
    }
    return ret;
}

serial_status_t serial_hander_init(serial_handler_t **req_handler, uint8_t port, uint32_t baud_rate,
                                   uint8_t data_width, uint8_t parity, uint8_t nstop)
{
    serial_handler_t *handler = NULL;
    serial_status_t status = SERIAL_SUCCESS;
    handler = serial_alloc_handler();
    if (handler == NULL)
    {
        return SERIAL_HANDER_INIT_ERROR;
    }
    status = serial_open(handler, port, baud_rate, data_width, parity, nstop);
    if (status != SERIAL_SUCCESS)
    {
        return status;
    }
    serial_mutex_create(&handler->serial_mutex);
    handler->frame_recv = serial_frame_recv;
    handler->frame_send = serial_frame_send;
    handler->respond_timeout = 500;
    *req_handler = handler;
    return status;
}

serial_status_t serial_hander_uninit(serial_handler_t *req_handler)
{
    serial_status_t status = SERIAL_SUCCESS;

    serial_mutex_unlock(&req_handler->serial_mutex);
    serial_mutex_del(&req_handler->serial_mutex);
    serial_close(req_handler);
    serial_free_handler(req_handler);

    return status;
}
