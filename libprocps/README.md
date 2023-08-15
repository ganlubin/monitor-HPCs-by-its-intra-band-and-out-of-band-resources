the property of proc_t:

| variable type | variable name | description |
| ------------- | ------------- | ----------- |
| int | tid | task ID, POSIX thread ID|
| int | ppid | pid of parent process |
| unsigned long | maj_delta, min_delta | since last update, major/minor page fault |
| unsigned | pcpu | CPU% usage |
| char | state | single-char code for process state (S=sleeping) |
| unsigned long long | utime | user-mode CPU time accumulated by process|
| unsigned long long | stime | kernel-mode CPU time accumulated by process|
| unsigned long long | cutime | cumulative utime of process and children|
| unsigned long long | cstime | cumulative stime of process and children|
| unsigned long long | start_time | start time of process?|
| char[18] | signal | mask of pending signals, per-task for readtask() but per-proc for readproc()|
| char[18] | blocked |mask of blocked signals|
| char[18] | sigignore |mask of ignored signals|
| char[18] | sigcatch |mask of caught  signals|
| char[18] | _sigpnd |mask of PER TASK pending signals|
| unsigned long | start_code | address of beginning of code segment|
| unsigned long | end_code | address of end of code segment |
| unsigned long | start_stack | address of the bottom of stack |
| unsigned long | kstk_esp | kernel stack pointer|
| unsigned long | kstk_eip | kernel instruction pointer|
| unsigned long | wchan | address of kernel wait channel process is sleeping in|
| long | priority | kernel scheduling priority|
| long | nice | standard unix nice level of process |
| long | rss | identical to 'resident' ??? |
| long | alarm | ??? |
| long | size | total virtual memory |
| long | resident | resident non-swapped memory |
| long | share | shared (mmap'd) memory (memory mapping???) |
| long | trs | text resident set|
| long | lrs | library resident set |
| long | drs | data + stack resident set |
| long | dt | dirty pages |
| unsigned long | vm_size | equals 'size' (KB) |
| unsigned long | vm_lock | locked pages (KB) |
| unsigned long | vm_rss | equals 'rss' or 'resident' (KB) |
| unsigned long | vm_rss_anon | the 'anonymous' portion of vm_rss |
| unsigned long | vm_rss_shared | the 'shared'portion of vm_rss (as KB) |
| unsigned long | vm_data | data only size (KB) |
| unsigned long | vm_stack | stack only size (KB) |
| unsigned long | vm_swap | based on linux-2.6.34 "swap ents" (as kb) |
| unsigned long | vm_exe | equals 'trs' (as KB) |
| unsigned long | vm_lib | total, not just used, library pages (as KB) |
| unsigned long | rtprio | real-time priority |
| unsigned long | sched | scheduling class |
| unsigned long | vsize | number of pages of virtual memory | 
| unsigned long | rss_rlim | resident set size limit ? |
| unsigned long | flags | kernel flags for the process |
| unsigned long | min_flt, maj_flt | number of minor, major page faults since process start |
| unsigned long | cmin_flt, cmaj_flt | cumulative min_flt, maj_flt of process and child processes |
| char | **environ | environment string vector |
| char | **cmdline | command line string vector |
| char | **cgroup | cgroup string vector | 
| char | *cgname | name portion of above (if possible) |
| char | *supgid | supplementary gids as comma delimited str |
| char | *supgrp | supp grp names as comma delimited str, derived from supgid |
| char[33] | euser | effective user name |
| char[33] | ruser | real user name |
| char[33] | suser | saved user name |
| char[33] | fuser | filesystem user name |
| char[33] | rgroup | real group name | 
| char[33] | egroup | effective group name |
| char[33] | sgroup | saved group name |
| char[33] | fgroup | filesystem group name |
| char[16] | cmd | basename of executable file in call to exec(2) |
| struct proc_t | *ring | thread group ring |
| struct proc_t | *next | various library uses|
| int | pgrp | process group id |
| int | session | session ID |
| int | nlwp | number of threads, or 0 if no clue |
| int | tgid | thread group ID, the POSIX PID(see also: tid) |
| int | tty | full device number of controlling terminal |
| int | eudi, egid | uids and gids should be uid_t or gid_t from pwd.h, effective |
| int | ruid, rgid | real |
| int | suid, sgid | saved |
| int | fuid, fgid | fs (used for file access only) |
| int | tpgid | terminal process gourp id |
| int | exit_signal | might not be SIGCHLD |
| int | processor | current (or most recent?) CPU |
| int | oom_score | badness for OOM killer |
| int | oom_adj | adjustment to OOM score |
| long[6] | ns | inode number of namespaces |
| char | *sd_mach | systemd vm/container name |
| char | *sd_ouid | systemd session owner uid |
| char | *sd_seat | systemd login session seat |
| char | *sd_sess | systemd login session id |
| char | *sd_slice | systemd slice unit |
| char | *sd_unit | systemd system unit id |
| char | *sd_uunit | systemd user unit id |
| const char | *lxcname | lxc container name |