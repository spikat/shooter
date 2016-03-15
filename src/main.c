#include "shooter.h"

int     main(__attribute__((unused)) int ac, __attribute__((unused)) char** av)
{
    shooter_ctx     ctx;
    unsigned int    framelimit;
    int             ret;
    int             run = 1;
    
    ret = shooter_init(&ctx);
    if (ret) return (ret);

    while (run) {
        framelimit = SDL_GetTicks() + FRAME_TICKS;

        ret = manage_inputs(&ctx);
        if (ret) break;

        ret = draw(&ctx);
        if (ret) break;

        delay(framelimit);
    }
    shooter_cleanup(&ctx);
    return (ret);
}
