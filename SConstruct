# -*- python -*-

env = Environment(CXXFLAGS=['-Wall', '-O2'],
                  CPPPATH=['../SDL_tty'],
                  LIBS=['SDL_image'])
env.ParseConfig("sdl-config --cflags --libs")
env.Program('keyboard', ['keyboard.cpp', '../SDL_tty/libSDL_tty.a'])

# EOF #
