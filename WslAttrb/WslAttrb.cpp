#include "WslAttrb.hpp"

void Usage(wchar_t* prog) {

	printf(
		"\n Usage: %ls [-] [option] [filepath]\n"
		" Configure LXSS attributes in WSL with user permission\n"
		" Options:\n"
		"    -a: <path>                    add DRVFS metadata.\n"
		"    -c: <source> <destination>    copy attributes.\n"
		"    -g: <path>                    get attributes.\n"
		"    -s: <path>                    set attributes.\n", prog);
}

void addDrvfs(wchar_t* src);
void copyEa(wchar_t* src, wchar_t* dst);
void getEa(wchar_t* src);
void setEa(wchar_t* src);

int wmain(int argc, wchar_t* argv[]) {

	if (argc < 3) {
		Usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	else if (wcscmp(argv[1], L"-a") == 0) {
		addDrvfs(argv[2]);
		return 0;
	}
	else if (wcscmp(argv[1], L"-c") == 0) {
		copyEa(argv[2], argv[3]);
		return 0;
	}
	else if (wcscmp(argv[1], L"-g") == 0) {
		getEa(argv[2]);
		return 0;
	}
	else if (wcscmp(argv[1], L"-s") == 0) {
		setEa(argv[2]);
		return 0;
	}
	else {
		printf("\n Unknown argument.\n");
		Usage(argv[0]);
		exit(EXIT_FAILURE);
	}
}
