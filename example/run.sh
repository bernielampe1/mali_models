#!/bin/sh

trap 'kill $(pgrep -f http.server)' EXIT SIGINT SIGTERM

KERNEL="linux-4.19.320"

# created initramfs everytime just in case something changed, it's fast enough
cd initramfs
find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../initramfs.cpio.gz
cd ..

# server to pull files over
python -m http.server --bind 127.0.0.1 8080 &

# start qemu
qemu-system-x86_64 -S -smp 1 \
                   -gdb tcp::12345 \
                   -m 8192M \
                   -kernel ${KERNEL}/arch/x86_64/boot/bzImage \
                   -initrd initramfs.cpio.gz \
                   -net nic -net user \
                   -nographic \
                   -append "console=ttyS0 root=/dev/ram nokaslr debug earlyprintk loglevel=8"
