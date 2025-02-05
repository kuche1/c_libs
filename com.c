
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

char * com_init(struct com * * self)
{
    char * err = "com_init: unreachable";

    struct com * s = malloc(sizeof(struct com));
    if(!s)
    {
        err = "com_init: malloc failure";
        goto err_malloc;
    }
    * self = s;

    s->inbox_eventfd = eventfd(0, EFD_NONBLOCK);
    if(s->inbox_eventfd < 0)
    {
        err = "com_init: eventfd failure";
        goto err_eventfd;
    }

    if(pthread_mutex_init(& s->inbox_lock, NULL))
    {
        err = "com_init: pthread_mutex_init failure";
        goto err_mutex;
    }

    return NULL;

    pthread_mutex_destroy(& s->inbox_lock);
err_mutex:

    close(s->inbox_eventfd);
err_eventfd:

    free(s);
err_malloc:

    return err;
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

char * com_send_raw(struct com * self, struct com * other, uint64_t msg)
{
    char * err = "com_send_raw: unreachable";

    if(pthread_mutex_lock(& other->inbox_lock))
    {
        err = "com_send_raw: could not acquire inbox lock";
        goto err_lock;
    }

    ssize_t sz = write(other->inbox_eventfd, & msg, sizeof(msg));
    if(sz < 0)
    {
        err = "com_send_raw: write failure";
        goto err_write;
    }
    if(sz != sizeof(msg))
    {
        err = "com_send_raw: assertion failed: sz != sizeof(msg)"
        goto err_write;
    }

    if(pthread_mutex_unlock(& other->inbox_lock))
    {
        CRITICAL("com_send_raw: could not unlock inbox lock");
    }

err_write:

    if(pthread_mutex_unlock(& other->inbox_lock))
    {
        CRITICAL("com_send_raw: could not unlock inbox lock during the handling of another error");
    }
err_lock:

    return err;
}
