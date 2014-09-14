#include <stdio.h>
#include <stdlib.h>
#include "estring.h"

int main ( void )
{
    String stackS = make_string("Test string"),
		   intString = make_string("123"),
		   dblString = make_string(" 12.3"),
           *heapS = new_string("This is on the heap");
    int test_int;
    double test_double;
    S_TO_NUM(intString, &test_int, NUM_INT);
    S_TO_NUM(dblString, &test_double, NUM_DOUBLE);
    destroy_string(
		&intString
	);
	destroy_string(
		&dblString
	);
    printf(
        "%s\n%s\n",
        TO_STRING(stackS),
        P_TO_STRING(heapS)
    );
    printf(
		"String to int test: %d\nString to double test: %f\n",
		test_int,
		test_double
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
