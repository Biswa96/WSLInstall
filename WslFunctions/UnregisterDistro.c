#include <stdio.h>
#include <Windows.h>
#include <wslapi.h>

int main(void)
{
    int wargc;
    wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

    HRESULT result = WslUnregisterDistribution(wargv[1]);

    if (result != S_OK)
        printf("Error: 0x%08lX\n", result);
}
