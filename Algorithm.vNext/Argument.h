#pragma once

#include <map>
#include <set>
#include <vector>
#include "String.h"

using namespace std;

namespace Test {

	// Class to parse command line arguments
	template<class T> class Argument {
	private:
		vector<basic_string<T>> indexed;
		map<basic_string<T>, basic_string<T>> named;
        
		// Parse command line arguments
		void Parse(int argc, T * argv[])
		{
			if (argc <= 0 || argv == nullptr) return;
			int i = 0;
			while (i < argc) {
				if (argv[i][0] == T('-')) {
					basic_string<T> key = basic_string<T>(&argv[i][1]);
					if (i + 1 < argc && argv[i + 1][0] != T('-')) {
						// case: -key value
						basic_string<T> value = basic_string<T>(argv[i + 1]);
						this->named.insert(pair<basic_string<T>, basic_string<T>>(String::ToLower(key), value));
						i += 2;
					} else {
						// case 1: -key
						// case 2: -key1 -key2
						this->named.insert(pair<basic_string<T>, basic_string<T>>(String::ToLower(key), basic_string<T>()));
						i++;
					}
				} else {
					basic_string<T> value = basic_string<T>(argv[i]);
					this->indexed.push_back(value);
					i++;
				}
			}
		}
	public:
		// Create an Argument object with command line arguments
		Argument(int argc, T * argv[]) { Parse(argc, argv); }

		// Copy constructor
		Argument(const Argument & a) : this->indexed(a.indexed), this->named(a.named) {}

		// Destructor
		~Argument(void) {}

		// Count named arguments
		size_t CountNamedArgs(void) const { return this->named.size(); }

		// Count indexed arguments
		size_t CountIndexedArgs(void) const { return this->indexed.size(); }

		// Count total arguments
		size_t Count(void) const { return CountNamedArgs() + CountIndexedArgs(); }

		// Check if a named argument exists
		bool Has(const basic_string<T> & key) const
		{
			basic_string<T> keyl = String::ToLower(key);
			return this->named.find(keyl) != this->named.end();
		}

		// Check if an indexed argument exists
		bool Has(unsigned int index) const { return index < this->indexed.size(); }

		// Get a named argument value
		const basic_string<T> & operator[](const basic_string<T> & key) const
		{
			basic_string<T> keyl = String::ToLower(key);
			map<basic_string<T>, basic_string<T>>::iterator it = this->named.find(keyl);
			if (it != this->named.end()) {
				return it->second;
			} else {
				throw invalid_argument(String::Format("Invalid argument name %s", String::ToString(key)));
			}
		}

		// Get an indexed argument value
		const basic_string<T> & operator[](unsigned int index) const
		{
			if (index < this->indexed.size()) {
				return this->indexed[index];
			}
			else {
				throw invalid_argument(String::Format("Invalid argument index %d", index));
			}
		}

		// Convert all arguments into a string representation
		const basic_string<T> ToString(void) const
		{
			basic_string<T> s;
			unsigned int i = 0;
			string t;
			for (map<basic_string<T>, basic_string<T>>::const_iterator it = this->named.cbegin();
				it != this->named.cend();
				it++) {
				t = "-";
				s.append(t.begin(), t.end());
				s += it->first;
				t = " ";
				s.append(t.begin(), t.end());
				s += it->second;
				if ((i++) < this->named.size() - 1) {
					t = " ";
					s.append(t.begin(), t.end());
				}
			}
			if (this->named.size() > 0 && this->indexed.size() > 0) {
				t = " ";
				s.append(t.begin(), t.end());
			}
			for (size_t i = 0; i < this->indexed.size(); i++) {
				s += this->indexed[i];
				if (i != this->indexed.size() - 1) {
					t = " ";
					s.append(t.begin(), t.end());
				}
			}
			return s;
		}

		// Get the names of all named arguments
		const set<basic_string<T>> Keys(void) const
		{
			set<basic_string<T>> keys;
			for (map<basic_string<T>, basic_string<T>>::const_iterator it = this->named.cbegin();
				it != this->named.cend();
				it++) {
				keys.insert(it->first);
			}
			return keys;
		}
	};
}