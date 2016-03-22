#include <stdio.h>

#include "shooter.h"

#define SCORE_SZ    64

int     update_score_texture(shooter_ctx* ctx)
{
    SDL_Surface*    sur;
    char            s[SCORE_SZ];

    snprintf(s, SCORE_SZ, "score: %i", ctx->p.score);
    sur = TTF_RenderText_Blended(ctx->main_font, s, ctx->main_font_color);
    if (!sur) {
        TTF_ERROR("TTF_RenderText_Blended");
        return (1);
    }
    if (ctx->score.texture) SDL_DestroyTexture(ctx->score.texture);
    ctx->score.texture = SDL_CreateTextureFromSurface(ctx->renderer, sur);
    if (!(ctx->score.texture)) {
        SDL_FreeSurface(sur);
        SDL_ERROR("SDL_CreateTextureFromSurface");
        return (1);
    }
    ctx->score.sx = sur->w;
    ctx->score.sy = sur->h;
    SDL_FreeSurface(sur);
    return (0);
}

int     update_score(shooter_ctx* ctx, int score)
{
    ctx->p.score += score;
    return (update_score_texture(ctx));
}

int     init_score(shooter_ctx* ctx)
{
    ctx->p.score = 0;
    return (update_score_texture(ctx));
}
