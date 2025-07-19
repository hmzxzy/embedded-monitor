#include "../include/system_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Global buffer for hostname (safe to return pointer)
static char hostname_buffer[128];

//Get hostname
const char* get_hostname() {
    if (gethostname(hostname_buffer, sizeof(hostname_buffer)) != 0) {
        perror("get_hostname failed");
        return "unknown";
    }
    return hostname_buffer;
}

//Get total RAM in KB from /proc/meminfo
int get_ram() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("get_ram failed");
        return -1;
    }

    int ram_kb = 0;
    char label[64];
    fscanf(fp, "%s %d", label, &ram_kb);  // Reads "MemTotal: 123456"
    fclose(fp);
    return ram_kb;
}

//Get system uptime in seconds from /proc/uptime
float get_uptime() {
    FILE *fp = fopen("/proc/uptime", "r");
    if (!fp) {
        perror("get_uptime failed");
        return -1;
    }

    float uptime_seconds = 0.0;
    fscanf(fp, "%f", &uptime_seconds);  // Reads the first number
    fclose(fp);
    return uptime_seconds;
}

//Get CPU usage over a short interval
float get_cpu_usage() {
    FILE *fp;
    char buffer[256];
    unsigned long long int user, nice, system, idle, iowait, irq, softirq;
    unsigned long long int total1, total2, idle1, idle2;

    // First read
    fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("get_cpu_usage read 1 failed");
        return -1;
    }

    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "cpu  %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq);
    fclose(fp);

    idle1 = idle + iowait;
    total1 = user + nice + system + idle + iowait + irq + softirq;

    usleep(100000);  // Sleep 100ms

    // Second read
    fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("get_cpu_usage read 2 failed");
        return -1;
    }

    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "cpu  %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq);
    fclose(fp);

    idle2 = idle + iowait;
    total2 = user + nice + system + idle + iowait + irq + softirq;

    float total_diff = (float)(total2 - total1);
    float idle_diff = (float)(idle2 - idle1);

    if (total_diff == 0) return 0;

    return 100.0 * (1.0 - idle_diff / total_diff);
}

