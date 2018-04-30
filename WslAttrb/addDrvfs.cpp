#include "WslAttrb.hpp"
#include <sys/stat.h>

/*Number of Extended Attributes*/
#define n 3 

const char* EaName[n] = { "$LXUID", "$LXGID", "$LXMOD" };
const unsigned long EaDataSize = offsetof(FILE_FULL_EA_INFORMATION, EaName) + sizeof(EaName[0]) + sizeof(ULONG);

void addDrvfs(wchar_t* src) {

	IO_STATUS_BLOCK IoStatusBlock;
	HANDLE handle = NULL;
	NTSTATUS res = -1;
	FILE_FULL_EA_INFORMATION* EaBuffer;
	char Buffer[EaDataSize * n];
	memset(Buffer, NULL, EaDataSize * n);
	char Temp[EaDataSize];
	ULONG uid, gid, mode, permission;

	printf("Enter UID: ");
	scanf("%d", &uid);

	printf("Enter GID: ");
	scanf("%d", &gid);

	printf("Enter file permission: ");
	scanf("%o", &permission);
	mode = _S_IFREG | permission;

	ULONG EaValue[3] = { uid, gid, mode};

	for (int i = 0; i < n; i++) {

		EaBuffer = (FILE_FULL_EA_INFORMATION*)Temp;
		memset(EaBuffer, NULL, EaDataSize);
		EaBuffer->NextEntryOffset = EaDataSize;

		if (i == n - 1) {
			EaBuffer->NextEntryOffset = NULL;
		}

		EaBuffer->Flags = NULL;
		EaBuffer->EaNameLength = (UCHAR)strlen(EaName[i]);
		EaBuffer->EaValueLength = sizeof(EaValue[i]);
		strcpy(EaBuffer->EaName, EaName[i]);
		memcpy(EaBuffer->EaName + EaBuffer->EaNameLength + 1, &EaValue[i], sizeof(EaValue[i]));
		memcpy(Buffer + i * EaDataSize, EaBuffer, EaDataSize);
	}
	
	handle = GetFileHandle(src, TRUE);
	res = NtSetEaFile(handle, &IoStatusBlock, &Buffer, EaDataSize * n);
	(res == STATUS_SUCCESS) ? printf("Success\n") : printf("NtSetEaFile Error: 0x%x\n", res);
}
