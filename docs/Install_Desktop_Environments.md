# Install any desktop environment in WSL

## Requirements

* Latest Windows 10 Pro with WSL feature enabled. 

* Any distribution installed in WSL. All of the following methods are done in Ubuntu but it can be used in others distributions also, package manager will be different. 

* Any X11 server in Windows side, for example, XMing, VcxSrv, X410 etc.

## Install KDE

The full download and installation procedure takes 3±1 hours depending on your network and hardwares because [I/O in WSL](https://github.com/Microsoft/WSL/issues/873) is very much slower than actual GNU/Linux systems. 

### Steps:

* Update and upgrade: `sudo apt-get update; sudo apt-get upgrade -y` 

* Install Kubuntu DE (~1 GB) ([Source](https://itsfoss.com/install-kde-on-ubuntu/)): `sudo apt-get install kubuntu-desktop` 

* Optional packages: `sudo apt-get install kstart kde-plasma-desktop kscreen konq-plugins` 

* Install all Qt5 libraries: `sudo apt-get install libqt5*` 

* Install others: `sudo apt-get binutils dbus-x11` 

* Remove `.note.ABI-tag` section ([Source](https://github.com/Microsoft/WSL/issues/3023)): `sudo strip --remove-section=.note.ABI-tag /usr/lib/x86_64-linux-gnu/libQt5Core.so.5` 

* Redirect `dbus` traffic to `localhost` ([Source](https://github.com/QMonkey/wsl-tutorial)): Add these lines in `/etc/dbus-1/session.conf` file 

```xml
<listen>tcp:host=localhost,port=0,family=ipv4</listen>
<auth>ANONYMOUS</auth>
<allow_anonymous/>
```

* Add these variables in `~/.bashrc` file: 

```bash
export DISPLAY=:0.0
export LIBGL_ALWAYS_INDIRECT=1
```

* Run VcxSrv with "One large window" and display number 0 (zero). Alternatively use this command: `vcxsrv.exe :0 -clipboard -wgl` 

* Change to non root user and run `startkde` to start Kubuntu desktop environment. If DWM.exe (Desktop Window Manager) or ConHost.exe (Console Host) shows high CPU/RAM usage then redirect the command output with `startkde > /dev/null 2>&1` command. 

### Notes:

* If some packages are broken then use any one of these three commands to fix those: 

```bash
sudo apt-get --fix-broken install
sudo apt-get --mix-fissing upgrade
sudo dpkg --configure -a
```

* Do not execute `startkde` with root user. 

* Allow KDE binaries in Windows Firewall to auto-download some Wallpapers, Themes etc. 


