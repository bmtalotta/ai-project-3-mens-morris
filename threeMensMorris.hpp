#ifndef threeMensMorris_HPP
#define threeMensMorris_HPP
#include <vector>
#include <string>

void printBoard (std::vector<std::vector<std::string>> board);
void threeMensMorris(int numberOfRealPlayers);
class ThreeMensMorrisTeam{
    int placed, remaining, taken;
    bool jump;
    public:
    ThreeMensMorrisTeam(){
        placed = 0;
        remaining = 6;
        taken = 0;
        jump = false;
    }
    void jumpCheck(){
        if(remaining == 3){
            jump = true;
        }
    }
    bool checkIfOut(){
        if(remaining == 2){
            return true;
        }
        return false;
    }

};
#endif //"!threeMensMorris_HPP"