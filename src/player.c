#include "shooter.h"
#include "assets.h"

int     change_player_ship(shooter_ctx* ctx, asset* a)
{
    ctx->p.ship = a;
    fill_collision_square(&(ctx->p.col), a->sx, a->sy);    
    return (0);
}

int     init_player(shooter_ctx* ctx)
{
    if (!ctx) return (EINVAL);
    ctx->p.x = SCREEN_WIDTH / 2;
    ctx->p.y = SCREEN_HEIGHT * 0.9;
    change_player_ship(ctx, ctx->a[ship1]);
    ctx->p.armor = PLAYER_BASE_ARMOR;
    ctx->p.shield = PLAYER_BASE_SHIELD;
    return (0);
}
