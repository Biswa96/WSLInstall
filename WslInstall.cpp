#include <Windows.h>

typedef int (WINAPI* RegisterDistro)(PCWSTR, PCWSTR);
int wmain(int argc, wchar_t *argv[])
{
	HMODULE dll = LoadLibraryExW(L"wslapi.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
	RegisterDistro func = (RegisterDistro)GetProcAddress(dll, "WslRegisterDistribution");
	func(argv[1], argv[2]);
}
//END_10_lines//