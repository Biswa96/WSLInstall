# Chroot into ARMv8 64bit (AARCH64) distribution

This is for WSL2 only.

## Ubuntu

### Procedure

* Install required packages:

```
sudo apt install \
build-essential \
binfmt-support \
daemonize \
libarchive-tools \
qemu-system \
qemu-user \
qemu-user-static \
gcc-aarch64-linux-gnu \
g++-aarch64-linux-gnu
```

* Download `server-cloudimg-arm64-wsl.rootfs.tar.gz` from [Ubuntu Cloud image][1].

* Extract the tarball in a folder:

```
sudo bsdtar -xpf server-cloudimg-arm64-wsl.rootfs.tar.gz -C folder
```

* Copy qemu static binary into that folder:

```
sudo cp /usr/bin/qemu-aarch64-static folder/usr/bin
```

* Start systemd with daemonize:

```
sudo daemonize \
/usr/bin/unshare -fp --mount-proc \
/lib/systemd/systemd --system-unit=basic.target
```

* Check if AARCH64 binfmt entry is present:

```
ls /proc/sys/fs/binfmt_misc/
```

* Mount and chroot into the environment:

```
sudo mount -o bind /proc folder/proc
sudo mount -o bind /dev folder/dev
sudo chroot folder qemu-aarch64-static /bin/bash
```

* In the chroot, delete `/etc/resolv.conf` file and write a name server to it.


## ArchLinux

[Name resolution does not work][2]

### Procedure

* Install required packages:

```
sudo pacman -S --needed \
base-devel binutils git qemu qemu-arch-extra aarch64-linux-gnu-gcc
```

* Compile and install qemu-arm-static package from AUR:

```
git clone https://aur.archlinux.org/qemu-arm-static.git
cd qemu-arm-static
makepkg -si
```

* Download and extract ArchLinux AARCH64 tarball:

```
wget http://os.archlinuxarm.org/os/ArchLinuxARM-aarch64-latest.tar.gz
sudo bsdtar -xpf ArchLinuxARM-aarch64-latest.tar.gz -C folder
```

* Copy qemu static binary into that folder:

```
sudo cp /usr/bin/qemu-aarch64-static folder/usr/bin
```

* Register binfmt entries manually:

```
cat /usr/lib/binfmt.d/aarch64.conf | sudo tee /proc/sys/fs/binfmt_misc/register > /dev/null
cat /usr/lib/binfmt.d/arm.conf | sudo tee /proc/sys/fs/binfmt_misc/register > /dev/null
cat /usr/lib/binfmt.d/armeb.conf | sudo tee /proc/sys/fs/binfmt_misc/register > /dev/null
ls /proc/sys/fs/binfmt_misc/
```

* Chroot into the environment:

```
sudo arch-chroot folder qemu-aarch64-static /bin/bash
```


## Related Links

* [ArchLinux ARM: Raspberry Pi installation][3]
* [Unix&Linux SE: How-to chroot into a different architecture file system][4]


<!-- Links -->
[1]: https://cloud-images.ubuntu.com/releases/
[2]: https://unix.stackexchange.com/q/554452/336403
[3]: https://archlinuxarm.org/platforms/armv8/broadcom/raspberry-pi-4
[4]: https://unix.stackexchange.com/q/41889/336403

<!-- END -->
