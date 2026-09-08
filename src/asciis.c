#include <stdio.h>
#include <string.h>
#include "info.h"
#include <stddef.h>
#include "asciis.h"
#include "../build/logos.h"

int ascii(char *linha, size_t tamanho)
{
    static size_t pos = 0;

    const unsigned char *logo = src_logo_ascii_d_debian_txt;
    unsigned int logo_len = src_logo_ascii_d_debian_txt_len;

    if (pos >= logo_len || tamanho == 0)
        return 0;

    size_t i = 0;

    while (pos < logo_len && i < tamanho - 1) {
        char c = logo[pos++];

        if (c == '\n')
            break;

        linha[i++] = c;
    }

    linha[i] = '\0';

    return 1;
}



