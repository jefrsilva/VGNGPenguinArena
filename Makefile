CFLAGS = -pedantic -ansi -Wall
CC = clang++
LIBS = -lSDL -lSDL_mixer
SRCS = TitleState.cpp ArenaState.cpp HighScoresState.cpp Arena.cpp CollisionBox.cpp Object.cpp Item.cpp Fish.cpp Seal.cpp Penguin.cpp FishEater.cpp PenguinHUD.cpp Text.cpp WaterFX.cpp PowerUp.cpp ChallengeGenerator.cpp ChallengeStats.cpp
OBJS = TitleState.o ArenaState.o HighScoresState.o Arena.o CollisionBox.o Object.o Item.o Fish.o Seal.o Penguin.o FishEater.o PenguinHUD.o Text.o WaterFX.o PowerUp.o ChallengeGenerator.o ChallengeStats.o

main: main.o ${OBJS}
	${CC} ${CFLAGS} -o $@ main.o ${OBJS} ${LIBS}

.cpp.o:
	${CC} ${CFLAGS} -c $<

depend:
	makedepend ${SRCS}

clean:
	rm *.o *~ main




# DO NOT DELETE

TitleState.o: TitleState.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
TitleState.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
TitleState.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
TitleState.o: /usr/include/features.h /usr/include/sys/cdefs.h
TitleState.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
TitleState.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
TitleState.o: /usr/include/bits/typesizes.h /usr/include/time.h
TitleState.o: /usr/include/endian.h /usr/include/bits/endian.h
TitleState.o: /usr/include/sys/select.h /usr/include/bits/select.h
TitleState.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
TitleState.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
TitleState.o: /usr/include/stdio.h /usr/include/libio.h
TitleState.o: /usr/include/_G_config.h /usr/include/wchar.h
TitleState.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
TitleState.o: /usr/include/stdlib.h /usr/include/alloca.h
TitleState.o: /usr/include/string.h /usr/include/strings.h
TitleState.o: /usr/include/inttypes.h /usr/include/stdint.h
TitleState.o: /usr/include/bits/wchar.h /usr/include/ctype.h
TitleState.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
TitleState.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
TitleState.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
TitleState.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
TitleState.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
TitleState.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
TitleState.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
TitleState.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
TitleState.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
TitleState.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
TitleState.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
TitleState.o: /usr/include/SDL/SDL_mixer.h /usr/include/SDL/SDL_types.h
TitleState.o: GlobalSettings.h GameState.h
ArenaState.o: ArenaState.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
ArenaState.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
ArenaState.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
ArenaState.o: /usr/include/features.h /usr/include/sys/cdefs.h
ArenaState.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ArenaState.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
ArenaState.o: /usr/include/bits/typesizes.h /usr/include/time.h
ArenaState.o: /usr/include/endian.h /usr/include/bits/endian.h
ArenaState.o: /usr/include/sys/select.h /usr/include/bits/select.h
ArenaState.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ArenaState.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ArenaState.o: /usr/include/stdio.h /usr/include/libio.h
ArenaState.o: /usr/include/_G_config.h /usr/include/wchar.h
ArenaState.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ArenaState.o: /usr/include/stdlib.h /usr/include/alloca.h
ArenaState.o: /usr/include/string.h /usr/include/strings.h
ArenaState.o: /usr/include/inttypes.h /usr/include/stdint.h
ArenaState.o: /usr/include/bits/wchar.h /usr/include/ctype.h
ArenaState.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
ArenaState.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
ArenaState.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
ArenaState.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
ArenaState.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
ArenaState.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
ArenaState.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
ArenaState.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
ArenaState.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
ArenaState.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
ArenaState.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
ArenaState.o: /usr/include/SDL/SDL_mixer.h /usr/include/SDL/SDL_types.h
ArenaState.o: GlobalSettings.h GameState.h HighScoresState.h Text.h Object.h
ArenaState.o: CollisionBox.h Item.h Penguin.h Arena.h WaterFX.h
ArenaState.o: ChallengeStats.h Seal.h Fish.h PowerUp.h FishEater.h
ArenaState.o: ChallengeGenerator.h PenguinHUD.h
HighScoresState.o: HighScoresState.h /usr/include/SDL/SDL.h
HighScoresState.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
HighScoresState.o: /usr/include/SDL/SDL_config.h
HighScoresState.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
HighScoresState.o: /usr/include/features.h /usr/include/sys/cdefs.h
HighScoresState.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
HighScoresState.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
HighScoresState.o: /usr/include/bits/typesizes.h /usr/include/time.h
HighScoresState.o: /usr/include/endian.h /usr/include/bits/endian.h
HighScoresState.o: /usr/include/sys/select.h /usr/include/bits/select.h
HighScoresState.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
HighScoresState.o: /usr/include/sys/sysmacros.h
HighScoresState.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
HighScoresState.o: /usr/include/libio.h /usr/include/_G_config.h
HighScoresState.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
HighScoresState.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
HighScoresState.o: /usr/include/alloca.h /usr/include/string.h
HighScoresState.o: /usr/include/strings.h /usr/include/inttypes.h
HighScoresState.o: /usr/include/stdint.h /usr/include/bits/wchar.h
HighScoresState.o: /usr/include/ctype.h /usr/include/iconv.h
HighScoresState.o: /usr/include/SDL/begin_code.h
HighScoresState.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
HighScoresState.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
HighScoresState.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
HighScoresState.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
HighScoresState.o: /usr/include/SDL/SDL_cpuinfo.h
HighScoresState.o: /usr/include/SDL/SDL_events.h
HighScoresState.o: /usr/include/SDL/SDL_active.h
HighScoresState.o: /usr/include/SDL/SDL_keyboard.h
HighScoresState.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
HighScoresState.o: /usr/include/SDL/SDL_video.h
HighScoresState.o: /usr/include/SDL/SDL_joystick.h
HighScoresState.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
HighScoresState.o: /usr/include/SDL/SDL_timer.h
HighScoresState.o: /usr/include/SDL/SDL_version.h GlobalSettings.h Text.h
Arena.o: Arena.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Arena.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Arena.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
Arena.o: /usr/include/features.h /usr/include/sys/cdefs.h
Arena.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Arena.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
Arena.o: /usr/include/bits/typesizes.h /usr/include/time.h
Arena.o: /usr/include/endian.h /usr/include/bits/endian.h
Arena.o: /usr/include/sys/select.h /usr/include/bits/select.h
Arena.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Arena.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Arena.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Arena.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Arena.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Arena.o: /usr/include/alloca.h /usr/include/string.h /usr/include/strings.h
Arena.o: /usr/include/inttypes.h /usr/include/stdint.h
Arena.o: /usr/include/bits/wchar.h /usr/include/ctype.h /usr/include/iconv.h
Arena.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Arena.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Arena.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Arena.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Arena.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Arena.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Arena.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Arena.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Arena.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Arena.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Arena.o: /usr/include/SDL/SDL_version.h GlobalSettings.h
CollisionBox.o: CollisionBox.h
Object.o: Object.h CollisionBox.h GlobalSettings.h
Item.o: Item.h Penguin.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Item.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Item.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
Item.o: /usr/include/features.h /usr/include/sys/cdefs.h
Item.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Item.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
Item.o: /usr/include/bits/typesizes.h /usr/include/time.h
Item.o: /usr/include/endian.h /usr/include/bits/endian.h
Item.o: /usr/include/sys/select.h /usr/include/bits/select.h
Item.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Item.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Item.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Item.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Item.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Item.o: /usr/include/alloca.h /usr/include/string.h /usr/include/strings.h
Item.o: /usr/include/inttypes.h /usr/include/stdint.h
Item.o: /usr/include/bits/wchar.h /usr/include/ctype.h /usr/include/iconv.h
Item.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Item.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Item.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Item.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Item.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Item.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Item.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Item.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Item.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Item.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Item.o: /usr/include/SDL/SDL_version.h /usr/include/SDL/SDL_mixer.h
Item.o: /usr/include/SDL/SDL_types.h GlobalSettings.h Object.h CollisionBox.h
Item.o: Arena.h WaterFX.h ChallengeStats.h
Fish.o: Fish.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Fish.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Fish.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
Fish.o: /usr/include/features.h /usr/include/sys/cdefs.h
Fish.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Fish.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
Fish.o: /usr/include/bits/typesizes.h /usr/include/time.h
Fish.o: /usr/include/endian.h /usr/include/bits/endian.h
Fish.o: /usr/include/sys/select.h /usr/include/bits/select.h
Fish.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Fish.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Fish.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Fish.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Fish.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Fish.o: /usr/include/alloca.h /usr/include/string.h /usr/include/strings.h
Fish.o: /usr/include/inttypes.h /usr/include/stdint.h
Fish.o: /usr/include/bits/wchar.h /usr/include/ctype.h /usr/include/iconv.h
Fish.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Fish.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Fish.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Fish.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Fish.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Fish.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Fish.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Fish.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Fish.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Fish.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Fish.o: /usr/include/SDL/SDL_version.h Object.h CollisionBox.h
Fish.o: GlobalSettings.h Item.h Penguin.h /usr/include/SDL/SDL_mixer.h
Fish.o: /usr/include/SDL/SDL_types.h Arena.h WaterFX.h ChallengeStats.h
Seal.o: Seal.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Seal.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Seal.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
Seal.o: /usr/include/features.h /usr/include/sys/cdefs.h
Seal.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Seal.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
Seal.o: /usr/include/bits/typesizes.h /usr/include/time.h
Seal.o: /usr/include/endian.h /usr/include/bits/endian.h
Seal.o: /usr/include/sys/select.h /usr/include/bits/select.h
Seal.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Seal.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Seal.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Seal.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Seal.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Seal.o: /usr/include/alloca.h /usr/include/string.h /usr/include/strings.h
Seal.o: /usr/include/inttypes.h /usr/include/stdint.h
Seal.o: /usr/include/bits/wchar.h /usr/include/ctype.h /usr/include/iconv.h
Seal.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Seal.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Seal.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Seal.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Seal.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Seal.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Seal.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Seal.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Seal.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Seal.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Seal.o: /usr/include/SDL/SDL_version.h Object.h CollisionBox.h
Seal.o: GlobalSettings.h Arena.h
Penguin.o: Penguin.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Penguin.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Penguin.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
Penguin.o: /usr/include/features.h /usr/include/sys/cdefs.h
Penguin.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Penguin.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
Penguin.o: /usr/include/bits/typesizes.h /usr/include/time.h
Penguin.o: /usr/include/endian.h /usr/include/bits/endian.h
Penguin.o: /usr/include/sys/select.h /usr/include/bits/select.h
Penguin.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Penguin.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Penguin.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Penguin.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Penguin.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Penguin.o: /usr/include/alloca.h /usr/include/string.h /usr/include/strings.h
Penguin.o: /usr/include/inttypes.h /usr/include/stdint.h
Penguin.o: /usr/include/bits/wchar.h /usr/include/ctype.h
Penguin.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
Penguin.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
Penguin.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
Penguin.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
Penguin.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
Penguin.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
Penguin.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
Penguin.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
Penguin.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
Penguin.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
Penguin.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
Penguin.o: /usr/include/SDL/SDL_mixer.h /usr/include/SDL/SDL_types.h
Penguin.o: GlobalSettings.h Object.h CollisionBox.h Arena.h WaterFX.h
Penguin.o: ChallengeStats.h
FishEater.o: FishEater.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
FishEater.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
FishEater.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
FishEater.o: /usr/include/features.h /usr/include/sys/cdefs.h
FishEater.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
FishEater.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
FishEater.o: /usr/include/bits/typesizes.h /usr/include/time.h
FishEater.o: /usr/include/endian.h /usr/include/bits/endian.h
FishEater.o: /usr/include/sys/select.h /usr/include/bits/select.h
FishEater.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
FishEater.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
FishEater.o: /usr/include/stdio.h /usr/include/libio.h
FishEater.o: /usr/include/_G_config.h /usr/include/wchar.h
FishEater.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
FishEater.o: /usr/include/stdlib.h /usr/include/alloca.h
FishEater.o: /usr/include/string.h /usr/include/strings.h
FishEater.o: /usr/include/inttypes.h /usr/include/stdint.h
FishEater.o: /usr/include/bits/wchar.h /usr/include/ctype.h
FishEater.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
FishEater.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
FishEater.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
FishEater.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
FishEater.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
FishEater.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
FishEater.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
FishEater.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
FishEater.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
FishEater.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
FishEater.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
FishEater.o: /usr/include/SDL/SDL_mixer.h /usr/include/SDL/SDL_types.h
FishEater.o: Object.h CollisionBox.h GlobalSettings.h Penguin.h Arena.h
FishEater.o: WaterFX.h ChallengeStats.h ChallengeGenerator.h Text.h
PenguinHUD.o: PenguinHUD.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
PenguinHUD.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
PenguinHUD.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
PenguinHUD.o: /usr/include/features.h /usr/include/sys/cdefs.h
PenguinHUD.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
PenguinHUD.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
PenguinHUD.o: /usr/include/bits/typesizes.h /usr/include/time.h
PenguinHUD.o: /usr/include/endian.h /usr/include/bits/endian.h
PenguinHUD.o: /usr/include/sys/select.h /usr/include/bits/select.h
PenguinHUD.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
PenguinHUD.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
PenguinHUD.o: /usr/include/stdio.h /usr/include/libio.h
PenguinHUD.o: /usr/include/_G_config.h /usr/include/wchar.h
PenguinHUD.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
PenguinHUD.o: /usr/include/stdlib.h /usr/include/alloca.h
PenguinHUD.o: /usr/include/string.h /usr/include/strings.h
PenguinHUD.o: /usr/include/inttypes.h /usr/include/stdint.h
PenguinHUD.o: /usr/include/bits/wchar.h /usr/include/ctype.h
PenguinHUD.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
PenguinHUD.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
PenguinHUD.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
PenguinHUD.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
PenguinHUD.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
PenguinHUD.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
PenguinHUD.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
PenguinHUD.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
PenguinHUD.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
PenguinHUD.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
PenguinHUD.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
PenguinHUD.o: Penguin.h /usr/include/SDL/SDL_mixer.h
PenguinHUD.o: /usr/include/SDL/SDL_types.h GlobalSettings.h Object.h
PenguinHUD.o: CollisionBox.h Arena.h WaterFX.h ChallengeStats.h Text.h
PenguinHUD.o: PowerUp.h Item.h
Text.o: Text.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
Text.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
Text.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
Text.o: /usr/include/features.h /usr/include/sys/cdefs.h
Text.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Text.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
Text.o: /usr/include/bits/typesizes.h /usr/include/time.h
Text.o: /usr/include/endian.h /usr/include/bits/endian.h
Text.o: /usr/include/sys/select.h /usr/include/bits/select.h
Text.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Text.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Text.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
Text.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
Text.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
Text.o: /usr/include/alloca.h /usr/include/string.h /usr/include/strings.h
Text.o: /usr/include/inttypes.h /usr/include/stdint.h
Text.o: /usr/include/bits/wchar.h /usr/include/ctype.h /usr/include/iconv.h
Text.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
Text.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
Text.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
Text.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
Text.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
Text.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
Text.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
Text.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
Text.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
Text.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
Text.o: /usr/include/SDL/SDL_version.h
WaterFX.o: WaterFX.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
WaterFX.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
WaterFX.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
WaterFX.o: /usr/include/features.h /usr/include/sys/cdefs.h
WaterFX.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
WaterFX.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
WaterFX.o: /usr/include/bits/typesizes.h /usr/include/time.h
WaterFX.o: /usr/include/endian.h /usr/include/bits/endian.h
WaterFX.o: /usr/include/sys/select.h /usr/include/bits/select.h
WaterFX.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
WaterFX.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
WaterFX.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
WaterFX.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
WaterFX.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
WaterFX.o: /usr/include/alloca.h /usr/include/string.h /usr/include/strings.h
WaterFX.o: /usr/include/inttypes.h /usr/include/stdint.h
WaterFX.o: /usr/include/bits/wchar.h /usr/include/ctype.h
WaterFX.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
WaterFX.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
WaterFX.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
WaterFX.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
WaterFX.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
WaterFX.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
WaterFX.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
WaterFX.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
WaterFX.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
WaterFX.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
WaterFX.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
WaterFX.o: Object.h CollisionBox.h GlobalSettings.h Arena.h
PowerUp.o: PowerUp.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
PowerUp.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
PowerUp.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
PowerUp.o: /usr/include/features.h /usr/include/sys/cdefs.h
PowerUp.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
PowerUp.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
PowerUp.o: /usr/include/bits/typesizes.h /usr/include/time.h
PowerUp.o: /usr/include/endian.h /usr/include/bits/endian.h
PowerUp.o: /usr/include/sys/select.h /usr/include/bits/select.h
PowerUp.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
PowerUp.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
PowerUp.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
PowerUp.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
PowerUp.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
PowerUp.o: /usr/include/alloca.h /usr/include/string.h /usr/include/strings.h
PowerUp.o: /usr/include/inttypes.h /usr/include/stdint.h
PowerUp.o: /usr/include/bits/wchar.h /usr/include/ctype.h
PowerUp.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
PowerUp.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
PowerUp.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
PowerUp.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
PowerUp.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
PowerUp.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
PowerUp.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
PowerUp.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
PowerUp.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
PowerUp.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
PowerUp.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
PowerUp.o: GlobalSettings.h Object.h CollisionBox.h Item.h Penguin.h
PowerUp.o: /usr/include/SDL/SDL_mixer.h /usr/include/SDL/SDL_types.h Arena.h
PowerUp.o: WaterFX.h ChallengeStats.h
ChallengeGenerator.o: ChallengeGenerator.h /usr/include/SDL/SDL.h
ChallengeGenerator.o: /usr/include/SDL/SDL_main.h
ChallengeGenerator.o: /usr/include/SDL/SDL_stdinc.h
ChallengeGenerator.o: /usr/include/SDL/SDL_config.h
ChallengeGenerator.o: /usr/include/SDL/SDL_platform.h
ChallengeGenerator.o: /usr/include/sys/types.h /usr/include/features.h
ChallengeGenerator.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ChallengeGenerator.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
ChallengeGenerator.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ChallengeGenerator.o: /usr/include/time.h /usr/include/endian.h
ChallengeGenerator.o: /usr/include/bits/endian.h /usr/include/sys/select.h
ChallengeGenerator.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
ChallengeGenerator.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
ChallengeGenerator.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
ChallengeGenerator.o: /usr/include/libio.h /usr/include/_G_config.h
ChallengeGenerator.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
ChallengeGenerator.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
ChallengeGenerator.o: /usr/include/alloca.h /usr/include/string.h
ChallengeGenerator.o: /usr/include/strings.h /usr/include/inttypes.h
ChallengeGenerator.o: /usr/include/stdint.h /usr/include/bits/wchar.h
ChallengeGenerator.o: /usr/include/ctype.h /usr/include/iconv.h
ChallengeGenerator.o: /usr/include/SDL/begin_code.h
ChallengeGenerator.o: /usr/include/SDL/close_code.h
ChallengeGenerator.o: /usr/include/SDL/SDL_audio.h
ChallengeGenerator.o: /usr/include/SDL/SDL_error.h
ChallengeGenerator.o: /usr/include/SDL/SDL_endian.h
ChallengeGenerator.o: /usr/include/SDL/SDL_mutex.h
ChallengeGenerator.o: /usr/include/SDL/SDL_thread.h
ChallengeGenerator.o: /usr/include/SDL/SDL_rwops.h
ChallengeGenerator.o: /usr/include/SDL/SDL_cdrom.h
ChallengeGenerator.o: /usr/include/SDL/SDL_cpuinfo.h
ChallengeGenerator.o: /usr/include/SDL/SDL_events.h
ChallengeGenerator.o: /usr/include/SDL/SDL_active.h
ChallengeGenerator.o: /usr/include/SDL/SDL_keyboard.h
ChallengeGenerator.o: /usr/include/SDL/SDL_keysym.h
ChallengeGenerator.o: /usr/include/SDL/SDL_mouse.h
ChallengeGenerator.o: /usr/include/SDL/SDL_video.h
ChallengeGenerator.o: /usr/include/SDL/SDL_joystick.h
ChallengeGenerator.o: /usr/include/SDL/SDL_quit.h
ChallengeGenerator.o: /usr/include/SDL/SDL_loadso.h
ChallengeGenerator.o: /usr/include/SDL/SDL_timer.h
ChallengeGenerator.o: /usr/include/SDL/SDL_version.h
ChallengeGenerator.o: /usr/include/SDL/SDL_mixer.h
ChallengeGenerator.o: /usr/include/SDL/SDL_types.h Text.h Penguin.h
ChallengeGenerator.o: GlobalSettings.h Object.h CollisionBox.h Arena.h
ChallengeGenerator.o: WaterFX.h ChallengeStats.h
ChallengeStats.o: ChallengeStats.h GlobalSettings.h
