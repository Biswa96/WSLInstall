#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_NO_STATUS
#include <Windows.h>
#undef WIN32_NO_STATUS
#include <winternl.h>
#include <ntstatus.h>
#include <stdio.h>
#include <ctime> //for time(0)//
#include <sys/stat.h> //for stat()//
#pragma comment(lib, "ntdll.lib")

struct EaData {
	short Flags;
	short Version;
	long mode;
	long uid;
	long gid;
	long rdev;
	long atime_nsec;
	long mtime_nsec;
	long ctime_nsec;
	long long atime;
	long long mtime;
	long long ctime;
};

struct FILE_FULL_EA_INFORMATION {
	ULONG  NextEntryOffset;
	UCHAR  Flags;
	UCHAR  EaNameLength;
	USHORT EaValueLength;
	CHAR   EaName[1];
};

const char* lxattrb = "LXATTRB";
const int lxattrbSize = 7; //size of LXATTRB attribute without null byte//
const int EaBufferSize = sizeof(FILE_FULL_EA_INFORMATION) + lxattrbSize + sizeof(EaData);

extern "C" BOOLEAN NTAPI RtlDosPathNameToNtPathName_U(
	_In_ PWSTR DosFileName,
	_Out_ PUNICODE_STRING NtFileName,
	_Out_opt_ PWSTR* FilePart,
	_Out_opt_ PVOID RelativeName
);

extern "C" NTSTATUS NTAPI NtQueryEaFile(
	_In_     HANDLE           FileHandle,
	_Out_    PIO_STATUS_BLOCK IoStatusBlock,
	_Out_    PVOID            Buffer,
	_In_     ULONG            Length,
	_In_     BOOLEAN          ReturnSingleEntry,
	_In_opt_ PVOID            EaList,
	_In_     ULONG            EaListLength,
	_In_opt_ PULONG           EaIndex,
	_In_     BOOLEAN          RestartScan
);

extern "C" NTSTATUS WINAPI NtSetEaFile(
	_In_  HANDLE           FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_  PVOID            Buffer,
	_In_  ULONG            Length
);

HANDLE GetFileHandle(wchar_t* DosFileName, bool write ) {

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
