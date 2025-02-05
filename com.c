
#include "com.h"

#include "err.h"

#include <sys/eventfd.h>
#include <stdlib.h>
#include <unistd.h>

struct com
{
    int inbox_eventfd; // this is also used as the id of the instance
    pthread_mutex_t inbox_lock;
};

enum com_init$pln$err com_init$pln(struct com * * self)
{
    enum com_init$pln$err err = -1;

    struct com * s = malloc(sizeof(struct com));
    if(!s)
    {
        err = COM_INIT$PLN$ERR_MALLOC;
        goto err_malloc;
    }
    * self = s;

    s->inbox_eventfd = eventfd(0, EFD_NONBLOCK);
    if(s->inbox_eventfd < 0)
    {
        err = COM_INIT$PLN$ERR_EVENTFD;
        goto err_eventfd;
    }

    if(pthread_mutex_init(& s->inbox_lock, NULL))
    {
        err = COM_INIT$PLN$ERR_MUTEX_INIT;
        goto err_mutex;
    }

    return NULL;

    if(pthread_mutex_destroy(& s->inbox_lock))
    {
        err = COM_INIT$PLN$ERR_ERR_MUTEX_CLOSE;
    }
err_mutex:

    if(close(s->inbox_eventfd))
    {
        err = COM_INIT$PLN$ERR_ERR_CLOSE;
    }
err_eventfd:

    free(s);
err_malloc:

    return err;
}

enum com_init$plti$err com_init$plti(struct com * * self)
{
    switch(com_init$pln(self))
    {
        case COM_INIT$PLN$ERR_NONE:
            return COM_INIT$PLTI$ERR_NONE;
        
        case COM_INIT$PLN$ERR_MALLOC:
            return COM_INIT$PLTI$ERR_MALLOC;

        case COM_INIT$PLN$ERR_EVENTFD:
            return COM_INIT$PLTI$ERR_EVENTFD;

        case COM_INIT$PLTI$ERR_MUTEX_INIT:
        case COM_INIT$PLN$ERR_ERR_MUTEX_DEINIT:
        case COM_INIT$PLN$ERR_ERR_CLOSE:
            PANIC();
    }

    return -1;
}

void com_init$(struct com * * self)
{
    PANIC(com_init(self));
}

char * com_deinit(struct com * self)
{
    if(pthread_mutex_destroy(& self->inbox_lock))
    {
        return "com_deinit: could not destroy inbox lock";
    }

    if(close(self->inbox_eventfd))
    {
        return "com_deinit: close failure";
    }

    free(self);

    return NULL;
}

void com_deinit$(struct com * self)
{
    PANIC(com_deinit(self));
}

enum com_send_raw_err com_send_raw(struct com * self, struct com * other, uint64_t msg)
{
    enum com_send_raw_err err = -1;

    if(pthread_mutex_lock(& other->inbox_lock))
    {
        err = CON_SEND_RAW_ERR_LOCK;
        goto err_lock;
    }

    ssize_t sz = write(other->inbox_eventfd, & msg, sizeof(msg));
    if(sz < 0)
    {
        err = CON_SEND_RAW_ERR_WRITE;
        goto err_write;
    }
    if(sz != sizeof(msg))
    {
        err = CON_SEND_RAW_ERR_WRITE_NOT_FULL;
        goto err_write;
    }

    if(pthread_mutex_unlock(& other->inbox_lock))
    {
        err = CON_SEND_RAW_ERR_UNLOCK;
        goto err_unlock;
    }

    return COM_SEND_RAW_ERR_NONE;

err_unlock:
err_write:

    if(pthread_mutex_unlock(& other->inbox_lock))
    {
        err = CON_SEND_RAW_ERR_UNLOCK_DURING_ERR;
    }
err_lock:

    return err;
}

void com_send_raw$(struct com * self, struct com * other, uint64_t msg)
{
    PANICIF(com_send_raw(self, other, msg));
}
