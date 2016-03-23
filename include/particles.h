#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#define NB_SHIP_PARTS           100
#define MAX_SHIP_PARTS_X_VEL    0
#define MAX_SHIP_PARTS_Y_VEL    5
#define PLAYER_SHIP_PARTS_COLOR 204, 0, 0, 192
#define SHIP_PART_MAX_LIFE      10
#define SHIP_PART_MIN_LIFE      3

typedef struct  s_particle {
    int         x;
    int         y;
    int         xvel;
    int         yvel;
    int         life;
}               particle;


#define NB_HIT_PARTS        90
#define MAX_HIT_PARTS_VEL   4
#define HIT_PARTS_COLOR     255, 255, 0, 192
#define HIT_FRAMES          20
#define HIT_MIN_LIFE        3
#define HIT_MAX_LIFE        20

typedef struct          s_hit_parts {
    int                 x, y;
    int                 frame;
    particle            parts[NB_HIT_PARTS];
    struct s_hit_parts* next;
}                       hit_parts;

#endif /* __PARTICLES_H__ */
