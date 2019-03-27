## Convert .tar.xz to .tar.gz

First it will be better if you have a Linux environment and change user to `root`.
Always copy the .tar.xz file to `/home/user` folder to avoid any hard link conflicts.
Let the file name as **distro.tar.xz** and file path `/mnt/c/MyFiles`.
It is important to use [**`--hard-dereference`**](https://www.gnu.org/software/tar/manual/html_node/hard-links.html)
option with tar command with `sudo`.

```
cp /mnt/c/MyFiles/distro.tar.xz ~
cd ~
mkdir /tmp
tar -xf distro.tar.xz -C tmp/
cd tmp/
tar -czf ../distro.tar.gz --hard-dereference *
cd ~
mv distro.tar.gz /mnt/c/MyFiles/
rm -rf tmp/
```

## Convert SquashFS to .tar.gz

Let the file name as **distro.squashfs** (or in some cases **distro.SFS**)
and file path `/mnt/c/MyFiles`. Here also it will be better if you copy
the file in an Linux environment and change user to `root`.

```
cp /mnt/c/MyFiles/distro.squashfs ~
cd ~
unsquashfs -d tmp distro.squashfs
cd tmp
tar -czf ../distro.tar.gz --hard-dereference *
cd ~
mv distro.tar.gz /mnt/c/MyFiles/
rm -rf tmp/
```
