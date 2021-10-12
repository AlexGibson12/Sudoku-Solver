#ifndef sudoku_board_h
#define sudoku_board_h
#include <bits/stdc++.h>
using namespace std;
typedef enum {

    NUMBER,

    BLANK

} CellType;

typedef struct {

    CellType type;

    int entry;

    set<int> possibilities;

} SudokuEntry;
class SudokuBoard{
	public:
		int size;
		vector<vector<SudokuEntry*>> board;
        SudokuBoard(int size);
        SudokuBoard(int initsize, vector<vector<SudokuEntry*>> initial);
        bool ValidRow(vector<SudokuEntry*> entries);
        void PlaceEntry(int x, int y, int value);
        bool BoardIsSolved();
        void printBoard();
        int SolveBoard();
        vector<int> nextposition();
        void LoadBoard(vector<vector<int>> vec);
};


#endif
