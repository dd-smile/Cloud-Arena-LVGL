#include "serial_mutex.h"

static serial_handler_t serial_handler[SERIAL_CONFIG_HANDLER_MAX] = {0};

serial_handler_t *serial_alloc_handler(void)        
{
    for (uint8_t i = 0; i < SERIAL_CONFIG_HANDLER_MAX; i++)
    {
        if (serial_handler[i].used == 0)
        {
            serial_handler[i].used = 1;
            return &serial_handler[i];
        }
    }
    return NULL;
}

void serial_free_handler(serial_handler_t *handler)     
{
    if (handler->used == 1)
    {
        handler->used = 0;
    }
}

serial_status_t serial_mutex_create(SERIAL_MUTEX_T *mutex)
{
    if (pthread_mutex_init(mutex, NULL) != 0)
    {
        return SERIAL_MUTEX_ERROR;
    }
    else
    {
        return SERIAL_SUCCESS;
    }
}

serial_status_t serial_mutex_lock(SERIAL_MUTEX_T *mutex)
{
    if (pthread_mutex_lock(mutex) != 0)
    {
        return SERIAL_MUTEX_ERROR;
    }
    else
    {
        return SERIAL_SUCCESS;
    }
}

serial_status_t serial_mutex_unlock(SERIAL_MUTEX_T *mutex)
{

    if (pthread_mutex_unlock(mutex) != 0)
    {
        return SERIAL_MUTEX_ERROR;
    }
    else
    {
        return SERIAL_SUCCESS;
    }
}

serial_status_t serial_mutex_del(SERIAL_MUTEX_T *mutex)
{

    if (pthread_mutex_destroy(mutex) != 0)
    {
        return SERIAL_MUTEX_ERROR;
    }
    else
    {
        return SERIAL_SUCCESS;
    }
}
