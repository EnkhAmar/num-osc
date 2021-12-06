#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "tchar.h"

int _tmain(int argc, _TCHAR* argv[])
{
	BOOL bSuccess;
	HANDLE hFileHandle;
	TCHAR *filename = _T("text1.txt");
	OVERLAPPED structOverlap;

	hFileHandle = CreateFile(filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);

	if(hFileHandle == INVALID_HANDLE_VALUE){
		printf("Error creating file.\n");
		exit(EXIT_FAILURE);
	} else {
		_tprintf(_T("File %s created.\n"), filename);
	}

	//initialize structure
	ZeroMemory(&structOverlap, sizeof(structOverlap));

	bSuccess = LockFileEx(hFileHandle, LOCKFILE_EXCLUSIVE_LOCK, 0, 100, 0, &structOverlap);

	if(bSuccess){
		_tprintf(_T("Lock on file %s.\n"), filename);
	}

	//unlock file
	// bSuccess = UnlockFileEx(hFileHandle, 0, 100, 0, &structOverlap);

	// if(bSuccess){
	// 	printf("File unlocked.\n");
	// }

	return 0;
}