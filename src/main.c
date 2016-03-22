#include "shooter.h"

void    usage(void)
{
    puts("commads:\n"
         "    - use arrows to move\n"
         "    - use 'v' to pew pew\n"
         "    - use 'escape' to quit");
}

int     main(__attribute__((unused)) int ac, __attribute__((unused)) char** av)
{
    shooter_ctx     ctx;
    unsigned int    framelimit;
    int             ret;
    int             run = 1;

    ret = deps_init(&ctx);
    if (ret) return (ret);

    ret = load_assets(&ctx);
    if (ret) return (ret);

    ret = init_player(&ctx);
    if (ret) return (ret);

    usage();

    while (run) {
        framelimit = SDL_GetTicks() + TICK_60_FPS;

        ret = manage_inputs(&ctx);
        if (ret) break;

        if (ctx.i.escape) break;

        if (manage_flying_obj(&ctx))
            break;

        ret = spawning(&ctx);
        if (ret) return (ret);

        ret = draw(&ctx);
        if (ret) break;

        delay(framelimit);
    }
    unload_assets(&ctx);
    deps_cleanup(&ctx);
    printf("\nYour score is %i, %s\n", ctx.p.score,
           (ctx.p.score <= 0 ? "big zero.." :
            (ctx.p.score >= 500 ? "star killer!" :
             "rookie.")));
    return (ret);
}
