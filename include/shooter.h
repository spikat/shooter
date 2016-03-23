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
#define PLAYER_BASE_ARMOR       100
#define PLAYER_BASE_SHIELD      0

#define ASTEROID_COL_DAMAGE     45

#define TICK_60_FPS     16 /* 60FPS */

#define MAX_FREE_FOS    64

#define SCORE_CRASH_ASTEROID    (-100)
#define SCORE_SHOOT_ASTEROID    (10)
#define SCORE_X_POS             10
#define SCORE_Y_POS             10

#define SDL_ERROR(x)                                                \
    printf("%s: %s Error: %s\n", __FUNCTION__, x, SDL_GetError());
#define TTF_ERROR(x)                                                \
    printf("%s: %s Error: %s\n", __FUNCTION__, x, TTF_GetError());
#define IMG_ERROR(x)                                                \
    printf("%s: %s Error: %s\n", __FUNCTION__, x, IMG_GetError());
#define MIX_ERROR(x)                                                \
    printf("%s: %s Error: %s\n", __FUNCTION__, x, Mix_GetError());


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

typedef struct      s_asset {
    SDL_Texture*    texture;
    int             sx, sy;
}                   asset;

typedef struct      s_collision_sqr {
    int             x, y;
    int             sx, sy;
}                   collision_sqr;

typedef struct      s_pew {
    asset*          a;
    int             damage;
    int             xspeed;
    int             yspeed;
}                   pew;

typedef struct      s_gun {
    pew             pew;
    /* asset*       gun; */ /* TODO */
    int             firerate;
    int             firecd;
    int             xoff;
    int             yoff;
    struct s_gun*   next;
}                   gun;

typedef struct      s_player {
    /* player position */
    int             x, y;
    /* player ship */
    asset*          ship;
    int             armor;
    int             shield;
    /* collision square */
    collision_sqr   col;
    /* guns */
    gun*            guns;
    int             score;
}                   player;

typedef struct      s_flying_obj {
    /* int             layer; */
    asset*          a;
    int             x, y;
    int             xspeed, yspeed;
    /* collision square */
    int             collisionable;
    collision_sqr   col;
    int             col_damage;
    int             life;
    struct s_flying_obj* next;
}                   flying_obj;

typedef struct      s_shooter_ctx {
    /* SDL context */
    SDL_Window*     screen;
    SDL_Renderer*   renderer;
    asset           score;
    /* frame input */
    input           i;
    /* all sprites assets */
    asset**         a;
    /* fonts assets */
    TTF_Font*       main_font;
    SDL_Color       main_font_color;
    /* player context */
    player          p; /* layer 5 */
    /* flying objects */
    flying_obj*     bg; /* layer 1 */
    int             bg_cpt;
    flying_obj*     pews; /* layer 2 */
    flying_obj*     asteroids; /* layer 3 */
    flying_obj*     enemies; /* layer 4 */
    /* freelist of flying objects */
    flying_obj*     free_fos;
    unsigned int    free_fos_cpt;
}                   shooter_ctx;

/*
  PROTOTYPES
*/

/* init.c */
int     deps_init(shooter_ctx* ctx);
int     deps_cleanup(shooter_ctx* ctx);
/* inputs.c */
int     manage_inputs(shooter_ctx* ctx);
/* draw.c */
int     draw(shooter_ctx* ctx);
/* delay.c */
void    delay(unsigned int frame_limit);
/* spawning.c */
int     spawning(shooter_ctx* ctx);
/* assets.c */
int     load_assets(shooter_ctx* ctx);
int     unload_assets(shooter_ctx* ctx);
/* flying_objs.c */
flying_obj* fo_new(shooter_ctx* ctx);
int     manage_flying_obj(shooter_ctx* ctx);
/* player.c */
int     init_player(shooter_ctx* ctx);
int     change_player_ship(shooter_ctx* ctx, asset* a);
/* collision.c */
void    fill_collision_square(collision_sqr* col, int sx, int sy);
int     boom(collision_sqr* col1, int x1, int y1,
             collision_sqr* col2, int x2, int y2);
/* score.c */
int     init_score(shooter_ctx* ctx);
int     update_score(shooter_ctx* ctx, int score);

#endif /* __SHOOTER_H__ */
