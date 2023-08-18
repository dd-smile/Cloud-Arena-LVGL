
#ifndef _SERIAL_COLOR_H
#define _SERIAL_COLOR_H
#include "serial_mutex.h"
#include "serial_api.h"
#include "serial_define.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "lvgl/lvgl.h"


void serial_send(const unsigned char *data, int length);
/**
 * Serial port initialization
 * @param  handler This is the struct pointer
 * @return no return value
 */
void serial_init(serial_handler_t **handler);


/**
 * Serial port uninitialization
 * @param  serial port pointer
 * @return no return value
 */
void serial_uinit(serial_handler_t *handler);


/**
 * Serial send data
 * @param  what to send
 * @return no return value
 */
// void *serial_send(char *text);


/**
 *print received content
 * @param NULL
 * @return no return value
 */
void *serial_recv();

void ReadSerialDi(void *args);

extern serial_handler_t *serial_handler;


#endif