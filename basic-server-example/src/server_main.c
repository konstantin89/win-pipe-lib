#include <stdio.h>
#include <stdlib.h>

#include "pipe.h"
#include "pipe_wrapper.h"
#include "pipe_operation_status.h"

#define EXET_CODE_ERROR 1
#define EXET_CODE_SUCCESS 0

#define BASIC_SERVER_PIPE_NAME L"\\\\.\\pipe\\basic-server-pipe"
#define PIPE_BUFFER_SIZE 64

int basicServerExample()
{
	PipeOperationStatus opStatus = 0;
	PPipe pipePtr = NULL;
	
	pipePtr = (PPipe)malloc(sizeof(Pipe));

	if (pipePtr == NULL)
	{
		printf("[X] Failed to allocate memory for pipe \n");

		return EXET_CODE_ERROR;
	}

	opStatus = CreateSyncPipe(BASIC_SERVER_PIPE_NAME, PIPE_BUFFER_SIZE, pipePtr);

	if (opStatus != Success)
	{
		printf("[X] CreateSyncPipe failed with error [%d] \n", opStatus);
	}

	ConnectNamedPipe(pipePtr->handle, NULL);

	for (unsigned int i = 0; i < 100; i++)
	{
		DWORD bytesWritten;
		PipeOperationStatus opStatus = 0;

		opStatus = WriteBuffer(pipePtr, (char*)&i, sizeof(unsigned int), &bytesWritten);

		if (opStatus != Success)
		{
			printf("[X] WriteBuffer failed with error [%d] \n", opStatus);
		}

		else
		{
			printf("[V] Written [%d] bytes \n", bytesWritten);
		}

	}
	
	DisconnectPipe(pipePtr);

	return EXET_CODE_SUCCESS;
}

int main()
{
	return basicServerExample();
}
