#include "WslAttrb.hpp"

void copyEa(wchar_t* src, wchar_t* dst) {

	NTSTATUS resA, resB;
	IO_STATUS_BLOCK IoStatusBlock;
	HANDLE srcFileHandle = GetFileHandle(src, FALSE);
	HANDLE dstFileHandle = GetFileHandle(dst, TRUE);
	char Buffer[EaBufferSize];
	FILE_FULL_EA_INFORMATION* EaBuffer = (FILE_FULL_EA_INFORMATION*)Buffer;

	resA = NtQueryEaFile(srcFileHandle, &IoStatusBlock, EaBuffer, EaBufferSize, TRUE, NULL, 0, NULL, FALSE);
	if (resA == STATUS_SUCCESS) {
		resB = NtSetEaFile(dstFileHandle, &IoStatusBlock, EaBuffer, EaBufferSize);
		(resB == STATUS_SUCCESS) ? printf("Successfully copied\n") : printf("NtSetEaFile Error: 0x%x\n", resB);
	}
	else 
		printf("NtQueryEaFile Error: 0x%x\n", resA);
}
