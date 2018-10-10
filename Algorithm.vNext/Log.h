#pragma once

#include <iostream>
#include <set>
#include <stdarg.h>
#include <string>
#include <unordered_set>
#include <vector>

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
		vsprintf_s(buffer, format, args); \
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
		Log(ostream & os = cout, LogLevel level = LogLevel::Information) : _os(os), _level(level) {}
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

		template<class T> void Print(const T * a, size_t len, const char * format = "%d", const char * sep = ", ")
		{
			WriteInformation("{");
			for (size_t i = 0; i < len; i++) {
				if (i != 0) WriteInformation(sep);
				WriteInformation(format, a[i]);
			}
			WriteInformation("}\n");
		}
		
		template<class T> void Print(const vector<T> & v, const char * format = "%d", const char * sep = ", ")
		{
			WriteInformation("{");
			for (size_t i = 0; i < v.size(); i++) {
				if (i != 0) WriteInformation(sep);
				WriteInformation(format, v[i]);
			}
			WriteInformation("}\n");
		}

		template<class T> void Print(const vector<T> & v, function<void(Log &, const T &)> format, const char * sep = ", ")
		{
			WriteInformation("{");
			for (size_t i = 0; i < v.size(); i++) {
				if (i != 0) WriteInformation(sep);
				format(*this, v[i]);
			}
			WriteInformation("}\n");
		}

		template<class T> void Print(const vector<vector<T>> & v, const char * format = "%d", const char * sep = ", ")
		{
			WriteInformation("{\n");
			for (size_t i = 0; i < v.size(); i++) {
				WriteInformation(" ");
				Print(v[i], format, sep);
			}
			WriteInformation("}\n");
		}

		template<class T> void Print(const set<T> & s, const char * format = "%d", const char * sep = ", ")
		{
			WriteInformation("{");
			int i = 0;
			for_each(s.begin(), s.end(), [&](const T & t) {
				if (i != 0) WriteInformation(sep);
				WriteInformation(format, t);
				i++;
			});
			WriteInformation("}\n");
		}

		template<class T> void Print(const unordered_set<T> & s, const char * format = "%d", const char * sep = ", ")
		{
			WriteInformation("{");
			int i = 0;
			for_each(s.begin(), s.end(), [&](const T & t) {
				if (i != 0) WriteInformation(sep);
				WriteInformation(format, t);
				i++;
			});
			WriteInformation("}\n");
		}

		template<class T> void Print(const unordered_set<T> & s, function<void(Log &, const T &)> format, const char * sep = ", ")
		{
			WriteInformation("{");
			int i = 0;
			for_each(s.begin(), s.end(), [&](const T & t) {
				if (i != 0) WriteInformation(sep);
				format(*this, t);
				i++;
			});
			WriteInformation("}\n");
		}
	};
}