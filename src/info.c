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
char cpu[128];
char environment[50];
 
void get_system_info(void)
{
    struct utsname system;


/* pegar o shell */

  
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
            snprintf(uptime, sizeof(uptime), "");
        }

        fclose(file);
    } else {
        snprintf(uptime, sizeof(uptime), "");
    }
}

void get_distro() {
  char line[40];

  FILE *distro_file = fopen("/etc/os-release", "r");
  
  if (distro_file == NULL) {
//    printf("lordfetch: this file is null\n");
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

void get_cpu(void)
{
    FILE *file = fopen("/proc/cpuinfo", "r");

    if (file == NULL) {
        snprintf(cpu, sizeof(cpu), "");
        return;
    }

    char line[256];

    while (fgets(line, sizeof(line), file)) {

        if (strncmp(line, "model name", 10) == 0) {
            char *colon = strchr(line, ':');

            if (colon != NULL) {
                snprintf(cpu, sizeof(cpu), "%s", colon + 2);
                cpu[strcspn(cpu, "\n")] = '\0';
            }

            break;
        }

        /*
         * ARM/aarch64 normalmente não possui "model name".
         */
        if (strncmp(line, "Hardware", 8) == 0) {
            char *colon = strchr(line, ':');

            if (colon != NULL) {
                snprintf(cpu, sizeof(cpu), "%s", colon + 2);
                cpu[strcspn(cpu, "\n")] = '\0';
            }

            break;
        }
    }

    fclose(file);

    if (cpu[0] == '\0')
        snprintf(cpu, sizeof(cpu), "");
}
