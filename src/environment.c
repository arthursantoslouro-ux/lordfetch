#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "environment.h"

int is_android(void)
{
    FILE *file = popen(
        "getprop ro.build.version.sdk 2>/dev/null",
        "r"
    );

    if (file == NULL)
        return 0;

    char sdk[16];

    if (fgets(sdk, sizeof(sdk), file) != NULL) {
        pclose(file);
        return sdk[0] != '\0';
    }

    pclose(file);

    return 0;
}

int is_termux(void)
{
    const char *prefix = getenv("PREFIX");

    if (prefix == NULL)
        return 0;

    return strstr(prefix, "com.termux") != NULL;
}
