#pragma once

#include <iostream>
#include <stdarg.h>
#include <string>
#include "Matrix.h"
#include "LowerTriangularMatrix.h"
#include "UpperTriangularMatrix.h"
using namespace std;

namespace Test {
	enum LogLevel {
		Error,
		Warning,
		Information,
		Verbose
	};

	class Log {
	private:
		static const size_t MaxLength = 1024;
		ostream & _os;
		LogLevel _level;
	public:
		__declspec(dllexport) Log(ostream & os = cout, LogLevel level = LogLevel::Error) : _os(os), _level(level) {}
		__declspec(dllexport) ~Log() {}

		__declspec(dllexport) void WriteError(const char * format, ...);
		__declspec(dllexport) void WriteWarning(const char * format, ...);
		__declspec(dllexport) void WriteInformation(const char * format, ...);
		__declspec(dllexport) void WriteVerbose(const char * format, ...);

		template<class T> __declspec(dllexport) void Print(T a[], int n, const char * format = "%d", const char * sep = ", ");

		template<class T> __declspec(dllexport) void Print(vector<T> v, const char * format = "%d", const char * sep = ", ");
		template<class T> __declspec(dllexport) void Print(vector<T> v, function<void(Log &, T &)> format, const char * sep = ", ");

		template<class T> __declspec(dllexport) void Print(const T * input, const int length, const int columns, const char * format = "%d", const char * sep = ", ");

		template<class T> __declspec(dllexport) void Print(Matrix<T> & matrix, const char * format = "%d", const char * sep = ", ");
		template<class T> __declspec(dllexport) void Print(Matrix<T> & matrix, function<void(Log &, T &)> format, const char * sep = ", ");

		template<class T> __declspec(dllexport) void Print(LowerTriangularMatrix<T> & matrix, const char * format = "%d", const char * sep = ", ");
		template<class T> __declspec(dllexport) void Print(LowerTriangularMatrix<T> & matrix, function<void(Log &, T)> format, const char * sep = ", ");

		template<class T> __declspec(dllexport) void Print(UpperTriangularMatrix<T> & matrix, const char * format = "%d", const char * sep = ", ");
		template<class T> __declspec(dllexport) void Print(UpperTriangularMatrix<T> & matrix, function<void(Log &, T)> format, const char * sep = ", ");
	};

	template<class T> void Log::Print(T a[], int n, const char * format, const char * sep)
	{
		WriteInformation("[");
		for (int i = 0; i < n; i++) {
			if (i != 0) WriteInformation(sep);
			WriteInformation(format, a[i]);
		}
		WriteInformation("]\n");
	}

	template<class T> void Log::Print(vector<T> v, const char * format, const char * sep)
	{
		WriteInformation("{");
		for (size_t i = 0; i < v.size(); i++) {
			if (i != 0) WriteInformation(sep);
			WriteInformation(format, v[i]);
		}
		WriteInformation("}\n");
	}

	template<class T> void Log::Print(vector<T> v, function<void(Log &, T &)> format, const char * sep)
	{
		WriteInformation("{");
		for (size_t i = 0; i < v.size(); i++) {
			if (i != 0) WriteInformation(sep);
			format(*this, v[i]);
		}
		WriteInformation("}\n");
	}

	template<class T> void Log::Print(const T * input, const int length, const int columns, const char * format, const char * sep)
	{
		if (input == nullptr || length <= 0) return;
		int rows = length / columns;
		WriteInformation("[\n");

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (j == 0) WriteInformation(" ");
				else WriteInformation(sep);
				WriteInformation(format, *(input + i * columns + j));
			}
			WriteInformation("\n");
		}

		int remainders = length % columns;
		if (remainders > 0) {
			for (int j = 0; j < remainders; j++) {
				if (j == 0) WriteInformation(" ");
				else WriteInformation(sep);
				WriteInformation(format, *(input + rows * columns + j));
			}
			WriteInformation("\n");
		}

		WriteInformation("]\n");
	}

	template<class T> void Log::Print(Matrix<T> & matrix, const char * format, const char * sep)
	{
		WriteInformation("[\n");
		for (size_t i = 0; i < matrix.Rows(); i++) {
			for (size_t j = 0; j < matrix.Cols(); j++) {
				if (j == 0) WriteInformation(" ");
				else WriteInformation(sep);
				WriteInformation(format, matrix(i, j));
			}
			WriteInformation("\n");
		}
		WriteInformation("]\n");
	}

	template<class T> void Log::Print(Matrix<T> & matrix, function<void(Log &, T &)> format, const char * sep)
	{
		WriteInformation("[\n");
		for (size_t i = 0; i < matrix.Rows(); i++) {
			for (size_t j = 0; j < matrix.Cols(); j++) {
				if (j == 0) WriteInformation(" ");
				else WriteInformation(sep);
				format(*this, matrix(i, j));
			}
			WriteInformation("\n");
		}
		WriteInformation("]\n");
	}

	template<class T> void Log::Print(LowerTriangularMatrix<T> & matrix, const char * format, const char * sep)
	{
		WriteInformation("[\n");
		for (size_t i = 0; i < matrix.Rows(); i++) {
			for (size_t j = 0; j < matrix.Cols(); j++) {
				if (j == 0) WriteInformation(" ");
				else WriteInformation(sep);
				WriteInformation(format, i < j ? 0 : matrix(i, j));
			}
			WriteInformation("\n");
		}
		WriteInformation("]\n");
	}

	template<class T> void Log::Print(LowerTriangularMatrix<T> & matrix, function<void(Log &, T)> format, const char * sep)
	{
		WriteInformation("[\n");
		for (size_t i = 0; i < matrix.Rows(); i++) {
			for (size_t j = 0; j < matrix.Cols(); j++) {
				if (j == 0) WriteInformation(" ");
				else WriteInformation(sep);
				format(*this, i < j ? 0 : matrix(i, j));
			}
			WriteInformation("\n");
		}
		WriteInformation("]\n");
	}

	template<class T> void Log::Print(UpperTriangularMatrix<T> & matrix, const char * format, const char * sep)
	{
		WriteInformation("[\n");
		for (size_t i = 0; i < matrix.Rows(); i++) {
			for (size_t j = 0; j < matrix.Cols(); j++) {
				if (j == 0) WriteInformation(" ");
				else WriteInformation(sep);
				WriteInformation(format, i > j ? 0 : matrix(i, j));
			}
			WriteInformation("\n");
		}
		WriteInformation("]\n");
	}

	template<class T> void Log::Print(UpperTriangularMatrix<T> & matrix, function<void(Log &, T)> format, const char * sep)
	{
		WriteInformation("[\n");
		for (size_t i = 0; i < matrix.Rows(); i++) {
			for (size_t j = 0; j < matrix.Cols(); j++) {
				if (j == 0) WriteInformation(" ");
				else WriteInformation(sep);
				format(*this, i > j ? 0 : matrix(i, j));
			}
			WriteInformation("\n");
		}
		WriteInformation("]\n");
	}
}