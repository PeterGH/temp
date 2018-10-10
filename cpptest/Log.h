#pragma once

#include <iostream>
#include <stdarg.h>
#include <string>

namespace Test {

    using namespace std;

    enum LogLevel {
        Error,
        Warning,
        Information,
        Verbose
    };

#define WRITE(level, format) \
    if (_level >= level) { \
        char buffer[MaxLength]; \
        va_list args; \
        va_start(args, format); \
        vsnprintf(buffer, MaxLength, format, args); \
        va_end(args); \
        if (level == LogLevel::Error || level == LogLevel::Warning) \
            _os << #level << ": " << string(buffer); \
        else \
            _os << string(buffer); \
    }

    class Log {
    private:
        static const size_t MaxLength = 1024;
        ostream & _os;
        LogLevel _level;
    public:
        Log(ostream & os = cout, LogLevel level = LogLevel::Information)
            : _os(os), _level(level)
        {}
        ~Log() {}

        void WriteError(const char * format, ...)
        {
            WRITE(Error, format);
        }

        void WriteWarning(const char * format, ...)
        {
            WRITE(Warning, format);
        }

        void WriteInformation(const char * format, ...)
        {
            WRITE(Information, format);
        }

        void WriteVerbose(const char * format, ...)
        {
            WRITE(Verbose, format);
        }

        template<class T>
        Log & operator<<(const T & value)
        {
            _os << value;
            return *this;
        }

        Log & operator<<(ostream & (*pf)(ostream &))
        {
            _os << (*pf);
            return *this;
        }

        template<class T1, class T2>
        Log & operator<<(const pair<T1, T2> & p)
        {
            _os << "(" << p.first << ", " << p.second << ")";
            return *this;
        }

        template<class T>
        Log & operator<<(const vector<T> & m)
        {
            *this << "{";
            for (size_t i = 0; i < m.size(); i++)
            {
                if (i > 0) *this << ", ";
                *this << m[i];
            }
            *this << "}" << endl;
            return *this;
        }

        template<class T>
        Log & operator<<(const vector<vector<T>> & m)
        {
            _os << "{" << endl;
            for (size_t i = 0; i < m.size(); i++)
            {
                _os << "  {";
                for (size_t j = 0; j < m[i].size(); j++)
                {
                    if (j > 0) _os << ", ";
                    _os << m[i][j];
                }
                _os << "}" << endl;
            }
            _os << "}" << endl;
            return *this;
        }

        template<class K, class V>
        Log & operator<<(const map<K, vector<vector<V>>> & m)
        {
            *this << "{" << endl;
            for (map<K, vector<vector<V>>>::const_iterator it = m.cbegin(); it != m.cend(); it++)
            {
                *this << it->first << ":" << endl;
                *this << it->second;
            }
            *this << "}" << endl;
            return *this;
        }
    };
}