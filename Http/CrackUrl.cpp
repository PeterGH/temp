// CrackUrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <winhttp.h>
#include <strsafe.h>
#pragma comment(lib, "winhttp.lib")

int wmain(int argc, wchar_t* argv[])
{
	if (argc == 1) {
		wprintf_s(L"Usage: %s [Url]\n", argv[0]);
		return -1;
	}
	DWORD error = 0;

	URL_COMPONENTS url;
	size_t szUrl = sizeof(URL_COMPONENTS);
	ZeroMemory(&url, szUrl);
	url.dwStructSize = szUrl;
	url.dwSchemeLength = 1;
	url.dwHostNameLength = 1;
	url.dwUserNameLength = 1;
	url.dwPasswordLength = 1;
	url.dwUrlPathLength = 1;
	url.dwExtraInfoLength = 1;

	size_t szUrlLength;
	if (FAILED(StringCchLength(argv[1], _MAX_PATH, &szUrlLength))) {
		error = GetLastError();
		wprintf_s(L"Failed to get the length of %s, error %d\n", argv[1], error);
		return error;
	}

	if (WinHttpCrackUrl(argv[1], szUrlLength, 0, &url) == FALSE) {
		error = GetLastError();
		wprintf_s(L"Failed to crach %s, error %d\n", argv[1], error);
		return error;
	}

	wprintf_s(L"URL_COMPONENTS:\n");
	wprintf_s(L"\tdwStructSize\t%d\n", url.dwStructSize);
	wprintf_s(L"\tlpszScheme\t%s\n", url.lpszScheme);
	wprintf_s(L"\tdwSchemeLength\t%d\n", url.dwSchemeLength);
	wprintf_s(L"\tnSchem\t%d\n", url.nScheme);
	wprintf_s(L"\tlpszHostName\t%s\n", url.lpszHostName);
	wprintf_s(L"\tdwHostNameLength\t%d\n", url.dwHostNameLength);
	wprintf_s(L"\tnPort\t%d\n", url.nPort);
	wprintf_s(L"\tlpszUserName\t%s\n", url.lpszUserName);
	wprintf_s(L"\tdwUserNameLength\t%d\n", url.dwUserNameLength);
	wprintf_s(L"\tlpszPassword\t%s\n", url.lpszPassword);
	wprintf_s(L"\tdwPasswordLength\t%d\n", url.dwPasswordLength);
	wprintf_s(L"\tlpszUrlPath\t%s\n", url.lpszUrlPath);
	wprintf_s(L"\tdwUrlPathlength\t%d\n", url.dwUrlPathLength);
	wprintf_s(L"\tlpszExtraInfo\t%s\n", url.lpszExtraInfo);
	wprintf_s(L"\tdwExtraInfoLength\t%d\n", url.dwExtraInfoLength);
	return 0;
}

