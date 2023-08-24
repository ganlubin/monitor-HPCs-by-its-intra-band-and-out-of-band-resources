#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <systemd/sd-bus.h>
#include <proc/readproc.h>
#include <cstring>
#include <iostream>

int EXIT_CODE = 0;
sd_bus_slot *slot = NULL;
sd_bus *bus = NULL;
sd_bus_message *msg = NULL;
int r = 0, x = 0, y = 0;

PROCTAB *proc = openproc(PROC_FILLMEM | PROC_FILLSTAT);

proc_t proc_info;

int main()
{
        memset(&proc_info, 0, sizeof(proc_info));
        while (readproc(proc, &proc_info) != NULL) 
        { 
                if (proc_info.cmd == NULL)
                        continue;
                printf("Process ID: %d\n", proc_info.tid); // 打印进程ID
                printf("------------------------------\n");
        }
        return 0;
}