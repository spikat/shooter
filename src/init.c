#include <stdlib.h>
#include <time.h>

#include "shooter.h"

int     deps_init(shooter_ctx* ctx)
{
    if (!ctx) return (EINVAL);
    bzero(ctx, sizeof(*ctx));

    /* SDL INIT */
    if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_EVENTS)) {
        SDL_ERROR("SDL_Init");
        return (1);
    }
    ctx->screen = SDL_CreateWindow(GAME_TITLE,
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);
    if (!(ctx->screen)) {
        SDL_ERROR("SDL_CreateWindow");
        return (1);
    }
    ctx->renderer = SDL_CreateRenderer(ctx->screen, -1,
                                       SDL_RENDERER_PRESENTVSYNC);
    if (!(ctx->renderer)) {
        SDL_ERROR("SDL_CreateRenderer");
        return (1);
    }
    SDL_ShowCursor(SDL_DISABLE);

    /* SDL_IMG Init */
    if ((IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF)) !=
                 (IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF)) {
        SDL_ERROR("IMG_Init");
        return (1);
    }

    /* SDL_TTF */
    if (TTF_Init()) {
        SDL_ERROR("TTF_Init");
        return (1);
    }

    /* SDL mixer */
    if ((Mix_Init(MIX_INIT_FLAC|MIX_INIT_MP3|MIX_INIT_OGG)) !=
                 (MIX_INIT_FLAC|MIX_INIT_MP3|MIX_INIT_OGG)) {
        SDL_ERROR("Mix_Init");
        return (1);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        SDL_ERROR("Mix_OpenAudio");
        return (1);
    }
    Mix_AllocateChannels(32);
    srand(time(NULL));
    return (0);
}

int     deps_cleanup(shooter_ctx* ctx)
{
    if (!ctx) return (EINVAL);

    /* SDL cleanup */
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->screen);

    /* SDL_Image cleanup */
    IMG_Quit();

    /* SDL_TTF cleanup */
    TTF_Quit();

    /* SDL mixer */
    Mix_Quit();

    SDL_Quit();
    return (0);
}
