#include <stdio.h>
#include <string.h>
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
        host,
        kernel,
        uptime,
        distro,
        shell,
        cpu,
        environment,
        ram,
        ip,
    };

    const char *informacoes[] = {
        "OS",
        "Host",
        "Kernel",
        "Uptime",
        "Distro",
        "Shell",
        "CPU",
        "Environment",
        "Memory",
        "Local IP",
    };

    while (ascii(logo, logo_len, linha_ascii, sizeof(linha_ascii))) {

        printf("%-35s", linha_ascii);

        if (linha == 0) {

            printf(
                " %s%s\033[0m@%s%s\033[0m",
                distro_color,
                username,
                distro_color,
                hostname
            );

        } else if (linha == 1) {

            int tamanho =
                strlen(username) +
                1 +
                strlen(hostname);

            printf(" ");

            for (int i = 0; i < tamanho; i++) {
                printf("-");
            }

        } else {

            while (info_pos < 10 &&
                   infos[info_pos][0] == '\0') {

                info_pos++;
            }

            if (info_pos < 10) {

                if (info_pos == 9) {

                    printf(
                        " %sLocal IP (%s):\033[0m %s",
                        distro_color,
                        network_interface,
                        ip
                    );

                } else {

                    printf(
                        " %s%s:\033[0m %s",
                        distro_color,
                        informacoes[info_pos],
                        infos[info_pos]
                    );
                }

                info_pos++;

            } else if (info_pos == 10) {

                printf(
                    " %sPackages:\033[0m %s (%s)",
                    distro_color,
                    packages,
                    package_manager
                );

                info_pos++;
            }
        }

        putchar('\n');
        linha++;
    }

    while (info_pos < 10) {

        if (infos[info_pos][0] != '\0') {

            if (info_pos == 9) {

                printf(
                    "%-35s %sLocal IP (%s):\033[0m %s\n",
                    "",
                    distro_color,
                    network_interface,
                    ip
                );

            } else {

                printf(
                    "%-35s %s%s\033[0m: %s\n",
                    "",
                    distro_color,
                    informacoes[info_pos],
                    infos[info_pos]
                );
            }
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
