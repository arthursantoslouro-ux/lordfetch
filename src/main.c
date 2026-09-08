#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include "asciis.h"
#include "info.h"
#include "show.h"

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



int main(int argc, char *argv[])
{
  processar_flags(argc, argv);  
  get_distro();
  show(); 
  return 0;
}
