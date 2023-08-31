#include <chrono>
#include <codecvt>
#include <cstring>
#include <ctime>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <locale>
#include <proc/readproc.h>
#include <random>
#include <sstream>
#include <sys/stat.h>
#include <systemd/sd-bus.h>
#include <thread>

sd_bus_slot *slot = NULL;
sd_bus *bus = NULL;
sd_bus_message *msg = NULL;
int r = 0;
std::random_device rd;
std::mt19937 generator(rd());

void printFiles(const proc_t &t, std::ofstream &outputFile);
std::string getCurrentDate();
void exit_process();

static int handle_signal(sd_bus_message *m) {
  proc_t proc;
  static int k = 0;
  int r;
  r = sd_bus_message_read(
      m,
      "iittuytttttsssssttttttxxxxxxxxxxxtttttttttttttttttttsssssssssiiiiiiiiiii"
      "iiiiiii",
      &proc.tid, &proc.ppid, &proc.maj_delta, &proc.min_delta, &proc.pcpu,
      &proc.state, &proc.utime, &proc.stime, &proc.cutime, &proc.cstime,
      &proc.start_time, proc.signal, proc.blocked, proc.sigignore,
      proc.sigcatch, proc._sigpnd, &proc.start_code, &proc.end_code,
      &proc.start_stack, &proc.kstk_esp, &proc.kstk_eip, &proc.wchan,
      &proc.priority, &proc.nice, &proc.rss, &proc.alarm, &proc.size,
      &proc.resident, &proc.share, &proc.trs, &proc.lrs, &proc.drs, &proc.dt,
      &proc.vm_size, &proc.vm_lock, &proc.vm_rss, &proc.vm_rss_anon,
      &proc.vm_rss_shared, &proc.vm_data, &proc.vm_stack, &proc.vm_swap,
      &proc.vm_exe, &proc.vm_lib, &proc.rtprio, &proc.sched, &proc.vsize,
      &proc.rss_rlim, &proc.flags, &proc.maj_flt, &proc.min_flt, &proc.cmaj_flt,
      &proc.cmin_flt, proc.euser, proc.ruser, proc.suser, proc.fuser,
      proc.rgroup, proc.egroup, proc.sgroup, proc.fgroup, proc.cmd, &proc.pgrp,
      &proc.session, &proc.nlwp, &proc.tgid, &proc.tty, &proc.euid, &proc.egid,
      &proc.ruid, &proc.rgid, &proc.suid, &proc.sgid, &proc.fuid, &proc.fgid,
      &proc.tpgid, &proc.exit_signal, &proc.processor, &proc.oom_score,
      &proc.oom_adj);
  if (r < 0) {
    fprintf(stderr, "Failed to parse struct data: %s\n", strerror(-r));
    return r;
  }

  std::string today_time = getCurrentDate();
  std::string storage_path = "./output/results/";
  std::string folderPath = storage_path + today_time;

  struct stat info;
  if (stat(folderPath.c_str(), &info) != 0) {
    if (mkdir(folderPath.c_str(), 0755) != 0) {
      std::cerr << "cannot create the folder" << std::endl;
      return -1;
    }
  } else if (info.st_mode & S_IFDIR) {
    // already open the folder
  } else {
    std::cerr << "not a folder" << std::endl;
    return -1;
  }

  if (proc.tid == 1) {
    k++;
    std::string filename = folderPath + "/output_" + std::to_string(k) + ".txt";
    std::ofstream outputFile(filename, std::ios::out | std::ios::binary);
    if (!outputFile) {
      std::cerr << "create file failure" << std::endl;
      return -1;
    }
    // utf-8
    std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
    printFiles(proc, outputFile);
  } else {
    std::string existingFilename = folderPath + "/output_" + std::to_string(k) + ".txt";
    std::ofstream outputFile(existingFilename, std::ios::out | std::ios::binary | std::ios::app);
    if (!outputFile) {
      std::cerr << "Failed to open file" << std::endl;
      return -1;
    }
    //utf-8
    std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
    printFiles(proc, outputFile);
  }

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

void printFiles(const proc_t &t, std::ofstream &outputFile) {

  outputFile << "tid: " << t.tid << std::endl;
  outputFile << "ppid: " << t.ppid << std::endl;
  outputFile << "maj_delta: " << t.maj_delta << std::endl;
  outputFile << "min_delta: " << t.min_delta << std::endl;
  outputFile << "pcpu: " << t.pcpu << std::endl;
  outputFile << "state: " << t.state << std::endl;
  outputFile << "utime: " << t.utime << std::endl;
  outputFile << "stime: " << t.stime << std::endl;
  outputFile << "cutime: " << t.cutime << std::endl;
  outputFile << "cstime: " << t.cstime << std::endl;
  outputFile << "start_time: " << t.start_time << std::endl;
  outputFile << "signal: " << t.signal << std::endl;
  outputFile << "blocked: " << t.blocked << std::endl;
  outputFile << "sigignore: " << t.sigignore << std::endl;
  outputFile << "sigcatch: " << t.sigcatch << std::endl;
  outputFile << "_sigpnd: " << t._sigpnd << std::endl;
  outputFile << "start_code: " << t.start_code << std::endl;
  outputFile << "end_code: " << t.end_code << std::endl;
  outputFile << "start_stack: " << t.start_stack << std::endl;
  outputFile << "kstk_esp: " << t.kstk_esp << std::endl;
  outputFile << "kstk_eip: " << t.kstk_eip << std::endl;
  outputFile << "wchan: " << t.wchan << std::endl;
  outputFile << "priority: " << t.priority << std::endl;
  outputFile << "nice: " << t.nice << std::endl;
  outputFile << "rss: " << t.rss << std::endl;
  outputFile << "alarm: " << t.alarm << std::endl;
  outputFile << "size: " << t.size << std::endl;
  outputFile << "resident: " << t.resident << std::endl;
  outputFile << "share: " << t.share << std::endl;
  outputFile << "trs: " << t.trs << std::endl;
  outputFile << "lrs: " << t.lrs << std::endl;
  outputFile << "drs: " << t.drs << std::endl;
  outputFile << "dt: " << t.dt << std::endl;
  outputFile << "vm_size: " << t.vm_size << std::endl;
  outputFile << "vm_lock: " << t.vm_lock << std::endl;
  outputFile << "vm_rss: " << t.vm_rss << std::endl;
  outputFile << "vm_rss_anon: " << t.vm_rss_anon << std::endl;
  outputFile << "vm_rss_shared: " << t.vm_rss_shared << std::endl;
  outputFile << "vm_data: " << t.vm_data << std::endl;
  outputFile << "vm_stack: " << t.vm_stack << std::endl;
  outputFile << "vm_swap: " << t.vm_swap << std::endl;
  outputFile << "vm_exe: " << t.vm_exe << std::endl;
  outputFile << "vm_lib: " << t.vm_lib << std::endl;
  outputFile << "rtprio: " << t.rtprio << std::endl;
  outputFile << "sched: " << t.sched << std::endl;
  outputFile << "vsize: " << t.vsize << std::endl;
  outputFile << "rss_rlim: " << t.rss_rlim << std::endl;
  outputFile << "flags: " << t.flags << std::endl;
  outputFile << "maj_flt: " << t.maj_flt << std::endl;
  outputFile << "min_flt: " << t.min_flt << std::endl;
  outputFile << "cmaj_flt: " << t.cmaj_flt << std::endl;
  outputFile << "cmin_flt: " << t.cmin_flt << std::endl;
  outputFile << "euser: " << t.euser << std::endl;
  outputFile << "ruser: " << t.ruser << std::endl;
  outputFile << "suser: " << t.suser << std::endl;
  outputFile << "fuser: " << t.fuser << std::endl;
  outputFile << "rgroup: " << t.rgroup << std::endl;
  outputFile << "egroup: " << t.egroup << std::endl;
  outputFile << "sgroup: " << t.sgroup << std::endl;
  outputFile << "fgroup: " << t.fgroup << std::endl;
  outputFile << "cmd: " << t.cmd << std::endl;
  outputFile << "pgrp: " << t.pgrp << std::endl;
  outputFile << "session: " << t.session << std::endl;
  outputFile << "nlwp: " << t.nlwp << std::endl;
  outputFile << "tgid: " << t.tgid << std::endl;
  outputFile << "tty: " << t.tty << std::endl;
  outputFile << "euid: " << t.euid << std::endl;
  outputFile << "egid: " << t.egid << std::endl;
  outputFile << "ruid: " << t.ruid << std::endl;
  outputFile << "rgid: " << t.rgid << std::endl;
  outputFile << "suid: " << t.suid << std::endl;
  outputFile << "sgid: " << t.sgid << std::endl;
  outputFile << "fuid: " << t.fuid << std::endl;
  outputFile << "fgid: " << t.fgid << std::endl;
  outputFile << "tpgid: " << t.tpgid << std::endl;
  outputFile << "exit_signal: " << t.exit_signal << std::endl;
  outputFile << "processor: " << t.processor << std::endl;
  outputFile << "oom_score: " << t.oom_score << std::endl;
  outputFile << "oom_adj: " << t.oom_adj << std::endl;
  outputFile << std::endl;

  outputFile.close();
}

std::string getCurrentDate() {
  time_t now = time(0);
  struct tm localTime;
  localtime_r(&now, &localTime);

  std::stringstream dateStream;
  dateStream << (1900 + localTime.tm_year) << "-" << (1 + localTime.tm_mon)
             << "-" << localTime.tm_mday;

  return dateStream.str();
}

void exit_process() {
  sd_bus_message_unref(msg);
  sd_bus_slot_unref(slot);
  sd_bus_unref(bus);
  exit(-1);
}