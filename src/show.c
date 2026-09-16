#include <stdio.h>
#include "../headers/show.h"
#include "../headers/info.h"
#include "../headers/asciis.h"

void show(unsigned char *logo, unsigned int logo_len)
{
    char linha_ascii[130];
    int info_pos = 0;
    int linha = 0;

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
        ip,
        packages
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
        "ip",
        "packages"
    };

    while (ascii(logo, logo_len, linha_ascii, sizeof(linha_ascii))) {

        printf("%-35s", linha_ascii);

        if (linha == 0) {

            printf(" \033[1;32m%s@%s\033[0m",
                   username,
                   hostname);

        } else if (linha == 1) {

            printf(" ---------------------------");

        } else {

            while (info_pos < 11 &&
                   infos[info_pos][0] == '\0') {
                info_pos++;
            }

            if (info_pos < 11) {

                printf(
                    " %s%s:\033[0m %s",
                    distro_color,
                    informacoes[info_pos],
                    infos[info_pos]
                );

                info_pos++;
            }
        }

        putchar('\n');
        linha++;
    }

    while (info_pos < 11) {

        if (infos[info_pos][0] != '\0') {

            printf(
                "%-35s %s%s:\033[0m %s\n",
                "",
                distro_color,
                informacoes[info_pos],
                infos[info_pos]
            );
        }

        info_pos++;
    }

    /*
     * Cores ANSI normais
     */
    printf(
        "%-35s "
        "\033[40m    "
        "\033[41m    "
        "\033[42m    "
        "\033[43m    "
        "\033[44m    "
        "\033[45m    "
        "\033[46m    "
        "\033[47m    "
        "\033[0m\n",
        ""
    );

    /*
     * Cores ANSI brilhantes
     */
    printf(
        "%-35s "
        "\033[100m    "
        "\033[101m    "
        "\033[102m    "
        "\033[103m    "
        "\033[104m    "
        "\033[105m    "
        "\033[106m    "
        "\033[107m    "
        "\033[0m\n",
        ""
    );
}
