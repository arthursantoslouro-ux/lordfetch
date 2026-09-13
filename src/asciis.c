#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "../headers/asciis.h"
#include "../headers/info.h"

char linha_logo[4096];

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






void show_logo(int argc, char *argv[])
{
    if (argc < 3)
        return;

    FILE *arquivo = fopen(argv[2], "r");

    if (arquivo == NULL) {
        printf("lordfetch: não foi possível abrir o logo\n");
        return;
    }

    char linha_logo[4096];

    const char *infos[] = {
        os,
        kernel,
        arch,
        uptime,
        distro,
        shell,
        cpu,
        environment,
        ram,
        ip
    };

    const char *informacoes[] = {
        "os",
        "kernel",
        "arch",
        "uptime",
        "distro",
        "shell",
        "cpu",
        "environment",
        "ram",
        "ip"
    };

    int info_pos = 0;
    int linha = 0;

    while (fgets(linha_logo, sizeof(linha_logo), arquivo)) {

        /* Remove o \n que o fgets colocou */
        linha_logo[strcspn(linha_logo, "\n")] = '\0';

        /*
         * Imprime o logo ANSI.
         *
         * 35 espaços depois do logo deixam um espaço
         * para as informações do sistema.
         */
        printf("%s", linha_logo);

        /*
         * Informações do sistema
         */
        if (linha == 0) {

            printf("     \033[1;32m%s@%s\033[0m",
                   username,
                   hostname);

        } else if (linha == 1) {

            printf("     ---------------------------");

        } else {

            while (info_pos < 10 &&
                   infos[info_pos][0] == '\0') {
                info_pos++;
            }

            if (info_pos < 10) {

                printf("     \033[32m%s:\033[0m %s",
                       informacoes[info_pos],
                       infos[info_pos]);

                info_pos++;
            }
        }

        putchar('\n');

        linha++;
    }

    /*
     * Se o logo acabar antes das informações,
     * continua mostrando as informações abaixo.
     */
    while (info_pos < 10) {

        if (infos[info_pos][0] != '\0') {

            printf(
                "     \033[32m%s:\033[0m %s\n",
                informacoes[info_pos],
                infos[info_pos]
            );
        }

        info_pos++;
    }

    fclose(arquivo);
}
