#include "shooter.h"
#include "assets.h"
#include "guns.h"

void      player_remove_guns(shooter_ctx* ctx)
{
    gun* g;

    for (g = ctx->p.guns; g; g = ctx->p.guns) {
        ctx->p.guns = g->next;
        free(g);
    }
}

int     change_player_ship(shooter_ctx* ctx, asset* a)
{
    ctx->p.ship = a;
    fill_collision_square(&(ctx->p.col), a->sx, a->sy);
    player_remove_guns(ctx);
    return (0);
}

int     player_ship_add_gun(shooter_ctx* ctx, enum gun_pos pos, enum gun_id id)
{
    gun*    g;

    g = malloc(sizeof(*g));
    if (!g) return (ENOMEM);
    fill_gun(ctx, g, id);
    switch (pos) {
    case (top):
        g->xoff = ctx->p.ship->sx / 2;
        g->yoff = ctx->p.ship->sy * GUN_POS_FACTOR;
        break;
    case (left):
        g->xoff = ctx->p.ship->sx * GUN_POS_FACTOR;
        g->yoff = ctx->p.ship->sy / 2;
        break;
    case (right):
        g->xoff = ctx->p.ship->sx * (1 - GUN_POS_FACTOR);
        g->yoff = ctx->p.ship->sy / 2;
        break;
    default:
        return (EINVAL);
    }
    g->next = ctx->p.guns;
    ctx->p.guns = g;
    return (0);
}

int     init_player(shooter_ctx* ctx)
{
    if (!ctx) return (EINVAL);
    ctx->p.x = SCREEN_WIDTH / 2;
    ctx->p.y = SCREEN_HEIGHT * 0.9;
    ctx->p.armor = PLAYER_BASE_ARMOR;
    ctx->p.shield = PLAYER_BASE_SHIELD;
    ctx->p.score = 0;
    change_player_ship(ctx, ctx->a[ship1]);
    if (player_ship_add_gun(ctx, right, gun1)) return (1);
    if (player_ship_add_gun(ctx, left, gun1)) return (1);
    return (0);
}
