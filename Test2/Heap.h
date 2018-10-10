#pragma once
#include <vector>
#include <algorithm>
using namespace std;
namespace My {
	//
	// To track top n numbers in a set, create a min heap of size n,
	// enumerate each number and push it into the heap if it is greater than the root of heap.
	//
	// To track bottom n numbers in a set, create a max heap of size n,
	// enumerate each number and push it into the heap if it is smaller than the root of heap.
	//
	// Default Compare is less<T>, which creates a maximum heap.
	// If Compare is greater<T>, then it creates a minimum heap.
	//
	template<class T, class Compare = less<T>> class Heap {
	private:
		vector<T> elements;
		Compare compare;
		unsigned long capacity;
		void Init(const vector<T> & input);
	public:
		Heap(void) : capacity(ULONG_MAX) {} 
		// Create a heap containing upto cap elements
		Heap(unsigned long cap) : capacity(cap) {}
		Heap(const vector<T> & input);
		Heap(const vector<T> & input, unsigned long cap);
		~Heap(void) {}

		void Push(const T & e);

		const T & Top(void) { return this->elements.front(); }

		// Pop the root of heap
		T Pop(void);

		bool IsHeap(void) { return is_heap(this->elements.begin(), this->elements.end(), this->compare); }
		size_t Size(void) { return this->elements.size(); }
		void Print(void);
	};

	template<class T, class Compare> Heap<T, Compare>::Heap(const vector<T> & input)
	{
		this->capacity = ULONG_MAX;
		this->Init(input);
	}

	template<class T, class Compare> Heap<T, Compare>::Heap(const vector<T> & input, unsigned long cap)
	{
		this->capacity = cap;
		this->Init(input);
	}

	template<class T, class Compare> void Heap<T, Compare>::Init(const vector<T> & input)
	{
		unsigned long l = min<unsigned long>(this->capacity, input.size());
		for (unsigned long i = 0; i < l; i ++) {
			this->elements.push_back(input[i]);
		}

		make_heap(this->elements.begin(), this->elements.end(), this->compare);

		for (unsigned long i = l; i < input.size() - 1; i ++) {
			if (this->compare(input[i], this->Top())) {
				this->Pop();
				this->Push(input[i]);
			}
		}
	}

	template<class T, class Compare> void Heap<T, Compare>::Push(const T & e)
	{
		if (this->elements.size() < this->capacity) {
			this->elements.push_back(e);
			push_heap(this->elements.begin(), this->elements.end(), this->compare);
		} else if (this->compare(e, this->Top())) {
			// The top element is the gate to the heap
			this->Pop();
			this->elements.push_back(e);
			push_heap(this->elements.begin(), this->elements.end(), this->compare);
		}
	}

	template<class T, class Compare> T Heap<T, Compare>::Pop(void)
	{
		if (this->elements.size() == 0) {
			throw runtime_error("Heap is empty.");
		}

		pop_heap(this->elements.begin(), this->elements.end(), this->compare);
		T & value = this->elements.back();
		this->elements.pop_back();
		return value;
	}

	template<class T, class Compare> void Heap<T, Compare>::Print(void)
	{
		for_each(this->elements.begin(), this->elements.end(), [&](const T & e) -> void
		{
			cout << "\t" << e;
		});

		cout << endl;
	}
}