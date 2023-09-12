# Monitor HPCs by its intra-band and out-of-band resources

Now I'm designing a tool, which could monitor servers' status by its intraband and outofband resources.     
Please view it in branch "master".

## Updates

### **2023-09-12**

We config the hardware env, and we could test services on the board now.

### **2023-09-07**

We found the author and group of paper "MonSTer_An Out-of-the-Box Monitoring Tool for High Performance Computing Systems", and we will research the project: https://github.com/nsfcac/MonSter

### **2023-09-05**

We add a module called "Zlib Transform", which user zlib to compress the data, and use udp to transform, we get the data successfully.

### **2023-09-04**

We use UDP to send and get the proc_t, but the packages are too huge to get, we will try to fix the problems.

### **2023-08-30**

We add the Nagios service on server.

We fix the bugs in D-Bus Sender.

### **2023-08-29**

We found some wrong in process, I will suspend the D-Bus transform temporarily and try to arrange NagiosCore and its plugins on one server and test it on another test-server, about how to install Nagios on Ubuntu 18.04, it could be found at: https://www.digitalocean.com/community/tutorials/how-to-install-nagios-4-and-monitor-your-servers-on-ubuntu-18-04

### **2023-08-28**

We add all the properties of proc_t in the sd_bus_message_append() and test it. Now we could send and get all info of proc_t.

### **2023-08-25**

We made the test in folder send_process_to_DBus, and it combines libprocps and D-Bus sender, could automatically send and get the proc_t info.

### **2023-08-23**

We made the test that automatically send and get the d-bus infomation.


### **2023-08-21**

We made the test that send a struct's info to D-Bus system and use a program to get the info.  Now we could transmit info between D-bus and resource manager.
Welcome to the manpage of sd-bus: https://manpages.debian.org/experimental/libsystemd-dev/index.html

### **2023-08-16**

We made the baseboard chip test, for the foundation of the hardware test.

### **2023-08-15**

We add the libprocps's README.md to describe the properties of class "proc_t".

### **2023-08-14**

We add libprocps library and test it, now we could use the demo "libprocps/test" to get the cpu usage of tasks in the host and some other resources.

We add libtopology library and test it, we could use the demo "libtopology/test" to get the every PU, and print its deep in the topology. (Although I did not know what it means..)

