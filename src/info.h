#ifndef INFO_H
#define INFO_H

extern char os[64];
extern char kernel[128];
extern char arch[64];
extern char hostname[128];
extern char uptime[64];
extern char distro[64];
extern char shell[50];

void get_system_info(void);

void get_distro();

#endif
