#include <iostream>
#include <stdarg.h>
#include <typeinfo>
#include "cpp.h"
using namespace std;

template<class T> T Test_VarArg(int count, T arg1, ...)
{
	va_list ptr;

	va_start(ptr, count);
	
	cout << count;
	
	T next;

	for (int i = 0; i < count; i ++) {
		next = va_arg(ptr, T);
		cout << " " << next;
	}

	next = va_arg(ptr, T);
	if (typeid(T) == typeid(int)) {
		cout << " int " << next << endl;
		//WIN_ASSERT_EQUAL(next, 0);
	} else {
		cout << " " << next << endl;
		//WIN_ASSERT_EQUAL(next, NULL);
	}
	
	va_end(ptr);
	
	return next;
}