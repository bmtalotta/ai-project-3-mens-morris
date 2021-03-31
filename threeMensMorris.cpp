#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include <vector>
using std::vector;

void printBoard( vector<vector<char>> board){
    int positionTrackerX = -1;
    int positionTrackerY = -1;
    vector<vector<string>> blankDisplayBoard = {{"A1","-", "-", "-", "A3", "-","-","-","A5"},
                                                {"|", " ", " ", " ", "|"," ", " "," ", "|"},
                                                {"|", " ", "B2", "-", "B3","-", "B4"," ", "|"},
                                                {"|", " ", "|", " ", " "," ", "|"," ", "|"},
                                                {"C1", "-", "C2", " ", " ", " ", "C4","-","C5"},
                                                {"|", " ", "|", " ", " "," ", "|"," ", "|"}, 
                                                {"|", " ", "D2", "-", "D3","-", "D4"," ", "|"},
                                                {"|", " ", " ", " ", "|"," ", " "," ", "|"},
                                                {"E1","-", "-", "-", "E3", "-","-","-","E5"}};
    for(int i = 0; i < blankDisplayBoard.size(); ++i){
        if(i%2 == 0){
            ++positionTrackerY;
        };
        for(int j = 0; j < blankDisplayBoard[i].size(); ++j){
            if(blankDisplayBoard[i][j].size() == 2){
                ++positionTrackerX;
                if(board[positionTrackerY][positionTrackerX] == 'B' ||board[positionTrackerY][positionTrackerX] == 'N'){
                    ++positionTrackerX;
                }
                if(board[positionTrackerY][positionTrackerX] != ' '){
                    cout << board[positionTrackerY][positionTrackerX] << ' ';
                }
                else{
                    cout << blankDisplayBoard[i][j] << ' ';
                }
            }
            else{
            cout << blankDisplayBoard[i][j] << ' ';
            }
            if(blankDisplayBoard[i][j].size() != 2){
                cout << ' ';
            }
        }
        positionTrackerX = -1;
        cout << std::endl;
    }
}
void threeMensMorris(int numberOfRealPlayers){
    vector<vector<char>> board = {{' ', 'B', ' ', 'B', ' '},    //B is bad spots, not placeable. N is not placeable or crossable blanks are valid spots.
                                  {'B', ' ', ' ', ' ', 'B'},
                                  {' ', ' ', 'N', ' ', ' '},
                                  {'B', ' ', ' ', ' ', 'B'},
                                  {' ', 'B', ' ', 'B', ' '}};
    printBoard(board);
}
