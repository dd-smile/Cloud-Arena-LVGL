#ifndef _SERIAL_API_H
#define _SERIAL_API_H

#include <stdint.h>
#include "serial_define.h"

/**
 * Serial send data
 * @param  Serial port structure pointer
 * @return Is itsuccessfully
 */
serial_status_t serial_frame_send(serial_handler_t *handler);


/**
 * Serial read data
 * @param   Serial port structure pointer
 * @return Is itsuccessfully
 */
serial_status_t serial_frame_recv(serial_handler_t *handler);


/**
 * Open serial port
 * @param  handler This is the struct pointer
 * @param  port  This is the serial port channel 0 is channel one and 1 is channel two
 * @param  baud_rate  This is the serial port baud rate  support 9600, 19200, 38400, 57600, 115200
 * @param  data_width  This is the serial port data bit Usually 8
 * @param  parity  This is the serial port parity Usually 0
 * @param  nstop  This is the serial port stop bit Usually 1
 * @return Is itsuccessfully
 */
serial_status_t serial_open(serial_handler_t *handler, uint8_t port, uint32_t baud_rate, uint8_t data_width, serial_parity_t parity, uint8_t nstop);


/**
 * Serial port initialization
 * @param  Serial port structure pointer
 * @return Is itsuccessfully
 */
serial_status_t serial_close(serial_handler_t *handler);


/**
 * Serial port initialization
 * @param  handler  struct pointer
 * @param  port   serial port channel 0 is channel one and 1 is channel two
 * @param  baud_rate   serial port baud rate  support 9600, 19200, 38400, 57600, 115200
 * @param  data_width   serial port data bit Usually 8
 * @param  parity   serial port parity Usually 0
 * @param  nstop    serial port stop bit Usually 1
 * @return Is itsuccessfully
 */
serial_status_t serial_hander_init(serial_handler_t **req_handler, uint8_t port, uint32_t baud_rate, uint8_t data_width, uint8_t parity, uint8_t nstop);


/**
 * Serial port initialization
 * @param   Serial port structure pointer
 * @return Is itsuccessfully
 */
serial_status_t serial_hander_uninit(serial_handler_t *req_handler);


#endif

