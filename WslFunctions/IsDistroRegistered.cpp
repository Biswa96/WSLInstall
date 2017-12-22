#include <windows.h>
#include <stdio.h>

typedef BOOL(WINAPI* IsDistroRegistered)(
	PCWSTR distroName
	);

int main() {
	int wargc;
	wchar_t** wargv;
	wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);
	HMODULE dll = LoadLibraryExW(L"wslapi.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
	IsDistroRegistered func = (IsDistroRegistered)GetProcAddress(dll, "WslIsDistributionRegistered");
	BOOL result = func(wargv[1]);

	if (result == true) {
		printf("Distribution name '%ls' is registerd\n", wargv[1]);
	}

	if (result == false) {
		printf("Distribution name '%ls' is not registerd\n", wargv[1]);
	}
}
//end-24//