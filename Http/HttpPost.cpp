// HttpPost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <winnt.h>
#include <winhttp.h>
#include <memory>
#pragma comment(lib, "winhttp.lib")
using namespace std;

int PostFile(wchar_t* file, wchar_t* url )
{
	DWORD error = 0;
	auto free = [](char* &b)->void {
		if (b != NULL) {
			delete[] b;
			b = NULL;
		}			
	};

	HANDLE hFile = NULL;
	if ((hFile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
		error = GetLastError();
		wprintf_s(L"Failed to open %s, error %d\n", file, error);
		goto Exit;
	}

	LARGE_INTEGER szFile;
	if (GetFileSizeEx(hFile, &szFile) == FALSE) {
		error = GetLastError();
		wprintf_s(L"Failed to get the size of %s, error %d\n", file, error);
		CloseHandle(hFile);
		goto Exit;
	}

    HINTERNET hSession = NULL;
    if ((hSession = WinHttpOpen(L"", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0)) == NULL) {
		error = GetLastError();
		wprintf_s(L"Failed to create a session to %s, error %d\n", url, error);
		goto Exit;
	}
	
	HINTERNET hConnect = NULL;
    if ((hConnect = WinHttpConnect(hSession, url, INTERNET_DEFAULT_PORT, 0)) == NULL) {
		error = GetLastError();
		wprintf_s(L"Failed to create a connection to %s, error %d\n", url, error);
		goto Exit;
	}

	HINTERNET hRequest = NULL;
	if ((hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/telemetry.request", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0)) == NULL) {
		error = GetLastError();
		wprintf_s(L"Failed to create a request to %s, error %d\n", url, error);
		goto Exit;
	}

	if (WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, szFile.LowPart, 0) == FALSE) {
		error = GetLastError();
		wprintf_s(L"Failed to send a request to %s, error %d\n", url, error);
		goto Exit;
	}

	const DWORD szChunk = 1024;
	char bufChunk[szChunk];
	DWORD bytesRead = 0;
	DWORD bytesWritten = 0;
	do {
		if (ReadFile(hFile, bufChunk, szChunk, &bytesRead, NULL) == FALSE) {
			error = GetLastError();
			wprintf_s(L"Failed to read %s, error %d\n", file, error);
			break;
		}
		if (bytesRead > 0) {
			if (WinHttpWriteData(hRequest, bufChunk, bytesRead, &bytesWritten) == FALSE) {
				error = GetLastError();
				wprintf_s(L"Failed to post %s, error %d\n", file, error);
				break;
			}
		} else {
			break;
		}
	} while (true);

	if (WinHttpReceiveResponse(hRequest, NULL) == FALSE) {
		error = GetLastError();
		wprintf_s(L"Failed to get a response from %s, error %d\n", url, error);
		goto Exit;
	}
	
	wprintf_s(L"Posted %s to %s, %d\n", file, url, error);
	
	DWORD dwSize = 0;	
	WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, WINHTTP_NO_OUTPUT_BUFFER, &dwSize, WINHTTP_NO_HEADER_INDEX);
	if(GetLastError( ) == ERROR_INSUFFICIENT_BUFFER) {
		unique_ptr<wchar_t[]> pHeader(new wchar_t[dwSize/sizeof(wchar_t)]);
		if (WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, pHeader.get(), &dwSize, WINHTTP_NO_HEADER_INDEX) == FALSE) {
			error = GetLastError();
			wprintf_s(L"Failed to get the response header, error %d\n", error);
			goto Exit;
        }
		wprintf_s(L"%s", pHeader.get());
    }

	DWORD dwMaxSize = 0;
	DWORD dwDownloaded = 0;
	char* buffer = NULL;	
	do {
		if (WinHttpQueryDataAvailable(hRequest, &dwSize) == FALSE) {
			error = GetLastError();
			wprintf_s(L"Failed to query data from %s, error %d\n", url, error);
			break;
		}

		if (dwSize == 0) {
			break;
		}

		if (dwSize > dwMaxSize) {
			free(buffer);
			if ((buffer = new char[dwSize + 1]) == NULL) {
				wprintf_s(L"Failed to allocate a buffer of %d bytes\n", dwSize + 1);
				break;
			}
			dwMaxSize = dwSize;			
		}

		ZeroMemory(buffer, dwSize + 1);

		if (WinHttpReadData(hRequest, buffer, dwSize, &dwDownloaded) == FALSE) {
			error = GetLastError();
			wprintf_s(L"Failed to receive data from %s, %d, %d, error %d\n", url, dwSize, dwDownloaded, error);
			break;
		} else {
			printf_s("%s", buffer);
		}

		if (dwDownloaded == 0) {
			break;
		}
	} while(dwSize > 0);

	free(buffer);

Exit:
	if (hRequest != NULL) WinHttpCloseHandle(hRequest);
	if (hConnect != NULL) WinHttpCloseHandle(hConnect);
	if (hSession != NULL) WinHttpCloseHandle(hSession);
		
    return error;
}

int wmain(int argc, wchar_t* argv[])
{
	if (argc == 1) {
		wprintf_s(L"Usage: %s [Input] [Url]\n", argv[0]);
		return -1;
	}

	return PostFile(argv[1], argv[2]);
}

