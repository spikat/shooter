bin_PROGRAMS				= spishooter

spishooter_SOURCES			= main.c init.c draw.c inputs.c delay.c \
							  spawning.c assets.c flying_objs.c \
							  player.c collision.c guns.c score.c \
							  particles.c

spishooter_CFLAGS			= -Wall -I$(top_srcdir)/include \
							  ${sdl2_CFLAGS} ${SDL2_ttf_CFLAGS} \
							  ${SDL2_image_CFLAGS}

spishooter_LDADD 			= ${sdl2_LIBS} ${SDL2_ttf_LIBS} \
							  ${SDL2_image_LIBS} -lm

if USE_SOUND
spishooter_CFLAGS			+= ${SDL2_mixer_CFLAGS}
spishooter_LDADD			+= ${SDL2_mixer_LIBS}
endif
