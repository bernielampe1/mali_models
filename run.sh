#!/bin/bash

trap 'kill $(pgrep -f http.server)' EXIT INT TERM
python -m http.server --bind 127.0.0.1 8080 &

KERNEL="kernels/linux-4.19.135_arm64/Image.gz"
DTB="kernels/dtb/qemu_mod-arm64.dtb"
INITRD="initramfs/initramfs-arm64.cpio.gz"
DISK="disks/linux-4.19.135_arm64_mods.img"

qemu-system-aarch64 \
    -gdb tcp::12345 \
    -machine virt \
    -cpu cortex-a57 \
    -smp 2 \
    -m 4096 \
    -net nic -net user \
    -nographic \
    -kernel $KERNEL \
    -dtb $DTB \
    -initrd $INITRD \
    -drive file=${DISK},format=raw,index=1,media=disk \
    -append 'console=ttyAMA0 root=/dev/ram nokaslr debug earlyprintk'
