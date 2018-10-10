#include "RandomTest.h"

void RandomTest::Init(void)
{
	Add("Next(max)", [&]() {
		function<void(int, int, int)> test = [&](int max, int count, int delta){
			Logger().WriteInformation("Random(%d) %d times expecting max delta %d\n", max, count, delta);
			map<int, int> freq;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next(max);
				map<int, int>::iterator it = freq.find(v);
				if (it == freq.end()) {
					freq.insert(pair<int, int>(v, 1));
				} else {
					it->second++;
				}
			}

			int ave = count / (1 + max);
			Logger().WriteInformation("Average\t%d\n", ave);			

			int size = max + 1;
			ASSERT1(freq.size() == size);

			for (int i = 0; i <= max; i++) {
				int f = 0;
				map<int, int>::iterator it = freq.find(i);
				if (it != freq.end()) {
					f = it->second;
				}

				Logger().WriteInformation("%d\t%d\n", i, f);
				ASSERT1(f <= (ave + delta));
				ASSERT1(f >= (ave - delta));
			}
		}; 
		
		test(0, 100000, 0);
		test(1, 1000000, 1000);
		test(100, 1000000, 500);
		test(1000, 1000000, 200);
		test(10000, 1000000, 100);
	});

	Add("Next(min, max)", [&]() {
		function<void(int, int, int, int)> test = [&](int min, int max, int count, int delta){
			Logger().WriteInformation("Random(%d) %d times expecting max delta %d\n", max, count, delta);
			map<int, int> freq;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next(min, max);
				map<int, int>::iterator it = freq.find(v);
				if (it == freq.end()) {
					freq.insert(pair<int, int>(v, 1));
				}
				else {
					it->second++;
				}
			}

			int ave = count / (1 + max - min);
			Logger().WriteInformation("Average\t%d\n", ave);

			int size = 1 + max - min;
			ASSERT1(freq.size() == size);

			for (int i = min; i <= max; i++) {
				int f = 0;
				map<int, int>::iterator it = freq.find(i);
				if (it != freq.end()) {
					f = it->second;
				}

				Logger().WriteInformation("%d\t%d\n", i, f);
				ASSERT1(f <= (ave + delta));
				ASSERT1(f >= (ave - delta));
			}
		};

		test(2, 2, 100000, 0);
		test(3, 4, 1000000, 1000);
		test(5, 105, 1000000, 500);
		test(106, 1106, 1000000, 200);
		test(1107, 11107, 1000000, 100);
	});

	Add("Sample(n,m)", [&](){
		function<void(int, int, int, function<void(unsigned int, unsigned int, vector<unsigned int> &)>)>
		test = [&](int n, int m, int count, function<void(unsigned int, unsigned int, vector<unsigned int> &)> sample){
			Logger().WriteInformation("Sample(%d, %d) %d times\n", n, m, count);
			map<string, int> freq;
			for (int i = 0; i < count; i++) {
				vector<unsigned int> samples;
				sample(n, m, samples);
				std::sort(samples.begin(), samples.end());
				string key = Test::String::Join(samples, ":");
				map<string, int>::iterator it = freq.find(key);
				if (it == freq.end()) {
					freq.insert(pair<string, int>(key, 1));
				} else {
					it->second++;
				}
			}

			int ave = count / freq.size();
			Logger().WriteInformation("Samples\t%d\n", freq.size());
			Logger().WriteInformation("Average\t%d\n", ave);

			int delta = ave >> 1;

			for_each(freq.begin(), freq.end(), [&](pair<string, int> it){
				Logger().WriteInformation("%s, %d times\n", it.first.c_str(), it.second);
				ASSERT1(it.second <= (ave + delta));
				ASSERT1(it.second >= (ave - delta));
			});
		};

		auto sample = [&](unsigned int n, unsigned int m, vector<unsigned int> & s) { Test::Random::Sample(n, m, s); };
		test(10, 1, 1000, sample);
		test(10, 2, 10000, sample);
		test(10, 4, 100000, sample);
		test(10, 6, 100000, sample);
		test(10, 8, 10000, sample);
		test(10, 10, 1000, sample);

		auto sample2 = [&](unsigned int n, unsigned int m, vector<unsigned int> & s) { Test::Random::Sample2(n, m, s); };
		test(10, 1, 1000, sample2);
		test(10, 2, 10000, sample2);
		test(10, 4, 100000, sample2);
		test(10, 6, 100000, sample2);
		test(10, 8, 10000, sample2);
		test(10, 10, 1000, sample2);
	});
}