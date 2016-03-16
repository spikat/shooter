#include "shooter.h"

void        fo_destroy(shooter_ctx* ctx, flying_obj* fo)
{
    /* free / free list */
    if (ctx->free_fos_cpt > MAX_FREE_FOS) {
        free(fo);
    } else {
        fo->next = ctx->free_fos;
        ctx->free_fos = fo;
        ctx->free_fos_cpt++;
    }
}

flying_obj* fo_new(shooter_ctx* ctx)
{
    flying_obj* fo;

    if (ctx->free_fos) {
        fo = ctx->free_fos;
        ctx->free_fos = ctx->free_fos->next;
        ctx->free_fos_cpt--;
    } else {
        fo = malloc(sizeof(*fo));
        if (!fo) return (NULL);
    }
    return (fo);
}

int         is_player_collision(shooter_ctx* ctx, flying_obj* fo)
{
    if (boom(&(ctx->p.col), ctx->p.x, ctx->p.y, &(fo->col), fo->x, fo->y))
        return (1);
    return (0);
}

int         is_asteroid_collision(shooter_ctx* ctx, flying_obj* fo)
{
    flying_obj* a;
    flying_obj* lasta;

    for (lasta = NULL, a = ctx->asteroids; a; lasta = a, a = a->next)
        if (boom(&(fo->col), fo->x, fo->y, &(a->col), a->x, a->y)) {
            a->life -= fo->col_damage;
            if (a->life <= 0) { /* asteroid destroyed */
                if (lasta) lasta->next = a->next;
                else ctx->asteroids = a->next;
                fo_destroy(ctx, a);
            }
            return (1);
        }
    return (0);
}

int         manage_flying_bg(shooter_ctx* ctx)
{
    /* TODO */
    return (0);
}

int         manage_flying_asteroids(shooter_ctx* ctx)
{
    flying_obj* fo;
    flying_obj* last = NULL;

    for (fo = ctx->asteroids; fo; ) {
        fo->x += fo->xspeed;
        fo->y += fo->yspeed;
        if (fo->x > SCREEN_WIDTH ||
            fo->y > SCREEN_HEIGHT ||
            fo->x + fo->a->sx < 0) {
            /* detach & destroy */
            if (last) last->next = fo->next;
            else ctx->asteroids = fo->next;
            fo_destroy(ctx, fo);
            /* next elem */
            if (last) fo = last->next;
            else fo = ctx->asteroids;
        } else if (is_player_collision(ctx, fo)) {
            if (ctx->p.shield) {
                fo->col_damage -= ctx->p.shield;
                ctx->p.shield = 0;
            }
            ctx->p.armor -= fo->col_damage;
            if (ctx->p.armor <= 0) {
                puts("\nBoom. You are dead.");
                return (1);
            }
            /* detach & destroy */
            if (last) last->next = fo->next;
            else ctx->asteroids = fo->next;
            fo_destroy(ctx, fo);
            /* next elem */
            if (last) fo = last->next;
            else fo = ctx->asteroids;
        } else {
            /* next elem */
            last = fo;
            fo = fo->next;
        }
    }
    return (0);
}

int         manage_flying_enemies(shooter_ctx* ctx)
{
    /* TODO */
    return (0);
}

int         manage_flying_pews(shooter_ctx* ctx)
{
    flying_obj* fo;
    flying_obj* last = NULL;

    for (fo = ctx->pews; fo; ) {
        fo->x += fo->xspeed;
        fo->y += fo->yspeed;
        if (fo->x > SCREEN_WIDTH ||
            fo->y > SCREEN_HEIGHT ||
            fo->x + fo->a->sx < 0) {
            /* detach & destroy */
            if (last) last->next = fo->next;
            else ctx->pews = fo->next;
            fo_destroy(ctx, fo);
            /* next elem */
            if (last) fo = last->next;
            else fo = ctx->pews;
        } else if (is_asteroid_collision(ctx, fo)) {
            /* detach & destroy */
            if (last) last->next = fo->next;
            else ctx->pews = fo->next;
            fo_destroy(ctx, fo);
            /* next elem */
            if (last) fo = last->next;
            else fo = ctx->pews;
        } else {
            /* next elem */
            last = fo;
            fo = fo->next;
        }
    }
    return (0);
}

int         manage_flying_obj(shooter_ctx* ctx)
{
    if (manage_flying_bg(ctx)) return (1);
    if (manage_flying_pews(ctx)) return (1);
    if (manage_flying_asteroids(ctx)) return (1);
    if (manage_flying_enemies(ctx)) return (1);
    return (0);
}
