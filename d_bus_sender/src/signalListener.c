#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <systemd/sd-bus.h>

// 定义处理信号的回调函数
static int handle_signal(sd_bus_message *m) {
        int x, y;
        int r;

        /* Read the struct data from the message */
        // 从消息中读取结构体数据
        r = sd_bus_message_read(m, "ii", &x, &y);
        if (r < 0) {
                fprintf(stderr, "Failed to parse struct data: %s\n", strerror(-r));
                return r;
        }

        /* Print the struct data to the terminal */
        // 将结构体数据打印到终端
        printf("Received struct data: x=%d, y=%d\n", x, y);

        return 0;
}

int main() {
        sd_bus_slot *slot = NULL;
        sd_bus *bus = NULL;
        int r;

        /* Connect to the user bus this time */
        r = sd_bus_open_user(&bus);
        if (r < 0) {
                fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
                goto finish;
        }

        /* Add the match rule to filter the signal */
        // 添加匹配规则以过滤信号
        r = sd_bus_add_match(bus, &slot, "type='signal',interface='net.poettering.Calculator',member='StructData'", (sd_bus_message_handler_t)handle_signal, NULL);
        if (r < 0) {
                fprintf(stderr, "Failed to add match rule: %s\n", strerror(-r));
                goto finish;
        }

        for (;;) {
                /* Process requests */
                r = sd_bus_process(bus, NULL);
                if (r < 0) {
                        fprintf(stderr, "Failed to process bus: %s\n", strerror(-r));
                        goto finish;
                }
                if (r > 0) /* we processed a request, try to process another one, right-away */
                        continue;

                /* Wait for the next request to process */
                r = sd_bus_wait(bus, (uint64_t) -1);
                if (r < 0) {
                        fprintf(stderr, "Failed to wait on bus: %s\n", strerror(-r));
                        goto finish;
                }
        }

finish:
        sd_bus_slot_unref(slot);
        sd_bus_unref(bus);

        return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}