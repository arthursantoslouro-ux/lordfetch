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
#include "../headers/environment.h"


char os[64];
char kernel[128];
char hostname[128];
char uptime[64];
char distro[64];
char shell[50];
char cpu[128];
char environment[50];
char ram[64];
char username[64];
char ip[64];
char packages[64];
char package_manager[32];
char distro_color[16];
char host[128];
char network_interface[32];

void get_system_info(void)
{
    struct utsname system;


/* pegar o shell */

  
    /* Kernel, OS e arquitetura */
    if (uname(&system) == 0) {
        snprintf(os, sizeof(os), "%s", system.sysname);
        snprintf(kernel, sizeof(kernel), "%s %s", system.sysname, system.release);
  //snprintf(arch, sizeof(arch), "%s", system.machine);
    } else {
        snprintf(os, sizeof(os), "Unknown");
        snprintf(kernel, sizeof(kernel), "Unknown");
    //    snprintf(arch, sizeof(arch), "Unknown");
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


void get_distro_color(void)
{
    if (strstr(distro, "arch") != NULL) {

        snprintf(
            distro_color,
            sizeof(distro_color),
            "\033[1;94m"
        );

    } else if (strstr(distro, "ubuntu") != NULL) {

        snprintf(
            distro_color,
            sizeof(distro_color),
            "\033[1;33m"
        );

    } else if (strstr(distro, "debian") != NULL) {

        snprintf(
            distro_color,
            sizeof(distro_color),
            "\033[1;31m"
        );

    } else if (strstr(distro, "fedora") != NULL) {

        snprintf(
            distro_color,
            sizeof(distro_color),
            "\033[1;34m"
        );

    } else if (strstr(distro, "mint") != NULL) {

        snprintf(
            distro_color,
            sizeof(distro_color),
            "\033[1;32m"
        );

    } else if (strstr(distro, "pop") != NULL) {

        snprintf(
            distro_color,
            sizeof(distro_color),
            "\033[1;36m"
        );

    } else if (strstr(distro, "gentoo") != NULL) {

        snprintf(
            distro_color,
            sizeof(distro_color),
            "\033[1;35m"
        );

    } else if (strstr(distro, "kali") != NULL) {

        snprintf(
            distro_color,
            sizeof(distro_color),
            "\033[1;36m"
        );

    }

    else if (strstr(distro, "alpine") != NULL) {
      snprintf(distro_color, sizeof(distro_color), "\033[1;35m");
    }

     else {

        snprintf(
            distro_color,
            sizeof(distro_color),
            "\033[1;32m"
        );
    }
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

    unsigned long total_kb = 0;
    unsigned long available_kb = 0;

    while (fgets(line, sizeof(line), file)) {

        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line, "MemTotal: %lu kB", &total_kb);
        }

        else if (strncmp(line, "MemAvailable:", 13) == 0) {
            sscanf(line, "MemAvailable: %lu kB", &available_kb);
        }

        if (total_kb > 0 && available_kb > 0)
            break;
    }

    fclose(file);

    if (total_kb == 0)
        return;

    unsigned long used_kb = total_kb - available_kb;

    double total_gib = total_kb / 1024.0 / 1024.0;
    double used_gib = used_kb / 1024.0 / 1024.0;

    int percent = (int)((used_kb * 100.0) / total_kb);

    snprintf(
        ram,
        sizeof(ram),
        "%.2f GiB / %.2f GiB (\033[33m%d%%\033[0m)",
        used_gib,
        total_gib,
        percent
    );
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
    network_interface[0] = '\0';

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

        char address[INET_ADDRSTRLEN];

        if (inet_ntop(
                AF_INET,
                &addr->sin_addr,
                address,
                sizeof(address)) == NULL)
            continue;

        struct sockaddr_in *netmask =
            (struct sockaddr_in *)interface->ifa_netmask;

        unsigned int prefix = 0;

        if (netmask != NULL) {
            uint32_t mask = ntohl(netmask->sin_addr.s_addr);

            while (mask) {
                prefix += mask & 1;
                mask >>= 1;
            }
        }

        snprintf(
            network_interface,
            sizeof(network_interface),
            "%s",
            interface->ifa_name
        );

        snprintf(
            ip,
            sizeof(ip),
            "%s/%u",
            address,
            prefix
        );

        break;
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

    char command[128];

    snprintf(
        command,
        sizeof(command),
        "%s --version 2>/dev/null",
        nome
    );

    FILE *file = popen(command, "r");

    if (file == NULL) {
        snprintf(shell, sizeof(shell), "%s", nome);
        return;
    }

    char version[256];

    if (fgets(version, sizeof(version), file) == NULL) {
        snprintf(shell, sizeof(shell), "%s", nome);
        pclose(file);
        return;
    }

    pclose(file);

    version[strcspn(version, "\n")] = '\0';

    char *version_number = NULL;

    if (strcmp(nome, "zsh") == 0) {
        /*
         * zsh 5.9 (aarch64...)
         */
        char *p = strchr(version, ' ');

        if (p != NULL)
            version_number = p + 1;
    }

    else if (strcmp(nome, "bash") == 0) {
        /*
         * GNU bash, version 5.2.37(1)-release
         */
        char *p = strstr(version, "version ");

        if (p != NULL)
            version_number = p + 8;
    }

    else if (strcmp(nome, "fish") == 0) {
        /*
         * fish, version 4.0.1
         */
        char *p = strstr(version, "version ");

        if (p != NULL)
            version_number = p + 8;
    }

    if (version_number != NULL) {
        /*
         * Remove tudo depois do próximo espaço.
         */
        char *space = strchr(version_number, ' ');

        if (space != NULL)
            *space = '\0';

        /*
         * Bash pode retornar:
         * 5.2.37(1)-release
         *
         * Remove o que vem depois do primeiro '('.
         */
        char *parenthesis = strchr(version_number, '(');

        if (parenthesis != NULL)
            *parenthesis = '\0';

        snprintf(
            shell,
            sizeof(shell),
            "%s %s",
            nome,
            version_number
        );
    }
    else {
        snprintf(
            shell,
            sizeof(shell),
            "%s",
            nome
        );
    }
}


void get_packages(void)
{
    FILE *file = NULL;

    /*
     * Debian / Ubuntu / Mint / Kali
     */
    file = popen(
        "command -v dpkg-query >/dev/null 2>&1 && "
        "dpkg-query -f '${binary:Package}\\n' -W 2>/dev/null | wc -l",
        "r"
    );

    if (file != NULL) {
      snprintf(package_manager, sizeof(package_manager), "%s", "dpkg");
      if (fgets(packages, sizeof(packages), file) != NULL &&
            atoi(packages) > 0) {
            packages[strcspn(packages, "\n")] = '\0';
            pclose(file);
            return;
        }

        pclose(file);
    }

    /*
     * Arch / Manjaro
     */
    file = popen(
        "command -v pacman >/dev/null 2>&1 && "
        "pacman -Qq 2>/dev/null | wc -l",
        "r"
    );

    if (file != NULL) {
        snprintf(package_manager, sizeof(package_manager), "%s", "pacman");  
        if (fgets(packages, sizeof(packages), file) != NULL &&
            atoi(packages) > 0) {
            packages[strcspn(packages, "\n")] = '\0';
            pclose(file);
            return;
        }

        pclose(file);
    }

    /*
     * Fedora / RHEL / openSUSE
     */
    file = popen(
        "command -v rpm >/dev/null 2>&1 && "
        "rpm -qa 2>/dev/null | wc -l",
        "r"
    );

    if (file != NULL) {
        snprintf(package_manager, sizeof(package_manager), "%s", "rpm");
        if (fgets(packages, sizeof(packages), file) != NULL &&
            atoi(packages) > 0) {
            packages[strcspn(packages, "\n")] = '\0';
            pclose(file);
            return;
        }

        pclose(file);
    }

    /*
     * Alpine
     */
    file = popen(
        "command -v apk >/dev/null 2>&1 && "
        "apk info 2>/dev/null | wc -l",
        "r"
    );

    if (file != NULL) {
        snprintf(package_manager, sizeof(package_manager), "%s", "apk");
        if (fgets(packages, sizeof(packages), file) != NULL &&
            atoi(packages) > 0) {
            packages[strcspn(packages, "\n")] = '\0';
            pclose(file);
            return;
        }

        pclose(file);
    }

    packages[0] = '\0';
}

void get_os_info(void)
{
    struct utsname info;

    if (uname(&info) != 0)
        return;

    if (is_android()) {

        FILE *file = popen(
            "getprop ro.build.version.release",
            "r"
        );

        if (file == NULL)
            return;

        char version[16];

        if (fgets(version, sizeof(version), file) != NULL) {

            version[strcspn(version, "\n")] = '\0';

            const char *codename = "Unknown";

            if (strcmp(version, "17") == 0)
                codename = "Cinnamon Bun";
            else if (strcmp(version, "16") == 0)
                codename = "Baklava";
            else if (strcmp(version, "15") == 0)
                codename = "Vanilla Ice Cream";
            else if (strcmp(version, "14") == 0)
                codename = "Upside Down Cake";
            else if (strcmp(version, "13") == 0)
                codename = "Tiramisu";
            else if (strcmp(version, "12") == 0)
                codename = "Snow Cone";
            else if (strcmp(version, "11") == 0)
                codename = "Red Velvet Cake";
            else if (strcmp(version, "10") == 0)
                codename = "Quince Tart";

            snprintf(
                os,
                sizeof(os),
                "Android %s %s %s",
                codename,
                version,
                info.machine
            );
        }

        pclose(file);

    } else {

        snprintf(
            os,
            sizeof(os),
            "%s %s",
            info.sysname,
            info.machine
        );
    }

}

void get_host(void)
{
    FILE *file = popen(
        "getprop ro.product.manufacturer",
        "r"
    );

    if (file == NULL)
        return;

    char manufacturer[64];

    if (fgets(manufacturer, sizeof(manufacturer), file) == NULL) {
        pclose(file);
        return;
    }

    manufacturer[strcspn(manufacturer, "\n")] = '\0';

    pclose(file);

    file = popen(
        "getprop ro.product.model",
        "r"
    );

    if (file == NULL)
        return;

    char model[64];

    if (fgets(model, sizeof(model), file) == NULL) {
        pclose(file);
        return;
    }

    model[strcspn(model, "\n")] = '\0';

    pclose(file);

    snprintf(
        host,
        sizeof(host),
        "%s %s",
        manufacturer,
        model
    );
}
