
#include "net.h"

#include "err.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define LISTEN_QUEUE 5

struct net
{
    int sock;
    struct sockaddr_in addr;
};

char * net_init(struct net * * self, uint16_t port)
{
    char * err = "net_init: unreachable";

    struct net * s = malloc(sizeof(struct net));
    if(!s)
    {
        err = "net_init: malloc failure";
        goto err_malloc;
    }
    * self = s;

    s->sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if(s->sock < 0)
    {
        err = "net_init: could not create socket";
        goto err_sock;
    }

    if(setsockopt(s->sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        err = "net_init: could not make socket reusable";
        goto err_reusable;
    }

    memset(& s->addr, 0, sizeof(s->addr));

    s->addr.sin_family = AF_INET;
    s->addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    s->addr.sin_port = htons(port);

    if(bind(s->sock, (struct sockaddr *) & s->addr, sizeof(s->addr)))
    {
        err = "net_init: could not bind";
        goto err_bind;
    }

    if(listen(s->sock, LISTEN_QUEUE))
    { 
        err = "net_init: could not listen";
        goto err_listen;
    }

    return NULL;

err_listen:
err_bind:
err_reusable:

    close(s->sock);
err_sock:

    free(s);
err_malloc:

    return err;
}

void net_init$(struct net * * self, uint16_t port)
{
    PANIC(net_init(self, port));
}

char * net_deinit(struct net * self)
{
    if(shutdown(self->sock, SHUT_RDWR))
    {
        return "net_deinit: shutdown failure";
    }

    if(close(self->sock))
    {
        return "net_deinit: close failure";
    }

    free(self);

    return NULL;
}

void net_deinit$(struct net * net)
{
    PANIC(net_deinit(net));
}
