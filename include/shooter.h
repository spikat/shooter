#ifndef __SHOOTER_H__
#define __SHOOTER_H__

/*
  INCLUDES
*/
#include <errno.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>

/*
  DEFINES
*/

#define GAME_TITLE      "spi's shooter"
#define SCREEN_WIDTH    1600
#define SCREEN_HEIGHT   900
/* #define SCREEN_WIDTH    1920 */
/* #define SCREEN_HEIGHT   1080 */

#define PLAYER_PIXELS_PER_MOVE  15

#define TICK_60_FPS     16 /* 60FPS */

#define SDL_ERROR(x)                                                \
    printf("%s: %s Error: %s\n", __FUNCTION__, x, SDL_GetError());

/*
  STRUCTS
*/

typedef struct  s_input {
    int         left;
    int         right;
    int         up;
    int         down;
    int         shoot; // v
    int         bomb; // b
    int         enter; // enter
    int         escape; // escape
}               input;

typedef struct  s_assets {
    SDL_Texture*    background;
    SDL_Texture*    player_ship;
}               assets;

typedef struct      s_player {
    /* player position */
    int             x;
    int             y;
    /* player ship size */
    int             sx;
    int             sy;
}                   player;

typedef struct      s_shooter_ctx {
    SDL_Window*     screen;
    SDL_Renderer*   renderer;
    input           i;
    assets          a;
    player          p;
}                   shooter_ctx;

/*
  PROTOTYPES
*/

/* init.c */
int     deps_init(shooter_ctx* ctx);
int     deps_cleanup(shooter_ctx* ctx);
int     load_assets(shooter_ctx* ctx);
int     unload_assets(shooter_ctx* ctx);
int     init_player(shooter_ctx* ctx);
/* inputs.c */
int     manage_inputs(shooter_ctx* ctx);
/* draw.c */
int     draw(shooter_ctx* ctx);
/* delay.c */
void    delay(unsigned int frame_limit);

#endif /* __SHOOTER_H__ */
