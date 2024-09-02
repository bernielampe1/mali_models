#!/usr/bin/bash

diskname=$1
kodir=$2

if [ -z "$diskname" -o -z "$kodir" ]; then
    echo "DISKNAME KODIR"
    exit 1
fi

if [ $UID -ne 0 ]; then
    echo "must be root"
    exit 1
fi

dd if=/dev/zero of=$diskname bs=4096 count=500000

parted --script $diskname \
    mklabel gpt \
    mkpart primary 0% 100%

loop=$(losetup --find --show -P $diskname)
echo $loop

mkfs.ext4 ${loop}p1

mount ${loop}p1 /mnt

cp $kodir/* /mnt

umount /mnt

losetup -d $loop

