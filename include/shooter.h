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

/*
  DEFINES
*/

#define GAME_TITLE      "spi's shooter"
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480

#define FRAME_TICKS     16

#define SDL_ERROR(x)                                \
    printf("%s Error: %s\n", x, SDL_GetError());

/*
  STRUCTS
*/

typedef struct  s_input {
    int         left;
    int         right;
    int         up;
    int         down;
    int         shoot;
    int         bomb;
    int         enter;
    int         pause;    
}               input;

typedef struct      s_shooter_ctx {
    SDL_Window*     screen;
    SDL_Renderer*   renderer;
}                   shooter_ctx;

/*
  PROTOTYPES
*/

int     shooter_init(shooter_ctx* ctx);
int     shooter_cleanup(shooter_ctx* ctx);
int     manage_inputs(shooter_ctx* ctx);
int     draw(shooter_ctx* ctx);
int     delay(unsigned int frames);

#endif /* __SHOOTER_H__ */
