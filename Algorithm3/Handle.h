#pragma once

template<class T> class Handle
{
private:
	struct Internal;
	Internal * _internal;
public:
	Handle(void);
	~Handle(void);
	void Set(T);
	T Get(void);
};

template<class T> Handle<T>::Handle(void)
{
	_internal = new Internal;
}


template<class T> Handle<T>::~Handle(void)
{
	delete _internal;
}

template<class T> void Handle<T>::Set(T data)
{
	_internal->_data = data;
}

template<class T> T Handle<T>::Get(void)
{
	return _internal->_data;
}


template  __declspec(dllexport) class Handle<int>;