#pragma once

#include <algorithm>
#include <sstream>
#include <vector>
#include "Log.h"

using namespace std;

namespace Test {
	// This implementation uses a vector as the container and the methods from <algorithm> to manipulate it.
	// The default template parameter Compare is less<T>, which creates a maximum heap.
	// If Compare is greater<T>, then it creates a minimum heap.
	// To track top n numbers in a set, create a min heap of size n,
	// enumerate each number and push it into the heap if it is greater than the root of heap.
	// To track bottom n numbers in a set, create a max heap of size n,
	// enumerate each number and push it into the heap if it is smaller than the root of heap.
	template<class T, class Compare = less<T>> class Heap {
	private:
		vector<T> _elements;
		Compare _compare; // static?
		unsigned long _capacity;

		// Initialize the heap using a given vector
		// If the number of elements in the vector is greater than the heap capacity,
		// then only top (for min heap) or botton elements (for max heap) will be pushed into the heap.
		void Init(const vector<T> & input);
	public:
		// Create a heap that can contain upto ULONG_MAX elements
		Heap(void) : _capacity(ULONG_MAX) {}

		// Create a heap of specified capacity
		Heap(unsigned long cap) : _capacity(cap) {}

		// Create a heap using an existing container
		Heap(const vector<T> & input);

		// Create a heap of specified capacity using an existing container
		Heap(const vector<T> & input, unsigned long cap);
		
		~Heap(void) {}

		// Return true if this is really a heap
		bool IsHeap(void) { return is_heap(_elements.begin(), _elements.end(), _compare); }

		// Pop the top of heap
		T Pop(void);

		void Print(Log & log);
		
		// Try to push an element into the heap
		// Return true if an element is pushed into the heap successfully.
		// Return false if the heap is at capacity and the element does not fit into the heap.
		bool Push(const T & e);
		
		// Get the number of elements in the heap
		size_t Size(void) { return _elements.size(); }

		// Get a reference to the top of heap
		const T & Top(void) { return _elements.front(); }
	};

	template<class T, class Compare> void Heap<T, Compare>::Init(const vector<T> & input)
	{
		unsigned long l = min<unsigned long>(_capacity, input.size());
		for (unsigned long i = 0; i < l; i++) {
			_elements.push_back(input[i]);
		}

		make_heap(_elements.begin(), _elements.end(), _compare);

		for (unsigned long i = l; i < input.size() - 1; i++) {
			if (_compare(input[i], Top())) {
				Pop();
				Push(input[i]);
			}
		}
	}

	template<class T, class Compare> Heap<T, Compare>::Heap(const vector<T> & input)
	{
		_capacity = ULONG_MAX;
		Init(input);
	}

	template<class T, class Compare> Heap<T, Compare>::Heap(const vector<T> & input, unsigned long cap)
	{
		_capacity = cap;
		Init(input);
	}

	template<class T, class Compare> T Heap<T, Compare>::Pop(void)
	{
		if (_elements.size() == 0) throw runtime_error("Heap is empty.");
		
		// pop_heap moves the top to the end of container
		pop_heap(_elements.begin(), _elements.end(), _compare);
		
		// Get a reference to the popped top element
		T & value = _elements.back();
		
		// Remvoe the popped to element from the heap
		_elements.pop_back();
		
		return value;
	}

	template<class T, class Compare> void Heap<T, Compare>::Print(Log & log)
	{
		for_each(_elements.begin(), _elements.end(), [&](const T & e) -> void
		{
			log.WriteInformation("\t%d", e);
		});

		log.WriteInformation("\n");
	}

	template<class T, class Compare> bool Heap<T, Compare>::Push(const T & e)
	{
		// [TODO] While?
		if (_elements.size() >= _capacity) {
			// Check against the top element since it is the gate to the heap
			if (_compare(e, Top())) {
				// Pop the top to make a room for the element
				Pop();
			} else {
				// The element does not fit in the heap
				return false;
			}
		}

		// Add the element to the end of vector
		_elements.push_back(e);

		// push_heap moves the end of vector into the heap
		push_heap(_elements.begin(), _elements.end(), _compare);

		return true;
	}
}