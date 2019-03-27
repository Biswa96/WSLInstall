#include <stdio.h>
#include <Windows.h>
#include <wslapi.h>

int main(void)
{
    int wargc;
    wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

    HRESULT result = WslConfigureDistribution(wargv[1],
                                              1000,
                                              WSL_DISTRIBUTION_FLAGS_DEFAULT);

    if (result != S_OK)
        printf("Error: 0x%08lX\n", result);
}
