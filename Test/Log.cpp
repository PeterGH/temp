#include "Log.h"

namespace Test {

	void Log::WriteError(const char * format, ...)
	{
		if (_level >= LogLevel::Error) {
			char buffer[MaxLength];
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, format, args);
			va_end(args);
			_os << "Error: " << string(buffer);
		}
	}

	void Log::WriteWarning(const char * format, ...)
	{
		if (_level >= LogLevel::Warning) {
			char buffer[MaxLength];
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, format, args);
			va_end(args);
			_os << "Warning: " << string(buffer);
		}
	}

	void Log::WriteInformation(const char * format, ...)
	{
		if (_level >= LogLevel::Information) {
			char buffer[MaxLength];
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, format, args);
			va_end(args);
			_os << string(buffer);
		}
	}

	void Log::WriteVerbose(const char * format, ...)
	{
		if (_level >= LogLevel::Verbose) {
			char buffer[MaxLength];
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, format, args);
			va_end(args);
			_os << string(buffer);
		}
	}
}