#!/bin/sh
set -e
. /usr/share/initramfs-tools/hook-functions

# Filesystem: aufs/overlay
manual_add_modules aufs
manual_add_modules overlay

