#!/bin/sh

fname=$1
module="mali_kbase"
devname="mali0"

# if already loaded, remove
/sbin/rmmod $module || true

# remove stale node
rm -f /dev/${devname}

# insert module
/sbin/insmod ${fname} || exit 1

# get major number
major=$(cat /sys/devices/platform/c0000.gpu/misc/mali0/dev | awk -F: '{print $1}')
minor=$(cat /sys/devices/platform/c0000.gpu/misc/mali0/dev | awk -F: '{print $2}')
if [ -z "$major" -o -z "$minor" ]; then
    exit 1
fi

# refresh device node
mknod /dev/${devname} c ${major} ${minor} || exit 1
chown 0:0 /dev/${devname} || exit 1
chmod 664 /dev/${devname} || exit 1

# print helpful debug statments
TEXT=`cat /sys/module/mali_kbase/sections/.text`
BSS=`cat /sys/module/mali_kbase/sections/.bss`
DATA=`cat /sys/module/mali_kbase/sections/.data`

echo "# Add the following lines to the .gdbinit or copy into kernel gdb session"
echo "add-symbol-file \${PWD}/${fname} $TEXT -s .bss $BSS -s .data $DATA"
echo "directory \${KERNEL_SRC}"
