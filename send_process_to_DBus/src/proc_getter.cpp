#include <cstring>
#include <errno.h>
#include <iostream>
#include <proc/readproc.h>
#include <random>
#include <systemd/sd-bus.h>

sd_bus_slot *slot = NULL;
sd_bus *bus = NULL;
sd_bus_message *msg = NULL;
int r = 0;
std::random_device rd;
std::mt19937 generator(rd());

void exit_process() {
  sd_bus_message_unref(msg);
  sd_bus_slot_unref(slot);
  sd_bus_unref(bus);
  exit(-1);
}

static int handle_signal(sd_bus_message *m) {
  proc_t proc;

  int r;
  r = sd_bus_message_read(m, "iittuytttttsssssttttttxxxxxxxxxxxtttttttttttttttttttsssssssssiiiiiiiiiiiiiiiiii", &proc.tid, &proc.ppid, &proc.maj_delta,
                                      &proc.min_delta, &proc.pcpu, &proc.state,
                                      &proc.utime, &proc.stime, &proc.cutime,
                                      &proc.cstime, &proc.start_time, proc.signal,
                                      proc.blocked, proc.sigignore, proc.sigcatch,
                                      proc._sigpnd, &proc.start_code, &proc.end_code,
                                      &proc.start_stack, &proc.kstk_esp, &proc.kstk_eip,
                                      &proc.wchan, &proc.priority, &proc.nice,
                                      &proc.rss, &proc.alarm, &proc.size, &proc.resident,
                                      &proc.share, &proc.trs, &proc.lrs, &proc.drs,
                                      &proc.dt, &proc.vm_size, &proc.vm_lock, 
                                      &proc.vm_rss, &proc.vm_rss_anon, &proc.vm_rss_shared,
                                      &proc.vm_data, &proc.vm_stack, &proc.vm_swap,
                                      &proc.vm_exe, &proc.vm_lib, &proc.rtprio,
                                      &proc.sched, &proc.vsize, &proc.rss_rlim,
                                      &proc.flags, &proc.maj_flt, &proc.min_flt,
                                      &proc.cmaj_flt, &proc.cmin_flt, proc.euser,
                                      proc.ruser, proc.suser, proc.fuser, proc.rgroup,
                                      proc.egroup, proc.sgroup, proc.fgroup, proc.cmd,
                                      &proc.pgrp, &proc.session, &proc.nlwp, &proc.tgid,
                                      &proc.tty, &proc.euid, &proc.egid, &proc.ruid,
                                      &proc.rgid, &proc.suid, &proc.sgid, &proc.fuid,
                                      &proc.fgid, &proc.tpgid, &proc.exit_signal,
                                      &proc.processor, &proc.oom_score, &proc.oom_adj);
  if (r < 0) {
    fprintf(stderr, "Failed to parse struct data: %s\n", strerror(-r));
    return r;
  }

  std::cout << "tid = " << proc.tid << ',';
  std::cout << "ppid = " << proc.ppid << ',';
  std::cout << "maj_delta = " << proc.maj_delta << ',';
  std::cout << "min_delta = " << proc.min_delta << ',';
  std::cout << "pcpu = " << proc.pcpu << ',';
  std::cout << "state = " << proc.state << std::endl;


  std::uniform_int_distribution<int> distribution(1, 100);
  int randomNumber = distribution(generator);
  std::cout << randomNumber << std::endl;

  return 0;
}

int main() {
  r = sd_bus_open_user(&bus);
  if (r < 0) {
    fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
    exit_process();
  }

  r = sd_bus_add_match(
      bus, &slot,
      "type='signal',interface='net.poettering.DBusSender',member='Sender'",
      (sd_bus_message_handler_t)handle_signal, NULL);
  if (r < 0) {
    fprintf(stderr, "Failed to add match rule: %s\n", strerror(-r));
    exit_process();
  }

  while (1) {
    /* Process requests */
    r = sd_bus_process(bus, NULL);
    if (r < 0) {
      fprintf(stderr, "Failed to process bus: %s\n", strerror(-r));
      exit_process();
    }
    if (r >
        0) /* we processed a request, try to process another one, right-away */
      continue;

    /* Wait for the next request to process */
    r = sd_bus_wait(bus, (uint64_t)-1);
    if (r < 0) {
      fprintf(stderr, "Failed to wait on bus: %s\n", strerror(-r));
      exit_process();
    }
  }

  return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}