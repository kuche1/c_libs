
#ifndef _NET_H_
#define _NET_H_

#include <stdint.h>

enum net_event
{
    NET_EVENT_TIMEOUT = 0,
    NET_EVENT_CONNECT,
    NET_EVENT_DISCONNECT,
    NET_EVENT_RECV,
};

struct net;

char * net_init (struct net * * self, uint16_t port);
void   net_init$(struct net * * self, uint16_t port);

char * net_deinit (struct net * self);
void   net_deinit$(struct net * self);

enum net_event net_wait_event(struct net * self, int * client, int timeout_ms);

char * net_hangup (int client);
void   net_hangup$(int client);

char * net_recv_byte (int client, char * byte);
void   net_recv_byte$(int client, char * byte);

char * net_send_byte (int client, char byte);
void   net_send_byte$(int client, char byte);

#endif
