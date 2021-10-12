#include "sudoku.h"
void sudoku_free(SudokuBoard* board){

    for(int i =0;i<board->size;i++){

        for(int j = 0;j<board->size;j++){

            free((board->board)[i][j]);

        }

    }

    free(board);

}

SudokuBoard::SudokuBoard(int initsize){

        size = initsize;

        for(int i = 0;i<size;i++){

            board.push_back({});

            for(int j = 0;j<size;j++){

                SudokuEntry* entry = new SudokuEntry;

                entry->type = BLANK;

                entry->entry = -1;

                set<int> newset;

                for(int i = 0;i<size;i++){

                    newset.insert(i+1);

                }

               

                entry->possibilities = newset;

                board[i].push_back(entry);

            }

           

        }

    }

SudokuBoard::SudokuBoard(int initsize, vector<vector<SudokuEntry*>> initial){

        board = initial;

        size = initsize;

    }

    bool SudokuBoard::ValidRow(vector<SudokuEntry*> entries){

        int numberentries = 0;

        set<int> entryvalues {};

        for(auto x: entries){

            if(x->type == NUMBER){

                numberentries++;

                entryvalues.insert(x->entry);

            }

               

        }

        return numberentries == entryvalues.size();

    }

    bool SudokuBoard::BoardIsSolved(){

       

        bool solved = true;

        for(int i = 0;i<size;i++){

            for(int j = 0;j<size;j++){

                if(board[i][j]->type == BLANK){

                    solved = false;

                }

            }

        }

       

        return solved;

    }

    void SudokuBoard::printBoard(){

        for(int i = 0;i<size;i++){

            for(int j = 0;j<size;j++){
                if(board[i][j]->entry== -1 ){
                    cout << "- ";
                }else{
                printf("%d ",board[i][j]->entry);
                }
            }

            printf("\n");

        }

       

    }

    int SudokuBoard::SolveBoard(){

       if(BoardIsSolved()){
        return 100*(board[0][0]->entry) + 10*(board[0][1]->entry) + (board[0][2]->entry); 
       }else{
        
            vector<int> nextmove = nextposition();

            if(nextmove[0] == -1){

                return 0;

            }

            set<int> possibilities = board[nextmove[1]][nextmove[0]]->possibilities;
	    int depth = 0;
            for(auto x: possibilities){
                SudokuBoard* newboard = new SudokuBoard(size);
                vector<vector<int>> temp;
                for(int i = 0;i<size;i++){
                    temp.push_back({});
                    for(int j = 0;j<size;j++){
                        if(board[i][j]->type == BLANK){
                            temp[i].push_back(-1);
                        }else{
                            temp[i].push_back(board[i][j]->entry);
                        }
                        
                    }
                }
                newboard->LoadBoard(temp);
                newboard->PlaceEntry(nextmove[0],nextmove[1],x);
		int k = newboard->SolveBoard();
		if(k !=0){
                depth = k;
		}
		sudoku_free(newboard);
               

               	

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

                if(board[i][j]->type == BLANK ){

                currentsize = (board[i][j]->possibilities).size();

                if(currentsize == 0){

                    vector<int> v = {-1,-1};

                    return v;

                }

                if(currentsize < minpossibilities){

                    minpossibilities = currentsize;

                    squarex = j;

                    squarey =i ;

                   

                }

                }

            }

        }

        vector<int> v = {squarex,squarey};

        return v;

    }

    void SudokuBoard::PlaceEntry(int x, int y, int value){
        
        for(int i = 0;i<size;i++){

            (board[i][x] -> possibilities).erase(value);

        }
        for(int j = 0;j<size;j++){

            (board[y][j] -> possibilities).erase(value);

        }
        int blockx = 3*(x/3);

        int blocky = 3*(y/3);
       
        for(int i = 0;i<3;i++){

            for(int j = 0;j<3;j++){
                
                (board[blocky+j][blockx+i] -> possibilities).erase(value);

            }

        }
        board[y][x] -> possibilities = {};
        board[y][x]->entry = value;

        board[y][x] ->type = NUMBER;

    }

    void SudokuBoard::LoadBoard(vector<vector<int>> vec){

        for(int i = 0;i<size;i++){

            for(int j = 0;j<size;j++){

                SudokuEntry* entry = new SudokuEntry;

                entry->type = BLANK;

                entry->entry = -1;

                set<int> newset;

                for(int i = 0;i<size;i++){

                    newset.insert(i+1);

                }

               

                entry->possibilities = newset ;

                board[i][j] = entry;

            }

        }
        for(int i =0;i<size;i++){

            for(int j = 0;j<size;j++){
             
                if (vec[i][j]>0){

                    
                    PlaceEntry(j,i,vec[i][j]);

                }

            }

        }

    }



