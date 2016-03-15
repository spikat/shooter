#include "shooter.h"
#include "assets.h"

struct texture_asset asset_table [] = {
    /* BG: 1 */
    { background0, A_BACKGROUND },

    /* ships: 7 */
    { ship1, A_SHIP1 },
    { ship2, A_SHIP2 },
    { ship3, A_SHIP3 },
    { ship4, A_SHIP4 },
    { ship5, A_SHIP5 },
    { ship6, A_SHIP6 },
    { ship7, A_SHIP7 },

    /* asteroids: 20 */
    { asteroid1a, A_ASTEROID1a },
    { asteroid1b, A_ASTEROID1b },
    { asteroid2a, A_ASTEROID2a },
    { asteroid2b, A_ASTEROID2b },
    { asteroid3a, A_ASTEROID3a },
    { asteroid3b, A_ASTEROID3b },
    { asteroid4a, A_ASTEROID4a },
    { asteroid4b, A_ASTEROID4b },
    { asteroid5a, A_ASTEROID5a },
    { asteroid5b, A_ASTEROID5b },
    { asteroid6a, A_ASTEROID6a },
    { asteroid6b, A_ASTEROID6b },
    { asteroid7a, A_ASTEROID7a },
    { asteroid7b, A_ASTEROID7b },
    { asteroid8a, A_ASTEROID8a },
    { asteroid8b, A_ASTEROID8b },
    { asteroid9a, A_ASTEROID9a },
    { asteroid9b, A_ASTEROID9b },
    { asteroid10a, A_ASTEROID10a },
    { asteroid10b, A_ASTEROID10b },

    /* celestial bodies: 16 */
    { fog1, A_FOG1 },
    { fog2, A_FOG2 },
    { fog3, A_FOG3 },
    { fog4, A_FOG4 },
    { fog5, A_FOG5 },
    { fog6, A_FOG6 },
    { fog7, A_FOG7 },
    { planet1, A_PLANET1 },
    { planet2, A_PLANET2 },
    { planet3, A_PLANET3 },
    { planet4, A_PLANET4 },
    { planet5, A_PLANET5 },
    { planet6, A_PLANET6 },
    { planet7, A_PLANET7 },
    { star1, A_STAR1 },
    { star2, A_STAR2 },

    { last, NULL }
};


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
    unsigned int i;

    if (!ctx) return (EINVAL);
    ctx->a = malloc(sizeof(SDL_Texture*) * (enum asset)(last));
    if (!(ctx->a)) return (ENOMEM);
    for (i = 0; i < (enum asset)(last); i++)
        _LOAD_IMAGE(ctx, asset_table[i].path, &(ctx->a[i]));
    return (0);
}

int     unload_assets(shooter_ctx* ctx)
{
    unsigned int i;

    if (!ctx) return (EINVAL);
    for (i = 0; i < (enum asset)last; i++)
        SDL_DestroyTexture(ctx->a[i]);
    return (0);
}