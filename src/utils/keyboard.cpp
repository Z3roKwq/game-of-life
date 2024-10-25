//
// Created by Z3roKwq on 10/23/2024.
//

#include "keyboard.h"

#if defined(_WIN32)
   #include <conio.h>

   int Keyboard::GetPressedKey() {
      return _kbhit() ? _getch() : false;
   }
#elif defined(__linux__) || defined(__APPLE__)
   #include <iostream>
   #include <unistd.h>
   #include <termios.h>
   #include <fcntl.h>

   void Keyboard::SetNonCanonicalMode(bool enabled) {
      static struct termios old_tio;

      if (enabled) {
         tcgetattr(STDIN_FILENO, &old_tio);

         struct termios new_tio = old_tio;
         new_tio.c_lflag &= ~(ICANON | ECHO);
         tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

         int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
         fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
      } else {
         tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
      }
   }

   int Keyboard::GetPressedKey() {
      int ch = getchar();
      if (ch != EOF)
         return ch;
      return -1;
   }
#endif