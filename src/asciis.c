#include <stdio.h>
#include "asciis.h"
#include <string.h>

void ascii(char path[50]) {
  
  char linha[100];

  FILE *arquivo = fopen(path, "r");
  
  while (fgets(linha, sizeof(linha), arquivo)) {
    printf("%s", linha);
  }

}
