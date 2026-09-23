#include <stdio.h>
#include <string.h>
#include "../headers/asciis.h"
#include "../headers/info.h"
#include "../headers/show.h"
#include "../build/logos.h"
#include "../headers/environment.h"
#include "../headers/lordfetch.h"

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
        "  --logo <file>    Use a custom ASCII/ANSI logo\n"
        "\n"
        "Examples:\n"
        "  lordfetch --help\n"
        "  lordfetch --logo ~/logo.ansi\n"
    );
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

    if (strcmp(argv[1], "--logo") == 0) {

        if (argc < 3) {
            printf("lordfetch: --logo requires a file\n");
            return 1;
        }

        show_logo(argc, argv);
        return 1;
    }

    printf(
        "lordfetch: unknown option '%s'\n",
        argv[1]
    );

    return 1;
}


int main(int argc, char *argv[]) {



   /*
     * Coleta as informações do sistema.
     */
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
        
    if (processar_flags(argc, argv))
    return 0;

    /*
     * Android
     */
    if (is_android()) {

        show(
            src_logo_ascii_a_android_txt,
            src_logo_ascii_a_android_txt_len
        );

        return 0;
    }





    /*
     * Fedora
     */
    if (strstr(distro, "fedora") != NULL) {

        show(
            src_logo_ascii_f_fedora_txt,
            src_logo_ascii_f_fedora_txt_len
        );

        return 0;
    }



if (strstr(distro, "blackarch") != NULL) {

    show(
        src_logo_ascii_b_blackarch_txt,
        src_logo_ascii_b_blackarch_txt_len
    );

    return 0;
}




    /*
     * Arch Linux
     */
    if (strstr(distro, "arch") != NULL) {

        show(
            src_logo_ascii_a_arch_txt,
            src_logo_ascii_a_arch_txt_len
        );

        return 0;
    }


    /*
     * Ubuntu
     */
    if (strstr(distro, "ubuntu") != NULL) {

        show(
            src_logo_ascii_u_ubuntu_txt,
            src_logo_ascii_u_ubuntu_txt_len
        );

        return 0;
    }


    /*
     * Debian
     */
    if (strstr(distro, "debian") != NULL) {

        show(
            src_logo_ascii_d_debian_txt,
            src_logo_ascii_d_debian_txt_len
        );

        return 0;
    }


    /*
     * Linux Mint
     */
    if (strstr(distro, "mint") != NULL) {

        show(
            src_logo_ascii_l_linuxmint_txt,
            src_logo_ascii_l_linuxmint_txt_len
        );

        return 0;
    }


    /*
     * Pop!_OS
     */
    if (strstr(distro, "pop") != NULL) {

        show(
            src_logo_ascii_p_pop_txt,
            src_logo_ascii_p_pop_txt_len
        );

        return 0;
    }


    /*
     * Gentoo
     */
    if (strstr(distro, "gentoo") != NULL) {

        show(
            src_logo_ascii_g_gentoo_txt,
            src_logo_ascii_g_gentoo_txt_len
        );

        return 0;
    }


    /*
     * Kali Linux
     */
    if (strstr(distro, "kali") != NULL) {

        show(
            src_logo_ascii_k_kali_txt,
            src_logo_ascii_k_kali_txt_len
        );

        return 0;
    }

  /*
  * alpine 
    */
    

   if (strstr(distro, "alpine") != NULL) {

        show(src_logo_ascii_a_alpine_txt, src_logo_ascii_a_alpine_txt_len);

        return 0;
    }


  



    printf(
        "lordfetch: unknown distro\n"
    );

    return 0;
}

