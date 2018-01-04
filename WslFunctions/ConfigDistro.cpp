#include <Windows.h>
#include <iostream>

typedef enum _WSL_DISTRIBUTION_FLAGS {
	NONE = 0,
	ENABLE_INTEROP = 1,
	APPEND_NT_PATH = 2,
	ENABLE_DRIVE_MOUNTING = 4,
	ENABLE_ALL = 7	/* github.com/Microsoft/WSL/issues/2744 */
} WSL_DISTRIBUTION_FLAGS;

typedef enum _USER_ID {
	ROOT = 0,
	NORMAL_USER = 1000
} USER_ID;

typedef HRESULT(WINAPI* ConfigDistro)(
	PCWSTR distroName,
	ULONG defaultUID,
	WSL_DISTRIBUTION_FLAGS wslFlags
	);

int main() {
	int wargc, DefaultUID;
	wchar_t** wargv;
	wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);
	HMODULE dll = LoadLibraryExW(L"wslapi.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
	ConfigDistro func = (ConfigDistro)GetProcAddress(dll, "WslConfigureDistribution");
	HRESULT result = func(wargv[1], NORMAL_USER, ENABLE_ALL);

	if (result == S_OK)
		printf("Distribution '%ls' is configured successfully\n", wargv[1]);
	else
		printf("Error: 0x%x\n", result);
}
//end-36//