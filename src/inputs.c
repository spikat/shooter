#include "shooter.h"

extern int run;

int get_input(shooter_ctx* ctx)
{
    SDL_Event event;

    /* bzero(&(ctx->i), sizeof(input)); */
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return (1);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_LEFT:
                ctx->i.left = 1;
                break;

            case SDLK_RIGHT:
                ctx->i.right = 1;
                break;

            case SDLK_DOWN:
                ctx->i.down = 1;
                break;

            case SDLK_UP:
                ctx->i.up = 1;
                break;

            case SDLK_ESCAPE:
                ctx->i.escape = 1;
                break;

            case SDLK_RETURN:
                ctx->i.enter = 1;
                break;

            case SDLK_b:
                ctx->i.bomb = 1;
                break;

            case SDLK_v:
                ctx->i.shoot = 1;
                break;

            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                ctx->i.left = 0;
                break;

            case SDLK_RIGHT:
                ctx->i.right = 0;
                break;

            case SDLK_DOWN:
                ctx->i.down = 0;
                break;

            case SDLK_UP:
                ctx->i.up = 0;
                break;

            case SDLK_ESCAPE:
                ctx->i.escape = 0;
                break;

            case SDLK_RETURN:
                ctx->i.enter = 0;
                break;

            case SDLK_b:
                ctx->i.bomb = 0;
                break;

            case SDLK_v:
                ctx->i.shoot = 0;
                break;

            default:
                break;
            }
            break;
        }
    }
    return (0);
}

int     parse_input(shooter_ctx* ctx)
{
    switch (ctx->gs) {
    case (shooter) :
        if (ctx->i.left == 1)
            ctx->p.x -= PLAYER_PIXELS_PER_MOVE;
        if (ctx->i.right == 1)
            ctx->p.x += PLAYER_PIXELS_PER_MOVE;
        if (ctx->i.up == 1)
            ctx->p.y -= PLAYER_PIXELS_PER_MOVE;
        if (ctx->i.down == 1)
            ctx->p.y += PLAYER_PIXELS_PER_MOVE;

        /* check borders */
        if (ctx->p.x < 0)
            ctx->p.x = 0;
        if ((ctx->p.x + ctx->p.ship->sx) >= SCREEN_WIDTH)
            ctx->p.x = (SCREEN_WIDTH - ctx->p.ship->sx);
        if (ctx->p.y < 0)
            ctx->p.y = 0;
        if (ctx->p.y + ctx->p.ship->sy > SCREEN_HEIGHT)
            ctx->p.y = SCREEN_HEIGHT - ctx->p.ship->sy;

        if (ctx->i.escape) {
            ctx->gs = score_tab;
            ctx->i.escape = 0;
        }
        break ;

    case score_tab:
        if (ctx->i.escape) {
            run = 0;
            ctx->i.escape = 0;
        }
        if (ctx->i.enter) {
            printf("\nYour score is %i, %s\n", ctx->p.score,
                   (ctx->p.score <= 0 ? "big zero.." :
                    (ctx->p.score >= 500 ? "star killer!" :
                     "rookie.")));
            clean_shooter(ctx);
            init_player(ctx);
            ctx->gs = shooter;
            ctx->i.enter = 0;
        }

        break;
    default :
        break ;
    }

    return (0);
}

int     manage_inputs(shooter_ctx* ctx)
{
    int ret;

    ret = get_input(ctx);
    if (ret) return (ret);

    ret = parse_input(ctx);
    if (ret) return (ret);

    return (0);
}
