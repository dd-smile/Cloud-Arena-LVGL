#ifndef _SERIAL_MUTEX_H
#define _SERIAL_MUTEX_H

#include <pthread.h>
#include "serial_define.h"

serial_handler_t *serial_alloc_handler(void);
void serial_free_handler(serial_handler_t *handler);

serial_status_t serial_mutex_create(SERIAL_MUTEX_T *mutex);

serial_status_t serial_mutex_lock(SERIAL_MUTEX_T *mutex);

serial_status_t serial_mutex_unlock(SERIAL_MUTEX_T *mutex);

serial_status_t serial_mutex_del(SERIAL_MUTEX_T *mutex);

#endif

