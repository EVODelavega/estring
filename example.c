#include <stdio.h>
#include <stdlib.h>
#include "estring.h"

int main ( void )
{
    String stackS = make_string("Test string"),
           *heapS = new_string("This is on the heap");
    printf(
        "%s\n%s\n",
        TO_STRING(stackS),
        P_TO_STRING(heapS)
    );
    CONCAT_CHAR(
        heapS,
        "\nConcat literal"
    );
    printf("%s\n", P_TO_STRING(heapS));
    CONCAT_CHAR(
        &stackS,
        "\n"
    );
    puts(TO_STRING(stackS));
    CONCAT_STRING(
        heapS,
        &stackS
    );
    printf("%s\n", P_TO_STRING(heapS));
    destroy_string(&stackS);
    delete_string(&heapS);
    return 0;
}
