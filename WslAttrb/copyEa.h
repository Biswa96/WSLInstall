#pragma once
#include "definition.h"

void copyEa(wchar_t* src, wchar_t* dst) {

	NTSTATUS resA, resB;
	IO_STATUS_BLOCK IoStatusBlock;
	const int EaBufferSize = sizeof(FILE_FULL_EA_INFORMATION) + lxattrbSize + sizeof(EaData);
	FILE_FULL_EA_INFORMATION EaBuffer[EaBufferSize];

	resA = NtQueryEaFile(GetFileHandle(src), &IoStatusBlock, EaBuffer, EaBufferSize, TRUE, NULL, 0, NULL, FALSE);
	if (resA == STATUS_SUCCESS) {
		resB = NtSetEaFile(GetFileHandle(dst), &IoStatusBlock, EaBuffer, EaBufferSize);
		(resB == STATUS_SUCCESS) ? printf("Successfully copied\n") : printf("NtSetEaFile Error: 0x%x\n", resB);
	}
	else 
		printf("NtQueryEaFile Error: 0x%x\n", resA);
}

/*END-20*/