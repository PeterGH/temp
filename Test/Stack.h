#pragma once

#include <queue>

using namespace std;

namespace Test {
	template<class T> class Stack {
	private:
		queue<T> queue0, queue1;
		static void Flush(queue<T> & nonempty, queue<T> & empty, size_t count);
	public:
		Stack(void) {}
		~Stack(void) {}

		bool Empty(void) const;
		void Pop(void);
		void Push(const T & value);
		size_t Size(void) const;
		T & Top(void);
	};

	template<class T> void Stack<T>::Flush(queue<T> & nonempty, queue<T> & empty, size_t count)
	{
		while (count > 0) {
			T v = nonempty.front();
			nonempty.pop();
			empty.push(v);
			count--;
		}
	}
	
	template<class T> bool Stack<T>::Empty(void) const
	{
		return queue0.empty() && queue1.empty();
	}

	template<class T> void Stack<T>::Pop(void)
	{
		if (queue0.empty() && queue1.empty()) throw runtime_error("Stack is empty");
		else if (!queue0.empty()) {
			Flush(queue0, queue1, queue0.size() - 1);
			queue0.pop();
		} else if (!queue1.empty()) {
			Flush(queue1, queue0, queue1.size() - 1);
			queue1.pop();
		}
	}

	template<class T> void Stack<T>::Push(const T & value)
	{
		if (!queue0.empty()) queue0.push(value);
		else if (!queue1.empty()) queue1.push(value);
		else queue0.push(value);
	}

	template<class T> size_t Stack<T>::Size(void) const
	{
		return queue0.size() + queue1.size();
	}

	template<class T> T & Stack<T>::Top(void)
	{
		if (queue0.empty() && queue1.empty()) throw runtime_error("Stack is empty");
		else if (!queue0.empty()) return queue0.back();
		else return queue1.back();
	}
}