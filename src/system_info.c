#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/system_info.h"

int get_ram() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/meminfo");
        return -1;
    }

    char line[256];
    int ram_kb = -1;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "MemAvailable: %d kB", &ram_kb) == 1) {
            break;
        }
    }

    fclose(fp);
    return ram_kb;
}

float get_uptime() {
    FILE *fp = fopen("/proc/uptime", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/uptime");
        return -1.0;
    }

    float up_time = 0.0;
    fscanf(fp, "%f", &up_time);
    fclose(fp);

    return up_time;
}
