#include "sudoku.h"
bool scanNextBoard(vector<vector<int>>& state,ifstream& fin){
	string x;
	fin >> x;
	fin >> x;
	state = {};

	for(int i = 0;i<9;i++){
		x = "";
		state.push_back({});
		if(fin>>x){
			for(int j =0 ;j<9;j++){
				state[i].push_back(x[j]-'0');
				
			if(state[i][j] == 0){
				state[i][j] = -1;
			}}
		}else{
			return false;
		}
	}
	return true;

}
int main()
{

    vector<vector<int>> state {}; 
    ifstream fin ;
    fin.open("input.txt",ios::in);
    int l = 0;
    while(scanNextBoard(state,fin)){
    SudokuBoard stuff = SudokuBoard(9);
    stuff.LoadBoard(state);
    l+=stuff.SolveBoard();
    }
    cout << l << endl;
    return 0;

}

