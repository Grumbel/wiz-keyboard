wiz-keyboard
============

Simple toy keyboard/terminal application, originally created for the
WIZ, but runs fine on a regular PC as well.

![Screenshot of wiz-keyboard](https://raw.githubusercontent.com/Grumbel/wiz-keyboard/master/screenshot.png)


Compiling
---------

The wiz-keyboard repository uses SDL_tty as a git submodule, so
checkout with:

    git clone --recursive git://github.com/Grumbel/wiz-keyboard

or run:

    git submodule update --init --recursive

to ensure that the `external/SDL_tty/` directory is properly created.

The compilation works via `cmake`:

    mkdir build
    cd build
    cmake ..
    make

To run it, back to the top level directory and run:

    build/build/wiz-keyboard
