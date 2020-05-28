#pragma once

#include "pipe.h"
#include "pipe_operation_status.h"

PipeOperationStatus CreateSyncPipe(LPCWSTR pipeName, DWORD bufferSize, PPipe pipe);

PipeOperationStatus DisconnectPipe(PPipe pipe);

PipeOperationStatus OpenPipeWrapper(LPCWSTR pipeName, PPipe pipe);

PipeOperationStatus ClosePipeWrapper(PPipe pipe);

PipeOperationStatus WriteBuffer(PPipe pipe, char* buf, DWORD bufferLen, PDWORD bytesWritten);

PipeOperationStatus ReadBuffer(PPipe pipe, char* buf, DWORD bufferLen, PDWORD bytesRead);
