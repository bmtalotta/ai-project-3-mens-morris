#include "player.hpp"
// Player definitions
Player::Player(){
    _piece = 'X';
    _placing = true;
    _canFly = false;
    _remaining = 6;
    _AIplayer = true;
}