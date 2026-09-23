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
        printf("lordfetch: It wasn't possible to open the logo\n");
        return;
    }

    char linha_logo[4096];

    const char *infos[] = {
        os,
        host,
        kernel,
        shell,
        ram,
        ip,
        packages
    };

    const char *informacoes[] = {
        "OS",
        "Host",
        "Kernel",
        "Shell",
        "Memory",
        "Local IP",
        "Packages"
    };

    int info_pos = 0;
    int linha = 0;

    while (fgets(linha_logo, sizeof(linha_logo), arquivo)) {

        linha_logo[strcspn(linha_logo, "\n")] = '\0';

        printf("%s", linha_logo);

        if (linha == 0) {

            printf(
                "     %s%s@%s\033[0m",
                distro_color,
                username,
                hostname
            );

        } else if (linha == 1) {

            int tamanho =
                strlen(username) +
                1 +
                strlen(hostname);

            printf("     ");

            for (int i = 0; i < tamanho; i++) {
                printf("-");
            }

        } else {

            if (info_pos < 7 &&
                infos[info_pos][0] != '\0') {

                if (info_pos == 5) {

                    printf(
                        "     %s%s (%s):\033[0m %s",
                        distro_color,
                        informacoes[info_pos],
                        network_interface,
                        infos[info_pos]
                    );

                } else if (info_pos == 6) {

                    printf(
                        "     %s%s:\033[0m %s (%s)",
                        distro_color,
                        informacoes[info_pos],
                        infos[info_pos],
                        package_manager
                    );

                } else {

                    printf(
                        "     %s%s:\033[0m %s",
                        distro_color,
                        informacoes[info_pos],
                        infos[info_pos]
                    );
                }

                info_pos++;
            }
        }

        putchar('\n');

        linha++;
    }

    while (info_pos < 7) {

        if (infos[info_pos][0] != '\0') {

            if (info_pos == 5) {

                printf(
                    "     %s%s (%s):\033[0m %s\n",
                    distro_color,
                    informacoes[info_pos],
                    network_interface,
                    infos[info_pos]
                );

            } else if (info_pos == 6) {

                printf(
                    "     %s%s:\033[0m %s (%s)\n",
                    distro_color,
                    informacoes[info_pos],
                    infos[info_pos],
                    package_manager
                );

            } else {

                printf(
                    "     %s%s:\033[0m %s\n",
                    distro_color,
                    informacoes[info_pos],
                    infos[info_pos]
                );
            }
        }

        info_pos++;
    }

    fclose(arquivo);
}


 void show_colors(void)
{
    printf(
        "\033[30m███\033[31m███\033[32m███\033[33m███"
        "\033[34m███\033[35m███\033[36m███\033[37m███"
        "\033[0m\n"
    );
} 
