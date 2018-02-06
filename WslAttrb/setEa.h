#pragma once
#include "definition.h"

void setEa(wchar_t* src) {

	EaData eaData[sizeof(EaData)];
	memset(eaData, 0, sizeof(EaData)); // set all elements to zero //
	eaData->Version = 1;
	int mode; printf("Enter file permission: ");
	scanf("%o", &mode);
	eaData->mode = 0x8000 | mode; // octate 0x81ff == 100777 //
	eaData->atime = eaData->ctime = eaData->mtime = time(0);

	const int EaBufferSize = sizeof(FILE_FULL_EA_INFORMATION) + lxattrbSize + sizeof(EaData);
	FILE_FULL_EA_INFORMATION EaBuffer[EaBufferSize];
	EaBuffer->NextEntryOffset = 0;
	EaBuffer->Flags = 0;
	EaBuffer->EaNameLength = lxattrbSize;
	EaBuffer->EaValueLength = sizeof(EaData);
	strcpy(EaBuffer->EaName, lxattrb);
	
	// destination position is 8th bit after LXATTRB //
	memcpy(EaBuffer->EaName + (EaBuffer->EaNameLength + 1), &eaData, sizeof(EaData));

	IO_STATUS_BLOCK status;
	NTSTATUS res = NtSetEaFile(GetFileHandle(src), &status, EaBuffer, EaBufferSize);
	(res == STATUS_SUCCESS) ? printf("Successfully added attributes\n") : printf("NtSetEaFile Error: 0x%x\n", res);
}

/* END-30*/