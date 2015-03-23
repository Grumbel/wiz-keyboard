# -*- python -*-

import os

env = Environment(ENV = os.environ,
                  CXXFLAGS=['-Wall', '-O2'],
                  LIBS=['SDL_image'])
env.ParseConfig("sdl-config --cflags --libs")
env.Append(LIBS='SDL_tty')
env.Program('keyboard', ['keyboard.cpp'])

# EOF #
