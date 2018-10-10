#pragma once

#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

namespace Test {

    // Class to parse command line arguments
    template<class T> class Argument {
    private:
        vector<basic_string<T>> _indexedArgs;
        map<basic_string<T>, basic_string<T>> _namedArgs;

        // Parse command line arguments
        void Parse(int argc, T * argv[])
        {
            if (argc <= 0 || argv == nullptr) return;
            int i = 0;
            while (i < argc) {
                if (argv[i][0] == T('-')) {
                    basic_string<T> key = basic_string<T>(&argv[i][1]);
                    ToLower(key);
                    if (i + 1 < argc && argv[i + 1][0] != T('-')) {
                        // case: -key value
                        basic_string<T> value = basic_string<T>(argv[i + 1]);
                        _namedArgs.insert(pair<basic_string<T>, basic_string<T>>(key, value));
                        i += 2;
                    } else {
                        // case 1: -key
                        // case 2: -key1 -key2
                        _namedArgs.insert(pair<basic_string<T>, basic_string<T>>(key, basic_string<T>()));
                        i++;
                    }
                } else {
                    basic_string<T> value = basic_string<T>(argv[i]);
                    _indexedArgs.push_back(value);
                    i++;
                }
            }
        }

        static void ToLower(basic_string<T> & input)
        {
            transform(input.begin(), input.end(), input.begin(), tolower);
        }

        static basic_string<T> ToLower(const basic_string<T> & input)
        {
            basic_string<T> output = input;
            ToLower(output);
            return output;
        }

    public:
        // Create an Argument object with command line arguments
        Argument(int argc, T * argv[]) { Parse(argc, argv); }

        // Copy constructor
        Argument(const Argument & a) : _indexedArgs(a._indexedArgs), _namedArgs(a._namedArgs) {}

        // Destructor
        ~Argument(void) {}

        // Count named arguments
        size_t CountNamedArgs(void) const { return _namedArgs.size(); }

        // Count indexed arguments
        size_t CountIndexedArgs(void) const { return _indexedArgs.size(); }

        // Count total arguments
        size_t Count(void) const { return CountNamedArgs() + CountIndexedArgs(); }

        // Check if a named argument exists
        bool Has(const basic_string<T> & key) const
        {
            basic_string<T> keyl = ToLower(key);
            return _namedArgs.find(keyl) != _namedArgs.end();
        }

        // Check if an indexed argument exists
        bool Has(unsigned int index) const { return index < _indexedArgs.size(); }

        // Get a named argument value
        const basic_string<T> & operator[](const basic_string<T> & key) const
        {
            basic_string<T> keyl = ToLower(key);
            map<basic_string<T>, basic_string<T>>::const_iterator it = _namedArgs.find(keyl);
            if (it != this->_namedArgs.end()) return it->second;
            basic_stringstream<T> ss;
            ss << "Invalid argument name " << key;
            throw invalid_argument(ss.str());
        }

        // Get an indexed argument value
        const basic_string<T> & operator[](unsigned int index) const
        {
            if (index < _indexedArgs.size()) return _indexedArgs[index];
            basic_stringstream<T> ss;
            ss << "Invalid argument index " << index;
            throw invalid_argument(ss.str());
        }

        // Convert all arguments into a string representation
        const basic_string<T> ToString(void) const
        {
            basic_stringstream<T> ss;
            size_t i = 0;
            for (map<basic_string<T>, basic_string<T>>::const_iterator it = _namedArgs.cbegin();
                it != _namedArgs.cend();
                it++) {
                ss << T('-');
                ss << it->first;
                ss << T(' ');
                ss << it->second;
                if ((i++) < _namedArgs.size() - 1) {
                    ss << T(' ');
                }
            }
            if (_namedArgs.size() > 0 && _indexedArgs.size() > 0) {
                ss << T(' ');
            }
            for (size_t i = 0; i < _indexedArgs.size(); i++) {
                ss << _indexedArgs[i];
                if (i != _indexedArgs.size() - 1) {
                    ss << T(' ');
                }
            }
            return ss.str();
        }

        // Get the names of all named arguments
        const set<basic_string<T>> Keys(void) const
        {
            set<basic_string<T>> keys;
            for (map<basic_string<T>, basic_string<T>>::const_iterator it = _namedArgs.cbegin();
                it != _namedArgs.cend();
                it++) {
                keys.insert(it->first);
            }
            return keys;
        }
    };
}