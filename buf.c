
#include "buf.h"

#include "err.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1 // must be at least 1

struct buf
{
    char * mem;
    size_t item_size;

    size_t len;
    size_t size;
};

char * buf_init(struct buf * * self, size_t item_size)
{
    struct buf * s = malloc(sizeof(struct buf));
    if(!s)
    {
        return "buf_init: malloc failure";
    }
    * self = s;

    s->mem = malloc(item_size * INITIAL_SIZE);
    if(!s->mem)
    {
        return "buf_init: malloc failure";
    }

    s->item_size = item_size;
    s->len = 0;
    s->size = INITIAL_SIZE;

    return NULL;
}

void buf_init$(struct buf * * self, size_t item_size)
{
    PANICIF(buf_init(self, item_size));
}

void buf_deinit(struct buf * self)
{
    free(self->mem);
}

char * buf_append(struct buf * self, void * * item)
{
    if(self->len >= self->size)
    {
        void * new = realloc(self->mem, self->item_size * self->size * 2);
        if(!new)
        {
            return "buf_append: relloc failure";
        }

        self->mem = new;
        self->size *= 2;
    }

    * item = & self->mem[self->item_size * self->len];
    self->len += 1;

    return NULL;
}

void buf_append$(struct buf * self, void * * item)
{
    PANICIF(buf_append(self, item));
}

char * buf_remove(struct buf * self, size_t idx)
{
    if(idx >= self->len)
    {
        return "buf_remove: invalid index";
    }

    if((self->len >= 2) && (idx != self->len - 1)){
        memcpy(
            & self->mem[self->item_size * idx],
            & self->mem[self->item_size * (self->len - 1)],
            self->item_size);
    }

    self->len -= 1;

    return NULL;
}

void buf_remove$(struct buf * self, size_t idx)
{
    PANICIF(buf_remove(self, idx));
}

size_t buf_len(struct buf * self)
{
    return self->len;
}

char * buf_get(struct buf * self, size_t idx, void * * item)
{
    if(idx >= self->len)
    {
        return "buf_get: invalid index";
    }

    * item = & self->mem[self->item_size * idx];

    return NULL;
}

void buf_get$(struct buf * self, size_t idx, void * * item)
{
    PANICIF(buf_get(self, idx, item));
}

void * buf_get_arr(struct buf * self)
{
    return self->mem;
}
