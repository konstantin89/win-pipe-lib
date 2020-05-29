#include <stdio.h>
#include <stdlib.h>

#include "pipe.h"
#include "pipe_wrapper.h"
#include "pipe_operation_status.h"

#define EXIT_CODE_ERROR 1
#define EXIT_CODE_SUCCESS 0

#define BASIC_SERVER_PIPE_NAME L"\\\\.\\pipe\\basic-server-pipe"
#define PIPE_BUFFER_SIZE 16

int basicClientExample()
{
	PipeOperationStatus opStatus = 0;
	PPipe pipePtr = NULL;

	pipePtr = (PPipe)malloc(sizeof(Pipe));

	if (pipePtr == NULL)
	{
		printf("[X] Failed to allocate memory for pipe \n");
		return EXIT_CODE_ERROR;
	}

	opStatus = OpenPipeWrapper(BASIC_SERVER_PIPE_NAME, pipePtr);

	if (opStatus != Success)
	{
		printf("[X] OpenPipe failed with error [%d] \n", opStatus);
		return EXIT_CODE_ERROR;
	}

	BOOL isReadSucceed = TRUE;
	char buffer[PIPE_BUFFER_SIZE];
	DWORD bytesRead;

	while (isReadSucceed)
	{

		opStatus = ReadBuffer(pipePtr, buffer, PIPE_BUFFER_SIZE, &bytesRead);

		if (opStatus != Success)
		{
			printf("[X] Read failed with error [%d] \n", opStatus);
			isReadSucceed = FALSE;
		}

		printf("[V] Readed [%d] bytes from pipe \n", bytesRead);

	}

	ClosePipeWrapper(pipePtr);

	return EXIT_CODE_SUCCESS;
}

int main()
{
	return basicClientExample();
}
