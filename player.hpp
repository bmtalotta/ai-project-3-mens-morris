#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <memory>
#include <iostream>

class Player
{
protected:

public:
    char _piece;
    bool _placing;
    bool _canFly;
    int _remaining; 
    bool _AIplayer;
    int _lastMoveX;
    int _lastMoveY;
    Player();
};

std::shared_ptr<Player> makePlayer();

#endif