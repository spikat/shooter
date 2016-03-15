bin_PROGRAMS				= spishooter spishooter_static

spishooter_SOURCES			= main.c init.c draw.c inputs.c delay.c
 spishooter_static_SOURCES	= $(spishooter_SOURCES)

spishooter_CFLAGS			= -Wall -I$(top_srcdir)/include $(shell sdl2-config --cflags)
spishooter_static_CFLAGS	= $(spishooter_CFLAGS)


SDL_DEPS					= -lfreetype -lc -ldl -lpulse-simple -lpulse -lsndio -lX11 \
							  -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss -lXxf86vm \
							  -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon \
							  -lrt -ldbus-1 -lxcb -lXrender -lXfixes -lX11-xcb -lICE -lSM \
							  -lXau -lXdmcp -lnsl -lFLAC -lresolv -lpcre -logg -lpng12 \
							  -ljpeg -ltiff -lwebp -lz -llzma -ljbig -lpthread -lstdc++ \
							  -lgcc_s -lreadline -lpcre -ltinfo -lnsl -lmodplug -lresolv \
							  -lmad -lfluidsynth -lvorbis -lvorbisfile

spishooter_LDFLAGS 			= $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image -lSDL2_mixer
spishooter_static_LDFLAGS	= $(shell sdl2-config --static-libs) $(SDL_DEPS)

LIBPATH						= /usr/lib/x86_64-linux-gnu
spishooter_static_LDADD		= $(LIBPATH)/libSDL2.a \
					  		  $(LIBPATH)/libSDL2main.a \
					  		  $(LIBPATH)/libSDL2_ttf.a \
					  		  $(LIBPATH)/libSDL2_image.a \
					  		  $(LIBPATH)/libSDL2_mixer.a

