#include "copyEa.h"
#include "getEa.h"
#include "setEa.h"

void Usage(wchar_t* appName) {
	printf(
		"\n Usage: %ls [option] [parameter]\n"
		" Command Options:\n"
		" -c: copy attributes <source> <destination>\n"
		" -g: get attributes <source>\n"
		" -s: set attributes <source>\n", appName);
}

int wmain(int argc, wchar_t* argv[]) {

	if (argc < 2) {
		Usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	if (wcscmp(argv[1], L"-c") == 0) {
		copyEa(argv[2], argv[3]);
		return 0;
	}
	if (wcscmp(argv[1], L"-g") == 0) {
		getEa(argv[2]);
		return 0;
	}
	if (wcscmp(argv[1], L"-s") == 0) {
		setEa(argv[2]);
		return 0;
	}
	else {
		printf("\n Unknown argument.\n");
		Usage(argv[0]);
		exit(EXIT_FAILURE);
	}
}
