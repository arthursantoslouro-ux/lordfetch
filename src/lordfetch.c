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
        "  lordfetch [options]\n"
        "\n"
        "Options:\n"
        "  -h, --help       Show this help message\n"
        "  -v, --version    Show version information\n"
        "  -w, --watch      Update system information continuously\n"
        "  -l, --logo <name>    Use a logo or custom ASCII/ANSI file\n"
        "\n"
        "Examples:\n"
        "  lordfetch --help\n"
        "  lordfetch --version\n"
        "  lordfetch --watch\n"
        "  lordfetch --logo archlinux\n"
        "  lordfetch --logo debian --watch\n"
        "  lordfetch --logo ~/logo.ansi\n"
    );
}

static void update_info(void)
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
    get_terminal();
}

static int show_logo_by_name(const char *name)
{
    if (strcmp(name, "android") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[32m");
        show(src_logo_ascii_a_android_txt,
             src_logo_ascii_a_android_txt_len);
    }
    else if (strcmp(name, "archlinux") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[1;36m");
        show(src_logo_ascii_a_arch_txt,
             src_logo_ascii_a_arch_txt_len);
    }
    else if (strcmp(name, "blackarch") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[1;36m");
        show(src_logo_ascii_b_blackarch_txt,
             src_logo_ascii_b_blackarch_txt_len);
    }
    else if (strcmp(name, "debian") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[1;31m");
        show(src_logo_ascii_d_debian_txt,
             src_logo_ascii_d_debian_txt_len);
    }
    else if (strcmp(name, "ubuntu") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[1;33m");
        show(src_logo_ascii_u_ubuntu_txt,
             src_logo_ascii_u_ubuntu_txt_len);
    }
    else if (strcmp(name, "fedora") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[1;34m");
        show(src_logo_ascii_f_fedora_txt,
             src_logo_ascii_f_fedora_txt_len);
    }
    else if (strcmp(name, "mint") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[1;32m");
        show(src_logo_ascii_l_linuxmint_txt,
             src_logo_ascii_l_linuxmint_txt_len);
    }
    else if (strcmp(name, "pop") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[1;36m");
        show(src_logo_ascii_p_pop_txt,
             src_logo_ascii_p_pop_txt_len);
    }
    else if (strcmp(name, "gentoo") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[1;35m");
        show(src_logo_ascii_g_gentoo_txt,
             src_logo_ascii_g_gentoo_txt_len);
    }
    else if (strcmp(name, "kali") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[1;36m");
        show(src_logo_ascii_k_kali_txt,
             src_logo_ascii_k_kali_txt_len);
    }
    else if (strcmp(name, "alpine") == 0) {
        snprintf(distro_color, sizeof(distro_color), "\033[1;35m");
        show(src_logo_ascii_a_alpine_txt,
             src_logo_ascii_a_alpine_txt_len);
    }
    else {
        return 0;
    }

    return 1;
}

static void show_system(const char *logo_name)
{
    if (logo_name != NULL) {
        if (!show_logo_by_name(logo_name)) {
            char *logo_argv[] = {
                "lordfetch", "--logo", (char *)logo_name, NULL
            };

            show_logo(3, logo_argv);
        }

        return;
    }

    if (is_android()) {
        show(src_logo_ascii_a_android_txt,
             src_logo_ascii_a_android_txt_len);
    }
    else if (strstr(distro, "fedora") != NULL) {
        show(src_logo_ascii_f_fedora_txt,
             src_logo_ascii_f_fedora_txt_len);
    }
    else if (strstr(distro, "blackarch") != NULL) {
        show(src_logo_ascii_b_blackarch_txt,
             src_logo_ascii_b_blackarch_txt_len);
    }
    else if (strstr(distro, "arch") != NULL) {
        show(src_logo_ascii_a_arch_txt,
             src_logo_ascii_a_arch_txt_len);
    }
    else if (strstr(distro, "ubuntu") != NULL) {
        show(src_logo_ascii_u_ubuntu_txt,
             src_logo_ascii_u_ubuntu_txt_len);
    }
    else if (strstr(distro, "debian") != NULL) {
        show(src_logo_ascii_d_debian_txt,
             src_logo_ascii_d_debian_txt_len);
    }
    else if (strstr(distro, "mint") != NULL) {
        show(src_logo_ascii_l_linuxmint_txt,
             src_logo_ascii_l_linuxmint_txt_len);
    }
    else if (strstr(distro, "pop") != NULL) {
        show(src_logo_ascii_p_pop_txt,
             src_logo_ascii_p_pop_txt_len);
    }
    else if (strstr(distro, "gentoo") != NULL) {
        show(src_logo_ascii_g_gentoo_txt,
             src_logo_ascii_g_gentoo_txt_len);
    }
    else if (strstr(distro, "kali") != NULL) {
        show(src_logo_ascii_k_kali_txt,
             src_logo_ascii_k_kali_txt_len);
    }
    else if (strstr(distro, "alpine") != NULL) {
        show(src_logo_ascii_a_alpine_txt,
             src_logo_ascii_a_alpine_txt_len);
    }
    else {
      show(src_logo_ascii___fallback_txt, src_logo_ascii___fallback_txt_len);
   }
}

int process_flags(int argc, char *argv[])
{
    const char *logo_name = NULL;
    int continuous = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 ||
            strcmp(argv[i], "--help") == 0) {
            help();
            return 1;
        }

        if (strcmp(argv[i], "-v") == 0 ||
            strcmp(argv[i], "--version") == 0) {
            printf("lordfetch %s\n", LORDFETCH_VERSION);
            return 1;
        }

        if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--watch") == 0) {
            continuous = 1;
            continue;
        }

        if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--logo") == 0) {
            if (i + 1 >= argc ||
                argv[i + 1][0] == '-') {
                fprintf(stderr,
                        "lordfetch: -l/--logo requires a name or file\n");
                return 1;
            }

            logo_name = argv[++i];
            continue;
        }

        fprintf(stderr,
                "lordfetch: unknown option '%s'\n",
                argv[i]);
        return 1;
    }

    if (continuous) {
        while (1) {
            printf("\033[H\033[J");

            update_info();
            show_system(logo_name);

            fflush(stdout);
            sleep(1);
        }
    }

    if (logo_name != NULL) {
        show_system(logo_name);
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    update_info();

    if (process_flags(argc, argv))
        return 0;

    show_system(NULL);

    return 0;
}
