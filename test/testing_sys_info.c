#include <stdio.h>
#include "../include/system_info.h"

int main() {
    int ram = get_ram();           
    float uptime = get_uptime();

    if (ram != -1)
        printf("Available RAM: %d kB\n", ram);
    else
        printf("Failed to get RAM info.\n");

    if (uptime >= 0)
        printf("Uptime: %.2f seconds\n", uptime);
    else
        printf("Failed to get uptime.\n");

    return 0;
}
