#include <stdio.h>
#include <stdlib.h>
#include "estring.h"

int main ( void )
{
    String stackS = make_string("Test string"),
           *heapS = new_string("This is on the heap");
    printf("%s\n%s\n", stackS.self, heapS->self);
    CONCAT_CHAR(
        heapS,
        "\nConcat literal"
    );
    printf("%s\n", heapS->self);
    CONCAT_CHAR(
        &stackS,
        "\n"
    );
    puts(stackS.self);
    CONCAT_STRING(
        heapS,
        &stackS
    );
    printf("%s\n", heapS->self);
    free(stackS.self);
    delete_string(&heapS);
    return 0;
}
