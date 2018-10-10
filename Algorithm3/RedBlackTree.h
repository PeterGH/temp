#pragma once

#include <iostream>
#include <functional>

#include "BSTNode.h"

typedef enum {
	RED,
	BLACK,
	UNDEFINED
} RBColor;

template<class T> class RBNode : public BSTNode<T>
{
private:
	RBColor _color;

public:
	RBNode(T) : base(T), _color(RBColor::BLACK) {}
	~RBNode(void) : ~base() {}

};

template __declspec(dllexport) class RBNode<int>;