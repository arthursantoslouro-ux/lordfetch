#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include "asciis.h"
#include "info.h"
#include "show.h"
#include "../build/logos.h"

void help(void) {
    printf(
        "lordfetch - System Information Tool\n"
        "\n"
        "Usage:\n"
        "  lordfetch [option]\n"
        "\n"
        "Options:\n"
        "  -h, --help    Show this help message\n"
        "\n"
        "Example:\n"
        "  lordfetch --help\n"
    );
}


void processar_flags(int argc, char *argv[]) {
  int i = 1;

  while (i < argc) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      help();
     
      break;
      return;
    }
      i++;
  }
}






int main(int argc, char *argv[]) {
  processar_flags(argc, argv);  
  get_system_info();
  get_distro();
  get_cpu(); 

  if (strstr(distro, "fedora") != NULL) {
      show(src_logo_ascii_f_fedora_txt, src_logo_ascii_f_fedora_txt_len);
      return 0;
    }

  else if (strstr(distro, "arch") != NULL) {
      show(src_logo_ascii_a_arch_txt, src_logo_ascii_a_arch_txt_len);
      return 0;
    }



  else if (strstr(distro, "ubuntu") != NULL) {
      show(src_logo_ascii_u_ubuntu_txt, src_logo_ascii_u_ubuntu_txt_len);
      return 0;
    }


  else if (strstr(distro, "debian") != NULL) {
      show(src_logo_ascii_d_debian_txt, src_logo_ascii_d_debian_txt_len);
      return 0;
    }



  else if (strstr(distro, "mint") != NULL) {
    show(src_logo_ascii_l_linuxmint_txt, src_logo_ascii_l_linuxmint_txt_len);
    return 0;
  }



  else if (strstr(distro, "pop") != NULL) {
    show(src_logo_ascii_p_pop_txt, src_logo_ascii_p_pop_txt_len);
    return 0;
  }




  else if (strstr(distro, "gentoo") != NULL) {
    show(src_logo_ascii_g_gentoo_txt, src_logo_ascii_g_gentoo_txt_len);
    return 0;
  }

  else if (strstr(distro, "kali") != NULL) {
    show(src_logo_ascii_k_kali_txt, src_logo_ascii_k_kali_txt_len);
    return 0;
  }



  else {
    printf("lordfetch: unknown distro\n");
    return 0;
  }



return 0;

}









