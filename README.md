# Monitor HPCs by its intra-band and out-of-band resources

Now I'm designing a tool, which could monitor servers' status by its intraband and outofband resources.     
Please view it in branch "master".

## Updates

### **2023-08-14**

We add libprocps library and test it, now we could use the demo "libprocps/test" to get the cpu usage of tasks in the host and some other resources.

We add libtopology library and test it, we could use the demo "libtopology/test" to get the every PU, and print its deep in the topology. (Although I did not know what it means..)

### **2023-08-15**

We add the libprocps's README.md to describe the properties of class "proc_t".

### **2023-08-16**

We made the baseboard chip test, for the foundation of the hardware test.

### **2023-08-21**

We made the test that send a struct's info to D-Bus system and use a program to get the info.  Now we could transmit info between D-bus and resource manager.
Welcome to the manpage of sd-bus: https://manpages.debian.org/experimental/libsystemd-dev/index.html

### **2023-08-23**

We made the test that automatically send and get the d-bus infomation.
