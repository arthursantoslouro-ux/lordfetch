#include <stddef.h>
#include "asciis.h"

int ascii(unsigned char *logo, unsigned int logo_len,
          char *linha, size_t tamanho)
{
    static size_t pos = 0;
    size_t i = 0;

    if (pos >= logo_len || tamanho == 0)
        return 0;

    while (pos < logo_len && i < tamanho - 1) {
        char c = logo[pos++];

        if (c == '\n')
            break;

        linha[i++] = c;
    }

    linha[i] = '\0';

    return 1;
}
