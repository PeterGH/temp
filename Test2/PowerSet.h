#pragma once
#include <vector>
using namespace std;

namespace My {
	// The powerset of any set S is the set of all subsets of S, including the empty set and S itself.

	template<class T> class PowerSet {
	private:
		static vector<vector<T>> ComputeRecursively(typename vector<T>::iterator & begin, typename vector<T>::iterator & end);
	public:
		static vector<vector<T>> Compute(vector<T> & set);
	};

	template<class T> vector<vector<T>> PowerSet<T>::ComputeRecursively(typename vector<T>::iterator & begin, typename vector<T>::iterator & end)
	{
		if (begin == end) {
			// Create an empty element
			vector<T> empty;
			// Note the return vector contains one element, which is an empty vector.
			return vector<vector<T>>(1, empty);
		}

		T first = * begin;
		
		begin ++;
		// Compute the powerset using the elements excluding the first one
		vector<vector<T>> s = ComputeRecursively(begin, end);

		vector<vector<T>> ps(s.begin(), s.end());
		
		for_each (s.begin(), s.end(), [&](vector<T> & v)->void {
			v.push_back(first);
			ps.push_back(v);
		});

		return ps;
	}

	template<class T> vector<vector<T>> PowerSet<T>::Compute(vector<T> & set)
	{
		return ComputeRecursively(set.begin(), set.end());
	}
}