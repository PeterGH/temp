#pragma once
#include <memory>
#include <string>

using namespace std;

namespace Huffman {

	template<class T> class Character {
	public:
		Character * left;
		Character * right;
		T character;
		double frequency;

		Character(T ch, double freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
		Character(Character * left, Character * right);
		~Character(void);

		// Return 1 if left.frequency > right.frequency
		// Return -1 if left.frequency < right.frequency
		// Return 0 if left.frequency = right.frequency
		static int Compare(const Character & left, const Character & right);

		static void PostOrder(const Character * c);

		static void InOrder(const Character * c, const string & code);
	};

	template<class T> Character<T>::Character(Character * left, Character * right)
	{
		this->character = left->frequency > right->frequency ? left->character : right->character;
		this->frequency = left->frequency + right->frequency;
		this->left = left;
		this->right = right;
		// cout << this->character << "[" << this->frequency << "] = " 
		// 	<< left->character << "[" << left->frequency << "] + " 
		// 	<< right->character << "[" << right->frequency << "]" << endl;
	}

	template<class T> Character<T>::~Character(void)
	{
		if (this->left != nullptr) {
			delete this->left;
			this->left = nullptr;
		}
		if (this->right != nullptr) {
			delete this->right;
			this->right = nullptr;
		}
		// cout << "Deleted " << this->character << "\t" << this->frequency << endl;
	}

	template<class T> int Character<T>::Compare(const Character & left, const Character & right)
	{
		if (left.frequency > right.frequency)
			return 1;
		else if (left.frequency < right.frequency)
			return -1;
		else
			return 0;
	}

	template<class T> void Character<T>::PostOrder(const Character * c)
	{
		if (c->left == nullptr && c->right == nullptr)
			cout << c->character << "\t" << c->frequency << endl;
		if (c->left != nullptr)
			PostOrder(c->left);
		if (c->right != nullptr)
			PostOrder(c->right);
	}

	template<class T> void Character<T>::InOrder(const Character * c, const string & code)
	{
		if (c->left == nullptr && c->right == nullptr) {
			cout << c->character << "[" << c->frequency << "]\t" << code << endl;
			return;
		}

		if (c->left != nullptr) {
			string lcode = string(code) + "0";
			InOrder(c->left, lcode);
		}

		if (c->right != nullptr) {
			string rcode = string(code) + "1";
			InOrder(c->right, rcode);
		}
	}

	template class Character<char>;
}

