#include "shooter.h"

int     draw_image(shooter_ctx* ctx, SDL_Texture* t, int x, int y)
{
    int         ret;
    SDL_Rect    dest;

    dest.x = x;
    dest.y = y;

    ret = SDL_QueryTexture(t, NULL, NULL, &dest.w, &dest.h);
    if (ret) {
        SDL_ERROR("SDL_QueryTexture");
        return (ret);
    }
    
    ret = SDL_RenderCopy(ctx->renderer, t, NULL, &dest);
    if (ret) {
        SDL_ERROR("SDL_RenderCopy");
        return (ret);
    }
    return (0);
}

int     draw_background(shooter_ctx* ctx, SDL_Texture* t, int x, int y)
{
    int         ret;
    SDL_Rect    dest;

    dest.x = x;
    dest.y = y;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;
    
    ret = SDL_RenderCopy(ctx->renderer, t, NULL, &dest);
    if (ret) {
        SDL_ERROR("SDL_RenderCopy");
        return (ret);
    }
    return (0);
}

#define _DRAW_IMAGE(ctx, texture, x, y)             \
    if (draw_image(ctx, texture, x, y)) return (1)

#define _DRAW_BACKGROUND(ctx, texture, x, y)             \
    if (draw_background(ctx, texture, x, y)) return (1)

int     draw(shooter_ctx* ctx)
{
    static int first = 1;

    if (first) {
        SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
        SDL_RenderClear(ctx->renderer);
        /* first = 0; */
    }

    _DRAW_BACKGROUND(ctx, ctx->a.background, 0, 0);
    _DRAW_IMAGE(ctx, ctx->a.player_ship, ctx->p.x, ctx->p.y);

	SDL_RenderPresent(ctx->renderer);

    /* SDL_Delay(1); /\* ?? TODO *\/ */
    return (0);
}
