#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include "../headers/info.h"
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netinet/in.h>



char os[64];
char kernel[128];
char arch[64];
char hostname[128];
char uptime[64];
char distro[64];
char shell[50];
char cpu[128];
char environment[50];
char ram[64];
char username[64];
char ip[64];

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



void get_ram(void)
{  
    FILE *file = fopen("/proc/meminfo", "r");

    if (file == NULL)
        return;

    char line[128];

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            unsigned long ram_kb;

            if (sscanf(line, "MemTotal: %lu kB", &ram_kb) == 1) {
                double ram_gib = ram_kb / 1024.0 / 1024.0;

                snprintf(ram, sizeof(ram),
                         "%.2f GiB", ram_gib);
            }

            break;
        }
    }

    fclose(file);

}


void get_username(void)
{
    struct passwd *pw = getpwuid(getuid());

    if (pw != NULL)
        snprintf(username, sizeof(username), "%s", pw->pw_name);
}


void get_ip(void)
{
    struct ifaddrs *interfaces;
    struct ifaddrs *interface;

    ip[0] = '\0';

    if (getifaddrs(&interfaces) == -1)
        return;

    for (interface = interfaces;
         interface != NULL;
         interface = interface->ifa_next) {

        if (interface->ifa_addr == NULL)
            continue;

        if (interface->ifa_addr->sa_family != AF_INET)
            continue;

        struct sockaddr_in *addr =
            (struct sockaddr_in *)interface->ifa_addr;

        if (ntohl(addr->sin_addr.s_addr) == INADDR_LOOPBACK)
            continue;

        if (inet_ntop(
                AF_INET,
                &addr->sin_addr,
                ip,
                sizeof(ip)) != NULL) {
            break;
        }
    }

    freeifaddrs(interfaces);
}


void get_shell(void)
{
    const char *shell_env = getenv("SHELL");

    if (shell_env == NULL)
        return;

    const char *nome = strrchr(shell_env, '/');

    if (nome != NULL)
        nome++;
    else
        nome = shell_env;

    snprintf(
        shell,
        sizeof(shell),
        "%s",
        nome
    );
}
