#include "Test.h"

void CppTest::Init(void)
{
    Add("Subtraction of two size_t", [&]() {
        size_t a = 123;
        size_t b = 456;
        auto c = a - b;
        Logger() << "(size_t)" << a << " - (size_t)" << b << " = (" << typeid(a - b).name() << ")" << a - b << "\n";
        ASSERT1(a - b > 0);
    });

    Add("Map by pair", [&]() {
        map<pair<int, int>, int> m;
        m[make_pair(0, 1)] = 1;
        m[make_pair(2, 3)] = 5;
        ASSERT1(m.find(make_pair(2, 3)) != m.end());
        ASSERT1(m.find(make_pair(0, 1)) != m.end());
        ASSERT1(m.find(make_pair(0, 3)) == m.end());
    });

    Add("Change string", [&]() {
        string s = "a string";
        Logger() << s << "\n";
        s[0] = 'b';
        Logger() << s << endl;
        s[5] = '\0';
        Logger() << s << endl;
    });

    Add("String character", [&]() {
        string s = "ab";
        ASSERT1(s[0] == 'a');
        ASSERT1(s[1] == 'a' + 1);
    });

    Add("String resize", [&]() {
        auto print = [&](string s) {
            Logger() << "\"" << s << "\".length = " << s.length() << endl;
            Logger() << "\"" << s << "\".size = " << s.size() << endl;
        };
        string str = "0123456789";
        print(str);
        for (int i = 9; i >= 0; i--) {
            str.resize(i);
            print(str);
        }
    });

    Add("atoi", [&]() {
        auto test = [&](string s, int expect) {
            int n = atoi(s.c_str());
            ASSERT1(n == expect);
        };
        test("01", 1);
    });

    Add("Sort pairs", [&]() {
        vector<pair<int, int>> pairs;
        for (int i = 9; i > 0; i--)
        {
            for (int j = 9; j > 0; j--)
            {
                pairs.push_back(make_pair(i, j));
            }
        }
        sort(pairs.begin(), pairs.end());
        for (size_t i = 0; i < pairs.size(); i++)
        {
            Logger() << "(" << pairs[i].first << ", " << pairs[i].second << ")" << endl;
        }
        ASSERT1(make_pair(1, 2) < make_pair(2, 1));
    });

    Add("Sort vector<vector>", [&]() {
        auto check = [&](vector<vector<int>>& g) {
            Logger() << "Before sort" << endl << g;
            sort(g.begin(), g.begin());
            Logger() << "After sort" << endl << g;
        };
        {
            vector<vector<int>> g =
            {
                { 3, 2 , 1},
                { 2, 1},
                { 3, 1},
                { 3, 2},
                { 2 },
                { 1}
            };
            check(g);
        }
        {
            vector<vector<int>> g =
            {
                { 1, 2 , 3 },
                { 1, 2 },
                { 1, 3 },
                { 2, 3 },
                { 2 },
                { 1 }
            };
            check(g);
        }
    });
}