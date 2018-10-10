// Rotation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include <memory>
#include "..\Algorithm\Rotation.h"
using namespace std;
int main(int argc, char * argv[])
{
	if (argc < 3) {
		printf_s("Usage: %s [Input] [Distance]\n", argv[0]);
		return -1;
	}

	int length = strlen(argv[1]);
	int distance = atoi(argv[2]);
	unique_ptr<char> input(unique_ptr<char>(new char[length+1]));
	strcpy_s(input.get(), length+1, argv[1]);
	My::Rotation::Left(input.get(), length, distance);
	printf_s("Left rotation:\t%s\n", input);
	strcpy_s(input.get(), length+1, argv[1]);
	My::Rotation::Right(input.get(), length, distance);
	printf_s("Right rotation:\t%s\n", input);
	return 0;
}

