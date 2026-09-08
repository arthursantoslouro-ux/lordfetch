#include "show.h"
#include "info.h"
#include "asciis.h"
#include <stdio.h>

void show(void)
{
    char linha_ascii[130];
    int info_pos = 0;

    const char *infos[] = {
        os,
        kernel,
        arch,
        hostname,
        uptime,
        distro
    };

    while (ascii(linha_ascii, sizeof(linha_ascii))) {
        printf("%-35s", linha_ascii);

        if (info_pos < 6)
            printf("%s", infos[info_pos++]);

        putchar('\n');
    }
}
