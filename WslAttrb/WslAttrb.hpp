#define _CRT_SECURE_NO_WARNINGS
#define WIN32_NO_STATUS
#include <Windows.h>
#undef WIN32_NO_STATUS
#include <winternl.h>
#include <ntstatus.h>
#include <stdio.h>
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

static const char lxattrb[] = "LXATTRB";
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

HANDLE GetFileHandle(wchar_t* DosFileName, bool write);
