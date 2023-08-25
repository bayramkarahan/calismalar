#!/bin/sh
set -e
if [ "$1" = "prereqs" ]; then exit 0; fi
if grep "^enabled=false" /${rootmnt}/etc/deepfreeze.conf ; then
    exit 0
fi
# prepare directories
mount -t tmpfs tmpfs /tmp || true
mkdir -p /tmp/work/source /tmp/work/a /tmp/work/b /tmp/work/target || true
# mount source
mount --bind /${rootmnt} /tmp/work/source
mount -o remount,rw /tmp/work/source
# create overlay
mount -t overlay -o lowerdir=/tmp/work/source,upperdir=/tmp/work/a,workdir=/tmp/work/b overlay /tmp/work/target
mount --bind /tmp/work/target /${rootmnt}
# fix fstab (remove rootfs from fstab)
cat /tmp/work/source/etc/fstab | sed "s/\t/ /g" | grep -v " / " > /${rootmnt}/etc/fstab
# bind mount config
mount --make-private --bind /tmp/work/source/etc/deepfreeze.conf /${rootmnt}/etc/deepfreeze.conf
# remove apt and dpkg from overlay
if grep "^remove-apt=true" /${rootmnt}/etc/deepfreeze.conf ; then
    rm -rf /${rootmnt}/var/lib/apt /${rootmnt}/var/lib/dpkg /${rootmnt}/etc/apt
    rm -rf /${rootmnt}/usr/lib/apt /${rootmnt}/usr/bin/apt* /${rootmnt}/usr/lib/dpkg /${rootmnt}/usr/bin/dpkg*
fi
# remove sudo and pkexec from overlay
if grep "^remove-root=true" /${rootmnt}/etc/deepfreeze.conf ; then
    rm -rf /${rootmnt}/usr/bin/sudo
    rm -rf /${rootmnt}/usr/bin/pkexec
fi
# bind mount from config
grep "^bind=" /${rootmnt}/etc/deepfreeze.conf | cut -f2 -d"=" | while read line ; do
    if [ -e "$line" ] ; then
        mount --make-private --bind /tmp/work/source/"$line" /${rootmnt}/"$line"
    fi
done