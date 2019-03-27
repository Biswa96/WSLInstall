#include <stdio.h>
#include <Windows.h>
#include <wslapi.h>

int main(void)
{
    int wargc;
    wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

    BOOL result = WslIsDistributionRegistered(wargv[1]);

    if (result)
        printf("Distribution name '%ls' is registered\n", wargv[1]);
    else
        printf("Distribution name '%ls' is not registered\n", wargv[1]);
}
