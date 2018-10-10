#include "Header.h"

void MatrixProblemTest::Init(void)
{
	Add("SearchWord", [&]() {
		auto check = [&](const vector<vector<char>> & m, const string & w, bool e) {
			Logger().Print(m, "%c", " ");
			Logger().WriteInformation("%s\n", w.c_str());
			bool r = MatrixProblem::SearchWord::Existed(m, w);
			bool r2 = MatrixProblem::SearchWord::Existed2(m, w);
			ASSERT1(r == e);
			ASSERT1(r2 == e);
		};
		{
			vector<vector<char>> m =
			{
				{ 'x', 'x', 'x' },
				{ 'x', 'h', 'e' },
				{ 'o', 'l', 'x' },
				{ 'x', 'l', 'x' }
			};
			check(m, "hello", true);
		}
		{
			vector<vector<char>> m =
			{
				{ 'x', 'x', 'x' },
				{ 'x', 'h', 'e' },
				{ 'o', 'l', 'x' },
				{ 'x', 'l', 'x' }
			};
			check(m, "hillo", false);
		}
		{
			// This will fail
			vector<vector<char>> m =
			{
				{ 'x', 'w', 'h', 'b' },
				{ 'u', 'k', 'o', 'm' },
				{ 'z', 'w', 'v', 'a' },
				{ 't', 'd', 'k', 'n' }
			};
			// check(m, "owuxwhm", true);
		}
		{
			vector<vector<char>> m =
			{
				{ 'w', 'x', 'x' },
				{ 'x', 'w', 'x' },
				{ 'x', 'x', 'x' }
			};
			check(m, "www", true);
		}
		{
			vector<vector<char>> m =
			{
				{ 'w', 'y', 'x' },
				{ 'x', 'w', 'x' },
				{ 'x', 'x', 'x' }
			};
			check(m, "wwwy", true);
		}
		{
			vector<vector<char>> m =
			{
				{ 'x', 'x', 'x' },
				{ 'w', 'y', 'x' },
				{ 'x', 'w', 'x' }
			};
			check(m, "wwwy", true);
		}
		{
			vector<vector<char>> m =
			{
				{ 'y', 'x', 'x' },
				{ 'w', 'x', 'x' },
				{ 'x', 'w', 'x' }
			};
			check(m, "wwwy", true);
		}
		/*
		{
			for (int i = 0; i < 10; i++) {
				string word = String::Random(string("abcdefghijklmnopqrstuvwxyz"), 1 + (rand() % 10));
				vector<vector<char>> matrix = MatrixProblem::Generator::RandomWithoutWord(word);
				check(matrix, word, false);
			}
		}
		{
			for (int i = 0; i < 10; i++) {
				string word = String::Random(string("abcdefghijklmnopqrstuvwxyz"), 1 + (rand() % 10));
				vector<vector<char>> matrix = MatrixProblem::Generator::RandomWithWord(word);
				check(matrix, word, true);
			}
		}
		*/
	});

	Add("SurroundedRegion", [&]() {
		auto verify = [&](vector<vector<char>> & board) {
			int height = board.size();
			int width = board[0].size();
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (board[i][j] == 'O') {
						bool boundary = i == 0 || i == height - 1 || j == 0 || j == width - 1;
						pair<int, int> p = make_pair(i, j);
						set<pair<int, int>> region;
						queue<pair<int, int>> q;
						region.insert(p);
						q.push(p);
						while (!q.empty()) {
							p = q.front();
							q.pop();
							pair<int, int> n;
							if (p.first > 0 && board[p.first - 1][p.second] == 'O') {
								if (p.first - 1 == 0) boundary = true;
								n = make_pair(p.first - 1, p.second);
								if (region.find(n) == region.end()) {
									region.insert(n);
									q.push(n);
								}
							}
							if (p.second > 0 && board[p.first][p.second - 1] == 'O') {
								if (p.second - 1 == 0) boundary = true;
								n = make_pair(p.first, p.second - 1);
								if (region.find(n) == region.end()) {
									region.insert(n);
									q.push(n);
								}
							}
							if (p.second < width - 1 && board[p.first][p.second + 1] == 'O') {
								if (p.second + 1 == width - 1) boundary = true;
								n = make_pair(p.first, p.second + 1);
								if (region.find(n) == region.end()) {
									region.insert(n);
									q.push(n);
								}
							}
							if (p.first < height - 1 && board[p.first + 1][p.second] == 'O') {
								if (p.first + 1 == height - 1) boundary = true;
								n = make_pair(p.first + 1, p.second);
								if (region.find(n) == region.end()) {
									region.insert(n);
									q.push(n);
								}
							}
						}

						ASSERT1(boundary);
					}
				}
			}
		};

		auto check = [&](vector<vector<char>> & board, vector<vector<char>> & board2) {
			Logger().WriteInformation("Input:\n");
			Logger().Print(board, "%c");
			MatrixProblem::SurroundedRegion::Capture(board);
			Logger().WriteInformation("Output1:\n");
			Logger().Print(board, "%c");;
			verify(board);
			MatrixProblem::SurroundedRegion::Capture2(board2);
			Logger().WriteInformation("Output2:\n");
			Logger().Print(board2, "%c");
			verify(board2);
			int height = board.size();
			int width = board[0].size();
			int height2 = board.size();
			int width2 = board[0].size();
			ASSERT1(height == height2);
			ASSERT1(width == width2);
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					ASSERT1(board[i][j] == board2[i][j]);
				}
			}
		};
		{
			vector<vector<char>> board = { { 'X' } };
			vector<vector<char>> board2 = { { 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O' } };
			vector<vector<char>> board2 = { { 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'O' } };
			vector<vector<char>> board2 = { { 'X', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'O' } };
			vector<vector<char>> board2 = { { 'O', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X' },{ 'X' } };
			vector<vector<char>> board2 = { { 'X' },{ 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X' },{ 'O' } };
			vector<vector<char>> board2 = { { 'X' },{ 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O' },{ 'X' } };
			vector<vector<char>> board2 = { { 'O' },{ 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O' },{ 'O' } };
			vector<vector<char>> board2 = { { 'O' },{ 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X' },{ 'X', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'X' },{ 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X' },{ 'X', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'X' },{ 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'O' },{ 'X', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'O' },{ 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X' },{ 'O', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'X' },{ 'O', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X' },{ 'X', 'O' } };
			vector<vector<char>> board2 = { { 'X', 'X' },{ 'X', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'O' },{ 'X', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'O' },{ 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X' },{ 'O', 'O' } };
			vector<vector<char>> board2 = { { 'X', 'X' },{ 'O', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X' },{ 'O', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'X' },{ 'O', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'O' },{ 'X', 'O' } };
			vector<vector<char>> board2 = { { 'X', 'O' },{ 'X', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X' },{ 'X', 'O' } };
			vector<vector<char>> board2 = { { 'O', 'X' },{ 'X', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'O' },{ 'O', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'O' },{ 'O', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X', 'X' },{ 'X', 'X', 'X' },{ 'X', 'X', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'X', 'X' },{ 'X', 'X', 'X' },{ 'X', 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X', 'X' },{ 'X', 'X', 'X' },{ 'X', 'X', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'X', 'X' },{ 'X', 'X', 'X' },{ 'X', 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X', 'X' },{ 'X', 'O', 'X' },{ 'X', 'X', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'X', 'X' },{ 'X', 'O', 'X' },{ 'X', 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'O', 'X' },{ 'X', 'O', 'X' },{ 'X', 'X', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'O', 'X' },{ 'X', 'O', 'X' },{ 'X', 'X', 'X' } };
			check(board, board2);
		}
		{
			for (int i = 0; i < 100; i++) {
				int height = 1 + rand() % 100;
				int width = 1 + rand() % 100;
				Logger().WriteInformation("Run %d, %d X %d\n", i, height, width);
				vector<vector<char>> board;
				vector<vector<char>> board2;
				for (int j = 0; j < height; j++) {
					vector<char> row;
					for (int k = 0; k < width; k++) {
						int v = rand();
						if ((v & 0x1) == 1) {
							row.push_back('X');
						}
						else {
							row.push_back('O');
						}
					}
					board.push_back(row);
					board2.push_back(row);
				}
				check(board, board2);
			}
		}
	});
}