#include "shooter.h"

void    delay(unsigned int frame_limit)
{
    unsigned int ticks = SDL_GetTicks();

	if (frame_limit < ticks)
	{
		return;
	}
    /* ?? */
	/* if (frame_limit > ticks + 16) */
	/* { */
	/* 	SDL_Delay(16); */
	/* } */
	else
	{
		SDL_Delay(frame_limit - ticks);
	}
}
