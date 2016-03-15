#include "shooter.h"

#define COLLISION_FACTOR    (0.25) /* -> 25% cropped all around, collision = 50% */

void    fill_collision_square(collision_sqr* col, int sx, int sy)
{
    col->x = sx * COLLISION_FACTOR;
    col->y = sy * COLLISION_FACTOR;
    col->sx = sx * (1 - (COLLISION_FACTOR * 2));
    col->sy = sy * (1 - (COLLISION_FACTOR * 2));
    return ;
}

int     boom(collision_sqr* col1, int x1, int y1,
             collision_sqr* col2, int x2, int y2)
{
    /* for each corner, check if it is in the area of the second square */

    /* north west */
    if ((x1 + col1->x >= x2 + col2->x &&
         x1 + col1->x <= x2 + col2->x + col2->sx &&
         y1 + col1->y >= y2 + col2->y &&
         y1 + col1->y <= y2 + col2->y + col2->sy) ||
        /* north east */
        (x1 + col1->x + col1->sx >= x2 + col2->x &&
         x1 + col1->x + col1->sx <= x2 + col2->x + col2->sx &&
         y1 + col1->y >= y2 + col2->y &&
         y1 + col1->y <= y2 + col2->y + col2->sy) ||
        /* south west */
        (x1 + col1->x >= x2 + col2->x &&
         x1 + col1->x <= x2 + col2->x + col2->sx &&
         y1 + col1->y + col1->sy >= y2 + col2->y &&
         y1 + col1->y + col1->sy <= y2 + col2->y + col2->sy) ||
        /* south east */
        (x1 + col1->x + col1->sx >= x2 + col2->x &&
         x1 + col1->x + col1->sx <= x2 + col2->x + col2->sx &&
         y1 + col1->y + col1->sy >= y2 + col2->y &&
         y1 + col1->y + col1->sy <= y2 + col2->y + col2->sy))
        return (1);
    return (0);
}

