#ifndef INFO_H
#define INFO_H
extern char os[64];
extern char kernel[128];
extern char arch[64];
extern char hostname[128];
extern char uptime[64];
extern char distro[64];
extern char shell[50];
extern char cpu[128];
extern char environment[50];
extern char ram[64];
extern char username[64];

void get_system_info(void);
void get_distro(void);
void get_cpu(void);
void get_ram(void);
void get_username(void);
#endif
