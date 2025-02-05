
// TODO tova s panic nivata mi haresva kato ideq no habq nerealno mnogo vreme s nego
// no trqbva da izmislq kak da go napravq po-adekvatno che da ne habq tolkova mnogo vreme
// moje bi da summarize-na nqkoi ot greshkite, moje bi da namalq nivata na panic level

#ifndef _COM_H_
#define _COM_H_

// multithreaded communication

struct com;

enum com_init$pln$err
{
    COM_INIT$PLN$ERR_NONE = 0,
    COM_INIT$PLN$ERR_MALLOC,
    COM_INIT$PLN$ERR_EVENTFD,
    COM_INIT$PLN$ERR_MUTEX_INIT,
    COM_INIT$PLN$ERR_ERR_MUTEX_DEINIT,
    COM_INIT$PLN$ERR_ERR_CLOSE,
};
enum com_init$pln$err com_init$pln(struct com * * self);

enum com_init$plti$err
{
    COM_INIT$PLTI$ERR_NONE = 0,
    COM_INIT$PLTI$ERR_MALLOC,
    COM_INIT$PLTI$ERR_EVENTFD,
};
enum com_init$plti$err com_init$plti(struct com * self)

// PM will be the same as TI

void com_init$ploor(struct com * self);

// A will be the same as OOR

#if COM_PANIC_LEVEL_NONE

    #define com_init com_init$pln

#elif COM_PANIC_LEVEL_THEORETICALLY_IMPOSSIBLE

    #define com_init com_init$plti

#elif COM_PANIC_LEVEL_PROGRAMMER_MISTAKE

    #define com_init com_init$plpm

#elif COM_PANIC_LEVEL_OUT_OF_RESOURCE

    #define com_init com_init$ploor

#elif COM_PANIC_LEVEL_ALWAYS

    #define com_init com_init$pla

#else

#error You need to define a panic level. Those are used to determine when a function should panic and when it should return some kind of error instead. The available panic levels are: COM_PANIC_LEVEL_NONE (never panic), COM_PANIC_LEVEL_THEORETICALLY_IMPOSSIBLE (panic only on theoretically impossible conditions), COM_PANIC_LEVEL_PROGRAMMER_MISTAKE (panic if the programmer has made a mistake), COM_PANIC_LEVEL_OUT_OF_RESOURCE (panic if out of resources, for example if malloc fails), COM_PANIC_LEVEL_ALWAYS (always panic).

#endif

char * com_init (struct com * * self, enum com_panic_level panic_level);
void   com_init$(struct com * * self);

char * com_deinit (struct com * self);
void   com_deinit$(struct com * self);

enum com_send_raw_err
{
    COM_SEND_RAW_ERR_NONE = 0,
    CON_SEND_RAW_ERR_LOCK,
    CON_SEND_RAW_ERR_WRITE,
    CON_SEND_RAW_ERR_WRITE_NOT_FULL,
    CON_SEND_RAW_ERR_UNLOCK,
    CON_SEND_RAW_ERR_UNLOCK_DURING_ERR,
};
char * com_send_raw(struct com * self, struct com * other, uint64_t msg); // TODO make static

#endif
