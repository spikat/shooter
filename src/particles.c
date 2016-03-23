#include <math.h>

#include "shooter.h"
#include "particles.h"


int         manage_player_ship_particles(shooter_ctx* ctx)
{
    int     i;

    for (i = 0; i < NB_SHIP_PARTS; i++) {
        if (ctx->p.parts[i].life == 0) {
            ctx->p.parts[i].x = ctx->p.x + (rand() % ctx->p.ship->sx / 2) + ctx->p.ship->sx / 4;
            ctx->p.parts[i].y = ctx->p.y + ctx->p.ship->sy;
            ctx->p.parts[i].xvel = (MAX_SHIP_PARTS_X_VEL ? rand() % MAX_SHIP_PARTS_X_VEL + 1 : 0);
            ctx->p.parts[i].yvel = rand() % MAX_SHIP_PARTS_Y_VEL + 1;
            ctx->p.parts[i].life = rand() % (SHIP_PART_MAX_LIFE - SHIP_PART_MIN_LIFE) + SHIP_PART_MIN_LIFE;
        } else {
            ctx->p.parts[i].life--;
            ctx->p.parts[i].x += ctx->p.parts[i].xvel;
            ctx->p.parts[i].y += ctx->p.parts[i].yvel;
        }
    }
    return (0);
}

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
void        fill_hit_part(particle* p, int x, int y)
{
    double  angle = rand() % 360;
    int     velocity = rand() % MAX_HIT_PARTS_VEL + 1;

    p->x = x;
    p->y = y;
    p->xvel = cos(angle) * velocity;
    p->yvel = sin(angle) * velocity;
    if (rand() % 2) p->xvel *= -1;
    if (rand() % 2) p->yvel *= -1;
    p->life = rand() % (HIT_MAX_LIFE - HIT_MIN_LIFE) + HIT_MIN_LIFE;
}

int         manage_hits_particles(shooter_ctx* ctx)
{
    int         i;
    hit_parts*  h;
    hit_parts*  last;

    for (last = NULL, h = ctx->hits; h; ) {
        h->frame--;
        if (!(h->frame)) {
            if (last) {
                last->next = h->next;
                h->next = ctx->hits_free;
                ctx->hits_free = h;
                h = last->next;
            } else {
                ctx->hits = h->next;
                h->next = ctx->hits_free;
                ctx->hits_free = h;
                h = ctx->hits;
            }
            continue;
        }
        for (i = 0; i < NB_HIT_PARTS; i++) {
            if (h->parts[i].life != 0) {
                h->parts[i].life--;
                h->parts[i].x += h->parts[i].xvel;
                h->parts[i].y += h->parts[i].yvel;
            }
        }
        last = h;
        h = h->next;
    }
    return (0);
}

int         add_hit(shooter_ctx* ctx, int x, int y)
{
    int         i;
    hit_parts*  h;

    if (ctx->hits_free) {
        h = ctx->hits_free;
        ctx->hits_free = ctx->hits_free->next;
    } else {
        h = malloc(sizeof(*h));
        if (!h) return (ENOMEM);
    }

    for (i = 0; i < NB_HIT_PARTS; i++) {
        fill_hit_part(&(h->parts[i]), x, y);
    }
    h->frame = HIT_FRAMES;
    h->x = x;
    h->y = y;
    h->next = ctx->hits;
    ctx->hits = h;
    return (0);
}

int         manage_particles(shooter_ctx* ctx)
{
    if (manage_hits_particles(ctx) ||
        manage_player_ship_particles(ctx))
        return (1);
    return (0);
}
