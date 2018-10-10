#pragma once

template<class T> T Test_VarArg(int, T, ...);
template __declspec(dllexport) int Test_VarArg(int, int, ...);
//__declspec(dllexport) void Test_VarArg(int, ...);
template __declspec(dllexport) char * Test_VarArg(int, char *, ...);