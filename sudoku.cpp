#include "sudoku.h"

SudokuBoard::SudokuBoard(int initsize){
        size = initsize;
        freepositions = 81;
        for(int i = 0;i<size;i++){

            board.push_back({});

            for(int j = 0;j<size;j++){
                board[i].push_back({-1,{1,2,3,4,5,6,7,8,9}});
            }
        }

    }
    void SudokuBoard::printBoard(){

        for(int i = 0;i<size;i++){

            for(int j = 0;j<size;j++){
                if(board[i][j].entry== -1 ){
                    cout << "- ";
                }else{
                printf("%d ",board[i][j].entry);
                }
            }

            printf("\n");

        }

       

    }

    int SudokuBoard::SolveBoard(){

       if(freepositions == 0){
           int l = 100*(board[0][0].entry) + 10*(board[0][1].entry) + (board[0][2].entry);
        printBoard();
	   return l;
       }else{
        
            vector<int> nextmove = nextposition();

            if(nextmove[0] == -1){

                return 0;

            }

            set<int> possibilities = board[nextmove[1]][nextmove[0]].possibilities;
	        int depth = 0;
            for(auto x: possibilities){
               
                vector<pair<int,int>> changed = PlaceEntry(nextmove[0],nextmove[1],x);
               
               int k = SolveBoard();
                for(auto y:changed){
                    board[y.first][y.second].possibilities.insert(x);
                }
                board[nextmove[1]][nextmove[0]].entry = -1;
                freepositions += 1;
		        if(k !=0){
                    depth = k;
                    break;
		    }
               

               	

            }
            return depth ;

       }

    }

    vector<int> SudokuBoard::nextposition(){

        int minpossibilities = size+1;

        int squarex = 0;

        int squarey =0 ;

        int currentsize =0 ;

        for(int i = 0;i<size;i++){

            for(int j = 0;j<size;j++){

                if(board[i][j].entry == -1 ){

                currentsize = (board[i][j].possibilities).size();

                if(currentsize == 0){

                    vector<int> v = {-1,-1};

                    return v;

                }

                if(currentsize < minpossibilities){

                    minpossibilities = currentsize;
                    if(currentsize == 1){
                        return {j,i};
                    }
                    squarex = j;

                    squarey =i ;
                    
                   

                }

                }

            }

        }


        return {squarex,squarey};

    }
    
    vector<pair<int,int>>  SudokuBoard::PlaceEntry(int x, int y, int value){
        vector<pair<int,int>> pairs = {};
        for(int i = 0;i<size;i++){
            if(board[i][x].possibilities.erase(value)){
                pairs.push_back({i,x});
            }
        }
        for(int j = 0;j<size;j++){
            if(board[y][j].possibilities.erase(value)){
                pairs.push_back({y,j});
            }
        }
        int blockx = 3*(x/3);
        int blocky = 3*(y/3);
        for(int i = 0;i<3;i++){
            for(int j = 0;j<3;j++){
                if(board[blocky+j][blockx+i].possibilities.erase(value)){
                    pairs.push_back({blocky+j,blockx+i});
                }
            }
        }
        board[y][x].entry = value;
        freepositions -=1;
        return pairs;

    }

    void SudokuBoard::LoadBoard(vector<vector<int>> vec){
        for(int i =0;i<size;i++){
            for(int j = 0;j<size;j++){
                if (vec[i][j]>0){
                    PlaceEntry(j,i,vec[i][j]);
                }
            }
        }
    }



;
