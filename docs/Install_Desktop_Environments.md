# Install any desktop environment in WSL

The full download and installation procedure take some times depending on
your network and hardwares because [I/O in WSL](https://github.com/Microsoft/WSL/issues/873)
is very much slower than actual GNU/Linux systems. 

## Requirements

* Latest Windows 10 Pro with WSL feature enabled.
* Any distribution installed in WSL.
* Any X11 server in Windows side, for example, XMing, VcxSrv, X410 etc.
* Add these variables in `~/.bashrc` file: 

```bash
export DISPLAY=:0.0
export LIBGL_ALWAYS_INDIRECT=1
```

* Run VcxSrv with "One large window" and display number 0 (zero).
Alternatively use this command: `vcxsrv.exe :0 -clipboard -wgl` 

## XFCE in Fedora

### Steps:

* Update and upgrade: `dnf upgrade`
* Install XFCE group pacakge: `dnf group install "Xfce Desktop"`
* Start XFCE: `startxfce4` or `xfce4-session`

### Notes:

If there is any error like this:
Failed to obtain the transaction lock (logged in as: root).
Run these commands as root to clean up temporary files.

```bash
rm -f /var/lib/rpm/__db.*
rm -f /var/lib/rpm/.*.lock
```

## KDE in Ubuntu

### Steps:

* Update and upgrade: `apt update; apt upgrade -y` 

* Install Kubuntu DE (~1 GB) ([Source](https://wiki.debian.org/KDE)):
`apt install kde-plasma-desktop` 

* Optional packages: `apt install kde-standard kstart kscreen konq-plugins` 

* Install all Qt5 libraries: `apt install libqt5*` 

* Install others: `apt install binutils dbus-x11` 

* Remove `.note.ABI-tag` section ([Source](https://github.com/Microsoft/WSL/issues/3023)):
`strip --remove-section=.note.ABI-tag /usr/lib/x86_64-linux-gnu/libQt5Core.so.5` 

* Redirect `dbus` traffic to `localhost` ([Source](https://github.com/QMonkey/wsl-tutorial)):
Add these lines in `/etc/dbus-1/session.conf` file 

```xml
<listen>tcp:host=localhost,port=0,family=ipv4</listen>
<auth>ANONYMOUS</auth>
<allow_anonymous/>
```

* Change to non root user and run `startkde` to start Kubuntu desktop environment.
If DWM.exe (Desktop Window Manager) or ConHost.exe (Console Host)
shows high CPU/RAM usage then redirect the command output with `startkde > /dev/null 2>&1` command. 

### Notes:

* If some packages are broken then use any one of these three commands to fix those: 

```bash
apt --fix-broken install
apt --mix-fissing upgrade
dpkg --configure -a
```

* Do not execute `startkde` with root user. 

* Allow KDE binaries in Windows Firewall to auto-download some Wallpapers, Themes etc. 


