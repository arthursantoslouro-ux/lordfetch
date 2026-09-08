#include <stdio.h>
#include "asciis.h"
#include <string.h>
#include "../build/logos.h"
#include "info.h"

void ascii() {
  get_distro();
  
  if (strstr(distro, "debian") != NULL) {
    fwrite(src_logo_ascii_d_debian_txt, src_logo_ascii_d_debian_txt_len, 1, stdout);
  
  }


  else if (strstr(distro, "arch") != NULL) {
    fwrite(src_logo_ascii_a_arch_txt, src_logo_ascii_a_arch_txt_len, 1, stdout);
  }


}



