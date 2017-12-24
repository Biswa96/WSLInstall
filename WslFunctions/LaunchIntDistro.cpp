#include <Windows.h>
#include <stdio.h>

typedef HRESULT (WINAPI* LaunchIntDistro)(
	PCWSTR distroName,
	PCWSTR command,
	BOOL   useCurrentWorkingDirectory,
	DWORD  *pExitCode
	);

int main() {
	int wargc;
	wchar_t** wargv;
	wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);
	ULONG ExitCode;
	HMODULE dll = LoadLibraryExW(L"wslapi.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
	LaunchIntDistro func = (LaunchIntDistro)GetProcAddress(dll, "WslLaunchInteractive");
	HRESULT result = func(wargv[1], wargv[2], true, &ExitCode);
	
	if (result == S_OK)
		printf("'%ls' runs command successfully\n", wargv[1]);
	else
		printf("Error: 0x%x\n", result);
		ExitProcess(ExitCode);
}
//end-26//