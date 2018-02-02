#include "WslRegistry.h"

/* Command Options: 1. Distribution Name 2. Installation full path */
int main(int argc, char* argv[]) {

	if (argc != 3) exit(EXIT_FAILURE);
	long res[5];

	GUID guid;
	CoCreateGuid(&guid);

	wchar_t guidString[STRING_LENGTH];
	StringFromGUID2(guid, guidString, STRING_LENGTH);

	char distroID[STRING_LENGTH];
	wcstombs(distroID, guidString, STRING_LENGTH);
	char registry[MAX_PATH] = "Software\\Microsoft\\Windows\\CurrentVersion\\Lxss\\";
	strcat(registry, distroID);

	HKEY hKey;
	res[0] = RegCreateKeyExA(HKEY_CURRENT_USER, registry, NULL, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	Log(res[0]);

	res[1] = RegSetValueExA(hKey, "DistributionName", NULL, REG_SZ, (const BYTE*)argv[1], strlen(argv[1]) + 1);
	Log(res[1]);

	res[2] = RegSetValueExA(hKey, "BasePath", NULL, REG_SZ, (const BYTE*)argv[2], strlen(argv[2]) + 1);
	Log(res[2]);

	int state = INSTALLED;
	res[3] = RegSetValueExA(hKey, "State", NULL, REG_DWORD, (const BYTE*)&state, sizeof(ULONG));
	Log(res[3]);

	int flag = ENABLE_ALL;
	res[4] = RegSetValueExA(hKey, "Flags", NULL, REG_DWORD, (const BYTE*)&flag, sizeof(ULONG));
	Log(res[4]);

	RegCloseKey(hKey);
}

/*END-42*/