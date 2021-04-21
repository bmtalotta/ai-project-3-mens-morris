#include <iostream>
#include "player.hpp"
using std::cout;
using std::cin;
using std::endl;
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

bool validPlacement(int x, int y, vector<vector<char>> &board){
    if(board[x][y] == ' '){
    return true;
    }
    return false;
}
bool validAdjacent(int startX, int startY, int endX, int endY, vector<vector<char>> &board,  std::shared_ptr<Player> &curPlayer){
    int distancex = endX-startX;
    int distancey = endY-startY;
    int direction = 1;
    if(distancey < 0 || distancex < 0){
        direction = -1;
    }
    if(distancey != 0 && distancey != 0){
        return false;
    }
    if(distancex + distancey > 2 || distancex + distancey < -2){
        return false;
    }
    for(int i = 0; i < abs(distancex); ++i){
        if(board[(startX + i * direction)][startY] == ' '){
            return true;
        }
        if(board[(startX + i * direction)][startY] == 'N'){
            return false;
        }
    }
    for(int i = 0; i < abs(distancey); ++i){
        if(board[startX][(startY + i * direction)] == ' '){
            return true;
        }
        if(board[startX][(startY + i * direction)] == 'N'){
            return false;
        }
    }
    return false;
}
void placePiece(int x, int y, vector<vector<char>> &board, std::shared_ptr<Player> &curPlayer){
    if(validPlacement(x, y, board)){
        board[x][y] = curPlayer->_piece;
    }
    return;
}
void movePiece(int startX, int startY, int endX, int endY, vector<vector<char>> &board, std::shared_ptr<Player> &curPlayer){
    if(validPlacement(endX, endY, board)){
        board[startX][startY] = ' ';
        board[endX][endY] = curPlayer->_piece;
    }
    return;
}
void swapPlayer(bool &playerPiece,  std::shared_ptr<Player> &curPlayer,  std::shared_ptr<Player> &playerOne,  std::shared_ptr<Player> &playerTwo){
    cout << "here" <<endl;
    playerPiece = !playerPiece;
    if(playerPiece){
        playerTwo = curPlayer;
        curPlayer = playerOne;
    }else{
        playerOne = curPlayer;
        curPlayer = playerTwo;
    }
}

void botPlacement(char &letter, int &number, vector<vector<char>> &board, char team){
    

}
bool checkForThree( std::shared_ptr<Player> &curPlayer, vector<vector<char>> &board){
    int horInRow = 0;
    int vertInRow = 0;
    for(int i = 0; i < board.size(); ++i){
        if(board[curPlayer->_lastMoveX][i] == curPlayer->_piece){
            vertInRow++;
        }else if(board[curPlayer->_lastMoveX][i] == ' ' || board[curPlayer->_lastMoveX][i] == 'N'){
            vertInRow = 0;
        }
        if(board[i][curPlayer->_lastMoveY] == curPlayer->_piece){
            horInRow++;
        }else if(board[i][curPlayer->_lastMoveY] == ' ' || board[i][curPlayer->_lastMoveY] == 'N'){
            horInRow = 0;
        }
    }
    if(horInRow == 3 || vertInRow == 3){
        return true;
    }
    return false;
};
int playerChoice(char &letter){
    int letterPos;
    if(std::tolower(letter) == 'a'){
        letterPos = 0;
    }else if(std::tolower(letter) == 'b'){
        letterPos = 1;
    }else if(std::tolower(letter) == 'c'){
        letterPos = 2;
    }else if(std::tolower(letter) == 'd'){
        letterPos = 3;
    }else if(std::tolower(letter) == 'e'){
        letterPos = 4;
    }
    return letterPos;
}
void takePiece( std::shared_ptr<Player> &curPlayer, vector<vector<char>> &board){
    char takeable = 'X';
    char letter;
    int y;
    int x;
    if(curPlayer->_piece == takeable){
        takeable = 'O';
    }
    cout << "enter position of oponents piece you want to take" << endl;
    cin >> letter;
    cin >> y;
    --y;
    x = playerChoice(letter);
    board[x][y] = ' ';
}
void botTurn( std::shared_ptr<Player> &curPlayer, vector<vector<char>> &board){

}

int menu(){
    cout << "1. player vs player\n 2. player vs AI\n3. AI vs AI" << endl;
    int userChoice;
    cin >> userChoice;
    return (userChoice);
}
void sixMensMorris(){
    vector<vector<char>> board = {{' ', 'B', ' ', 'B', ' '},    //B is bad spots, not placeable. N is not placeable or crossable. Blanks are valid spots.
                                  {'B', ' ', ' ', ' ', 'B'},
                                  {' ', ' ', 'N', ' ', ' '},
                                  {'B', ' ', ' ', ' ', 'B'},
                                  {' ', 'B', ' ', 'B', ' '}};
    printBoard(board);
    std::shared_ptr<Player> playerOne = makePlayer();
    std::shared_ptr<Player> playerTwo = makePlayer();
    playerTwo->_piece = 'O';
    std::shared_ptr<Player> curPlayer = playerTwo;
    
    int userChoice = menu();
    int goingFirst = rand() % 2 + 1;
    bool playerOnesTurn = true;
    if(userChoice == 1){
        playerOne->_AIplayer = false;
        playerTwo->_AIplayer = false;
        curPlayer = playerOne;
    }
    if(userChoice == 2){
        playerOne->_AIplayer = false;
        curPlayer = playerOne;
        if(goingFirst == 1){
            cout << "You are going first!" << endl;
        }
        else{
            playerOnesTurn = false;
            cout << "The AI is going first" << endl;
        }
    }
    int turnCount = 0;
    char letter;
    int number;
    int letterPos = 0;
    int removed;
    bool successfullyPlaced;
    while(turnCount < 12){
        removed = 0;
        cout << curPlayer->_piece << "'s turn" << endl;
        turnCount += 1;
        successfullyPlaced = false;
        if(curPlayer->_AIplayer == false){
            while(!successfullyPlaced){
                cout << "choose an available position to place your piece" << endl;
                cout << "Enter the letter" << endl;
                cin >> letter;
                letterPos = playerChoice(letter);
                cout << "Enter the number" << endl;
                cin >> number;
                --number;
                curPlayer->_lastMoveX = letterPos;
                curPlayer->_lastMoveY = number;
                if(validPlacement(letterPos, number, board)){
                    successfullyPlaced = true;
                    placePiece(letterPos, number, board, curPlayer);
                }else{
                    cout << "position invalid, try again" << endl;
                }
            }
        }else{
            botTurn(curPlayer, board);
        }
        
        if(checkForThree(curPlayer, board)){
            takePiece(curPlayer, board);
            removed = -1;
        }
        swapPlayer(playerOnesTurn, curPlayer, playerOne, playerTwo);
        curPlayer->_remaining += removed;
        printBoard(board);
    }
    curPlayer->_placing = false;
    playerOne->_placing = false;
    playerTwo->_placing = false;
    bool gameOver = false;
    bool successfulMove = false;
    int pieceX;
    int pieceY;
    while(!gameOver){
        if(curPlayer->_AIplayer){
            botTurn(curPlayer, board);
        }else{
            while(!successfulMove){
                cout << "select a piece to move" << endl;
                cout << "enter the letter" << endl;
                cin >> letter;
                pieceX = playerChoice(letter);
                cout <<"enter the number" << endl;
                cin >> pieceY;
                --pieceY;
                cout << "select where to move the piece" << endl;
                cout << "enter the letter" << endl;
                cin >> letter;
                letterPos = playerChoice(letter);
                cout <<"enter the number" << endl;
                cin >> number;
                --number;
                if(validAdjacent(pieceX, pieceY, letterPos, number, board, curPlayer) || (curPlayer->_canFly && validPlacement(letterPos, number, board))){
                    successfulMove = true;
                    movePiece(pieceX, pieceY, letterPos, number, board, curPlayer);
                }else{
                    cout << "position invalid, try again" << endl;
                }
            }
            successfulMove = false;
        }
        if(checkForThree(curPlayer, board)){
            takePiece(curPlayer, board);
            swapPlayer(playerOnesTurn,curPlayer,playerOne, playerTwo);
            --curPlayer->_remaining;
        }else{
            swapPlayer(playerOnesTurn,curPlayer,playerOne, playerTwo);
        }
        if(playerOne->_remaining == 2 || playerTwo->_remaining == 2){
            gameOver = true;
            swapPlayer(playerOnesTurn,curPlayer,playerOne, playerTwo);
            cout << curPlayer->_piece << "'s have won" << endl;
        }

    }

}