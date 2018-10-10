// SearchString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <regex>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 3) {
		cout << "Usage: " << argv[0] << " [Pattern] [Input]" << endl;
		return -1;
	}

	try {
		regex pattern(argv[1]);
		match_results<const char*> results;
		char* input = argv[2];
		if (regex_match(input, results, pattern, regex_constants::match_default)) {
			cout << "regex_match succeeded." << endl;
		} else {
			cout << "regex_match failed." << endl;
			if (regex_search(input, results, pattern, regex_constants::match_default)) {
				cout << "regex_search succeeded." << endl;
			} else {
				cout << "regex_search failed." << endl;
				return -1;
			}		
		}

		cout << "StartPosition\tEndPosition\tValue" << endl;
		for (cmatch::iterator it = results.begin(); it != results.end(); it ++) {
			cout << (it->first - input) << "\t" << (it->second - input) << "\t" << it->str() << endl;
		}	
	} catch (regex_error& err) {
		cout << "Error " << err.code() << ": " << err.what() << endl;
		return err.code();
	}

    return 0;
}

