#include <stdio.h>
#include "colors.h"

void color(int id)
{
    switch (id) {
        case 1:
            printf("\033[34m"); // azul
            break;

        case 2:
            printf("\033[36m"); // ciano
            break;
    }
}
