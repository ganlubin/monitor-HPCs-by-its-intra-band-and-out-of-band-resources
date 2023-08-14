# monitor-HPCs-by-its-intra-band-and-out-of-band-resources
Now I'm designing a tool, which could monitor servers' status by its intraband and outofband resources.

ok, and I will update my context after experiences.

--2023-08-14--
We add libprocps library and test it, now we could use the demo "libprocps/test" to get the cpu usage of tasks in the host and some other resources.
We add libtopology library and test it, we could use the demo "libtopology/test" to get the every PU, and print its deep in the topology. (Although I didnot know what it means..)
