### We design a tool that **signalSender** could send struct's values on d-bus during special time, and **signalListener** could get the info anytime.


```
cd src
make clean
make
cd output
./signalListener
./signalSender
```


### Thanks for the help from "**Pid Eins**" : https://0pointer.net/blog/the-new-sd-bus-api-of-systemd.html and the manpage of **sd-bus** : https://manpages.debian.org/experimental/libsystemd-dev/index.html
