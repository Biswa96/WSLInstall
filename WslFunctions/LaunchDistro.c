#include <stdio.h>
#include <Windows.h>
#include <wslapi.h>

int main(void)
{
    int wargc;
    wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

    HANDLE ProcessHandle = NULL;
    HRESULT result = WslLaunch(wargv[1],
                               wargv[2],
                               TRUE,
                               GetStdHandle(STD_INPUT_HANDLE),
                               GetStdHandle(STD_OUTPUT_HANDLE),
                               GetStdHandle(STD_ERROR_HANDLE),
                               &ProcessHandle);
    CloseHandle(ProcessHandle);

    if (result != S_OK)
        printf("Error: 0x%08lX\n", result);
}
