#pragma once

#include <vector>
#include <map>
#include <set>
#include "MyString.h"

using namespace std;

namespace My {

	template<class T> class Argument
	{
	private:
		vector<basic_string<T>> _indexed;
		map<basic_string<T>, basic_string<T>> _named;
		void Parse(int argc, T * argv[]);
	public:
		Argument(int argc, T * argv[]) { Parse(argc, argv); }
		Argument(const Argument & a) : _indexed(a._indexed), _named(a._named) {}
		~Argument(void) {}
		size_t CountNamedArgs(void) const { return _named.size(); }
		size_t CountIndexedArgs(void) const { return _indexed.size(); }
		size_t Count(void) const { return CountNamedArgs() + CountIndexedArgs(); }
		bool Has(const basic_string<T> & key);
		bool Has(unsigned int index) const { return index < _indexed.size(); }
		const basic_string<T> & operator[](const basic_string<T> & key);
		const basic_string<T> & operator[](unsigned int index);
		const basic_string<T> ToString(void);
		const set<basic_string<T>> Keys(void);	
	};

	template<class T> void Argument<T>::Parse(int argc, T * argv[])
	{
		int i = 0;
		do {
			if (argv[i][0] == T('-')) {
				basic_string<T> key = basic_string<T>(&argv[i][1]);
				if (i + 1 < argc && argv[i+1][0] != T('-')) {
					// case: -key value					
					basic_string<T> value = basic_string<T>(argv[i+1]);
					_named.insert(pair<basic_string<T>, basic_string<T>>(String::ToLower(key), value));
					i += 2;
				} else {
					// case 1: -key
					// case 2: -key1 -key2
					_named.insert(pair<basic_string<T>, basic_string<T>>(String::ToLower(key), basic_string<T>()));
					i ++;
				}
			} else {
				basic_string<T> value = basic_string<T>(argv[i]);
				_indexed.push_back(value);
				i ++;
			}
		} while (i < argc);
	}
	
	template<class T> bool Argument<T>::Has(const basic_string<T> & key)
	{
		basic_string<T> keyl = String::ToLower(key);
		map<basic_string<T>, basic_string<T>>::iterator it = _named.find(keyl);
		if (it != _named.end()) {
			return true;
		} else {
			return false;
		}
	}

	template<class T> const basic_string<T> & Argument<T>::operator[](const basic_string<T> & key)
	{
		basic_string<T> keyl = String::ToLower(key);
		map<basic_string<T>, basic_string<T>>::iterator it = _named.find(keyl);
		if (it != _named.end()) {
			return it->second;
		} else {
			throw invalid_argument(String::Format("Invalid argument name %s", String::ToString(key)));
		}
	}

	template<class T> const basic_string<T> & Argument<T>::operator[](unsigned int index)
	{
		if (index < _indexed.size()) {
			return _indexed[index];
		} else {
			throw invalid_argument(String::Format("Invalid argument index %d", index));
		}
	}

	template<class T> const basic_string<T> Argument<T>::ToString(void)
	{
		basic_string<T> s;
		unsigned int i = 0;
		string t;
		for (map<basic_string<T>, basic_string<T>>::iterator it = _named.begin(); it != _named.end(); it ++) {
			t = "-";
			s.append(t.begin(), t.end());
			s += it->first;
			t = " ";
			s.append(t.begin(), t.end());
			s += it->second;
			if ((i ++) < _named.size() - 1) {
				t = " ";
				s.append(t.begin(), t.end());			
			}
		}
		if (_named.size() > 0 && _indexed.size() > 0) {
			t = " ";
			s.append(t.begin(), t.end());			
		}
		for (unsigned int i = 0; i < _indexed.size(); i ++) {
			s += _indexed[i];
			if (i != _indexed.size() - 1) {
				t = " ";
				s.append(t.begin(), t.end());
			}
		}
		return s;
	}

	template<class T> const set<basic_string<T>> Argument<T>::Keys(void)
	{
		set<basic_string<T>> keys;
		for (map<basic_string<T>, basic_string<T>>::iterator it = _named.begin(); it != _named.end(); it ++) {
			keys.insert(it->first);
		}
		return keys;		
	}

}

