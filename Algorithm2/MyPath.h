#pragma once

#include <string>
#include <stdlib.h>
#include <vector>
#include <io.h>
#include <functional>
#include <ppl.h>
#include <iostream>
#include <concurrent_vector.h>
#include "MyString.h"

using namespace std;
using namespace Concurrency;

namespace My
{	
	class __declspec(dllexport) Path
	{
	private:
		wchar_t drive[_MAX_DRIVE];
		wchar_t directory[_MAX_DIR];
		wchar_t file[_MAX_FNAME];
		wchar_t extension[_MAX_EXT];
		
	public:
		Path(const wchar_t *);
		~Path(void) {}
		wstring FullPath(void) const;
		wstring Drive(void) const { return wstring(drive); }
		wstring Directory(void) const { return wstring(directory); }
		wstring File(void) const { return wstring(file); }
		wstring Extension(void) const { return wstring(extension); }

		static wchar_t * Combine(wchar_t * output, const wchar_t * parent, const wchar_t * child) {
			wcscpy_s(output, _MAX_PATH, parent);
			if (output[wcslen(output)-1] != L'\\') {
				wcscat_s(output, _MAX_PATH, L"\\");
			}
			wcscat_s(output, _MAX_PATH, child);
			return output;
		}

		static wchar_t * Combine(wchar_t * parent, const wchar_t * child) {
			if (parent[wcslen(parent)-1] != L'\\') {
				wcscat_s(parent, _MAX_PATH, L"\\");			
			}
			wcscat_s(parent, _MAX_PATH, child);
			return parent;
		}

		static vector<wstring> & GetItems(
			vector<wstring> & items, 
			const wstring & directory, 
			function<bool (struct _wfinddata_t &)> skip,
			const wstring & wildchar = L"*", 
			const bool recursive = false);
		
		static concurrent_vector<wstring> & GetItemsP(
			concurrent_vector<wstring> & items, 
			const wstring & directory, 
			function<bool (struct _wfinddata_t &)> skip,
			const wstring & wildchar = L"*", 
			const bool recursive = false);
		
		static vector<wstring>& GetDirectories(
			vector<wstring> & items, 
			const wstring & directory, 
			const wstring & wildchar = L"*", 
			const bool recursive = false) 
		{ 
			return GetItems(items, directory, 
				[](struct _wfinddata_t & item) -> bool { return wcscmp(item.name, L".") == 0 || wcscmp(item.name, L"..") == 0 || (item.attrib & _A_SUBDIR) == 0; },
				wildchar, recursive); 
		}

		static concurrent_vector<wstring>& GetDirectories(
			concurrent_vector<wstring> & items, 
			const wstring & directory, 
			const wstring & wildchar = L"*", 
			const bool recursive = false) 
		{ 
			return GetItemsP(items, directory, 
				[](struct _wfinddata_t & item) -> bool { return wcscmp(item.name, L".") == 0 || wcscmp(item.name, L"..") == 0 || (item.attrib & _A_SUBDIR) == 0; },
				wildchar, recursive); 
		}

		static vector<wstring>& GetFiles(
			vector<wstring> & items, 
			const wstring & directory, 
			const wstring & wildchar = L"*", 
			const bool recursive = false) 
		{
			// Valid attributes are:
			// _A_NORMAL	0x00
			// _A_RDONLY	0x01
			// _A_HIDDEN	0x02
			// _A_SYSTEM	0x04
			// _A_SUBDIR	0x10
			// _A_ARCH		0x20			
			return GetItems(items, directory, 
				[](struct _wfinddata_t & item) -> bool { return (item.attrib & _A_SUBDIR) != 0; },
				wildchar, recursive); 
		}

		static concurrent_vector<wstring>& GetFiles(
			concurrent_vector<wstring> & items, 
			const wstring & directory, 
			const wstring & wildchar = L"*", 
			const bool recursive = false) 
		{
			// Valid attributes are:
			// _A_NORMAL	0x00
			// _A_RDONLY	0x01
			// _A_HIDDEN	0x02
			// _A_SYSTEM	0x04
			// _A_SUBDIR	0x10
			// _A_ARCH		0x20			
			return GetItemsP(items, directory, 
				[](struct _wfinddata_t & item) -> bool { return (item.attrib & _A_SUBDIR) != 0; },
				wildchar, recursive); 
		}

		static void ProcessItems(
			const wstring & directory, 
			function<bool (struct _wfinddata_t &)> skip,
			function<void (wstring)> process,
			const wstring & wildchar = L"*", 
			const bool recursive = false);
		
		static void ProcessDirectories(
			const wstring & directory, 
			function<void (wstring)> process,
			const wstring & wildchar = L"*", 
			const bool recursive = false) 
		{ 
			ProcessItems(directory, 
				[](struct _wfinddata_t & item) -> bool { return wcscmp(item.name, L".") == 0 || wcscmp(item.name, L"..") == 0 || (item.attrib & _A_SUBDIR) == 0; },
				process, wildchar, recursive); 
		}

		static void ProcessFiles(
			const wstring & directory, 
			function<void (wstring)> process,
			const wstring & wildchar = L"*", 
			const bool recursive = false) 
		{
			// Valid attributes are:
			// _A_NORMAL	0x00
			// _A_RDONLY	0x01
			// _A_HIDDEN	0x02
			// _A_SYSTEM	0x04
			// _A_SUBDIR	0x10
			// _A_ARCH		0x20			
			ProcessItems(directory,
				[](struct _wfinddata_t & item) -> bool { return (item.attrib & _A_SUBDIR) != 0; },
				process, wildchar, recursive); 
		}

	};
}

