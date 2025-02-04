# c_libs

some C libraries

## conventions

### errors

if the percise reason for an error doesnt really matter:\
errors are returned as string containing an explanation\
NULL is returned if there is no error

if a string is used to indicate an error, that same function\
must have an alternative implementation that instead returns void\
and internally calls the original function (but panics if there is\
an error)

### other

if a function can cause a panic the name needs to end with `$`

private data is never shown

includes are ordered by length

`{` is always alone on a line (testing this out)

address-related operations (`*` and `&`) need to be surrounded by spaces
