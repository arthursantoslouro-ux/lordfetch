#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "../headers/asciis.h"
#include "../headers/info.h"

#define INFO_COUNT 11
#define LOGO_GAP 2

char linha_logo[4096];

int ascii(unsigned char *logo, unsigned int logo_len,
          char *linha, size_t tamanho)
{
    static size_t pos = 0;
    size_t i = 0;

    if (tamanho == 0)
        return 0;

    if (pos >= logo_len) {
        pos = 0;
        return 0;
    }

    while (pos < logo_len && i < tamanho - 1) {
        char c = logo[pos++];

        if (c == '\n')
            break;

        linha[i++] = c;
    }

    linha[i] = '\0';
    return 1;
}

/* Remove espaços, tabs, CR e LF do final da linha. */
static void trim_line(char *line)
{
    size_t len = strlen(line);

    while (len > 0 &&
           (line[len - 1] == ' ' ||
            line[len - 1] == '\t' ||
            line[len - 1] == '\r' ||
            line[len - 1] == '\n')) {
        line[--len] = '\0';
    }
}

/* Calcula a largura visível, ignorando sequências ANSI CSI. */
static size_t visible_width(const char *line)
{
    size_t width = 0;
    size_t i = 0;

    while (line[i] != '\0') {
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

        /* Conta cada caractere UTF-8 uma vez. */
        if ((c & 0xc0) != 0x80)
            width++;

        i++;
    }

    return width;
}

static const char *get_info(size_t index)
{
    static const char *infos[INFO_COUNT] = {
        os,
        host,
        kernel,
        uptime,
        shell,
        cpu,
        environment,
        ram,
        ip,
        terminal,
        packages
    };

    return index < INFO_COUNT ? infos[index] : "";
}

static void print_info(size_t index)
{
    static const char *labels[INFO_COUNT] = {
        "OS",
        "Host",
        "Kernel",
        "Uptime",
        "Shell",
        "CPU",
        "Environment",
        "Memory",
        "Local IP",
        "Terminal",
        "Packages"
    };

    const char *value = get_info(index);

    if (index >= INFO_COUNT || value[0] == '\0')
        return;

    if (index == 8) {
        printf(
            "%s%s (%s):\033[0m %s",
            distro_color,
            labels[index],
            network_interface,
            value
        );
    } else if (index == 10) {
        printf(
            "%s%s:\033[0m %s (%s)",
            distro_color,
            labels[index],
            value,
            package_manager
        );
    } else {
        printf(
            "%s%s:\033[0m %s",
            distro_color,
            labels[index],
            value
        );
    }
}

void show_logo(int argc, char *argv[])
{
    if (argc < 3 || argv[2] == NULL)
        return;

    if (strstr(argv[2], "archlinux") != NULL) {
        snprintf(distro, sizeof(distro), "archlinux");
        snprintf(
            distro_color,
            sizeof(distro_color),
            "\033[1;36m"
        );
    }

    FILE *arquivo = fopen(argv[2], "r");

    if (arquivo == NULL) {
        fprintf(
            stderr,
            "lordfetch: It wasn't possible to open the logo\n"
        );
        return;
    }

    char line_buffer[4096];
    size_t max_width = 0;

    /*
     * Primeira passagem: calcula a maior largura visível.
     * Espaços e tabs finais não entram na medida.
     */
    while (fgets(line_buffer, sizeof(line_buffer), arquivo)) {
        trim_line(line_buffer);

        size_t width = visible_width(line_buffer);

        if (width > max_width)
            max_width = width;
    }

    rewind(arquivo);

    size_t info_pos = 0;
    size_t line_number = 0;

    /*
     * Segunda passagem: imprime o logo e as informações.
     */
    while (fgets(line_buffer, sizeof(line_buffer), arquivo)) {
        trim_line(line_buffer);

        size_t width = visible_width(line_buffer);

        fputs(line_buffer, stdout);

        for (size_t i = width; i < max_width + LOGO_GAP; i++)
            putchar(' ');

        if (line_number == 0) {
            printf(
                "%s%s@%s\033[0m",
                distro_color,
                username,
                hostname
            );
        } else if (line_number == 1) {
            size_t banner_width =
                strlen(username) + 1 + strlen(hostname);

            for (size_t i = 0; i < banner_width; i++)
                putchar('-');
        } else {
            while (info_pos < INFO_COUNT &&
                   get_info(info_pos)[0] == '\0') {
                info_pos++;
            }

            if (info_pos < INFO_COUNT)
                print_info(info_pos++);
        }

        putchar('\n');
        line_number++;
    }

    /*
     * Imprime os campos restantes na mesma coluna.
     */
    while (info_pos < INFO_COUNT) {
        if (get_info(info_pos)[0] != '\0') {
            for (size_t i = 0; i < max_width + LOGO_GAP; i++)
                putchar(' ');

            print_info(info_pos);
            putchar('\n');
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
