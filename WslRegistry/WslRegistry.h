#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <Objbase.h>
#include <stdio.h>

#define STRING_LENGTH 40
#define Log(x) (x == ERROR_SUCCESS) ? printf("Success\n") : printf("Failed\n")

enum FLAGS {
	NONE = 0,
	ENABLE_INTEROP = 1,
	APPEND_NT_PATH = 2,
	ENABLE_DRIVE_MOUNTING = 4,
	ENABLE_ALL = 7
};

enum STATES {
	INSTALLING = 3,
	INSTALLED = 1
};

/*END-22*/