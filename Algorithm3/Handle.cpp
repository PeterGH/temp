#include "Handle.h"

template<class T> struct Handle<T>::Internal
{
	T _data;
};

