#include "RandomTest.h"
#include "..\Algorithm\Random.h"

using namespace std;

void RandomTest::Init(void) 
{
	Add("Next(max)", [&]() {
		int max = 100;
		int count = 100000;
		My::Random rnd;
		map<int, int> freq;
		for (int i = 0; i < count; i ++) {
			int v = rnd.Next(max);
			map<int, int>::iterator it = freq.find(v);
			if (it == freq.end()) {
				freq.insert(pair<int, int>(v, 1));
			} else {
				it->second ++;
			}
		}

		int ave = count / (1 + max);
		cout << "Average\t" << ave << endl;

		int delta = 100;

		for (int i = 0; i <= max; i ++) {
			cout << i;
			int f = 0;
			map<int, int>::iterator it = freq.find(i);
			if (it != freq.end()) {
				f = it->second;
			}

			cout << "\t" << f << endl;
			ASSERT1(f < (ave + delta));
			ASSERT1(f > (ave - delta));
		}
	});

	Add("Next(min, max)", [&]() {
		int min = 100;
		int max = 200;
		int count = 100000;
		My::Random rnd;
		map<int, int> freq;
		for (int i = 0; i < count; i ++) {
			int v = rnd.Next(min, max);
			map<int, int>::iterator it = freq.find(v);
			if (it == freq.end()) {
				freq.insert(pair<int, int>(v, 1));
			} else {
				it->second ++;
			}
		}

		int ave = count / (1 + max - min);
		cout << "Average\t" << ave << endl;

		int delta = 100;

		for (int i = min; i <= max; i ++) {
			cout << i;
			int f = 0;
			map<int, int>::iterator it = freq.find(i);
			if (it != freq.end()) {
				f = it->second;
			}

			cout << "\t" << f << endl;
			ASSERT1(f < (ave + delta));
			ASSERT1(f > (ave - delta));
		}
	});

	Add("Sample(10, 1)", [&]() {
		My::Random rnd;
		int max = 10;
		int count = 100000;

		map<unsigned int, int> freq;
		for (int i = 0; i < count; i ++) {
			vector<unsigned int> samples;
			rnd.Sample(max, 1, samples);
			map<unsigned int, int>::iterator it = freq.find(samples[0]);
			if (it == freq.end()) {
				freq.insert(pair<unsigned int, int>(samples[0], 1));
			} else {
				it->second ++;
			}
		}

		int ave = count / max;
		cout << "Average\t" << ave << endl;

		int delta = 1000;

		for (int i = 0; i < max; i ++) {
			cout << i;
			int f = 0;
			map<unsigned int, int>::iterator it = freq.find(i);
			if (it != freq.end()) {
				f = it->second;
			}

			cout << "\t" << f << endl;
			ASSERT1(f < (ave + delta));
			ASSERT1(f > (ave - delta));
		}
	});

	Add("Sample(10, 10)", [&]() {
		My::Random rnd;
		vector<unsigned int> samples;
		rnd.Sample(10, 10, samples);

		for_each (samples.begin(), samples.end(), [&](unsigned int i) {
			cout << "\t" << i;
		});
		
		cout << endl;
	});
}