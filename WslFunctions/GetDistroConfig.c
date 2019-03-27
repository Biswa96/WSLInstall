#include <stdio.h>
#include <Windows.h>
#include <wslapi.h>

int main(void)
{
    int wargc;
    wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

    ULONG Version, DefaultUID, DefaultEnvCnt;
    WSL_DISTRIBUTION_FLAGS WslFlags;
    PSTR* DefaultEnv = NULL;
    HRESULT result = WslGetDistributionConfiguration(wargv[1],
                                                     &Version,
                                                     &DefaultUID,
                                                     &WslFlags,
                                                     &DefaultEnv,
                                                     &DefaultEnvCnt);

    if (result == S_OK)
    {
        printf("Version: %lu\n"
               "DefaultUID: %lu\n"
               "WslFlags: %i\n"
               "Default Environment Variables Array: %s\n"
               "Default Environment Variables Count: %lu\n",
               Version, DefaultUID, WslFlags, *DefaultEnv, DefaultEnvCnt);
    }
    else
        printf("Error: 0x%08lX\n", result);
}
