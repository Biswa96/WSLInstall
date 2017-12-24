#include <Windows.h>
#include <stdio.h>

typedef HRESULT (WINAPI* GetDistroConfig)(
	PCWSTR distroName,
	ULONG* Version,
	ULONG* DefaultUID,
	int* WSL_DISTRIBUTION_FLAGS,
	PSTR** DefaultEnvironmentVariablesArray,
	ULONG* DefaultEnvironmentVariablesCount
	);

int main() {
	int wargc;
	wchar_t** wargv;
	wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);
	ULONG Version, DefaultUID, DefaultEnvCnt;
	int WslFlags;
	PSTR* DefaultEnv;
	HMODULE dll = LoadLibraryExW(L"wslapi.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
	GetDistroConfig func = (GetDistroConfig)GetProcAddress(dll, "WslGetDistributionConfiguration");
	HRESULT result = func(wargv[1], &Version, &DefaultUID, &WslFlags, &DefaultEnv, &DefaultEnvCnt);
	
	if (result == S_OK) {
	printf("Version: %lu\n"
		"DefaultUID: %lu\n"
		"WslFlags: %i\n"
		"Default Environment Variables Array: %s\n"
		"Default Environment Variables Count: %lu\n", Version, DefaultUID, WslFlags, &DefaultEnv, DefaultEnvCnt);
	}
	else
	printf("Error: 0x%x\n", result);
}
//end-34//