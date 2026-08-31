#!/usr/bin/env bash
qemu-system-x86_64 \
	-m 2048 \
	-smp 2 \
	-drive file=lfs-penguin.qcow2,media=disk,if=virtio \
	-nic user,model=virtio \
	-virtfs local,path=.,mount_tag=pingu,security_model=mapped,id=pingu \
	-nographic \
	-accel kvm \
	-device qemu-xhci,id=xhci
