#include <Windows.h>
#include <stdio.h>

typedef HRESULT (WINAPI* LaunchDistro)(
	PCWSTR  distroName,
	PCWSTR  command,
	BOOL    useCurrentWorkingDirectory,
	HANDLE  hStdIn,
	HANDLE  hStdOut,
	HANDLE  hStdErr,
	HANDLE* phProcess
	);

int main() {
	int wargc;
	wchar_t** wargv;
	wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);
	HMODULE dll = LoadLibraryExW(L"wslapi.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
	LaunchDistro func = (LaunchDistro)GetProcAddress(dll, "WslLaunch");
	HANDLE proc = nullptr;
	HRESULT result = func(wargv[1], wargv[2],
		true,
		GetStdHandle(STD_INPUT_HANDLE),
		GetStdHandle(STD_OUTPUT_HANDLE),
		GetStdHandle(STD_ERROR_HANDLE),
		&proc);
	CloseHandle(proc);
	
	if (result == S_OK) {
		printf("'%ls' runs command successfully\n", wargv[1]);
	}
	
	else
	printf("Error: 0x%x\n", result);
}
//end-36//