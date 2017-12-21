# WSLInstall
Install any GNU/Linux distribution userspace in Windows Subsystem for Linux (WSL) with compressed RootFS tarballs :package: (tar.gz) or with Docker containers :whale: or with ISO files :cd: 

## Build

Clone this GitHub repository with this link https://github.com/Biswa96/WSLInstall.git . Use MSBuild (or mingw-w64) to make executable file from solution file (.sln). The solution file only provides x64-Release version. Or download the executable from release page.

## How to use

1. First make a folder where you want to install that distribution, that may be any partition or any drive. 
2. Place both `WslInstall.exe` and `{distribution}.tar.gz` files in that same folder. 
3. Open command prompt in that folder and type the command like this: `WslInstall.exe <distro_name> <distribution.tar.gz>`. Always put a space between the two command arguments i.e. between <distro_name> and <distribution.tar.gz>. 
4. After some seconds, that distribution will be installed. Confirm it with `wslconfig.exe /list /all` command. Also you may see a `rootfs` folder in that directory where you want to install.

## How does it work

In the source code, the main function imports the [`WslRegisterDistribution`](https://msdn.microsoft.com/en-us/library/windows/desktop/mt826870(v=vs.85).aspx) from `wslapi.dll` file. Then it passes the provided two commandline arguments in `distroName` and in `tarGzFilename` string parameters of that function respectively and the imported function installs that distribution. See details of [WSL Functions](https://msdn.microsoft.com/en-us/library/windows/desktop/mt826874(v=vs.85).aspx) and [WSL_DISTRIBUTION_FLAGS](https://msdn.microsoft.com/en-us/library/windows/desktop/mt826872(v=vs.85).aspx). Go through the [**Wiki page**](https://github.com/Biswa96/WSLInstall/wiki) for further details. More features will come in future :wink: 

## Other repositories
1. [LxRunoffline](https://github.com/DDoSolitary/LxRunOffline.git)
2. [WSL-DistroLauncher](https://github.com/yuk7/WSL-DistroLauncher.git)
3. [runnix](https://github.com/npyl/runnix.git)
4. [miniwsl](https://github.com/0xbadfca11/miniwsl.git)
5. [wslbridge](https://github.com/rprichard/wslbridge.git)

<!--END-26_Lines--!>
