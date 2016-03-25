#include "shooter.h"
#include "assets.h"

int     draw_image(shooter_ctx* ctx, asset* a, int x, int y)
{
    int         ret;
    SDL_Rect    dest;

    dest.x = x;
    dest.y = y;
    dest.w = a->sx;
    dest.h = a->sy;

    ret = SDL_RenderCopy(ctx->renderer, a->texture, NULL, &dest);
    if (ret) {
        SDL_ERROR("SDL_RenderCopy");
        return (ret);
    }
    return (0);
}

int     draw_background(shooter_ctx* ctx, asset* a, int x, int y)
{
    int         ret;
    SDL_Rect    dest;

    dest.x = x;
    dest.y = y;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;

    ret = SDL_RenderCopy(ctx->renderer, a->texture, NULL, &dest);
    if (ret) {
        SDL_ERROR("SDL_RenderCopy");
        return (ret);
    }
    return (0);
}

int     draw_hits_particles(shooter_ctx* ctx)
{
    int         i;
    hit_parts*  h;

    if (SDL_SetRenderDrawColor(ctx->renderer, HIT_PARTS_COLOR)) {
        SDL_ERROR("SDL_SetRenderDrawColor");
        return (1);
    }
    for (h = ctx->hits; h; h = h->next)
        for (i = 0; i < NB_HIT_PARTS; i++)
            if (h->parts[i].life) {
                if (SDL_RenderDrawPoint(ctx->renderer,
                                        h->parts[i].x, h->parts[i].y)) {
                    SDL_ERROR("SDL_RenderDrawPoint");
                    return (1);
                }
            }
    return (0);
}

int     draw_crashs_particles(shooter_ctx* ctx)
{
    int         i;
    hit_parts*  h;

    if (SDL_SetRenderDrawColor(ctx->renderer, CRASH_PARTS_COLOR)) {
        SDL_ERROR("SDL_SetRenderDrawColor");
        return (1);
    }
    for (h = ctx->crashs; h; h = h->next)
        for (i = 0; i < NB_CRASH_PARTS; i++)
            if (h->parts[i].life) {
                if (SDL_RenderDrawPoint(ctx->renderer,
                                        h->parts[i].x, h->parts[i].y)) {
                    SDL_ERROR("SDL_RenderDrawPoint");
                    return (1);
                }
            }
    return (0);
}

int     draw_player_ship_particles(shooter_ctx* ctx)
{
    int i;

    if (SDL_SetRenderDrawColor(ctx->renderer, PLAYER_SHIP_PARTS_COLOR)) {
        SDL_ERROR("SDL_SetRenderDrawColor");
        return (1);
    }
    for (i = 0; i < NB_SHIP_PARTS; i++)
        if (ctx->p.parts[i].life) {
            if (SDL_RenderDrawPoint(ctx->renderer,
                                    ctx->p.parts[i].x, ctx->p.parts[i].y)) {
                SDL_ERROR("SDL_RenderDrawPoint");
                return (1);
            }
        }
    return (0);
}

#define _DRAW_IMAGE(ctx, a, x, y)             \
    if (draw_image(ctx, a, x, y)) return (1)

#define _DRAW_BACKGROUND(ctx, a, x, y)             \
    if (draw_background(ctx, a, x, y)) return (1)

int     draw(shooter_ctx* ctx)
{
    /* static int  first = 1; */
    flying_obj* fo;

    /* BACKGROUND */
    /* if (first) { */
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);
        /* first = 0; */
    /* } */
    _DRAW_BACKGROUND(ctx, ctx->a[background0], 0, 0);

    /* FLYING OBJS */
    for (fo = ctx->bg; fo; fo = fo->next) {
        _DRAW_IMAGE(ctx, fo->a, fo->x, fo->y);
    }
    for (fo = ctx->asteroids; fo; fo = fo->next) {
        _DRAW_IMAGE(ctx, fo->a, fo->x, fo->y);
    }
    for (fo = ctx->pews; fo; fo = fo->next) {
        _DRAW_IMAGE(ctx, fo->a, fo->x, fo->y);
    }
    for (fo = ctx->enemies; fo; fo = fo->next) {
        _DRAW_IMAGE(ctx, fo->a, fo->x, fo->y);
    }

    /* HITS */
    draw_hits_particles(ctx);

    /* CRASHS */
    draw_crashs_particles(ctx);

    /* player ship */
    draw_player_ship_particles(ctx);
    _DRAW_IMAGE(ctx, ctx->p.ship, ctx->p.x, ctx->p.y);

    /* draw score */
    _DRAW_IMAGE(ctx, &(ctx->score), SCORE_X_POS, SCORE_Y_POS);

    /* draw all */
    SDL_RenderPresent(ctx->renderer);

    /* SDL_Delay(1); /\* ?? TODO *\/ */
    return (0);
}
