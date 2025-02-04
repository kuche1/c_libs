
#include "buf.h"

#include <assert.h>
#include <string.h>

int main(void)
{
    struct buf * ints;
    buf_init$(& ints, sizeof(int));

    {
        int * item;
        buf_append$(ints, (void * *) & item);
        * item = 5;
    }

    {
        int * item;
        buf_get$(ints, 0, (void * *) & item);
        assert(* item == 5);
    }

    buf_remove$(ints, 0);

    assert(buf_remove(ints, 0));

    {
        int * item;
        buf_append$(ints, (void * *) & item);
        * item = 6;
    }

    {
        int * item;
        buf_append$(ints, (void * *) & item);
        * item = 9;
    }

    {
        int * item;
        buf_append$(ints, (void * *) & item);
        * item = 2;
    }

    {
        int * item;
        buf_get$(ints, 0, (void * *) & item);
        assert(* item == 6);
    }

    {
        int * item;
        buf_get$(ints, 1, (void * *) & item);
        assert(* item == 9);
    }

    {
        int * item;
        buf_get$(ints, 2, (void * *) & item);
        assert(* item == 2);
    }

    assert(buf_len(ints) == 3);

    {
        int * all = buf_get_arr(ints);
        int expected[] = {6, 9, 2};
        assert(memcmp(all, expected, sizeof(expected)) == 0);
    }

    buf_deinit(ints);

    return 0;
}
