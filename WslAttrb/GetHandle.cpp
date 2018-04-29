#include "WslAttrb.hpp"

HANDLE GetFileHandle(wchar_t* DosFileName, bool write) {

	UNICODE_STRING FileName;
	IO_STATUS_BLOCK IoStatusBlock;
	OBJECT_ATTRIBUTES ObjectAttributes;
	ACCESS_MASK DesiredAccess = GENERIC_READ;
	HANDLE FileHandle;
	NTSTATUS res;
	RtlDosPathNameToNtPathName_U(DosFileName, &FileName, NULL, NULL);
	InitializeObjectAttributes(&ObjectAttributes, &FileName, 0, NULL, NULL);

	// GENERIC_WRITE contains FILE_WRITE_EA File Access Rights //
	if (write) {
		DesiredAccess |= GENERIC_WRITE;
	}

	res = NtCreateFile(&FileHandle, DesiredAccess, &ObjectAttributes, &IoStatusBlock, NULL, 0,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, FILE_OPEN_IF, 0, NULL, 0);
	if (res != STATUS_SUCCESS) {
		printf("NtCreateFile Error: 0x%x\n", res);
		exit(EXIT_FAILURE);
	}
	return FileHandle;
}