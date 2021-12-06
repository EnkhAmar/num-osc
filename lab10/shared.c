#include <windows.h>
#include <stdio.h>

int main(void){
	HANDLE hFileHandle;
	BOOL bSuccess;
	char *szFilename = "text1.txt";
	char szBuffer[256];

	hFileHandle = CreateFile(szFilename, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);

	if(hFileHandle == INVALID_HANDLE_VALUE){
		printf("Error creating handle to new file.\n");
		exit(EXIT_FAILURE);
	}

	bSuccess = LockFile(hFileHandle, 0, 0, sizeof(szBuffer), 0);
	if(bSuccess){
		printf("File lock on %s secured.\n", szFilename);
	}

	CloseHandle(hFileHandle);
	return 0;
}
