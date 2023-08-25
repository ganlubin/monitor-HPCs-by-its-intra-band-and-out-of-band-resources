#include <cstring>
#include <errno.h>
#include <iostream>
#include <proc/readproc.h>
#include <systemd/sd-bus.h>
#include <random>

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
  int tid;
  unsigned long long stime;

  int r;
  r = sd_bus_message_read(m, "it", &tid, &stime);
  if (r < 0) {
    fprintf(stderr, "Failed to parse struct data: %s\n", strerror(-r));
    return r;
  }

  std::cout << "Received data: tid = " << tid << " stime = " << stime
            << std::endl;

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