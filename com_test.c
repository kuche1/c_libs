
#include "com.h"

#include <assert.h>

int main(void)
{
    struct com * com;
    com_init$(& com);

    assert(com_get_id(com) == 3);

    com_deinit$(com);
}