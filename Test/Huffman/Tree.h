#pragma once
#include <map>
#include <queue>
#include "Character.h"
using namespace std;
namespace Huffman {

	template<class T> struct Greater : public binary_function <Character<T> *, Character<T> *, bool>
	{
		bool operator() (const Character<T> * left, const Character<T> * right) const
		{
			return 1 == Character<T>::Compare(left, right);
		}
	};

	template<class T> class Tree {
	private:
		Character<T> * root;
	public:
		Tree(void) : root(nullptr) {}
		~Tree(void);
		void ComputeTree(map<T, unsigned long> & chars);
		void PrintCode(void);
	};

	template<class T> Tree<T>::~Tree(void)
	{
		if (this->root != nullptr)
		{
			delete this->root;
			this->root = nullptr;
		}
	}

	template<class T> void Tree<T>::ComputeTree(map<T, unsigned long> & chars)
	{
		priority_queue<Character<T> *, vector<Character<T> *>, Greater<T>> queue;

		for (map<char, unsigned long>::iterator it = chars.begin(); it != chars.end(); it++) {
			queue.push(new Character<T>(it->first, it->second));
		}

		while (queue.size() > 1) {
			Character<T> * ch1 = queue.top();
			queue.pop();
			Character<T> * ch2 = queue.top();
			queue.pop();
			queue.push(new Character<T>(ch1, ch2));
		}

		this->root = queue.top();
		queue.pop();
	}

	template<class T> void Tree<T>::PrintCode(void)
	{
		Character<T>::Encode(this->root, string());
	}
}