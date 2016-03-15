#include "shooter.h"

int         is_player_collision(shooter_ctx* ctx, flying_obj* fo)
{
    if (boom(&(ctx->p.col), ctx->p.x, ctx->p.y, &(fo->col), fo->x, fo->y))
        return (1);
    return (0);
}

void        fo_destroy(shooter_ctx* ctx, flying_obj* fo, flying_obj* last)
{
    /* detach */
    if (last) last->next = fo->next;
    else ctx->fos = fo->next;

    /* free / free list */
    if (ctx->free_fos_cpt > MAX_FREE_FOS) {
        free(fo);
    } else {
        fo->next = ctx->free_fos;
        ctx->free_fos = fo;
        ctx->free_fos_cpt++;
    }
}

int         manage_flying_obj(shooter_ctx* ctx)
{
    flying_obj* fo;
    flying_obj* last = NULL;

    for (fo = ctx->fos; fo; ) {
        fo->x += fo->xspeed;
        fo->y += fo->yspeed;
        if (fo->x > SCREEN_WIDTH ||
            fo->y > SCREEN_HEIGHT ||
            fo->x + fo->a->sx < 0) {

            fo_destroy(ctx, fo, last);
            /* next elem */
            if (last) fo = last->next;
            else fo = ctx->fos;
        } else if (is_player_collision(ctx, fo)) {
            puts("player collision !");
            if (ctx->p.shield) {
                fo->col_damage -= ctx->p.shield;
                ctx->p.shield = 0;
            }
            ctx->p.armor -= fo->col_damage;
            if (ctx->p.armor <= 0) return (1);

            fo_destroy(ctx, fo, last);
            /* next elem */
            if (last) fo = last->next;
            else fo = ctx->fos;
        } else {
            /* next elem */
            last = fo;
            fo = fo->next;
        }
    }
    return (0);
}
