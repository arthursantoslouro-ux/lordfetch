#include <stdio.h>
#include "show.h"
#include "info.h"
#include "asciis.h"

void show(unsigned char *logo, unsigned int logo_len)
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

    while (ascii(logo, logo_len, linha_ascii, sizeof(linha_ascii))) {
        printf("%-35s", linha_ascii);

        if (info_pos < 6)
            printf("%s", infos[info_pos++]);

        putchar('\n');
    }
}
