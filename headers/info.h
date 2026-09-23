#ifndef INFO_H
#define INFO_H

extern char os[64];
extern char kernel[128];
extern char hostname[128];
extern char uptime[64];
extern char distro[64];
extern char shell[50];
extern char cpu[128];
extern char environment[50];
extern char ram[64];
extern char username[64];
extern char ip[64];
extern char packages[64];
extern char package_manager[32];
extern char distro_color[16];
extern char host[128];
extern char network_interface[32];

void get_distro_color(void);
void get_system_info(void);
void get_distro(void);
void get_cpu(void);
void get_ram(void);
void get_username(void);
void get_ip(void);
void get_shell(void);
void get_packages(void);
void get_os_info(void);
void get_host(void);


#endif
