#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../headers/asciis.h"
#include "../headers/info.h"
#include "../headers/show.h"
#include "../headers/environment.h"
#include "../headers/lordfetch.h"
#include "../build/logos.h"

void help(void)
{
    printf(
        "lordfetch - System Information Tool\n"
        "\n"
        "Usage:\n"
        "  lordfetch [option]\n"
        "\n"
        "Options:\n"
        "  -h, --help       Show this help message\n"
        "  -v, --version    Show version information\n"
        "  -c               Update system information continuously\n"
        "  --logo <name>    Use a logo or custom ASCII/ANSI file\n"
        "\n"
        "Examples:\n"
        "  lordfetch --help\n"
        "  lordfetch -c\n"
        "  lordfetch --logo archlinux\n"
        "  lordfetch --logo ~/logo.ansi\n"
    );
}

static void atualizar_info(void)
{
    get_system_info();
    get_distro();
    get_cpu();
    get_ram();
    get_username();
    get_ip();
    get_shell();
    get_packages();
    get_distro_color();
    get_os_info();
    get_host();
}

static void show_system(void)
{
    if (is_android()) {
        show(
            src_logo_ascii_a_android_txt,
            src_logo_ascii_a_android_txt_len
        );
    }
    else if (strstr(distro, "fedora") != NULL) {
        show(
            src_logo_ascii_f_fedora_txt,
            src_logo_ascii_f_fedora_txt_len
        );
    }
    else if (strstr(distro, "blackarch") != NULL) {
        show(
            src_logo_ascii_b_blackarch_txt,
            src_logo_ascii_b_blackarch_txt_len
        );
    }
    else if (strstr(distro, "arch") != NULL) {
        show(
            src_logo_ascii_a_arch_txt,
            src_logo_ascii_a_arch_txt_len
        );
    }
    else if (strstr(distro, "ubuntu") != NULL) {
        show(
            src_logo_ascii_u_ubuntu_txt,
            src_logo_ascii_u_ubuntu_txt_len
        );
    }
    else if (strstr(distro, "debian") != NULL) {
        show(
            src_logo_ascii_d_debian_txt,
            src_logo_ascii_d_debian_txt_len
        );
    }
    else if (strstr(distro, "mint") != NULL) {
        show(
            src_logo_ascii_l_linuxmint_txt,
            src_logo_ascii_l_linuxmint_txt_len
        );
    }
    else if (strstr(distro, "pop") != NULL) {
        show(
            src_logo_ascii_p_pop_txt,
            src_logo_ascii_p_pop_txt_len
        );
    }
    else if (strstr(distro, "gentoo") != NULL) {
        show(
            src_logo_ascii_g_gentoo_txt,
            src_logo_ascii_g_gentoo_txt_len
        );
    }
    else if (strstr(distro, "kali") != NULL) {
        show(
            src_logo_ascii_k_kali_txt,
            src_logo_ascii_k_kali_txt_len
        );
    }
    else if (strstr(distro, "alpine") != NULL) {
        show(
            src_logo_ascii_a_alpine_txt,
            src_logo_ascii_a_alpine_txt_len
        );
    }
    else {
        printf("lordfetch: unknown distro\n");
    }
}

int processar_flags(int argc, char *argv[])
{
    if (argc < 2)
        return 0;

    if (strcmp(argv[1], "-h") == 0 ||
        strcmp(argv[1], "--help") == 0) {
        help();
        return 1;
    }

    if (strcmp(argv[1], "-v") == 0 ||
        strcmp(argv[1], "--version") == 0) {
        printf("lordfetch %s\n", LORDFETCH_VERSION);
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0) {
        while (1) {
            printf("\033[H\033[J");

            atualizar_info();
            show_system();

            fflush(stdout);
            sleep(1);
        }

        return 1;
    }

    if (strcmp(argv[1], "--logo") == 0) {
        if (argc < 3) {
            printf(
                "lordfetch: --logo requires a name or file\n"
            );
            return 1;
        }

        if (strcmp(argv[2], "android") == 0) {
            snprintf(
                distro_color,
                sizeof(distro_color),
                "\033[32m"
            );

            show(
                src_logo_ascii_a_android_txt,
                src_logo_ascii_a_android_txt_len
            );

            return 1;
        }

        if (strcmp(argv[2], "archlinux") == 0) {
            snprintf(distro, sizeof(distro), "archlinux");
            snprintf(distro_color, sizeof(distro_color), "\033[1;36m");

            show(
                src_logo_ascii_a_arch_txt,
                src_logo_ascii_a_arch_txt_len
            );
            return 1;
        }

        if (strcmp(argv[2], "blackarch") == 0) {
            snprintf(distro, sizeof(distro), "blackarch");
            snprintf(distro_color, sizeof(distro_color), "\033[1;36m");

            show(
                src_logo_ascii_b_blackarch_txt,
                src_logo_ascii_b_blackarch_txt_len
            );
            return 1;
        }

        if (strcmp(argv[2], "debian") == 0) {
            snprintf(distro, sizeof(distro), "debian");
            snprintf(distro_color, sizeof(distro_color), "\033[1;31m");

            show(
                src_logo_ascii_d_debian_txt,
                src_logo_ascii_d_debian_txt_len
            );
            return 1;
        }

        if (strcmp(argv[2], "ubuntu") == 0) {
            snprintf(distro, sizeof(distro), "ubuntu");
            snprintf(distro_color, sizeof(distro_color), "\033[1;33m");

            show(
                src_logo_ascii_u_ubuntu_txt,
                src_logo_ascii_u_ubuntu_txt_len
            );
            return 1;
        }

        if (strcmp(argv[2], "fedora") == 0) {
            snprintf(distro, sizeof(distro), "fedora");
            snprintf(distro_color, sizeof(distro_color), "\033[1;34m");

            show(
                src_logo_ascii_f_fedora_txt,
                src_logo_ascii_f_fedora_txt_len
            );
            return 1;
        }

        if (strcmp(argv[2], "mint") == 0) {
            snprintf(distro, sizeof(distro), "mint");
            snprintf(distro_color, sizeof(distro_color), "\033[1;32m");

            show(
                src_logo_ascii_l_linuxmint_txt,
                src_logo_ascii_l_linuxmint_txt_len
            );
            return 1;
        }

        if (strcmp(argv[2], "pop") == 0) {
            snprintf(distro, sizeof(distro), "pop");
            snprintf(distro_color, sizeof(distro_color), "\033[1;36m");

            show(
                src_logo_ascii_p_pop_txt,
                src_logo_ascii_p_pop_txt_len
            );
            return 1;
        }

        if (strcmp(argv[2], "gentoo") == 0) {
            snprintf(distro, sizeof(distro), "gentoo");
            snprintf(distro_color, sizeof(distro_color), "\033[1;35m");

            show(
                src_logo_ascii_g_gentoo_txt,
                src_logo_ascii_g_gentoo_txt_len
            );
            return 1;
        }

        if (strcmp(argv[2], "kali") == 0) {
            snprintf(distro, sizeof(distro), "kali");
            snprintf(distro_color, sizeof(distro_color), "\033[1;36m");

            show(
                src_logo_ascii_k_kali_txt,
                src_logo_ascii_k_kali_txt_len
            );
            return 1;
        }

        if (strcmp(argv[2], "alpine") == 0) {
            snprintf(distro, sizeof(distro), "alpine");
            snprintf(distro_color, sizeof(distro_color), "\033[1;35m");

            show(
                src_logo_ascii_a_alpine_txt,
                src_logo_ascii_a_alpine_txt_len
            );
            return 1;
        }

        show_logo(argc, argv);
        return 1;
    }

    printf("lordfetch: unknown option '%s'\n", argv[1]);
    return 1;
}

int main(int argc, char *argv[])
{
    atualizar_info();

    if (processar_flags(argc, argv))
        return 0;

    show_system();

    return 0;
}
