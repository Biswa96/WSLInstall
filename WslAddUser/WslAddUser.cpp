#include <stdio.h>
#include <wchar.h>
#include <windows.h>

typedef BOOL(WINAPI* IsDistroRegistered)(PCWSTR);
typedef HRESULT(WINAPI* LaunchIntDistro)(PCWSTR, PCWSTR, BOOL, DWORD*);
typedef HRESULT(WINAPI* ConfigDistro)(PCWSTR, ULONG, ULONG);

HMODULE dll = LoadLibraryExW(L"wslapi.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
IsDistroRegistered funcA = (IsDistroRegistered)GetProcAddress(dll, "WslIsDistributionRegistered");
LaunchIntDistro funcB = (LaunchIntDistro)GetProcAddress(dll, "WslLaunchInteractive");
ConfigDistro funcC = (ConfigDistro)GetProcAddress(dll, "WslConfigureDistribution");

int wmain(int argc, wchar_t* argv[])
{
	ULONG ExitCode;
	BOOL resA = funcA(argv[1]);
	if (resA)
	{
		printf("Distro '%ws' is registered\n Press any key to Continue to add user ....\n\n", argv[1]);
		getchar();

//add user//
		wchar_t addUser[300] = L"/usr/sbin/adduser --quiet --force-badname --disabled-password --gecos '' ";	//space required//
		wcscat_s(addUser, 300, argv[2]);
		printf("addUser command: %ws\n", addUser);
		HRESULT resB = funcB(argv[1], addUser, true, &ExitCode);
		printf("Hresult addUser: 0x%08lx\n Press any key to Continue to modify user ....\n\n", resB);
		getchar();

//modify user//
		wchar_t userMod[300] = L"/usr/sbin/usermod -aG adm,dialout,cdrom,floppy,sudo,audio,dip,video,plugdev ";	//space required//
		wcscat_s(userMod, 300, argv[2]);
		printf("userMod command: %ws\n", userMod);
		HRESULT resC = funcB(argv[1], userMod, true, &ExitCode);
		printf("Hresult userMod: 0x%08lx\n Press any key to Continue to add password ....\n\n", resC);
		getchar();

//add user password//
		wchar_t passWd[300] = L"/usr/bin/passwd ";	//space required//
		wcscat_s(passWd, 300, argv[2]);
		printf("passWd command: %ws\n", passWd);
		HRESULT resD = funcB(argv[1], passWd, true, &ExitCode);
		printf("Hresult passWd: 0x%08lx\n Press any key to Continue to get user id ....\n\n", resD);
		getchar();

//get user id//
		wchar_t userId[300] = L"/usr/bin/id -u ";	//space required//
		wcscat_s(userId, 300, argv[2]);
		printf("%ws\n", userId);
		HRESULT resE = funcB(argv[1], userId, true, &ExitCode);
		printf("Hresult userId: 0x%08lx\n Press any key to Continue to set user '%ws' as default ....\n\n", resE, argv[2]);
		getchar();

//set user as default//
		HRESULT resF = funcC(argv[1], 1000, 0x7);	//0x7 for all permission//
		printf("Hresult: 0x%08lx\n Default User is now: %ws \n\n", resF, argv[2]);

		ExitProcess(ExitCode);
	}

	if (!resA)
	{
		printf("There is no distribution with the supplied name '%ws'.\n\n", argv[1]);
		exit(0);
	}
}
//end-68//