#include "shooter.h"
#include "assets.h"
#include "guns.h"

struct      s_pew_def {
    enum pew_id     id;
    enum asset      a;
    int             damage;
    int             xspeed;
    int             yspeed;
}           base_pew;

struct s_pew_def         pew_tab[] = {
    { pew1_vertical, pew1, 5,  0, -20 },
    { pew2_vertical, pew2, 20, 0, -20 },
    { pew3_vertical, pew3, 80, 0, -20 },
    { pew_last, last, 0, 0, 0 }
};

struct          s_gun_def {
    enum gun_id id;
    enum pew_id pew;
    int         firerate;
    /* asset*   a; */
}               gun_def;

struct s_gun_def         gun_tab[] = {
    { gun1, pew1_vertical, 10 },
    { gun2, pew2_vertical, 30 },
    { gun3, pew3_vertical, 60 },
    { gun_last, pew_last, 0 }
};

int _get_pew_index(enum pew_id id)
{
    int     i;
    for (i = 0; pew_tab[i].id != pew_last; i++)
        if (pew_tab[i].id == id)
            return (i);
    return (-1);
}

int _get_gun_index(enum gun_id id)
{
    int     i;
    for (i = 0; gun_tab[i].id != gun_last; i++)
        if (gun_tab[i].id == id)
            return (i);
    return (-1);
}

int         fill_gun(shooter_ctx* ctx, gun* g, enum gun_id id)
{
    int     gid, pid;

    if (!ctx || !g || id < 0 || id >= gun_last)
        return (EINVAL);

    gid = _get_gun_index(id);
    if (gid < 0) {
        fprintf(stderr, "%s Error: failed to get gunid %i.\n", __FUNCTION__, id);
        return (-1);
    }

    pid = _get_pew_index(gun_tab[gid].pew);
    if (pid < 0) {
        fprintf(stderr, "%s Error: failed to get pewid %i.\n", __FUNCTION__, pid);
        return (-1);
    }

    g->pew.a = ctx->a[pew_tab[pid].a];
    g->pew.damage = pew_tab[pid].damage;
    g->pew.xspeed = pew_tab[pid].xspeed;
    g->pew.yspeed = pew_tab[pid].yspeed;
    g->firerate = gun_tab[gid].firerate;
    g->firecd = 0;
    return (0);;
}
