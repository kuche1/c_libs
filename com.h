
#ifndef _COM_H_
#define _COM_H_

// multithreaded communication

struct com;

char * com_init (struct com * * self);
void   com_init$(struct com * * self);

char * com_deinit (struct com * self);
void   com_deinit$(struct com * self);

char * com_send_raw(struct com * self, struct com * other, uint64_t msg); // TODO make static

#endif
