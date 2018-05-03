#include "shooter.h"

#define GUN_POS_FACTOR (0.20)

enum gun_pos {
    top = 0,
    left,
    right
};

enum pew_id {
    pew1_vertical = 0,
    pew2_vertical,
    pew3_vertical,
    pew_last
};

enum        gun_id {
    gun1 = 0,
    gun2,
    gun3,
    gun_last
};

int     fill_gun(shooter_ctx* ctx, gun* g, enum gun_id id);
