#include "MyPath.h"

namespace My
{
	
	Path::Path(const wchar_t * path)
	{
		_wsplitpath_s(path, drive, _MAX_DRIVE, directory, _MAX_DIR, file, _MAX_FNAME, extension, _MAX_EXT);	
	}

	wstring Path::FullPath(void) const
	{
		wchar_t path[_MAX_PATH];
		_wmakepath_s(path, _MAX_PATH, drive, directory, file, extension);
		return wstring(path);
	}

	vector<wstring> & Path::GetItems(vector<wstring> & items, const wstring & directory, function<bool (struct _wfinddata_t &)> skip, const wstring & wildchar, const bool recursive)
	{
		wchar_t path[_MAX_PATH];
		Combine(path, directory.c_str(), wildchar.c_str());
		
		struct _wfinddata_t item;
		intptr_t hItem;
		hItem = _wfindfirst(path, &item);

		if (hItem != -1L) {
			do {
				if (skip(item)) continue;
				Combine(path, directory.c_str(), item.name);
				items.push_back(wstring(path));			
			} while (_wfindnext(hItem, &item) == 0);
		
			_findclose(hItem);
		}

		if (recursive) {
			vector<wstring> subdirs;
			GetDirectories(subdirs, directory);
			for (vector<wstring>::iterator it = subdirs.begin(); it != subdirs.end(); it ++) {
				GetItems(items, it->data(), skip, wildchar, recursive);
			}
		}
		return items;
	}

	concurrent_vector<wstring> & Path::GetItemsP(concurrent_vector<wstring> & items, const wstring & directory, function<bool (struct _wfinddata_t &)> skip, const wstring & wildchar, const bool recursive)
	{
		wchar_t path[_MAX_PATH];
		Combine(path, directory.c_str(), wildchar.c_str());
		
		struct _wfinddata_t item;
		intptr_t hItem;
		hItem = _wfindfirst(path, &item);

		if (hItem != -1L) {
			do {
				if (skip(item)) continue;
				Combine(path, directory.c_str(), item.name);
				items.push_back(wstring(path));			
			} while (_wfindnext(hItem, &item) == 0);
		
			_findclose(hItem);
		}

		if (recursive) {
			vector<wstring> subdirs;
			GetDirectories(subdirs, directory);
			//for_each(subdirs.begin(), subdirs.end(), [](wstring dir) { wprintf_s(L"  %s:\n", dir); });
			//for (vector<wstring>::iterator it = subdirs.begin(); it != subdirs.end(); it ++) {
			//	wprintf_s(L"  %s:\n", it->data());
			//}
			parallel_for_each (subdirs.begin(), subdirs.end(), [&items, &skip, &wildchar, recursive](wstring & dir) {
				GetItemsP(items, dir, skip, wildchar, recursive);
			});
		}
		return items;
	}

	void Path::ProcessItems(
		const wstring & directory, 
		function<bool (struct _wfinddata_t &)> skip, 
		function<void (wstring path)> process,
		const wstring & wildchar, 
		const bool recursive)
	{
		wchar_t path[_MAX_PATH];
		Combine(path, directory.c_str(), wildchar.c_str());
		
		struct _wfinddata_t item;
		intptr_t hItem;
		hItem = _wfindfirst(path, &item);

		if (hItem != -1L) {
			do {
				if (skip(item)) continue;
				Combine(path, directory.c_str(), item.name);
				process(wstring(path));
			} while (_wfindnext(hItem, &item) == 0);
		
			_findclose(hItem);
		}

		if (recursive) {
			vector<wstring> subdirs;
			GetDirectories(subdirs, directory);
			//for_each(subdirs.begin(), subdirs.end(), [](wstring dir) { wprintf_s(L"  %s:\n", dir); });
			parallel_for_each (subdirs.begin(), subdirs.end(), [&skip, &process, &wildchar, recursive](wstring & dir) {
				ProcessItems(dir, skip, process, wildchar, recursive);
			});
		}
	}

}
