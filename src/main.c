#include "shooter.h"

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

    while (run) {
        framelimit = SDL_GetTicks() + TICK_60_FPS;

        ret = manage_inputs(&ctx);
        if (ret) break;

        if (ctx.i.escape) break;
        
        ret = draw(&ctx);
        if (ret) break;

        delay(framelimit);
    }
    unload_assets(&ctx);
    deps_cleanup(&ctx);
    return (ret);
}
