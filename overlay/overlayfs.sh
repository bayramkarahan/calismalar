#!/usr/bin/env bash
set -eux

# https://askubuntu.com/questions/109413/how-do-i-use-overlayfs/1075564#1075564
# https://askubuntu.com/questions/699565/example-overlayfs-usage

# Global setup.
top=overlayfs.tmp
rm -rf "$top"
mkdir -p "$top"
cd "$top"

# Create the filesystems.
mkdir lower
mkdir upper
mkdir overlay
dd if=/dev/zero of=lower.ext4 bs=1024 count=102400
dd if=/dev/zero of=upper.ext4 bs=1024 count=102400
mkfs -t ext4 lower.ext4
mkfs -t ext4 upper.ext4
sudo mount lower.ext4 lower
sudo mount upper.ext4 upper
sudo chown "$USER:$USER" lower
sudo chown "$USER:$USER" upper
printf 'lower-content' > lower/lower-file
# upper and work must be on the same filesystem.
mkdir upper/upper
mkdir upper/work
printf 'upper-content' > upper/upper/upper-file
# Work must be empty.
# echo 'work-content' >> upper/work/work-file

# Make the lower readonly to show that that is possible:
# writes actually end up on the upper filesystem.
sudo mount -o remount,ro lower.ext4 lower
printf 'elif-content' > lower/elif-file
# Create the mount.
sudo mount \
  -t overlay \
  -o lowerdir=lower,upperdir=upper/upper,workdir=upper/work \
  none \
  overlay \
;
printf 'overlay-content' > overlay/overlay-file
ls lower upper/upper upper/work overlay

# Cleanup.
#sudo umount overlay
#sudo umount upper
#sudo umount lower
