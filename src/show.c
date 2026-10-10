#include <stdio.h>
#include <string.h>
#include "../headers/show.h"
#include "../headers/info.h"
#include "../headers/asciis.h"

#define LOGO_WIDTH 35

void print_logo_line(const char *line)
{
    int width = 0;

    for (int i = 0; line[i] != '\0';) {
        unsigned char c = (unsigned char)line[i];

        if (c == 0x1b && line[i + 1] == '[') {
            i += 2;

            while (line[i] != '\0' &&
                   !((unsigned char)line[i] >= 0x40 &&
                     (unsigned char)line[i] <= 0x7e)) {
                i++;
            }

            if (line[i] != '\0')
                i++;

            continue;
        }

        if ((c & 0xc0) != 0x80)
            width++;

        i++;
    }

    fputs(line, stdout);

    while (width < LOGO_WIDTH) {
        putchar(' ');
        width++;
    }
}

int line_is_ansi_only(const char *line)
{
    int i = 0;
    int has_ansi = 0;

    while (line[i] != '\0') {
        if ((unsigned char)line[i] != 0x1b)
            return 0;

        i++;

        if (line[i] != '[')
            return 0;

        i++;

        while (line[i] != '\0' &&
               !((unsigned char)line[i] >= 0x40 &&
                 (unsigned char)line[i] <= 0x7e)) {
            i++;
        }

        if (line[i] == '\0')
            return 0;

        i++;
        has_ansi = 1;
    }

    return has_ansi;
}

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
        shell,
        cpu,
        environment,
        ram,
        ip,
        terminal
    };

    const char *informacoes[] = {
        "OS",
        "Host",
        "Kernel",
        "Uptime",
        "Shell",
        "CPU",
        "Environment",
        "Memory",
        "Local IP",
        "Terminal"
    };

    while (ascii(
        logo,
        logo_len,
        linha_ascii,
        sizeof(linha_ascii)
    )) {
        if (line_is_ansi_only(linha_ascii)) {
            printf("%s", linha_ascii);
            continue;
        }

        print_logo_line(linha_ascii);

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

            putchar(' ');

            for (int i = 0; i < tamanho; i++)
                putchar('-');
        } else {
            while (info_pos < 10 &&
                   infos[info_pos][0] == '\0') {
                info_pos++;
            }

            if (info_pos < 10) {
                if (info_pos == 8) {
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
            } else if (info_pos == 10 &&
                       packages[0] != '\0') {
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
            if (info_pos == 8) {
                printf(
                    "%-*s %sLocal IP (%s):\033[0m %s\n",
                    LOGO_WIDTH,
                    "",
                    distro_color,
                    network_interface,
                    ip
                );
            } else {
                printf(
                    "%-*s %s%s:\033[0m %s\n",
                    LOGO_WIDTH,
                    "",
                    distro_color,
                    informacoes[info_pos],
                    infos[info_pos]
                );
            }
        }

        info_pos++;
    }

    printf(
        "%-*s "
        "\033[40m    "
        "\033[41m    "
        "\033[42m    "
        "\033[43m    "
        "\033[44m    "
        "\033[45m    "
        "\033[46m    "
        "\033[47m    "
        "\033[0m\n",
        LOGO_WIDTH,
        ""
    );

    printf(
        "%-*s "
        "\033[100m    "
        "\033[101m    "
        "\033[102m    "
        "\033[103m    "
        "\033[104m    "
        "\033[105m    "
        "\033[106m    "
        "\033[107m    "
        "\033[0m\n",
        LOGO_WIDTH,
        ""
    );
}
