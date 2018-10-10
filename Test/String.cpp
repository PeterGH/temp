#include "String.h"

namespace Test {

	// Find the length of shortest transformation sequence from a start string to a end string, such that
	// 1. only one character can be changed at each step
	// 2. each intermediate word must exist in a dictionary
	// Notes:
	// 1. all words are in the lower case
	// 2. start and end may not be in the dictionary
	int String::WordLadder(const string & start, const string & end, const unordered_set<string> & dictionary)
	{
		if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return 0;
		unordered_set<string> dict;
		dict.insert(dictionary.begin(), dictionary.end());
		if (dict.find(start) == dict.end()) dict.insert(start);
		if (dict.find(end) == dict.end()) dict.insert(end);

		map<string, vector<string>> graph;
		for_each (dict.begin(), dict.end(), [&](string word){
			graph[word] = vector<string> { };
		});

		for_each (dict.begin(), dict.end(), [&](string word){
			int wordLen = word.length();
			for (map<string, vector<string>>::iterator it = graph.begin(); it != graph.end(); it++){
				if (wordLen == it->first.length()) {
					int diff = 0;
					for (int i = 0; i < wordLen; i++) {
						if (word[i] != it->first[i]) diff++;
						if (diff > 1) break;
					}
					if (diff == 1) {
						it->second.push_back(word);
					}
				}
			}
		});

		bool found = false;
		unordered_set<string> visited;
		queue<string> q[2];
		int step = 0;
		q[0].push(start);
		visited.insert(start);
		while (!q[0].empty() || !q[1].empty()) {
			queue<string> & current = q[step & 0x1];
			queue<string> & next = q[(step + 1) & 0x1];
			while (!current.empty()) {
				string word = current.front();
				current.pop();
				for (size_t i = 0; i <  graph[word].size(); i++){
					if (graph[word][i] == end) {
						found = true;
						break;
					}
					if (visited.find(graph[word][i]) == visited.end()){
						visited.insert(graph[word][i]);
						next.push(graph[word][i]);
					}
				}

				if (found) {
					return step + 2;
				}
			}

			step++;
		}
		return 0;
	}

	// Find the length of shortest transformation sequence from a start string to a end string, such that
	// 1. only one character can be changed at each step
	// 2. each intermediate word must exist in a dictionary
	// Notes:
	// 1. all words are in the lower case
	// 2. start and end may not be in the dictionary
	int String::WordLadder2(const string & start, const string & end, const unordered_set<string> & dictionary)
	{
		if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return 0;
		unordered_set<string> dict;
		dict.insert(dictionary.begin(), dictionary.end());

		auto diff1 = [&](const string & first, const string & second)->bool {
			if (first.size() != second.size()) return false;
			int diff = 0;
			for (size_t i = 0; i < first.length(); i++) {
				if (first[i] != second[i]) diff++;
				if (diff > 1) return false;
			}
			return diff == 1;
		};

		vector<string> q[2];
		int step = 0;
		q[0].push_back(start);
		while (!q[0].empty() || !q[1].empty()) {
			vector<string> & current = q[step & 0x1];
			vector<string> & next = q[(step + 1) & 0x1];
			while (!current.empty()) {
				string word = current.front();
				current.erase(current.begin());
				for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); it++){
					if (diff1(word, *it)) {
						if (diff1(*it, end)) {
							return step + 3;
						} else {
							next.push_back(*it);
						}
					}
				}
			}
			for_each (next.begin(), next.end(), [&](string & s){
				dict.erase(s);
			});
			step++;
		}
		return 0;
	}

	// Find the length of shortest transformation sequence from a start string to a end string, such that
	// 1. only one character can be changed at each step
	// 2. each intermediate word must exist in a dictionary
	// Notes:
	// 1. all words are in the lower case
	// 2. start and end may not be in the dictionary
	int String::WordLadder3(const string & start, const string & end, const unordered_set<string> & dictionary)
	{
		if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return 0;

		unordered_set<string> visited;
		queue<string> q[2];
		int step = 0;
		q[0].push(start);
		visited.insert(start);
		while (!q[0].empty() || !q[1].empty()) {
			queue<string> & current = q[step & 0x1];
			queue<string> & next = q[(step + 1) & 0x1];
			while (!current.empty()) {
				string word = current.front();
				current.pop();
				int wordLen = word.size();
				string temp;
				for (int i = 0; i < wordLen; i++) {
					temp = word;
					for (char j = 'a'; j <= 'z'; j++) {
						temp[i] = j;
						if (temp == end) {
							return step + 2;
						}
						if (dictionary.find(temp) != dictionary.end() && visited.find(temp) == visited.end()) {
							visited.insert(temp);
							next.push(temp);
						}
					}
				}
			}
			step++;
		}
		return 0;
	}

	// Find all shortest transformation sequences from a start string to a end string, such that
	// 1. only one character can be changed at each step
	// 2. each intermediate word must exist in a dictionary
	// Notes:
	// 1. all words are in the lower case
	// 2. start and end may not be in the dictionary
	vector<vector<string>> String::WordLadders(const string & start, const string & end, const unordered_set<string> & dictionary)
	{
		vector<vector<string>> ladders = { };
		if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return ladders;

		unordered_map<string, vector<vector<string>>> path;
		unordered_map<string, int> level;
		queue<string> q[2];
		int step = 0;
		bool stop = false;
		q[0].push(start);
		level[start] = step;
		path[start] = vector<vector<string>> { };
		path[start].push_back(vector<string> { start });
		while (!q[0].empty() || !q[1].empty()) {
			queue<string> & current = q[step & 0x1];
			queue<string> & next = q[(step + 1) & 0x1];
			while (!current.empty()) {
				string word = current.front();
				current.pop();
				int wordLen = word.size();
				string temp;
				for (int i = 0; i < wordLen; i++) {
					temp = word;
					for (char j = 'a'; j <= 'z'; j++) {
						temp[i] = j;
						if (temp == end) {
							for_each(path[word].begin(), path[word].end(), [&](vector<string> & p){
								vector<string> r(p);
								r.push_back(temp);
								ladders.push_back(r);
							});
							stop = true;
						} else if (dictionary.find(temp) != dictionary.end()) {
							if (level.find(temp) == level.end()) {
								level[temp] = step + 1;
								next.push(temp);
								path[temp] = vector<vector<string>> { };
							}
							if (level[temp] > step) {
								for_each(path[word].begin(), path[word].end(), [&](vector<string> & p){
									vector<string> r(p);
									r.push_back(temp);
									path[temp].push_back(r);
								});
							}
						}
					}
				}
			}
			if (stop) break;
			step++;
		}
		return ladders;
	}

	// Find all subsequences of input string that match a pattern.
	// Return the total count.
	int String::MatchSubsequence(const string & input, const string & pattern)
	{
		if (input.length() < pattern.length() || pattern.length() == 0) return 0;
		if (input.length() == pattern.length()) {
			if (input == pattern) return 1;
			else return 0;
		}
		int count = 0;
		for (size_t i = 0; i <= input.length() - pattern.length(); i++) {
			if (input[i] == pattern[0]) {
				if (pattern.length() == 1) count++;
				else count += MatchSubsequence(input.substr(i+1), pattern.substr(1));
			}
		}
		return count;
	}

	// Find all subsequences of input string that match a pattern.
	// Return the total count.
	int String::MatchSubsequence2(const string & input, const string & pattern)
	{
		if (input.length() < pattern.length() || pattern.length() == 0) return 0;

		map<pair<size_t, size_t>, int> count;
		function<int(size_t, size_t)>
		search = [&](size_t i, size_t j) -> int {
			if (input.length() - i == pattern.length() - j) {
				return input.substr(i) == pattern.substr(j) ? 1 : 0;
			}
			int c = 0;
			for (size_t k = i; k <= input.length() - pattern.length() + j; k++) {
				if (input[k] == pattern[j]) {
					pair<size_t, size_t> p = make_pair(k, j);
					if (count.find(p) == count.end()) {
						if (j == pattern.length() - 1) {
							count[p] = 1;
						} else {
							count[p] = search(k+1, j+1);
						}
					}
					c+= count[p];
				}
			}
			return c;
		};

		return search(0, 0);
	}
}