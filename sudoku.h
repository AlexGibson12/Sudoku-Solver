#ifndef sudoku_board_h
#define sudoku_board_h
#include <bits/stdc++.h>
using namespace std;


typedef struct {
    int entry;
    set<int> possibilities;
} SudokuEntry;
class SudokuBoard{
	public:
		int size;
		vector<vector<SudokuEntry>> board;
        SudokuBoard(int size);
       
        vector<pair<int,int>> PlaceEntry(int x, int y, int value);
        bool BoardIsSolved();
        void printBoard();
        int SolveBoard();
        vector<int> nextposition();
        void LoadBoard(vector<vector<int>> vec);
};


#endif
