This project is a set of working mali device driver testing environments using qemu and stubbed out gpu functionality. Built and run on Ubuntu 22.04.4 LTS x86_64.

# Emulator options

1. mali verisons
    * Bifrost versions 0 - 50

2. mali modes
    * jm - job manager
    * csf - command stream frontend

3. pre-built kernel versions
    * linux-4.19.135.tar.gz

4. arch's
    * x86_64
    * arm64

5. instrumentation modes
    * NO-ASAN
    * ASAN

# Install Prereqs:
These are targets for Ubuntu 22.04.4 LTS.

```console
# sudo apt-get install build-dep linux libncurses-dev gawk flex bison openssl libssl-dev dkms libelf-dev libudev-dev libpci-dev libiberty-dev autoconf llvm git qemu-system-arm gdb-multiarch
```

# Booting up:
```console
$ gunzip disks/linux-4.19.135_arm64_mods.img.gz
$ ./run.sh
[    0.000000] Booting Linux on physical CPU 0x0000000000 [0x411fd070]
[    0.000000] Linux version 4.19.135 (user@host) (gcc version 11.4.0 (Ubuntu 11.4.0-1ubuntu1~22.04)) #1 SMP PREEMPT Thu Jul 11 16:12:20 EDT 2024
[    0.000000] Machine model: linux,dummy-virt
[    0.000000] efi: Getting EFI parameters from FDT:
[    0.000000] efi: UEFI not found.
[    0.000000] cma: Reserved 32 MiB at 0x00000000fe000000
[    0.000000] NUMA: No NUMA configuration found
<snip>
[    1.072240] Loading compiled-in X.509 certificates
[    1.083918] input: gpio-keys as /devices/platform/gpio-keys/input/input0
[    1.087367] rtc-pl031 9010000.pl031: setting system clock to 2024-09-02 18:48:41 UTC (1725302921)
[    1.088966] ALSA device list:
[    1.089067]   No soundcards found.
[    1.092655] uart-pl011 9000000.pl011: no DMA platform data
[    1.109920] Freeing unused kernel memory: 1216K
[    1.111929] Run /init as init process
/ # uname -a
Linux (none) 4.19.135 #1 SMP PREEMPT Thu Jul 11 16:12:20 EDT 2024 aarch64 GNU/Linux
/ #
```

# Loading a the mali GPU module:
```console
/ # mount /mnt
/mnt # cd /mnt
/mnt # ./load_mod.sh mali_kbase_jm_r40p0.ko
rmmod: remove 'mali_kbase': No such file or directory
[   93.374691] mali_kbase: loading out-of-tree module taints kernel.
[   93.461907] mali c0000.gpu: Kernel DDK version r40p0-01eac0
[   93.462333] Couldn't find control register values for GPU ; using default tMIx
[   93.462558] mali c0000.gpu: Using Dummy Model
[   93.467091] mali c0000.gpu: GPU identified as 0x0 arch 6.0.10 r0p1 status 0
[   93.468636] mali c0000.gpu: No priority control manager is configured
[   93.473432] mali c0000.gpu: No memory group manager is configured
[   93.475481] mali c0000.gpu: No OPPs found in device tree! Scaling timeouts using 100000 kHz
[   93.489364] mali c0000.gpu: Probed as mali0
# Add the following lines to the .gdbinit or copy into kernel gdb session
add-symbol-file mali_kbase_jm_r40p0.ko 0xffff000000b40000 -s .bss 0xffff000000bfadc0 -s .data 0xffff000000bf6168
/mnt # ls -l /dev/mali0 
crw-rw-r--    1 0        0          10,  58 Sep  2 18:50 /dev/mali0
```

# Debugging:
```console
$ cd modules/linux-4.19.135_arm64
$ unxz mali_kbase_jm_r40p0.ko.xz 
$ cd linux-4.19.135_arm64/
$ unxz vmlinux.xz
$ gdb-multiarch vmlinux
(gdb) target remote :12345
(gdb) add-symbol-file ../../modules/linux-4.19.135_arm64/mali_kbase_jm_r40p0.ko 0xffff000000b40000 -s .bss 0xffff000000bfadc0 -s .data 0xffff000000bf6168
add symbol table from file "../../modules/linux-4.19.135_arm64/mali_kbase_jm_r40p0.ko" at
	.text_addr = 0xffff000000b40000
	.bss_addr = 0xffff000000bfadc0
	.data_addr = 0xffff000000bf6168
(y or n) y
Reading symbols from ../../modules/linux-4.19.135_arm64/mali_kbase_jm_r40p0.ko...
(gdb) b kbase_mmap
Breakpoint 1 at 0xffff000000b57fb0: file /home/user/jb/drivers/modules/BX304L01B-SW-99002-r40p0-01eac0/driver/product/kernel/drivers/gpu/arm/midgard/mali_kbase_core_linux.c, line 2235.
(gdb) c
Continuing.

Thread 1 hit Breakpoint 1, kbase_open (inode=0xffff8000fb6284b0, filp=0xffff8000fb36cb00) at ./include/linux/fs.h:851
851	./include/linux/fs.h: No such file or directory.
(gdb) bt
#0  kbase_open (inode=0xffff8000fb6284b0, filp=0xffff8000fb36cb00) at ./include/linux/fs.h:851
#1  0xffff000008630414 in misc_open (inode=0xffff8000fb6284b0, file=0xffff8000fb36cb00) at drivers/char/misc.c:141
#2  0xffff00000824a050 in chrdev_open (inode=0x3a, filp=0xffff000009241c18 <misc_mtx>) at fs/char_dev.c:423
#3  0xffff000008240214 in do_dentry_open (f=0xffff8000fb36cb00, inode=0xffff8000fb6284b0, open=0xffff0000092d0c18 <cdev_lock>) at fs/open.c:796
#4  0xffff000008241828 in vfs_open (path=<optimized out>, file=<optimized out>) at fs/open.c:902
Backtrace stopped: previous frame identical to this frame (corrupt stack?)
```
