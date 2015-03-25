#include <SDL.h>
#include <SDL_tty.h>
#include "font8x8.h"

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) < 0 )
    {
      return 1;
    }

  atexit(SDL_Quit);

  SDL_Surface* screen;
  if (!(screen = SDL_SetVideoMode(320, 240, 0, SDL_SWSURFACE)))
    {
      return 1;
    }

  TTY_Font* font = FNT_CreateFromData(font8x8);
  TTY* tty = TTY_Create(40, 30, font);

  TTY_printf(tty, "Mouse Test\n");
  TTY_print(tty, "!\"#&\n'()*+,-./\n"
            "0123456789:;<=>?@\nABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\n");

  int num_joys = SDL_NumJoysticks();
  TTY_printf(tty, "Number of Joystcks: %d\n", num_joys);
  for(int i = 0; i < num_joys; ++i)
    {
      SDL_Joystick* joy = SDL_JoystickOpen(i);
      if (joy)
        {
          TTY_printf(tty, "JoystickName: %d - %s\n", i, SDL_JoystickName (i));
        }
    }

  bool quit = false;
  while(!quit)
    {
      SDL_Event event;
      while(SDL_PollEvent(&event))
        {
          switch(event.type)
            {
              case SDL_QUIT:
                quit = true;
                break;

              case SDL_KEYDOWN:
                TTY_printf(tty, "KeyDown: %3d '%s'\n",
                           (int)event.key.keysym.sym, SDL_GetKeyName(event.key.keysym.sym));
                break;

              case SDL_KEYUP:
                TTY_printf(tty, "KeyUp:   %3d '%s'\n",
                           (int)event.key.keysym.sym, SDL_GetKeyName(event.key.keysym.sym));
                break;

              case SDL_MOUSEBUTTONUP:
                TTY_printf(tty, "MouseButtonUp:   %d - %dx%d\n",
                           event.button.button, event.button.x, event.button.y);
                break;

              case SDL_MOUSEBUTTONDOWN:
                TTY_printf(tty, "MouseButtonDown: %d - %dx%d\n",
                           event.button.button, event.button.x, event.button.y);
                break;

              case SDL_MOUSEMOTION:
                TTY_printf(tty, "MouseMotion:          %dx%d\n", (int)event.motion.x, (int)event.motion.y);
                break;

              case SDL_JOYAXISMOTION:
                TTY_printf(tty, "JoyAxisMotion:          %dx%d\n",
                           (int)event.jaxis.axis, (int)event.jaxis.value);
                break;

              case SDL_JOYBUTTONDOWN:
                TTY_printf(tty, "JoyBtnDown:          %dx%d\n",
                           (int)event.jbutton.button, (int)event.jbutton.state);
                break;

              case SDL_JOYBUTTONUP:
                TTY_printf(tty, "JoyBtnUp:          %dx%d\n",
                           (int)event.jbutton.button, (int)event.jbutton.state);
                break;

              default:
                TTY_printf(tty, "Unknown Event: %d\n", (int)event.type);
                break;
            }
        }

      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
      TTY_Blit(tty, screen, 0, 0);
      SDL_Flip(screen);

      SDL_Delay(33);
    }

  TTY_Free(tty);
  FNT_Free(font);

  return 0;
}

/* EOF */
