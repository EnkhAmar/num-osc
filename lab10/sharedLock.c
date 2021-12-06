#include <windows.h>
#include <stdio.h>

int main(void){
	HANDLE hFileHandle;
	BOOL bSuccess;
	char *szFilename = "text1.txt";
	char szBuffer[256];

	//create new file
	//with both reading and writing authority
	//and reading and writing sharing
	hFileHandle = CreateFile(szFilename, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);

	if(hFileHandle == INVALID_HANDLE_VALUE){
		printf("Error creating handle to new file.\n");
		exit(EXIT_FAILURE);
	}

	//lock the file for the buffer length
	bSuccess = LockFile(hFileHandle, 0, 0, sizeof(szBuffer), 0);
	if(bSuccess){
		printf("File lock on %s secured.\n", szFilename);
	}

	//now let's release the lock
	// bSuccess = UnlockFile(hFileHandle, 0, 0, sizeof(szBuffer), 0);

	// if(bSuccess){
	// 	printf("File lock on %s released.\n", szFilename);
	// }

	//close the handle
	CloseHandle(hFileHandle);
	return 0;
}
