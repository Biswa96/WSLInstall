#include <Windows.h>
#include <stdio.h>

typedef HRESULT (WINAPI* RegisterDistro)(
	PCWSTR distroName,
	PCWSTR tarGzFilename
	);

int main() {
	int wargc;
	wchar_t** wargv;
	wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);
	HMODULE dll = LoadLibraryExW(L"wslapi.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
	RegisterDistro func = (RegisterDistro)GetProcAddress(dll, "WslRegisterDistribution");
	HRESULT result = func(wargv[1], wargv[2]);
	
	if (result == S_OK) {
		printf("Distribution '%ls' is successfully installed\n", wargv[1]);
	}
	
	else
	printf("Error: 0x%x\n", result);
}
//end-24//