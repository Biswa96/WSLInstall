#define _CRT_SECURE_NO_WARNINGS
#include <Objbase.h>
#include <iostream>
#include <Windows.h>

void Log(long result, wchar_t* function) {
	if (result == ERROR_SUCCESS) { printf("%ls successfully\n", function); }
	else { printf("%ls failed\n", function); }
}
//end-10//