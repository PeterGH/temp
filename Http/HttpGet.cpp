// HttpGet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <strsafe.h>
#include <winhttp.h>
#include <memory>
#pragma comment(lib, "winhttp.lib")
using namespace std;

int wmain(int argc, wchar_t* argv[])
{
	if (argc == 1) {
		wprintf_s(L"Usage: %s [Url]\n", argv[0]);
		return -1;
	}

	DWORD error = 0;
	auto free = [](char* &b)->void {
		if (b != NULL) {
			delete[] b;
			b = NULL;
		}
	};
	
	wchar_t scheme[6] = {L'h', L't', L't', L'p'};
	wchar_t host[256];
	wchar_t path[2049];
	
	wchar_t* p = NULL;
	if ((p = wcsstr(argv[1], L"://")) != NULL) {
		if (FAILED(StringCchCopy(scheme, 5, argv[1]))) {
			error = GetLastError();
			wprintf_s(L"Failed to get scheme from %s, error %d\n", argv[1], error);
			goto Exit;
		}
	}
	wprintf_s(L"Scheme: %s\n", scheme);

	HINTERNET hSession = NULL;
	if ((hSession = WinHttpOpen(L"", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0)) == NULL) {
		error = GetLastError();
		wprintf_s(L"Failed to create an HTTP session to %s, error %d\n", argv[1], error);
		goto Exit;
	}
	
	HINTERNET hConnect = NULL;
	if ((hConnect = WinHttpConnect(hSession, argv[1], INTERNET_DEFAULT_PORT, 0)) == NULL) {
		error = GetLastError();
		wprintf_s(L"Failed to create an HTTP connection to %s, error %d\n", argv[1], error);
		goto Exit;
	}

	HINTERNET hRequest = NULL;
	if ((hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0)) == NULL) {
		error = GetLastError();
		wprintf_s(L"Failed to create an HTTP request to %s, error %d\n", argv[1], error);
		goto Exit;
	}

	if (WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) == FALSE) {
		error = GetLastError();
		wprintf_s(L"Failed to send an HTTP request to %s, error %d\n", argv[1], error);
		goto Exit;
	}

	if (WinHttpReceiveResponse(hRequest, NULL) == FALSE) {
		error = GetLastError();
		wprintf_s(L"Failed to receive an HTTP response from %s, error %d\n", argv[1], error);
		goto Exit;
	}

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
			wprintf_s(L"Failed to query data from %s, error %d\n", argv[1], error);
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
			wprintf_s(L"Failed to receive data from %s, %d, %d, error %d\n", argv[1], dwSize, dwDownloaded, error);
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
	auto close = [](HINTERNET h)->void {
		if (h != NULL) {
			WinHttpCloseHandle(h);
		}
	};
	close(hRequest);
	close(hConnect);
	close(hSession);
	return error;
}

