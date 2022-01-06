#!/bin/sh
qemu-system-x86_64 -kernel linux-5.13.1/arch/x86_64/boot/bzImage -hda rootfs.img -append "console=ttyS0 root=/dev/sda" -nographic
