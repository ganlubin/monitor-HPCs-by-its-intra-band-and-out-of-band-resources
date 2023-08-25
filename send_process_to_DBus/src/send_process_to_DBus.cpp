#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <proc/readproc.h>
#include <systemd/sd-bus.h>
#include <unistd.h>
#include <vector>

int EXIT_CODE = 0;
sd_bus_slot *slot = NULL;
sd_bus *bus = NULL;
sd_bus_message *msg = NULL;
int r = 0;

PROCTAB *proc;
proc_t proc_info;
std::vector<proc_t> processes;

void exit_process();
void readFromProc(PROCTAB *proc, proc_t proc_info);

int main() {
  r = sd_bus_open_user(&bus);
  if (r < 0) {
    fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
    exit_process();
  }
  r = sd_bus_request_name(bus, "net.poettering.DBusSender", 0);
  if (r < 0) {
    fprintf(stderr, "Failed to acquire service name: %s\n", strerror(-r));
    exit_process();
  }
  while (1) {
    r = sd_bus_process(bus, NULL);
    if (r < 0) {
      fprintf(stderr, "Failed to process bus: %s\n", strerror(-r));
      exit_process();
    }
    if (r >= 0) {
      readFromProc(proc, proc_info);

      for (proc_t T : processes) {
        r = sd_bus_message_new_signal(bus, &msg, "/net/poettering/DBusSender",
                                      "net.poettering.DBusSender", "Sender");
        if (r < 0) {
          fprintf(stderr, "Failed to create signal message: %s\n",
                  strerror(-r));
          exit_process();
        }

        r = sd_bus_message_append(msg, "it", T.tid, T.stime);
        if (r < 0) {
          fprintf(stderr, "Failed to append struct data to message: %s\n",
                  strerror(-r));
          exit_process();
        }

        r = sd_bus_send(bus, msg, NULL);
        if (r < 0) {
          fprintf(stderr, "Failed to send signal message: %s\n", strerror(-r));
          exit_process();
        }
      }
      processes.clear();
      sleep(5);
    }
  }
  closeproc(proc);
  return 0;
}

void readFromProc(PROCTAB *proc, proc_t proc_info) {
  proc = openproc(PROC_FILLMEM | PROC_FILLSTATUS | PROC_FILLUSR);
  memset(&proc_info, 0, sizeof(proc_info));
  while (readproc(proc, &proc_info) != NULL) {
    proc_t tt;
    if (proc_info.cmd == NULL) {
      continue;
    }
    tt = proc_info;
    processes.push_back(tt);
  }
  std::cout << processes.size() << std::endl;
}

void exit_process() {
  sd_bus_message_unref(msg);
  sd_bus_slot_unref(slot);
  sd_bus_unref(bus);
  exit(-1);
}