# WSLInstall
Install any GNU/Linux distribution userspace in Windows Subsystem for Linux (WSL) with compressed RootFS tarballs :package: (tar.gz) or with Docker containers :whale: or with ISO files :cd: 

## Build

Clone this GitHub repository with this link https://github.com/Biswa96/WSLInstall.git . Use MSBuild (or mingw-w64) to make executable file from project file(.vcxproj). Or use the makefile in `WslFunctions` folder. The project file only provides x64-Release version. 

## How to use

### WslInstall: Installs GNU/Linux distributions 

1. First make a folder where you want to install that distribution, that may be any partition of internal drives only. External drives are not supported now. 
2. Place both `WslInstall.exe` and `{distribution}.tar.gz` files in that same folder. 
3. Open command prompt in that folder and type the command like this: `WslInstall.exe <distro_name> <distribution.tar.gz>`. Always put a space between the two command arguments like between <distro_name> and <distribution.tar.gz>. 
4. After some seconds, that distribution will be installed. Confirm it with `wslconfig.exe /list /all` command. Also you may see a `rootfs` folder in that directory where you want to install.

### WsAttrb: Add NTFS extended attributes 

With WslAttrb you can add DRVFS metadata without mounting Windows partitions in WSL. Also it tries to fix if you accidentally edit/move Linux root files from Windows. You have to use absolute file path. For example, if you installed distro in `C:\foo\bar` and you want to fix `/bin/bash` then you have to use this command: `WslAttrb.exe -s C:\foo\bar\rootfs\bin\bash`. 

The command options are:

```WslAttrb.bat
Usage: WslAttrb.exe [-] [option] [filepath]
Configure LXSS attributes in WSL with user permission
Options:
-a: <path>                    add DRVFS metadata i.e. UID, GID, MODE. 
-c: <source> <destination>    copy attributes from <source> to <destination>. 
-g: <path>                    get attributes. 
-s: <path>                    set attributes or fix the file. 
```

## How does it work

* WslInstall: In the source code, the main function imports the [`WslRegisterDistribution`] function from `wslapi.dll` file. Then it passes the provided two commandline arguments in `distroName` and in `tarGzFilename` string parameters of that function respectively and the imported function installs that distribution. See details of [WSL Functions] and [WSL_DISTRIBUTION_FLAGS]. 

* WslAttrb: This adds `LXATTRB` extended attribute to fix the WSL files to be visible in Linux world. Also this configures three other DRVFS extended attributes viz. `$LXUID`, `$LXGID` and `$LXMOD` simultaneously. 

This is only for testing purposes. See [list of distributions](Distro_Links.md) that can be added in WSL and how to [make RootFS tar.gz](Make-RootFS-tar.gz.md) for further details. More features will come in future :wink: 

## Other repositories
1. [LxRunoffline](https://github.com/DDoSolitary/LxRunOffline.git)
2. [WSL-DistroLauncher](https://github.com/yuk7/WSL-DistroLauncher.git)
3. [runnix](https://github.com/npyl/runnix.git)
4. [miniwsl](https://github.com/0xbadfca11/miniwsl.git)
5. [wslbridge](https://github.com/rprichard/wslbridge.git)


## License

This project is licensed under GNU General Public License v3 or higher. See [LICENSE](LICENSE) for more details. You are free to study, change, modify the source code and make your own version and publish that. 

<!--Links-->

[`WslRegisterDistribution`]: https://msdn.microsoft.com/en-us/library/windows/desktop/mt826870(v=vs.85).aspx
[WSL Functions]: https://msdn.microsoft.com/en-us/library/windows/desktop/mt826874(v=vs.85).aspx
[WSL_DISTRIBUTION_FLAGS]: https://msdn.microsoft.com/en-us/library/windows/desktop/mt826872(v=vs.85).aspx
