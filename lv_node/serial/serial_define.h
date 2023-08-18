#ifndef _SERIAL_DEFINE_H
#define _SERIAL_DEFINE_H
#include <stdint.h>
#include <pthread.h>

#define SERIAL_BUF_MAX_LENGTH (1024 * 3) // serial buffer max length
#define SERIAL_CONFIG_HANDLER_MAX 2      // serial config handler max number
#define SERIAL_MUTEX_T pthread_mutex_t   // serial mutex type

/**
 * Serial port status
 * @param  SERIAL_SUCCESS  success
 * @param  SERIAL_FRAME_SEND_ERR  frame send error
 * @param  SERIAL_SLAVE_NO_RESPOND  slave no respond
 * @param  SERIAL_MUTEX_ERROR  mutex error
 * @param  SERIAL_HANDER_INIT_ERROR  handler init error
 * @param  SERIAL_INIT_ERROR  serial init error
 **/
typedef enum serial_status
{
    SERIAL_SUCCESS = 0,
    SERIAL_FRAME_SEND_ERR,
    SERIAL_SLAVE_NO_RESPOND,
    SERIAL_MUTEX_ERROR,
    SERIAL_HANDER_INIT_ERROR,
    SERIAL_INIT_ERROR
} serial_status_t;

/**
 * Serial port parity
 * @param  SERIAL_PAR_NONE        none
 * @param  SERIAL_PAR_ODD         odd
 * @param  SERIAL_PAR_EVEN        even
 **/
typedef enum
{
    SERIAL_PAR_NONE,
    SERIAL_PAR_ODD,
    SERIAL_PAR_EVEN
} serial_parity_t;

typedef struct serial_handler serial_handler_t;
typedef serial_status_t (*serial_send_func_t)(serial_handler_t *handler);
typedef serial_status_t (*serial_recv_func_t)(serial_handler_t *handler);

/**
 * serial data structure
 */
typedef struct serial_handler
{
    uint8_t used;                                     /**< The value is 1 when used */
    uint8_t serial_frame_buff[SERIAL_BUF_MAX_LENGTH]; /**< Buffer used to send and receive frame*/
    uint32_t serial_offset;                           /**< Offset of the ydt on ydt_frame_buff[] */
    uint32_t serial_frame_length;                     /**< The length of the whole frame */
    uint32_t respond_timeout;                         // ms
    serial_send_func_t frame_send;                    /**< The callback funciton to send the frame */
    serial_recv_func_t frame_recv;                    /**< The callback funciton to receive the frame */
    SERIAL_MUTEX_T serial_mutex;
    void *private;
} serial_handler_t;

#endif
