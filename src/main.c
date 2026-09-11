#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include "asciis.h"
#include "info.h"
#include "show.h"
#include "../build/logos.h"
#include "environment.h"

void help(void) {
    printf(
        "lordfetch - System Information Tool\n"
        "\n"
        "Usage:\n"
        "  lordfetch [option]\n"
        "\n"
        "Options:\n"
        "  -h, --help       Show this help message\n"
        "  -v, --version    Show version information\n"
        "\n"
        "Example:\n"
        "  lordfetch --help\n"
    );
}


int processar_flags(int argc, char *argv[]) {
    int i = 1;

    while (i < argc) {

        if (strcmp(argv[i], "-h") == 0 ||
            strcmp(argv[i], "--help") == 0) {

            help();

            return 1;
        }

        if (strcmp(argv[i], "-v") == 0 ||
            strcmp(argv[i], "--version") == 0) {

            printf("lordfetch 0.1.0\n");

            return 1;
        }

        i++;
    }

    return 0;
}


int main(int argc, char *argv[]) {

    if (processar_flags(argc, argv))
        return 0;

    get_system_info();
    get_distro();
    get_cpu();
    get_ram();


    if (is_android()) {

        if (is_termux()) {

            snprintf(
                environment,
                sizeof(environment),
                "%s",
                "android \033[1;33m(termux)\033[0m"
            );

            show(
                src_logo_ascii_a_android_txt,
                src_logo_ascii_a_android_txt_len
            );

        } else {

            snprintf(
                environment,
                sizeof(environment),
                "%s",
                "android"
            );

            show(
                src_logo_ascii_a_android_txt,
                src_logo_ascii_a_android_txt_len
            );
        }

        return 0;
    }


    if (strstr(distro, "fedora") != NULL) {

        show(
            src_logo_ascii_f_fedora_txt,
            src_logo_ascii_f_fedora_txt_len
        );

        return 0;
    }

    else if (strstr(distro, "arch") != NULL) {

        show(
            src_logo_ascii_a_arch_txt,
            src_logo_ascii_a_arch_txt_len
        );

        return 0;
    }

    else if (strstr(distro, "ubuntu") != NULL) {

        show(
            src_logo_ascii_u_ubuntu_txt,
            src_logo_ascii_u_ubuntu_txt_len
        );

        return 0;
    }

    else if (strstr(distro, "debian") != NULL) {

        show(
            src_logo_ascii_d_debian_txt,
            src_logo_ascii_d_debian_txt_len
        );

        return 0;
    }

    else if (strstr(distro, "mint") != NULL) {

        show(
            src_logo_ascii_l_linuxmint_txt,
            src_logo_ascii_l_linuxmint_txt_len
        );

        return 0;
    }

    else if (strstr(distro, "pop") != NULL) {

        show(
            src_logo_ascii_p_pop_txt,
            src_logo_ascii_p_pop_txt_len
        );

        return 0;
    }

    else if (strstr(distro, "gentoo") != NULL) {

        show(
            src_logo_ascii_g_gentoo_txt,
            src_logo_ascii_g_gentoo_txt_len
        );

        return 0;
    }

    else if (strstr(distro, "kali") != NULL) {

        show(
            src_logo_ascii_k_kali_txt,
            src_logo_ascii_k_kali_txt_len
        );

        return 0;
    }

    else {

        printf("lordfetch: unknown distro\n");

        return 0;
    }


    return 0;
}
