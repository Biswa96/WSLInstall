#include "WslInstall2.h"

int main(int argc, char **argv) {
	long res[6];
	GUID guid;
	CoCreateGuid(&guid);

	wchar_t* guidString;
	StringFromCLSID(guid, &guidString);
	printf("Distro ID: %ls\n", guidString);

	wchar_t registry[300] = L"Software\\Microsoft\\Windows\\CurrentVersion\\Lxss\\";
	wcscat(registry, guidString);
	printf("Registry Path: %ls\n", registry);

	/* convert wchar_t to char */
	char mbstr[300];
	wcstombs(mbstr, registry, 300);

	HKEY hKey;
	res[0] = RegCreateKeyExA(HKEY_CURRENT_USER, mbstr, NULL, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	Log(res[0], L"Registry created");

	res[1] = RegSetValueExA(hKey, "DistributionName", NULL, REG_SZ, (const BYTE*)argv[1], strlen(argv[1])+1);
	Log(res[1], L"Distribution name added");

	res[2] = RegSetValueExA(hKey, "BasePath", NULL, REG_SZ, (const BYTE*)argv[2], strlen(argv[2])+1);
	Log(res[2], L"Distribution path added");
	
	ULONG state = 1;
	res[3] = RegSetValueExA(hKey, "State", NULL, REG_DWORD, (const BYTE*)&state, sizeof(state));
	Log(res[3], L"State added");
	
	ULONG flag = 7;
	res[4] = RegSetValueExA(hKey, "Flags", NULL, REG_DWORD, (const BYTE*)&flag, sizeof(flag));
	Log(res[4], L"Flags added");

	res[5] = RegCloseKey(hKey);
	Log(res[5], L"RegCloseKey");
}
//end-42//