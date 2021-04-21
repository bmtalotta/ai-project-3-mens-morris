#include "player.hpp"
// Player definitions
Player::Player(){
    _piece = 'X';
    _placing = true;
    _canFly = false;
    _remaining = 6;
    _AIplayer = true;
    _lastMoveX = 0;
    _lastMoveY = 0;
}

std::shared_ptr<Player> makePlayer()
{
    return std::make_shared<Player>(Player());
}