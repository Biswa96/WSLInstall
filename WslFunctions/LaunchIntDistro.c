#include <stdio.h>
#include <Windows.h>
#include <wslapi.h>

int main(void)
{
    int wargc;
    wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

    ULONG ExitCode = 0;
    HRESULT result = WslLaunchInteractive(wargv[1],
                                          wargv[2],
                                          TRUE,
                                          &ExitCode);
    ExitProcess(ExitCode);

    if (result != S_OK)
        printf("Error: 0x%08lX\n", result);
}
