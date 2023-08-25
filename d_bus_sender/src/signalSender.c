#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>
#include <unistd.h>


int EXIT_CODE = 0;
sd_bus_slot *slot = NULL;
sd_bus *bus = NULL;
sd_bus_message *msg = NULL;
int r = 0, x = 0, y = 0;

typedef struct your_struct_t {
  int x;
  int y;
} your_struct_t;

void exit_process() {
  sd_bus_message_unref(msg);
  sd_bus_slot_unref(slot);
  sd_bus_unref(bus);
  exit(-1);
}

int main() {
  /* Connect to the user bus this time */
  r = sd_bus_open_user(&bus);
  if (r < 0) {
    fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
    exit_process();
  }

  /* Pack the struct data into the message */
  your_struct_t your_struct_data;

  /* Take a well-known service name so that clients can find us */
  r = sd_bus_request_name(bus, "net.poettering.Calculator", 0);
  if (r < 0) {
    fprintf(stderr, "Failed to acquire service name: %s\n", strerror(-r));
    exit_process();
  }

  for (x = 0, y = 10;; x++, y++) {
    /* Process requests */
    r = sd_bus_process(bus, NULL);
    if (r < 0) {
      fprintf(stderr, "Failed to process bus: %s\n", strerror(-r));
      exit_process();
    }
    if (r >= 0) {
      sleep(2);

      /* Create the message to store the struct data */
      r = sd_bus_message_new_signal(bus, &msg, "/net/poettering/Calculator",
                                    "net.poettering.Calculator", "StructData");
      if (r < 0) {
        fprintf(stderr, "Failed to create signal message: %s\n", strerror(-r));
        exit_process();
      }

      // 设置结构体数据
      your_struct_data.x = x;
      your_struct_data.y = y;
      // 将结构体数据打包到消息中
      r = sd_bus_message_append(msg, "ii", your_struct_data.x,
                                your_struct_data.y);
      if (r < 0) {
        fprintf(stderr, "Failed to append struct data to message: %s\n",
                strerror(-r));
        exit_process();
      }

      /* Send the signal message */
      r = sd_bus_send(bus, msg, NULL);
      if (r < 0) {
        fprintf(stderr, "Failed to send signal message: %s\n", strerror(-r));
        exit_process();
      }

      sd_bus_message_unref(msg);
      sd_bus_slot_unref(slot);
    }
  }

  return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}