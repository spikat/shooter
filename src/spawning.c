#include "shooter.h"
#include "assets.h"

#define ASTEROID_SPAWN_RATE     10
#define ASTEROID_SPAWN_CHANCE   2

#define ASTEROID_MAX_X_VELOCITY 5
#define ASTEROID_MAX_Y_VELOCITY 10

#define ASTEROID_LIFE           10

int         spawn_asteroid(shooter_ctx* ctx, int x, int y)
{
    flying_obj* fo = fo_new(ctx);

    fo->xspeed = (rand() % ASTEROID_MAX_X_VELOCITY) + 1;
    fo->yspeed = (rand() % ASTEROID_MAX_Y_VELOCITY) + 1;
    if (x > SCREEN_WIDTH / 2)
        fo->xspeed *= -1;
    fo->a = ctx->a[asteroid1a + rand() % 20];
    fo->x = x;
    if (y) fo->y = y;
    else fo->y = fo->a->sy * -1;

    /* collission init */
    fo->collisionable = 1;
    fill_collision_square(&(fo->col), fo->a->sx, fo->a->sy);
    fo->col_damage = ASTEROID_COL_DAMAGE;
    fo->life = ASTEROID_LIFE;

    fo->next = ctx->asteroids;
    ctx->asteroids = fo;
    return (0);
}

int         spawn_pew(shooter_ctx* ctx, int x, int y, gun* g)
{
    flying_obj* fo = fo_new(ctx);

    fo->a = g->pew.a;
    fo->x = x + g->xoff - (g->pew.a->sx / 2);
    if (g->pew.yspeed > 0) { /* like enemy pew */
        fo->y = y + g->yoff;
    } else { /* like player pew */
        fo->y = y + g->yoff - g->pew.a->sy;
    }
    fo->xspeed = g->pew.xspeed;
    fo->yspeed = g->pew.yspeed;
    fo->collisionable = 1;
    fill_collision_square(&(fo->col), fo->a->sx, fo->a->sy);
    fo->col_damage = g->pew.damage;
    fo->life = 0; /* may change later? */

    fo->next = ctx->pews;
    ctx->pews = fo;
    return (0);
}

int         spawning(shooter_ctx* ctx)
{
    gun*    g;
    static int i = 0;
    i++;

    /* ASTEROIDS */
    if (!(i % ASTEROID_SPAWN_RATE) &&
        !(rand() % ASTEROID_SPAWN_CHANCE)) {
        if (spawn_asteroid(ctx, rand() % SCREEN_WIDTH, 0))
            return (1);
    }
    /* PEW PEW */
    /* player ship */
    for (g = ctx->p.guns; g; g = g->next) {
        if (g->firecd) g->firecd--;
        else if (ctx->i.shoot) {
            g->firecd = g->firerate;
            if (spawn_pew(ctx, ctx->p.x, ctx->p.y, g))
                return (1);
        }
    }
    return (0);
}
