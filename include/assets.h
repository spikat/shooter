#ifndef __ASSETS_H__
#define __ASSETS_H__

/* BACKGROUND */
#define A_BACKGROUND    "assets/sprites/backgrounds/stars.png"

/* CELESTIAL BODIES */
#define A_FOG1          "assets/sprites/celestial_bodies/fog1.png"
#define A_FOG2          "assets/sprites/celestial_bodies/fog2.png"
#define A_FOG3          "assets/sprites/celestial_bodies/fog3.png"
#define A_FOG4          "assets/sprites/celestial_bodies/fog4.png"
#define A_FOG5          "assets/sprites/celestial_bodies/fog5.png"
#define A_FOG6          "assets/sprites/celestial_bodies/fog6.png"
#define A_FOG7          "assets/sprites/celestial_bodies/fog7.png"
#define A_PLANET1       "assets/sprites/celestial_bodies/planet1.png"
#define A_PLANET2       "assets/sprites/celestial_bodies/planet2.png"
#define A_PLANET3       "assets/sprites/celestial_bodies/planet3.png"
#define A_PLANET4       "assets/sprites/celestial_bodies/planet4.png"
#define A_PLANET5       "assets/sprites/celestial_bodies/planet5.png"
#define A_PLANET6       "assets/sprites/celestial_bodies/planet6.png"
#define A_PLANET7       "assets/sprites/celestial_bodies/planet7.png"
#define A_STAR1         "assets/sprites/celestial_bodies/star1.png"
#define A_STAR2         "assets/sprites/celestial_bodies/star2.png"

/* SHIPS */
#define A_SHIP1         "assets/sprites/ships/ship1.png"
#define A_SHIP2         "assets/sprites/ships/ship2.png"
#define A_SHIP3         "assets/sprites/ships/ship3.png"
#define A_SHIP4         "assets/sprites/ships/ship4.png"
#define A_SHIP5         "assets/sprites/ships/ship5.png"
#define A_SHIP6         "assets/sprites/ships/ship6.png"
#define A_SHIP7         "assets/sprites/ships/ship7.png"

/* ASTEROIDS */
#define A_ASTEROID1a    "assets/sprites/asteroids/asteroid1a.png"
#define A_ASTEROID1b    "assets/sprites/asteroids/asteroid1b.png"
#define A_ASTEROID2a    "assets/sprites/asteroids/asteroid2a.png"
#define A_ASTEROID2b    "assets/sprites/asteroids/asteroid2b.png"
#define A_ASTEROID3a    "assets/sprites/asteroids/asteroid3a.png"
#define A_ASTEROID3b    "assets/sprites/asteroids/asteroid3b.png"
#define A_ASTEROID4a    "assets/sprites/asteroids/asteroid4a.png"
#define A_ASTEROID4b    "assets/sprites/asteroids/asteroid4b.png"
#define A_ASTEROID5a    "assets/sprites/asteroids/asteroid5a.png"
#define A_ASTEROID5b    "assets/sprites/asteroids/asteroid5b.png"
#define A_ASTEROID6a    "assets/sprites/asteroids/asteroid6a.png"
#define A_ASTEROID6b    "assets/sprites/asteroids/asteroid6b.png"
#define A_ASTEROID7a    "assets/sprites/asteroids/asteroid7a.png"
#define A_ASTEROID7b    "assets/sprites/asteroids/asteroid7b.png"
#define A_ASTEROID8a    "assets/sprites/asteroids/asteroid8a.png"
#define A_ASTEROID8b    "assets/sprites/asteroids/asteroid8b.png"
#define A_ASTEROID9a    "assets/sprites/asteroids/asteroid9a.png"
#define A_ASTEROID9b    "assets/sprites/asteroids/asteroid9b.png"
#define A_ASTEROID10a   "assets/sprites/asteroids/asteroid10a.png"
#define A_ASTEROID10b   "assets/sprites/asteroids/asteroid10b.png"


enum asset {
    /* BG: 1 */
    background0 = 0,

    /* ships: 7 */
    ship1,
    ship2,
    ship3,
    ship4,
    ship5,
    ship6,
    ship7,

    /* asteroids: 20 */
    asteroid1a,
    asteroid1b,
    asteroid2a,
    asteroid2b,
    asteroid3a,
    asteroid3b,
    asteroid4a,
    asteroid4b,
    asteroid5a,
    asteroid5b,
    asteroid6a,
    asteroid6b,
    asteroid7a,
    asteroid7b,
    asteroid8a,
    asteroid8b,
    asteroid9a,
    asteroid9b,
    asteroid10a,
    asteroid10b,

    /* celestial bodies: 16 */
    fog1,
    fog2,
    fog3,
    fog4,
    fog5,
    fog6,
    fog7,
    planet1,
    planet2,
    planet3,
    planet4,
    planet5,
    planet6,
    planet7,
    star1,
    star2,

    last
}; /* TOTAL: 44 */

struct texture_asset {
    enum asset      index;
    char*           path;
};


#endif /* __ASSETS_H__ */
