#include "MRIntegerTest.h"
#include "..\Algorithm\MRInteger.h"
#include "..\Algorithm\RadixSort.h"
#include <vector>

void MRIntegerTest::Init(void)
{
	Add("Random", [&]() {
		unsigned int b[] = {1, 2, 4, 8, 16, 32};
		My::MRInteger mri(b, 6);
		std::vector<My::MRInteger> numbers;
		for (int i = 0; i < 30000; i ++) {
			mri.Random();
			numbers.push_back(My::MRInteger(mri));			
		}
		
		sort(numbers.begin(), numbers.end());
		
		// for_each (numbers.begin(), numbers.end(), [](My::MRInteger & it) {
		// 	for (int j = it.Length() - 1; j >= 0; j --) {
		// 		cout << "\t" << it[j];
		// 	}
		// 	cout  << endl;
		// });

		ASSERT1(std::is_sorted(numbers.begin(), numbers.end(), [](const My::MRInteger & second, const My::MRInteger & first) {
			if (second < first)	{
				for (int j = first.Length() - 1; j >= 0; j --) {
					cout << "\t" << first[j];
				}
				cout  << endl;
				for (int j = second.Length() - 1; j >= 0; j --) {
					cout << "\t" << second[j];
				}
				cout  << endl;				
				return true;
			} else {
				return false;
			}
		}));
	});

	Add("RadixSort", [&]() {
		unsigned int b[] = {1, 2, 4, 8, 16, 32};
		My::MRInteger mri(b, 6);
		std::vector<My::MRInteger> numbers;
		for (int i = 0; i < 30000; i ++) {
			mri.Random();
			numbers.push_back(My::MRInteger(mri));			
		}
		
		My::RadixSort::Sort(numbers);

		for_each (numbers.begin(), numbers.end(), [](My::MRInteger & it) {
			for (int j = it.Length() - 1; j >= 0; j --) {
				cout << "\t" << it[j];
			}
			cout  << endl;
		});

		ASSERT1(std::is_sorted(numbers.begin(), numbers.end(), [](const My::MRInteger & second, const My::MRInteger & first) {
			if (second < first)	{
				for (int j = first.Length() - 1; j >= 0; j --) {
					cout << "\t" << first[j];
				}
				cout  << endl;
				for (int j = second.Length() - 1; j >= 0; j --) {
					cout << "\t" << second[j];
				}
				cout  << endl;				
				return true;
			} else {
				return false;
			}
		}));
	});
}

