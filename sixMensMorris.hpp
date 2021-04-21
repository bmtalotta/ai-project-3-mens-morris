#ifndef sixMensMorris_HPP
#define sixMensMorris_HPP
#include <vector>
#include <string>


void printBoard (std::vector<std::vector<std::string>> board);
void sixMensMorris();
class sixMensMorrisTeam{
    int placed, remaining, taken;
    bool jump;
    public:
    sixMensMorrisTeam(){
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
#endif //"!sixMensMorris_HPP"