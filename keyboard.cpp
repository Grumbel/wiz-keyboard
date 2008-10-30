#include <vector>
#include <assert.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_tty.h>
#include <unistd.h>
//#include "exec.hpp"
#include "fontc64.h"

/*
SDLKey matrix[] = {
  SDLK_ESCAPE,   SDLK_ESCAPE,   SDLK_F1,    SDLK_F2,    SDLK_F3,    SDLK_F4,    SDLK_F5,    SDLK_F6,    SDLK_F7,    SDLK_F8,    SDLK_F9,     SDLK_F10,       SDLK_F11,         SDLK_F12,          SDLK_BACKSPACE, SDLK_BACKSPACE,
  SDLK_TAB,      SDLK_TAB,      SDLK_1,      SDLK_2,    SDLK_3,     SDLK_4,     SDLK_5,     SDLK_6,     SDLK_7,     SDLK_8,     SDLK_9,      SDLK_0,         SDLK_MINUS,       SDLK_EQUALS,       SDLK_RETURN,    SDLK_RETURN,
  SDLK_TAB,      SDLK_TAB,      SDLK_q,      SDLK_w,    SDLK_e,     SDLK_r,     SDLK_t,     SDLK_y,     SDLK_u,     SDLK_i,     SDLK_o,      SDLK_p,         SDLK_LEFTBRACKET, SDLK_RIGHTBRACKET, SDLK_RETURN,    SDLK_RETURN,
  SDLK_CAPSLOCK, SDLK_CAPSLOCK, SDLK_a,      SDLK_s,    SDLK_d,     SDLK_f,     SDLK_g,     SDLK_h,     SDLK_j,     SDLK_k,     SDLK_l,      SDLK_SEMICOLON, SDLK_ASTERISK,    SDLK_UNKNOWN,      SDLK_UNKNOWN,   SDLK_UNKNOWN, 
  SDLK_LSHIFT,   SDLK_LSHIFT,   SDLK_z,      SDLK_x,    SDLK_c,     SDLK_v,     SDLK_b,     SDLK_n,     SDLK_m,     SDLK_COMMA, SDLK_PERIOD, SDLK_SLASH,     SDLK_BACKSLASH,   SDLK_UNKNOWN,      SDLK_UP,        SDLK_UNKNOWN,
  SDLK_LCTRL,    SDLK_LCTRL,    SDLK_LALT,   SDLK_LALT, SDLK_SPACE, SDLK_SPACE, SDLK_SPACE, SDLK_SPACE, SDLK_SPACE, SDLK_SPACE, SDLK_SPACE,  SDLK_RALT,      SDLK_RALT,        SDLK_LEFT,         SDLK_DOWN,      SDLK_RIGHT
};
*/
enum {
  K_ESC = 256,
  K_TAB,
  K_CAPS,
  K_SHIFT,
  K_CTRL,
  K_ALT,
  K_BKSPC,
  K_RETURN,
  K_F1,
  K_F2,
  K_F3,
  K_F4,
  K_F5,
  K_F6,
  K_F7,
  K_F8,
  K_F9,
  K_F10,
  K_F11,
  K_F12,
  K_UP,
  K_DOWN,
  K_LEFT,
  K_RIGHT,
};

int matrix[] = {
  K_ESC,   K_ESC,  K_F1, K_F2, K_F3, K_F4, K_F5, K_F6, K_F7, K_F8, K_F9, K_F10, K_F11, K_F12, K_BKSPC, K_BKSPC,
  K_TAB,   K_TAB,   '1',  '2',   '3',   '4',   '5',   '6',   '7',   '8',   '9',    '0', '-', '=', K_RETURN, K_RETURN,
  K_TAB,   K_TAB,   'q',  'w',   'e',   'r',   't',   'y',   'u',   'i',   'o',    'p', '[', ']', K_RETURN, K_RETURN,
  K_CAPS,  K_CAPS,  'a',  's',   'd',   'f',   'g',   'h',   'j',   'k',   'l',    ';', '\'', '\0', '\0', '\0',
  K_SHIFT, K_SHIFT, 'z',  'x',   'c',   'v',   'b',   'n',   'm',   ',',   '.',    '/', '\\', '\0', K_UP, '\0',
  K_CTRL,  K_CTRL, K_ALT, K_ALT, ' ', ' ', ' ', ' ', ' ', ' ', ' ',  K_ALT, K_ALT, K_LEFT, K_DOWN, K_RIGHT
};

int matrix_shift[] = {
  K_ESC,   K_ESC,  K_F1, K_F2, K_F3, K_F4, K_F5, K_F6, K_F7, K_F8, K_F9, K_F10, K_F11, K_F12, K_BKSPC, K_BKSPC,
  K_TAB,   K_TAB,   '!',  '@',   '#',   '$',   '%',   '^',   '&',   '*',   '(',    ')', '_', '+', K_RETURN, K_RETURN,
  K_TAB,   K_TAB,   'Q',  'W',   'E',   'R',   'T',   'Y',   'U',   'I',   'O',    'P', '{', '}', K_RETURN, K_RETURN,
  K_CAPS,  K_CAPS,  'A',  'S',   'D',   'F',   'G',   'H',   'J',   'K',   'L',    ':', '"', '\0', '\0', '\0',
  K_SHIFT, K_SHIFT, 'Z',  'X',   'C',   'V',   'B',   'N',   'M',   '<',   '>',    '?', '|', '\0', K_UP, '\0',
  K_CTRL,  K_CTRL, K_ALT, K_ALT, ' ', ' ', ' ', ' ', ' ', ' ', ' ',  K_ALT, K_ALT, K_LEFT, K_DOWN, K_RIGHT
};

std::vector<std::string>
tokenize(const std::string& str, char split_char)
{
  std::string::size_type start = 0;
  std::string::size_type end   = 0;

  std::vector<std::string> tokens;

  while (start < str.size())
    {
      if ((end = str.find(split_char, start)) == std::string::npos)
        {
          tokens.push_back(str.substr(start));
          break;
        }

      const std::string& ret = str.substr(start, end - start);

      if (!ret.empty())
        tokens.push_back(ret);

      start = end + 1;
    }

  return tokens;
}

SDL_Surface* load_surface(const std::string& name)
{
  SDL_Surface* tmp = IMG_Load(name.c_str());
  if (!tmp)
    {
      std::cout << "Error: " << SDL_GetError() << std::endl;
      return 0;
    }
  SDL_Surface* res = SDL_DisplayFormat(tmp);
  SDL_FreeSurface(tmp);
  return res;
}

void eval(const std::vector<std::string>& tokens)
{
  std::string cmd = tokens.front();

  if (cmd == "cd")
    {
      
    }
  else if (cmd == "ls")
    {
      
    }
}

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0 ) 
    {
      return 1;
    }
  
  atexit(SDL_Quit);
  
  SDL_Surface* screen;
  if (!(screen = SDL_SetVideoMode(320, 240, 0, SDL_HWSURFACE|SDL_DOUBLEBUF)))
    {
      return 1;
    }

  SDL_Surface* keyboard_normal = load_surface("keyboard_normal.png");
  SDL_Surface* keyboard_shift  = load_surface("keyboard_shift.png");

  TTY_Font* font = FNT_CreateFromData(fontc64);
  TTY* tty = TTY_Create(312/8, 112/8, font);

  TTY_printf(tty, "\n   **** COMMODORE 64 BASIC V%d ****\n\n", 2);
  TTY_printf(tty, "%dk RAM SYSTEM  38911 BASIC BYTES FREE\n\n", 64);
  TTY_printf(tty, "READY.\n");

  TTY_EnableVisibleCursor(tty, 1);

  bool quit = false;
  bool mouse_down = false;
  int  mouse_x = 0;
  int  mouse_y = 0;
  bool shifted = false;
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
                //TTY_printf(tty, "MouseButtonUp:   %d - %dx%d\n",
                //           event.button.button, event.button.x, event.button.y);
                mouse_down = false;
                mouse_x = event.button.x;
                mouse_y = event.button.y;
                break;

              case SDL_MOUSEBUTTONDOWN:
                //TTY_printf(tty, "MouseButtonDown: %d - %dx%d\n", 
                //           event.button.button, event.button.x, event.button.y);
                mouse_down = true;
                mouse_x = event.button.x;
                mouse_y = event.button.y;

                {
                  int key = shifted ? matrix_shift[(mouse_x/20) + ((mouse_y - 120)/20) * 16] :
                    matrix[(mouse_x/20) + ((mouse_y - 120)/20) * 16];
                  //TTY_printf(tty, "Key: %s\n", SDL_GetKeyName(key));
                  if (key < 256)
                    {
                      TTY_putchar(tty, (char)key);
                    }
                  else
                    {
                      switch(key)
                        {
                          case K_SHIFT:
                            shifted = !shifted;
                            break;

                          case K_RETURN:
                            {
                              char line[256];
                              int cx, cy;
                              TTY_GetCursor(tty, &cx, &cy);
                          
                              for(int i = 0; i < tty->width; ++i)
                                {
                                  line[i] = TTY_GetChar(tty, i, cy);
                                  line[i+1] = '\0';
                                }

                              TTY_putchar(tty, '\n');

                              //TTY_printf(tty, "Line: '%s'\n", line);
                              std::vector<std::string> tokens = tokenize(line, ' ');
                              if (!tokens.empty())
                                {
                                  eval(tokens);
                                  /*
                                  if (tokens.front() == "cd")
                                    {
                                      if (tokens.size() == 2)
                                        chdir(tokens[1].c_str());
                                      else
                                        TTY_print(tty, "Error: cd requires one directory argument");
                                    }
                                  else
                                    {
                                      Exec exec(tokens.front());
                                        for(std::vector<std::string>::iterator i = tokens.begin()+1; i != tokens.end(); ++i)
                                        {
                                        exec.arg(*i);
                                        }

                                        exec.exec();

                                        TTY_print(tty, std::string(exec.get_stdout().begin(), exec.get_stdout().end()).c_str());
                                        TTY_print(tty, std::string(exec.get_stderr().begin(), exec.get_stderr().end()).c_str());
                                        }
                                        }
                                  */
                                }
                            }
                            break;

                          case K_BKSPC:
                            {
                              int cx, cy;
                              TTY_GetCursor(tty, &cx, &cy);
                              TTY_SetCursor(tty, cx-1, cy);
                              TTY_putchar_nomove(tty, ' ');
                            }
                            break;

                          case K_LEFT:
                            {
                              int cx, cy;
                              TTY_GetCursor(tty, &cx, &cy);
                              TTY_SetCursor(tty, cx-1, cy);
                            }
                            break;

                          case K_RIGHT:
                            {
                              int cx, cy;
                              TTY_GetCursor(tty, &cx, &cy);
                              TTY_SetCursor(tty, cx+1, cy);
                            }
                            break;

                          case K_UP:
                            {
                              int cx, cy;
                              TTY_GetCursor(tty, &cx, &cy);
                              TTY_SetCursor(tty, cx, cy-1);
                            }
                            break;

                          case K_DOWN:
                            {
                              int cx, cy;
                              TTY_GetCursor(tty, &cx, &cy);
                              TTY_SetCursor(tty, cx, cy+1);
                            }
                            break;

                          default:
                            break;
                        }
                    }
                }
                break;
                
              case SDL_MOUSEMOTION:
                //TTY_printf(tty, "MouseMotion:          %dx%d\n", event.motion.x, event.motion.y);
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
                break;

              default:
                //TTY_printf(tty, "Unknown: %d\n", (int)event.type);
                break;
            }
        }

      //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 0, 0));
      if (shifted)
        SDL_BlitSurface(keyboard_shift, NULL, screen, NULL);
      else
        SDL_BlitSurface(keyboard_normal, NULL, screen, NULL);

      TTY_Blit(tty, screen, 4, 4);


      if (mouse_down && mouse_y > 120)
        {
          SDL_Rect rect;
          rect.x = (mouse_x)/20 * 20;
          rect.y = (mouse_y)/20 * 20;
          rect.w = 20;
          rect.h = 20;

          SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 0));
        }

      SDL_Flip(screen);

      SDL_Delay(33);
    }

  TTY_Free(tty);
  FNT_Free(font);

  return 0;
}

/* EOF */
