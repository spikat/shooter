#include "shooter.h"

int         manage_flying_obj(shooter_ctx* ctx)
{
    flying_obj* fo;
    flying_obj* last = NULL;

    for (fo = ctx->fos; fo; ) {
        fo->x += fo->xspeed;
        fo->y += fo->yspeed;
        if (fo->x > SCREEN_WIDTH ||
            fo->y > SCREEN_HEIGHT ||
            fo->x + fo->sx < 0) {
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
            /* next elem */
            if (last) fo = last->next;
            else fo = ctx->fos;
        }
        else {
            /* next elem */
            last = fo;
            fo = fo->next;
        }
    }
    return (0);
}
