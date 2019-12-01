# WSLInstall

Install any GNU/Linux distribution userspace in Windows Subsystem for Linux (WSL)
with compressed RootFS tarballs :package: (tar.gz) or
with Docker containers :whale: or with ISO files :cd: 

## Build

Clone this GitHub repository with this link https://github.com/Biswa96/WSLInstall.git .
Use MSBuild (or mingw-w64) to make executable file from project file(.vcxproj).
Or use the makefile in `WslFunctions` folder. The project file only provides x64-Release version. 

### Build wslapi export libraries:

* Generate DEF file: `gendef /c/Windows/System32/wslapi.dll` 
* For MSVC: `lib /DEF:wslapi.def /MACHINE:X64` 
* For GCC: `dlltool -D /c/Windows/System32/wslapi.dll -d wslapi.def -l libwslapi.a` 

wslapi export library was added in latest mingw-64 toolchain. See this commits
for further details:

* [wslapi export library](https://sourceforge.net/p/mingw-w64/mingw-w64/ci/bfd2db7ac52c48fb48a679f41b6e0ea6e815f047/)
* [wslapi header file](https://sourceforge.net/p/mingw-w64/mingw-w64/ci/a04227bc74288284755304089f243989ae50c7e5/)

## How to use

### WslInstall: Installs GNU/Linux distributions 

1. First make a folder where you want to install that distribution,
that may be any partition of internal drives only. External drives are not supported now. 
2. Place both `WslInstall.exe` and `{distribution}.tar.gz` files in that same folder. 
3. Open command prompt in that folder and type the command like this:
`WslInstall.exe <distro_name> <distribution.tar.gz>`. Always put a space
between the two command arguments like between <distro_name> and <distribution.tar.gz>. 
4. After some seconds, that distribution will be installed. Confirm it with
`wslconfig.exe /list /all` command. Also you may see a `rootfs` folder in that
directory where you want to install.

## How does it work

* WslInstall: In the source code, the main function imports the
[`WslRegisterDistribution`] function from `wslapi.dll` file. Then it passes
the provided two commandline arguments in `distroName` and in `tarGzFilename`
string parameters of that function respectively and the imported function
installs that distribution. See details of [WSL Functions] and [WSL_DISTRIBUTION_FLAGS]. 


## Table Of Contents:

* Docs:
  - [Install any distribution in WSL](docs/Install_Distributions.md)
  - [Install any desktop environment in WSL](docs/Install_Desktop_Environments.md)
  - [List of distributions](docs/Distro_Links.md)
  - [Make rootfs tarball](docs/Make_RootFS.md)
  - [Chroot into ARMv8 64bit (AARCH64) distribution](docs/Chroot_ARM64_Linux_Distro.md)

* Tools:
  - DistroLink: Create a shortcut file aka. shell link with `\\wsl$` path.


## Other repositories
1. [LxRunoffline](https://github.com/DDoSolitary/LxRunOffline.git)
2. [WSL-DistroLauncher](https://github.com/yuk7/WSL-DistroLauncher.git)
3. [runnix](https://github.com/npyl/runnix.git)
4. [miniwsl](https://github.com/0xbadfca11/miniwsl.git)
5. [wslbridge](https://github.com/rprichard/wslbridge.git)


## License

This project is licensed under GNU General Public License v3 or higher. See [LICENSE](LICENSE) for more details. You are free to study, change, modify the source code and make your own version and publish that. 

<!--Links-->

[`WslRegisterDistribution`]: https://docs.microsoft.com/en-us/windows/desktop/api/wslapi/nf-wslapi-wslregisterdistribution
[WSL Functions]: https://docs.microsoft.com/en-us/windows/desktop/api/wslapi/
[WSL_DISTRIBUTION_FLAGS]: https://docs.microsoft.com/en-us/windows/desktop/api/wslapi/ne-wslapi-wsl_distribution_flags
