
#ifndef _BUF_H_
#define _BUF_H_

#include <sys/types.h>

struct buf;

char * buf_init (struct buf * self, size_t item_size);
void   buf_init$(struct buf * self, size_t item_size);

void buf_deinit(struct buf * self);

char * buf_append (struct buf * self, void * * item);
void   buf_append$(struct buf * self, void * * item);
// `* item` will be set to a pointer to the memory allocated for the new element
//     said memory has to be filled by the caller

char * buf_remove (struct buf * self, size_t idx);
void   buf_remove$(struct buf * self, size_t idx);
// the last element will be copied to index `idx` (if needed)
//     then the length will be reduced

size_t buf_len(struct buf * self);

char * buf_get (struct buf * self, size_t idx, void * * item);
void   buf_get$(struct buf * self, size_t idx, void * * item);
// pointer to item is written to `* item`

void * buf_get_arr(struct buf * self);
// return a pointer to the continious region in momory
//     that contain all buffer elements

#endif
