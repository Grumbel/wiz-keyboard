# wiz-keyboard - Simple toy keyboard/terminal application
# Copyright (C) 2015 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.0)
project(wiz-keyboard VERSION 0.0.0)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

include_directories(.)
include_directories(src/)
include_directories(external/SDL_tty/include)

add_library(SDL_tty
  external/SDL_tty/src/SDL_fnt.c
  external/SDL_tty/src/SDL_tty.c)
target_link_libraries(SDL_tty ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES})
target_include_directories(SDL_tty SYSTEM PUBLIC ${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIRS})

add_executable(console src/console.cpp)
target_link_libraries(console ${SDL_LIBRARY} SDL_tty)
target_include_directories(console SYSTEM PUBLIC ${SDL_INCLUDE_DIR})

add_executable(wiz-keyboard src/exec.cpp src/keyboard.cpp)
target_link_libraries(wiz-keyboard ${SDL_LIBRARY} SDL_tty)
target_include_directories(wiz-keyboard SYSTEM PUBLIC ${SDL_INCLUDE_DIR})

# EOF #
