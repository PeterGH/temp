#include <iostream>
#include <fstream>
#include "Character.h"
#include "Tree.h"
using namespace std;
using namespace Huffman;

int main(int argc, char * argv[])
{
	if (argc < 2) {
		cout << "Usage: Huffman.exe [File]" << endl;
		return -1;
	}

	map<char, unsigned long> chars;

	ifstream input(argv[1], ios_base::in | ios_base::binary);

	// Work for ASCII encoding only
	// Other encoding has 0x00 as either higher or lower byte,
	// which translates to NULL
	char c;
	while (input.peek() && input.good()) {
		input.get(c);
		if (chars.find(c) == chars.end()) {
			chars.insert(make_pair(c, 1));
		} else {
			chars[c]++;
		}
	}

	input.close();

	Tree<char> tree;
	tree.ComputeTree(chars);
	tree.PrintCode();
}