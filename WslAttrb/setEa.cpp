#include "WslAttrb.hpp"
#include <ctime> //for time(0)//
#include <sys/stat.h> //for stat()//

unsigned long setMode(wchar_t* path) {

	unsigned long mode = 0;
	int permission; printf("Enter file permission: ");
	scanf("%o", &permission);

	struct _stat s;
	int res = _wstat(path, &s);
	if (res == 0) {
		if (s.st_mode & _S_IFDIR)
			mode = _S_IFDIR | permission;
		else if (s.st_mode & _S_IFREG)
			mode = _S_IFREG | permission;

	/* Symbolic links and Hard links don't work */
	}
	return mode;
}

void setEa(wchar_t* src) {

	EaData eaData[sizeof(EaData)];
	memset(eaData, 0, sizeof(EaData)); // set all elements to zero //
	eaData->Version = 1;
	eaData->mode = setMode(src); // octate 0x81ff == 100777 //
	eaData->atime = eaData->ctime = eaData->mtime = time(0);

	char Buffer[EaBufferSize];
	FILE_FULL_EA_INFORMATION* EaBuffer = (FILE_FULL_EA_INFORMATION*)Buffer;
	EaBuffer->NextEntryOffset = 0;
	EaBuffer->Flags = 0;
	EaBuffer->EaNameLength = lxattrbSize;
	EaBuffer->EaValueLength = sizeof(EaData);
	strcpy(EaBuffer->EaName, lxattrb);
	
	// destination position is 8th bit after LXATTRB //
	memcpy(EaBuffer->EaName + (EaBuffer->EaNameLength + 1), &eaData, sizeof(EaData));

	IO_STATUS_BLOCK status;
	HANDLE FileHandle = GetFileHandle(src, TRUE);
	NTSTATUS res = NtSetEaFile(FileHandle, &status, EaBuffer, EaBufferSize);
	(res == STATUS_SUCCESS) ? printf("Successfully added attributes\n") : printf("NtSetEaFile Error: 0x%x\n", res);
}
