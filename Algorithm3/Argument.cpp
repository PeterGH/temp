#include "Argument.h"

namespace My {

	void ArgumentA::Parse(int argc, char * argv[])
	{
		int i = 0;
		do {
			if (argv[i][0] == '-') {
				string key = StringA::ToString(&argv[i][1]);
				if (i + 1 < argc && argv[i+1][0] != '-') {
					// case: -key value					
					string value = StringA::ToString(argv[i+1]);
					_named.insert(pair<string, string>(StringA::ToLower(key), value));
					i += 2;
				} else {
					// case 1: -key
					// case 2: -key1 -key2
					_named.insert(pair<string, string>(StringA::ToLower(key), StringA::Empty));
					i ++;
				}
			} else {
				string value = StringA::ToString(argv[i]);
				_indexed.push_back(value);
				i ++;
			}
		} while (i < argc);
	}
	
	bool ArgumentA::Has(const string & key)
	{
		string keyl = StringA::ToLower(key);
		map<string, string>::iterator it = _named.find(keyl);
		if (it != _named.end()) {
			return true;
		} else {
			return false;
		}
	}

	string & ArgumentA::operator[](const string & key)
	{
		string keyl = StringA::ToLower(key);
		map<string, string>::iterator it = _named.find(keyl);
		if (it != _named.end()) {
			return it->second;
		} else {
			throw invalid_argument(key.c_str());
		}
	}

	string & ArgumentA::operator[](unsigned int index)
	{
		if (index < _indexed.size()) {
			return _indexed[index];
		} else {
			throw invalid_argument("Invalid index");
		}
	}

	string ArgumentA::ToString(void)
	{
		string s;
		for (map<string, string>::iterator it = _named.begin(); it != _named.end(); it ++) {
			s += "-";
			s += it->first;
			s += " ";
			s += it->second;
			if (it != _named.end()) {
				s += " ";
			}
		}
		if (_named.size() > 0 && _indexed.size() > 0) {
			s += " ";
		}
		for (size_t i = 0; i < _indexed.size(); i ++) {
			s += _indexed[i];
			if (i != _indexed.size() - 1) {
				s += " ";
			}
		}
		return s;
	}

	void ArgumentW::Parse(int argc, wchar_t * argv[])
	{
		int i = 0;
		do {
			if (argv[i][0] == L'-') {
				if (i + 1 < argc && argv[i+1][0] != L'-') {
					// case: -key value
					_named.insert(pair<wstring, wstring>(StringW::ToLower(&argv[i][1]), argv[i+1]));
					i += 2;
				} else {
					// case 1: -key
					// case 2: -key1 -key2
					_named.insert(pair<wstring, wstring>(StringW::ToLower(&argv[i][1]), StringW::Empty));
					i ++;
				}
			} else {
				_indexed.push_back(argv[i]);
				i ++;
			}
		} while (i < argc);
		
	}
	
	bool ArgumentW::Has(const wstring & key)
	{
		wstring keyl = StringW::ToLower(key);
		map<wstring, wstring>::iterator it = _named.find(keyl);
		if (it != _named.end()) {
			return true;
		} else {
			return false;
		}
	}	

	wstring & ArgumentW::operator[](const wstring & key)
	{
		wstring keyl = StringW::ToLower(key);
		map<wstring, wstring>::iterator it = _named.find(keyl);
		if (it != _named.end()) {
			return it->second;
		} else {
			throw invalid_argument("Invalid key");
		}
	}

	wstring & ArgumentW::operator[](unsigned int index)
	{
		if (index < _indexed.size()) {
			return _indexed[index];
		} else {
			throw invalid_argument("Invalid index");
		}
	}

	wstring ArgumentW::ToString(void)
	{
		wstring s;		
		for (map<wstring, wstring>::iterator it = _named.begin(); it != _named.end(); it ++) {
			s += L"-";
			s += it->first;
			s += L" ";
			s += it->second;
			if (it != _named.end()) {
				s += L" ";
			}
		}
		if (_named.size() > 0 && _indexed.size() > 0) {
			s += L" ";
		}
		for (size_t i = 0; i < _indexed.size(); i ++) {
			s += _indexed[i];
			if (i != _indexed.size() - 1) {
				s += L" ";
			}
		}
		return s;
	}
}