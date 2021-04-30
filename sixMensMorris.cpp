#include <iostream>
#include "player.hpp"
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include<math.h>
#include<chrono>
using std::shared_ptr;
#include <stdio.h>
void printBoard( vector<vector<char>> board){
    int positionTrackerX = -1;
    int positionTrackerY = -1;
    cout << "  1     2     3     4     5" << endl;
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
            if(positionTrackerY == 0){
                cout << "A ";
            }else if(positionTrackerY == 1){
                cout << "B ";
            }else if(positionTrackerY == 2){
                cout << "C ";
            }else if(positionTrackerY == 3){
                cout << "D ";
            }else if(positionTrackerY == 4){
                cout << "E ";
            }
        }else{
            cout << "  ";
        }
        for(int j = 0; j < blankDisplayBoard[i].size(); ++j){
            if(blankDisplayBoard[i][j].size() == 2){
                ++positionTrackerX;
                if(board[positionTrackerY][positionTrackerX] == 'B' ||board[positionTrackerY][positionTrackerX] == 'N'){
                    ++positionTrackerX;
                }
                if(board[positionTrackerY][positionTrackerX] != ' '){
                    if(board[positionTrackerY][positionTrackerX] == 'X'){
                        printf("\033[31m");
                        cout << board[positionTrackerY][positionTrackerX] << ' ' << ' ';
                    }else if(board[positionTrackerY][positionTrackerX] == 'O'){
                        printf("\033[34m");
                        cout << board[positionTrackerY][positionTrackerX] << ' ' << ' ';
                    }else{
                        printf("\033[0m");
                        cout << board[positionTrackerY][positionTrackerX] << ' ' << ' ';
                    }
                }
                else{
                    cout << blankDisplayBoard[i][j] << ' ';
                }
            }
            else{
                
                printf("\033[0m");
                cout << blankDisplayBoard[i][j] << ' ';
            }
            if(blankDisplayBoard[i][j].size() != 2){
                cout << ' ';
            }
        }
        positionTrackerX = -1;
        
        printf("\033[0m");
        cout << std::endl;
    }
}

bool validPlacement(int x, int y, vector<vector<char>> &board){
    if(board[x][y] == ' '){
    return true;
    }
    return false;
}
bool validAdjacent(int startX, int startY, int endX, int endY, vector<vector<char>> &board,  std::shared_ptr<Player> curPlayer){
    int distancex = endX-startX;
    int distancey = endY-startY;
    int direction = 1;
    
    if(board[startX][startY] != curPlayer->_piece){
        return false;
    }
    if(distancey < 0 || distancex < 0){
        direction = -1;
    }
    if(distancex != 0 && distancey != 0){
        return false;
    }
    if(distancex + distancey > 2 || distancex + distancey < -2){
        return false;
    }
    for(int i = 1; i < abs(distancex) + 1; ++i){
        if(board[(startX + (i * direction))][startY] == ' '){
            return true;
        }
        if(board[(startX + (i * direction))][startY] == 'N'){
            return false;
        }
    }
    for(int i = 1; i < abs(distancey) + 1; ++i){
        if(board[startX][(startY + (i * direction))] == ' '){
            return true;
        }
        if(board[startX][(startY + (i * direction))] == 'N'){
            return false;
        }
    }
    return false;
}
void placePiece(int x, int y, vector<vector<char>> &board, std::shared_ptr<Player> curPlayer){
    if(validPlacement(x, y, board)){
        board[x][y] = curPlayer->_piece;
    }
    return;
}
void movePiece(int startX, int startY, int endX, int endY, vector<vector<char>> &board, std::shared_ptr<Player> curPlayer){
    if(validPlacement(endX, endY, board)){
        board[startX][startY] = ' ';
        board[endX][endY] = curPlayer->_piece;
    }
    return;
}
bool checkForThree( std::shared_ptr<Player> curPlayer, vector<vector<char>> &board){
    int horInRow = 0;
    int vertInRow = 0;
    for(int i = 0; i < 5; ++i){
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
}
bool checkForThreeBot( int lastMoveX, int lastMoveY, char piece, vector<vector<char>> &board){
    int horInRow = 0;
    int vertInRow = 0;
    for(int i = 0; i < board.size(); ++i){
        if(board[lastMoveX][i] == piece){
            vertInRow++;
        }else if(board[lastMoveX][i] == ' ' || board[lastMoveX][i] == 'N'){
            vertInRow = 0;
        }
        if(board[i][lastMoveY] == piece){
            horInRow++;
        }else if(board[i][lastMoveY] == ' ' || board[i][lastMoveY] == 'N'){
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
void takePiece( std::shared_ptr<Player> curPlayer, vector<vector<char>> &board){
    printBoard(board);
    char takeable = 'X';
    char letter;
    int y;
    int x;
    bool successfullTake = false;
    while(!successfullTake){
        if(curPlayer->_piece == takeable){
            takeable = 'O';
        }
        cout << "enter position of oponents piece you want to take" << endl;
        cin >> letter;
        cin >> y;
        --y;
        x = playerChoice(letter);
        if(board[x][y] == takeable){
            board[x][y] = ' ';
            successfullTake = true;
            cout << "piece successfully taken" << endl;
        }else{
            cout << "chosen position invalid, pick again" << endl;
            printBoard(board);
        }
    }
}
struct nodeData{
	vector<vector<char>> curBoard;
	int numberOfVisits=0;
	int lastMoveX=0;
	int lastMoveY=0;
	int winScore=0;
	char team;
	int gameState=3;
    bool placing;
    bool canFly = false;
    int remaining;
    int numPlaced;
	nodeData(){
		
	}
	nodeData(int x, int y, char piece, int placed, int rem, vector<vector<char>> board){
		lastMoveY = y;
		lastMoveX = x;
		team=piece;
		curBoard = board;
        remaining = rem;
        numPlaced = placed;
	}
};
struct boardNode{
	nodeData data;
	std::shared_ptr<boardNode> parent;
	vector<std::shared_ptr<boardNode>>children;
	boardNode()
	{
	}
	boardNode(std::shared_ptr<boardNode> base, nodeData ndata){
		parent=base;
		data = ndata;
	}
	
};

bool checkForWinner(vector<vector<char>> board, char teamChecking){
    char opponentTeam = 'X';
    int count = 0;
    if(opponentTeam == teamChecking){
        opponentTeam = 'O';
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(board[i][j] == opponentTeam){
                count++;
            }
        }
    }
    
    if(count == 2){
       return true;
    }
    return false;
}
std::shared_ptr<boardNode> make_child(std::shared_ptr<boardNode> parent, nodeData data){
		return std::make_unique<boardNode>(boardNode(parent, data));
	}

double ucbValue (int parentVisitCount, int winScore, int numberOfVisits){
	if(numberOfVisits == 0){
		return 9999;
	}
    
	//cout << 100000*(winScore / numberOfVisits) + 1.41 * sqrt(log(parentVisitCount)/numberOfVisits) << endl;
	return (winScore / numberOfVisits) + (1.41 * sqrt(log(parentVisitCount)/numberOfVisits));
}

shared_ptr<boardNode> findBestNodeWithUCB(shared_ptr<boardNode> node){
	auto parentVisitCount = node->data.numberOfVisits;
	vector<double> childUCB;
	for (int i = 0; i < node->children.size(); ++i){
		childUCB.push_back(ucbValue(parentVisitCount, node->children[i]->data.winScore, node->children[i]->data.numberOfVisits));
	}

	double curMax = childUCB[0];
	int maxIndx = 0;
	for (int i = 1; i < node->children.size(); ++i){
		//cout << childUCB[i] << " halfway" << endl;
		if(curMax < childUCB[i]){
			curMax = childUCB[i];
			maxIndx = i;
		}
	}
	//cout << curMax << endl;
	return node->children[maxIndx];
}
shared_ptr<boardNode> selectPromisingNode(shared_ptr<boardNode> rootNode){
	return findBestNodeWithUCB(rootNode);
}

void playTurn(vector<vector<char>> &board, char teamPlaying,bool placing){
    bool canFly =false;
    int count = 0;
    int randMove;
    int moveX;
    int moveY;
    char opp = 'X';
    if(opp == teamPlaying){
        opp = 'O';
    }
    vector<std::pair<std::pair<int,int>,std::pair<int,int>>> posibleMoves;
    vector<std::pair<int,int>> oppPieces;
    vector<std::pair<int,int>> myPieces;
    vector<std::pair<int,int>> openSpots;
    std::pair<int,int> startPos;
    std::pair<int, int> endPos;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(board[i][j] == teamPlaying){
                count++;
                myPieces.push_back({i,j});
            }
            if(board[i][j] == opp){
                oppPieces.push_back({i,j});
            }
            if(board[i][j] == ' '){
                openSpots.push_back({i,j});
            }
        }
    }
    if(count == 3 && !placing){
        canFly = true;
    }
    int moveMyPiece;
    int randomSpot;
    if(myPieces.size() > 0){
        moveMyPiece = rand() % myPieces.size();
    }
    if(openSpots.size() > 0){
        randomSpot = rand() % openSpots.size();
    }
    if(canFly){//for when flying
        board[myPieces[moveMyPiece].first][myPieces[moveMyPiece].second] = ' ';
        moveX = openSpots[randomSpot].first;
        moveY = openSpots[randomSpot].second;
        
    }else if(placing){//for when placing
        moveX = openSpots[randomSpot].first;
        moveY = openSpots[randomSpot].second;
    }else{
        for(int i = 0; i < 5; ++i){
			for(int j = 0; j < 5; ++j){
				if(board[i][j] == teamPlaying){
                    if(i!=4){
                        //cout << "a1" <<endl;
                        if(board[i+1][j] == ' '){
                            startPos = {i,j};
                            endPos = {i+1,j};
                            posibleMoves.push_back({startPos,endPos});
                        }else if(i < 3){
                            //cout << "a2" <<endl;
                            if(board[i+2][j] == ' ' && board[i+1][j] != 'N'){
                                startPos = {i,j};
                                endPos = {i+2,j};
                                posibleMoves.push_back({startPos,endPos});
                            }
                        }
                    }
                    if(i!=0){
                        //cout << "b1" <<endl;
                        if(board[i-1][j] == ' '){
                            startPos = {i,j};
                            endPos = {i-1,j};
                            posibleMoves.push_back({startPos,endPos});
                        }else if(i > 1){
                            //cout << "b2" <<endl;
                            if(board[i-2][j] == ' ' && board[i-1][j] != 'N'){
                                startPos = {i,j};
                                endPos = {i-2,j};
                                posibleMoves.push_back({startPos,endPos});
                            }
                        }
                    }
                    if(j!=4){
                        //cout << "c1" <<endl;
                        if(board[i][j+1] == ' '){
                            startPos = {i,j};
                            endPos = {i,j+1};
                            posibleMoves.push_back({startPos,endPos});
                        }else if(j < 3){
                            //cout << "c2" <<endl;
                            if(board[i][j+2] == ' ' && board[i][j+1] != 'N'){
                                startPos = {i,j};
                                endPos = {i,j+2};
                                posibleMoves.push_back({startPos,endPos});
                            }
                        }
                    }
                    if(j!=0){
                        //cout << "d1" <<endl;
                        if(board[i][j-1] == ' '){
                            startPos = {i,j};
                            endPos = {i,j-1};
                            posibleMoves.push_back({startPos,endPos});
                        }else if(j > 1){
                            //cout << "d2" <<endl;
                            if(board[i][j-2] == ' ' && board[i][j-1] != 'N'){
                                startPos = {i,j};
                                endPos = {i,j-2};
                                posibleMoves.push_back({startPos,endPos});
                            }
                        }
                    }
			    }
            }
		}
        randMove = rand() % posibleMoves.size();
        board[posibleMoves[randMove].first.first][posibleMoves[randMove].first.second] = ' ';
        moveX = posibleMoves[randMove].second.first;
        moveY = posibleMoves[randMove].second.second;
    }
    int takeOpp;
    board[moveX][moveY] = teamPlaying;
    if(checkForThreeBot(moveX, moveY, teamPlaying, board)){
        takeOpp = rand() % oppPieces.size();
        board[oppPieces[takeOpp].first][oppPieces[takeOpp].second] = ' ';
    }
}

void generateChildren(shared_ptr<boardNode> parent){
	vector<vector<char>> parentBoard = parent->data.curBoard;
    if(parent->data.numPlaced < 12){
        parent->data.placing = true;
    }else{
        parent->data.placing = false;
    }
    int count = 0;
	char piece = 'X';
    char oppPiece = 'O';
	if(parent->data.team=='X'){
		piece='O';
        oppPiece = 'X';
	}
    vector<std::pair<int,int>> oppPieces;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(parentBoard[i][j] == parent->data.team){
                count++;
                if(parentBoard[i][j] == oppPiece){
                oppPieces.push_back({i,j});
                }
            }
        }
    }
    parent->data.remaining = count;
    if(parent->data.remaining == 3){
        parent->data.canFly = true;
    }else{
        parent->data.canFly = false;
    }
    int numPlaced = parent->data.numPlaced;
    if(parent->data.placing){
        numPlaced++;
    }
    int remove;
    if(oppPieces.size() > 1){
        remove = rand() % oppPieces.size();
    }
    if(parent->data.placing){
        for (int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(parentBoard[i][j] == ' '){
                    parentBoard[i][j] = piece;
                    if(checkForThreeBot(i,j,piece,parentBoard)){
                        parentBoard[oppPieces[remove].first][oppPieces[remove].second] = ' ';
                    }
                    parent->children.push_back(make_child(parent, nodeData(i,j,piece, numPlaced, parent->data.remaining, parentBoard)));
                    if(checkForThreeBot(i,j,piece,parentBoard)){
                        parentBoard[oppPieces[remove].first][oppPieces[remove].second] = oppPiece;
                    }
                    parentBoard[i][j] = ' ';
                }
            }
        }
    }else if(parent->data.canFly){
        for (int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(parentBoard[i][j] == piece){
                    for(int k = 0; k < 5; k++){
                        for(int l = 0; l < 5; l++){
                            if(parentBoard[k][l] == ' '){
                                parentBoard[k][l] = piece;
                                parentBoard[i][j] = ' ';
                                if(checkForThreeBot(k,l,piece,parentBoard)){
                                    parentBoard[oppPieces[remove].first][oppPieces[remove].second] = ' ';
                                }
                                parent->children.push_back(make_child(parent, nodeData(k,l,piece, numPlaced, parent->data.remaining, parentBoard)));
                                if(checkForThreeBot(i,j,piece,parentBoard)){
                                    parentBoard[oppPieces[remove].first][oppPieces[remove].second] = oppPiece;
                                }
                                parentBoard[i][j] = piece;
                                parentBoard[k][l] = ' ';
                            }
                        }
                    }
                    
                }
            }
        }
    }else{
            for (int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(parentBoard[i][j] == piece){
                        if(i!=4){
                            if(parentBoard[i+1][j] == ' '){
                                parentBoard[i+1][j] = piece;
                                if(checkForThreeBot(i+1,j,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = ' ';
                                }
                                parent->children.push_back(make_child(parent, nodeData(i+1,j,piece, numPlaced, parent->data.remaining, parentBoard)));
                                if(checkForThreeBot(i+1,j,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = oppPiece;
                                }
                                parentBoard[i+1][j] = ' ';
                            }else if(i < 3){
                                if(parentBoard[i+2][j] == ' ' && parentBoard[i+1][j] != 'N'){
                                    parentBoard[i+2][j] = piece;
                                    if(checkForThreeBot(i+2,j,piece,parentBoard)){
                                        parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = ' ';
                                    }
                                    parent->children.push_back(make_child(parent, nodeData(i+2,j,piece, numPlaced, parent->data.remaining, parentBoard)));
                                    if(checkForThreeBot(i+2,j,piece,parentBoard)){
                                        parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = oppPiece;
                                    }
                                    parentBoard[i+2][j] = ' ';
                                }
                            }
                        if(i!=0){
                            if(parentBoard[i-1][j] == ' '){
                                parentBoard[i-1][j] = piece;
                                if(checkForThreeBot(i-1,j,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = ' ';
                                }
                                parent->children.push_back(make_child(parent, nodeData(i-1,j,piece, numPlaced, parent->data.remaining, parentBoard)));
                                if(checkForThreeBot(i-1,j,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = oppPiece;
                                }
                                parentBoard[i-1][j] = ' ';
                            }else if(i > 1){
                                if(parentBoard[i-2][j] == ' ' && parentBoard[i-1][j] != 'N'){
                                    parentBoard[i-2][j] = piece;
                                    if(checkForThreeBot(i-2,j,piece,parentBoard)){
                                        parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = ' ';
                                    }
                                    parent->children.push_back(make_child(parent, nodeData(i-2,j,piece, numPlaced, parent->data.remaining, parentBoard)));
                                    if(checkForThreeBot(i-2,j,piece,parentBoard)){
                                        parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = oppPiece;
                                    }
                                    parentBoard[i-2][j] = ' ';
                                }
                            }
                        }
                        if(j!=4){
                            if(parentBoard[i][j+1] == ' '){
                                parentBoard[i][j+1] = piece;
                                if(checkForThreeBot(i,j+1,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = ' ';
                                }
                                parent->children.push_back(make_child(parent, nodeData(i,j+1,piece, numPlaced, parent->data.remaining, parentBoard)));
                                if(checkForThreeBot(i,j+1,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = oppPiece;
                                }
                                parentBoard[i][j+1] = ' ';
                            }
                        }else if(j < 3){
                            if(parentBoard[i][j+2] == ' ' && parentBoard[i][j+1] != 'N'){
                                parentBoard[i][j+2] = piece;
                                if(checkForThreeBot(i,j+2,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = ' ';
                                }
                                parent->children.push_back(make_child(parent, nodeData(i,j+2,piece, numPlaced, parent->data.remaining, parentBoard)));
                                if(checkForThreeBot(i,j+2,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = oppPiece;
                                }
                                parentBoard[i][j+2] = ' ';
                            }
                        }
                        if(j!=0){
                            if(parentBoard[i][j-1] == ' '){
                                parentBoard[i][j-1] = piece;
                                if(checkForThreeBot(i,j-1,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = ' ';
                                }
                                parent->children.push_back(make_child(parent, nodeData(i,j-1,piece, numPlaced, parent->data.remaining, parentBoard)));
                                if(checkForThreeBot(i,j-1,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = oppPiece;
                                }
                                parentBoard[i][j-1] = ' ';
                            }
                        }else if(j > 1){
                            if(parentBoard[i][j-2] == ' ' && parentBoard[i][j-1] != 'N'){
                                parentBoard[i][j+2] = piece;
                                if(checkForThreeBot(i,j-2,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = ' ';
                                }
                                parent->children.push_back(make_child(parent, nodeData(i,j-2,piece, numPlaced, parent->data.remaining, parentBoard)));
                                if(checkForThreeBot(i,j-2,piece,parentBoard)){
                                    parentBoard[oppPieces[oppPiece].first][oppPieces[oppPiece].second] = oppPiece;
                                }
                                parentBoard[i][j-2] = ' ';
                            }
                        }
                    }
                }
            }
        }
    }
	return;
}
void expandNode(std::shared_ptr<boardNode> rootNode){
	if(rootNode->children.size()==0){
		generateChildren(rootNode);
	}
	return;
}
shared_ptr<boardNode> randomMove(shared_ptr<boardNode> node){
	int i = node->children.size();
	int j = rand() % i;
	return node->children[j];
}
int simRanPlayout(shared_ptr<boardNode> nodeToExplore, char opponent){
	auto tempBoard = nodeToExplore->data.curBoard;
	auto tempPiece = nodeToExplore->data.team;
    auto placing = nodeToExplore->data.placing;
	int state = 0;
	if(tempPiece=='X'){
				tempPiece='O';
			}else{
				tempPiece='X';
			}
    //check if the opponent wins with this board
    if(!nodeToExplore->data.placing){
        if(checkForWinner(tempBoard, tempPiece)){
            state = 1;
        }
    }
	if(state == 1){
		nodeToExplore->data.winScore = 0;
		return 1;
	}
    //switch to tracking bots team
	if(tempPiece=='X'){
				tempPiece='O';
			}else{
				tempPiece='X';
			}
	state = 3;
	int randX = 0;
	int randY = 0;
    int move;
    int numPlaced = nodeToExplore->data.numPlaced;
    //cout << "sim match" << endl;
	while(state == 3){
        //while game not over
        //find a piece that can move
        playTurn(tempBoard,tempPiece,nodeToExplore->data.placing);
        //printBoard(tempBoard);
        //cout << endl;

        if(nodeToExplore->data.placing){
            numPlaced++;
            if(numPlaced >= 12){
                nodeToExplore->data.placing = false;
            }
        }
        if(checkForWinner(tempBoard, tempPiece)){
            state =  1;
        }
        //change teams
        if(tempPiece=='X'){
            tempPiece='O';
        }else{
            tempPiece='X';
        }
    //go again till game over
	}
    
	if(tempPiece == nodeToExplore->data.team){
 		return state;
	}
	return 2;
}
void backpropagation(shared_ptr<boardNode> nodeToExplore, int playoutResult,char botTeam){
	auto tempNode = nodeToExplore;
	while(tempNode){
		++tempNode->data.numberOfVisits;
		if((tempNode->data.team != botTeam) && (playoutResult == 1)){
			++tempNode->data.winScore;
		}
		tempNode = tempNode->parent;
	}
}
shared_ptr<boardNode> getBestChild(shared_ptr<boardNode> rootNode){
	int bestChildIndx = 0;
	double bestScoreVal = -1;
	for(int i = 0; i < rootNode->children.size() -1; i++){
		// cout << (double)rootNode->children[i]->data.winScore << endl;
		if(bestScoreVal < (double)rootNode->children[i]->data.winScore/(double)rootNode->children[i]->data.numberOfVisits){\

			bestScoreVal = (double)rootNode->children[i]->data.winScore/(double)rootNode->children[i]->data.numberOfVisits;
			bestChildIndx = i;
		}
	}
	return rootNode->children[bestChildIndx];
}
std::pair<int,int> nextMove(vector<vector<char>> &match, char &monteBotsTeam, int turnCount, int rem){
	char opponent = 'X';
	if(opponent == monteBotsTeam){
	opponent = 'O';
	}
	shared_ptr<boardNode> rootNode = std::make_shared<boardNode>();
	rootNode->data.curBoard = match;
	rootNode->data.team = monteBotsTeam;
    rootNode->data.remaining = rem;
    if(turnCount < 12){
    rootNode->data.numPlaced = turnCount;
    }else{
        
    rootNode->data.numPlaced = 12;
    }
	generateChildren(rootNode);
	auto startTime = std::chrono::system_clock::now();
	auto endTime = std::chrono::system_clock::now();
	std::chrono::duration<double> runTime = endTime - startTime;
	int numberOfNodes = 0;
	while ( runTime.count() < 5.0){
		shared_ptr<boardNode> promisingNode = selectPromisingNode(rootNode);
		if(promisingNode->children.size()==0){
			expandNode(promisingNode);
		}
		numberOfNodes += rootNode->children.size();
		auto nodeToExplore = promisingNode;
		numberOfNodes += promisingNode->children.size();
		if(nodeToExplore->children.size() > 0){
			nodeToExplore = randomMove(promisingNode);
			promisingNode.reset();
		}
		auto playoutResults = simRanPlayout(nodeToExplore, opponent);
		backpropagation(nodeToExplore, playoutResults, monteBotsTeam);
		numberOfNodes+= nodeToExplore->children.size();
		nodeToExplore->children.clear();
		nodeToExplore.reset();
		endTime = std::chrono::system_clock::now();
		runTime = endTime - startTime;
	}
	auto bestNode = getBestChild(rootNode);
	cout << endl << "MCTS created " << numberOfNodes << " Boards" << endl;
	return {bestNode->data.lastMoveX, bestNode->data.lastMoveY};	
}
int botTurn( std::shared_ptr<Player> curPlayer, vector<vector<char>> &board, int turnCount){
    std::pair<int,int> botsMove = nextMove(board, curPlayer->_piece, turnCount,curPlayer->_remaining);
    board[botsMove.first][botsMove.second] = curPlayer->_piece;
    if(checkForThreeBot(botsMove.first,botsMove.second,curPlayer->_piece,board)){
        return -1;
    }
    return 0;

}

int menu(){
    cout << "1. player vs player\n2. player vs AI\n3. AI vs AI" << endl;
    int userChoice;
    cin >> userChoice;
    return (userChoice);
}

int humanTurn(vector<vector<char>> &board, std::shared_ptr<Player> curPlayer, int turnCount){
    
    int removed = 0;
    char letter;
    int number;
    int letterPos;
    bool successfulMove = false; 
    bool successfullyPlaced = false;
    while(turnCount < 12){
        cout << curPlayer->_piece << "'s turn" << endl;
        turnCount += 1;
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
        if(checkForThree(curPlayer, board)){
            takePiece(curPlayer, board);
            removed = -1;
        }
        return removed;
    }
    int pieceX;
    int pieceY;
    while(!successfulMove && turnCount >= 12){
        cout << curPlayer->_piece << "'s turn" << endl;
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
            curPlayer->_lastMoveX = letterPos;
            curPlayer->_lastMoveY = number;
            movePiece(pieceX, pieceY, letterPos, number, board, curPlayer);
        }else{
            cout << "position invalid, try again"  << endl;
            printBoard(board);
        }
    }
    if(checkForThree(curPlayer, board)){
        takePiece(curPlayer, board);
        removed = -1;
    }
    return removed;
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
    
    int userChoice = menu();
    if(userChoice == 1){
        playerOne->_AIplayer = false;
        playerTwo->_AIplayer = false;
    }
    if(userChoice == 2){
        playerOne->_AIplayer = false;
    }
    int turnCount = 0;
    int letterPos = 0;
    bool gameOver = false;
    int remove;
    while(!gameOver){
        printBoard(board);
        if(playerOne->_AIplayer){
            remove = botTurn(playerOne, board, turnCount);
        }else{
            remove = humanTurn(board, playerOne, turnCount);
        }
        playerTwo->_remaining +=remove;
        remove = 0;
        turnCount++;
        printBoard(board);
        if(playerTwo->_remaining == 2){
            cout << playerOne->_piece <<"'s have won" << endl;
            gameOver = true;
            return;
        }
        if(playerTwo->_AIplayer){
            remove = botTurn(playerTwo, board, turnCount);
        }else{
            humanTurn(board, playerTwo, turnCount);
        }
        turnCount++;
        playerOne->_remaining +=remove;
        remove = 0;
        if(playerOne->_remaining == 2){
            cout << playerTwo->_piece <<"'s have won" << endl;
            gameOver = true;
            return;
        }

    }
}