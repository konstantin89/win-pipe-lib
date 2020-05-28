#include "pipe_wrapper.h"

#include <string.h>

PipeOperationStatus CreateSyncPipe(LPCWSTR pipeName, DWORD bufferSize, PPipe pipe)
{
	if (pipe == NULL)
	{
		return InvalidParam;
	}

	if (wcslen(pipeName) == 0)
	{
		return InvalidParam;
	}

	HANDLE pipeHandle = CreateNamedPipe(
		pipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		bufferSize,
		bufferSize,
		0,
		NULL);

	if (pipeHandle == INVALID_HANDLE_VALUE)
	{
		return GenericError;
	}

	pipe->handle = pipeHandle;

	return Success;
}

PipeOperationStatus OpenPipeWrapper(LPCWSTR pipeName, PPipe pipe)
{
	if (pipe == NULL)
	{
		return InvalidParam;
	}

	if (wcslen(pipeName) == 0)
	{
		return InvalidParam;
	}

	HANDLE pipeHandle = CreateFile(
		pipeName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (pipeHandle == INVALID_HANDLE_VALUE)
	{
		return GenericError;
	}

	pipe->handle = pipeHandle;

	return Success;
}


PipeOperationStatus DisconnectPipe(PPipe pipe)
{
	if (pipe == NULL)
	{
		return InvalidParam;
	}

	BOOL isDisconnectSucceed = DisconnectNamedPipe(pipe->handle);

	if (isDisconnectSucceed == 0)
	{
		return GenericError;
	}

	return Success;
}

PipeOperationStatus WriteBuffer(PPipe pipe, char* buf, DWORD bufferLen, PDWORD bytesWritten)
{
	if (pipe == NULL)
	{
		return InvalidParam;
	}

	if (pipe->handle == INVALID_HANDLE_VALUE)
	{
		return InvalidParam;
	}

	if (buf == NULL)
	{
		return InvalidParam;
	}

	if (bytesWritten == NULL)
	{
		return InvalidParam;
	}

	if (bufferLen == 0)
	{
		return InvalidParam;
	}

	BOOL writeReturnValue = WriteFile(
		pipe->handle,
		buf,
		bufferLen,
		bytesWritten,
		NULL);

	if (writeReturnValue == 0)
	{
		return GenericError;
	}

	return Success;
}

PipeOperationStatus ReadBuffer(PPipe pipe, char* buf, DWORD bufferLen, PDWORD bytesRead)
{
	if (pipe == NULL)
	{
		return InvalidParam;
	}

	if (pipe->handle == INVALID_HANDLE_VALUE)
	{
		return InvalidParam;
	}

	if (buf == NULL)
	{
		return InvalidParam;
	}

	if (bytesRead == NULL)
	{
		return InvalidParam;
	}

	if (bufferLen == 0)
	{
		return InvalidParam;
	}

	BOOL writeReturnValue = ReadFile(
		pipe->handle,
		buf,
		bufferLen,
		bytesRead,
		NULL);

	if (writeReturnValue == 0)
	{
		return GenericError;
	}

	return Success;
}

PipeOperationStatus ClosePipeWrapper(PPipe pipe)
{
	if (pipe == NULL)
	{
		return InvalidParam;
	}

	BOOL returnCode = CloseHandle(pipe->handle);

	if (returnCode == 0)
	{
		return GenericError;
	}

	return Success;
}
