//
// Created by Z3roKwq on 10/23/2024.
//

#include "console.h"

#include <utility>

#if defined(_WIN32)
   #include <windows.h>

   void Console::Clear() {
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

      CONSOLE_SCREEN_BUFFER_INFO csbi;
      GetConsoleScreenBufferInfo(hConsole, &csbi);

      DWORD size = csbi.dwSize.X * csbi.dwSize.Y;
      COORD coords = { 0, 0 };
      DWORD written;

      FillConsoleOutputCharacter(hConsole, ' ', size, coords, &written);
      FillConsoleOutputAttribute(hConsole, csbi.wAttributes, size, coords, &written);
      SetConsoleCursorPosition(hConsole, coords);
   }

   void Console::Print(const unsigned char* buffer, const unsigned int size) {
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

      DWORD written;

      WriteConsoleA(hConsole, buffer, size, &written, nullptr);
   }

   std::pair<int, int> Console::GetSize() {
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

      CONSOLE_SCREEN_BUFFER_INFO csbi;
      GetConsoleScreenBufferInfo(hConsole, &csbi);

      return { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
   }
#elif defined(__linux__) || defined(__APPLE__)
   #include <cstdio>
   #include <cstdlib>
   #include <unistd.h>
   #include <sys/ioctl.h>

   void Console::Clear() {
      std::system("clear");
   }

   void Console::Print(const unsigned char* buffer, const unsigned int size) {
      write(STDOUT_FILENO, buffer, size);
   }

   std::pair<int, int> Console::GetSize() {
      struct winsize w;
      ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
      return { w.ws_col, w.ws_row };
   }
#endif