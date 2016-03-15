#include "shooter.h"
#include "assets.h"

#define ASTEROID_SPAWN_RATE     10
#define ASTEROID_SPAWN_CHANCE   2

#define ASTEROID_MAX_X_VELOCITY 5
#define ASTEROID_MAX_Y_VELOCITY 10

int         spawn_asteroid(shooter_ctx* ctx, int x, int y)
{
    flying_obj* fo = NULL;

    if (ctx->free_fos) {
        fo = ctx->free_fos;
        ctx->free_fos = ctx->free_fos->next;
        ctx->free_fos_cpt--;
    } else {
        fo = malloc(sizeof(*fo));
        if (!fo) return (ENOMEM);
    }

    fo->xspeed = (rand() % ASTEROID_MAX_X_VELOCITY) + 1;
    fo->yspeed = (rand() % ASTEROID_MAX_Y_VELOCITY) + 1;
    if (x > SCREEN_WIDTH / 2)
        fo->xspeed *= -1;
    fo->a = ctx->a[asteroid1a + rand() % 20];
    fo->x = x;
    if (y) fo->y = y;
    else fo->y = fo->a->sy * -1;
    fo->next = ctx->fos;
    ctx->fos = fo;
    return (0);
}

int         spawning(shooter_ctx* ctx)
{
    static int i = 0;
    i++;

    /* ASTEROIDS */
    if (!(i % ASTEROID_SPAWN_RATE) &&
        !(rand() % ASTEROID_SPAWN_CHANCE)) {
        if (spawn_asteroid(ctx, rand() % SCREEN_WIDTH, 0))
            return (1);
    }
    return (0);
}
