#include <stdio.h>
#include "show.h"
#include "info.h"
#include "asciis.h"

void show(unsigned char *logo, unsigned int logo_len)
{
    char linha_ascii[130];
    int info_pos = 0;
    int inform = 0;

    const char *infos[] = {
        os,
        kernel,
        arch,
        hostname,
        uptime,
        distro,
        shell,
        cpu,
        environment,
        ram 
  };

  const char *informacoes[] = {
      "os",
      "kernel",
      "arch",
      "hostname",
      "uptime",
      "distro",
      "shell",
      "cpu",
      "environment",
      "ram"      
  };
  
while (ascii(logo, logo_len, linha_ascii, sizeof(linha_ascii))) {
    printf("%-35s", linha_ascii);

    while (info_pos < 10 && infos[info_pos][0] == '\0')
        info_pos++;

    if (info_pos < 10) {
        printf(" \t\033[32m%s:\033[0m %s",
               informacoes[info_pos],
               infos[info_pos]);

        info_pos++;
    }

    putchar('\n');
}


}
