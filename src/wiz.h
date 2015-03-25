#ifndef HEADER_WIZ_H
#define HEADER_WIZ_H

/** WIZ buttons are send as Joystick Button events with the following
    button numbers */
enum WizButton {
  WIZ_DPAD_UP         = 0,
  WIZ_DPAD_UP_LEFT    = 1,
  WIZ_DPAD_LEFT       = 2,
  WIZ_DPAD_DOWN_LEFT  = 3,
  WIZ_DPAD_DOWN       = 4,
  WIZ_DPAD_DOWN_RIGHT = 5,
  WIZ_DPAD_RIGHT      = 6,
  WIZ_DPAD_UP_RIGHT   = 7,

  WIZ_BTN_MENU   = 8,
  WIZ_BTN_SELECT = 9,

  WIZ_BTN_L = 10,
  WIZ_BTN_R = 11,

  WIZ_BTN_A = 12,
  WIZ_BTN_B = 13,
  WIZ_BTN_X = 14,
  WIZ_BTN_Y = 15,

  WIZ_VOLUME_UP   = 16,
  WIZ_VOLUME_DOWN = 17
};

#endif

/* EOF */
