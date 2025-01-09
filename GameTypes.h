#ifndef GAME_TYPES_H
#define GAME_TYPES_H

enum class ShootResult {
    HIT,
    MISS,
    SUNK,
    INVALID
};

struct AttackResult {
    ShootResult result;
    int x;
    int y;
};

#endif 