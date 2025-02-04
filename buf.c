
#include "buf.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1 // must be at least 1

#define PANIC(val) { \
    if(val) \
    { \
        exit(EXIT_FAILURE); \
    } \
}

struct buf
{
    char * mem;
    size_t item_size;

    size_t len;
    size_t size;
};

char * buf_init(struct buf * self, size_t item_size)
{
    self->mem = malloc(item_size * INITIAL_SIZE);
    if(!self->mem)
    {
        return "malloc failure";
    }

    self->item_size = item_size;
    self->len = 0;
    self->size = INITIAL_SIZE;

    return NULL;
}

void buf_init$(struct buf * self, size_t item_size)
{
    PANIC(buf_init(self, item_size));
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
            return "relloc failure";
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
    PANIC(buf_append(self, item));
}

char * buf_remove(struct buf * self, size_t idx)
{
    if(idx >= self->len)
    {
        return "invalid index";
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
    PANIC(buf_remove(self, idx));
}

size_t buf_len(struct buf * self)
{
    return self->len;
}

char * buf_get(struct buf * self, size_t idx, void * * item)
{
    if(idx >= self->len)
    {
        return "invalid index";
    }

    * item = & self->mem[self->item_size * idx];

    return NULL;
}

void buf_get$(struct buf * self, size_t idx, void * * item)
{
    PANIC(buf_get(self, idx, item));
}

void * buf_get_arr(struct buf * self)
{
    return self->mem;
}
