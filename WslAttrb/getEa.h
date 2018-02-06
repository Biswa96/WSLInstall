#pragma once
#include "definition.h"

void getEa(wchar_t* src) {

	NTSTATUS res;
	IO_STATUS_BLOCK IoStatusBlock;
	const int EaBufferSize = sizeof(FILE_FULL_EA_INFORMATION) + lxattrbSize + sizeof(EaData);
	FILE_FULL_EA_INFORMATION EaBuffer[EaBufferSize];

	res = NtQueryEaFile(GetFileHandle(src), &IoStatusBlock, EaBuffer, EaBufferSize, TRUE, NULL, 0, NULL, FALSE);
	if (res == STATUS_SUCCESS) {
		printf(" EaName: %s\n EaNameLength: %u\n EaValueLength: %u\n",
			EaBuffer->EaName,
			EaBuffer->EaNameLength,
			EaBuffer->EaValueLength);
	}
	else {
		printf("NtQueryEaFile Error: 0x%x\n", res);
	}
}
/*END-22*/