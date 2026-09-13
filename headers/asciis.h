#ifndef ASCII_H
#define ASCII_H

extern char linha_logo[4096];

#include <stddef.h>

int ascii(unsigned char *logo, unsigned int logo_len,
          char *linha, size_t tamanho);



void show_logo(int argc, char *argv[]);

#endif
