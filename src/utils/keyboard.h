//
// Created by Z3roKwq on 10/23/2024.
//

#ifndef KEYBOARD_H
#define KEYBOARD_H

#if defined(_WIN32)
   #define KEY_ESC   0x1B
   #define KEY_UP    0x48
   #define KEY_DOWN  0x50
   #define KEY_LEFT  0x4B
   #define KEY_RIGHT 0x4D
   #define KEY_ENTER 0x0D
#elif defined(__linux__) || defined(__APPLE__)
   #define KEY_ESC   0x1B
   #define KEY_UP    0x41
   #define KEY_DOWN  0x42
   #define KEY_LEFT  0x44
   #define KEY_RIGHT 0x43
   #define KEY_ENTER 0x0A
#endif

class Keyboard {
public:
   #if defined(__linux__) || defined(__APPLE__)
      static void SetNonCanonicalMode(bool enabled);
   #endif

   static int GetPressedKey();
};

#endif //KEYBOARD_H