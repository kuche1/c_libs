# c_libs

some C libraries

## conventions

### errors

if the percise reason for an error doesnt really matter:\
errors are returned as string containing the source function\
and an explanation\
NULL is returned if there is no error

if a string is used to indicate an error, that same function\
must have an alternative implementation that instead returns void\
and internally calls the original function (but panics if there is\
an error)

(just an idea) if there is an errno it always needs to be printed or\
included in the returned string

(TODO) make another library that wraps around stdandard functions\
and checks for errno and prints that errno (and then maybe we could\
use enums for errors)

(TODO) maybe use "error level" which translates to "at which level do we\
want to propagate errors", something like 0(never panic) 1(panic but only when\
errors are theoretically impossible) 2(panic when the programmer made a mistake)\
3(always panic)

### includes

includes are ordered by length

the first include is the associated `.h` file\
then after an empty line any `"` includes\
then after an empty line any `<` includes

### other

if a function can cause a panic the name needs to end with `$`

private data is never shown

`{` is always alone on a line (testing this out)

address-related operations (`*` and `&`) need to be surrounded by spaces
