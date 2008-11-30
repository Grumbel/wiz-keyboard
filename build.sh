#!/bin/sh

ARMGXX="/aesop/cross/gcc-4.0.2-glibc-2.3.6/arm-linux/bin/arm-linux-g++"
ARMSDLCFG="/aesop/cross/gcc-4.0.2-glibc-2.3.6/arm-linux/arm-linux/bin/sdl-config"

set -x

g++ -Wall -Werror console.cpp -o console `sdl-config --libs --cflags`  -I../SDL_tty/ ../SDL_tty/SDL_tty.c ../SDL_tty/SDL_fnt.c

$ARMGXX -Wall -Werror console.cpp -o console.gpe `$ARMSDLCFG --libs --cflags`  -I../SDL_tty/ ../SDL_tty/SDL_tty.c ../SDL_tty/SDL_fnt.c

$ARMGXX -DGP2X -Wall -Werror keyboard.cpp -o keyboard.gpe `$ARMSDLCFG --libs --cflags`  -I../SDL_tty/ ../SDL_tty/SDL_tty.c ../SDL_tty/SDL_fnt.c -lSDL_image


# EOF #
