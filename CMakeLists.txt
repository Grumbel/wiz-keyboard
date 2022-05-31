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

cmake_minimum_required(VERSION 3.19)
project(wiz-keyboard VERSION 0.0.0)

include(GNUInstallDirs)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

function(build_dependencies)
  set(BUILD_TESTS OFF)

  find_package(SDL_tty REQUIRED)
  if(NOT TARGET SDL_tty::SDL_tty)
    add_subdirectory(external/SDL_tty/ EXCLUDE_FROM_ALL)
  endif()
endfunction()
build_dependencies()

add_executable(wiz-console src/console.cpp)
target_compile_definitions(wiz-console PRIVATE
  WIZKEYBOARD_DATADIR=\"${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_NAME}\")
target_link_libraries(wiz-console PRIVATE
  SDL_tty::SDL_tty
  ${SDL_IMAGE_LIBRARIES}
  SDL::SDL)
target_include_directories(wiz-console PRIVATE
  ${SDL_IMAGE_INCLUDE_DIRS})

add_executable(wiz-keyboard src/exec.cpp src/keyboard.cpp)
target_compile_definitions(wiz-keyboard PRIVATE
  WIZKEYBOARD_DATADIR=\"${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_NAME}\")
target_link_libraries(wiz-keyboard PRIVATE
  SDL_tty::SDL_tty
  ${SDL_IMAGE_LIBRARIES}
  SDL::SDL)
target_include_directories(wiz-keyboard PRIVATE
  ${SDL_IMAGE_INCLUDE_DIRS})

install(TARGETS wiz-keyboard wiz-console
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

install(DIRECTORY "data/"
  DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}")

# EOF #
