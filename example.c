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
    PREPEND_CHAR(
        &stackS,
        "This is a heap-"
    );
    printf(
        "\nPrepend literal:\n%s\n",
        TO_STRING(stackS)
    );
    CONCAT_CHAR(
        heapS,
        "\nConcat literal"
    );
    printf("\nConcatenated to heap:\n%s\n", P_TO_STRING(heapS));
    CONCAT_CHAR(
        &stackS,
        "\n"
    );
    PREPEND_STRING(
        heapS,
        &stackS
    );
    puts("Prepend string to string:");
    puts(P_TO_STRING(heapS));
    CONCAT_STRING(
        heapS,
        &stackS
    );
    puts("Concatenate strings:");
    printf("%s\n", P_TO_STRING(heapS));
    destroy_string(&stackS);
    delete_string(&heapS);
    return 0;
}
