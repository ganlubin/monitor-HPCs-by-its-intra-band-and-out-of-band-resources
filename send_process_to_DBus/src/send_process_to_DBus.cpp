#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <fstream>
#include <proc/readproc.h>
#include <systemd/sd-bus.h>


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

        /*
        y uint8_t
        b boolean
        n int16_t
        q uint16_t
        i int32_t
        u uint32_t
        x int64_t
        t uint64_t
        d double
        s string char[]
        */
        // r = sd_bus_message_append(msg, "i", T.tid);
        r = sd_bus_message_append(
            msg,
            "iittuytttttsssssttttttxxxxxxxxxxxtttttttttttttttttttsssssssssiiiiiiiiiiiiiiiiii",
            T.tid, 
            T.ppid,
            T.maj_delta, 
            T.min_delta,
            T.pcpu,
            T.state,
            T.utime,
            T.stime,
            T.cutime, 
            T.cstime, 
            T.start_time,
            T.signal, 
            T.blocked,
            T.sigignore, 
            T.sigcatch, 
            T._sigpnd, 
            T.start_code, 
            T.end_code,
            T.start_stack, 
            T.kstk_esp, 
            T.kstk_eip,
            T.wchan, 
            T.priority, 
            T.nice,
            T.rss, 
            T.alarm, 
            T.size, 
            T.resident, 
            T.share, 
            T.trs, 
            T.lrs,
            T.drs,
            T.dt, 
            T.vm_size, 
            T.vm_lock, 
            T.vm_rss, 
            T.vm_rss_anon,
            T.vm_rss_shared, 
            T.vm_data, 
            T.vm_stack, 
            T.vm_swap, 
            T.vm_exe,
            T.vm_lib,
            T.rtprio, 
            T.sched, 
            T.vsize, 
            T.rss_rlim, 
            T.flags,
            T.maj_flt, 
            T.min_flt, 
            T.cmaj_flt, 
            T.cmin_flt, 
            T.euser, 
            T.ruser,
            T.suser, 
            T.fuser, 
            T.rgroup, 
            T.egroup, 
            T.sgroup, 
            T.fgroup,
            T.cmd,
            T.pgrp, 
            T.session, 
            T.nlwp, 
            T.tgid, 
            T.tty, 
            T.euid, 
            T.egid, 
            T.ruid,
            T.rgid, 
            T.suid, 
            T.sgid,
            T.fuid, 
            T.fgid, 
            T.tpgid, 
            T.exit_signal,
            T.processor, 
            T.oom_score, 
            T.oom_adj
            );
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
      sleep(10);
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