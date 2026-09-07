#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>

#include "info.h"

char os[64];
char kernel[128];
char arch[64];
char hostname[128];
char uptime[64];

void get_system_info(void)
{
    struct utsname system;

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
/*
void get_distro() {

}
*/
