// Huffman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <memory>
#include "Character.h"
using namespace std;
using namespace Huffman;

struct Greater : public binary_function <Character<char> *, Character<char> *, bool>
{
	bool operator() (const Character<char> * left, const Character<char> * right) const 
	{ 
		return 1 == Character<char>::Compare(*left, *right); 
	}
};

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "Usage: Huffman.exe [File]" << endl;
		return -1;
	}

	map<char, unsigned long> count;

	ifstream input(argv[1], ios_base::in | ios_base::binary);
	
	// Work for ASCII encoding only
	// Other encoding has 0x00 as either higher or lower byte,
	// which translates to NULL
	char c;
	// cout << hex << uppercase;
	while (input.peek() && input.good()) {
		input.get(c);
		// cout << c;
		if (count.find(c) == count.end()) {
			count.insert(make_pair(c, 1));
		} else {
			count[c]++;
		}
	}
	// cout << endl;
	input.close();

	priority_queue<Character<char> *, vector<Character<char> *>, Greater> queue;

	for (map<char, unsigned long>::iterator it = count.begin(); it != count.end(); it++) {
		queue.push(new Character<char>(it->first, it->second));
	}

	while (queue.size() > 1) {
		Character<char> * ch1 = queue.top();
		queue.pop();
		Character<char> * ch2 = queue.top();
		queue.pop();
		queue.push(new Character<char>(ch1, ch2));
	}

	// cout << "Huffman tree:" << endl;

	Character<char> * ch = queue.top();
	queue.pop();
	// Character<char>::PostOrder(ch);

	cout << "Encoding " << endl;
	Character<char>::InOrder(ch, string());

	delete ch;
	return 0;
}

