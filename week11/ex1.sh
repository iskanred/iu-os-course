#!bin/bash

fallocate -l 100M lofs.img

# Create filesystem on loopback device new file
sudo losetup -fP lofs.img
sudo mkfs.ext4 lofs.img

# Mount filesystem on new folder
mkdir lofsdisk
sudo mount -o loop lofs.img lofsdisk
