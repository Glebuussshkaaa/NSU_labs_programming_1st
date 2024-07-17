#include "error.h"
#include <stdio.h>
#include <stdlib.h>

int BadInputError(void) {
    printf("bad input\n");
    return EXIT_SUCCESS;
}

int ErrorHandler(void) {
    printf("Ошибка\n");
    return EXIT_SUCCESS;
}


