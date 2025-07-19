#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

int get_ram();                  // Returns total RAM in KB
float get_uptime();            // Returns system uptime in seconds
float get_cpu_usage();         // Returns CPU usage % over 100ms
const char* get_hostname();    // Returns hostname

#endif // SYSTEM_INFO_H

