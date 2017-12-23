#include <Windows.h>
#include <stdio.h>

typedef HRESULT (WINAPI* UnregisterDistro)(
	 PCWSTR distroName
	);

int main() {
	int wargc;
	wchar_t** wargv;
	wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);
	HMODULE dll = LoadLibraryExW(L"wslapi.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
	UnregisterDistro func = (UnregisterDistro)GetProcAddress(dll, "WslUnregisterDistribution");
	HRESULT result = func(wargv[1]);
	
	if (result == S_OK) {
		printf("Distribution '%ls' is successfully removed\n", wargv[1]);
	}
	
	else
	printf("Error: 0x%x\n", result);
	
}
//end-24//