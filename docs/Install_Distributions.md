# Install any distribution in WSL

## Requirements:

1. Required packages: 7zip-full, squashfs-tool 
2. Pre-installed "supported" distributions from Windows Store. 
3. root user access in WSL. 

## Arch Linux

1. Login root user in that pre-installed WSL distribution and `cd /root`. 
2. Download latest [Arch Linux ISO](https://mirrors.edge.kernel.org/archlinux/iso/latest/). 
3. Extract `arch/x86_64/airootfs.sfs` file from it. 
4. Extract files from airootfs.sfs: `unsquashfs -d temp airootfs.sfs` 
5. Make GZIP tarball from those extracted files: `tar -czf ../arch.tar.gz --hard-dereference *` 
6. Install it with `wsl.exe --import` command. 

### Additional steps for Arch Linux:

1. Allow required binaries e.g. `pacman` in Windows Firewall. 
2. Remove or rename `/etc/resolv.conf` file. 
3. Try to update packages with `pacman -Syyu` and allow all required PGP keys. 
4. Initialize keyring for pacman: `pacman-key --init` 
5. Reload the default keys ([Source][1]): `pacman-key --populate`
6. Now install, update or upgrade packages. 

<!-- Links -->
[1]: https://bbs.archlinux.org/viewtopic.php?id=233480
