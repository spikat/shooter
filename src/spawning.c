#include "shooter.h"

#define ASTEROID_SPAWN_RATE     100
#define ASTEROID_SPAWN_CHANCE   3


int         spawn_asteroid(shooter_ctx* ctx, int x, int y)
{
    /* TODO */
    return (0);
}

int         spawning(shooter_ctx* ctx)
{
    static int i = 0;
    i++;

    /* ASTEROIDS */
    if (!(i % ASTEROID_SPAWN_RATE) &&
        !(rand() % ASTEROID_SPAWN_CHANCE)) {
        if (spawn_asteroid(ctx, rand() % SCREEN_WIDTH, rand() %SCREEN_HEIGHT))
            return (1);
    }
    return (0);
}
