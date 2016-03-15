#include "shooter.h"
#include "assets.h"

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

int     load_image(shooter_ctx* ctx, char *name, SDL_Texture** texture)
{
    SDL_Surface *loadedImage = NULL;

    *texture = NULL;
    loadedImage = IMG_Load(name);
    if (loadedImage != NULL) {
        *texture = SDL_CreateTextureFromSurface(ctx->renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else {
        SDL_ERROR("IMG_Load");
        return (1);
    }

    if (!(*texture)) {
        SDL_ERROR("SDL_CreateTextureFromSurface");
        return (1);
    }
    return (0);
 
}

#define _LOAD_IMAGE(ctx, path, pobj)                     \
    if (load_image(ctx, path, pobj)) return (1)

int     load_assets(shooter_ctx* ctx)
{
    if (!ctx) return (EINVAL);

    /* backgrounds */
    _LOAD_IMAGE(ctx, A_BACKGROUND, &(ctx->a.background));

    /* player ship */
    _LOAD_IMAGE(ctx, A_SHIP1, &(ctx->a.player_ship));
    if (SDL_QueryTexture(ctx->a.player_ship, NULL, NULL, &(ctx->p.sx), &(ctx->p.sy))) {
        SDL_ERROR("SDL_QueryTexture");
        return (1);
    }
    /* printf("sx = %i sy = %i\n", ctx->p.sx, ctx->p.sy); */
    return (0);
}

int     unload_assets(shooter_ctx* ctx)
{
    if (!ctx) return (EINVAL);
    SDL_DestroyTexture(ctx->a.background);
    SDL_DestroyTexture(ctx->a.player_ship);
    return (0);
}

int     init_player(shooter_ctx* ctx)
{
    if (!ctx) return (EINVAL);
    ctx->p.x = SCREEN_WIDTH / 2;
    ctx->p.y = SCREEN_HEIGHT * 0.9;
    return (0);
}
