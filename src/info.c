#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include "info.h"
#include <stdlib.h>
#include <pwd.h>

// struct passwd *pw = getpwuid(getuid());


char os[64];
char kernel[128];
char arch[64];
char hostname[128];
char uptime[64];
char distro[64];
char shell[50];


void get_system_info(void)
{
    struct utsname system;


/* pegar o shell */
FILE *shell_file = popen("ps -eo comm= | grep -E '^(bash|zsh|fish)$' | head -n 1", "r");

if (shell_file != NULL) {
    if (fgets(shell, sizeof(shell), shell_file) != NULL) {
        shell[strcspn(shell, "\n")] = '\0';
    } else {
        snprintf(shell, sizeof(shell), "%s", "Unknown");
    }

    pclose(shell_file);
}
  
    /* Kernel, OS e arquitetura */
    if (uname(&system) == 0) {
        snprintf(os, sizeof(os), "%s", system.sysname);
        snprintf(kernel, sizeof(kernel), "%s", system.release);
        snprintf(arch, sizeof(arch), "%s", system.machine);
    } else {
        snprintf(os, sizeof(os), "Unknown");
        snprintf(kernel, sizeof(kernel), "Unknown");
        snprintf(arch, sizeof(arch), "Unknown");
    }

    /* Hostname */
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        snprintf(hostname, sizeof(hostname), "Unknown");
    }

    /* Uptime */
    FILE *file = fopen("/proc/uptime", "r");

    if (file != NULL) {
        double seconds;

        if (fscanf(file, "%lf", &seconds) == 1) {
            int hours = (int)seconds / 3600;
            int minutes = ((int)seconds % 3600) / 60;

            snprintf(
                uptime,
                sizeof(uptime),
                "%dh %dm",
                hours,
                minutes
            );
        } else {
            snprintf(uptime, sizeof(uptime), "Unknown");
        }

        fclose(file);
    } else {
        snprintf(uptime, sizeof(uptime), "Unknown");
    }
}

void get_distro() {
  char line[40];

  FILE *distro_file = fopen("/etc/os-release", "r");
  
  if (distro_file == NULL) {
    printf("lordfetch: this file is null\n");
    return;
    fclose(distro_file);
  }

  while (fgets(line, sizeof(line), distro_file)) {

//       char *resultado = strstr(line, "ID=");
   
    if (strncmp(line, "ID=", 3) == 0) {
        strcpy(distro, line + 3);
        
          size_t  pos = strcspn(distro, "\n");
          distro[pos] = '\0';

    }
  }  
fclose(distro_file);
}

