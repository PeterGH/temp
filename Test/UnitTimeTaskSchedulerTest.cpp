#include "UnitTimeTaskSchedulerTest.h"

void UnitTimeTaskSchedulerTest::Init(void)
{
	Add("Run", [&](){
		vector<pair<int, int>> tasks {
			make_pair(1, 30),
			make_pair(2, 60),
			make_pair(3, 40),
			make_pair(4, 50),
			make_pair(4, 20),
			make_pair(4, 70),
			make_pair(6, 10)
		};

		for_each(tasks.begin(), tasks.end(), [&](pair<int, int> & t){
			Logger().WriteInformation("\t(%d, %d)", t.first, t.second);
		});

		Logger().WriteInformation("\n");
		
		vector<pair<int, int>> ontime;
		vector<pair<int, int>> late;
		Test::UnitTimeTaskScheduler::Schedule(tasks, ontime, late);

		for_each(ontime.begin(), ontime.end(), [&](pair<int, int> & t){
			Logger().WriteInformation("\t(%d, %d)", t.first, t.second);
		});

		Logger().WriteInformation("\n");

		for_each(late.begin(), late.end(), [&](pair<int, int> & t){
			Logger().WriteInformation("\t(%d, %d)", t.first, t.second);
		});

		Logger().WriteInformation("\n");

		ASSERT1(ontime.size() == 5);
		ASSERT1(late.size() == 2);
	});

	Add("Random", [&](){
		for (int i = 0; i < 100; i++) {
			int count = Test::Random::Next(1, 100);
			Logger().WriteInformation("Run %d, %d tasks", i, count);

			vector<pair<int, int>> tasks;
			for (int j = 0; j < count; j++) {
				tasks.push_back(make_pair(Test::Random::Next(1, count), Test::Random::Next(1, 1000)));
			}

			vector<pair<int, int>> ontime;
			vector<pair<int, int>> late;
			Test::UnitTimeTaskScheduler::Schedule(tasks, ontime, late);

			Logger().WriteInformation(", %d, %d\n", ontime.size(), late.size());

			for (int j = 0; j < (int)ontime.size(); j ++) {
				ASSERT2(
					j + 1 <= ontime[j].first, 
					Test::String::Format(
						"Ontime task with deadline %d and weight %d is scheduled in time slot %d",
						ontime[j].first, ontime[j].second, j + 1));
			}

			for (int j = 0; j < (int)late.size(); j ++) {
				ASSERT2(
					j + (int)ontime.size() + 1 > late[j].first, 
					Test::String::Format(
						"Late task with deadline %d and weight %d is scheduled in time slot %d",
						late[j].first, late[j].second, j + ontime.size() + 1));
			}
		}
	});
}